/*******************************************************************************
 * XAquaLED.h
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

#ifndef XAquaLED_h
#define XAquaLED_h

/*******************************************************************************
 * Supported hardware:
 * __32MX795F512L__		chipKIT MAX32 PIC32MX795F512L
 *******************************************************************************/

#if defined(__XHW__) && defined(__32MX795F512L__)

#define __XAquaLED__

/// AquaLEDSource All in One Super Screw Shield for chipKit Max32 (16bit parallel LCD interface)
class XAquaLED : public XLCDBus16
{
public:
	/// Constructor
	/// @param freq Target frequency
	XAquaLED(uint32_t freq = 0);

protected:
	/// Initializes the interface
	virtual void OnInit() override;
	/// Write bus data
	/// @param data Bus data
	virtual void OnWriteBus(uint16_t data);

private:
	// Delete copy constructor and assignment operator
	XAquaLED(const XAquaLED&) = delete;
	XAquaLED& operator=(const XAquaLED&) = delete;
};

#endif // __XHW__
#endif
