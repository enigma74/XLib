/*******************************************************************************
 * XLCDI.h
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

#ifndef XLCDI_h
#define XLCDI_h

#if defined(__XHW__)

/// LCD interface type
enum class XLCDIType : uint8_t
{
	/// Serial
	Serial,
	/// Parallel 8bit
	Parallel8,
	/// Parallel 16bit
	Parallel16
};

// ********************************************************************************

/// Base LCD interface class
class XLCDI
{
public:
	/// Type
	const XLCDIType Type;
	/// Chip select pin
	XIO CS;
	/// Data/command pin
	XIO DC;
	/// Reset pin
	XIO RST;

	/// Enable device access
	inline void Enable() const
	{
		CS.Low();
	}

	/// Disable device access
	inline void Disable() const
	{
		CS.High();
	}

	/// Initializes the interface
	void Init();

	/// Write a command to the device
	/// @param cmd Command byte
	inline void Command(uint8_t cmd)
	{
		if (Begin(true, true))
			OnWriteByte(cmd, true);
	}

	/// Write data to the device
	/// @param data Data
	inline void WriteByte(uint8_t data)
	{
		if (Begin(true))
			OnWriteByte(data);
	}

	/// Write data to the device
	/// @param data Data
	inline void WriteWord(uint16_t data)
	{
		if (Begin(true))
			OnWriteWord(data);
	}

	/// Write pixel color to the device
	/// @param color Color
	/// @param count Pixel count
	inline void WriteColor(const XColor& color, uint32_t count = 1)
	{
		if (count && Begin(true))
			OnWriteColor(color, count);
	}

protected:
	/// Target frequency
	uint32_t m_freq;

	/// Constructor
	/// @param type Type
	/// @param freq Target frequency
	XLCDI(XLCDIType type, uint32_t freq = 0);
	/// Destructor
	virtual ~XLCDI() { }

	/// Initializes the interface
	virtual void OnInit() { }

	/// Begins a read/write operation
	/// @param write Write flag
	virtual void OnBegin(bool write) { }
	/// Begins a read/write operation
	/// @param write Write flag
	/// @param cmd Command flag
	bool Begin(bool write, bool cmd = false);

	/// Write data to the device
	/// @param data Data
	/// @param cmd Command flag
	virtual void OnWriteByte(uint8_t data, bool cmd = false) = 0;

	/// Write data to the device
	/// @param data Data
	inline virtual void OnWriteWord(uint16_t data)
	{
		OnWriteByte(XHiByte(data));
		OnWriteByte(XLoByte(data));
	}

	/// Write pixel color to the device
	/// @param color Color
	/// @param count Pixel count
	virtual void OnWriteColor(XColor color, uint32_t count = 1) = 0;

private:
	// Delete copy constructor and assignment operator
	XLCDI(const XLCDI&) = delete;
	XLCDI& operator=(const XLCDI&) = delete;
};

#endif // __XHW__
#endif
