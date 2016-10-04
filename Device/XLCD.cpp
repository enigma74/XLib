/*******************************************************************************
 * XLCD.cpp
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

#include "XDevice.h"
#include "XLCD.h"

#if defined(__XHW__)

XLCD::XLCD(XLCDI& i)
	: I(i)
{
	m_inverted = false;
	m_contrast = 0;
}

// ********************************************************************************

void XLCD::Init()
{
	I.Init();
	I.Enable();
	OnOff();
	OnInit();
	OnInvert();
	OnContrast();
	OnClear();
	OnOn();
	I.Disable();
}

void XLCD::On()
{
	I.Enable();
	OnOn();
	I.Disable();
}

void XLCD::Off()
{
	I.Enable();
	OnOff();
	I.Disable();
}

void XLCD::Invert(bool inverted)
{
	if (inverted == m_inverted)
		return;
	I.Enable();
	m_inverted = inverted;
	OnInvert();
	I.Disable();
}

void XLCD::Contrast(uint8_t contrast)
{
	if (contrast == m_contrast)
		return;
	I.Enable();
	m_contrast = contrast;
	OnContrast();
	I.Disable();
}

void XLCD::Clear()
{
	I.Enable();
	OnClear();
	I.Disable();
}

#endif // __XHW__
