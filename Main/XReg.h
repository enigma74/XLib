/*******************************************************************************
 * XReg.h
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
