/*******************************************************************************
 * XLineRenderer.h
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

#ifndef XLineRenderer_h
#define XLineRenderer_h

#include "XRenderer.h"

/// Bresenham line coordinates helper
class XLineRenderer : public XRenderer
{
public:
	/// Constructor
	/// @param a First location
	/// @param b Second location
	XLineRenderer(XPoint a = XPoint(), XPoint b = XPoint());
	
	/// Inits the helper with new locations
	/// @param a First location
	/// @param b Second location
	void Init(XPoint a, XPoint b);

	/// Calculates next quadrant point
	virtual bool Next() override;
	
private:
	/// X change
	int16_t m_dx;
	/// Y change
	int16_t m_dy;
	/// Slope error
	int16_t m_e;
	/// X increment
	int16_t m_xi;
	/// Y increment
	int16_t m_yi;
	/// First location
	XPoint m_a;
	/// Second location
	XPoint m_b;

	// Delete copy constructor and assignment operator
	XLineRenderer(const XLineRenderer&) = delete;
	XLineRenderer& operator=(const XLineRenderer&) = delete;
};

#endif
