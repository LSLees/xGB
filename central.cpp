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
			bool H = (regB & 0x0f) == 0x0f;

			this->regB++;

			this->regF &= FLAG_C;

			if (regB == 0)
			{
				this->regF |= FLAG_Z;
			}
			
			this->regF &= ~FLAG_N;

			if (H)
			{
				this->regF |= FLAG_H;
			}

			return 4;
		}

		case 0x14: // INC D
		{
			this->regF = (this->regF & ~FLAG_Z) | ((this->regD == 0xff) ? FLAG_Z : 0);
			this->regD++;

			return 4;
		}

		default:
		{
			std::cout << "invalid opcode\n";
			return 0;
		}
	}
}