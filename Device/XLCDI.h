/*******************************************************************************
 * XLCDI.h
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
	/// Clock cycles to compensate frequency
	uint32_t m_delay;

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
