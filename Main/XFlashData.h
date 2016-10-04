/*******************************************************************************
 * XFlashData.h
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
