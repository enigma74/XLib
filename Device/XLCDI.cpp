/*******************************************************************************
 * XLCDI.cpp
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
#include "XLCDI.h"

#if defined(__XHW__)

XLCDI::XLCDI(XLCDIType type, uint32_t freq)
	: Type(type)
{
	m_delay = XFreqCycles(freq);
}

void XLCDI::Init()
{
	CS.InitOutput(HIGH);
	DC.InitOutput();
	RST.InitOutput(HIGH);
	delay(5);
	RST.Low();
	delay(15);
	RST.High();
	delay(15);
	OnInit();
}

bool XLCDI::Begin(bool write, bool cmd)
{
	if (!CS.IsInit() || CS)
		return false;
	OnBegin(write);
	DC = !cmd;
	return true;
}

#endif // __XHW__
