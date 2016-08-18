/*******************************************************************************
 * XUtils.h
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

#ifndef XUtils_h
#define XUtils_h

#define X_SetFlag(x, f) (x |= f)
#define X_ClearFlag(x, f) (x &= ~f)
#define X_ToggleFlag(x, f) (x ^= f)
#define X_GetFlag(x, f) ((x & f) == f)

#define X_SizeOfA(a) (sizeof(a) / sizeof(a[0]))

/// Swap two items of the same type
/// @tparam T Type of items
/// @param a First item
/// @param b Second item
template <typename T> inline void XSwap(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}

/// Returns the minimum value from two
/// @tparam T Type of values
/// @param a First value
/// @param b Second value
template <typename T> inline T XMin(T a, T b)
{
	return a < b ? a : b;
}

/// Returns the minimum value from three
/// @tparam T Type of values
/// @param a First value
/// @param b Second value
/// @param c Third value
template <typename T> inline T XMin(T a, T b, T c)
{
	return XMin(a, XMin(b, c));
}

/// Returns the maximum value from two
/// @tparam T Type of values
/// @param a First value
/// @param b Second value
template <typename T> inline T XMax(T a, T b)
{
	return a > b ? a : b;
}

/// Returns the maximum value from three
/// @tparam T Type of values
/// @param a First value
/// @param b Second value
/// @param c Third value
template <typename T> inline T XMax(T a, T b, T c)
{
	return XMax(a, XMax(b, c));
}

/// Limits a value to a specified range
/// @tparam T Type of value
/// @param v Value
/// @param min Minimum range value
/// @param max Maximum range value
template <typename T> inline T XInRange(T v, T min, T max)
{
	return (min > max)
		? XMax(XMin(v, min), max)
		: XMax(XMin(v, max), min);
}

/// Returns the high byte of the specified word
/// @param word Word
inline uint8_t XHiByte(uint16_t word)
{
	return word >> 8;
}

/// Returns the low byte of the specified word
/// @param word Word
inline uint8_t XLoByte(uint16_t word)
{
	return (uint8_t)word;
}

/// Returns the high word of the specified dword
/// @param dword DWord
inline uint16_t XHiWord(uint32_t dword)
{
	return dword >> 16;
}

/// Returns the low word of the specified dword
/// @param dword DWord
inline uint16_t XLoWord(uint32_t dword)
{
	return (uint16_t)dword;
}

// ******************************************************************************

/// Template class to do basic math operations on a value in a safe way
/// @tparam T Type of value
/// @tparam TCheck Signed type bigger than T for checks
/// @tparam TMin Minimum value
/// @tparam TMax Maximum value
template <typename T, typename TCheck, T TMin, T TMax> class _XSafe
{
public:
	/// Actual value
	T Value;
	/// Overflow state from last operation
	bool Overflow;
	
	/// Constructor
	/// @param value Value
	_XSafe(T value = T(0))
	{
		Overflow = false;
		Value = value;
	}
	
	/// Returns minimum value
	inline T MinValue() const
	{
		return TMin;
	}
	
	/// Returns maximum value
	inline T MaxValue() const
	{
		return TMax;
	}
	
	/// Returns the actual value
	inline operator T() const
	{
		return Value;
	}
	
	/// Adds a value to current value
	_XSafe& operator+=(T b)
	{
		Overflow = false;
		if (b != 0)
			UseResult((TCheck)Value + b);
		return *this;
	}
	
	/// Returns the result from a value added to current value
	_XSafe operator+(T b) const
	{
		return _XSafe(*this) += b;
	}
	
	/// Subtract a value from current value
	_XSafe& operator-=(T b)
	{
		Overflow = false;
		if (b != 0)
			UseResult((TCheck)Value - b);
		return *this;
	}
	
	/// Returns the result from a value subtracted from current value
	_XSafe operator-(T b) const
	{
		return _XSafe(*this) -= b;
	}
	
	/// Multiplies current value by the specified factor
	_XSafe& operator *=(float f)
	{
		Overflow = false;
		if (f == 0)
			Value = 0;
		else if ((Value != 0) && (f != 1))
			UseResult((TCheck)Value * f);
		return *this;
	}
	
	/// Returns the result of current value multiplied by the specified factor
	_XSafe operator*(float f) const
	{
		return _XSafe(*this) *= f;
	}
	
	/// Divides current value by the specified factor
	_XSafe& operator /=(float f)
	{
		Overflow = false;
		if (f == 0)
		{
			Overflow = true;
			Value = TMax;
		}
		else if ((TMin < 0) && (f == -1) && (Value == TMin))
			Overflow = true;
		else if ((Value != 0) && (f != 1))
			UseResult((TCheck)Value / f);
		return *this;
	}
	
	/// Returns the result of current value divided by the specified factor
	_XSafe operator/(float f) const
	{
		return _XSafe(*this) /= f;
	}
	
private:
	/// Checks and uses the specified result
	/// @param result Result
	void UseResult(TCheck result)
	{
		int e = (result < TMin) ? -1 : ((result > TMax) ? 1 : 0);
		Overflow = e != 0;
		Value = (e < 0) ? TMin : ((e > 0) ? TMax : (T)result);
	}
};

/// Class to do basic math operations on a uint8_t value in a safe way
typedef _XSafe<uint8_t, int16_t, 0x00, 0xFF> XSafeUInt8;
/// Class to do basic math operations on a uint16_t value in a safe way
typedef _XSafe<uint16_t, int32_t, 0x0000, 0xFFFF> XSafeUInt16;
/// Class to do basic math operations on a int16_t value in a safe way
typedef _XSafe<int16_t, int32_t, int16_t(0x8000), 0x7FFF> XSafeInt16;

// ******************************************************************************

#if defined(__XHW__)

#define X_1Mhz 1000000L
#define X_2Mhz 2000000L
#define X_4Mhz 4000000L
#define X_6Mhz 6000000L
#define X_8Mhz 8000000L

/// Returns the number of cycle needed for a cycle of the specified frequency
/// @param freq Target frequency
inline uint32_t XFreqCycles(uint32_t freq)
{
	return (freq > 0) ? ((freq < F_CPU) ? (F_CPU / freq) : 1) : 0;
}

/// Waits for about specified clock cycles
/// @param cycles Clock cycles
inline void XWaitCycles(uint32_t cycles)
{
	// half cycles to compensate while cycle checks
	if (!(cycles >> 1))
		return;
	while (cycles)
	{
		__asm__ __volatile__ ("nop\n\t");
		cycles--;
	}
}

#endif // __XHW__

#endif
