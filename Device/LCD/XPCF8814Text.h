/*******************************************************************************
 * XPCF8814Text.h
 *
 * Copyright (c) Moreno Seri (moreno.seri@gmail.com)
 *
 * This file is part of XLib.
 *
 * XLib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
