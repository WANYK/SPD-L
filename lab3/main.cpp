#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "RandomNumberGenerator.h"
#include <algorithm>

using namespace std;

struct Zadanie
{
	int indx;
	int p_j;
	int w_j;
	int d_j;
};

void Wyswietl(vector<Zadanie> z1)
{
	cout << "nr: [ ";
	for(int i=0; i<z1.size(); i++)
	{
		cout << z1[i].indx << " ";
	}
	cout << "]" << endl;

	cout << "p = [ ";
	for(int i=0; i<z1.size(); i++)
	{
		cout << z1[i].p_j << " ";
	}
	cout << "]" << endl;

	cout << "w = [ ";
	for(int i=0; i<z1.size(); i++)
	{
		cout << z1[i].w_j << " ";
	}
	cout << "]" << endl;

	cout << "d = [ ";
	for(int i=0; i<z1.size(); i++)
	{
		cout << z1[i].d_j << " ";
	}
	cout << "]" << endl;
}

int Kryt(vector<Zadanie> z1)
{
	int S[z1.size()];
	int C[z1.size()];
	int T[z1.size()];
	int F;

	S[0] = 0;
	C[0] = z1[0].p_j;
	T[0] = max(C[0] - z1[0].d_j, 0);
	F=T[0]*z1[0].w_j;
	for(int i = 1; i<z1.size(); i++)
	{
		S[i] = C[i-1];
		C[i] = S[i]+z1[i].p_j;
		T[i] = max(C[i]-z1[i].d_j, 0);
		F+=T[i]*z1[i].w_j;
		//cout << "S= " << S[i] << " C= " << C[i] << " T= " << T[i] << endl;
	}

	return F;
}

vector<Zadanie> Sort_it(vector<Zadanie> z1)
{
	vector<Zadanie> wynik = z1;

	for(int i = 0; i<wynik.size(); i++)
	{
		for(int j=0; j<wynik.size(); j++)
		{
			if(wynik[j].d_j >= wynik[i].d_j)
			{
				swap(wynik[j], wynik[i]);
			}
		}
	}
	return wynik;
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

	Zadanie* quest = new Zadanie [wlk];

	vector<Zadanie> quest2;
	vector<Zadanie> wynik;
	int i, X;
	int A = 0;
	char x;

	for(i=0; i<wlk; i++)
	{
		quest[i].indx = i+1;
		quest[i].p_j = r1.nextInt(1,29);
		A+=quest[i].p_j;
	}

	for(i=0; i<wlk; i++)
	{
		quest[i].w_j = r1.nextInt(1,9);
	}
	cout << "Wybierz param X: 1 -> A, else -> 29: ";
	cin >> x;
	switch(x)
	{
		case '1':
		X = A;
		break;
		default:
		X = 29;
		break;
	}
	for(i=0; i<wlk; i++)
	{
		quest[i].d_j = r1.nextInt(1,X);
	}

	for(i=0; i<wlk; i++)
	{
		quest2.push_back(quest[i]);
	}

	delete [] quest ;
	Wyswietl(quest2);
	//Wyswietl(Sort_it(quest2));
	cout << "neutral WiTi sum = " << Kryt(quest2) << endl;
	cout << "greedy WiTi sum = " << Kryt(Sort_it(quest2)) << endl;
	return 0;
}