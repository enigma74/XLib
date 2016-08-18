/*******************************************************************************
 * XSDL.h
 * XSDL display can be enabled defining X_SDL in the project
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

#ifndef XSDL_h
#define XSDL_h

#if defined(X_SDL)
	#include "SDL.h"
	#if SDL_MAJOR_VERSION < 2
		#undef X_SDL
	#endif
#endif
#if defined(X_SDL)

#define delay(ms) SDL_Delay(ms)

/// Test display emulation
class XSDL : public XDisplay, public XEventPool
{
public:
	/// Constructor
	/// @param size Display size
	/// @param pcaption Window caption
	/// @param accelerated Hardware accelerated flag
	XSDL(XSize size, PCSTR pcaption = NULL, bool accelerated = true);
	/// Destructor
	~XSDL();

	/// Checks for init status
	inline bool IsInit() const
	{
		return m_ps;
	}
	
	/// Returns the error
	PCSTR GetError();
	/// Clears the display
	void Clear();
	/// Poll an available event
	virtual XEvent PollEvent() override;
	
private:
	/// Init flag
	bool m_init = false;
	/// Window pointer
	SDL_Window* m_pw = NULL;
	/// Renderer pointer
	SDL_Renderer* m_pr = NULL;
	/// Pixel format pointer
	SDL_PixelFormat* m_pf = NULL;
	/// Texture surface pointer
	SDL_Surface* m_ps = NULL;

	/// Transform XRect to SDL_Rect
	SDL_Rect Rect(const XRect& rect);
	
	/// Ends a drawing sequence
	virtual void OnEndSequence() override;
	
	/// Fills a rectangle
	/// @param rect Display rectangle
	/// @param color Color to use
	virtual void OnFill(const XRect& rect, const XColor& color) override;
};

#endif // X_SDL
#endif
