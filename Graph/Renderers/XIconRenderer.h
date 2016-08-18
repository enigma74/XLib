/*******************************************************************************
 * XIconRenderer.h
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

#ifndef XIconRenderer_h
#define XIconRenderer_h

#include "XGlyphRenderer.h"

/// Icon points renderer
class XIconRenderer : public XGlyphRenderer
{
public:
	/// Constructor
	/// @param rect Rectangle
	/// @param picon Icon data pointer
	XIconRenderer(const XRect& rect = XRect(), const XData* picon = NULL);

	/// Inits the renderer with new data
	/// @param rect Rectangle
	/// @param picon Icon data pointer
	void Init(const XRect& rect, const XData* picon);

	/// Returns icon size
	inline XSize Size() const
	{
		return m_size;
	}

	/// Calculates next icon point
	virtual bool Next() override;

private:
	/// Icon rect
	XRect m_rect;
	/// Icon size
	XSize m_size;
	/// Starting location
	XPoint m_a;

private:
	// Delete copy constructor and assignment operator
	XIconRenderer(const XIconRenderer&) = delete;
	XIconRenderer& operator=(const XIconRenderer&) = delete;
};

#endif
