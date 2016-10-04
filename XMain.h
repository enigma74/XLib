/*******************************************************************************
 * XMain.h
 * Main functions for embedded devices
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

#ifndef XMain_h
#define XMain_h

#if defined(__AVR__) || defined(__arm__) || defined(__PIC32MX__)
	#if (ARDUINO > 100)
		#include "Arduino.h"
	#else
		#include "WProgram.h"
	#endif
	#define __XHW__
#endif

#include <stdint.h>

#include "Main/XUtils.h"
#include "Main/XReg.h"
#include "Main/XIO.h"

#include "Main/XArray.h"
#include "Main/XData.h"
#include "Main/XFlashData.h"

#include "Main/XString.h"

#endif
