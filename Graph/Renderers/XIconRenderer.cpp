/*******************************************************************************
 * XIconRenderer.cpp
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
