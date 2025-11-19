#include <cstdint>


class cpu
{
	uint8_t regA;
	uint8_t regF;
	uint8_t regB;
	uint8_t regC;
	uint8_t regD;
	uint8_t regE;
	uint8_t regH;
	uint8_t regL;
	uint16_t regPC;
	uint16_t regSP;

	uint16_t getAF()
	{
		return (regA << 8) | regF;
	}

	uint16_t getBC()
	{
		return (regB << 8) | regC;
	}

	uint16_t getDE()
	{
		return (regD << 8) | regE;
	}

	uint16_t getHL()
	{
		return (regH << 8) | regL;
	}

	void setAF(uint16_t af)
	{
		regA = af >> 8;
		regF = af & 0xf0;
	}

	void setBC(uint16_t bc)
	{
		regB = bc >> 8;
		regC = bc & 0xff;
	}

	void setDE(uint16_t de)
	{
		regD = de >> 8;
		regE = de & 0xff;
	}

	void setHL(uint16_t hl)
	{
		regH = hl >> 8;
		regL = hl & 0xff;
	}
};