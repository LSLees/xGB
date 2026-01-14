#include "xSystem.h"

xgb::xgb()
{
	cpu.attachSys(this);
}

xgb::~xgb()
{

}

bool xgb::load(const char* filename)
{
	return mem.load(filename);
}

void xgb::write(uint16_t addr, uint8_t data)
{
	// memory mapping shit
	mem.write(addr, data);
}

uint8_t xgb::read(uint16_t addr)
{
	// route to ppu apu etc
	return mem.read(addr);
}

void xgb::updateTimer(int cycles)
{
	this->div += cycles;
	if (this->div >= 256)
	{
		this->div = 0;
		uint8_t current = this->read(0xff04);
		this->write(0xff04, current + 1);
	}

	uint8_t tac = this->read(0xff87);

	if (tac & 0x04)
	{
		this->tima += cycles;
		int threshold = 1024;
		switch (tac & 0x03)
		{
		case 0: threshold = 1024; break;
		case 1: threshold = 16; break;
		case 2: threshold = 64; break;
		case 3: threshold = 256; break;
		}

		while (this->tima >= threshold)
		{
			this->tima -= threshold;
			uint8_t timaT = this->read(0xff05);
			if (timaT == 0xff)
			{
				uint8_t tmaT = this->read(0xff06);
				this->write(0xff05, tmaT);

				uint8_t flags = this->read(0xff0f);
				this->write(0xff0f, flags | 0x04);
			}
			else
			{
				this->write(0xff05, timaT + 1);
			}
		}
	}
}

void xgb::tick()
{
	int cycles = this->cpu.tick();
	this->updateTimer(cycles);
}