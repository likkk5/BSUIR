#include "pch.h"
#include "CppUnitTest.h"
#include "../riscv_sim/src/BaseTypes.h"
#include "../riscv_sim/src/Cpu.h"
#include "../riscv_sim/src/CsrFile.h"
#include "../riscv_sim/src/Decoder.h"
#include "../riscv_sim/src/Executor.h"
#include "../riscv_sim/src/Instruction.h"
#include "../riscv_sim/src/Memory.h"
#include "../riscv_sim/src/RegisterFile.h"

constexpr unsigned maxInstructionInFlight = 8;

template <>
PoolAllocator<Instruction> PoolAllocated<Instruction>::allocator{ maxInstructionInFlight };

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestSubMR
{
	TEST_CLASS(UnitTestSubMR)
	{
	public:
		///<summary>
		///Тест декодировки инструкции Sub
		///</summary>
		TEST_METHOD(TestDecodeSub)
		{
			//x2 = x1 - x3
			Word subWrd = createAddSub(false, 2, 1, 3);
			Decoder decoder;
			InstructionPtr instrDecoded = decoder.Decode(subWrd);
			Assert::AreEqual(static_cast<int>(instrDecoded->_type),
				static_cast<int>(IType::Alu));
			Assert::AreEqual(static_cast<int>(instrDecoded->_aluFunc),
				static_cast<int>(AluFunc::Sub));
		}
		///<summary>
		///Тест проверки расчета инструкции Sub
		///</summary>
		TEST_METHOD(TestSubCpu)
		{
			//Загрузка двух чисел, вычитание и запись результата
			Memory mem;
			mem.setWord(0x0, createLui(1, 4321));
			mem.setWord(0x4, createLui(3, 1234));
			mem.setWord(0x8, createAddSub(false, 2, 1, 3));
			mem.setWord(0xC, createSw(5, 2, 0x18));
			Cpu cpu{ mem };
			cpu.Reset(0x0);
			for (int i = 0; i < 4; i++)
			{
				cpu.ProcessInstruction();
			}
			Word calculate = (4321u - 1234u) << 12u;
			Word result = mem.Request(0x18);
			Assert::AreEqual(result, calculate);
		}
	private:
		enum InstrType
		{
			Add,
			Sub,
			Lui
		};
		Word createLui(uint16_t rd, uint32_t imm)
		{
			Word result = 0b0110111;
			result += rd << 7;
			result += imm << 12;
			return result;
		}
		Word createSw(uint16_t rs1, uint16_t rs2, uint32_t imm)
		{
			Word result = 0b0100011;
			result += (imm & 0b11111) << 7;
			result += 0b010 << 12;
			result += rs1 << 15;
			result += rs2 << 20;
			result += (imm & 0b111111100000) << 25;
			return result;
		}
		Word createAddSub(bool isAdd, uint16_t rd, uint16_t rs1, uint16_t rs2)
		{
			Word result = 0b0110011;
			result += rd << 7;
			result += rs1 << 15;
			result += rs2 << 20;
			if (!isAdd)
				result += 0b1 << 30;
			return result;
		}
	};
}
