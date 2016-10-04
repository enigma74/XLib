/*******************************************************************************
 * XTextRenderer.h
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

#ifndef XTextRenderer_h
#define XTextRenderer_h

#include "XGlyphRenderer.h"

/// Row informations
struct _XRI
{
	/// Break position
	int BP;
	/// X position
	int16_t x;
};

// ********************************************************************************

/// One line text helper
class XTextRenderer : public XGlyphRenderer
{
public:
	/// Constructor
	/// @param rect Rectangle
	/// @param ptext Text pointer
	/// @param integralHeight Fixed line height rendering
	XTextRenderer(const XRect& rect = XRect(), const XText* ptext = NULL, int16_t integralHeight = 0);

	/// Inits the helper with new bounds
	/// @param rect Rectangle
	/// @param ptext Text pointer
	/// @param integralHeight Fixed line height rendering
	void Init(const XRect& rect, const XText* ptext, int16_t integralHeight = 0);

	/// Returns text size
	inline XSize Size() const
	{
		return m_size;
	}
	
	/// Calculates next text point
	virtual bool Next() override;
	
	/// Returns current char index
	inline int Index() const
	{
		return m_index - 1;
	}

	/// Returns current row
	inline int Row() const
	{
		return m_row;
	}

private:
	/// Fixed line height rendering flag
	bool m_integral;
	/// Text rect
	XRect m_rect;
	/// Text pointer
	const XText* m_ptext;
	/// Font pointer
	const XData* m_pfont;
	/// Max width
	int16_t m_maxwidth;
	/// Tracking
	int16_t m_tracking;
	/// Leading
	int16_t m_leading;
	/// Space width
	int16_t m_space;
	/// Start char ascii
	uint8_t m_startascii;
	/// End char ascii
	uint8_t m_endascii;
	/// Icons data offset
	uint32_t m_offset;
	
	/// Text size
	XSize m_size;
	/// Rows infotmations
	XArray<_XRI> m_rows;
	/// Multiple rows
	bool m_multirow;
	/// Current row
	int m_row;
	
	/// Next char index
	int m_index;
	/// Current char
	char m_ch;
	/// Current char cell location
	XPoint m_cl;
	/// Current char width
	uint16_t m_width;
	/// Current glyph position
	XPoint m_gl;

	/// Begins the calculation
	void Begin();
	/// Calculates next char glyph info
	bool NextChar();

	// Delete copy constructor and assignment operator
	XTextRenderer(const XTextRenderer&) = delete;
	XTextRenderer& operator=(const XTextRenderer&) = delete;
};

#endif
