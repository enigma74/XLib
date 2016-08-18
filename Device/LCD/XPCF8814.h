/*******************************************************************************
 * XPCF8814.h
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

#ifndef XPCF8814_h
#define XPCF8814_h

#if defined(__XHW__)

/// Nokia 1100 LCD
class XPCF8814 : public XGLCD
{
public:
	/// Constructor
	/// @param i Interface
	XPCF8814(XLCDSerial& i);

private:
	/// Buffer (873 bytes)
	uint8_t m_buff[97][9];

	/// Initializes the LCD
	virtual void OnInit() override;
	/// Turns on the LCD
	virtual void OnOn() override;
	/// Turns off the LCD
	virtual void OnOff() override;
//	/// Rotates the LCD
//	virtual bool OnRotate() override;
	/// Inverts the LCD
	virtual void OnInvert() override;
	/// Changes contrast
	virtual void OnContrast() override;

	/// Go to specified row and column
	/// @param l Display location (y is the row)
	void OnLocation(XPoint l);

	/// Clears the LCD
	virtual void OnClear() override;

	/// Begins a drawing function
	virtual void OnBeginFunction() override;
	/// Ends a drawing function
	virtual void OnEndFunction() override;
	/// Ends a drawing sequence
	virtual void OnEndSequence() override;

	/// Fills a rectangle
	/// @param rect Display rectangle
	/// @param color Color to use
	virtual void OnFill(const XRect& rect, const XColor& color) override;

	// Delete copy constructor and assignment operator
	XPCF8814(const XPCF8814&) = delete;
	XPCF8814& operator=(const XPCF8814&) = delete;
};

#endif // __XHW__
#endif
