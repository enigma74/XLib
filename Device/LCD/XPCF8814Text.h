/*******************************************************************************
 * XPCF8814Text.h
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

/*******************************************************************************
 * Nokia 1100 LCD, PCF8814 (96x65, 8 rows)
 * -
 *  |- 9: Unused
 *  |- 8: LED+ (3v3)
 *  |- 7: VDD (3v3)
 *  |- 6: VDDI (3v3)
 *  |- 5: SCLK
 *  |- 4: SDA
 *  |- 3: GND
 *  |- 2: XCS
 *  |- 1: XRES
 * -
 *******************************************************************************/

#ifndef XPCF8814Text_h
#define XPCF8814Text_h

#if defined(__XHW__)

/// Nokia 1100 LCD (Text only)
class XPCF8814Text : public XLCD
{
public:
	/// Display rect (y are rows)
	const XRect Rect;

	/// Constructor
	/// @param i Interface
	XPCF8814Text(XLCDSerial& i);

	/// Draws a text
	/// @param rect Display rectangle (y is the row)
	/// @param text Text data
	/// @param invert Invert flag
	void Text(XRect rect, const XText& text, bool invert = false);

private:
	/// Initializes the LCD
	virtual void OnInit() override;
	/// Turns on the LCD
	virtual void OnOn() override;
	/// Turns off the LCD
	virtual void OnOff() override;
	/// Inverts the LCD
	virtual void OnInvert() override;
	/// Changes contrast
	virtual void OnContrast() override;
	/// Go to specified row and column
	/// @param p Display location (y is the row)
	void OnLocation(XPoint p);
	/// Clears the LCD
	virtual void OnClear() override;

	// Delete copy constructor and assignment operator
	XPCF8814Text(const XPCF8814Text&) = delete;
	XPCF8814Text& operator=(const XPCF8814Text&) = delete;
};

#endif // __XHW__
#endif
