/*******************************************************************************
 * XFlashData.cpp
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
