/*******************************************************************************
 * XAquaLED.h
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

#ifndef XAquaLED_h
#define XAquaLED_h

/*******************************************************************************
 * Supported hardware:
 * __32MX795F512L__		chipKIT MAX32 PIC32MX795F512L
 *******************************************************************************/

#if defined(__XHW__) && defined(__32MX795F512L__)

#define __XAquaLED__

/// AquaLEDSource All in One Super Screw Shield for chipKit Max32 (16bit parallel LCD interface)
class XAquaLED : public XLCDBus16
{
public:
	/// Constructor
	/// @param freq Target frequency
	XAquaLED(uint32_t freq = 0);

protected:
	/// Initializes the interface
	virtual void OnInit() override;
	/// Write bus data
	/// @param data Bus data
	virtual void OnWriteBus(uint16_t data);

private:
	// Delete copy constructor and assignment operator
	XAquaLED(const XAquaLED&) = delete;
	XAquaLED& operator=(const XAquaLED&) = delete;
};

#endif // __XHW__
#endif
