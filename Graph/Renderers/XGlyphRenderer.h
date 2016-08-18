/*******************************************************************************
 * XGlyphRenderer.h
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
