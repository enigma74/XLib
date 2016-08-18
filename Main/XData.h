/*******************************************************************************
 * XData.h
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
