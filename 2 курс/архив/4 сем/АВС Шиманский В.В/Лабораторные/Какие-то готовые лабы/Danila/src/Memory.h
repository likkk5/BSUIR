
#ifndef RISCV_SIM_DATAMEMORY_H
#define RISCV_SIM_DATAMEMORY_H

#include "Instruction.h"
#include <iostream>
#include <fstream>
#include <elf.h>
#include <cstring>
#include <vector>
#include <cassert>
#include <map>


static constexpr size_t memSize = 1024*1024; // memory size in 4-byte words

static constexpr size_t lineSizeBytes = 128;
static constexpr size_t instrCacheSize = 2048;
static constexpr size_t dataCacheSize = 1024;
static constexpr size_t accessTime = 152;
static constexpr size_t lineSizeWords = lineSizeBytes / sizeof(Word);
using Line = std::array<Word, lineSizeWords>;
static Word ToWordAddr(Word addr) { return addr >> 2u; }
static Word ToLineAddr(Word addr) { return addr & ~(lineSizeBytes - 1); }
static Word ToLineOffset(Word addr) { return ToWordAddr(addr) & (lineSizeWords - 1); }

struct LineInfo 
{
    Word tag;
    Word lru;
    bool rewrite = false;
};

class MemoryStorage {
public:

    MemoryStorage()
    {
        _mem.resize(memSize);
    }

    bool LoadElf(const std::string &elf_filename) {
        std::ifstream elffile;
        elffile.open(elf_filename, std::ios::in | std::ios::binary);

        if (!elffile.is_open()) {
            std::cerr << "ERROR: load_elf: failed opening file \"" << elf_filename << "\"" << std::endl;
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
        Elf32_Ehdr *ehdr = (Elf32_Ehdr *) buf.data();
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
        } else if (e_ident[EI_CLASS] == ELFCLASS64) {
            // 64-bit ELF
            return this->LoadElfSpecific<Elf64_Ehdr, Elf64_Phdr>(buf.data(), buf_sz);
        } else {
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

    void ReadLine(Word lineBegin, Line& line)
    {
        for (int i = 0; i < line.size(); i++) {
            line[i] = _mem[lineBegin + i];
        }
    }

    void WriteLine(Word lineBegin, Line& line) 
    {
        for (int i = 0; i < line.size(); i++) {
            _mem[lineBegin + i] = line[i];
        }
    }

private:
    template <typename Elf_Ehdr, typename Elf_Phdr>
    bool LoadElfSpecific(char *buf, size_t buf_sz) {
        // 64-bit ELF
        Elf_Ehdr *ehdr = (Elf_Ehdr*) buf;
        Elf_Phdr *phdr = (Elf_Phdr*) (buf + ehdr->e_phoff);
        if (buf_sz < ehdr->e_phoff + ehdr->e_phnum * sizeof(Elf_Phdr)) {
            std::cerr << "ERROR: load_elf: file too small for expected number of program header tables" << std::endl;
            return false;
        }
        auto memptr = reinterpret_cast<char*>(_mem.data());
        // loop through program header tables
        for (int i = 0 ; i < ehdr->e_phnum ; i++) {
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


class IMem
{
public:
    IMem() = default;
    virtual ~IMem() = default;
    IMem(const IMem &) = delete;
    IMem(IMem &&) = delete;

    IMem& operator=(const IMem&) = delete;
    IMem& operator=(IMem&&) = delete;

    virtual void Request(Word ip) = 0;
    virtual std::optional<Word> Response() = 0;
    virtual void Request(InstructionPtr &instr) = 0;
    virtual bool Response(InstructionPtr &instr) = 0;
    virtual void Clock() = 0;
};


class UncachedMem : public IMem
{
public:
    explicit UncachedMem(MemoryStorage& amem)
        : _mem(amem)
    {

    }

    void Request(Word ip)
    {
        _requestedIp = ip;
        _waitCycles = latency;
    }

    std::optional<Word> Response()
    {
        if (_waitCycles > 0)
            return std::optional<Word>();
        return _mem.Read(_requestedIp);
    }

    void Request(InstructionPtr &instr)
    {
        if (instr->_type != IType::Ld && instr->_type != IType::St)
            return;

        Request(instr->_addr);
    }

    bool Response(InstructionPtr &instr)
    {
        if (instr->_type != IType::Ld && instr->_type != IType::St)
            return true;

        if (_waitCycles != 0)
            return false;

        if (instr->_type == IType::Ld)
            instr->_data = _mem.Read(instr->_addr);
        else if (instr->_type == IType::St)
            _mem.Write(instr->_addr, instr->_data);

        return true;
    }

    void Clock()
    {
        if (_waitCycles > 0)
            --_waitCycles;
    }
private:
    static constexpr size_t latency = 120;
    Word _requestedIp = 0;
    size_t _waitCycles = 0;
    MemoryStorage& _mem;
};

class CachedMem : public IMem
{
public:
    explicit CachedMem(MemoryStorage& amem)///      в конструкторе резервирует количество линий кэш кода и кэш данных
        : _mem(amem)
    {
        Word isntrCacheLines = instrCacheSize / lineSizeBytes;
        _cacheInstr.resize(isntrCacheLines);
        Word dataCacheLines = dataCacheSize / lineSizeBytes;
        _cacheData.resize(dataCacheLines);
    }

    
    void Request(Word ip) //начало
    {

        _check_cache = false;
        _requestedIp = ip;
        _cacheWaitCycles = 3;
        _memWaitCycles = cacheLatency;
    }
    // std::optional<Word> Response()
    // {

    //        if (_memWaitCycles > 0)
    //         return std::optional<Word>();
        
    //     Word rewriteLine = 0;
    //     for (int i = 0; i < _cacheInstr.size(); i++) {
    //             rewriteLine = i;
    //         }
    //     }

    //     Word lineAddr = ToLineAddr(_requestedIp);

    //     _mem.ReadLine(ToWordAddr(lineAddr), _cacheInstr[rewriteLine].second);
    //     _cacheInstr[rewriteLine].first.tag = lineAddr;
    //     _cacheInstr[rewriteLine].first.lru = 0;

    //     return _cacheInstr[rewriteLine].second[offset];
        
    // }
    

    void Request(InstructionPtr &instr)
    {
        if (instr->_type != IType::Ld && instr->_type != IType::St)
            return;

        Request(instr->_addr);
    }

    bool Response(InstructionPtr &instr)  {
        if (instr->_type != IType::Ld && instr->_type != IType::St)
            return true;

        if (_cacheWaitCycles > 0)
            return false;

        Word offset = ToLineOffset(_requestedIp);
        Word lineAddr = ToLineAddr(_requestedIp);
        
        if (!_check_cache) {

            for (int i = 0; i < _cacheData.size(); i++) {
                if (lineAddr == _cacheData[i].first.tag) {
                    for (int j = i + 1; j < _cacheData.size(); j++) 
                        _cacheData[j].first.lru++;
                    _cacheData[i].first.lru = 0;

                    if (instr->_type == IType::Ld) {
                        instr->_data = _cacheData[i].second[offset];
                    } else if (instr->_type == IType::St) {
                        _cacheData[i].second[offset] = instr->_data;
                        _cacheData[i].first.rewrite = true;
                    }
                    return true;
                } else {
                    _cacheData[i].first.lru++;
                }
            }
            _check_cache = true;
        } 

        if (_memWaitCycles > 0)
            return false;
        
        Word rewriteLine = 0;
        for (int i = 0; i < _cacheData.size(); i++) {
            if (_cacheData[rewriteLine].first.lru < _cacheData[i].first.lru) {
                rewriteLine = i;
            }
        }


        if (_cacheData[rewriteLine].first.rewrite) {
            _mem.WriteLine(
                ToWordAddr(_cacheData[rewriteLine].first.tag), 
                _cacheData[rewriteLine].second
            );
        }

        _mem.ReadLine(
            ToWordAddr(lineAddr),
            _cacheData[rewriteLine].second
        );
        _cacheData[rewriteLine].first.lru = 0;
        _cacheData[rewriteLine].first.rewrite = false;
        _cacheData[rewriteLine].first.tag = lineAddr;

        if (instr->_type == IType::Ld) {
            instr->_data = _cacheData[rewriteLine].second[offset];
        } else if (instr->_type == IType::St) {
            _cacheData[rewriteLine].second[offset] = instr->_data;
            _cacheData[rewriteLine].first.rewrite = true;
        }

        return true;
    }

    std::optional<Word> Response()
    {

        Word line = ToLineAddr(_requestedIp);
        if (!_check_cache) {
            for (int i = 0; i < _cacheInstr.size(); i++) {
                if (line == _cacheInstr[i].first.tag) {
                    for (int j = i + 1; j < _cacheInstr.size(); j++) 
                        _cacheInstr[j].first.lru++;
                    _cacheInstr[i].first.lru = 0;
                    return _cacheInstr[i].second[ToLineOffset(_requestedIp)];
                } else {
                    _cacheInstr[i].first.lru++;
                }
            }
            
            _check_cache = true;
        }

        if (_memWaitCycles > 0)
            return std::optional<Word>();
        
        Word rewriteLine = 0;
        for (int i = 0; i < _cacheInstr.size(); i++) {
            if (_cacheInstr[rewriteLine].first.lru < _cacheInstr[i].first.lru) {
                rewriteLine = i;
            }
        }

        Word offset = ToLineOffset(_requestedIp);
        Word lineAddr = ToLineAddr(_requestedIp);

        _mem.ReadLine(ToWordAddr(lineAddr), _cacheInstr[rewriteLine].second);
        _cacheInstr[rewriteLine].first.tag = lineAddr;
        _cacheInstr[rewriteLine].first.lru = 0;

        return _cacheInstr[rewriteLine].second[offset];
        
    }
    void Clock()
    {
        if (_cacheWaitCycles > 0) {
            --_cacheWaitCycles;
            return;
        }
        if (_memWaitCycles > 0) {
            --_memWaitCycles;
        }
    }

private:

    static constexpr size_t memLatency = 120; 
    static constexpr size_t cacheLatency = accessTime; 
    Word _requestedIp = 0;
    size_t _memWaitCycles = 0;
    size_t _cacheWaitCycles = 0;
    // std::vector<std::pair<LineInfo, Line>> Data;
    // std::vector<std::pair<LineInfo, Line>> instr;
    bool _check_cache = false;
    MemoryStorage& _mem;
    std::vector<std::pair<LineInfo, Line>> _cacheData;
    std::vector<std::pair<LineInfo, Line>> _cacheInstr;
};

#endif //RISCV_SIM_DATAMEMORY_H
