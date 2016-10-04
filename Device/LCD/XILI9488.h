/*******************************************************************************
 * XILI9488.h
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
