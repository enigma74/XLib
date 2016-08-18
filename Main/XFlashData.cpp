/*******************************************************************************
 * XFlashData.cpp
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

#include "XMain.h"
#include "XFlashData.h"

XFlashData::XFlashData(const void* pdata, size_t size)
	: XData(pdata, size)
{
}

uint8_t XFlashData::GetByte(const void* address) const
{
#if defined(__AVR__)
	return pgm_read_byte(address);
#else
	return XData::GetByte(address);
#endif
}

uint16_t XFlashData::GetWord(const void* address) const
{
#if defined(__AVR__)
	return pgm_read_word(address);
#else
	return XData::GetWord(address);
#endif
}

uint32_t XFlashData::GetDWord(const void* address) const
{
#if defined(__AVR__)
	return pgm_read_dword(address);
#else
	return XData::GetDWord(address);
#endif
}

float XFlashData::GetFloat(const void* address) const
{
#if defined(__AVR__)
	return pgm_read_float(address);
#else
	return XData::GetFloat(address);
#endif
}
