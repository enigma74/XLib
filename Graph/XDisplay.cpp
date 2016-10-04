/*******************************************************************************
 * XDisplay.cpp
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
#include "XDisplay.h"

XDisplay::XDisplay(const XSize& size)
	: XContext(*this, size)
{
	m_count = 0;
}

// ********************************************************************************

void XDisplay::OnBegin()
{
	if (!m_count)
		OnBeginSequence();
	m_count++;
}

void XDisplay::OnEnd()
{
	if (!m_count)
		return;
	m_count--;
	if (!m_count)
		OnEndSequence();
}
