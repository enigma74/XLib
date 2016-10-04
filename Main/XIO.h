/*******************************************************************************
 * XIO.h
 *
 * Copyright (c) Moreno Seri (moreno.seri@gmail.com)
 *
 * This file is part of XLib.
 *
 * XLib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
