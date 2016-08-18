/*******************************************************************************
 * XLCDBus8.cpp
 *
 * Copyright (c) Moreno Seri (moreno.seri@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *******************************************************************************/

#include "XDevice.h"
#include "XLCDBus8.h"

#if defined(__XHW__)

XLCDBus8::XLCDBus8(uint32_t freq)
	: XLCDBus(XLCDIType::Parallel8, freq)
{
}

void XLCDBus8::OnInit()
{
	XLCDBus::OnInit();
	// set direction registers
#if defined(__AVR_ATmega328P__)
	DDRD = 0xFF;
#elif defined(__AVR_ATmega32U4__)
	DDRC |= 0x40;
	DDRD |= 0x9F;
	DDRE |= 0x40;
#elif defined(__AVR_ATmega1284P__)
	DDRB |= 0x0F;
	DDRD |= 0x0F;
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	DDRA = 0xFF;
#elif defined(__SAM3X8E__)
	REG_PIOA_OER = 0x0000C000; //PA14, PA15 enable
	REG_PIOB_OER = 0x04000000; //PB26 enable
	REG_PIOD_OER = 0x0000064F; //PD0-3, PD6, PD9-10 enable
#elif defined(__32MX320F128H__) || defined(__32MX340F512H__) || defined(__32MX795F512L__)
	TRISE = 0;
#elif defined(__MK20DX128__) || defined(__MK20DX256__)
	GPIOD_PDDR |= 0xFF;
	PORTD_PCR0 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	PORTD_PCR1 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	PORTD_PCR2 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	PORTD_PCR3 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	PORTD_PCR4 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	PORTD_PCR5 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	PORTD_PCR6 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	PORTD_PCR7 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
#elif defined(__CC3200R1M1RGC__)
	HWREG(GPIOA0_BASE + 0x0400) = 0xFF;
	for (int i = 0xA0; i <= 0xBC; i += 4)
		HWREG(0x4402E000 + i) = ((HWREG(0x4402E000 + i) & 0xFFFFFFF0) & ~(3 << 10));
#endif
}

void XLCDBus8::OnWriteBus(uint8_t data)
{
#if defined(__AVR_ATmega328P__)
	PORTD = data;
#elif defined(__AVR_ATmega32U4__)
	X_ClearFlag(PORTC, 0x40);
	X_ClearFlag(PORTD, 0x9F);
	X_ClearFlag(PORTE, 0x40);
	PORTC |= ((data & 0x20) << 1);
	PORTD |= ((data & 0x40) << 1) | (data & 0x10) | ((data & 0x08) >> 3)
		| ((data & 0x04) >> 1) | ((data & 0x03) << 2);
	PORTE |= ((data & 0x80) >> 1);
#elif defined(__AVR_ATmega1284P__)
	X_ClearFlag(PORTD, 0x0F);
	X_SetFlag(PORTD, (data & 0x0F));
	X_ClearFlag(PORTB, 0x0F);
	X_SetFlag(PORTB, (data & 0xF0) >> 4);
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	PORTA = data;
#elif defined(__SAM3X8E__)
	REG_PIOA_CODR = 0x0000C000;
	REG_PIOD_CODR = 0x0000064F;
	REG_PIOA_SODR = (data & 0x06) << 13;
		(data & 0x01) ? REG_PIOB_SODR = 0x4000000 : REG_PIOB_CODR = 0x4000000;
	REG_PIOD_SODR = ((data & 0x78) >> 3) | ((data & 0x80) >> 1);
#elif defined(__32MX320F128H__) || defined(__32MX340F512H__) || defined(__32MX795F512L__)
	LATECLR = 0xFF;
	LATESET = data;
#elif defined(__MK20DX128__) || defined(__MK20DX256__)
	*(volatile uint8_t *) (&GPIOD_PDOR) = data;
#elif defined(__CC3200R1M1RGC__)
	HWREG(GPIOA0_BASE + 0x03FC) = data;
#endif
}

void XLCDBus8::OnWriteColor(XColor color, uint32_t count)
{
	switch (color.Mode())
	{
		case XColorMode::RGB565:
		{
			// 2 bytes per 1px (MSB and LSB)
			uint16_t rgb = color.Encode();
			uint8_t ch = XHiByte(rgb);
			uint8_t cl = XLoByte(rgb);
			if (ch == cl)
			{
				WriteBus(ch, count << 1);
				return;
			}
			do
			{
				WriteBus(ch);
				WriteBus(cl);
			} while (--count);
			break;
		}
		case XColorMode::RGB666:
		{
			// 3 bytes per 1px (MSB 6bits component per byte)
			color.r <<= 2;
			color.g <<= 2;
			color.b <<= 2;
			if ((color.r == color.g) && (color.g == color.b))
			{
				WriteBus(color.r, count * 3);
				return;
			}
			do
			{
				WriteBus(color.r);
				WriteBus(color.g);
				WriteBus(color.b);
			} while (--count);
			break;
		}
		default:
			break;
	}
}

#endif // __XHW__
