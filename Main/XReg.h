/*******************************************************************************
 * XReg.h
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

#ifndef XReg_h
#define XReg_h

#if defined(__XHW__)

#if defined(__AVR__) || defined(__arm__)
	#if defined(ENERGIA)
		#define portInputRegister(p) portBASERegister(p)
		#define portOutputRegister(p) portBASERegister(p)
	#endif
	#if defined(__AVR__) || (TEENSYDUINO >= 117)
		typedef volatile uint8_t* XPReg;
		typedef uint8_t XVReg;
	#else
		typedef volatile uint32_t* XPReg;
		typedef uint32_t XVReg;
	#endif
#elif defined(__PIC32MX__)
	typedef volatile uint32_t* XPReg;
	typedef uint16_t XVReg;
#endif

/// Register manipulation functions
class XReg
{
public:
	/// Gets the state of specified bit mask in the specified register
	/// @param pr Register pointer
	/// @param bm Register bit mask
	static inline bool Get(XPReg pr, XVReg bm)
	{
#if defined(__AVR__) || defined(__arm__)
	#if defined(ENERGIA)
		return HWREG((uint32_t)pr + 0x3FC) & bm;
	#else
		return *pr & bm;
	#endif
#elif defined(__PIC32MX__)
		return *pr & bm;
#endif
	}

	/// Sets the specified bit mask in the specified register
	/// @param pr Register pointer
	/// @param bm Register bit mask
	static inline void Set(XPReg pr, XVReg bm)
	{
#if defined(__AVR__) || defined(__arm__)
	#if defined(ENERGIA)
		HWREG((uint32_t)pr + 0x3FC) |= bm;
	#else
		*pr |= bm;
	#endif
#elif defined(__PIC32MX__)
		*(pr + 2) = bm;
#endif
	}

	/// Clears the specified bit mask from the specified register
	/// @param pr Register pointer
	/// @param bm Register bit mask
	static inline void Clear(XPReg pr, XVReg bm)
	{
#if defined(__AVR__) || defined(__arm__)
	#if defined(ENERGIA)
		HWREG((uint32_t)pr + 0x3FC) &= ~bm;
	#else
		*pr &= ~bm;
	#endif
#elif defined(__PIC32MX__)
		*(pr + 1) = bm;
#endif
	}
};

#endif // __XHW__
#endif
