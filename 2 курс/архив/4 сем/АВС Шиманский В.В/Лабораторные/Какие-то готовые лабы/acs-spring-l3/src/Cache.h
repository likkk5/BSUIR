#ifndef RISCV_SIM_CACHE_H
#define RISCV_SIM_CACHE_H

#include "MemoryStorage.h"
#include <list>
#include <optional>

struct LineInfo
{
	LineInfo(Word tag, bool rewrite)
		: tag(tag), rewrite(rewrite) {}
	Word tag;
	bool rewrite = false;
};

class CacheData
{
public:
	explicit CacheData(Word maxCacheLines, MemoryStorage& amem)
		: maxCacheLines(maxCacheLines), _mem(amem) {}
	void pushLine(Word _requestedIp)
	{
		if (_cache.size() == maxCacheLines)
			popLine();

		calculateOffsetAddr(_requestedIp);

		_cache.push_back(std::pair<LineInfo, Line>
			(LineInfo(_lineAddr, false), _mem.ReadLine(ToWordAddr(_lineAddr))));
	}

	void popLine()
	{
		if (_cache.front().first.rewrite)
			_mem.WriteLine(
				ToWordAddr(_cache.front().first.tag),
				_cache.front().second
			);
		_cache.pop_front();
	}

protected:
	std::optional<Line> getCacheLine(Word _requestedIp)
	{
		calculateOffsetAddr(_requestedIp);

		std::optional<Line> result;
		if (_check_cache)
			return result;

		auto cacheI = _cache.cbegin();
		for (; cacheI != _cache.cend(); cacheI++)
			if (_lineAddr == cacheI->first.tag)
			{
				result = cacheI->second;
				break;
			}

		if (result)
		{
			auto lru = *cacheI;
			_cache.erase(cacheI);
			_cache.push_back(lru);
			_check_cache = true;
		}

		return result;
	}

	bool setCacheLineData(Word _requestedIp, Word data)
	{
		calculateOffsetAddr(_requestedIp);

		if (_check_cache)
			return true;

		auto cacheI = _cache.begin();
		for (; cacheI != _cache.cend(); cacheI++)
			if (_lineAddr == cacheI->first.tag)
				break;

		if (cacheI != _cache.cend())
		{
			cacheI->second[_offset] = data;
			cacheI->first.rewrite = true;
			return true;
		}
		return false;
	}

private:
	inline void calculateOffsetAddr(Word _requestedIp)
	{
		_offset = ToLineOffset(_requestedIp);
		_lineAddr = ToLineAddr(_requestedIp);
	}
	Word maxCacheLines;
protected:
	bool _check_cache = false;
	std::list<std::pair<LineInfo, Line>> _cache;
	MemoryStorage& _mem;

	Word _offset;
	Word _lineAddr;
};

class Cache : public CacheData
{
public:
	explicit Cache(Word maxCacheLines, MemoryStorage& amem)
		: CacheData(maxCacheLines, amem) {}
	inline bool isChecked()
	{
		return _check_cache;
	}
	inline void reset()
	{
		_check_cache = false;
		_cacheWaitCycles = cacheLatency;
	}

	std::optional<Word> getCacheData(Word _requestedIp)
	{
		if (_cacheWaitCycles != 0)
			return std::optional<Word>();

		auto line = CacheData::getCacheLine(_requestedIp);
		if (line)
			return line.value()[_offset];
		else
			return std::optional<Word>();
	}

	bool setCacheData(Word _requestedIp, Word data)
	{
		if (_cacheWaitCycles != 0)
			return false;

		auto line = CacheData::getCacheLine(_requestedIp);
		if (line)
		{
			return setCacheLineData(_requestedIp, data);
		}
		else
			return false;
	}

	inline void Clock()
	{
		if (_cacheWaitCycles > 0)
			_cacheWaitCycles--;
	}
private:
	static constexpr size_t cacheLatency = 3;
	size_t _cacheWaitCycles = 0;
};

#endif //RISCV_SIM_CACHE_H