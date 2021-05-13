#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "RandomNumberGenerator.h"
#include <algorithm>

using namespace std;


int main()
{
	
	long ziarno;
	cout << "Podaj ziarno: ";
	cin >> ziarno;
	RandomNumberGenerator r1(ziarno);

	int wlk;
	cout << "Wprowadz wielkosc instancji: ";
	cin >> wlk;
	int n = 3; //dla dwóch maszyn
	vector<int*> test1;
	for(int i=0; i<wlk; i++)
	{
		int* kkk = new int [n];
		test1.push_back(kkk);

	}

	for(int i = 0; i<wlk; i++)
	{
		for(int j = 0; j<n; j++)
		{
			
			test1[i][j] = r1.nextInt(1,29);
		}
	}
	cout << "p = [ ";
	for(int i = 0; i<wlk; i++)
	{
		cout << "[ ";
		for(int j = 0; j<n; j++)
		{
			cout << test1[i][j] << " ";

		}
		cout << "] ";
	}
	cout <<"]" << endl;
}