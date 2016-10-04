/*******************************************************************************
 * XText.h
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

#ifndef XText_h
#define XText_h

/// Text class
class XText
{
public:
	/// Default font pointer
	static const XData* DefaultFont;

	/// Horizontal and vertical alignment
	uint8_t Alignment;
	/// Wrap
	bool Wrap;
	/// Fixed size
	bool Fixed;
	/// Line leading
	int8_t Leading;
	/// Letter tracking
	int8_t Tracking;
	/// Font pointer
	const XData* Font;
	/// Value
	XString Value;
	
	/// Constructor
	/// @param pstr Source string pointer
	XText(PCSTR pstr = NULL);
	/// Constructor
	/// @param text Source text
	XText(const XText& text);
	
	/// Assigns a string to this instance
	XString& operator=(PCSTR pstr);
	/// Assigns a string to this instance
	XText& operator=(const XText& text);
};

#endif
