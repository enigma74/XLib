/*******************************************************************************
 * XILI9488.h
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

#ifndef XILI9488_h
#define XILI9488_h

#if defined(__XHW__)

/// ILI9488 LCD
class XILI9488 : public XGLCD
{
public:
	/// Constructor
	/// @param i Interface
	XILI9488(XLCDI& i);

private:
	/// Color mode
	XColorMode m_mode;

	/// Initializes the LCD
	virtual void OnInit() override;
	/// Turns on the LCD
	virtual void OnOn() override;
	/// Turns off the LCD
	virtual void OnOff() override;
	/// Rotates the LCD
	virtual bool OnRotate() override;
	/// Inverts the LCD
	virtual void OnInvert() override;

	/// Sets an LCD area access
	/// @param a First rect point
	/// @param b Second rect point
	void SetRect(const XPoint& a, const XPoint& b);
	/// Fills a rectangle
	/// @param rect Display rectangle
	/// @param color Color to use
	virtual void OnFill(const XRect& rect, const XColor& color) override;
//	/// Reads a pixel color
//	/// @param p Display location
//	virtual XColor OnReadPixel(const XPoint& p, const XColor& color) override;

	// Delete copy constructor and assignment operator
	XILI9488(const XILI9488&) = delete;
	XILI9488& operator=(const XILI9488&) = delete;
};

#endif // __XHW__
#endif
