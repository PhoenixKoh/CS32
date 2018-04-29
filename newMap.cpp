#include "newMap.h"
#include <iostream>

Map::Map(int capacity)         // Create an empty map (i.e., one with no key/value pairs)
{
	if (capacity >= 0)
	{
		m_capacity = capacity;
		m_array = new item[m_capacity];
	}
	else
	{
		std::cout << "The capacity of the map should be non-negative";
		exit(1);
	}
}

Map::Map(const Map& other) // copy constructor
{
	m_capacity = other.m_capacity;
	m_size = other.m_size;
	m_array = new item[other.m_capacity];
	for (int i = 0; i < other.m_capacity; i++) // just i < other.m_size??
		m_array[i] = other.m_array[i];
}

Map& Map::operator=(const Map& other) // assignment constructor
{
	if (this != &other) // 1. for statements like s1 = s1;
	{
		m_capacity = other.m_capacity;
		m_size = other.m_size;
		delete [] m_array; // 2. release storage (dynamic allocation)
		m_array = new item[other.m_capacity];
		for (int i = 0; i < other.m_capacity; i++) // just i < other.m_size??
			m_array[i] = other.m_array[i];
	}
	return *this; // 3. return a Map reference
}

Map::~Map() // destructor
{
	delete [] m_array; // Do not miss [], since m_appay's pointee is an ARRAY
}


bool Map::empty() const  // Return true if the map is empty, otherwise false.
{
	return m_size == 0;
}

int Map::size() const   // Return the number of key/value pairs in the map.
{
	return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value)
// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map, or the map has a fixed
// capacity and is full).
{
	int flag = locate(key);
	if ((flag == -1) && (m_size != m_capacity))
	{
		m_array[m_size].key = key;
		m_array[m_size].value = value;
		m_size++; // Do not miss
		return true;
	}
	else
		return false;
}

bool Map::update(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.
{
	int flag = locate(key);
	if (flag != -1)
	{
		m_array[flag].value = value;
		return true;
	}
	else
		return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// If key is not equal to any key currently in the map and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that the key is not already in the map and the map has a fixed
// capacity and is full).
{

	//if (m_size == 0) // could be included in the branch of if (m_size != DEFAULT_MAX_ITEMS)
	//{
	//	m_array[0].key = key;
	//	m_array[0].value = value;
	//	m_size++;
	//	return true;
	//}
	//else
	//{
	//	int flag = -1; // Usage: 1. check if contained, 2. record entry if contained
	//	for (int i = 0; i < m_size; i++)
	//	{
	//		if (m_array[i].key == key)
	//		{
	//			flag = i;
	//			break;
	//		}
	//	}
	//	if (flag != -1)
	//	{
	//		m_array[flag].value = value;
	//		return true;
	//	}
	//	else if (m_size != DEFAULT_MAX_ITEMS)
	//	{
	//		m_array[m_size].key = key;
	//		m_array[m_size].value = value;
	//		m_size++;
	//		return true;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}

	int flag = locate(key);
	if (flag != -1)
	{
		m_array[flag].value = value;
		return true;
	}
	else if (m_size != m_capacity)
	{
		m_array[m_size].key = key;
		m_array[m_size].value = value;
		m_size++;
		return true;
	}
	else
		return false;
}

bool Map::erase(const KeyType& key)
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.
{
	int flag = locate(key);
	if (flag == -1)
		return false;
	else
	{
		if (flag != (m_size - 1)) // Exchange 
		{
			m_array[flag].key = m_array[m_size - 1].key;
			m_array[flag].value = m_array[m_size - 1].value;
		}
		//HOW to set 0 of the any type?
		//KeyType keyAs0;
		//ValueType valueAs0;
		//m_array[m_size - 1].key = keyAs0;
		//m_array[m_size - 1].value = valueAs0;
		m_size--; // Do not forget to update size of Map
		return true;
	}
}

bool Map::contains(const KeyType& key) const
// Return true if key is equal to a key currently in the map, otherwise
// false.
{
	return (locate(key) != -1);
}

bool Map::get(const KeyType& key, ValueType& value) const
// If key is equal to a key currently in the map, set value to the
// value in the map that that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.
{
	int flag = locate(key);
	if (flag == -1)
		return false;
	else
	{
		value = m_array[flag].value;
		return true;
	}
}

bool Map::get(int i, KeyType& key, ValueType& value) const
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of one of the key/value pairs in the map and return
// true.  Otherwise, leave the key and value parameters unchanged and
// return false.  (See below for details about this function.)
{
	if ((0 <= i) && (i < size()))
	{
		key = m_array[i].key;
		value = m_array[i].value;
		return true;
	}
	else
		return false;
}

// HOW to implement WITHOUT creating any additional array or additional Map
void Map::swap(Map& other)
// Exchange the contents of this map with the other one.
{
	Map temp1 = *this;// Call Copy Constructor (default for Map and self-declared for newMap)
	*this = other;// Call Assignment Operator (default for Map and self-declared for newMap)
	other = temp1;
}

// local helper function
int Map::locate(const KeyType& key) const
{
	if (m_size == 0) // Could be omitted
		return -1;
	else
	{
		for (int i = 0; i < m_size; i++)
		{
			if (m_array[i].key == key)
				return i;
		}
		return -1; // Do not miss
	}
}