#pragma once
#include <cstdint>

class ppu
{
public:
	uint8_t* vram;
	uint8_t* oam;
	uint8_t* regLY; // current scanline
	uint8_t* regSTAT; // current mode
	uint8_t* regLCDC; // control
	uint8_t* regIF; // interrupt request
	uint8_t* regSCX; // 0xff43
	uint8_t* regSCY; // 0xff42

	void tick(int cycles);
	uint8_t decodeColor(uint16_t addr, uint8_t bit);

private:
	int cycleCounter = 0;
	int mode = 2;
};