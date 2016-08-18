/*******************************************************************************
 * XContext.h
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

#ifndef XContext_h
#define XContext_h

// Forwarded symbols
class XDisplay;

/// Base context class
class XContext
{
public:
	/// Display
	XDisplay& Display;
	/// Blending background color
	XColor BackColor;
	/// Color
	XColor Color;
	
	/// Constructor
	/// @param display Display
	/// @param bounds Context rect within display
	XContext(XDisplay& display, const XRect& rect);
	/// Destructor
	virtual ~XContext() { }

	/// Context rect within display
	inline XRect Rect() const
	{
		return m_rect;
	}
	
	/// Returns context size
	inline XSize Size() const
	{
		return m_rect.Size;
	}
	
	/// Returns context relative bounds
	inline XRect Bounds() const
	{
		return m_rect.Relative();
	}

	/// Begins a drawing sequence
	void Begin();
	/// Ends a drawing sequence
	void End();

	/// Draws a pixel
	/// @param p Relative location
	void Pixel(XPoint p);
	/// Draws a line
	/// @param a First relative location
	/// @param b Second relative location
	void Line(XPoint a, XPoint b);
	
	/// Draws a rectangle
	/// @param rect Relative rectangle
	/// @param rr Corners radius
	/// @param filled Filled
	void Rectangle(XRect rect, XRectRadius rr = 0, bool filled = false);

	/// Draws a filled rectangle
	/// @param rect Relative rectangle
	/// @param rr Corners radius
	inline void FillRectangle(XRect rect, XRectRadius rr = 0)
	{
		Rectangle(rect, rr, true);
	}
	
	/// Draws a rectangle filling context
	/// @param rr Corners radius
	inline void Rectangle(XRectRadius rr = 0)
	{
		Rectangle(Bounds(), rr);
	}

	/// Draws a filled rectangle filling context
	/// @param rr Corners radius
	inline void FillRectangle(XRectRadius rr = 0)
	{
		Rectangle(Bounds(), rr, true);
	}

	/// Draws an ellipse
	/// @param c Relative center location
	/// @param rx X radius
	/// @param ry Y radius
	/// @param filled Filled
	void Ellipse(XPoint c, uint16_t rx, uint16_t ry, bool filled = false);

	/// Draws a filled ellipse
	/// @param c Relative center location
	/// @param rx X radius
	/// @param ry Y radius
	inline void FillEllipse(XPoint c, uint16_t rx, uint16_t ry)
	{
		Ellipse(c, rx, ry, true);
	}
	
	/// Draws a circle
	/// @param c Relative center location
	/// @param r Radius
	/// @param filled Filled
	inline void Circle(XPoint c, uint16_t r, bool filled = false)
	{
		Ellipse(c, r, r, filled);
	}
	
	/// Draws a filled circle
	/// @param c Relative center location
	/// @param r Radius
	inline void FillCircle(XPoint c, uint16_t r)
	{
		Ellipse(c, r, r, true);
	}
	
	/// Draws a triangle
	/// @param a First relative location
	/// @param b Second relative location
	/// @param c Third relative location
	/// @param filled Filled
	void Triangle(XPoint a, XPoint b, XPoint c, bool filled = false);

	/// Draws a filled triangle
	/// @param a First relative location
	/// @param b Second relative location
	/// @param c Third relative location
	inline void FillTriangle(XPoint a, XPoint b, XPoint c)
	{
		Triangle(a, b, c, true);
	}
	
	/// Returns the size of the specified icon
	/// @param icon Icon data
	static XSize IconSize(const XData& icon);
	/// Draws a icon
	/// @param rect Relative rectangle
	/// @param icon Icon data
	void Icon(XRect rect, const XData& icon);
	
	/// Returns the size of the specified text
	/// @param text Text data
	/// @param size Maximum size
	static XSize TextSize(const XText& text, XSize max = XSize());
	/// Draws a text
	/// @param rect Relative rectangle
	/// @param text Text data
	void Text(XRect rect, const XText& text);

protected:
	/// Context rect within display
	XRect m_rect;

	/// Begins a drawing function
	bool BeginFunction();
	/// Ends a drawing function
	void EndFunction();

	/// Fills a rectangle
	/// @param rect Display rectangle
	/// @param alpha Alpha channel
	void Fill(XRect rect, uint8_t alpha = 0xFF);
	/// Draws a line
	/// @param a First display location
	/// @param b Second display location
	void OnLine(const XPoint& a, const XPoint& b);

private:
	// Delete copy constructor and assignment operator
	XContext(const XContext&) = delete;
	XContext& operator=(const XContext&) = delete;
};

#endif
