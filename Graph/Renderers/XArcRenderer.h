/*******************************************************************************
 * XArcRenderer.h
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

#ifndef XArcRenderer_h
#define XArcRenderer_h

#include "XRenderer.h"

/// Bresenham circle/ellipse arc coordinates helper for a quadrant
class XArcRenderer : public XRenderer
{
public:
	/// Constructor
	/// @param rx X radius
	/// @param ry Y radius
	XArcRenderer(uint16_t rx, uint16_t ry);
	/// Constructor
	/// @param r Radius
	XArcRenderer(uint16_t r = 0);
	
	/// Inits the helper for an ellipse with new radiuses
	/// @param rx X radius
	/// @param ry Y radius
	void Init(uint16_t rx, uint16_t ry);
	/// Inits the helper for a circle with new radius
	/// @param r Radius
	inline void Init(uint16_t r);
	
	/// Calculates next quadrant point
	virtual bool Next() override;
	
private:
	/// X change increment
	int32_t m_dxi;
	/// Y change increment
	int32_t m_dyi;
	/// X change
	int32_t m_dx;
	/// Y change
	int32_t m_dy;
	/// Radius error
	int32_t m_e;
	/// First point
	XPoint m_a;

	// Delete copy constructor and assignment operator
	XArcRenderer(const XArcRenderer&) = delete;
	XArcRenderer& operator=(const XArcRenderer&) = delete;
};

#endif
