/*******************************************************************************
 * XLineRenderer.cpp
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
#include "XLineRenderer.h"

#include <math.h>

XLineRenderer::XLineRenderer(XPoint a, XPoint b)
{
	Init(a, b);
}

void XLineRenderer::Init(XPoint a, XPoint b)
{
	m_dx = abs(b.x - a.x);
	m_dy = -abs(b.y - a.y);
	m_e = m_dx + m_dy;
	m_xi = (b.x > a.x) ? 1 : -1;
	m_yi = (b.y > a.y) ? 1 : -1;
	m_a = b.IsValid() ? a : X_InvalidPoint;
	m_b = b;
	m_l = X_InvalidPoint;
}

bool XLineRenderer::Next()
{
	if (m_l.IsValid())
	{
		// b reached
		if (m_b == m_l)
		{
			m_l = m_a = X_InvalidPoint;
			return false;
		}
		// next point
		int16_t e2 = 2 * m_e;
		if (e2 >= m_dy)
		{
			m_l.x += m_xi;
			m_e += m_dy;
		}
		if (e2 <= m_dx)
		{
			m_l.y += m_yi;
			m_e += m_dx;
		}
	}
	else
		m_l = m_a;
	return m_l.IsValid();
}
