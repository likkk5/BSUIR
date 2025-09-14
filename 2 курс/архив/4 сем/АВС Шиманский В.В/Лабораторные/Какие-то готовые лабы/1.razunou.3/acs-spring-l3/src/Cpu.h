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
		if (!_requestMem && !_responceMem)
		{ //если не происходит процесс обращения в память для чтения инструкции или передачи данных
			_mem.Request(_ip);
			_requestMem = true;
		}
		if (_requestMem && !_responceMem)
		{
			auto instr_data_op = _mem.Response();
			_requestMem = !instr_data_op.has_value();

			if (!_requestMem) // если новая инструкция получена
			{
				_instr = _decoder.Decode(instr_data_op.value());

				_rf.Read(_instr);
				_csrf.Read(_instr);

				_exe.Execute(_instr, _ip);
				_mem.Request(_instr);
				_responceMem = true;
			}
		}
		if (!_requestMem && _responceMem)
		{
			_responceMem = !_mem.Response(_instr);

			if (!_responceMem) //если данные переданы (прочтены или записаны)
			{
				_rf.Write(_instr);
				_csrf.Write(_instr);
				_ip = _instr->_nextIp;
				_csrf.InstructionExecuted();
			}
		}

		_csrf.Clock();
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
    // Add your code here, if needed
	bool _requestMem = false;
	bool _responceMem = false;
	InstructionPtr _instr = nullptr;
};


#endif //RISCV_SIM_CPU_H
