/*******************************************************************************
 * XEvent.h
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

#ifndef XEvent_h
#define XEvent_h

/// Events
enum class XEvents : uint8_t
{
	/// Close
	Close,
	/// Select next input
	Next,
	/// Select previous input
	Previous,
	/// Pushing
	Push,
	/// Releasing
	Release,
	/// Dragging
	Drag,
	/// Input
	Input,
	/// No event
	None
};

#define X_NoId 0xFFFF

// Forwarded symbols
class XEvent;

/// Event pool base class
class XEventPool
{
public:
	/// Destructor
	virtual ~XEventPool() { }

	/// Poll an available event
	virtual XEvent PollEvent() = 0;
};

// ********************************************************************************

/// Event class
class XEvent
{
public:
	/// Constructor
	/// @param event Event
	/// @param location Location of the event
	XEvent(XEvents event, const XPoint& location = X_InvalidPoint)
	{
		m_event = event;
		m_location = location;
		m_id = X_NoId;
	}
	
	/// Constructor
	/// @param id Input ID
	XEvent(uint16_t id)
		: XEvent(XEvents::Input)
	{
		m_id = id;
	}
	
	/// Sets the event pool
	static void SetPool(XEventPool& pool)
	{
		m_ppool = &pool;
	}

	/// Poll an available event
	static XEvent Poll()
	{
		return m_ppool ? m_ppool->PollEvent() : XEvent(XEvents::None);
	}

	// ********************************************************************************
	
	/// Checks for no event
	inline bool IsNone() const
	{
		return (m_event == XEvents::None);
	}
	
	/// Returns the event
	inline XEvents Event() const
	{
		return m_event;
	}
	
	/// Returns the event
	inline operator XEvents() const
	{
		return m_event;
	}
	
	/// Check for specified event
	/// @param event Event
	inline bool Is(XEvents event) const
	{
		return (m_event == event)
			&& ((event != XEvents::Input) || (m_id != X_NoId));
	}
	
	/// Returns location of the event
	inline XPoint Location() const
	{
		return m_location;
	}
	
	/// Returns location of the event
	inline operator XPoint() const
	{
		return m_location;
	}
	
	/// Returns input ID
	inline uint16_t Id() const
	{
		return Is(XEvents::Input) ? m_id : X_NoId;
	}

private:
	/// Event pool
	static XEventPool* m_ppool;

	/// Event
	XEvents m_event;
	/// Location of the event
	XPoint m_location;
	/// Input ID
	uint16_t m_id;
};

#endif
