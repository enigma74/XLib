/*******************************************************************************
 * XILI9488.cpp
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
#include "XILI9488.h"

#if defined(__XHW__)

XILI9488::XILI9488(XLCDI& i)
	: XGLCD(XSize(480, 320), i)
{
	m_mode = XColorMode::NoColor;
}

void XILI9488::OnInit()
{
//	// Sleep IN
//	I.Command(0x10);
	// Sleep OUT
	I.Command(0x11);
	delay(120);
	// Power Control 1
	I.Command(0xC0);
	I.WriteByte(0x0D); // 0x18
	I.WriteByte(0x0D); // 0x16
	// Power Control 2
	I.Command(0xC1);
	I.WriteByte(0x41); // 0x41: -VCIx4, 0x43: -VCIx5
	// Power Control 3 (Normal mode)
	I.Command(0xC2);
	I.WriteByte(0x00);
	// VCOM Control
	I.Command(0xC5);
	I.WriteByte(0x00);
	I.WriteByte(0x1E); // 0x48: -0.875, 0x1E: -1.53125
	I.WriteByte(0x80); // VCOM value from VCM_REG
	// Display Function Control
	I.Command(0xB6);
	I.WriteByte(0x00);
	I.WriteByte(0x02); // H/V scan directions
	I.WriteByte(0x3B);
	// Frame Rate Control
	I.Command(0xB1);
	I.WriteByte(0xB0); // 0xB0: ~70Hz
	// Display Inversion Control
	I.Command(0xB4);
	I.WriteByte(0x02);
	// PGAMCTRL (Positive Gamma Control)
	I.Command(0xE0);
	I.WriteByte(0x00);
	I.WriteByte(0x04);
	I.WriteByte(0x0E);
	I.WriteByte(0x08);
	I.WriteByte(0x17);
	I.WriteByte(0x0A);
	I.WriteByte(0x40);
	I.WriteByte(0x79);
	I.WriteByte(0x4D);
	I.WriteByte(0x07);
	I.WriteByte(0x0E);
	I.WriteByte(0x0A);
	I.WriteByte(0x1A);
	I.WriteByte(0x1D);
	I.WriteByte(0x0F);
	// NGAMCTRL (Negative Gamma Control)
	I.Command(0xE1);
	I.WriteByte(0x00);
	I.WriteByte(0x1B);
	I.WriteByte(0x1F);
	I.WriteByte(0x02);
	I.WriteByte(0x10);
	I.WriteByte(0x05);
	I.WriteByte(0x32);
	I.WriteByte(0x34);
	I.WriteByte(0x43);
	I.WriteByte(0x02);
	I.WriteByte(0x0A);
	I.WriteByte(0x09);
	I.WriteByte(0x33);
	I.WriteByte(0x37);
	I.WriteByte(0x0F);
	// Set Image Function
	I.Command(0xE9);
	I.WriteByte(0x00); // 0x01: 24bit Data Bus
	// Interface Pixel Format
	I.Command(0x3A);
	uint8_t pf = 0;
	// supported RGB modes:
	// 0x5x: 16bits (65K colors)
	// 0x6x: 18bits (262K colors)
	// supported MCU modes:
	switch (I.Type)
	{
	case XLCDIType::Serial: // IM: 101 (3 lines), IM: 111 (4 lines)
		// 0xx1: 3bits (8 colors)
		// 0xx6: 18bits (262K colors)
		pf = 0x66;
		m_mode = XColorMode::RGB666;
		break;
	case XLCDIType::Parallel8: // IM: 011
	case XLCDIType::Parallel16: // IM: 010
		// 0xx5: 16bits (65K colors)
		// 0xx6: 18bits (262K colors)
		pf = 0x55;
		m_mode = XColorMode::RGB565;
		break;
	//case XLCDIType::Parallel9: // IM: 001
	//case XLCDIType::Parallel18: // IM: 000
	//	// 0xx6: 18bits (262K colors)
	//	pf = 0x66;
	//	m_mode = XColorMode::RGB666
	//	break;
	}
	I.WriteByte(pf);
	XGLCD::OnInit();
	delay(5);
}

void XILI9488::OnOn()
{
	// Normal Mode
	I.Command(0x13);
	// Display On
	I.Command(0x29);
}

void XILI9488::OnOff()
{
	// Display Off
	I.Command(0x28);
	// All Pixel On/Off (0x23: On, 0x22: Off)
	I.Command(0x22);
}

bool XILI9488::OnRotate()
{
	// Memory Access Control
	I.Command(0x36);
	uint8_t b = 0x08; // BGR
	uint8_t flags = XGLCD::RotateFlags(X_LCDSwap, m_rotation);
	if (X_GetFlag(flags, X_LCDHFlip))
		b |= 0x40; // Column Address Order
	if (X_GetFlag(flags, X_LCDVFlip))
		b |= 0x80; // Row Address Order
	if (X_GetFlag(flags, X_LCDSwap))
		b |= 0x20; // Swap X/Y
	I.WriteByte(b);
	return true;
}

void XILI9488::OnInvert()
{
	// Display Inversion On/Off (0x21: On, 0x20: Off)
	if (m_inverted)
		I.Command(0x21);
	else
		I.Command(0x20);
}

void XILI9488::SetRect(const XPoint& a, const XPoint& b)
{
	// Column Address Set
	I.Command(0x2a);
	I.WriteByte(XHiByte(a.x));
	I.WriteByte(XLoByte(a.x));
	I.WriteByte(XHiByte(b.x));
	I.WriteByte(XLoByte(b.x));
	// Page Address Set
	I.Command(0x2b);
	I.WriteByte(XHiByte(a.y));
	I.WriteByte(XLoByte(a.y));
	I.WriteByte(XHiByte(b.y));
	I.WriteByte(XLoByte(b.y));
}

void XILI9488::OnFill(const XRect& rect, const XColor& color)
{
	SetRect(rect.Location, rect.Ending());
	// Memory Write
	I.Command(0x2c);
	I.WriteColor(color.To(m_mode), rect.Area());
}

//XColor XILI9488::OnReadPixel(const XPoint& p, const XColor& color)
//{
//	SetRect(p, p);
//	// Memory Read
//	I.Command(0x2e);
//
//	return X_Transparent;
//}

#endif // __XHW__
