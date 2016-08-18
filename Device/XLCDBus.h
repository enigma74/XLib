/*******************************************************************************
 * XLCDBus.h
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

#ifndef XLCDBus_h
#define XLCDBus_h

#if defined(__XHW__)

/// Base parallel LCD interface class
class XLCDBus : public XLCDI
{
public:
	/// Read data pin
	XIO RD;
	/// Write data pin
	XIO WR;

protected:
	/// Constructor
	/// @param type Type
	/// @param freq Target frequency
	XLCDBus(XLCDIType type, uint32_t freq = 0);

	/// Pulse write pin count times
	/// @param count Count
	void PulseWrite(uint32_t count = 1);

	/// Initializes the interface
	virtual void OnInit() override;
	/// Begins a read/write operation
	/// @param write Write flag
	virtual void OnBegin(bool write) override;

private:
	// Delete copy constructor and assignment operator
	XLCDBus(const XLCDBus&) = delete;
	XLCDBus& operator=(const XLCDBus&) = delete;
};

#endif // __XHW__
#endif
