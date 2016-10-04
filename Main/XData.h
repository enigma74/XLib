/*******************************************************************************
 * XData.h
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

#ifndef XData_h
#define XData_h

/// Binary data
class XData
{
public:
	/// Constructor
	/// @param pdata Data pointer
	/// @param size Data size
	XData(const void* pdata, size_t size);
	// Destructor
	virtual ~XData() { }
	
	/// Returns data size
	inline size_t Size() const
	{
		return m_size;
	}
	
	/// Gets the byte at the specified position
	/// @param index Index
	uint8_t Byte(uint32_t index) const;
	/// Gets the word at the specified position
	/// @param index Index
	uint16_t Word(uint32_t index) const;
	/// Gets the dword at the specified position
	/// @param index Index
	uint32_t DWord(uint32_t index) const;
	/// Gets the float at the specified position
	/// @param index Index
	float Float(uint32_t index) const;
	
	/// Gets the byte at the specified position
	inline uint8_t operator[](uint32_t index) const
	{
		return Byte(index);
	}
	
protected:
	/// Gets the byte at the specified address
	/// @param address Byte address
	virtual uint8_t GetByte(const void* address) const;
	/// Gets the word at the specified address
	/// @param address Word address
	virtual uint16_t GetWord(const void* address) const;
	/// Gets the dword at the specified address
	/// @param address DWord address
	virtual uint32_t GetDWord(const void* address) const;
	/// Gets the float at the specified address
	/// @param address Float address
	virtual float GetFloat(const void* address) const;
	
private:
	/// Data pointer
	const void* m_pdata;
	/// Data size
	size_t m_size;
	
	/// Returns the address of the specified index for the specified data size
	/// @param index Index
	/// @param size Data size
	const void* Address(uint32_t index, size_t size) const;

	// Delete copy constructor and assignment operator
	XData(const XData&) = delete;
	XData& operator=(const XData&) = delete;
};

#endif
