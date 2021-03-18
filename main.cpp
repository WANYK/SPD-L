#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <queue>

using namespace std;

struct Zdarzenie
{
	int r_j;
	int p_j;
	int q_j;
	int indx;


};

void Wyswietl(vector<Zdarzenie> z1,int wlk)
{
	cout << "j = [ ";
	for(int i=0; i<wlk; i++)
	{
		cout << z1[i].indx << " ";
	}
	cout << "]" << endl;

	cout << "p = [ ";
	for(int i=0; i<wlk; i++)
	{
		cout << z1[i].p_j << " ";
	}
	cout << "]" << endl;

	cout << "r = [ ";
	for(int i=0; i<wlk; i++)
	{
		cout << z1[i].r_j << " ";
	}
	cout << "]" << endl;

	cout << "q = [ ";
	for(int i=0; i<wlk; i++)
	{
		cout << z1[i].q_j << " ";
	}
	cout << "]" << endl;
}

int minimum(vector<Zdarzenie> z1, int wlk)
{
	int mm=z1[0].r_j;
	int id;
	for(int i=1; i<wlk; i++)
	{

		if(z1[i].r_j<mm)
		{
			mm=z1[i].r_j;
			id=i;
		}
	}
	//cout << "r: " << mm << endl;
	return mm;
}

int minimum_idx(vector<Zdarzenie> z1, int wlk)
{
	int mm=z1[0].r_j;
	int id = 0;
	for(int i=1; i<wlk; i++)
	{

		if(z1[i].r_j<mm)
		{
			mm=z1[i].r_j;
			id=i;
		}
	}
	//cout << "id_min: " <<id << endl;
	return id;
}

int maximum_idx(vector<Zdarzenie> z1, int wlk)
{
	int mm=z1[0].q_j;
	int id = 0;
	for(int i=1; i<wlk; i++)
	{

		if(z1[i].q_j>mm)
		{
			mm=z1[i].q_j;
			id=i;
		}
	}
	//cout << "id_max: " << id << endl;
	return id;
}

vector<Zdarzenie> Schrage_alg1(vector<Zdarzenie> z1, int wlk)
{
	int k = 0;
	int new_j;
	vector <Zdarzenie> G;
	vector <Zdarzenie> N;
	vector <Zdarzenie> Pi;
	N = z1;
	int t = minimum(N,N.size());
	cout << "C = [ ";
	cout << t << " ";
	
	//cout << "??: " <<(int) N.begin() << endl;
	//cout << G.size() << " " << N.size() << " " << t << endl;
	//cout << G.capacity() << " " << N.capacity() << " " << t << endl; 

	//int lag, bo nie wiem jak napisac funkcje sprawdzajaca pustosc tabeli

	while ( G.size() != 0 || N.size() != 0)
	{
		//cout << "xd" << endl;
		while(N.size() != 0 && minimum(N,N.size()) <=t)
		{
			new_j = minimum_idx(N,N.size());
			G.push_back(N[new_j]);
			N.erase(N.begin()+new_j);
			//cout << N.size() << endl;
			//Wyswietl(N,N.size());
		}
		if(G.size() != 0)
		{
			new_j=maximum_idx(G,G.size());
			//cout <<"idx G: " << new_j << endl;
			//cout << "G1: " << endl;
			//Wyswietl(G,G.size());
			Pi.push_back(G[new_j]);
			//cout << endl;
			G.erase(G.begin()+new_j);
			//cout << "G2: " << endl;
			//Wyswietl(G,G.size());
			t=t+N[new_j].p_j;
			k+=1;
			//cout << "Pi =" << endl;
			//Wyswietl(Pi,Pi.size());
			//cout << endl;
		}
		else t = minimum(N,N.size());
		cout << t << " ";
	}
	cout << "]";
	return Pi;
}


int main()
{
	srand(time(NULL));
	int wlk;
	int A=0;
	int x;

	cout << "Wprowadz wielkosc instancji: ";
	cin >> wlk;
	Zdarzenie* quest = new Zdarzenie [wlk];
	vector<Zdarzenie> quest2;
	vector<Zdarzenie> wynik;
	for(int i=0; i<wlk;i++)
	{
		quest[i].indx = i+1;
		quest[i].p_j=rand()%29+1;
		if(i<29)
		A+=i+1;
	}
	cout << "Wprowadz param X (1 lub 2): ";
	cin >> x;
	switch(x)
	{
		case 1:
		x = 29;
		break;
		case 2:
		x = A;
		break;
		default:
		cout << "Opcja niedostepna" << endl;
		x = 29;
		break;
	}
	for(int i=0; i<wlk;i++)
	{
		quest[i].r_j=rand()%A+1;
		quest[i].q_j=rand()%x+1;
		
	}
	for(int i=0; i<wlk;i++)
	{
		quest2.push_back(quest[i]);
	}
	cout << "Przed algorytmem: " << endl;
	Wyswietl(quest2,wlk);
	wynik=Schrage_alg1(quest2,quest2.size());
	cout << endl;
	cout << "Po algorytmie Schrage 1: " << endl;
	Wyswietl(wynik,wynik.size());
	return 0;
}
