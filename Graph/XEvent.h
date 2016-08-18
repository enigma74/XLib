/*******************************************************************************
 * XEvent.h
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
