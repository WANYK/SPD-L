#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "RandomNumberGenerator.h"
#include <algorithm>

using namespace std;

void Kryt(vector<int*> J, int m)
{
	int S[J.size()][m];
	int C[J.size()][m];
	int j = 0;
	S[0][0] = 0;
	C[0][0] = J[0][0];
	S[0][1] = C[0][0];
	C[0][1] = C[0][0]+J[0][1];
	S[0][2] = C[0][1];
	C[0][2] = C[0][1]+J[0][2];
	for(int i=1; i<J.size(); i++)
	{
		S[i][0] = C[i-1][0];
		S[i][1] = C[i-1][1];
		S[i][2] = C[i-1][2];
		C[i][0] = S[i][0] + J[i][0];
		C[i][1] = (C[i-1][1] > C[i][0] ? C[i-1][1] : C[i][0])+ J[i][1];
		C[i][2] = (C[i-1][2] > C[i][1] ? C[i-1][2] : C[i][1])+ J[i][2];

	}
	cout << "C = ";
	for(int i=0; i<J.size(); i++)
	{
		cout << "[ ";
		for(int j=0; j<m; j++)
		{
			cout << C[i][j] << " ";
		}
		cout << "]";
	}
	cout << endl << "C_max = " << C[J.size()-1][2] << endl;
}


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
	cout << endl;

	Kryt(test1, n);
}