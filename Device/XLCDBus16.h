/*******************************************************************************
 * XLCDBus16.h
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

#ifndef XLCDBus16_h
#define XLCDBus16_h

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

/// 16bit parallel LCD interface class
class XLCDBus16 : public XLCDBus
{
public:
	/// Constructor
	/// @param freq Target frequency
	XLCDBus16(uint32_t freq = 0);

protected:
	/// Initializes the interface
	virtual void OnInit() override;
	/// Write bus data
	/// @param data Bus data
	virtual void OnWriteBus(uint16_t data);

	/// Write bus data
	/// @param data Bus data
	/// @param count Count
	inline void WriteBus(uint16_t data, uint32_t count = 1)
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

	/// Write data to the device
	/// @param data Data
	inline virtual void OnWriteWord(uint16_t data) override
	{
		WriteBus(data);
	}

	/// Write pixel color to the device
	/// @param color Color
	/// @param count Pixel count
	virtual void OnWriteColor(XColor color, uint32_t count = 1) override;

private:
	// Delete copy constructor and assignment operator
	XLCDBus16(const XLCDBus16&) = delete;
	XLCDBus16& operator=(const XLCDBus16&) = delete;
};

#endif // __XHW__
#endif
