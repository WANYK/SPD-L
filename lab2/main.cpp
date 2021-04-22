#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "RandomNumberGenerator.h"
#include <algorithm>

using namespace std;

/*class Zadanie
{
	int idx;
	int C;
};*/

int min_idx(vector<int*> N, int m)
{
	int idx = 0;
	int buf = N[0][0];
	for(int i=0; i<N.size();i++)
	{
		for(int j=0; j<m; j++)
		{
			if(N[i][j]<buf)
			{
				buf=N[i][j];
				idx = i;
			}
		}
	}
	return idx;	
}
void Kryt(vector<int*> J, int m)
{
	int S[J.size()][m];
	int C[J.size()][m];
	int j = 0;
	S[0][0] = 0;
	C[0][0] = J[0][0];
	S[0][1] = C[0][0];
	C[0][1] = C[0][0]+J[0][1];
	for(int i=1; i<J.size(); i++)
	{
		S[i][0] = C[i-1][0];
		S[i][1] = C[i-1][1];
		C[i][0] = S[i][0] + J[i][0];
		C[i][1] = (C[i-1][1] > C[i][0] ? C[i-1][1] : C[i][0])+ J[i][1];
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
	cout << endl << "C_max = " << C[J.size()-1][1] << endl;
}
void Johnson(vector<int*> J, int m)
{
	int Pi[J.size()];
	int l = 0;
	int k = J.size()-1;
	int z = J.size();
	int tmp[J.size()][m];
	while(z>0)
	{
		int ii = min_idx(J,m);
		if(J[ii][0] < J[ii][m-1])
		{
			
			Pi[l] = ii+1;
			tmp[l][0] = J[ii][0];
			tmp[l][m-1] = J[ii][m-1];
			l++;	
		}
		else
		{
			Pi[k] = ii+1;
			tmp[k][0] = J[ii][0];
			tmp[k][m-1] = J[ii][m-1];
			k--;
		}
		J[ii][0] = 99;
		J[ii][m-1] = 99;
		z--;
	}
	cout << "Pi = [ ";
	for(int s=0; s<J.size(); s++)
	{
		cout << Pi[s] << " ";
	}
	cout << "]" << endl;
	for(int i = 0; i<J.size(); i++)
	{
		for(int j = 0; j<m; j++)
		{
			J[i][j] = tmp[i][j];
		}
	}
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
	int n = 2; //dla dwóch maszyn
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
	Johnson(test1, n);
	Kryt(test1,n);
	return 0;
}