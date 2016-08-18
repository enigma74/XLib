/*******************************************************************************
 * XLCDSerial.h
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
