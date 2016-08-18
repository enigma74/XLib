/*******************************************************************************
 * XLineRenderer.cpp
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
