/*******************************************************************************
 * XTextRenderer.cpp
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
#include "XTextRenderer.h"

XTextRenderer::XTextRenderer(const XRect& rect, const XText* ptext, int16_t integralHeight)
{
	Init(rect, ptext, integralHeight);
}

void XTextRenderer::Begin()
{
	m_row = 0;
	m_index = 0;
	m_cl = XPoint();
	m_width = 0;
}

bool XTextRenderer::NextChar()
{
	if (!m_pfont)
		return false;
	const XText& text = *m_ptext;
	// check for available char
	if (m_index >= text.Lenght())
		return false;
	// increment x position by previous width
	if (m_width)
		m_cl.x += m_width + m_tracking;
	// next char
	m_ch = text[m_index];
	m_index++;
	m_width = 0;
	m_gl = X_InvalidPoint;
	// check new row
	if (m_multirow && (m_index > m_rows[m_row].BP))
	{
		m_row++;
		m_cl.x = m_rows[m_row].x;
		m_cl.y += m_leading;
	}
	// space
	if (m_ch == ' ')
	{
		m_width = text.Fixed ? m_maxwidth : m_space;
		return true;
	}
	// check for font available char
	uint8_t ascii = m_ch;
	if ((ascii < m_startascii) || (ascii > m_endascii))
		return true;
	// check for available glyph data
	const XData& font = *m_pfont;
	uint32_t index = font.Word(6 + ((ascii - m_startascii) << 1));
	if ((index == 0) && (ascii > m_startascii))
		return true;
	// sets glyph info
	index += m_offset;
	GlyphInit(m_pfont, index + 3);
	m_width = font[index];
	m_gl = m_cl + XPoint(font[index + 1], font[index + 2]);
	if (text.Fixed)
	{
		m_gl.x += (m_maxwidth - m_width) >> 1;
		m_width = m_maxwidth;
	}
	return true;
}

void XTextRenderer::Init(const XRect& rect, const XText* ptext, int16_t integralHeight)
{
	m_integral = integralHeight > 0;
	m_rect = rect;
	if (m_integral)
		m_rect.Size.Height -= m_rect.Size.Height % integralHeight;
	m_ptext = ptext;
	m_pfont = ptext ? ptext->Font : NULL;
	m_size = XSize();
	Begin();
	if (!m_ptext)
		return;
	if (!m_pfont)
		m_pfont = XText::DefaultFont;
	if (!m_pfont)
		return;
	// font metrics
	const XText& text = *m_ptext;
	const XData& font = *m_pfont;
	m_maxwidth = font[1];
	m_tracking = text.Tracking;
	uint16_t height = m_leading = m_integral ? integralHeight : font[2];
	if (!m_integral)
		m_leading += text.Leading + 1;
	m_space = font[3];
	m_startascii = font[4];
	m_endascii = font[5];
	m_offset = 6 + ((m_endascii - m_startascii + 1) << 1);
	// analyzing text metrics
	uint8_t alignment = text.Alignment;
	XPoint ls = m_rect.Location;
	XPoint lc = m_rect.Center();
	XPoint le = m_rect.Ending();
	int16_t ox = (X_GetFlag(alignment, X_Left) ? ls.x
		: (X_GetFlag(alignment, X_Right) ? le.x
		: lc.x));
	m_rows.Clear();
	m_multirow = false;
	int bp = -1;
	int16_t bpw = 0;
	int16_t bpw2 = 0;
	uint16_t width = 0;
	// add a new row info
	auto _AddRow = [this, alignment, ox](int _bp, uint16_t _width)
	{
		int16_t x = ox - (X_GetFlag(alignment, X_Left) ? 0
			: (X_GetFlag(alignment, X_Right) ? _width
			: (_width >> 1) - 1));
		m_rows.Add({ _bp, x });
		if (_width > m_size.Width)
			m_size.Width = _width;
	};
	while (NextChar())
	{
		// taking increment
		uint16_t w = m_cl.x + m_width;
		// checks for new line or wrap
		bool nl = (m_ch == '\n');
		if (nl || (text.Wrap && (w > m_rect.Size.Width)))
		{
			// fix missing break position
			if (nl || (bp < 0))
			{
				bp = m_index;
				bpw2 = bpw = width;
				if (!nl)
				{
					bp--;
					bpw2 += m_tracking;
				}
			}
			// adding row info
			_AddRow(bp, bpw);
			bp = -1;
			// fixing new row position and width
			m_cl.x -= bpw2;
			w -= bpw2;
			m_cl.y += m_leading;
		}
		// taking space as a valid break position
		if (m_ch == ' ')
		{
			bp = m_index;
			bpw = width;
			bpw2 = w + m_tracking;
		}
		// saving new width
		width = w;
	}
	// adding last row info
	if (width > 0)
		_AddRow(m_index, width);
	int rows = m_rows.Count();
	m_multirow = rows > 1;
	m_size.Height = m_cl.y + height;
	// initialization
	Begin();
	m_cl.x = m_rows[m_row].x;
	uint16_t th = m_size.Height;
	if (X_GetFlag(alignment, X_Top))
		m_cl.y = ls.y;
	else if(X_GetFlag(alignment, X_Bottom))
		m_cl.y = le.y - th + 1;
	else if (m_integral)
	{
		int max = m_rect.Size.Height / m_leading;
		m_cl.y = ls.y + ((max - rows) >> 1) * m_leading;
	}
	else
		m_cl.y = lc.y - (th >> 1) + 1;
	m_l = m_gl = X_InvalidPoint;
}

bool XTextRenderer::Next()
{
	if (!m_pfont)
		return false;
	while (true)
	{
		if (m_gl.IsValid())
		{
			XPoint l = GlyphNext();
			if (l.IsValid())
			{
				if (m_integral && (l.y >= m_leading))
					continue;
				m_l = m_gl + l;
				if (m_rect.Contains(m_l))
					return true;
				continue;
			}
		}
		do
		{
			if (!NextChar())
			{
				m_pfont = NULL;
				m_l = X_InvalidPoint;
				return false;
			}
		} while (!m_gl.IsValid());
	}
}
