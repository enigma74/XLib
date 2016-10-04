/*******************************************************************************
 * XSDL.h
 * XSDL display can be enabled defining X_SDL in the project
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
