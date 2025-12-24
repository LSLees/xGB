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

	bool load(const char* filename);
	void tick();

	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr);
};