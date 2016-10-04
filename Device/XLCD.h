/*******************************************************************************
 * XLCD.h
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

#ifndef XLCD_h
#define XLCD_h

#if defined(__XHW__)

/// Base LCD class
class XLCD
{
public:
	/// Interface
	XLCDI& I;

	/// Initializes the LCD
	void Init();
	/// Turns on the LCD
	void On();
	/// Turns off the LCD
	void Off();

	/// Returns current inverted state
	inline bool Inverted() const
	{
		return m_inverted;
	}

	/// Inverts the LCD
	/// @param inverted Invert flag
	void Invert(bool inverted = true);

	/// Changes contrast
	/// @param contrast Contrast value
	inline uint8_t Contrast() const
	{
		return m_contrast;
	}

	/// Changes contrast
	/// @param contrast Contrast value
	void Contrast(uint8_t contrast);
	/// Clears the LCD
	void Clear();

protected:
	/// Inverted flag
	bool m_inverted;
	/// Constrast
	uint8_t m_contrast;

	/// Constructor
	/// @param i Interface
	XLCD(XLCDI& i);
	/// Destructor
	virtual ~XLCD() { }

	/// Initializes the LCD
	virtual void OnInit() = 0;
	/// Turns on the LCD
	inline virtual void OnOn() { }
	/// Turns off the LCD
	inline virtual void OnOff() { }
	/// Inverts the LCD
	inline virtual void OnInvert() { }
	/// Changes contrast
	inline virtual void OnContrast() { }
	/// Clears the LCD
	inline virtual void OnClear() { }

private:
	// Delete copy constructor and assignment operator
	XLCD(const XLCD&) = delete;
	XLCD& operator=(const XLCD&) = delete;
};

#endif // __XHW__
#endif
