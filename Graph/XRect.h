/*******************************************************************************
 * XRect.h
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

#ifndef XRect_h
#define XRect_h

#define X_InvalidPoint XPoint(0x8000, 0x8000)

#define X_Center 0x00
#define X_Top 0x01
#define X_Bottom 0x02
#define X_Left 0x04
#define X_Right 0x08
#define X_TopLeft X_Left | X_Top
#define X_TopRight X_Right | X_Top
#define X_BottomLeft X_Left | X_Bottom
#define X_BottomRight X_Right | X_Bottom

#define X_CornerNone 0x00
#define X_CornerTopLeft 0x01
#define X_CornerTopRight 0x02
#define X_CornerBottomLeft 0x04
#define X_CornerBottomRight 0x08
#define X_CornerTop (X_CornerTopLeft | X_CornerTopRight)
#define X_CornerLeft (X_CornerTopLeft | X_CornerBottomLeft)
#define X_CornerRight (X_CornerTopRight | X_CornerBottomRight)
#define X_CornerBottom (X_CornerBottomLeft | X_CornerBottomRight)
#define X_CornerAll (X_CornerTopLeft | X_CornerTopRight | X_CornerBottomLeft | X_CornerBottomRight)

// ********************************************************************************

/// Point location structure
struct XPoint
{
	/// X position
	int16_t x;
	/// Y position
	int16_t y;
	
	/// Constructor
	/// @param _x X position
	/// @param _y Y position
	XPoint(int16_t _x, int16_t _y)
	{
		x = _x;
		y = _y;
	}
	
	/// Constructor
	XPoint()
		: XPoint(0, 0)
	{
	}
	
	/// Comparison == operator
	bool operator==(const XPoint& b) const;
	/// Comparison != operator
	bool operator!=(const XPoint& b) const;
	
	/// Adds other location to this instance
	XPoint& operator+=(const XPoint& b);
	/// Subtracts other location from this instance
	XPoint& operator-=(const XPoint& b);
	/// Addition operator
	XPoint operator+(const XPoint& b) const;
	/// Subtraction operator
	XPoint operator-(const XPoint& b) const;

	/// Check for valid point
	inline bool IsValid() const
	{
		return *this != X_InvalidPoint;
	}
	
	/// Returns a new point with swapped coordinates
	inline XPoint Swap() const
	{
		return XPoint(y, x);
	}

	/// Return the distance from the line of the specified locations
	/// @param a First line location
	/// @param b Second line location
	inline int32_t DistanceFromLine(XPoint a, XPoint b)
	{
		return (b.x - a.x) * (y - a.y) - (b.y - a.y) * (x - a.x);
	}
};

// ********************************************************************************

/// Size structure
struct XSize
{
	/// Width
	uint16_t Width;
	/// Height
	uint16_t Height;
	
	/// Constructor
	/// @param width Width
	/// @param height Height
	XSize(uint16_t width, uint16_t height)
	{
		Width = width;
		Height = height;
	}
	
	/// Constructor
	/// @param p Point as size
	XSize(XPoint p)
		: XSize(p.x, p.y)
	{

	}

	/// Constructor
	XSize()
		: XSize(0, 0)
	{
	}
	
	/// Checks for empty size
	inline bool IsEmpty() const
	{
		return !Width || !Height;
	}

	/// Comparison == operator
	bool operator==(const XSize& b) const;
	/// Comparison != operator
	bool operator!=(const XSize& b) const;

	/// Adds other size to this instance
	XSize& operator+=(const XSize& b);
	/// Subtracts other size from this instance
	XSize& operator-=(const XSize& b);
	/// Addition operator
	XSize operator+(const XSize& b) const;
	/// Subtraction operator
	XSize operator-(const XSize& b) const;
	/// Multiplies the size by the specified factor
	XSize& operator*=(float factor);
	/// Divides the size by the specified factor
	XSize& operator/=(float factor);
	/// Multiplication operator
	XSize operator*(float factor) const;
	/// Division operator
	XSize operator/(float factor) const;
	
	/// Returns the size as point
	inline operator XPoint() const
	{
		return XPoint(Width, Height);
	}

	/// Returns the area
	inline uint32_t Area() const
	{
		return (uint32_t)Width * Height;
	}
};

// ********************************************************************************

/// Rect delta structure
struct XRectDelta
{
	/// Left delta
	uint16_t Left;
	/// Top delta
	uint16_t Top;
	/// Right delta
	uint16_t Right;
	/// Bottom delta
	uint16_t Bottom;
	
	/// Constructor
	/// @param left Left delta
	/// @param top Top delta
	/// @param right Right delta
	/// @param bottom Bottom delta
	XRectDelta(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom)
	{
		Left = left;
		Top = top;
		Right = right;
		Bottom = bottom;
	}
	
	/// Constructor
	/// @param horizontal Horizontal delta
	/// @param vertical Vertical delta
	XRectDelta(uint16_t horizontal, uint16_t vertical)
		: XRectDelta(horizontal, vertical, horizontal, vertical)
	{
	}
	
	/// Constructor
	/// @param delta Common delta
	XRectDelta(uint16_t delta = 0)
		: XRectDelta(delta, delta, delta, delta)
	{
	}
};

// ********************************************************************************

/// Rect corners radius structure
struct XRectRadius
{
	/// Radius
	uint16_t r;
	/// Corners
	uint8_t Corners;
	
	/// Constructor
	/// @param _r Radius
	/// @param corners Corners
	XRectRadius(uint16_t _r = 0, uint8_t corners = X_CornerAll)
	{
		r = _r;
		Corners = corners;
	}
	
	/// Checks for round corners
	inline bool IsSet() const
	{
		return r && Corners;
	}
	
	/// Checks for top left corner
	inline bool TopLeft() const
	{
		return X_GetFlag(Corners, X_CornerTopLeft);
	}
	
	/// Checks for top right corner
	inline bool TopRight() const
	{
		return X_GetFlag(Corners, X_CornerTopRight);
	}
	
	/// Checks for bottom left corner
	inline bool BottomLeft() const
	{
		return X_GetFlag(Corners, X_CornerBottomLeft);
	}
	
	/// Checks for bottom right corner
	inline bool BottomRight() const
	{
		return X_GetFlag(Corners, X_CornerBottomRight);
	}
	
	/// Checks for top corners
	inline bool Top() const
	{
		return X_GetFlag(Corners, X_CornerTop);
	}
	
	/// Checks for left corners
	inline bool Left() const
	{
		return X_GetFlag(Corners, X_CornerLeft);
	}
	
	/// Checks for right corners
	inline bool Right() const
	{
		return X_GetFlag(Corners, X_CornerRight);
	}
	
	/// Checks for bottom corners
	inline bool Bottom() const
	{
		return X_GetFlag(Corners, X_CornerBottom);
	}
};

// ********************************************************************************

/// Rect structure
struct XRect
{
	/// Location
	XPoint Location;
	/// Size
	XSize Size;
	
	/// Constructor
	/// @param location Location
	/// @param size Size
	XRect(const XPoint& location, const XSize& size = XSize(1, 1))
	{
		Location = location;
		Size = size;
	}
	
	/// Constructor
	/// @param size Size
	XRect(const XSize& size)
		: XRect(XPoint(), size)
	{
	}

	/// Constructor
	/// @param x X position
	/// @param y Y position
	/// @param width Width
	/// @param height Height
	XRect(int16_t x, int16_t y, uint16_t width, uint16_t height)
		: XRect(XPoint(x, y), XSize(width, height))
	{
	}

	/// Constructor
	XRect()
		: XRect(XPoint(), XSize())
	{
	}
	
	/// Constructor
	/// @param location Location
	/// @param ending Ending location
	XRect(const XPoint& location, const XPoint& ending);
	
	/// Adds other location to this instance
	XRect& operator+=(const XPoint& b);
	/// Subtracts other location from this instance
	XRect& operator-=(const XPoint& b);
	/// Location addition operator
	XRect operator+(const XPoint& b) const;
	/// Location subtraction operator
	XRect operator-(const XPoint& b) const;
	
	/// Adds a delta to this instance
	XRect& operator+=(const XRectDelta& delta);
	/// Subtracts a delta from this instance
	XRect& operator-=(const XRectDelta& delta);
	/// Delta addition operator
	XRect operator+(const XRectDelta& delta) const;
	/// Delta subtraction operator
	XRect operator-(const XRectDelta& delta) const;
	
	/// Returns ending location of the rect
	XPoint Ending() const;
	/// Returns center location of the rect
	XPoint Center() const;
	
	/// Checks for empty rect
	inline bool IsEmpty() const
	{
		return Size.IsEmpty();
	}

	/// Returns the area
	inline uint32_t Area() const
	{
		return Size.Area();
	}

	/// Checks if the point is contained by the rect
	/// @param point Point to be checked
	bool Contains(const XPoint& point) const;

	/// Fix the specified rect within bounds of the rect
	/// @param rect Rect to fix
	XRect Fix(XRect rect) const;
	/// Fix the specified corners radius within bounds of the rect
	/// @param rr Corners radius to fix
	XRectRadius Fix(XRectRadius rr) const;
	
	/// Returns a new rect with relative bounds
	inline XRect Relative() const
	{
		return XRect(Size);
	}
	
	/// Translates the specified rect relative point
	/// @param p Relative point
	inline XPoint Translate(XPoint p) const
	{
		return p + Location;
	}

	/// Translates the specified rect relative rect
	/// @param rect Relative rect
	inline XRect Translate(XRect rect) const
	{
		return rect + Location;
	}
};

#endif
