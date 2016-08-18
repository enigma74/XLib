/*******************************************************************************
 * XTouch.cpp
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
#include "XTouch.h"

#if defined(__XHW__)

XTouchCalibration::XTouchCalibration()
{
	Center = XPoint(0x07FF, 0x07FF);
	Max = XPoint(0x0FFF, 0x0FFF);
	Flags = 0;
}

// ******************************************************************************

XTouch::XTouch(XGLCD& lcd, uint32_t freq)
	: LCD(lcd)
{
	// predefined pins
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1284P__)
	CS.Pin(10);
	DIN.Pin(14);
	DOUT.Pin(9);
	CLK.Pin(15);
	PENIRQ.Pin(8);
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__SAM3X8E__)
	CS.Pin(5);
	DIN.Pin(4);
	DOUT.Pin(3);
	CLK.Pin(6);
	PENIRQ.Pin(2);
#elif defined(__32MX320F128H__) || defined(__32MX340F512H__)
	CS.Pin(21);
	DIN.Pin(22);
	DOUT.Pin(23);
	CLK.Pin(20);
	PENIRQ.Pin(24);
#elif defined(__32MX795F512L__)
	CS.Pin(63);
	DIN.Pin(64);
	DOUT.Pin(65);
	CLK.Pin(62);
	PENIRQ.Pin(66);
#elif defined(__MK20DX128__) || defined(__MK20DX256__)
	CS.Pin(31);
	DIN.Pin(27);
	DOUT.Pin(28);
	CLK.Pin(26);
	PENIRQ.Pin(29);
#elif defined(__CC3200R1M1RGC__)
	CS.Pin(13);
	DIN.Pin(19);
	DOUT.Pin(28);
	CLK.Pin(31);
	PENIRQ.Pin(17);
#endif
	m_delay = XFreqCycles(freq);
	m_flags = 0;
	m_lasttouch = 0;
	m_touching = false;
}

int16_t XTouch::SendCB(uint8_t cb, uint16_t t)
{
	// this function makes use of the 15 clk cycle mode
	bool check = (t > 0);
	bool more = check;
	uint8_t s = 0;
	uint8_t cbm = cb;
	bool first = true;
	bool pending = false;
	int16_t data = 0;
	int16_t previous = -1;
	int16_t retries = 5;
	for (uint8_t c = 0; c < 24; c++)
	{
		// starts another command on the 15th clk while receiving
		if (more && (c == 15))
		{
			s = 0;
			cbm = cb;
			pending = true;
		}
		// sending command
		if (s < 8)
		{
			DIN = cbm & 0x80;
			cbm <<= 1;
			s++;
		}
		// pulse clock
		CLK.PulseHigh(m_delay);
		// complete pending command cycle from the 8th clk
		if (pending && (c == 23))
		{
			c = 8;
			first = false;
			pending = false;
		}
		// skipping ending checked data and data-less cycles
		if (first || (check && !more) || (c < 8) || (c > 20))
			continue;
		if (c < 20)
		{
			// receiving data skipping last 3 zero bits
			data <<= 1;
			if (DOUT)
				data++;
			continue;
		}
		if (!check)
			continue;
		// 2 consecutive samples near tollerance
		if (previous >= 0)
		{
			int16_t d = previous - data;
			if (abs(d) <= t)
			{
				more = false;
				data = (previous + data) >> 1;
			}
			else
			{
				more = --retries > 0;
				if (!more)
					data = -1;
			}
		}
		if (!more)
			continue;
		previous = data;
		data = 0;
	}
	return data;
}

void XTouch::Init(const XTouchCalibration& tc)
{
	// initialize pins
	CS.InitOutput(HIGH);
	DIN.InitOutput();
	DOUT.InitInput();
	CLK.InitOutput();
	PENIRQ.InitInput(true);
	// send a reset command
	CS.Low();
	SendCB(0xE0);
	CS.High();
	// sets default params
	SetCalibration(tc);
	m_lasttouch = 0;
	m_touching = false;
}

bool XTouch::IsTouched()
{
	// checks !PENIRQ
	bool touched = !PENIRQ;
	// avoids spurious detouches
	uint32_t ms = millis();
	if (touched)
		m_lasttouch = ms;
	else if (m_lasttouch)
	{
		touched = ((ms - m_lasttouch) < 100);
		if (!touched)
			m_lasttouch = 0;
	}
	return touched;
}

XPoint XTouch::Read(const XSize& t, bool cal)
{
	if (!IsTouched())
		return X_InvalidPoint;
	CS.Low();
	uint32_t sx = 0;
	uint32_t sy = 0;
	uint16_t count = 0;
	uint16_t fails = 1;
	auto _Add = [&sx, &sy, &count](XPoint _l) -> void
	{
		sx += _l.x;
		sy += _l.y;
		count++;
	};
	// about 8 pixels tollerance
	XSize ts = cal ? t : XSize(t.Width << 3, t.Height << 3);
	uint32_t ms = cal ? millis() : 0;
	XPoint previous = X_InvalidPoint;
	while (IsTouched() && (cal || (count < 5)))
	{
		if (PENIRQ)
			continue;
		// calibrating for 1/2 second
		if (cal && ((millis() - ms) > 500))
		{
			cal = false;
			break;
		}
		// try to get current location
		XPoint l(SendCB(0x90, t.Width), SendCB(0xD0, t.Height));
		if ((l.x < 0) || (l.y < 0))
			continue;
		if (previous.IsValid())
		{
			// consecutive locations within tollerance
			XPoint d = previous - l;
			if ((abs(d.x) <= ts.Width) && (abs(d.y) <= ts.Height))
			{
				if (!count)
					_Add(previous);
				_Add(l);
			}
			else if (cal)
				fails++;
		}
		previous = l;
	}
	CS.High();
	// good/fails ratio > 2
	return (!cal && ((count / fails) > 2))
		? XPoint(sx / count, sy / count)
		: X_InvalidPoint;
}

bool XTouch::Calibrate(XTouchCalibration& tc)
{
	// max LCD tollerance
	uint16_t dmax = XMax(m_de.x, m_de.y);
	tc = XTouchCalibration();
	XSize t(tc.Max.x / dmax, tc.Max.y / dmax);
	// offset 5% of max LCD
	uint16_t offset = dmax * 5 / 100;
	XRect bounds = LCD.Bounds();
	XPoint db = XPoint(offset, offset);
	XPoint dc = bounds.Center();
	XPoint de = bounds.Ending() - db;
	// read points
	LCD.Clear();
	XPoint mp;
	uint16_t mr = 7;
	XPoint l[5];
	uint16_t count = 0;
	for (int i = 0; i < 5; i++)
	{
		// point coordinates
		switch (i)
		{
			case 0: mp = db; break;
			case 1: mp = XPoint(de.x, db.y); break;
			case 2: mp = XPoint(db.x, de.y); break;
			case 3: mp = de; break;
			case 4: mp = dc; break;
		}
		LCD.Color = X_White;
		LCD.Pixel(mp);
		// reading point
		do
		{
			LCD.Color = X_Red;
			LCD.Circle(mp, mr);
			WaitForTouch(false);
			WaitForTouch();
			// acquiring point
			LCD.Color = X_Green;
			LCD.Circle(mp, mr);
			l[i] = Read(t, true);
			if (l[i].IsValid())
			{
				count++;
				break;
			}
		} while (!IsTouched());
		// point acquired
		LCD.Color = l[i].IsValid() ? X_Green : X_Red;
		LCD.FillCircle(mp, mr);
	}
	WaitForTouch(false);
	if (count < 5)
		return false;
	// flags to LCD rotation
	tc.Flags = XGLCD::RotateFlags(0, LCD.Rotation());
	// check swap
	XPoint& c = l[4];
	XSize dqs = dc - db;
	if (((l[0].y > c.y) && (l[1].y < c.y)) || ((l[0].y < c.y) && (l[1].y > c.y)))
	{
		X_ToggleFlag(tc.Flags, X_LCDSwap);
		XSwap(l[1], l[2]);
		XSwap(dqs.Width, dqs.Height);
	}
	// calculating calibration
	XPoint b((l[0].x + l[2].x) >> 1, (l[0].y + l[1].y) >> 1);
	tc.Center = c;
	XPoint e((l[1].x + l[3].x) >> 1, (l[2].y + l[3].y) >> 1);
	// check flip
	if (b.x > e.x)
	{
		X_ToggleFlag(tc.Flags, X_LCDHFlip);
		XSwap(b.x, e.x);
	}
	if (b.y > e.y)
	{
		X_ToggleFlag(tc.Flags, X_LCDVFlip);
		XSwap(b.y, e.y);
	}
	// fix quadrant offset
	XSize tqs = c - b;
	b.x -= (int32_t) tqs.Width * offset / dqs.Width;
	b.y -= (int32_t) tqs.Height * offset / dqs.Height;
	tc.Min = b;
	tqs = e - c;
	e.x += (int32_t) tqs.Width * offset / dqs.Width;
	e.y += (int32_t) tqs.Height * offset / dqs.Height;
	tc.Max = e;
	SetCalibration(tc);
	return true;
}

void XTouch::SetCalibration(const XTouchCalibration& tc)
{
	m_origin = tc.Min;
	m_e1 = tc.Center - tc.Min;
	m_e2 = tc.Max - tc.Center;
	XPoint te = tc.Max - tc.Min;
	m_flags = XGLCD::RotateFlags(tc.Flags, LCD.Rotation());
	// adapt screen coordinates to touch hw orientation
	XRect db = LCD.Bounds();
	m_dc = db.Center();
	m_de = db.Ending();
	if (X_GetFlag(m_flags, X_LCDSwap))
	{
		XSwap(m_dc.x, m_dc.y);
		XSwap(m_de.x, m_de.y);
	}
	// tollerance
	m_t = XSize(te.x / m_de.x, te.y / m_de.y);
}

XEvent XTouch::PollEvent()
{
	XPoint l = Read(m_t);
	if (l.IsValid())
	{
		// fixing origin
		l -= m_origin;
		// defining quadrant bounds and offset
		XPoint e = m_e1;
		XPoint offset;
		if (l.x > m_e1.x)
		{
			l.x -= m_e1.x;
			e.x = m_e2.x;
			offset.x = m_dc.x + 1;
		}
		if (l.y > m_e1.y)
		{
			l.y -= m_e1.y;
			e.y = m_e2.y;
			offset.y = m_dc.y + 1;
		}
		// translating quadrant coordinates
		l.x = (int32_t) l.x * m_dc.x / e.x;
		l.x = XInRange(l.x, (int16_t) 0, m_dc.x);
		l.y = (int32_t) l.y * m_dc.y / e.y;
		l.y = XInRange(l.y, (int16_t) 0, m_dc.y);
		l += offset;
		// fixing rotation
		if (X_GetFlag(m_flags, X_LCDHFlip))
			l.x = m_de.x - l.x;
		if (X_GetFlag(m_flags, X_LCDVFlip))
			l.y = m_de.y - l.y;
		if (X_GetFlag(m_flags, X_LCDSwap))
			XSwap(l.x, l.y);
		m_l = l;
		if (m_touching)
			return XEvent(XEvents::Drag, m_l);
		m_touching = true;
		return XEvent(XEvents::Push, m_l);
	}
	else if (m_touching)
	{
		m_touching = false;
		return XEvent(XEvents::Release, m_l);
	}
	return XEvents::None;
}

#endif // __XHW__
