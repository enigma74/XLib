/*******************************************************************************
 * XArray.h
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

#ifndef XArray_h
#define XArray_h

#include <stdlib.h>
#include <string.h>

/// Template class for dynamic arrays of items
/// @param T Type of items
template<class T> class XArray
{
public:
	/// Constructor
	/// @param count Number of initial items
	XArray(int count = 0)
	{
		m_count = 0;
		m_items = NULL;
		Resize(count);
	}

	/// Destructor
	virtual ~XArray()
	{
		Resize(0);
	}

	/// Resizes the array
	/// @param count Number of items
	/// @param maintain Flag to maintain previous content
	bool Resize(int count, bool maintain = true)
	{
		bool ok = true;
		if (count < 0)
			count = 0;
		size_t size = count * sizeof(T);
		if (count != m_count)
		{
			if (count > 0)
			{
				T* p = (T*)realloc(m_items, size);
				ok = (p != NULL);
				if (ok)
				{
					m_count = count;
					m_items = p;
				}
			}
			else if (m_items)
			{
				free(m_items);
				m_count = 0;
				m_items = NULL;
			}
		}
		if (ok && m_items && !maintain)
			memset(m_items, 0, size);
		return ok;
	}

	/// Clears the array
	void Clear()
	{
		Resize(0);
	}

	/// Return the number of items contained
	inline int Count() const
	{
		return m_count;
	}

	/// Adds an item to the array
	/// @param item Item to add
	int Add(T item)
	{
		int index = m_count;
		if (!Resize(m_count + 1))
			return -1;
		m_items[index] = item;
		return index;
	}

	/// Returns the index of the specified item
	/// @param item Item to search
	int IndexOf(T item) const
	{
		int index = -1;
		for (int i = 0; i < m_count; i++)
			if (memcmp(&m_items[i], &item, sizeof(T)) == 0)
			{
				index = i;
				break;
			}
		return index;
	}

	/// Removes the item at the specified postition
	/// @param index Index of the item
	void RemoveAt(int index)
	{
		if (!VerifyIndex(index))
			return;
		int copy = m_count - index - 1;
		if (copy)
			memcpy(&m_items[index], &m_items[index + 1], (copy * sizeof(T)));
		m_count--;
		Resize(m_count);
	}

	/// Removes the specified item
	/// @param item Item to delete
	void Remove(T item)
	{
		RemoveAt(IndexOf(item));
	}

	/// Gets the item at the specified position
	/// @param index The index of the item
	inline T operator[](int index) const
	{
		return VerifyIndex(index) ? m_items[index] : T();
	}

	/// Gets the reference to the item at the specified position
	/// @param index The index of the item
	inline T& operator[](int index)
	{
		return VerifyIndex(index) ? m_items[index] : (m_default = T());
	}

protected:
	/// The number of items contained
	int m_count;
	/// Items
	T* m_items;
	/// The default item
	T m_default;

	/// Verify the index
	/// @param index Index
	inline bool VerifyIndex(int index) const
	{
		return ((index >= 0) && (index < m_count));
	}

private:
	// Delete copy constructor and assignment operator
	XArray(const XArray&) = delete;
	XArray& operator=(const XArray&) = delete;
};

#endif
