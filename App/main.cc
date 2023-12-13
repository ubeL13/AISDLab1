#include <PolyLine.h>
#include <complex>
#include <iostream> 
#include <cmath>

using namespace std;



int main()
{
	
	int N;
	float radius;
	do
	{
		cout << "Enter the number of vertices of the polygon: ";
		cin >> N;
	} while (N <= 2);
	cout << "Enter radius: ";
	cin >> radius;

	BrokenLine<float> poly = polygon(N, radius);
	cout << poly;
	return 0;


}
