/*******************************************************************************
 * XLCDBus16.cpp
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
#include "XLCDBus16.h"

#if defined(__XHW__)

XLCDBus16::XLCDBus16(uint32_t freq)
	: XLCDBus(XLCDIType::Parallel16, freq)
{
}

void XLCDBus16::OnInit()
{
	XLCDBus::OnInit();
	// set direction registers
#if defined(__AVR_ATmega328P__)
	DDRB |= 0x3F;
	DDRC |= 0x03;
	DDRD = 0xFF;
#elif defined(__AVR_ATmega32U4__)
	DDRB |= 0xF0;
	DDRC |= 0xC0;
	DDRD |= 0xDF;
	DDRE |= 0x40;
	DDRF |= 0xC0;
#elif defined(__AVR_ATmega1284P__)
	DDRA |= 0xC0;
	DDRB = 0xFF;
	DDRD |= 0x6F;
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	DDRA = 0xFF;
	DDRC = 0xFF;
#elif defined(__SAM3X8E__)
	REG_PIOA_OER = 0x0000C080; // PA7, PA14, PA15 enable
	REG_PIOB_OER = 0x04000000;// PB26 enable
	REG_PIOC_OER = 0x0000003E;// PC1-PC5 enable
	REG_PIOD_OER = 0x0000064F;// PD0-3, PD6, PD9-10 enable
#elif defined(__32MX320F128H__) || defined(__32MX340F512H__) || defined(__32MX795F512L__)
	TRISD = 0;
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
	GPIOB_PDDR |= 0x000F000F;
	PORTB_PCR0 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	PORTB_PCR1 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	PORTB_PCR2 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	PORTB_PCR3 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	PORTB_PCR16 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	PORTB_PCR17 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	PORTB_PCR18 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
	PORTB_PCR19 = PORT_PCR_SRE | PORT_PCR_DSE | PORT_PCR_MUX(1);
#elif defined(__CC3200R1M1RGC__)
	HWREG(GPIOA0_BASE + 0x0400) = 0xFF;
	for (int i = 0xA0; i <= 0xBC; i += 4)
		HWREG(0x4402E000 + i) = ((HWREG(0x4402E000 + i) & 0xFFFFFFF0) & ~(3 << 10));
	HWREG(GPIOA1_BASE + 0x0400) = 0xFF;
	for (int i = 0xC0; i <= 0xDC; i += 4)
		HWREG(0x4402E000 + i) = ((HWREG(0x4402E000 + i) & 0xFFFFFFF0) & ~(3 << 10));
#endif
}

void XLCDBus16::OnWriteBus(uint16_t data)
{
#if defined(__AVR_ATmega328P__)
	PORTD = XHiByte(data);
	X_ClearFlag(PORTC, 0x03);
	uint8_t dl = XLoByte(data);
	X_SetFlag(PORTC, (dl >> 6) & 0x03);
	X_ClearFlag(PORTB, 0x3F);
	X_SetFlag(PORTB, dl & 0x3F);
#elif defined(__AVR_ATmega32U4__)
	X_ClearFlag(PORTB, 0xF0);
	X_ClearFlag(PORTC, 0xC0);
	X_ClearFlag(PORTD, 0xDF);
	X_ClearFlag(PORTE, 0x40);
	X_ClearFlag(PORTF, 0xC0);
	uint8_t dh = XHiByte(data);
	uint8_t dl = XLoByte(data);
	PORTB |= ((dl & 0x0F) << 4);
	PORTC |= ((dl & 0x20) << 2) | ((dh & 0x20) << 1);
	PORTD |= ((dh & 0x40) << 1) | (dh & 0x10) | ((dh & 0x08) >> 3)
		| ((dh & 0x04) >> 1) | ((dh & 0x03) << 2) | ((dl & 0x10) << 2);
	PORTE |= ((dh & 0x80) >> 1);
	PORTF |= ((dl & 0x80) >> 1) + ((dl & 0x40) << 1);
#elif defined(__AVR_ATmega1284P__)
	uint8_t dh = XHiByte(data);
	uint8_t dl = XLoByte(data);
	X_ClearFlag(PORTD, 0x6F);
	X_SetFlag(PORTD, (dh & 0x0F) | ((dl & 0x03) << 5));
	PORTB = ((dh & 0xF0) >> 4) | ((dl & 0x3C) << 2);
	X_ClearFlag(PORTA, 0xC0);
	X_SetFlag(PORTA, ((dl & 0x40) << 1) | ((dl & 0x80) >> 1));
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	PORTA = XHiByte(data);
	PORTC = XLoByte(data);
#elif defined(__SAM3X8E__)
	REG_PIOA_CODR = 0x0000C080;
	REG_PIOA_SODR = ((data & 0x00000600) << 5) | ((data & 0x00000040) << 1);
	REG_PIOB_CODR = 0x04000000;
	REG_PIOB_SODR = (data & 0x00000100) << 18;
	REG_PIOC_CODR = 0x0000003E;
	REG_PIOC_SODR = ((data & 0x00000001) << 5) | ((data & 0x00000002) << 3)
		| ((data & 0x00000004) << 1) | ((data & 0x00000008) >> 1) | ((data & 0x00000010) >> 3);
	REG_PIOD_CODR = 0x0000064F;
	REG_PIOD_SODR = ((data & 0x00007800) >> 11) | ((data & 0x00008000) >> 9)
		| ((data & 0x00000020) << 5) | ((data & 0x00000080) << 2);
#elif defined(__32MX320F128H__) || defined(__32MX340F512H__) || defined(__32MX795F512L__)
	LATDCLR = 0xFF;
	LATDSET = XLoByte(data);
	LATECLR = 0xFF;
	LATESET = XHiByte(data);
#elif defined(__MK20DX128__) || defined(__MK20DX256__)
	*(volatile uint8_t *) (&GPIOD_PDOR) = XHiByte(data);
	GPIOB_PCOR = 0x000F000F; // clear data lines B0-3, B16-19
	GPIOB_PSOR = (data & 0x0F) | ((data & 0xF0) << 12);// set data lines 0-3, 16-19 if set in cl
#elif defined(__CC3200R1M1RGC__)
	HWREG(GPIOA0_BASE + 0x03FC) = XHiByte(data);
	HWREG(GPIOA1_BASE + 0x03FC) = XLoByte(data);
#endif
}

void XLCDBus16::OnWriteColor(XColor color, uint32_t count)
{
	switch (color.Mode())
	{
		case XColorMode::RGB565:
			// 1 word per 1px
			WriteBus(color.Encode(), count);
			break;
		case XColorMode::RGB666:
			// 3 words per 2px (MSB 6bits component per MSB/LSB byte combined on middle word)
			// ToDo: ...
			break;
		default:
			break;
	}
}

#endif // __XHW__
