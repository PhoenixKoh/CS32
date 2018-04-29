#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Map m;  // maps strings to doubles
	assert(m.empty());
	ValueType v = -1234.5;
	assert(!m.get("abc", v) && v == -1234.5); // v unchanged by get failure

	// insert()
	assert(m.insert("xyz", 9876.5));
	assert(m.size() == 1);
	assert(!m.insert("xyz", 9876.5)); // this key has already been added into the map
	assert(m.size() == 1);
	// Treat empty string ("") normally
	assert(!m.get("", v) && v == -1234.5); // v unchanged by get failure
	assert(m.insert("", 9876.5)); 
	assert(m.size() == 2);
	assert(!m.insert("", -1234.5));
	assert(m.size() == 2);
	assert(m.get("", v) && v == 9876.5); // v changed
	assert(m.erase("")); 
	assert(m.size() == 1);
	v = -1234.5;
	assert(!m.get("", v) && v == -1234.5); // v unchanged by get failure
	// update()
	assert(!m.update("abc", 9876.5));
	assert(m.size() == 1);
	assert(m.update("xyz", 5678.9));
	assert(m.size() == 1);
	assert(m.get("xyz", v) && v == 5678.9); // v changed by update() and get() success
	// insertOrUpdate()
	assert(m.insertOrUpdate("xyz", -1234.5));
	assert(m.size() == 1);
	assert(m.get("xyz", v) && v == -1234.5);
	assert(m.insertOrUpdate("abc", 5678.9));
	assert(m.size() == 2);
	assert(m.get("abc", v) && v == 5678.9); 
	assert(m.insertOrUpdate("opq", 2345.6));
	assert(m.size() == 3);
	assert(m.get("abc", v) && v == 5678.9);
	assert(m.get("opq", v) && v == 2345.6);
	// erase()
	assert(!m.erase("abcopqxyz"));
	assert(m.size() == 3);
	assert(m.erase("abc"));
	assert(m.size() == 2);
	assert(!m.get("abc", v) && v == 2345.6); // v unchanged by get failure
	// contains()
	assert(!m.contains("abc"));
	assert(m.contains("opq"));
	assert(m.contains("xyz"));
	// get()
	KeyType k1 = "abc";
	assert(!m.get(-1, k1, v) && k1 == "abc" ); // k1, v unchanged by get failure
	assert(!m.get(m.size(), k1, v) && k1 == "abc"); // k1, v unchanged by get failure
	assert(m.get(1, k1, v) && (k1 == "opq" || k1 == "xyz"));
	KeyType k2;
	assert(m.get(1, k2, v) && k2 == k1);
	// swap()
	Map m2;
	m2.insert("Ethel", 3.538);
	m2.insert("Nancy", 3.538);
	m2.insert("", 4);
	m.swap(m2);
	assert(m.size() == 3 && m.contains("Ethel") && m.contains("Nancy") && m.contains("") && m2.size() == 2 && m2.contains("opq") && m2.contains("xyz"));

	// Copy construcor, assignment operator
	ValueType v2;
	m = Map(m2);
	assert(m.size() == m2.size());
	for (int j = 0; j < m2.size(); j++)
		assert(m.get(j, k1, v) && m2.get(j, k2, v2) && k1 == k2 && v == v2);
	Map m3 = Map(m);
	assert(m3.size() == m.size());
	for (int j = 0; j < m3.size(); j++)
		assert(m.get(j, k1, v) && m3.get(j, k2, v2) && k1 == k2 && v == v2);

}

// Other types

//void test()
//{
//	//Map m;  // maps ints to strings
//	//assert(m.empty());
//	//ValueType v = "Ouch";
//	//assert(!m.get(42, v) && v == "Ouch"); // v unchanged by get failure
//	//m.insert(123456789, "Wow!");
//	//assert(m.size() == 1);
//	//KeyType k = 9876543;
//	//assert(m.get(0, k, v) && k == 123456789 && v == "Wow!");
//	//cout << "Passed all tests" << endl;
//
//
//	Map m;  // maps strings to doubles
//	assert(m.empty());
//	ValueType v = "Ouch";
//	assert(!m.get(1, v) && v == "Ouch"); // v unchanged by get failure
//
//	// insert()
//	assert(m.insert(1, ""));
//	assert(m.size() == 1);
//	assert(!m.insert(1, "Hello World!")); // this key has already been added into the map
//	assert(m.size() == 1);
//	// Treat 0 normally
//	assert(!m.get(0, v) && v == "Ouch"); // v unchanged by get failure
//	assert(m.insert(0, "Hello World!"));
//	assert(m.size() == 2);
//	assert(!m.insert(0, "Good bye World!"));
//	assert(m.size() == 2);
//	assert(m.get(0, v) && v == "Hello World!"); // v unchanged by get failure
//	assert(m.erase(0));
//	assert(m.size() == 1);
//	v = "Good bye World!";
//	assert(!m.get(0, v) && v == "Good bye World!"); // v unchanged by get failure
//	// update()
//	assert(!m.update(2, v));
//	assert(m.size() == 1);
//	assert(m.update(1, "Hello World!"));
//	assert(m.size() == 1);
//	assert(m.get(1, v) && v == "Hello World!"); // v changed by update() and get() success
//	// insertOrUpdate()
//	assert(m.insertOrUpdate(1, "Wonderful World!"));
//	assert(m.size() == 1);
//	assert(m.get(1, v) && v == "Wonderful World!");
//	assert(m.insertOrUpdate(2, "C++"));
//	assert(m.size() == 2);
//	assert(m.get(2, v) && v == "C++");
//	assert(m.insertOrUpdate(3, "Java"));
//	assert(m.size() == 3);
//	assert(m.get(2, v) && v == "C++");
//	assert(m.get(3, v) && v == "Java");
//	// erase()
//	assert(!m.erase(10));
//	assert(m.size() == 3);
//	assert(m.erase(2));
//	assert(m.size() == 2);
//	assert(!m.get(2, v) && v == "Java"); // v unchanged by get failure
//	// contains()
//	assert(!m.contains(2));
//	assert(m.contains(1));
//	assert(m.contains(3));
//	// get()
//	KeyType k1 = -1;
//	assert(!m.get(-1, k1, v) && k1 == -1); // k1, v unchanged by get failure
//	assert(!m.get(m.size(), k1, v) && k1 == -1); // k1, v unchanged by get failure
//	assert(m.get(1, k1, v) && (k1 == 1 || k1 == 3));
//	KeyType k2;
//	assert(m.get(1, k2, v) && k2 == k1);
//	// swap()
//	Map m2;
//	m2.insert(100, "APTX");
//	m2.insert(101, "4869");
//	m2.insert(0, "");
//	m.swap(m2);
//	assert(m.size() == 3 && m.contains(100) && m.contains(101) && m.contains(0) && m2.size() == 2 && m2.contains(1) && m2.contains(3));
//
//	// Copy construcor, assignment operator
//	ValueType v2;
//	m = Map(m2);
//	assert(m.size() == m2.size());
//	for (int j = 0; j < m2.size(); j++)
//		assert(m.get(j, k1, v) && m2.get(j, k2, v2) && k1 == k2 && v == v2);
//	Map m3 = Map(m);
//	assert(m3.size() == m.size());
//	for (int j = 0; j < m3.size(); j++)
//		assert(m.get(j, k1, v) && m3.get(j, k2, v2) && k1 == k2 && v == v2);
//}

int main()
{
	test();
	cout << "Passed all tests" << endl;
}