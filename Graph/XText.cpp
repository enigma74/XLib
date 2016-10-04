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

#include "XGraph.h"
#include "XText.h"

const XData* XText::DefaultFont = NULL;

XText::XText(PCSTR pstr)
{
	Alignment = X_TopLeft;
	Wrap = false;
	Fixed = false;
	Leading = 0;
	Tracking = 0;
	Font = DefaultFont;
	Value = pstr;
}

XText::XText(const XText& text)
{
	Alignment = text.Alignment;
	Wrap = text.Wrap;
	Fixed = text.Fixed;
	Leading = text.Leading;
	Tracking = text.Tracking;
	Font = text.Font;
	Value = text.Value;
}

XString& XText::operator=(PCSTR pstr)
{
	return (Value = pstr);
}

XText& XText::operator=(const XText& text)
{
	Value = text.Value;
	return *this;
}
