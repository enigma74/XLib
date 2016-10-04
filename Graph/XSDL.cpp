/*******************************************************************************
 * XSDL.cpp
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

#include "XGraph.h"
#include "XSDL.h"

#if defined(X_SDL)

#include "SDL.h"
#include "SDL_render.h"

XSDL::XSDL(XSize size, PCSTR pcaption, bool accelerated)
	: XDisplay(size)
{
	// initialization
	m_init = SDL_Init(SDL_INIT_VIDEO) == 0;
	if (!m_init)
		return;
	// creating window
	m_pw = SDL_CreateWindow(pcaption, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		size.Width, size.Height, SDL_WINDOW_SHOWN);
	if (!m_pw)
		return;
	m_pr = SDL_CreateRenderer(m_pw, -1, accelerated ? SDL_RENDERER_ACCELERATED : SDL_RENDERER_SOFTWARE);
	if (!m_pr)
		return;
	// creating surface
	m_pf = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
	m_ps = SDL_CreateRGBSurface(0, size.Width, size.Height, m_pf->BitsPerPixel,
		m_pf->Rmask, m_pf->Gmask, m_pf->Bmask, m_pf->Amask);
	if (!m_ps)
		return;
	// clearing surface
	Clear();
}

XSDL::~XSDL()
{
	if (!m_init)
		return;
	SDL_FreeFormat(m_pf);
	SDL_FreeSurface(m_ps);
	SDL_DestroyRenderer(m_pr);
	SDL_DestroyWindow(m_pw);
	SDL_Quit();
}

PCSTR XSDL::GetError()
{
	return SDL_GetError();
}

SDL_Rect XSDL::Rect(const XRect& rect)
{
	XPoint l = rect.Location;
	XSize size = rect.Size;
	SDL_Rect r = { l.x, l.y, size.Width, size.Height };
	return r;
}

void XSDL::Clear()
{
	OnBeginFunction();
	OnFill(m_rect, X_Black);
	OnEndFunction();
}

// ********************************************************************************

void XSDL::OnEndSequence()
{
	if (!m_ps)
		return;
	SDL_Texture* pt = SDL_CreateTextureFromSurface(m_pr, m_ps);
	SDL_RenderCopy(m_pr, pt, NULL, NULL);
	SDL_RenderPresent(m_pr);
	SDL_DestroyTexture(pt);
}

void XSDL::OnFill(const XRect& rect, const XColor& color)
{
	if (!m_ps)
		return;
	SDL_Rect r = Rect(rect);
	XColor c = color.To(XColorMode::RGB888);
	SDL_FillRect(m_ps, &r, SDL_MapRGB(m_pf, c.r, c.g, c.b));
}

// ********************************************************************************

XEvent XSDL::PollEvent()
{
	if (!m_ps)
		return XEvents::None;
	SDL_Event se;
	SDL_PumpEvents();
	if (!SDL_PollEvent(&se))
		return XEvents::None;
	switch (se.type)
	{
		case SDL_QUIT:
			return XEvents::Close;
		case SDL_KEYUP:
			switch (se.key.keysym.scancode)
			{
				case SDL_SCANCODE_ESCAPE:
					return XEvents::Close;
				case SDL_SCANCODE_SPACE:
					return XEvents::Release;
				default:
					break;
			}
			break;
		case SDL_KEYDOWN:
			switch (se.key.keysym.scancode)
			{
				case SDL_SCANCODE_TAB:
					return X_GetFlag(se.key.keysym.mod, KMOD_LSHIFT) ? XEvents::Previous : XEvents::Next;
				case SDL_SCANCODE_SPACE:
					return XEvents::Push;
				default:
					break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (se.button.button == SDL_BUTTON_LEFT)
				return XEvent(XEvents::Push, XPoint(se.button.x, se.button.y));
			break;
		case SDL_MOUSEBUTTONUP:
			if (se.button.button == SDL_BUTTON_LEFT)
				return XEvent(XEvents::Release, XPoint(se.button.x, se.button.y));
			break;
		case SDL_MOUSEMOTION:
			if (X_GetFlag(se.motion.state, SDL_BUTTON_LMASK))
				return XEvent(XEvents::Drag, XPoint(se.motion.x, se.motion.y));
			break;
	}
	return XEvents::None;
}

#endif // X_SDL
