/*******************************************************************************
 * XCTE16.h
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

#ifndef XCTE16_h
#define XCTE16_h

/*******************************************************************************
 * Supported hardware:
 * __SAM3X8E__				Arduino Due AT91SAM3X8E
 *******************************************************************************/

#if defined(__XHW__) && defined(__SAM3X8E__)

#define __XCTE16__

/// CTE TFT LCD/SD Shield for Arduino Due (16bit parallel LCD interface)
class XCTE16 : public XLCDBus16
{
public:
	/// Constructor
	/// @param freq Target frequency
	XCTE16(uint32_t freq = 0);

protected:
	/// Initializes the interface
	virtual void OnInit() override;
	/// Write bus data
	/// @param data Bus data
	virtual void OnWriteBus(uint16_t data);

private:
	// Delete copy constructor and assignment operator
	XCTE16(const XCTE16&) = delete;
	XCTE16& operator=(const XCTE16&) = delete;
};

#endif // __XHW__
#endif
