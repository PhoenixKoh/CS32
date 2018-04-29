#include "CarMap.h"
#include <iostream>
using namespace std;

CarMap::CarMap()       // Create an empty car map.
{	

}

bool CarMap::addCar(std::string license)
// If a car with the given license plate is not currently in the map, 
// and there is room in the map, add an entry for that car recording
// that it has 0 gallons of gas in it, and return true.  Otherwise,
// make no change to the map and return false.
{
	return m_map.insert(license, 0); // 0 gallons of gas in the car
}

double CarMap::gas(std::string license) const
// If a car with the given license plate is in the map, return the
// number of gallons of gas in its tank; otherwise, return -1.
{
	double flag = -1; // Should be of type int?
	m_map.get(license, flag);
	return flag;
}

bool CarMap::addGas(std::string license, double gallons)
// If no car with the given license plate is in the map or if
// gallons is negative, make no change to the map and return
// false.  Otherwise, increase the number of gallons of gas in the
// indicated car by the gallons parameter and return true.
{
	if (gallons >= 0)
	{
		double temp;
		if (m_map.get(license, temp))
		{
			m_map.update(license, (temp + gallons));
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

bool CarMap::useGas(std::string license, double gallons)
// If no car with the given license plate is in the map or if
// gallons is negative or if gallons > gas(), make no change to the
// map and return false.  Otherwise, decrease the number of gallons
// of gas in the indicated car by the gallons parameter and return
// true.
{
	if (gallons >= 0)
	{
		double temp;
		if (m_map.get(license, temp) && (temp > gallons))
		{
			m_map.update(license, (temp - gallons));
			return true;
		}
		else
			return false;
	}
	else
		return false;

}

int CarMap::fleetSize() const  // Return the number of cars in the CarMap.
{
	return m_map.size();
}

void CarMap::print() const
// Write to cout one line for every car in the map.  Each line
// consists of the car's license plate, followed by one space,
// followed by the number of gallons in that car's tank.  Write
// no other text.
{
	std::string license;
	double gallons;
	for (int i = 0; i < fleetSize(); i++)
	{
		m_map.get(i, license, gallons);
		cout << license << " " << gallons << endl;
	}
}