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

#if (defined(__AVR__) || defined(__arm__)) && defined(ENERGIA)
	#define portInputRegister(p) portBASERegister(p)
	#define portOutputRegister(p) portBASERegister(p)
#endif

#define X_NoPin 0xFF

#define X_1Mhz 1000000L
#define X_2Mhz 2000000L
#define X_4Mhz 4000000L
#define X_6Mhz 6000000L
#define X_8Mhz 8000000L

/// Waits for about specified clock cycles
/// @param cycles Clock cycles
inline void XWaitCycles(uint32_t cycles)
{
	if (cycles)
		do
		{
			__asm__ __volatile__ ("nop\n\t");
		} while (--cycles);
}

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
		if (!m_pr)
			return false;
#if defined(__AVR__) || defined(__arm__)
	#if defined(ENERGIA)
		return HWREG((uint32_t)m_pr + 0x3FC) & m_bm;
	#else
		return *m_pr & m_bm;
	#endif
#elif defined(__PIC32MX__)
		return *m_pr & m_bm;
#endif
	}

	/// Gets the pin state
	inline operator bool() const
	{
		return State();
	}

	// ******************************************************************************

	/// Checks for output initialization
	inline bool IsOutput() const
	{
		return m_output;
	}

	/// Initializes the pin as output at the specified frequency
	/// @param freq Target frequency
	/// @param state Initial pin state
	inline void InitDelayedOutput(uint32_t freq, bool state = LOW)
	{
		Init(OUTPUT);
		m_delay = 0;
		if (freq)
		{
			uint32_t max = F_CPU >> 1;
			if (freq < max)
				m_delay = max / freq;
		}
		State(state);
	}

	/// Initializes the pin as output
	/// @param state Initial pin state
	inline void InitOutput(bool state = LOW)
	{
		InitDelayedOutput(0, state);
	}

	/// Sets the pin to high
	inline void High() const
	{
		if (m_output)
			Set();
	}

	/// Sets the pin to low
	inline void Low() const
	{
		if (m_output)
			Clear();
	}

	/// Sets the pin state
	/// @param state Pin state
	inline void State(bool state) const
	{
		if (state)
			Set();
		else
			Clear();
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

	/// Sets the pin to high than back to low
	/// @param count Count
	inline void PulseHigh(uint32_t count = 1) const
	{
		if (!m_output || !count)
			return;
		if (m_delay)
			do
			{
				Set();
				XWaitCycles(m_delay);
				Clear();
				XWaitCycles(m_delay);
			} while (--count);
		else
			do
			{
				Set();
				Clear();
			} while (--count);
	}

	/// Sets the pin to low than back to high
	/// @param count Count
	inline void PulseLow(uint32_t count = 1) const
	{
		if (!m_output || !count)
			return;
		if (m_delay)
			do
			{
				Clear();
				XWaitCycles(m_delay);
				Set();
				XWaitCycles(m_delay);
			} while (--count);
		else
			do
			{
				Clear();
				Set();
			} while (--count);
	}

private:
	/// Pin number
	uint8_t m_pin;
	/// Output flag
	bool m_output;
	/// Clock cycles to compensate frequency
	uint16_t m_delay;
	/// Register pointer and bitmask
#if defined(__AVR__) || defined(__arm__)
	#if defined(__AVR__) || (TEENSYDUINO >= 117)
		volatile uint8_t* m_pr;
		uint8_t m_bm;
	#else
		volatile uint32_t* m_pr;
		uint32_t m_bm;
	#endif
#elif defined(__PIC32MX__)
	volatile uint32_t* m_pr;
	uint16_t m_bm;
#endif

	/// Initializes the pin
	/// @param mode Pin mode
	void Init(uint8_t mode);

	/// Sets the pin to high
	inline void Set() const
	{
#if defined(__AVR__) || defined(__arm__)
	#if defined(ENERGIA)
		HWREG((uint32_t)m_pr + 0x3FC) |= m_bm;
	#else
		*m_pr |= m_bm;
	#endif
#elif defined(__PIC32MX__)
		*(m_pr + 2) = m_bm;
#endif
	}

	/// Sets the pin to low
	inline void Clear() const
	{
#if defined(__AVR__) || defined(__arm__)
	#if defined(ENERGIA)
		HWREG((uint32_t)m_pr + 0x3FC) &= ~m_bm;
	#else
		*m_pr &= ~m_bm;
	#endif
#elif defined(__PIC32MX__)
		*(m_pr + 1) = m_bm;
#endif
	}

	// Delete copy constructor and assignment operator
	XIO(const XIO&) = delete;
};

#endif // __XHW__
#endif
