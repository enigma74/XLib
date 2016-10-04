/*******************************************************************************
 * XColor.cpp
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
#include "XColor.h"

#define X_Convert(c, s, t) (uint8_t)((c & s) * t / s)

XColor::XColor(uint8_t _r, uint8_t _g, uint8_t _b, XColorMode mode)
{
	m_mode = mode;
	r = _r;
	g = _g;
	b = _b;
}

XColor& XColor::operator+=(const XColor& other)
{
	XColor color = other.To(m_mode);
	r = XSafeUInt8(r) + color.r;
	g = XSafeUInt8(g) + color.g;
	b = XSafeUInt8(b) + color.b;
	return *this;
}

XColor& XColor::operator-=(const XColor& other)
{
	XColor color = other.To(m_mode);
	r = XSafeUInt8(r) - color.r;
	g = XSafeUInt8(g) - color.g;
	b = XSafeUInt8(b) - color.b;
	return *this;
}

XColor XColor::ModeLimits(XColorMode mode)
{
	switch (mode)
	{
		case XColorMode::Mono:
		case XColorMode::RGB111:
			return XColor(0x01, 0x01, 0x01);
		case XColorMode::RGB565:
			return XColor(0x1F, 0x3F, 0x1F);
		case XColorMode::RGB666:
			return XColor(0x3F, 0x3F, 0x3F);
		case XColorMode::RGB888:
			return XColor(0xFF, 0xFF, 0xFF);
		default:
			return X_NoColor;
	}
}

XColor XColor::To(XColorMode mode) const
{
	if (mode == m_mode)
		return *this;
	if (mode == XColorMode::NoColor)
		return X_NoColor;
	XColor color(mode);
	if (!IsValid())
		return color;
	XColor s = ModeLimits(m_mode);
	XColor t = ModeLimits(mode);
	color.r = X_Convert(r, s.r, t.r);
	color.g = X_Convert(g, s.g, t.g);
	color.b = X_Convert(b, s.b, t.b);
	return color;
}

uint32_t XColor::Encode() const
{
	switch (m_mode)
	{
		case XColorMode::Mono:
			return (r + g + b) ? 1 : 0;
		case XColorMode::RGB111:
			return (((uint32_t) r << 2) | ((uint32_t) g << 1) | b) & 0x00000003;
		case XColorMode::RGB565:
			return (((uint32_t) r << 11) | ((uint32_t) g << 5) | b) & 0x0000FFFF;
		case XColorMode::RGB666:
			return (((uint32_t) r << 12) | ((uint32_t) g << 6) | b) & 0x0003FFFF;
		case XColorMode::RGB888:
			return (((uint32_t) r << 16) | ((uint32_t) g << 8) | b) & 0x00FFFFFF;
		default:
			return 0;
	}
}

XColor XColor::Decode(uint32_t rgb, XColorMode mode)
{
	XColor color(mode);
	if (!color.IsValid())
		return color;
	switch (mode)
	{
		case XColorMode::Mono:
			color.r = color.g = color.b = rgb ? 1 : 0;
			break;
		case XColorMode::RGB111:
			color.r = (uint8_t) ((rgb >> 2) & 0x01);
			color.g = (uint8_t) ((rgb >> 1) & 0x01);
			color.b = (uint8_t) (rgb & 0x01);
			break;
		case XColorMode::RGB565:
			color.r = (uint8_t) ((rgb >> 11) & 0x1F);
			color.g = (uint8_t) ((rgb >> 5) & 0x3F);
			color.b = (uint8_t) (rgb & 0x1F);
			break;
		case XColorMode::RGB666:
			color.r = (uint8_t) ((rgb >> 12) & 0x3F);
			color.g = (uint8_t) ((rgb >> 6) & 0x3F);
			color.b = (uint8_t) (rgb & 0x3F);
			break;
		case XColorMode::RGB888:
			color.r = (uint8_t) (rgb >> 16);
			color.g = (uint8_t) (rgb >> 8);
			color.b = (uint8_t) rgb;
			break;
		default:
			break;
	}
	return color;
}

XColor XColor::BlendTo(XColor back, uint8_t a) const
{
	back = back.To(m_mode);
	if (!IsValid() || !a)
		return back;
	if (a == 0xFF)
		return *this;
	uint16_t fa = a + 1;
	uint16_t ba = 256 - a;
	back.r = (uint8_t) ((r * fa + back.r * ba) >> 8);
	back.g = (uint8_t) ((g * fa + back.g * ba) >> 8);
	back.b = (uint8_t) ((b * fa + back.b * ba) >> 8);
	return back;
}

//XColor XColor::FadeBy(uint8_t _a) const
//{
//	if (_a)
//		_a = (_a == 0xFF) ? a : a * _a / 0xFF;
//	return XColor(r, g, b, _a);
//}

//XColor XColor::Opaque() const
//{
//	if (a == 0xFF)
//		return *this;
//	if (!a)
//		return X_Black;
//	XColor opaque;
//	opaque.r = r * a / 0xFF;
//	opaque.g = g * a / 0xFF;
//	opaque.b = b * a / 0xFF;
//	return opaque;
//}
