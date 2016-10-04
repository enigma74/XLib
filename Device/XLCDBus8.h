/*******************************************************************************
 * XLCDBus8.h
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

#ifndef XLCDBus8_h
#define XLCDBus8_h

/*******************************************************************************
 * Supported hardware:
 * __AVR_ATmega328P__	Arduino Uno ATmega328P
 * __AVR_ATmega32U4__	Arduino Leonardo ATmega32U4
 * __AVR_ATmega1284P__	Arduino custom ATmega1284P
 * __AVR_ATmega1280__	Arduino Mega ATmega1280
 * __AVR_ATmega2560__	Arduino Mega ATmega2560
 * __SAM3X8E__				Arduino Due AT91SAM3X8E
 * __32MX320F128H__		chipKIT UNO32 PIC32MX320F128H
 * __32MX340F512H__		chipKIT uC32 PIC32MX340F512H
 * __32MX795F512L__		chipKIT MAX32 PIC32MX795F512L
 * __MK20DX128__			Teensy 3.x MK20DX128VLH7
 * __MK20DX256__			Teensy 3.x MK20DX256VLH7
 * __CC3200R1M1RGC__		TI CC3200 LaunchPad
 *******************************************************************************/

#if defined(__XHW__)

/// 8bit parallel LCD interface class
class XLCDBus8 : public XLCDBus
{
public:
	/// Constructor
	/// @param freq Target frequency
	XLCDBus8(uint32_t freq = 0);

protected:
	/// Initializes the interface
	virtual void OnInit() override;
	/// Write bus data
	/// @param data Bus data
	virtual void OnWriteBus(uint8_t data);

	/// Write bus data
	/// @param data Bus data
	/// @param count Count
	inline void WriteBus(uint8_t data, uint32_t count = 1)
	{
		OnWriteBus(data);
		PulseWrite(count);
	}

	/// Write data to the device
	/// @param data Data
	/// @param cmd Command flag
	inline virtual void OnWriteByte(uint8_t data, bool cmd = false) override
	{
		WriteBus(data);
	}

	/// Write pixel color to the device
	/// @param color Color
	/// @param count Pixel count
	virtual void OnWriteColor(XColor color, uint32_t count = 1) override;

private:
	// Delete copy constructor and assignment operator
	XLCDBus8(const XLCDBus8&) = delete;
	XLCDBus8& operator=(const XLCDBus8&) = delete;
};

#endif // __XHW__
#endif
