/*******************************************************************************
 * XUnoShield.h
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

#ifndef XUnoShield_h
#define XUnoShield_h

/*******************************************************************************
 * Supported hardware:
 * __AVR_ATmega1280__	Arduino Mega ATmega1280
 * __AVR_ATmega2560__	Arduino Mega ATmega2560
 *******************************************************************************/

#if defined(__XHW__)\
	&& (defined(__AVR_ATmega1280__)\
	|| defined(__AVR_ATmega2560__))

#define __XUnoShield__

/// Arduino Uno/2009 shield on Arduino Mega (8bit parallel LCD interface)
class XUnoShield : public XLCDBus8
{
public:
	/// Constructor
	/// @param freq Target frequency
	XUnoShield(uint32_t freq = 0);

protected:
	/// Initializes the interface
	virtual void OnInit() override;
	/// Write bus data
	/// @param data Bus data
	virtual void OnWriteBus(uint8_t data);

private:
	// Delete copy constructor and assignment operator
	XUnoShield(const XUnoShield&) = delete;
	XUnoShield& operator=(const XUnoShield&) = delete;
};

#endif // __XHW__
#endif
