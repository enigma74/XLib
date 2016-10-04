/*******************************************************************************
 * XArcRenderer.cpp
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
#include "XArcRenderer.h"

XArcRenderer::XArcRenderer(uint16_t rx, uint16_t ry)
{
	Init(rx, ry);
}

XArcRenderer::XArcRenderer(uint16_t r)
{
	Init(r, r);
}

void XArcRenderer::Init(uint16_t rx, uint16_t ry)
{
	// circle params
	m_dxi = m_dyi = 2;
	m_dx = (int32_t)1 - 2 * rx;
	m_dy = 1;
	// ellipse variation
	if (rx != ry)
	{
		int32_t rx2 = (int32_t)rx * rx;
		int32_t ry2 = (int32_t)ry * ry;
		m_dxi *= ry2;
		m_dyi *= rx2;
		m_dx *= ry2;
		m_dy *= rx2;
	}
	// initial values
	m_e = m_dx + m_dy;
	m_l = X_InvalidPoint;
	m_a = (rx || ry) ? XPoint(rx, 0) : X_InvalidPoint;
}

void XArcRenderer::Init(uint16_t r)
{
	Init(r, r);
}

bool XArcRenderer::Next()
{
	if (m_l.IsValid())
	{
		if (!m_l.x)
		{
			m_l = m_a = X_InvalidPoint;
			return false;
		}
		int32_t e2 = 2 * m_e;
		if (e2 >= m_dx)
		{
			m_l.x--;
			m_e += m_dx += m_dxi;
		}
		if (e2 <= m_dy)
		{
			m_l.y++;
			m_e += m_dy += m_dyi;
		}
	}
	else
		m_l = m_a;
	return m_l.IsValid();
}
