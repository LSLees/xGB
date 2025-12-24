#pragma once
#include <cstdint>

class memory
{
public:

	uint8_t ram[65536] = { 0 };

	bool load(const char* filename);
	uint8_t read(uint16_t address);
	void write(uint16_t address, uint8_t data);
};