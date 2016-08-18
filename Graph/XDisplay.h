/*******************************************************************************
 * XDisplay.h
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

#ifndef XDisplay_h
#define XDisplay_h

/// Base display class
class XDisplay : public XContext
{
	// Friends symbols
	friend XContext;

protected:
	/// Constructor
	/// @param size Display context size
	XDisplay(const XSize& size);

	/// Begins a drawing sequence
	inline virtual void OnBeginSequence() { }
	/// Ends a drawing sequence
	inline virtual void OnEndSequence() { }
	/// Begins a drawing sequence
	void OnBegin();
	/// Ends a drawing sequence
	void OnEnd();

	/// Begins a drawing function
	inline virtual void OnBeginFunction()
	{
		Begin();
	}

	/// Ends a drawing function
	inline virtual void OnEndFunction()
	{
		End();
	}
	
	/// Fills a rectangle
	/// @param rect Display rectangle
	/// @param color Color to use
	virtual void OnFill(const XRect& rect, const XColor& color) = 0;
	/// Reads a pixel color
	/// @param p Display location
	inline virtual XColor OnReadPixel(const XPoint& p, const XColor& color)
	{
		return X_NoColor;
	}
	
private:
	/// Drawing counter
	uint16_t m_count;

	// Delete copy constructor and assignment operator
	XDisplay(const XDisplay&) = delete;
	XDisplay& operator=(const XDisplay&) = delete;
};

#endif
