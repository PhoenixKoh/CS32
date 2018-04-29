#include "CarMap.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	CarMap carMap;
	assert(carMap.fleetSize() == 0);
	// addCar(), gas()
	std::string license1 = "APTX";
	assert(carMap.gas(license1) == -1 && carMap.addCar(license1));
	assert(carMap.fleetSize() == 1 && !carMap.addCar(license1) && carMap.gas(license1) == 0);
	std::string license2 = "4869";
	assert(carMap.addCar(license2) && carMap.fleetSize() == 2);
	// addGas(), useGas()
	assert(!carMap.addGas("abc", 3) && !carMap.useGas("abc", 3));
	assert(carMap.addGas(license1, 3) && !carMap.useGas(license2, 3));
	assert(carMap.gas(license1) == 3 && carMap.gas(license2) == 0);
	assert(!carMap.useGas(license1, 5) && carMap.addGas(license2, 3));
	assert(carMap.gas(license1) == 3 && carMap.gas(license2) == 3);
	assert(carMap.useGas(license1, 2) && carMap.addGas(license2, 3));
	assert(carMap.gas(license1) == 1 && carMap.gas(license2) == 6);
	assert(carMap.fleetSize() == 2);
	carMap.print();
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
}