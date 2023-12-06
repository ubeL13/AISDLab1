#include <PolyLine.h>
#include <complex>
#include <iostream> 
#include <cmath>

using namespace std;



int main()
{
	
	BrokenLine<int> letter = BrokenLine<int>(7);
	letter[0] = Point<int>(0, 1);
	letter[1] = Point<int>(0, 0);
	letter[2] = Point<int>(1, 0);
	letter[3] = Point<int>(1, 1);
	letter[4] = Point<int>(1, 0);
	letter[5] = Point<int>(2, 0);
	letter[6] = Point<int>(2, 1);
	cout << letter;

	//--------------------------------------------------------------
	return 0;

}
