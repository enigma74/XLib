/*******************************************************************************
 * XDevice.h
 * Device functions for embedded devices
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

#include "Device/XSDL.h"

#endif
