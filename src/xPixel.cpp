#include "xPixel.h"
#include <stdio.h>

const int MODE_2_CYCLES = 80;
const int MODE_3_CYCLES = 172;
const int MODE_0_CYCLES = 204;
const int CYCLES_PER_LINE = 456;
const int SCREEN_HEIGHT = 144;
const int VBLANK_LINES = 10;

uint8_t ppu::decodeColor(uint16_t addr, uint8_t bit)
{
	uint8_t data1 = this->vram[addr - 0x8000]; // lo
	uint8_t data2 = this->vram[addr - 0x8000 + 1]; // hi

	uint8_t tBit = 7 - bit;

	uint8_t lo = (data1 >> tBit) & 0x01;
	uint8_t hi = (data2 >> tBit) & 0x01;

	return (hi << 1) | lo;
}

void ppu::tick(int cycles)
{
    if (!(*regLCDC & 0x80)) return;

    this->cycleCounter += cycles;

    switch (this->mode)
    {
    case 0:
    {
        if (this->cycleCounter >= MODE_0_CYCLES)
        {
            this->cycleCounter -= MODE_0_CYCLES;
            (*this->regLY)++;

            if (*this->regLY == SCREEN_HEIGHT)
            {
                this->mode = 1;
                *this->regIF |= 0x01; // interrupt

                printf("V-Blank! Frame Done.\n");
            }
            else
            {
                this->mode = 2;
            }
        }
        break;
    }

    case 1: // V-Blank
    {
        if (this->cycleCounter >= CYCLES_PER_LINE)
        {
            this->cycleCounter -= CYCLES_PER_LINE;
            (*this->regLY)++;

            if (*this->regLY > 153)
            {
                this->mode = 2;
                *this->regLY = 0;
            }
        }
        break;
    }

    case 2: // OAM Scan
    {
        if (this->cycleCounter >= MODE_2_CYCLES)
        {
            this->cycleCounter -= MODE_2_CYCLES;
            this->mode = 3;
        }
        break;
    }

    case 3: // Draw
    {
        if (this->cycleCounter >= MODE_3_CYCLES)
        {
            this->cycleCounter -= MODE_3_CYCLES;
            this->mode = 0;

            uint16_t mapBase = (*this->regLCDC & 0x08) ? 0x9C00 : 0x9800;
            bool unsignedMode = (*this->regLCDC & 0x10);
            uint16_t tileData = unsignedMode ? 0x8000 : 0x8800;
            uint8_t yPos = *this->regLY + *this->regSCY;
            uint16_t tileRowIndex = (yPos / 8) * 32;
            uint8_t tileLine = yPos % 8;

            for (int x = 0; x < 160; x++)
            {
                uint8_t xPos = x + *this->regSCX;
                uint16_t tileColIndex = xPos / 8;
                uint16_t tileAddress = mapBase + tileRowIndex + tileColIndex;
                uint8_t tileNum = this->vram[tileAddress - 0x8000];
                uint16_t tileLocation;

                if (unsignedMode)
                {
                    tileLocation = tileData + (tileNum * 16);
                }
                else
                {
                    tileLocation = 0x9000 + ((int8_t)tileNum * 16);
                }

                uint16_t lineLocation = tileLocation + (tileLine * 2);
                uint8_t colorNum = decodeColor(lineLocation, xPos % 8);
            }
        }
        break;
    }
    }

    *this->regSTAT = (*this->regSTAT & 0xFC) | (this->mode & 0x03);
}