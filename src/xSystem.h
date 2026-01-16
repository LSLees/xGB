#pragma once
#include <cstdint>
#include "xCentral.h"
#include "xMem.h"
#include "xPixel.h"

class xgb
{
public:
	xgb();
	~xgb();

	cpu cpu;
	memory mem;
	ppu ppu;

	bool load(const char* filename);
	void tick();

	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr);

	int div = 0;
	int tima = 0;

	void updateTimer(int cycles);
};