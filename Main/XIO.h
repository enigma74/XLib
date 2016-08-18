/*******************************************************************************
 * XIO.h
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

#ifndef XIO_h
#define XIO_h

#if defined(__XHW__)

#define X_NoPin 0xFF

/// Fast digital input/output class
class XIO
{
public:
	/// Constructor
	/// @param pin Pin number
	XIO(uint8_t pin = X_NoPin);

	/// Sets pin number
	/// @param pin Pin number
	void Pin(uint8_t pin);

	/// Returns current pin number
	inline uint8_t Pin() const
	{
		return m_pin;
	}

	/// Checks initialization
	inline bool IsInit() const
	{
		return m_pr;
	}

	/// Initializes the pin as input
	/// @param pullup Pullup flag
	inline void InitInput(bool pullup = false)
	{
		Init(pullup ? INPUT_PULLUP : INPUT);
	}

	/// Gets the pin state
	inline bool State() const
	{
		return m_pr && XReg::Get(m_pr, m_bm);
	}

	/// Gets the pin state
	inline operator bool() const
	{
		return m_pr && XReg::Get(m_pr, m_bm);
	}

	// ******************************************************************************

	/// Checks for output initialization
	inline bool IsOutput() const
	{
		return m_output;
	}

	/// Initializes the pin as output
	/// @param state Initial pin state
	inline void InitOutput(bool state = LOW)
	{
		Init(OUTPUT);
		State(state);
	}

	/// Sets the pin state
	/// @param state Pin state
	inline void State(bool state) const
	{
		if (!m_output)
			return;
		if (state)
			XReg::Set(m_pr, m_bm);
		else
			XReg::Clear(m_pr, m_bm);
	}

	/// Sets the pin state
	inline const XIO& operator=(const XIO& pin) const
	{
		State(pin);
		return *this;
	}

	/// Sets the pin state
	inline const XIO& operator=(bool state) const
	{
		State(state);
		return *this;
	}

	/// Sets the pin to high
	inline void High() const
	{
		if (m_output)
			XReg::Set(m_pr, m_bm);
	}

	/// Sets the pin to low
	inline void Low() const
	{
		if (m_output)
			XReg::Clear(m_pr, m_bm);
	}

	/// Sets the pin to high than back to low within about the specified number of cycles
	/// @param cycles Clock cycles
	inline void PulseHigh(uint32_t cycles = 0) const
	{
		if (!m_output)
		return;
		if (!cycles)
		{
			XReg::Set(m_pr, m_bm);
			XReg::Clear(m_pr, m_bm);
			return;
		}
		cycles >>= 1;
		XReg::Set(m_pr, m_bm);
		XWaitCycles(cycles);
		XReg::Clear(m_pr, m_bm);
		XWaitCycles(cycles);
	}

	/// Sets the pin to low than back to high within about the specified number of cycles
	/// @param cycles Clock cycles
	inline void PulseLow(uint32_t cycles = 0) const
	{
		if (!m_output)
		return;
		if (!cycles)
		{
			XReg::Clear(m_pr, m_bm);
			XReg::Set(m_pr, m_bm);
			return;
		}
		cycles >>= 1;
		XReg::Clear(m_pr, m_bm);
		XWaitCycles(cycles);
		XReg::Set(m_pr, m_bm);
		XWaitCycles(cycles);
	}

private:
	/// Pin number
	uint8_t m_pin;
	/// Output flag
	bool m_output;
	/// Register pointer
	XPReg m_pr;
	/// Register bit mask
	XVReg m_bm;

	/// Initializes the pin
	/// @param mode Pin mode
	void Init(uint8_t mode);

	// Delete copy constructor and assignment operator
	XIO(const XIO&) = delete;
};

#endif // __XHW__
#endif
