#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "RandomNumberGenerator.h"
#include <algorithm>
#include <math.h>

using namespace std;


int Kryt(vector<vector<int>> J)
{
	int S[J.size()][J[0].size()];
	int C[J.size()][J[0].size()];
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
		for(int j=0; j<J[0].size(); j++)
		{
			cout << C[i][j] << " ";
		}
		cout << "]";
	}
	cout << endl << "C_max = " << C[J.size()-1][2] << endl;
	return C[J.size()-1][2];
}
void Wyswietl(vector<vector<int>> J)
{
	cout << "p = [ "; 
	for(int j = 0; j<J.size(); j++)
	{
		cout << "[ ";
		for(int i = 0; i<J[0].size(); i++)
		{
			 cout << J[j][i] << " ";
		}
		cout << "]";
	}
	cout << " ]" << endl;
}
void MNeh(vector<vector<int>> J)
{
	int k = 1;
	vector<vector<int>> test2 = J;
	int W[test2.size()];
	int indexes[J.size()];
	vector<vector<int>> test3;
	vector<vector<int>> test4;
	int mtp;
	int poz = 0;

	//test4.resize(test2.size());
	cout << "[ ";
	for(int i = 0; i< test2.size(); i++)
	{
		W[i] = test2[i][0]+test2[i][1]+test2[i][2];
		indexes[i] = i;
		cout << W[i] << " ";
	}
	cout << "]" << endl;

	for(int i = 0; i<J.size(); i++)
	{
		for(int j = 0; j<J.size(); j++)
		{
			if(W[j]<W[i]){
				swap(W[j],W[i]);
				swap(indexes[j], indexes[i]);
			}
		}
	}
	cout << "[ ";
	for(int i = 0; i< test2.size(); i++)
	{
		cout << indexes[i]+1 << " ";
	}
	cout << "]" << endl;

	while(k<=test2.size())
	{
		test3.insert(test3.begin(), test2[indexes[k-1]]);
		int KrytWsk = Kryt(test3);
		poz = 0;
		for(int l = 0; l<k-1; l++)
		{
			swap(test3[l],test3[l+1]);
			mtp = Kryt(test3);
			if(mtp < KrytWsk)
			{
				KrytWsk = mtp;
				poz = l+1;
			}
		}
		test4.insert(test4.begin()+poz, test2[indexes[k-1]]);
		test3 = test4;
		k++;
	}
	cout << "Wynik algorytmu: " << endl;
	Wyswietl(test4);
	Kryt(test4);

}

void MetaHeurystyka11(vector<vector<int>> J)
{
	vector<vector<int>> KK = J;
	vector<vector<int>> SS = KK;
	vector<vector<int>> Wynik = KK;
	int T0 = Kryt(KK);
	int Tk = T0 - 10;
	int i, j, tmp; 
	double x;
	///int Pi[J.size()];
	vector<int> Pii;
	vector<int> Pi;
	vector<int> Pi_wynik;

	for(int f =0; f<KK.size(); f++)
	{
		//Pi[i] = i;
		Pii.push_back(f);
		//cout << Pii[i] << endl;

	}

	while(T0 > Tk)
	{
		for(int k = 1; k<3; k++)
		{
			i = rand() % SS.size();
			j = rand() % SS.size();
			//cout << "Dane1: "<< i << " " << j << endl;
			while(i == j) j = rand() % SS.size();
			//cout << "Dane2: "<< i << " " << j << endl;
			swap(SS[i], SS[j]);
			swap(Pii[i], Pii[j]);

			if(Kryt(SS) > Kryt(KK))
			{
				tmp = rand() % 10000;
				x = (tmp)/(tmp+(rand()%10000));
				if(x >= exp((Kryt(KK)-Kryt(SS))/(T0)))
				{
					Pii = Pi;
					SS = KK;
				}
			}
			Pi = Pii;
			KK = SS;

			if(Kryt(KK) < Kryt(Wynik))
			{
				Wynik = KK;
				Pi_wynik = Pi;
			}

		}
		T0 -= 1;
	}
	cout << "Wynik metaheurystyki: " <<	endl;
	Kryt(Wynik); 

}


int main()
{
	long ziarno;
	cout << "Podaj ziarno: ";
	cin >> ziarno;
	RandomNumberGenerator r1(ziarno);
	srand(time(NULL));

	int wlk;
	cout << "Wprowadz wielkosc instancji: ";
	cin >> wlk;
	int n = 3;

	vector<vector<int>> test1;
	for(int j = 0; j<wlk; j++)
	{
		vector<int> test11;
		for(int i = 0; i<n; i++)
		{
			test11.push_back(r1.nextInt(1,29));
		}
		test1.push_back(test11);
	}
	Wyswietl(test1);
	cout << "Przed algorytmem: " << endl;
	cout << Kryt(test1) << endl;
	cout << endl << "---------------------" << endl;
	cout << endl << "NEH: " << endl;
	MNeh(test1);
	cout << endl << "---------------------" << endl;
	cout << endl << "Metaheurystyka: " << endl;
	MetaHeurystyka11(test1);

	return 0;
}