#include "xMem.h"
#include <fstream>
#include <iostream>
#include <vector>

bool memory::load(const char* filename)
{
	std::ifstream file(filename, std::ios::binary | std::ios::ate);

	if (!file.is_open())
	{
		std::cerr << "cannot open rom\n";
		return false;
	}

	std::streampos size = file.tellg();
	file.seekg(0, std::ios::beg);
	std::vector<char> buffer(size);

	if (file.read(buffer.data(), size))
	{
		long bytes = size;
		if (bytes > 0x8000)
		{
			bytes = 0x8000;
			std::cout << "rom exceeds 32kb\n";
		}

		for (long i = 0; i < bytes; i++)
		{
			this->write(i, (uint8_t)buffer[i]);
		}
	}
	else
	{
		std::cerr << "unable to read rom\n";
		return false;
	}

	return true;
}

uint8_t memory::read(uint16_t address)
{
	return this->ram[address];
}

void memory::write(uint16_t address, uint8_t data)
{
	ram[address] = data;
}