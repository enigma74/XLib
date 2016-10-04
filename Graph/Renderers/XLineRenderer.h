/*******************************************************************************
 * XLineRenderer.h
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

#ifndef XLineRenderer_h
#define XLineRenderer_h

#include "XRenderer.h"

/// Bresenham line coordinates helper
class XLineRenderer : public XRenderer
{
public:
	/// Constructor
	/// @param a First location
	/// @param b Second location
	XLineRenderer(XPoint a = XPoint(), XPoint b = XPoint());
	
	/// Inits the helper with new locations
	/// @param a First location
	/// @param b Second location
	void Init(XPoint a, XPoint b);

	/// Calculates next quadrant point
	virtual bool Next() override;
	
private:
	/// X change
	int16_t m_dx;
	/// Y change
	int16_t m_dy;
	/// Slope error
	int16_t m_e;
	/// X increment
	int16_t m_xi;
	/// Y increment
	int16_t m_yi;
	/// First location
	XPoint m_a;
	/// Second location
	XPoint m_b;

	// Delete copy constructor and assignment operator
	XLineRenderer(const XLineRenderer&) = delete;
	XLineRenderer& operator=(const XLineRenderer&) = delete;
};

#endif
