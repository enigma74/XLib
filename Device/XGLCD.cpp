/*******************************************************************************
 * XGLCD.cpp
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
