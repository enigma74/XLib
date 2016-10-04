/*******************************************************************************
 * XGlyphRenderer.cpp
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
