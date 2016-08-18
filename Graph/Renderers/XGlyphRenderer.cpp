/*******************************************************************************
 * XGlyphRenderer.cpp
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
#include "XGlyphRenderer.h"

XGlyphRenderer::XGlyphRenderer()
{
	GlyphInit(NULL);
}

XSize XGlyphRenderer::GlyphInit(const XData* pdata, uint32_t index)
{
	m_count = 0;
	m_bits = 0;
	m_p = X_InvalidPoint;
	m_alpha = 0;
	if (pdata)
	{
		const XData& data = *pdata;
		XSize size(data[index], data[index + 1]);
		if (!size.IsEmpty())
		{
			m_pdata = pdata;
			m_bpp = (data[0] & 0x03) + 1;
			m_index = index + 2;
			m_shift = 16 - m_bpp;
			m_max = (1 << m_bpp) - 1;
			m_b = size - XPoint(1, 1);
			return size;
		}
	}
	m_pdata = NULL;
	m_bpp = 0;
	m_index = 0;
	m_shift = 0;
	m_max = 0;
	m_b = XPoint();
	return XSize();
}

XPoint XGlyphRenderer::GlyphNext()
{
	if (!m_pdata)
		return X_InvalidPoint;
	// next position
	if (m_p.IsValid())
	{
		if (m_p.x == m_b.x)
		{
			if (m_p.y == m_b.y)
			{
				m_pdata = NULL;
				return X_InvalidPoint;
			}
			m_p.x = 0;
			m_p.y++;
		}
		else
			m_p.x++;
	}
	else
		m_p = XPoint();
	// needs more bits
	if (m_count < m_bpp)
	{
		m_bits |= (*m_pdata)[m_index] << (8 - m_count);
		m_index++;
		m_count += 8;
	}
	// alpha mask
	m_alpha = (m_bits >> m_shift) & m_max;
	if (m_alpha)
		m_alpha = m_alpha * 0xFF / m_max;
	m_bits <<= m_bpp;
	m_count -= m_bpp;
	return m_p;
}
