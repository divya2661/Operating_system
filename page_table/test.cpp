#include <iostream>
#include <vector>
using namespace std;  

int main()
{
	vector< vector<int> > buff;

	// To set values
	for(int i = 0; i < 10; i++)
	{
		vector<int> temp; // create an array, don't work directly on buff yet.
		for(int j = 0; j < 10; j++)
			temp.push_back(i); 
 
		buff.push_back(temp); // Store the array in the buffer
	}

	//To access values
	for(vector<vector<int> >::iterator it = buff.begin(); it != buff.end(); ++it)
	{
		//it is now a pointer to a vector<int>
		for(vector<int>::iterator jt = it->begin(); jt != it->end(); ++jt)
		{
			// jt is now a pointer to an integer.
			cout << *jt;
		}
		cout << endl;
	}

	return 0;
}