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

#include "XGraph.h"
#include "XText.h"

const XData* XText::DefaultFont = NULL;

XText::XText(PCSTR pstr)
{
	Alignment = X_TopLeft;
	Wrap = false;
	Fixed = false;
	Leading = 0;
	Tracking = 0;
	Font = DefaultFont;
	Value = pstr;
}

XText::XText(const XText& text)
{
	Alignment = text.Alignment;
	Wrap = text.Wrap;
	Fixed = text.Fixed;
	Leading = text.Leading;
	Tracking = text.Tracking;
	Font = text.Font;
	Value = text.Value;
}

XString& XText::operator=(PCSTR pstr)
{
	return (Value = pstr);
}

XText& XText::operator=(const XText& text)
{
	Value = text.Value;
	return *this;
}
