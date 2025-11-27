#include <iostream>
#include "central.h"

class cpu cpu;
class memory mem;

void init()
{
	cpu.mem = &mem;
	cpu.regPC = 0;

	cpu.tick();
}

void cpu::setFlag(uint8_t flag, bool set)
{
	if (set) this->regF |= flag;
	else this->regF &= flag;
}

void cpu::inc8(uint8_t* reg)
{
	(*reg)++;
	setFlag(flagZ, *reg == 0);
	setFlag(flagN, false);
	setFlag(flagH, (*reg & 0x0f) == 0);

}

void cpu::dec8(uint8_t* reg)
{
	(*reg)--;
	setFlag(flagZ, *reg == 0);
	setFlag(flagN, true);
	setFlag(flagH, (*reg & 0x0f) == 0x0f);
}

uint8_t cpu::tick()
{
	uint8_t opcode = this->mem->read(regPC++);

	switch (opcode)
	{
		case 0x00: // NOP
		{
			return 4;
		}

		case 0x01: // LD BC, u16
		{
			uint8_t lo = this->mem->read(regPC++);
			uint8_t hi = this->mem->read(regPC++);

			this->setBC((hi << 8) | lo);
			return 12;
		}
		
		case 0x11: // LD DE, u16
		{
			uint8_t lo = this->mem->read(regPC++);
			uint8_t hi = this->mem->read(regPC++);

			this->setDE((hi << 8) | lo);
			return 12;
		}

		case 0x21: // LD HL, u16
		{
			uint8_t lo = this->mem->read(regPC++);
			uint8_t hi = this->mem->read(regPC++);

			this->setHL((hi << 8) | lo);
			return 12;
		}

		case 0x31: // LD SP, u16
		{
			uint8_t lo = this->mem->read(regPC++);
			uint8_t hi = this->mem->read(regPC++);

			this->regSP = ((hi << 8) | lo);
			return 12;
		}

		case 0x04: // INC B
		{
			inc8(&this->regB);
			return 4;
		}

		case 0x14: // INC D
		{
			inc8(&this->regD);
			return 4;
		}

		case 0x20: // INC H
		{
			inc8(&this->regH);
			return 4;
		}

		case 0x0c: // INC C
		{
			inc8(&this->regC);
			return 4;
		}

		case 0x1c: // INC E
		{
			inc8(&this->regE);
			return 4;
		}

		case 0x2c: // INC L
		{
			inc8(&this->regL);
			return 4;
		}

		case 0x3c: // INC A
		{
			inc8(&this->regA);
			return 4;
		}

		case 0x05: // DEC B
		{
			dec8(&this->regB);
			return 4;
		}

		case 0x15: // DEC D
		{
			dec8(&this->regD);
			return 4;
		}

		case 0x25: // DEC H
		{
			dec8(&this->regH);
			return 4;
		}

		case 0x0d: // DEC C
		{
			dec8(&this->regC);
			return 4;
		}
		
		case 0x1d: // DEC E
		{
			dec8(&this->regE);
			return 4;
		}

		case 0x2d: // DEC L
		{
			dec8(&this->regL);
			return 4;
		}

		case 0x3d: // DEC A
		{
			dec8(&this->regA);
			return 4;
		}

		case 0x03: // INC BC
		{
			this->setBC(this->getBC() + 1);
			return 8;
		}

		case 0x13: // INC DE
		{
			this->setDE(this->getDE() + 1);
			return 8;
		}

		case 0x23: // INC HL
		{
			this->setHL(this->getHL() + 1);
			return 8;
		}

		case 0x33: // INC SP
		{
			this->regSP++;
			return 8;
		}

		default:
		{
			std::cout << "invalid opcode\n";
			return 0;
		}
	}
}