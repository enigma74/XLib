/*******************************************************************************
 * XColor.h
 * Omitted alpha channel due to uselessness, at the time
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

#ifndef XColor_h
#define XColor_h

#define X_Black			XColor(0x00, 0x00, 0x00)
#define X_LightBlack		XColor(0x1F, 0x1F, 0x1F)
#define X_DarkGrey		XColor(0x3F, 0x3F, 0x3F)
#define X_Grey				XColor(0x7F, 0x7F, 0x7F)
#define X_LightGrey		XColor(0xBF, 0xBF, 0xBF)
#define X_White			XColor(0xFF, 0xFF, 0xFF)

#define X_DarkBlue		XColor(0x00, 0x00, 0x7F)
#define X_Blue				XColor(0x00, 0x00, 0xFF)
#define X_DarkGreen		XColor(0x00, 0x7F, 0x00)
#define X_Green			XColor(0x00, 0xFF, 0x00)
#define X_DarkCyan		XColor(0x00, 0x7F, 0x7F)
#define X_Cyan				XColor(0x00, 0xFF, 0xFF)
#define X_DarkRed			XColor(0x7F, 0x00, 0x00)
#define X_Red				XColor(0xFF, 0x00, 0x00)
#define X_DarkMagenta	XColor(0x7F, 0x00, 0x7F)
#define X_Magenta			XColor(0xFF, 0x00, 0xFF)
#define X_DarkYellow		XColor(0x7F, 0x7F, 0x00)
#define X_Yellow			XColor(0xFF, 0xFF, 0x00)

#define X_Orange			XColor(0xFF, 0x99, 0x00)

#define X_NoColor			XColor()

/// Color mode
enum class XColorMode : uint8_t
{
	/// Monochrome black and white
	Mono,
	/// RGB 8 colors
	RGB111,
	/// RGB 65K colors
	RGB565,
	/// RGB 262K colors
	RGB666,
	/// RGB 16M colors
	RGB888,
	/// No color
	NoColor
};

// ********************************************************************************

/// Color structure
struct XColor
{
	/// Red component
	uint8_t r;
	/// Green component
	uint8_t g;
	/// Blue component
	uint8_t b;

	/// Constructor
	/// @param _r Red component
	/// @param _g Green component
	/// @param _b Blue component
	/// @param mode Color mode
	XColor(uint8_t _r, uint8_t _g, uint8_t _b, XColorMode mode = XColorMode::RGB888);
	
	/// Constructor
	/// @param mode Color mode
	XColor(XColorMode mode = XColorMode::NoColor)
		: XColor(0x00, 0x00, 0x00, mode)
	{
	}

	/// Returns color mode
	inline XColorMode Mode() const
	{
		return m_mode;
	}

	/// Check for a valid color
	inline bool IsValid() const
	{
		return m_mode != XColorMode::NoColor;
	}

	/// Comparison == operator
	inline bool operator==(const XColor& color) const
	{
		return (r == color.r) && (g == color.g) && (b == color.b) && (m_mode == color.m_mode);
	}

	/// Comparison != operator
	inline bool operator!=(const XColor& color) const
	{
		return !(*this == color);
	}
	
	/// Adds other color to this instance
	XColor& operator+=(const XColor& other);
	/// Subtracts other color from this instance
	XColor& operator-=(const XColor& other);

	/// Addition operator
	inline XColor operator+(const XColor& other) const
	{
		return XColor(*this) += other;
	}

	/// Subtraction operator
	inline XColor operator-(const XColor& other) const
	{
		return XColor(*this) -= other;
	}

	/// Increments this instance by the specified amount
	inline XColor& operator+=(uint8_t value)
	{
		return *this += XColor(value, value, value, m_mode);
	}

	/// Decrements this instance by the specified amount
	inline XColor& operator-=(uint8_t value)
	{
		return *this -= XColor(value, value, value, m_mode);
	}

	/// Addition operator
	inline XColor operator+(uint8_t value) const
	{
		return XColor(*this) += value;
	}

	/// Subtraction operator
	inline XColor operator-(uint8_t value) const
	{
		return XColor(*this) -= value;
	}

	/// Converts color mode
	/// @param mode Color mode
	XColor To(XColorMode mode) const;
	/// Encodes current color
	uint32_t Encode() const;
	/// Decodes the specified color
	/// @param rgb Encoded color
	/// @param mode Color mode
	static XColor Decode(uint32_t rgb, XColorMode mode = XColorMode::RGB888);

	/// Blends the color over another
	/// @param back Back color
	/// @param a Alpha channel
	XColor BlendTo(XColor back, uint8_t a) const;

private:
	/// Color mode
	XColorMode m_mode;
	/// Returns specified color mode limits
	/// @param mode Color mode
	static XColor ModeLimits(XColorMode mode);
};

#endif
