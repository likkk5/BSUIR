
#ifndef RISCV_SIM_EXECUTOR_H
#define RISCV_SIM_EXECUTOR_H

#include "Instruction.h"
#include <iostream>

using SWord = int32_t;

class Executor
{
public:
    void Execute(InstructionPtr& instr, Word ip)
    {
        // Add your code here.
        Word result = alu(instr);
        logicAlu(instr, ip, result);
        bool branchDecission = branch(instr);
        logicBranch(instr, ip, branchDecission);
    }

private:
    // Add helper functions here
    Word alu(InstructionPtr& instr) 
    {
        if (!instr->_src1 || (!instr->_src2 && !instr->_imm)) {
            return 0xdeadbeef;
        }

        Word left = instr->_src1Val;
        Word right, shift;
        if (instr->_imm) {
            right = instr->_imm.value();
        } else {
            right = instr->_src2Val;
        }

        switch(instr->_aluFunc)
        {
        case AluFunc::Add:
            return left + right;
        case AluFunc::Sub:
            return left - right;
        case AluFunc::And:
            return left & right;
        case AluFunc::Or:
            return left | right;
        case AluFunc::Xor:
            return left ^ right;
        case AluFunc::Slt:
            return SWord(left) < SWord(right);
        case AluFunc::Sltu:
            return left < right;
        case AluFunc::Sll:
            shift = right % 32u;
            return left << shift;
        case AluFunc::Srl:
            shift = right % 32u;
            return left >> shift;
        case AluFunc::Sra:
            shift = right % 32u;
            return Word(SWord(left) >> shift);
        }

        return 0xdeadbeef;
    }

    void logicAlu(InstructionPtr& instr, Word ip, Word result) 
    {
        switch(instr->_type) 
        {
        case IType::Csrr:
            instr->_data = instr->_csrVal;
            break;
        case IType::Csrw:
            instr->_data = instr->_src1Val;
            break;
        case IType::St:
            instr->_data = instr->_src2Val;
            instr->_addr = result;
            break;
        case IType::J:
        case IType::Jr:
            instr->_data = ip + 4u;
            break;
        case IType::Auipc:
            instr->_data = ip + instr->_imm.value();
            break;
        case IType::Ld:
            instr->_addr = result;
        default:
            instr->_data = result;
        }
    }

    bool branch(InstructionPtr& instr) 
    {
        if (instr->_brFunc == BrFunc::AT) {
            return true;
        } else if (instr->_brFunc == BrFunc::NT) {
            return false;
        }

        if (!instr->_src1 && !instr->_src2) {
            return true;
        }
        Word left = instr->_src1Val;
        Word right = instr->_src2Val;

        switch (instr->_brFunc)
        {
        case BrFunc::Eq:
            return left == right;
        case BrFunc::Neq:
            return left != right;
        case BrFunc::Lt:
            return SWord(left) < SWord(right);
        case BrFunc::Ltu:
            return left < right;
        case BrFunc::Ge:
            return SWord(left) >= SWord(right);
        case BrFunc::Geu:
            return left >= right;
        }
        return true;
    }
    
    void logicBranch(InstructionPtr& instr, Word ip, bool comp)  
    {
        if (!comp) {
            instr->_nextIp = ip + 4u;
            return;
        }
        switch (instr->_type)
        {
        case IType::Br:
        case IType::J:
            instr->_nextIp = ip + instr->_imm.value();
            break;
        case IType::Jr:
            instr->_nextIp = instr->_src1Val + instr->_imm.value();
            break;
        default:
            break;
        }

    }
};

#endif // RISCV_SIM_EXECUTOR_H
