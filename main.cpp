#include <cstdio>
#include <cstdint>

#include "BinFind.h"

static uint8_t buffer[] = {
	0x00, 0x00, 0x00, 0x00,
	0x05, 0x05, 0x04, 0x04,
	0xAA, 0xFF, 0xBB, 0xC4,
	0x04, 0x08, 0x0C, 0xA0,

	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,

	0x00, 0xFF, 0xFF, 0x00,
	0x3C
};

static void TestSearch(const char* pattern)
{
	printf("\nPattern: \"%s\"\n", pattern);

	BinFind find(buffer, sizeof(buffer));
	auto ret = find.Find(pattern);

	/*
	for (auto result : ret) {
		printf("* %p -> %p\n", result.Pointer, result.Pointer + result.Size);
	}
	*/

	BinFind_DumpMemory(buffer, sizeof(buffer), &ret);
}

int main()
{
	printf(" Starting ptr: %p\n", buffer);
	printf("   Ending ptr: %p\n", buffer + sizeof(buffer));

	TestSearch("05 05 04 04");
	TestSearch("05+ 04+");
	TestSearch(">=04");
	TestSearch(">=04+");
	TestSearch("0C A0 00+");
	TestSearch("05 05 FF? 04 04");

	getchar();

	return 0;
}
