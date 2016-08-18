/*******************************************************************************
 * XLCD.h
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
