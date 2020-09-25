#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

int main (int argc, char **argv) {
	
	int n;
	cout << "Enter the size of matrix: ";
	cin >> n;
	
	ofstream Matrix("matrix.txt");
	Matrix << n << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			Matrix << rand()%2 << " ";
		Matrix << endl;
	}
	return 0;
}
