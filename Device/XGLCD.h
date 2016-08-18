/*******************************************************************************
 * XGLCD.h
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
