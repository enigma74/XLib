/*******************************************************************************
 * XIconRenderer.cpp
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
#include "XIconRenderer.h"

XIconRenderer::XIconRenderer(const XRect& rect, const XData* picon)
{
	Init(rect, picon);
}

void XIconRenderer::Init(const XRect& rect, const XData* picon)
{
	m_l = X_InvalidPoint;
	if (picon == NULL)
		return;
	m_rect = rect;
	m_size = GlyphInit(picon);
	XPoint d = XPoint(rect.Size) - m_size;
	m_a = rect.Location + XPoint(d.x >> 1, d.y >> 1);
}

bool XIconRenderer::Next()
{
	do
	{
		XPoint l = GlyphNext();
		if (!l.IsValid())
		{
			m_l = X_InvalidPoint;
			return false;
		}
		m_l = m_a + l;
	} while (!m_rect.Contains(m_l));
	return true;
}
