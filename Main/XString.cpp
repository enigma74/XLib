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

#include "XMain.h"
#include "XString.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#ifdef _MSC_VER
	#define snprintf _snprintf
	#define strncasecmp _strnicmp
	#define strcasecmp _stricmp
#endif

#define X_MaxText 512
#define X_MaxNum 32

XString::XString(PCSTR pstr)
{
	m_pstr = NULL;
	From(pstr);
}

XString::XString(const XString& str)
	: XString((PCSTR)str)
{
}

XString::~XString()
{
	Clear();
}

// ********************************************************************************

XString& XString::Set(PSTR pstr, int lenght)
{
	m_lenght = lenght;
	if (m_pstr)
		delete m_pstr;
	m_pstr = pstr;
	if (m_pstr)
		m_pstr[lenght] = 0;
	return *this;
}

// ********************************************************************************

XString& XString::From(PCSTR pstr)
{
	int lenght = pstr ? (int)strlen(pstr) : 0;
	if (!lenght)
		return Set();
	PSTR ptmp = new char[lenght + 1];
	memcpy(ptmp, pstr, lenght);
	return Set(ptmp, lenght);
}

XString& XString::FromLong(long value, int base)
{
	char chars[] = "0123456789abcdef";

	char tmp[X_MaxNum];

//	int i = 0;
//	if (value < 0)
//	{
//		tmp[0] = '-';
//
//	}

	snprintf(tmp, X_MaxNum, "%li", value);
	//ltoa(value, tmp, X_MaxNum, base);
	return From(tmp);
}

long XString::ToLong(int base)
{
	return IsEmpty() ? 0 : atol(m_pstr);
}

XString& XString::Format(PCSTR fmt, ...)
{
	if (!fmt)
		return Clear();
	va_list args;
	va_start(args, fmt);
	char tmp[X_MaxText];
	vsnprintf(tmp, X_MaxText, fmt, args);
	va_end(args);
	return From(tmp);
}

char XString::operator[](int index) const
{
	return VerifyIndex(index) ? m_pstr[index] : 0;
}

char& XString::operator[](int index)
{
	return VerifyIndex(index) ? m_pstr[index] : (m_default = 0);
}

int XString::CompareTo(PCSTR pstr, bool ignorecase) const
{
	if (!m_pstr && !pstr)
		return 0;
	if (!m_pstr)
		return -1;
	if (!pstr)
		return 1;
	return ignorecase
		? strcasecmp(m_pstr, pstr)
		: strcmp(m_pstr, pstr);
}

int XString::NoCaseCompareTo(PCSTR pstr) const
{
	return CompareTo(pstr, true);
}

bool XString::Equals(PCSTR pstr, bool ignorecase) const
{
	return CompareTo(pstr, ignorecase) == 0;
}

bool XString::NoCaseEquals(PCSTR pstr) const
{
	return CompareTo(pstr, true) == 0;
}

int XString::IndexOf(PCSTR pstr, int start, int skip, bool ignorecase) const
{
	if (start < 0)
		start = 0;
	if (!pstr || (start >= m_lenght))
		return -1;
	while (skip >= 0)
	{
		PSTR paddr = ignorecase
			? strcasestr(m_pstr + start, pstr)
			: strstr(m_pstr + start, pstr);
		if (!paddr)
			return -1;
		int p = (int)(paddr - m_pstr);
		if (skip == 0)
			return p;
		start = p + 1;
		skip--;
	}
	return -1;
}

int XString::NoCaseIndexOf(PCSTR pstr, int start, int skip) const
{
	return IndexOf(pstr, start, skip, true);
}

int XString::IndexOf(char ch, int start, int skip, bool ignorecase) const
{
	char tmp[2] = { ch, 0 };
	return IndexOf(tmp, start, skip, ignorecase);
}

int XString::NoCaseIndexOf(char ch, int start, int skip) const
{
	return IndexOf(ch, start, skip, true);
}

XString& XString::InsertAt(int index, PCSTR pstr)
{
	int l = pstr ? (int)strlen(pstr) : 0;
	if ((index < 0) || (index > m_lenght) || !l)
		return *this;
	int lenght = m_lenght + l;
	PSTR ptmp = new char[lenght + 1];
	if (index > 0)
		memcpy(ptmp, m_pstr, index);
	memcpy(ptmp + index, pstr, l);
	int r = m_lenght - index;
	if (r)
		memcpy(ptmp + index + l, m_pstr + index, r);
	return Set(ptmp, lenght);
}

XString& XString::InsertAt(int index, char ch)
{
	char tmp[2] = { ch, 0 };
	return InsertAt(index, tmp);
}


XString& XString::Append(PCSTR pstr)
{
	return InsertAt(m_lenght, pstr);
}

XString& XString::Append(char ch)
{
	return InsertAt(m_lenght, ch);
}

XString& XString::operator+=(PCSTR pstr)
{
	return Append(pstr);
}

XString XString::operator+(PCSTR pstr) const
{
	return XString(*this).Append(pstr);
}

XString& XString::operator+=(char ch)
{
	return Append(ch);
}

XString XString::operator+(char ch) const
{
	return XString(*this).Append(ch);
}

XString& XString::RemoveAt(int index, int count)
{
	if ((index < 0) || (index >= m_lenght) || (count < 1))
		return *this;
	int r = m_lenght - index;
	if (count > r)
		count = r;
	if (count == m_lenght)
		return Set();
	int lenght = m_lenght - count;
	PSTR ptmp = new char[lenght + 1];
	if (index > 0)
		memcpy(ptmp, m_pstr, index);
	r -= count;
	if (r)
		memcpy(ptmp + index, m_pstr + index + count, r);
	return Set(ptmp, lenght);
}

XString& XString::CropAt(int index, int count)
{
	if ((index < 0) || (index >= m_lenght))
		return Set();
	int r = m_lenght - index;
	if ((count < 0) || (count > r))
		count = r;
	if (count == m_lenght)
		return *this;
	if (count == 0)
		return Set();
	PSTR ptmp = new char[count + 1];
	memcpy(ptmp, m_pstr + index, count);
	return Set(ptmp, count);
}

XString XString::Substring(int index, int count) const
{
	return XString(*this).CropAt(index, count);
}

bool XString::IsValidChar(int index, char invalid)
{
	char ch = m_pstr[index];
	return ((invalid > 0) && (ch != invalid))
		|| ((invalid == 0) && (ch > 0x20));
}

XString& XString::Trim(char ch)
{
	if (m_lenght == 0)
		return *this;
	for (int start = 0; start < m_lenght; start++)
		if (IsValidChar(start, ch))
			for (int end = m_lenght - 1; end >= start; end--)
				if (IsValidChar(end, ch))
					return CropAt(start, end - start + 1);
	return Set();
}

XString& XString::TrimStart(char ch)
{
	if (m_lenght == 0)
		return *this;
	for (int start = 0; start < m_lenght; start++)
		if (IsValidChar(start, ch))
			return CropAt(start, m_lenght - start);
	return Set();
}

XString& XString::TrimEnd(char ch)
{
	if (m_lenght == 0)
		return *this;
	for (int end = m_lenght - 1; end >= 0; end--)
		if (IsValidChar(end, ch))
			return CropAt(0, end + 1);
	return Set();
}

XString& XString::ToUpper()
{
	for (int index = 0; index < m_lenght; index++)
		m_pstr[index] = toupper(m_pstr[index]);
	return *this;
}

XString& XString::ToLower()
{
	for (int index = 0; index < m_lenght; index++)
		m_pstr[index] = tolower(m_pstr[index]);
	return *this;
}

XString& XString::ToTitle()
{
	bool upper = true;
	for (int index = 0; index < m_lenght; index++)
	{
		char ch = m_pstr[index];
		if (!isalnum(ch))
		{
			upper = true;
			continue;
		}
		if (isalpha(ch))
			m_pstr[index] = upper ? toupper(ch) : tolower(ch);
		upper = false;
	}
	return *this;
}
