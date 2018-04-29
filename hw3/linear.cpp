//#include <iostream>
//#include <cassert>
//
//bool somePredicate(double x)
//{
//	return x >= 0;
//}

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const double a[], int n)
{
	if (n <= 0) // What about NEGATIVE n?
		return true;
	// What about n larger than a.size()?
	if (!somePredicate(a[n-1]))
		return false;
	else
		return allTrue(a, (n-1));
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const double a[], int n)
{
	if (n <= 0)
		return 0;
	if (!somePredicate(a[n-1]))
		return 1 + countFalse(a, n-1);
	else
		return countFalse(a, n-1);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const double a[], int n)
{
	if (n <= 0)
		return -1;
	
	// last-rest divide conquer
	if (!somePredicate(a[n-1]))
	{
		int temp = firstFalse(a, n-1); // to reduce recursive calls 
		if (temp == -1)
			return n-1;
		else
			return temp;
	}
	else
		return firstFalse(a, n-1);
		
	// fisrt-rest divide conquer
	//if (!somePredicate(a[0]))
	//	return 0;
	//else
	//{
	//	int temp = firstFalse(a + 1, n - 1); 
	//	if (temp == -1)
	//		return -1;
	//	else
	//		return 1 + temp;
	//}
}

// Return the subscript of the smallest double in the array (i.e.,
// the one whose value is <= the value of all elements).  If more
// than one element has the same smallest value, return the smallest
// subscript of such an element.  If the array has no elements to
// examine, return -1.
int indexOfMin(const double a[], int n)
{
	if (n <= 0)
		return -1;

	int temp = indexOfMin(a, n-1);
	if (temp == -1 || a[temp] > a[n-1]) // strictly greater than for multiple minimum points
		return n-1;
	else
		return temp;

	//int temp = 1 + indexOfMin(a + 1, n - 1); // grater than -1!!
	//if (a[0] <= a[temp]) // strictly greater than for multiple minimum points
	//	return 0;
	//else
	//	return temp;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{
	if (n1 <= 0 && n2 > 0)
		return false;
	if (n2 <= 0)
		return true;
	if (a1[n1-1] == a2[n2-1])
		return includes(a1, (n1-1), a2, (n2-1));
	else
		return includes(a1, (n1-1), a2, n2);
}

//int main()
//{
//	double a[6] = { 0, -2, -3, 4, 6, 10};
//	double b[3] = { 0, -2, 3};
//	assert(!allTrue(a, 6));
//	assert(countFalse(a, 6) == 2);
//	assert(firstFalse(a, 6) == 1);
//	assert(indexOfMin(a, 6) == 2);
//	assert(!includes(a, 6, b, 3));
//	assert(includes(a, 6, b, 2));
//	assert(includes(a, 2, b, 2));
//	// corner cases
//	assert(allTrue(a, 0) && allTrue(a, -1));
//	assert(countFalse(a, 0) == 0 && countFalse(a, -1) == 0);
//	assert(firstFalse(a, 0) == -1 && firstFalse(a, -2) == -1);
//	assert(indexOfMin(a, 1) == 0 && indexOfMin(a, 0) == -1 && indexOfMin(a, -1) == -1);
//	assert(includes(a, 0, b, 0) && includes(a, 1, b, -2) && !includes(a, 0, b, 1));
//	a[1] = -a[1];
//	assert(!allTrue(a, 6));
//	assert(countFalse(a, 6) == 1);
//	assert(firstFalse(a, 6) == 2);
//	assert(firstFalse(a, 2) == -1);
//	assert(indexOfMin(a, 6) == 2);
//	assert(indexOfMin(a, 2) == 0);
//	assert(!includes(a, 6, b, 3));
//	assert(!includes(a, 2, b, 2));
//	assert(includes(a, 1, b, 1));
//	b[1] = -b[1];
//	assert(!includes(a, 3, b, 3));
//	assert(includes(a, 2, b, 2));
//	a[2] = -a[2];
//	assert(allTrue(a, 6));
//	assert(countFalse(a, 6) == 0);
//	assert(firstFalse(a, 6) == -1);
//	assert(indexOfMin(a, 6) == 0);
//	assert(includes(a, 6, b, 3));
//	a[5] = -a[5];
//	assert(indexOfMin(a, 6) == 5);
//	//
//	std::cout << "Passed all tests!" << std::endl;
//}