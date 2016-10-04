/*******************************************************************************
 * XString.h
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

#ifndef XString_h
#define XString_h

typedef char* PSTR;
typedef const char* PCSTR;

/// Dynamic string management class
class XString
{
public:
	/// Character for decimal separator
	static char DecimalSeparator;
	/// Character for thousands separator
	static char ThousandsSeparator;

	/// Constructor
	/// @param pstr Source string pointer
	XString(PCSTR pstr = NULL);
	/// Constructor
	/// @param str Source string
	XString(const XString& str);
	/// Constructor
	/// @param ch Source character
	/// @param count Number of characters
	XString(char ch, int count = 1);
	/// Constructor
	/// @param value Value to set
	/// @param base Value base (2, 10, 16)
	/// @param length Minimum length filled with zeroes
	XString(int16_t value, int base = 10, int length = 0);
	/// Constructor
	/// @param value Value to set
	/// @param base Value base (2, 10, 16)
	/// @param length Minimum length filled with zeroes
	XString(uint16_t value, int base = 10, int length = 0);
	/// Constructor
	/// @param value Value to set
	/// @param base Value base (2, 10, 16)
	/// @param length Minimum length filled with zeroes
	XString(int32_t value, int base = 10, int length = 0);
	/// Constructor
	/// @param value Value to set
	/// @param base Value base (2, 10, 16)
	/// @param length Minimum length filled with zeroes
	XString(uint32_t value, int base = 10, int length = 0);
	/// Constructor
	/// @param value Value to set
	/// @param base Value base (2, 10, 16)
	/// @param length Minimum length filled with zeroes
	XString(int64_t value, int base = 10, int length = 0);
	/// Constructor
	/// @param value Value to set
	/// @param base Value base (2, 10, 16)
	/// @param length Minimum length filled with zeroes
	XString(uint64_t value, int base = 10, int length = 0);
	/// Constructor
	/// @param value Value to set
	/// @param dec Number of decimals (0~15, -1 auto)
	/// @param length Minimum length filled with zeroes
	XString(float value, int dec = 2, int length = 0);
	/// Constructor
	/// @param value Value to set
	/// @param dec Number of decimals (0~15, -1 auto)
	/// @param length Minimum length filled with zeroes
	XString(double value, int dec = 2, int length = 0);

	/// Destructor
	virtual ~XString();
	
	/// Clears the string
	inline XString& Clear()
	{
		return SetBuffer(NULL, 0);
	}

	/// Assigns a string to this instance
	/// @param pstr Source string pointer
	XString& From(PCSTR pstr);
	/// Assigns a character to this instance
	/// @param ch Source character
	/// @param count Number of characters
	XString& From(char ch, int count = 1);
	/// Assigns a number to this instance
	/// @param value Value to set
	/// @param base Value base (2, 10, 16)
	/// @param length Minimum length filled with zeroes
	XString& From(int16_t value, int base = 10, int length = 0);
	/// Assigns a number to this instance
	/// @param value Value to set
	/// @param base Value base (2, 10, 16)
	/// @param length Minimum length filled with zeroes
	XString& From(uint16_t value, int base = 10, int length = 0);
	/// Assigns a number to this instance
	/// @param value Value to set
	/// @param base Value base (2, 10, 16)
	/// @param length Minimum length filled with zeroes
	XString& From(int32_t value, int base = 10, int length = 0);
	/// Assigns a number to this instance
	/// @param value Value to set
	/// @param base Value base (2, 10, 16)
	/// @param length Minimum length filled with zeroes
	XString& From(uint32_t value, int base = 10, int length = 0);
	/// Assigns a number to this instance
	/// @param value Value to set
	/// @param base Value base (2, 10, 16)
	/// @param length Minimum length filled with zeroes
	XString& From(int64_t value, int base = 10, int length = 0);
	/// Assigns a number to this instance
	/// @param value Value to set
	/// @param base Value base (2, 10, 16)
	/// @param length Minimum length filled with zeroes
	XString& From(uint64_t value, int base = 10, int length = 0);
	/// Assigns a number to this instance
	/// @param value Value to set
	/// @param dec Number of decimals (0~15, -1 auto)
	/// @param length Minimum length filled with zeroes
	XString& From(float value, int dec = 2, int length = 0);
	/// Assigns a number to this instance
	/// @param value Value to set
	/// @param dec Number of decimals (0~15, -1 auto)
	/// @param length Minimum length filled with zeroes
	XString& From(double value, int dec = 2, int length = 0);

	/// Assigns a string to this instance
	inline XString& operator=(PCSTR pstr)
	{
		return From(pstr);
	}

	/// Assigns a string to this instance
	inline XString& operator=(const XString& str)
	{
		return From((PCSTR)str);
	}

	/// Assigns a character to this instance
	inline XString& operator=(char ch)
	{
		return From(ch);
	}
	
	/// Returns string pointer
	inline operator PCSTR() const
	{
		return m_pstr;
	}
	
	/// Returns string length
	inline int Length() const
	{
		return m_length;
	}
	
	/// Checks for empty string
	inline bool IsEmpty() const
	{
		return m_length == 0;
	}
	
	/// Formats the string
	/// @param fmt Format to use
	/// @param ... Params
	XString& Format(PCSTR fmt, ...);
	
	/// Returns the specified character
	/// @param index Position
	char operator[](int index) const;
	/// Access the specified character
	/// @param index Position
	char& operator[](int index);
	
	/// Compares the string to another
	/// @param pstr Second string
	/// @param ignorecase Case insensitive flag
	int CompareTo(PCSTR pstr, bool ignorecase = false) const;
	/// Compares the string to another (case insensitive)
	/// @param pstr Second string
	int CompareToNoCase(PCSTR pstr) const;
	/// Checks for equality with another string
	/// @param pstr Second string
	/// @param ignorecase Case insensitive flag
	bool Equals(PCSTR pstr, bool ignorecase = false) const;
	/// Checks for equality with another string (case insensitive)
	/// @param pstr Second string
	bool EqualsNoCase(PCSTR pstr) const;
	
	/// Comparison == operator
	inline bool operator==(PCSTR pstr) const
	{
		return Equals(pstr);
	}

	/// Comparison != operator
	inline bool operator!=(PCSTR pstr) const
	{
		return !Equals(pstr);
	}

	/// Returns the index of the specified string
	/// @param pstr String to search
	/// @param start Starting position
	/// @param skip Strings to skip
	/// @param ignorecase Case insensitive flag
	int IndexOf(PCSTR pstr, int start = 0, int skip = 0, bool ignorecase = false) const;
	/// Returns the index of the specified string (case insensitive)
	/// @param pstr String to search
	/// @param start Starting position
	/// @param skip Strings to skip
	int IndexOfNoCase(PCSTR pstr, int start = 0, int skip = 0) const;
	/// Returns the index of the specified character
	/// @param ch Character to search
	/// @param start Starting position
	/// @param skip Characters to skip
	/// @param ignorecase Case insensitive flag
	int IndexOf(char ch, int start = 0, int skip = 0, bool ignorecase = false) const;
	/// Returns the index of the specified character (case insensitive)
	/// @param ch Character to search
	/// @param start Starting position
	/// @param skip Characters to skip
	int IndexOfNoCase(char ch, int start = 0, int skip = 0) const;

	/// Insert a string in the specified position
	/// @param index Position
	/// @param pstr String to insert
	XString& InsertAt(int index, PCSTR pstr);
	/// Appends a string
	/// @param pstr String to append
	XString& Append(PCSTR pstr);

	/// Appends a string
	XString& operator+=(PCSTR pstr);
	/// Appends a string
	XString& operator+=(const XString& str);
	/// Appends a character
	XString& operator+=(char ch);

	/// Concatenates two strings
	friend XString operator+(const XString& stra, const XString& strb);
	/// Concatenates two strings
	friend XString operator+(PCSTR pstra, const XString& strb);
	/// Concatenates two strings
	friend XString operator+(const XString& stra, PCSTR pstrb);
	/// Concatenates a character to a string
	friend XString operator+(char ch, const XString& str);
	/// Concatenates a string to a character
	friend XString operator+(const XString& str, char ch);

	/// Removes the specified number of characters at the specified position
	/// @param index Position
	/// @param count Number of characters
	XString& RemoveAt(int index, int count = 1);
	/// Crops the specified number of characters at the specified position
	/// @param index Position
	/// @param count Number of characters
	XString& CropAt(int index, int count = -1);
	/// Returns a substring of the specified number of characters at the specified position
	/// @param index Position
	/// @param count Number of characters
	XString Substring(int index, int count = -1) const;

	/// Trims specified leading characters
	/// @param ch Character (default all non-printable characters)
	XString& Trim(char ch = 0);
	/// Trims specified starting leading characters
	/// @param ch Character (default all non-printable characters)
	XString& TrimStart(char ch = 0);
	/// Trims specified ending leading characters
	/// @param ch Character (default all non-printable characters)
	XString& TrimEnd(char ch = 0);

	/// Converts the string to upper case
	XString& ToUpper();
	/// Converts the string to lower case
	XString& ToLower();
	/// Converts the string to title case
	XString& ToTitle();

	/// Converts this string to double
	double ToDouble();

protected:
	/// Sets the string buffer
	/// @param pstr String
	/// @param length Lenght
	XString& SetBuffer(PSTR pstr, int length);

	/// Verify the position
	/// @param index Position
	inline bool VerifyIndex(int index) const
	{
		return ((index >= 0) && (index < m_length));
	}

	/// Verify the correct value base
	/// @param base Value base (2, 10, 16)
	bool IsValidBase(int base);
	/// Checks for valid character at the specified position
	/// @param index Position
	/// @param invalid Character (default all non-printable characters)
	bool IsValidChar(int index, char invalid = 0);

private:
	/// Lenght
	int m_length;
	/// Buffer
	PSTR m_pstr;
	/// A default char
	char m_default;

	/// Assigns a number to this instance
	/// @tparam T Integral type of value
	/// @param value Value to set
	/// @param length Minimum length filled with zeroes
	/// @param base Value base (2, 10, 16)
	/// @param decIndex Decimal separator position
	template <typename T> XString& FromInt(T value, int length, int base = 10, int decIndex = 0);
};

#endif
