/*******************************************************************************
 * XCTE16.h
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
