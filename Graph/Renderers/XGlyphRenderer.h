/*******************************************************************************
 * XGlyphRenderer.h
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

#ifndef XGlyphRenderer_h
#define XGlyphRenderer_h

#include "XRenderer.h"

/// Glyph points renderer
class XGlyphRenderer : public XRenderer
{
public:
	/// Returns point alpha channel
	inline uint8_t Alpha() const
	{
		return m_alpha;
	}

protected:
	/// Constructor
	XGlyphRenderer();

	/// Inits the renderer with new data
	/// @param pdata Data pointer
	/// @param index Glyph data index
	XSize GlyphInit(const XData* pdata, uint32_t index = 1);

	/// Calculates next glyph point
	XPoint GlyphNext();

private:
	/// Data pointer
	const XData* m_pdata;
	/// Bits per pixel
	uint8_t m_bpp;
	/// Current data index
	uint32_t m_index;
	/// Bits count
	int16_t m_count;
	/// Bits
	uint16_t m_bits;
	/// Bits shift
	uint8_t m_shift;
	/// Maximum alpha value
	uint8_t m_max;
	/// Ending point
	XPoint m_b;
	/// Current point
	XPoint m_p;
	/// Point alpha channel
	uint8_t m_alpha;
};

#endif
