/*******************************************************************************
 * XData.cpp
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
