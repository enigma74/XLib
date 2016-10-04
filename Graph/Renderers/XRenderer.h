/*******************************************************************************
 * XRenderer.h
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

#ifndef XRenderer_h
#define XRenderer_h

/// Renderer base class
class XRenderer
{
public:
	/// Calculates next location
	virtual bool Next() = 0;

	/// Returns calculated location
	inline XPoint Location() const
	{
		return m_l;
	}

protected:
	/// Calculated location
	XPoint m_l;

	/// Constructor
	XRenderer() { }
	/// Destructor
	virtual ~XRenderer() { }
};

#endif
