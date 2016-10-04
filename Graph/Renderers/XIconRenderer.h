/*******************************************************************************
 * XIconRenderer.h
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

#ifndef XIconRenderer_h
#define XIconRenderer_h

#include "XGlyphRenderer.h"

/// Icon points renderer
class XIconRenderer : public XGlyphRenderer
{
public:
	/// Constructor
	/// @param rect Rectangle
	/// @param picon Icon data pointer
	XIconRenderer(const XRect& rect = XRect(), const XData* picon = NULL);

	/// Inits the renderer with new data
	/// @param rect Rectangle
	/// @param picon Icon data pointer
	void Init(const XRect& rect, const XData* picon);

	/// Returns icon size
	inline XSize Size() const
	{
		return m_size;
	}

	/// Calculates next icon point
	virtual bool Next() override;

private:
	/// Icon rect
	XRect m_rect;
	/// Icon size
	XSize m_size;
	/// Starting location
	XPoint m_a;

private:
	// Delete copy constructor and assignment operator
	XIconRenderer(const XIconRenderer&) = delete;
	XIconRenderer& operator=(const XIconRenderer&) = delete;
};

#endif
