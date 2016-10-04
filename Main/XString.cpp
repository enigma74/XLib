/*******************************************************************************
 * XString.h
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
#include "XString.h"

#include <ctype.h>
#include <math.h>
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

char XString::DecimalSeparator = '.';
char XString::ThousandsSeparator = ',';

XString::XString(PCSTR pstr)
{
	m_pstr = NULL;
	From(pstr);
}

XString::XString(const XString& str)
{
	m_pstr = NULL;
	From(str);
}

XString::XString(char ch, int count)
{
	m_pstr = NULL;
	From(ch, count);
}

XString::XString(int16_t value, int base, int length)
{
	m_pstr = NULL;
	From(value, base, length);
}

XString::XString(uint16_t value, int base, int length)
{
	m_pstr = NULL;
	From(value, base, length);
}

XString::XString(int32_t value, int base, int length)
{
	m_pstr = NULL;
	From(value, base, length);
}

XString::XString(uint32_t value, int base, int length)
{
	m_pstr = NULL;
	From(value, base, length);
}

XString::XString(int64_t value, int base, int length)
{
	m_pstr = NULL;
	From(value, base, length);
}

XString::XString(uint64_t value, int base, int length)
{
	m_pstr = NULL;
	From(value, base, length);
}

XString::XString(float value, int dec, int length)
{
	m_pstr = NULL;
	From(value, dec, length);
}

XString::XString(double value, int dec, int length)
{
	m_pstr = NULL;
	From(value, dec, length);
}

XString::~XString()
{
	Clear();
}

// ********************************************************************************

XString& XString::SetBuffer(PSTR pstr, int length)
{
	m_length = length;
	if (m_pstr)
		delete m_pstr;
	m_pstr = pstr;
	if (m_pstr)
		m_pstr[length] = 0;
	return *this;
}

XString& XString::From(PCSTR pstr)
{
	int lenght = pstr ? (int)strlen(pstr) : 0;
	if (!lenght)
		return Clear();
	PSTR ptmp = new char[lenght + 1];
	memcpy(ptmp, pstr, lenght);
	return SetBuffer(ptmp, lenght);
}

XString& XString::From(char ch, int count)
{
	if ((ch == 0) || (count < 1))
		return Clear();
	PSTR ptmp = new char[count + 1];
	for (int i = 0; i < count; i++)
		ptmp[i] = ch;
	return SetBuffer(ptmp, count);
}

bool XString::IsValidBase(int base)
{
	switch (base)
	{
		case 2:
		case 10:
		case 16:
			return true;
		default:
			return false;
	}
}

template <typename T> XString& XString::FromInt(T value, int length, int base, int decIndex)
{
	if (!IsValidBase(base))
		return Clear();
	PSTR ptmp = new char[X_MaxNum + 1];
	char digits[] = "0123456789ABCDEF";
	int i = X_MaxNum;
	bool neg = value < 0;
	if (decIndex < 0)
		decIndex = 0;
	int tIndex = base == 10
		? (decIndex ? decIndex + 4 : 3)
		: 0;
	do
	{
		int r = value % base;
		ptmp[--i] = digits[neg ? -r : r];
		value /= base;
		int p = (X_MaxNum - i);
		if (decIndex && (p == decIndex))
		{
			ptmp[--i] = DecimalSeparator;
			decIndex = 0;
		}
		if (tIndex && (p == tIndex))
		{
			ptmp[--i] = ThousandsSeparator;
			tIndex += 4;
		}
	} while ((value != 0) && (i > 0));
	if (neg && (i > 0))
		ptmp[--i] = '-';
	if (length > 0)
	{
		int start = length >= X_MaxNum ? 0 : X_MaxNum - length;
		char ch = base == 10 ? ' ' : '0';
		while (i > start)
			ptmp[--i] = ch;
	}
	return SetBuffer(ptmp, X_MaxNum).CropAt(i);
}

XString& XString::From(int16_t value, int base, int length)
{
	if (base != 10)
		return FromInt((uint16_t)value, length, base);
	return FromInt(value, length, base);
}

XString& XString::From(uint16_t value, int base, int length)
{
	if (!length)
	{
		switch (base)
		{
			case 2: length = 16; break;
			case 16: length = 4; break;
			default: break;
		}
	}
	return FromInt(value, length, base);
}

XString& XString::From(int32_t value, int base, int length)
{
	if (base != 10)
		return FromInt((uint32_t)value, length, base);
	return FromInt(value, length, base);
}

XString& XString::From(uint32_t value, int base, int length)
{
	if (!length)
	{
		switch (base)
		{
			case 2: length = 32; break;
			case 16: length = 8; break;
			default: break;
		}
	}
	return FromInt(value, length, base);
}

XString& XString::From(int64_t value, int base, int length)
{
	if (base != 10)
		return FromInt((uint64_t)value, length, base);
	return FromInt(value, length, base);
}

XString& XString::From(uint64_t value, int base, int length)
{
	if (!length)
	{
		switch (base)
		{
			case 2: length = 64; break;
			case 16: length = 16; break;
			default: break;
		}
	}
	return FromInt(value, length, base);
}

XString& XString::From(float value, int dec, int length)
{
	return From((double)value, dec, length);
}

XString& XString::From(double value, int dec, int length)
{
	if (dec)
	{
		int max = 15 - (int)log10(fabs(value));
		if (max > 0)
		{
			if (dec > 0)
			{
				if (dec > max)
					dec = max;
				value *= pow(10, dec);
			}
			else
			{
				dec = 0;
				while ((dec < max) && (fabs(value - round(value)) > 1e-7))
				{
					value *= 10.0;
					dec++;
				}
			}
		}
		else
			dec = 0;
	}
	return FromInt((int64_t)round(value), length, 10, dec);
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

int XString::CompareToNoCase(PCSTR pstr) const
{
	return CompareTo(pstr, true);
}

bool XString::Equals(PCSTR pstr, bool ignorecase) const
{
	return CompareTo(pstr, ignorecase) == 0;
}

bool XString::EqualsNoCase(PCSTR pstr) const
{
	return CompareTo(pstr, true) == 0;
}

int XString::IndexOf(PCSTR pstr, int start, int skip, bool ignorecase) const
{
	if (start < 0)
		start = 0;
	if (!pstr || (start >= m_length))
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

int XString::IndexOfNoCase(PCSTR pstr, int start, int skip) const
{
	return IndexOf(pstr, start, skip, true);
}

int XString::IndexOf(char ch, int start, int skip, bool ignorecase) const
{
	char tmp[2] = { ch, 0 };
	return IndexOf(tmp, start, skip, ignorecase);
}

int XString::IndexOfNoCase(char ch, int start, int skip) const
{
	return IndexOf(ch, start, skip, true);
}

XString& XString::InsertAt(int index, PCSTR pstr)
{
	int l = pstr ? (int)strlen(pstr) : 0;
	if ((index < 0) || (index > m_length) || !l)
		return *this;
	int length = m_length + l;
	PSTR ptmp = new char[length + 1];
	if (index > 0)
		memcpy(ptmp, m_pstr, index);
	memcpy(ptmp + index, pstr, l);
	int r = m_length - index;
	if (r)
		memcpy(ptmp + index + l, m_pstr + index, r);
	return SetBuffer(ptmp, length);
}

XString& XString::Append(PCSTR pstr)
{
	return InsertAt(m_length, pstr);
}

XString& XString::operator+=(PCSTR pstr)
{
	return Append(pstr);
}

XString& XString::operator+=(const XString& str)
{
	return Append(str);
}

XString& XString::operator+=(char ch)
{
	return Append(XString(ch));
}

XString operator+(const XString& stra, const XString& strb)
{
	return XString(stra) += strb;
}

XString operator+(PCSTR pstra, const XString& strb)
{
	return XString(pstra) += strb;
}

XString operator+(const XString& stra, PCSTR pstrb)
{
	return XString(stra) += pstrb;
}

XString operator+(char ch, const XString& str)
{
	return XString(ch) += str;
}

XString operator+(const XString& str, char ch)
{
	return XString(str) += ch;
}

XString& XString::RemoveAt(int index, int count)
{
	if ((index < 0) || (index >= m_length) || (count < 1))
		return *this;
	int r = m_length - index;
	if (count > r)
		count = r;
	if (count == m_length)
		return Clear();
	int length = m_length - count;
	PSTR ptmp = new char[length + 1];
	if (index > 0)
		memcpy(ptmp, m_pstr, index);
	r -= count;
	if (r)
		memcpy(ptmp + index, m_pstr + index + count, r);
	return SetBuffer(ptmp, length);
}

XString& XString::CropAt(int index, int count)
{
	if ((index < 0) || (index >= m_length))
		return Clear();
	int r = m_length - index;
	if ((count < 0) || (count > r))
		count = r;
	if (count == m_length)
		return *this;
	if (count == 0)
		return Clear();
	PSTR ptmp = new char[count + 1];
	memcpy(ptmp, m_pstr + index, count);
	return SetBuffer(ptmp, count);
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
	if (m_length == 0)
		return *this;
	for (int start = 0; start < m_length; start++)
		if (IsValidChar(start, ch))
			for (int end = m_length - 1; end >= start; end--)
				if (IsValidChar(end, ch))
					return CropAt(start, end - start + 1);
	return Clear();
}

XString& XString::TrimStart(char ch)
{
	if (m_length == 0)
		return *this;
	for (int start = 0; start < m_length; start++)
		if (IsValidChar(start, ch))
			return CropAt(start, m_length - start);
	return Clear();
}

XString& XString::TrimEnd(char ch)
{
	if (m_length == 0)
		return *this;
	for (int end = m_length - 1; end >= 0; end--)
		if (IsValidChar(end, ch))
			return CropAt(0, end + 1);
	return Clear();
}

XString& XString::ToUpper()
{
	for (int index = 0; index < m_length; index++)
		m_pstr[index] = toupper(m_pstr[index]);
	return *this;
}

XString& XString::ToLower()
{
	for (int index = 0; index < m_length; index++)
		m_pstr[index] = tolower(m_pstr[index]);
	return *this;
}

XString& XString::ToTitle()
{
	bool upper = true;
	for (int index = 0; index < m_length; index++)
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

double XString::ToDouble()
{
	return IsEmpty() ? 0 : strtod(m_pstr, NULL);
}
