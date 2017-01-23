/*******************************************************************************
 * XIO.cpp
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
#include "XIO.h"

#if defined(__XHW__)

XIO::XIO(uint8_t pin)
{
	Pin(pin);
}

void XIO::Pin(uint8_t pin)
{
	m_pin = pin;
	m_output = false;
	m_delay = 0;
	m_pr = NULL;
	m_bm = 0;
}

void XIO::Init(uint8_t mode)
{
	if (m_pin == X_NoPin)
		return;
	m_output = (mode == OUTPUT);
	m_delay = 0;
	m_pr = m_output
		? portOutputRegister(digitalPinToPort(m_pin))
		: portInputRegister(digitalPinToPort(m_pin));
	m_bm = digitalPinToBitMask(m_pin);
	pinMode(m_pin, mode);
}

#endif // __XHW__
