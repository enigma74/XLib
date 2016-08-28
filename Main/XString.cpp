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

XString::XString(PCSTR pstr)
{
	m_pstr = NULL;
	Set(pstr);
}

XString::XString(const XString& str)
	: XString((PCSTR)str)
{
}

XString::XString(char ch, int count)
	: XString((PSTR)NULL)
{
	Set(ch, count);
}

XString::XString(int16_t value, int base)
	: XString((PCSTR)NULL)
{
	Set(value, base);
}

XString::XString(uint16_t value, int base)
	: XString((PCSTR)NULL)
{
	Set(value, base);
}

XString::XString(int32_t value, int base)
	: XString((PCSTR)NULL)
{
	Set(value, base);
}

XString::XString(uint32_t value, int base)
	: XString((PCSTR)NULL)
{
	Set(value, base);
}

XString::XString(int64_t value, int base)
	: XString((PCSTR)NULL)
{
	Set(value, base);
}

XString::XString(uint64_t value, int base)
	: XString((PCSTR)NULL)
{
	Set(value, base);
}

XString::XString(float value, int dec)
	: XString((PCSTR)NULL)
{
	Set(value, dec);
}

XString::XString(double value, int dec)
	: XString((PCSTR)NULL)
{
	Set(value, dec);
}

XString::~XString()
{
	Clear();
}

// ********************************************************************************

XString& XString::SetBuffer(PSTR pstr, int lenght)
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

XString& XString::Set(PCSTR pstr)
{
	int lenght = pstr ? (int)strlen(pstr) : 0;
	if (!lenght)
		return Clear();
	PSTR ptmp = new char[lenght + 1];
	memcpy(ptmp, pstr, lenght);
	return SetBuffer(ptmp, lenght);
}

XString& XString::Set(char ch, int count)
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
		case 8:
		case 10:
		case 16:
			return true;
		default:
			return false;
	}
}

template <typename T> XString& XString::SetValue(T value, int base, int decIndex)
{
	if (!IsValidBase(base))
		return Clear();
	PSTR ptmp = new char[X_MaxNum + 1];
	char digits[] = "0123456789ABCDEF";
	int i = X_MaxNum;
	bool neg = value < 0;
	if (decIndex < 0)
		decIndex = 0;
	do
	{
		int r = value % base;
		ptmp[--i] = digits[neg ? -r : r];
		value /= base;
		if (decIndex && ((X_MaxNum - i) == decIndex))
		{
			ptmp[--i] = DecimalSeparator;
			decIndex = 0;
		}
	} while ((value != 0) && (i > 0));
	if (neg && (i > 0))
		ptmp[--i] = '-';
	return SetBuffer(ptmp, X_MaxNum).CropAt(i);
}

XString& XString::Set(int16_t value, int base)
{
	return SetValue(value, base);
}

XString& XString::Set(uint16_t value, int base)
{
	return SetValue(value, base);
}

XString& XString::Set(int32_t value, int base)
{
	return SetValue(value, base);
}

XString& XString::Set(uint32_t value, int base)
{
	return SetValue(value, base);
}

XString& XString::Set(int64_t value, int base)
{
	return SetValue(value, base);
}

XString& XString::Set(uint64_t value, int base)
{
	return SetValue(value, base);
}

XString& XString::Set(float value, int dec)
{
	return Set((double)value, dec);
}

XString& XString::Set(double value, int dec)
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
				while ((dec < max) && (fabs(value - round(value)) > 0.0001))
				{
					value *= 10.0;
					dec++;
				}
			}
		}
		else
			dec = 0;
	}
	return SetValue((int64_t)round(value), 10, dec);
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
	return Set(tmp);
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
	return SetBuffer(ptmp, lenght);
}

XString& XString::Append(PCSTR pstr)
{
	return InsertAt(m_lenght, pstr);
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
	return Append(XString(ch));
}

XString XString::operator+(char ch) const
{
	return XString(*this) += ch;
}

XString& XString::RemoveAt(int index, int count)
{
	if ((index < 0) || (index >= m_lenght) || (count < 1))
		return *this;
	int r = m_lenght - index;
	if (count > r)
		count = r;
	if (count == m_lenght)
		return Clear();
	int lenght = m_lenght - count;
	PSTR ptmp = new char[lenght + 1];
	if (index > 0)
		memcpy(ptmp, m_pstr, index);
	r -= count;
	if (r)
		memcpy(ptmp + index, m_pstr + index + count, r);
	return SetBuffer(ptmp, lenght);
}

XString& XString::CropAt(int index, int count)
{
	if ((index < 0) || (index >= m_lenght))
		return Clear();
	int r = m_lenght - index;
	if ((count < 0) || (count > r))
		count = r;
	if (count == m_lenght)
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
	if (m_lenght == 0)
		return *this;
	for (int start = 0; start < m_lenght; start++)
		if (IsValidChar(start, ch))
			for (int end = m_lenght - 1; end >= start; end--)
				if (IsValidChar(end, ch))
					return CropAt(start, end - start + 1);
	return Clear();
}

XString& XString::TrimStart(char ch)
{
	if (m_lenght == 0)
		return *this;
	for (int start = 0; start < m_lenght; start++)
		if (IsValidChar(start, ch))
			return CropAt(start, m_lenght - start);
	return Clear();
}

XString& XString::TrimEnd(char ch)
{
	if (m_lenght == 0)
		return *this;
	for (int end = m_lenght - 1; end >= 0; end--)
		if (IsValidChar(end, ch))
			return CropAt(0, end + 1);
	return Clear();
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

double XString::ToDouble()
{
	return IsEmpty() ? 0 : strtod(m_pstr, NULL);
}
