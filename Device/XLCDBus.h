/*******************************************************************************
 * XLCDBus.h
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

#ifndef XLCDBus_h
#define XLCDBus_h

#if defined(__XHW__)

/// Base parallel LCD interface class
class XLCDBus : public XLCDI
{
public:
	/// Read data pin
	XIO RD;
	/// Write data pin
	XIO WR;

protected:
	/// Constructor
	/// @param type Type
	/// @param freq Target frequency
	XLCDBus(XLCDIType type, uint32_t freq = 0);

	/// Pulse write pin count times
	/// @param count Count
	void PulseWrite(uint32_t count = 1);

	/// Initializes the interface
	virtual void OnInit() override;
	/// Begins a read/write operation
	/// @param write Write flag
	virtual void OnBegin(bool write) override;

private:
	// Delete copy constructor and assignment operator
	XLCDBus(const XLCDBus&) = delete;
	XLCDBus& operator=(const XLCDBus&) = delete;
};

#endif // __XHW__
#endif
