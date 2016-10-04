/*******************************************************************************
 * XGLCD.h
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

#ifndef XGLCD_h
#define XGLCD_h

#if defined(__XHW__)

#define X_LCDHFlip 0x01
#define X_LCDVFlip 0x02
#define X_LCDSwap 0x04

/// Graphic LCD rotation
enum class XGLCDRotation : uint8_t
{
	/// Default
	Default,
	/// Clockwise 90 degrees
	CW90,
	/// Counterclockwise 90 degrees
	CCW90,
	/// 180 degrees
	CW180
};

// ********************************************************************************

/// Base graphic LCD class
class XGLCD : public XLCD, public XDisplay
{
public:
	using XLCD::Init;
	/// Initializes the LCD
	/// @param rotation Rotation to use
	void Init(XGLCDRotation rotation);
	/// Rotates flags state by the specified rotation
	/// @param rotation Rotation to use
	static uint8_t RotateFlags(uint8_t flags, XGLCDRotation rotation);

	/// Returns current rotation
	inline XGLCDRotation Rotation() const
	{
		return m_rotation;
	}

protected:
	/// Physical size
	const XSize m_physical;
	/// Rotation
	XGLCDRotation m_rotation;

	/// Constructor
	/// @param size Display context size
	/// @param i Interface
	XGLCD(const XSize& size, XLCDI& i);

	/// Initializes the LCD
	virtual void OnInit() override;

	/// Rotates the LCD
	inline virtual bool OnRotate()
	{
		return false;
	}

	/// Clears the LCD
	inline virtual void OnClear() override
	{
		OnFill(m_rect, X_Black);
	}

	/// Begins a drawing function
	virtual void OnBeginFunction() override;
	/// Ends a drawing function
	virtual void OnEndFunction() override;

private:
	// Delete copy constructor and assignment operator
	XGLCD(const XGLCD&) = delete;
	XGLCD& operator=(const XGLCD&) = delete;
};

#endif // __XHW__
#endif
