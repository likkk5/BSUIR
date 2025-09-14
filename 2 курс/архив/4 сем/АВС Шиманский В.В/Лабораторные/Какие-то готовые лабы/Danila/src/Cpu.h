
#ifndef RISCV_SIM_CPU_H
#define RISCV_SIM_CPU_H

#include "Memory.h"
#include "Decoder.h"
#include "RegisterFile.h"
#include "CsrFile.h"
#include "Executor.h"

class Cpu
{
public:
    Cpu(IMem& mem)
        : _mem(mem)
    {

    }

    void Clock()
    {
        _csrf.Clock();

        // if (!r_instr) {
        //     _mem.Request(_ip);
        //     r_instr = true;
        // }
        if (!instr.has_value()) {

            if (!r_instr) {
                _mem.Request(_ip);
                r_instr = true;
            }

            if (!_mem.Response().has_value()) {
                return;
            }
            Word pre_instr = _mem.Response().value();


            // if (!r_instr) {
            //     _mem.Request(_ip);
            //     r_instr = false;
            // }

            // if (!_mem.Response().has_value()) {
            //     return;
            // }
            // Word pre_instr = _mem.Response().value();
            instr = _decoder.Decode(pre_instr);     

            _rf.Read(instr.value());
            _csrf.Read(instr.value());

            _exe.Execute(instr.value(), _ip);

        }

        if (!r_data) {
            _mem.Request(instr.value());
            r_data = true;
        }

        if (!_mem.Response(instr.value())) {
            return;
        }

        _rf.Write(instr.value());
        _csrf.Write(instr.value());
        _ip = instr.value()->_nextIp;

        r_instr = false;
        r_data = false;
        instr.reset();
        _csrf.InstructionExecuted();  
    }

    void Reset(Word ip)
    {
        _csrf.Reset();
        _ip = ip;
    }

    std::optional<CpuToHostData> GetMessage()
    {
        return _csrf.GetMessage();
    }

private:
    Reg32 _ip;
    Decoder _decoder;
    RegisterFile _rf;
    CsrFile _csrf;
    Executor _exe;
    IMem& _mem;
    std::optional<InstructionPtr> instr;
    bool r_instr = false;
    bool r_data = false;
};


#endif //RISCV_SIM_CPU_H
