#ifndef RISCV_SIM_DATAMEMORYSTORAGE_H
#define RISCV_SIM_DATAMEMORYSTORAGE_H

#include "Instruction.h"
#include <iostream>
#include <fstream>
#include "elf.h"
#include <cstring>
#include <vector>
#include <cassert>
#include <map>
#include <array>

static constexpr size_t memSize = 1024 * 1024; // memory size in 4-byte words

//MR 22 variant
static constexpr size_t lineSizeBytes = 128;
static constexpr size_t codeCacheSize = 1024;
static constexpr size_t dataCacheSize = 4096;
static constexpr size_t accessTime = 152;
static constexpr size_t lineSizeWords = lineSizeBytes / sizeof(Word);

using Line = std::array<Word, lineSizeWords>;
static Word ToWordAddr(Word addr) { return addr >> 2u; }
static Word ToLineAddr(Word addr) { return addr & ~(lineSizeBytes - 1); }
static Word ToLineOffset(Word addr) { return ToWordAddr(addr) & (lineSizeWords - 1); }

class MemoryStorage {
public:

	MemoryStorage()
	{
		_mem.resize(memSize);
	}

	bool LoadElf(const std::string &elf_filename)
	{
		std::ifstream elffile;
		elffile.open(elf_filename, std::ios::in | std::ios::binary);

		if (!elffile.is_open()) {
			std::cerr << "ERROR: load_elf: failed opening file \"" << elf_filename.c_str() << "\"" << std::endl;
			return false;
		}

		elffile.seekg(0, elffile.end);
		size_t buf_sz = elffile.tellg();
		elffile.seekg(0, elffile.beg);

		// Read the entire file. If it doesn't fit in host memory, it won't fit in the risc-v processor
		std::vector<char> buf(buf_sz);
		elffile.read(buf.data(), buf_sz);

		if (!elffile) {
			std::cerr << "ERROR: load_elf: failed reading elf header" << std::endl;
			return false;
		}

		if (buf_sz < sizeof(Elf32_Ehdr)) {
			std::cerr << "ERROR: load_elf: file too small to be a valid elf file" << std::endl;
			return false;
		}

		// make sure the header matches elf32 or elf64
		Elf32_Ehdr *ehdr = (Elf32_Ehdr *)buf.data();
		unsigned char* e_ident = ehdr->e_ident;
		if (e_ident[EI_MAG0] != ELFMAG0
			|| e_ident[EI_MAG1] != ELFMAG1
			|| e_ident[EI_MAG2] != ELFMAG2
			|| e_ident[EI_MAG3] != ELFMAG3) {
			std::cerr << "ERROR: load_elf: file is not an elf file" << std::endl;
			return false;
		}

		if (e_ident[EI_CLASS] == ELFCLASS32) {
			// 32-bit ELF
			return this->LoadElfSpecific<Elf32_Ehdr, Elf32_Phdr>(buf.data(), buf_sz);
		}
		else if (e_ident[EI_CLASS] == ELFCLASS64) {
			// 64-bit ELF
			return this->LoadElfSpecific<Elf64_Ehdr, Elf64_Phdr>(buf.data(), buf_sz);
		}
		else {
			std::cerr << "ERROR: load_elf: file is neither 32-bit nor 64-bit" << std::endl;
			return false;
		}
	}

	Word Read(Word ip)
	{
		return _mem[ToWordAddr(ip)];
	}

	void Write(Word ip, Word data)
	{
		_mem[ToWordAddr(ip)] = data;
	}

	Line ReadLine(Word lineBegin)
	{
		Line line;
		for (int i = 0; i < line.size(); i++) {
			line[i] = _mem[lineBegin + i];
		}
		return line;
	}

	void WriteLine(Word lineBegin, const Line& line)
	{
		for (int i = 0; i < line.size(); i++) {
			_mem[lineBegin + i] = line[i];
		}
	}

private:
	template <typename Elf_Ehdr, typename Elf_Phdr>
	bool LoadElfSpecific(char *buf, size_t buf_sz)
	{
		// 64-bit ELF
		Elf_Ehdr *ehdr = (Elf_Ehdr*)buf;
		Elf_Phdr *phdr = (Elf_Phdr*)(buf + ehdr->e_phoff);
		if (buf_sz < ehdr->e_phoff + ehdr->e_phnum * sizeof(Elf_Phdr)) {
			std::cerr << "ERROR: load_elf: file too small for expected number of program header tables" << std::endl;
			return false;
		}
		auto memptr = reinterpret_cast<char*>(_mem.data());
		// loop through program header tables
		for (int i = 0; i < ehdr->e_phnum; i++) {
			if ((phdr[i].p_type == PT_LOAD) && (phdr[i].p_memsz > 0)) {
				if (phdr[i].p_memsz < phdr[i].p_filesz) {
					std::cerr << "ERROR: load_elf: file size is larger than memory size" << std::endl;
					return false;
				}
				if (phdr[i].p_filesz > 0) {
					if (phdr[i].p_offset + phdr[i].p_filesz > buf_sz) {
						std::cerr << "ERROR: load_elf: file section overflow" << std::endl;
						return false;
					}

					// start of file section: buf + phdr[i].p_offset
					// end of file section: buf + phdr[i].p_offset + phdr[i].p_filesz
					// start of memory: phdr[i].p_paddr
					std::memcpy(memptr + phdr[i].p_paddr, buf + phdr[i].p_offset, phdr[i].p_filesz);
				}
				if (phdr[i].p_memsz > phdr[i].p_filesz) {
					// copy 0's to fill up remaining memory
					size_t zeros_sz = phdr[i].p_memsz - phdr[i].p_filesz;
					std::memset(memptr + phdr[i].p_paddr + phdr[i].p_filesz, 0, zeros_sz);
				}
			}
		}
		return true;
	}

	std::vector<Word> _mem;
};

#endif //RISCV_SIM_DATAMEMORYSTORAGE_H