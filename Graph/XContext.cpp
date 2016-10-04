/*******************************************************************************
 * XContext.cpp
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
#include "XContext.h"

XContext::XContext(XDisplay& display, const XRect& rect)
	: Display(display)
{
	m_rect = (&display == this) ? rect : Display.m_rect.Fix(rect);
	BackColor = X_Black;
	Color = X_White;
}

// ********************************************************************************

void XContext::Begin()
{
	Display.OnBegin();
}

void XContext::End()
{
	Display.OnEnd();
}

bool XContext::BeginFunction()
{
	if (!Color.IsValid())
		return false;
	Display.OnBeginFunction();
	return true;
}

void XContext::EndFunction()
{
	Display.OnEndFunction();
}

void XContext::Fill(XRect rect, uint8_t alpha)
{
	if (!alpha)
		return;
	rect = m_rect.Fix(rect);
	if (rect.IsEmpty())
		return;
	Display.OnFill(rect, (alpha == 0xFF) ? Color : Color.BlendTo(BackColor, alpha));
}

void XContext::Pixel(XPoint p)
{
	if (!BeginFunction())
		return;
	p = m_rect.Translate(p);
	Fill(p);
	EndFunction();
}

void XContext::OnLine(const XPoint& a, const XPoint& b)
{
	if ((a.x == b.x) || (a.y == b.y))
	{
		Fill(XRect(a, b));
		return;
	}
	XLineRenderer lr(a, b);
	while (lr.Next())
		Fill(lr.Location());
}

void XContext::Line(XPoint a, XPoint b)
{
	if (!BeginFunction())
		return;
	a = m_rect.Translate(a);
	b = m_rect.Translate(b);
	OnLine(a, b);
	EndFunction();
}

void XContext::Rectangle(XRect rect, XRectRadius rr, bool filled)
{
	if (rect.IsEmpty() || !BeginFunction())
		return;
	rect = m_rect.Translate(rect);
	rr = rect.Fix(rr);
	bool topleft = rr.TopLeft();
	bool topright = rr.TopRight();
	bool bottomleft = rr.BottomLeft();
	bool bottomright = rr.BottomRight();
	bool line = (rect.Size.Width <= 2) || (rect.Size.Height <= 2);
	if (filled || line)
	{
		// rounded corners
		if (!line && rr.IsSet())
		{
			XPoint b = rect.Location;
			XPoint e = rect.Ending();
			bool top = topleft || topright;
			bool bottom = bottomleft || bottomright;
			int16_t py = 0xFFFF;
			XArcRenderer ar(rr.r);
			while (ar.Next())
			{
				XPoint l = ar.Location();
				// avoiding double lines
				if (l.y == py)
					continue;
				int16_t dx = rr.r - l.x;
				int16_t dy = rr.r - l.y;
				if (top)
				{
					int16_t x1 = b.x + (topleft ? dx : 0);
					int16_t x2 = e.x - (topright ? dx : 0);
					Fill(XRect(XPoint(x1, b.y + dy), XPoint(x2, b.y + dy)));
				}
				if (bottom)
				{
					int16_t x1 = b.x + (bottomleft ? dx : 0);
					int16_t x2 = e.x - (bottomright ? dx : 0);
					Fill(XRect(XPoint(x1, e.y - dy), XPoint(x2, e.y - dy)));
				}
			}
			// removing drawn lines
			if (top)
				b.y += rr.r;
			if (bottom)
				e.y -= rr.r;
			if (b.y > e.y)
				return;
			rect = XRect(b, e);
		}
		// remaining
		Fill(rect);
	}
	else
	{
		XPoint b = rect.Location;
		XPoint e = rect.Ending();
		XPoint tl = b;
		XPoint tr = XPoint(e.x, b.y);
		XPoint bl = XPoint(b.x, e.y);
		XPoint br = e;
		// rounded corners
		if (rr.IsSet())
		{
			// centers of corners
			if (topleft)
				tl += XPoint(rr.r, rr.r);
			if (topright)
				tr += XPoint(-rr.r, rr.r);
			if (bottomleft)
				bl += XPoint(rr.r, -rr.r);
			if (bottomright)
				br += XPoint(-rr.r, -rr.r);
			XArcRenderer ar(rr.r);
			while (ar.Next())
			{
				XPoint l = ar.Location();
				if (topleft)
					Fill(tl + XPoint(-l.x, -l.y));
				if (topright)
					Fill(tr + XPoint(l.x, -l.y));
				if (bottomleft)
					Fill(bl + XPoint(-l.x, l.y));
				if (bottomright)
					Fill(br + XPoint(l.x, l.y));
			}
			// moving lines away from arcs
			if (topleft)
				tl += XPoint(1, 1);
			if (topright)
				tr += XPoint(-1, 1);
			if (bottomleft)
				bl += XPoint(1, -1);
			if (bottomright)
				br += XPoint(-1, -1);
		}
		// lines
		Fill(XRect(XPoint(tl.x, b.y), XPoint(tr.x, b.y)));
		Fill(XRect(XPoint(bl.x, e.y), XPoint(br.x, e.y)));
		Fill(XRect(XPoint(b.x, tl.y), XPoint(b.x, bl.y)));
		Fill(XRect(XPoint(e.x, tr.y), XPoint(e.x, br.y)));
	}
	EndFunction();
}

void XContext::Ellipse(XPoint c, uint16_t rx, uint16_t ry, bool filled)
{
	if (!rx || !ry || !BeginFunction())
		return;
	c = m_rect.Translate(c);
	int16_t py = 0x7FFF;
	XArcRenderer ar(rx, ry);
	while (ar.Next())
	{
		XPoint l = ar.Location();
		if (filled)
		{
			// avoiding double lines
			if (l.y == py)
				continue;
			py = l.y;
			int16_t w = l.x * 2 + 1;
			Fill(XRect(c - l, XSize(w, 1))); // top
			// skipping double center line
			if (l.y)
				Fill(XRect(c + XPoint(-l.x, l.y), XSize(w, 1))); // bottom
			continue;
		}
		Fill(c + XPoint(-l.x, -l.y)); // top left
		Fill(c + XPoint(l.x, -l.y)); // top right
		// skipping first point equal to ending
		if (!l.y)
			continue;
		Fill(c + XPoint(-l.x, l.y)); // bottom left
		Fill(c + XPoint(l.x, l.y)); // bottom right
	}
	EndFunction();
}

void XContext::Triangle(XPoint a, XPoint b, XPoint c, bool filled)
{
	if (!BeginFunction())
		return;
	a = m_rect.Translate(a);
	b = m_rect.Translate(b);
	c = m_rect.Translate(c);
	// check for lined points
	bool x = (a.x != b.x) || (b.x != c.x);
	bool y = (a.y != b.y) || (b.y != c.y);
	if (!x || !y)
	{
		XPoint l = a;
		XPoint e = a;
		if (x)
		{
			l.x = XMin(a.x, b.x, c.x);
			e.x = XMax(a.x, b.x, c.x);
		}
		if (y)
		{
			l.y = XMin(a.y, b.y, c.y);
			e.y = XMax(a.y, b.y, c.y);
		}
		Fill(XRect(l, e));
	}
	else if (filled)
	{
		if (a.y > b.y)
			XSwap(a, b);
		if (b.y > c.y)
			XSwap(b, c);
		if (a.y > b.y)
			XSwap(a, b);
		bool top = a.y == b.y;
		bool swap = top ? (a.x > b.x) : (b.DistanceFromLine(a, c) < 0);
		XLineRenderer lra;
		XLineRenderer lrb;
		(swap ? lrb : lra).Init(a, top ? c : b);
		(swap ? lra : lrb).Init(top ? b : a, c);
		// c point falling next function
		bool initc = false;
		auto _Next = [b, c, &initc](XLineRenderer &_lr) -> bool
		{
			if (_lr.Next())
				return true;
			if (initc)
				return false;
			initc = true;
			_lr.Init(b, c);
			return _lr.Next();
		};
		// next point calculation function
		auto _NextPoint = [&_Next](XLineRenderer &_lr, bool &_next, XPoint &_l, bool max)
		{
			// finding current y minimum/maximum x from first line
			while (_next)
			{
				_l = _lr.Location();
				_next = _Next(_lr);
				if (!_next)
					return;
				XPoint tmp = _lr.Location();
				if (!_l.IsValid())
				{
					_l = tmp;
					continue;
				}
				if (tmp.y != _l.y)
					return;
				_l.x = max
					? XMax(_l.x, tmp.x)
					: XMin(_l.x, tmp.x);
			}
		};
		// drawing triangle
		XPoint la = X_InvalidPoint;
		XPoint lb = X_InvalidPoint;
		bool nexta = true;
		bool nextb = true;
		do
		{
			_NextPoint(lra, nexta, la, false);
			_NextPoint(lrb, nextb, lb, true);
			Fill(XRect(la, lb));
		} while (nexta || nextb);
	}
	else
	{
		OnLine(a, b);
		OnLine(b, c);
		OnLine(c, a);
	}
	EndFunction();
}

XSize XContext::IconSize(const XData& icon)
{
	return XIconRenderer(XRect(), &icon).Size();
}

void XContext::Icon(XRect rect, const XData& icon)
{
	if (!icon.Size() || !BeginFunction())
		return;
	rect = m_rect.Translate(rect);
	XIconRenderer ir(rect, &icon);
	while (ir.Next())
	{
		uint8_t alpha = ir.Alpha();
		if (alpha)
			Fill(ir.Location(), alpha);
	}
	EndFunction();
}

XSize XContext::TextSize(const XText& text, XSize max)
{
	XRect rect(max);
	if (rect.IsEmpty())
		rect.Size = XSize(0xFFFF, 0xFFFF);
	return XTextRenderer(rect, &text).Size();
}

void XContext::Text(XRect rect, const XText& text)
{
	if (rect.IsEmpty() || text.Value.IsEmpty() || !BeginFunction())
		return;
	rect = m_rect.Translate(rect);
	XTextRenderer tr(rect, &text);
	while (tr.Next())
	{
		uint8_t alpha = tr.Alpha();
		if (alpha)
			Fill(tr.Location(), alpha);
	}
	EndFunction();
}
