/*******************************************************************************
 * XLCDSerial.h
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

#ifndef XLCDSerial_h
#define XLCDSerial_h

#if defined(__XHW__)

/// Serial LCD interface class
class XLCDSerial : public XLCDI
{
public:
	/// Data pin
	XIO SDA;
	/// Clock pin
	XIO SCL;

	/// Constructor
	/// @param freq Target frequency
	XLCDSerial(uint32_t freq = 0);

protected:
	/// Initializes the interface
	virtual void OnInit() override;

	/// Write data to the device
	/// @param data Data
	/// @param cmd Command flag
	virtual void OnWriteByte(uint8_t data, bool cmd = false) override;
	/// Write pixel color to the device
	/// @param color Color
	/// @param count Pixel count
	virtual void OnWriteColor(XColor color, uint32_t count = 1) override;

private:
	// Delete copy constructor and assignment operator
	XLCDSerial(const XLCDSerial&) = delete;
	XLCDSerial& operator=(const XLCDSerial&) = delete;
};

#endif // __XHW__
#endif
