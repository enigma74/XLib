/*******************************************************************************
 * XRect.cpp
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

#include "XGraph.h"
#include "XRect.h"

#define X_SizeEnding(size) XPoint(Size.Width - 1, Size.Height - 1)
#define X_SizeCenter(size) XPoint((size.Width >> 1) - 1, (size.Height >> 1) - 1)

// ********************************************************************************

bool XPoint::operator==(const XPoint& b) const
{
	return (x == b.x) && (y == b.y);
}

bool XPoint::operator!=(const XPoint& b) const
{
	return !(*this == b);
}

XPoint& XPoint::operator+=(const XPoint& b)
{
	x = XSafeInt16(x) + b.x;
	y = XSafeInt16(y) + b.y;
	return *this;
}

XPoint& XPoint::operator-=(const XPoint& b)
{
	x = XSafeInt16(x) - b.x;
	y = XSafeInt16(y) - b.y;
	return *this;
}

XPoint XPoint::operator+(const XPoint& b) const
{
	return XPoint(*this) += b;
}

XPoint XPoint::operator-(const XPoint& b) const
{
	return XPoint(*this) -= b;
}

// ********************************************************************************

bool XSize::operator==(const XSize& b) const
{
	return (Width == b.Width) && (Height == b.Height);
}

bool XSize::operator!=(const XSize& b) const
{
	return !(*this == b);
}

XSize& XSize::operator+=(const XSize& b)
{
	Width = XSafeUInt16(Width) + b.Width;
	Height = XSafeUInt16(Height) + b.Height;
	return *this;
}

XSize& XSize::operator-=(const XSize& b)
{
	Width = XSafeUInt16(Width) - b.Width;
	Height = XSafeUInt16(Height) - b.Height;
	return *this;
}

XSize XSize::operator+(const XSize& b) const
{
	return XSize(*this) += b;
}

XSize XSize::operator-(const XSize& b) const
{
	return XSize(*this) -= b;
}

XSize& XSize::operator*=(float factor)
{
	Width = XSafeUInt16(Width) * factor;
	Height = XSafeUInt16(Height) * factor;
	return *this;
}

XSize& XSize::operator/=(float factor)
{
	Width = XSafeUInt16(Width) / factor;
	Height = XSafeUInt16(Height) / factor;
	return *this;
}

XSize XSize::operator*(float factor) const
{
	return XSize(*this) *= factor;
}

XSize XSize::operator/(float factor) const
{
	return XSize(*this) /= factor;
}

// ********************************************************************************

XRect::XRect(const XPoint& location, const XPoint& ending)
{
	Location = XPoint(XMin(location.x, ending.x), XMin(location.y, ending.y));
	XPoint b = XPoint(XMax(location.x, ending.x), XMax(location.y, ending.y));
	Size = XSize(b.x - Location.x + 1, b.y - Location.y + 1);
}

XRect& XRect::operator+=(const XPoint& b)
{
	Location += b;
	return *this;
}

XRect& XRect::operator-=(const XPoint& b)
{
	Location -= b;
	return *this;
}

XRect XRect::operator+(const XPoint& b) const
{
	return XRect(*this) += b;
}

XRect XRect::operator-(const XPoint& b) const
{
	return XRect(*this) -= b;
}

XRect& XRect::operator+=(const XRectDelta& delta)
{
	Location -= XPoint(delta.Left, delta.Top);
	Size += XSize(delta.Left + delta.Right, delta.Top + delta.Bottom);
	return *this;
}

XRect& XRect::operator-=(const XRectDelta& delta)
{
	uint16_t dl = delta.Left;
	uint16_t dt = delta.Top;
	uint16_t dw = delta.Left + delta.Right;
	uint16_t dh = delta.Top + delta.Bottom;
	uint16_t w = Size.Width;
	if (dw > w)
		dl = (uint16_t) ((uint32_t) dl * w / dw);
	uint16_t h = Size.Height;
	if (dh > h)
		dt = (uint16_t) ((uint32_t) dt * h / dh);
	Location += XPoint(dl, dt);
	Size -= XSize(dw, dh);
	return *this;
}

XRect XRect::operator+(const XRectDelta& delta) const
{
	return XRect(*this) += delta;
}

XRect XRect::operator-(const XRectDelta& delta) const
{
	return XRect(*this) -= delta;
}

XPoint XRect::Ending() const
{
	return Location + X_SizeEnding(Size);
}

XPoint XRect::Center() const
{
	return Location + X_SizeCenter(Size);
}

bool XRect::Contains(const XPoint& point) const
{
	int16_t x = point.x;
	int16_t y = point.y;
	XPoint ending = Ending();
	return (x >= Location.x) && (x <= ending.x) && (y >= Location.y) && (y <= ending.y);
}

XRect XRect::Fix(XRect rect) const
{
	if (IsEmpty() || rect.IsEmpty())
		return XRect();
	if (rect.Size == XSize(1, 1))
		return Contains(rect.Location) ? rect : XRect();
	XPoint l = rect.Location;
	XPoint ending = Ending();
	if ((l.x > ending.x) || (l.y > ending.y))
		return XRect();
	rect.Location.x = XMax(rect.Location.x, Location.x);
	rect.Location.y = XMax(rect.Location.y, Location.y);
	l = rect.Location - l;
	rect.Size -= XSize(l.x, l.y);
	l = rect.Location - Location;
	XSize max = Size - XSize(l.x, l.y);
	rect.Size.Width = XMin(rect.Size.Width, max.Width);
	rect.Size.Height = XMin(rect.Size.Height, max.Height);
	return rect;
}

XRectRadius XRect::Fix(XRectRadius rr) const
{
	if (IsEmpty() || !rr.IsSet())
		return XRectRadius();
	uint16_t w = Size.Width;
	if (rr.Top() || rr.Bottom())
		w >>= 1;
	uint16_t h = Size.Height;
	if (rr.Left() || rr.Right())
		h >>= 1;
	rr.r = XMin(rr.r, h < w ? h : w);
	return rr;
}
