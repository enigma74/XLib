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
	/// Constructor
	/// @param pstr Source string pointer
	XString(PCSTR pstr = NULL);
	/// Constructor
	/// @param str Source string
	XString(const XString& str);
	/// Destructor
	virtual ~XString();
	
	/// Clears the string
	inline XString& Clear()
	{
		return Set();
	}

	/// Assigns a string to this instance
	/// @param pstr Source string pointer
	XString& From(PCSTR pstr);

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
	
	/// Returns string pointer
	inline operator PCSTR() const
	{
		return m_pstr;
	}
	
	/// Returns string lenght
	inline int Lenght() const
	{
		return m_lenght;
	}
	
	/// Checks for empty string
	inline bool IsEmpty() const
	{
		return m_lenght == 0;
	}

	/// Assigns a converted long to this instance
	XString& FromLong(long value, int base = 10);
	/// Convert this string to long
	long ToLong(int base = 10);
	
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
	int NoCaseCompareTo(PCSTR pstr) const;
	/// Checks for equality with another string
	/// @param pstr Second string
	/// @param ignorecase Case insensitive flag
	bool Equals(PCSTR pstr, bool ignorecase = false) const;
	/// Checks for equality with another string (case insensitive)
	/// @param pstr Second string
	bool NoCaseEquals(PCSTR pstr) const;
	
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
	int NoCaseIndexOf(PCSTR pstr, int start = 0, int skip = 0) const;
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
	int NoCaseIndexOf(char ch, int start = 0, int skip = 0) const;

	/// Insert a string in the specified position
	/// @param index Position
	/// @param pstr String to insert
	XString& InsertAt(int index, PCSTR pstr);
	/// Insert a character in the specified position
	/// @param index Position
	/// @param ch Character to insert
	XString& InsertAt(int index, char ch);
	/// Appends a string
	/// @param pstr String to append
	XString& Append(PCSTR pstr);
	/// Appends a character
	/// @param ch Character to append
	XString& Append(char ch);

	/// Appends a string
	XString& operator+=(PCSTR pstr);
	/// Adds a string
	XString operator+(PCSTR pstr) const;
	/// Appends a character
	XString& operator+=(char ch);
	/// Adds a character
	XString operator+(char ch) const;

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

protected:
	/// Lenght
	int m_lenght;
	/// Buffer
	PSTR m_pstr;
	/// A default char
	char m_default;

	/// Sets the string
	/// @param pstr String
	/// @param lenght Lenght
	XString& Set(PSTR pstr = NULL, int lenght = 0);
	
	/// Verify the position
	/// @param index Position
	inline bool VerifyIndex(int index) const
	{
		return ((index >= 0) && (index < m_lenght));
	}

	/// Checks for valid character at the specified position
	/// @param index Position
	/// @param invalid Character (default all non-printable characters)
	bool IsValidChar(int index, char invalid = 0);
};

#endif
