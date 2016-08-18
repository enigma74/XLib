/*******************************************************************************
 * XData.cpp
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
#include "XData.h"

XData::XData(const void* pdata, size_t size)
{
	m_pdata = pdata;
	m_size = size;
}

const void* XData::Address(uint32_t index, size_t size) const
{
	return (index <= (m_size - size)) ? (((uint8_t*)m_pdata) + index) : NULL;
}

uint8_t XData::GetByte(const void* address) const
{
	return *(const uint8_t*)address;
}

uint8_t XData::Byte(uint32_t index) const
{
	const void* address = Address(index, 1);
	return address ? GetByte(address) : 0;
}

uint16_t XData::GetWord(const void* address) const
{
	return *(const uint16_t*)address;
}

uint16_t XData::Word(uint32_t index) const
{
	const void* address = Address(index, 2);
	return address ? GetWord(address) : 0;
}

uint32_t XData::GetDWord(const void* address) const
{
	return *(const uint32_t*)address;
}

uint32_t XData::DWord(uint32_t index) const
{
	const void* address = Address(index, 2);
	return address ? GetDWord(address) : 0;
}

float XData::GetFloat(const void* address) const
{
	return *(const float*)address;
}

float XData::Float(uint32_t index) const
{
	const void* address = Address(index, 2);
	return address ? GetFloat(address) : 0.0;
}
