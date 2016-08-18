/*******************************************************************************
 * XUnoShield.h
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

#ifndef XUnoShield_h
#define XUnoShield_h

/*******************************************************************************
 * Supported hardware:
 * __AVR_ATmega1280__	Arduino Mega ATmega1280
 * __AVR_ATmega2560__	Arduino Mega ATmega2560
 *******************************************************************************/

#if defined(__XHW__)\
	&& (defined(__AVR_ATmega1280__)\
	|| defined(__AVR_ATmega2560__))

#define __XUnoShield__

/// Arduino Uno/2009 shield on Arduino Mega (8bit parallel LCD interface)
class XUnoShield : public XLCDBus8
{
public:
	/// Constructor
	/// @param freq Target frequency
	XUnoShield(uint32_t freq = 0);

protected:
	/// Initializes the interface
	virtual void OnInit() override;
	/// Write bus data
	/// @param data Bus data
	virtual void OnWriteBus(uint8_t data);

private:
	// Delete copy constructor and assignment operator
	XUnoShield(const XUnoShield&) = delete;
	XUnoShield& operator=(const XUnoShield&) = delete;
};

#endif // __XHW__
#endif
