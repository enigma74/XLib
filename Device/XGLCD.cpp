/*******************************************************************************
 * XGLCD.cpp
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

#include "XDevice.h"
#include "XGLCD.h"

#if defined(__XHW__)

XGLCD::XGLCD(const XSize& size, XLCDI& i)
	: XLCD(i), XDisplay(size), m_physical(size)
{
	m_rotation = XGLCDRotation::Default;
}

// ********************************************************************************

void XGLCD::OnInit()
{
	m_rect.Size = m_physical;
	if (!OnRotate())
	{
		m_rotation = XGLCDRotation::Default;
		return;
	}
	m_rect.Size = m_physical;
	if ((m_rotation == XGLCDRotation::CW90) || (m_rotation == XGLCDRotation::CCW90))
		XSwap(m_rect.Size.Width, m_rect.Size.Height);
}

void XGLCD::Init(XGLCDRotation rotation)
{
	m_rotation = rotation;
	XLCD::Init();
}

uint8_t XGLCD::RotateFlags(uint8_t flags, XGLCDRotation rotation)
{
	switch (rotation)
	{
		case XGLCDRotation::CW90:
			X_ToggleFlag(flags, X_LCDVFlip);
			X_ToggleFlag(flags, X_LCDSwap);
			break;
		case XGLCDRotation::CCW90:
			X_ToggleFlag(flags, X_LCDHFlip);
			X_ToggleFlag(flags, X_LCDSwap);
			break;
		case XGLCDRotation::CW180:
			X_ToggleFlag(flags, X_LCDHFlip);
			X_ToggleFlag(flags, X_LCDVFlip);
			break;
		default:
			break;
	}
	return flags;
}

// ********************************************************************************

void XGLCD::OnBeginFunction()
{
	XDisplay::OnBeginFunction();
	I.Enable();
}

void XGLCD::OnEndFunction()
{
	I.Disable();
	XDisplay::OnEndFunction();
}

#endif // __XHW__
