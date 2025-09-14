#ifndef RISCV_SIM_DATAMEMORY_H
#define RISCV_SIM_DATAMEMORY_H

#include "Instruction.h"
#include "MemoryStorage.h"
#include "Cache.h"

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

    virtual void Request(Word ip)
    {
        _requestedIp = ip;
        _memWaitCycles = memLatency;
    }

    virtual std::optional<Word> Response()
    {
        if (_memWaitCycles > 0)
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

        if (_memWaitCycles != 0)
            return false;

        if (instr->_type == IType::Ld)
            instr->_data = _mem.Read(instr->_addr);
        else if (instr->_type == IType::St)
            _mem.Write(instr->_addr, instr->_data);

        return true;
    }

	virtual void Clock()
    {
        if (_memWaitCycles > 0)
            _memWaitCycles--;
    }
protected:
    static constexpr size_t memLatency = accessTime;
    Word _requestedIp = 0;
    size_t _memWaitCycles = 0;
    MemoryStorage& _mem;
};


class CachedMem : public UncachedMem
{
public:
	explicit CachedMem(MemoryStorage& amem)
		: UncachedMem(amem),
		_cacheCode(Cache(codeCacheSize / lineSizeBytes, amem)),
		_cacheData(Cache(dataCacheSize / lineSizeBytes, amem))
	{
	}

	void Request(Word ip)
	{
		UncachedMem::Request(ip);
		_cacheCode.reset();
		_cacheData.reset();
	}

	std::optional<Word> Response()
	{
		auto cacheData = _cacheCode.getCacheData(_requestedIp);
		if (cacheData)
			return cacheData;

		if (_memWaitCycles > 0)
			return std::optional<Word>();

		_cacheCode.pushLine(_requestedIp);

		return _cacheCode.getCacheData(_requestedIp);
	}

	bool Response(InstructionPtr &instr) {
		if (instr->_type != IType::Ld && instr->_type != IType::St)
			return true;

		if (!_cacheData.getCacheData(_requestedIp) && !_cacheData.isChecked())
			return false;

		if (!_cacheData.getCacheData(_requestedIp) && _memWaitCycles > 0)
			return false;
		else if (!_cacheData.getCacheData(_requestedIp) && _memWaitCycles == 0)
			_cacheData.pushLine(_requestedIp);

		if (instr->_type == IType::Ld) {
			instr->_data = _cacheData.getCacheData(_requestedIp).value();
		}
		else if (instr->_type == IType::St) {
			_cacheData.setCacheData(_requestedIp, instr->_data);
		}
		return true;
	}

	void Clock()
	{
		UncachedMem::Clock();
		_cacheCode.Clock();
		_cacheData.Clock();
	}

private:
	Cache _cacheCode;
	Cache _cacheData;
};

#endif //RISCV_SIM_DATAMEMORY_H
