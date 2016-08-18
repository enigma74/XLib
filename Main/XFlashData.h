/*******************************************************************************
 * XFlashData.h
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

#ifndef XFlashData_h
#define XFlashData_h

#if defined(__AVR__)
	#include <avr/pgmspace.h>
#else
	#define PROGMEM
#endif

/// Flash binary data
class XFlashData : public XData
{
public:
	/// Constructor
	/// @param pdata Flash data pointer
	/// @param size Data size
	XFlashData(const void* pdata, size_t size);

protected:
	/// Gets the byte at the specified address
	/// @param address Byte address
	virtual uint8_t GetByte(const void* address) const override;
	/// Gets the word at the specified address
	/// @param address Word address
	virtual uint16_t GetWord(const void* address) const override;
	/// Gets the dword at the specified address
	/// @param address SWord address
	virtual uint32_t GetDWord(const void* address) const override;
	/// Gets the float at the specified address
	/// @param address Float address
	virtual float GetFloat(const void* address) const override;

private:
	// Delete copy constructor and assignment operator
	XFlashData(const XFlashData&) = delete;
	XFlashData& operator=(const XFlashData&) = delete;
};

#endif
