/*******************************************************************************
 * XDevice.h
 * Device functions for embedded devices
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

#ifndef XDevice_h
#define XDevice_h

#include "XMain.h"
#include "XGraph.h"

#include "Device/XLCDI.h"
#include "Device/XLCDSerial.h"
#include "Device/XLCDBus.h"
#include "Device/XLCDBus8.h"
#include "Device/XLCDBus16.h"

#include "Device/Shield/XUnoShield.h"
#include "Device/Shield/XCTE8.h"
#include "Device/Shield/XCTE16.h"
#include "Device/Shield/XElecHouse8.h"
#include "Device/Shield/XElecHouse16.h"
#include "Device/Shield/XAquaLED.h"

#include "Device/XLCD.h"
#include "Device/XGLCD.h"

#include "Device/LCD/XILI9488.h"
#include "Device/LCD/XPCF8814.h"

#include "Device/LCD/XPCF8814Text.h"

#include "Device/XTouch.h"

#endif
