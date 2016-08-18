/*******************************************************************************
 * XArcRenderer.cpp
 *
 * Copyright (c) Moreno Seri (moreno.seri@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
