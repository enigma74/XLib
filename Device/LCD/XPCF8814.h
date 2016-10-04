/*******************************************************************************
 * XPCF8814.h
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
