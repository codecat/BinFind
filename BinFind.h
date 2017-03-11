#pragma once

#include <cstdint>

#include <vector>
#include <tuple>

enum BinFindPatternByteOperation
{
	op_Equal,
	op_Unknown,

	op_LessThan,
	op_LessThanEqual,

	op_GreaterThan,
	op_GreaterThanEqual,
};

enum BinFindPatternByteRepeat
{
	rep_1,

	rep_0or1,
	rep_0orMore,
	rep_1orMore,
};

class BinFindPattern;

class BinFindPatternByte
{
public:
	BinFindPattern* Owner;
	uint32_t Info;

public:
	BinFindPatternByte(BinFindPattern* owner, const char* byte);

	bool MatchesByte(uint8_t input);
	// Returns: { NumBytes, Match }
	std::tuple<size_t, bool> Matches(uint8_t* input);

	inline BinFindPatternByteRepeat GetRepeat() { return (BinFindPatternByteRepeat)((Info & 0x00FF0000) >> 16); }
	inline BinFindPatternByteOperation GetOperation() { return (BinFindPatternByteOperation)((Info & 0x0000FF00) >> 8); }
	inline uint8_t GetValue() { return (uint8_t)(Info & 0x000000FF); }

private:
	BinFindPatternByte &NextInOwner();
};

class BinFindPattern
{
public:
	std::vector<BinFindPatternByte> Bytes;
	size_t CurrentOffset = 0;

	uint8_t* ResultHit = nullptr;
	size_t ResultSize = 0;

public:
	BinFindPattern(const char* pattern);

	void MatchBegin();
	// Returns: { NumBytes, Match }
	std::tuple<size_t, bool> MatchesNextByte(uint8_t* input);
	bool MatchComplete();
};

class BinFindSection
{
public:
	uint8_t* Pointer;
	size_t Size;
};

class BinFind
{
private:
	uint8_t* m_buffer;
	size_t m_size;

public:
	BinFind(uint8_t* buffer, size_t size);
	~BinFind();

	std::vector<BinFindSection> Find(const char* pattern);
};

extern void BinFind_DumpMemory(uint8_t* buffer, size_t size, std::vector<BinFindSection>* highlights = nullptr);
