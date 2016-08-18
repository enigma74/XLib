/*******************************************************************************
 * XArcRenderer.h
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

#ifndef XArcRenderer_h
#define XArcRenderer_h

#include "XRenderer.h"

/// Bresenham circle/ellipse arc coordinates helper for a quadrant
class XArcRenderer : public XRenderer
{
public:
	/// Constructor
	/// @param rx X radius
	/// @param ry Y radius
	XArcRenderer(uint16_t rx, uint16_t ry);
	/// Constructor
	/// @param r Radius
	XArcRenderer(uint16_t r = 0);
	
	/// Inits the helper for an ellipse with new radiuses
	/// @param rx X radius
	/// @param ry Y radius
	void Init(uint16_t rx, uint16_t ry);
	/// Inits the helper for a circle with new radius
	/// @param r Radius
	inline void Init(uint16_t r);
	
	/// Calculates next quadrant point
	virtual bool Next() override;
	
private:
	/// X change increment
	int32_t m_dxi;
	/// Y change increment
	int32_t m_dyi;
	/// X change
	int32_t m_dx;
	/// Y change
	int32_t m_dy;
	/// Radius error
	int32_t m_e;
	/// First point
	XPoint m_a;

	// Delete copy constructor and assignment operator
	XArcRenderer(const XArcRenderer&) = delete;
	XArcRenderer& operator=(const XArcRenderer&) = delete;
};

#endif
