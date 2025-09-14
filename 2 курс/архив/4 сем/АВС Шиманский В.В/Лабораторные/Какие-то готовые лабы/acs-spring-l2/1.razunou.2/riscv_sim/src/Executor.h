
#ifndef RISCV_SIM_EXECUTOR_H
#define RISCV_SIM_EXECUTOR_H

#include "Instruction.h"

class Executor
{
public:
    void Execute(InstructionPtr& instr, Word ip)
    {
		alu(instr);
		jumps(instr, ip);
    }

private:
	void alu(InstructionPtr& instr)
	{
		Word op1, op2;
		if (instr->_src1 && instr->_src2)
		{
			op1 = instr->_src1Val;
			op2 = instr->_src2Val;
		}
		else if (instr->_src1 && instr->_imm)
		{
			op1 = instr->_src1Val;
			op2 = instr->_imm.value();
		}
		else
			return;

		switch (instr->_type)
		{
		case IType::Alu:
			switch (instr->_aluFunc)
			{
			case AluFunc::Add:
				instr->_data = op1 + op2;
				break;
			case AluFunc::Sll:
				instr->_data = op1 << (op2 % 32);
				break;
			case AluFunc::Slt:
				instr->_data = static_cast<Word>(static_cast<int>(op1) < static_cast<int>(op2));
				break;
			case AluFunc::Sltu:
				instr->_data = op1 < op2;
				break;
			case AluFunc::Xor:
				instr->_data = op1 ^ op2;
				break;
			case AluFunc::And:
				instr->_data = op1 & op2;
				break;
			case AluFunc::Or:
				instr->_data = op1 | op2;
				break;
			case AluFunc::Sub:
				instr->_data = op1 - op2;
				break;
			case AluFunc::Sra:
				instr->_data = static_cast<Word>(static_cast<int>(op1) >> static_cast<int>(op2 % 32));
				break;
			case AluFunc::Srl:
				instr->_data = op1 >> (op2 % 32);
				break;
			}
			break;
		case IType::Ld:
			instr->_addr = static_cast<Word>(static_cast<int>(op1) + static_cast<int>(op2));
			break;
		case IType::St:
			instr->_addr = op1 + instr->_imm.value();
			instr->_data = instr->_src2Val;
			break;
		case IType::J:
		case IType::Jr:
			instr->_data = instr->_nextIp + 4;
			break;
		case IType::Csrr:
			instr->_data = instr->_csrVal;
			/*if (instr->_dst.value_or(0) != 0)
			{
				instr->_csrVal = static_cast<Word>(instr->_csr.value());
				instr->_data = instr->_csrVal;
			}
			instr->_csr.value() = static_cast<CsrIdx>(instr->_src1Val & 0xfff);*/
			break;
		case IType::Csrw:
			instr->_data = instr->_src1Val;
			/*instr->_csrVal = static_cast<Word>(instr->_csr.value());
			instr->_data = instr->_csrVal;
			if (instr->_src1.value_or(0) != 0)
				instr->_csr.value() = static_cast<CsrIdx>(instr->_src1Val & 0xfff);*/
			break;
		case IType::Auipc:
			instr->_data = instr->_nextIp + instr->_imm.value();
			break;
		}
	}

	void jumps(InstructionPtr& instr, Word ip)
	{
		Word op1 = instr->_src1Val;
		Word op2 = instr->_src2Val;

		bool result;
		switch (instr->_brFunc) {
		case BrFunc::Eq:
			result = (op1 == op2);
			break;
		case BrFunc::Neq:
			result = (op1 != op2);
			break;
		case BrFunc::Lt:
			result = (static_cast<int>(op1) < static_cast<int>(op2));
			break;
		case BrFunc::Ltu:
			result = (op1 < op2);
			break;
		case BrFunc::Ge:
			result = (static_cast<int>(op1) >= static_cast<int>(op2));
			break;
		case BrFunc::Geu:
			result = (op1 >= op2);
			break;
		case BrFunc::AT:
			result = true;
			break;
		case BrFunc::NT:
			result = false;
			break;
		}

		if (result)
		{
			switch (instr->_type) {
			case IType::Jr:
				instr->_nextIp = ip + instr->_imm.value() + instr->_src1Val;
				break;
			case IType::J:
			case IType::Br:
				instr->_nextIp = ip + instr->_imm.value();
				break;
			}
		}
		else
			instr->_nextIp = ip + 4;
	}
    // Add helper functions here
};

#endif // RISCV_SIM_EXECUTOR_H
