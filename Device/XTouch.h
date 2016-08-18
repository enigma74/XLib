/*******************************************************************************
 * XTouch.h
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

#ifndef XTouch_h
#define XTouch_h

#if defined(__XHW__)

/// Touch screen calibration data
struct XTouchCalibration
{
	/// Minimum
	XPoint Min;
	/// Center
	XPoint Center;
	/// Maximum
	XPoint Max;
	/// Rotation flags
	uint8_t Flags;

	/// Constructor
	XTouchCalibration();
};

// ******************************************************************************

/// Touch screen class
class XTouch : public XEventPool
{
public:
	/// LCD
	XGLCD& LCD;
	/// Chip select pin
	XIO CS;
	/// Chip data input pin
	XIO DIN;
	/// Chip data output pin
	XIO DOUT;
	/// Clock pin
	XIO CLK;
	/// Pen interrupt request pin
	XIO PENIRQ;

	/// Constructor
	/// @param lcd LCD
	/// @param freq Target frequency
	XTouch(XGLCD& lcd, uint32_t freq = X_2Mhz);

	/// Initializes the touch
	/// @param tc Calibration data
	void Init(const XTouchCalibration& tc = XTouchCalibration());

	/// Checks for touch
	bool IsTouched();

	/// Waits for touch/detouch
	/// @param touch Touch state to wait
	inline void WaitForTouch(bool touch = true)
	{
		while (IsTouched() != touch) ;
	}

	/// Calibrates the touch
	/// @param tc Calibration data
	bool Calibrate(XTouchCalibration& tc);
	/// Sets calibration data
	/// @param tc Calibration data
	void SetCalibration(const XTouchCalibration& tc);
	/// Poll an available event
	virtual XEvent PollEvent() override;

private:
	/// Clock cycles to compensate frequency
	uint32_t m_delay;

	/// Origin touch point
	XPoint m_origin;
	/// Ending touch point 1
	XPoint m_e1;
	/// Ending touch point 2
	XPoint m_e2;
	/// Rotation flags
	uint8_t m_flags;
	/// Center display point
	XPoint m_dc;
	/// Ending display point
	XPoint m_de;
	/// Tollerance
	XSize m_t;

	/// Milliseconds from last touch check
	uint32_t m_lasttouch;
	/// Touching flag
	bool m_touching;
	/// Touching location
	XPoint m_l;

	/// Sends a control byte and returns the response
	/// @param cb Control byte
	/// @param t Tollerance for axis read
	int16_t SendCB(uint8_t cb, uint16_t t = 0);
	/// Reads current uncalibrated touch location
	/// @param t Tollerance
	/// @param cal Calibration flag
	XPoint Read(const XSize& t, bool cal = false);

private:
	// Delete copy constructor and assignment operator
	XTouch(const XTouch&) = delete;
	XTouch& operator=(const XTouch&) = delete;
};

#endif // __XHW__
#endif
