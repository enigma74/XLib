/*******************************************************************************
 * XText.h
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

#ifndef XText_h
#define XText_h

/// Text class
class XText : public XString
{
public:
	/// Default font pointer
	static const XData* DefaultFont;

	/// Horizontal and vertical alignment
	uint8_t Alignment;
	/// Wrap
	bool Wrap;
	/// Fixed size
	bool Fixed;
	/// Line leading
	int8_t Leading;
	/// Letter tracking
	int8_t Tracking;
	/// Font pointer
	const XData* Font;
	
	/// Constructor
	/// @param pstr Source string pointer
	XText(PCSTR pstr = NULL);
	/// Constructor
	/// @param text Source text
	XText(const XText& text);
	
	/// Assigns a string to this instance
	inline XText& operator=(PCSTR pstr)
	{
		return (XText&)From(pstr);
	}
};

#endif
