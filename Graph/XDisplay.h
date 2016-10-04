/*******************************************************************************
 * XDisplay.h
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

#ifndef XDisplay_h
#define XDisplay_h

/// Base display class
class XDisplay : public XContext
{
	// Friends symbols
	friend XContext;

protected:
	/// Constructor
	/// @param size Display context size
	XDisplay(const XSize& size);

	/// Begins a drawing sequence
	inline virtual void OnBeginSequence() { }
	/// Ends a drawing sequence
	inline virtual void OnEndSequence() { }
	/// Begins a drawing sequence
	void OnBegin();
	/// Ends a drawing sequence
	void OnEnd();

	/// Begins a drawing function
	inline virtual void OnBeginFunction()
	{
		Begin();
	}

	/// Ends a drawing function
	inline virtual void OnEndFunction()
	{
		End();
	}
	
	/// Fills a rectangle
	/// @param rect Display rectangle
	/// @param color Color to use
	virtual void OnFill(const XRect& rect, const XColor& color) = 0;
	/// Reads a pixel color
	/// @param p Display location
	inline virtual XColor OnReadPixel(const XPoint& p, const XColor& color)
	{
		return X_NoColor;
	}
	
private:
	/// Drawing counter
	uint16_t m_count;

	// Delete copy constructor and assignment operator
	XDisplay(const XDisplay&) = delete;
	XDisplay& operator=(const XDisplay&) = delete;
};

#endif
