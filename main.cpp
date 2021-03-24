#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
//#include "RandomNumberGenerator.h"
#include <cmath>


using namespace std;

class RandomNumberGenerator
{
private:

	long seed;

public:
	RandomNumberGenerator(long seedValue) :
		seed(seedValue)
	{}
	int nextInt(int low, int high) {
		long k;
		double value_0_1;
		long m = 2147483647l, a = 16807l, b = 127773l, c = 2836l;

		k = seed / b;
		seed = a * (seed % b) - k * c;
		if (seed < 0)
			seed = seed + m;
		value_0_1 = seed;
		value_0_1 /= m;
		return low + (int)floor(value_0_1 * (high - low + 1));
	}
	float nextFloat(int low, int high) {
		low *= 100000;
		high *= 100000;
		float val = nextInt(low, high) / 100000.0;
		return val;
	}
};

enum Tryb {a, b}; //Tryb pracy algorytmu Schrage1 bez sortowania i z

struct Zdarzenie // Struktura zadania
{
	int r_j;	//czas wykonania zadania
	int p_j;	//czas przygotowania zadania
	int q_j;	//czas przedawnienia zadania
	int indx;	//nr zadania
};

struct Element
{
	Zdarzenie elem;
	Element* nast;

};

//Funkcja wyswietlajaca zawartosc wektora z zadaniami
void Wyswietl(vector<Zdarzenie> z1);

//Funkcja znajdujaca Zdarzenie z najmniejszym parametrem r
int min_r(vector<Zdarzenie> z1);

//Funkcja znajdujaca indeks zdarzenia o najmniejszym parametrze r
int min_r_idx(vector<Zdarzenie> z1);

//Funkcja znajdujaca indeks zdarzenia o najwiekszym parametrze q
int max_q_idx(vector<Zdarzenie> z1);

//Sortowanie Zadan na podstawie najmniejszego r
void sort_r(vector<Zdarzenie> &z1);

//Algorytm Schrage
vector<Zdarzenie> Schrage_alg1(vector<Zdarzenie> z1, Tryb tt);

//Kryterium optymalizacyjne, czyli czas zakonczenia wszystkich zadan i opuszczenia ich przez system
void Kryt(vector<Zdarzenie> &wynik);

//Algorytm Schrage2 z możliwością przerwań
vector<Zdarzenie> Schrage_alg2(vector<Zdarzenie> z1);



int main()
{
	long ziarno;
	cout << "Podaj ziarno: ";
	cin >> ziarno;
	RandomNumberGenerator r1(ziarno);
	srand(time(NULL));
	int wlk;
	int A=0;
	int x, i;
	
	cout << "Wprowadz wielkosc instancji: ";
	cin >> wlk;
	Zdarzenie* quest = new Zdarzenie [wlk];
	
	vector<Zdarzenie> quest2;
	vector<Zdarzenie> wynik;

	for(i = 0; i<wlk;i++)
	{
		quest[i].indx = i+1;
		quest[i].p_j=r1.nextInt(1,29);
		A+=quest[i].p_j;
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
	for(i=0; i<wlk;i++)
	{
		quest[i].r_j=r1.nextInt(1,A);
	}

	for(i=0; i<wlk;i++)
	{
		quest[i].q_j=r1.nextInt(1,x);
	}

	for(i=0; i<wlk;i++)
	{
		quest2.push_back(quest[i]);
	}

	delete [] quest;

	cout << "Przed algorytmem: " << endl;
	Wyswietl(quest2);
	Kryt(quest2);
	
	wynik=Schrage_alg1(quest2,a);
	cout << endl;
	cout << "Po algorytmie Schrage 1: " << endl;
	Wyswietl(wynik);
	Kryt(wynik);

	/*sort_r(quest2);
	cout << "Przed algorytmem: " << endl;
	Wyswietl(quest2);
	Kryt(quest2);*/

	wynik=Schrage_alg1(quest2,b);
	cout << endl;
	cout << "Po algorytmie Schrage 1 z sortowaniem: " << endl;
	Wyswietl(wynik);
	Kryt(wynik);


	wynik=Schrage_alg2(quest2);
	cout << endl;
	cout << "Po algorytmie Schrage z podzialem: " << endl;
	Wyswietl(wynik);
	Kryt(wynik);
	return 0;
}

//WSZYSTKIE FUNKCJE

//Funkcja wyswietlajaca zawartosc wektora z zadaniami
void Wyswietl(vector<Zdarzenie> z1)
{
	cout << "j = [ ";
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

	cout << "r = [ ";
	for(int i=0; i<z1.size(); i++)
	{
		cout << z1[i].r_j << " ";
	}
	cout << "]" << endl;

	cout << "q = [ ";
	for(int i=0; i<z1.size(); i++)
	{
		cout << z1[i].q_j << " ";
	}
	cout << "]" << endl;
}

//Funkcja znajdujaca Zdarzenie z najmniejszym parametrem r
int min_r(vector<Zdarzenie> z1)
{
	int mm=z1[0].r_j;
	int id = 0;
	for(int i=1; i<z1.size(); i++)
	{
		if(z1[i].r_j<mm)
		{
			mm=z1[i].r_j;
			id=i;
		}
	}
	return mm;
}

//Funkcja znajdujaca indeks zdarzenia o najmniejszym parametrze r
int min_r_idx(vector<Zdarzenie> z1)
{
	int mm=z1[0].r_j;
	int id = 0;
	for(int i=1; i<z1.size(); i++)
	{
		if(z1[i].r_j<mm)
		{
			mm=z1[i].r_j;
			id=i;
		}
	}
	return id;
}

//Funkcja znajdujaca indeks zdarzenia o najwiekszym parametrze q
int max_q_idx(vector<Zdarzenie> z1)
{
	int mm=z1[0].q_j;
	int id = 0;
	for(int i=1; i<z1.size(); i++)
	{
		if(z1[i].q_j>mm)
		{
			mm=z1[i].q_j;
			id=i;
		}
	}
	return id;
}

void sort_r(vector<Zdarzenie> &z1)
{
	for(int i=0; i<z1.size(); i++)
	{
		for(int j = 0; j<z1.size(); j++)
		{
			if(z1[j].r_j>z1[i].r_j)
			{
				swap(z1[j],z1[i]);
			}
		}
	}
}

vector<Zdarzenie> Schrage_alg1(vector<Zdarzenie> z1, Tryb tt)
{
	int k = 0;
	int new_j;
	vector <Zdarzenie> G;
	vector <Zdarzenie> N = z1;
	vector <Zdarzenie> Pi;
	switch(tt)
	{
		case a:
		break;
		case b:
		sort_r(N);
		break;
		default:
		exit(0);
		break;
	}
	int t = min_r(N);
	while ( G.size() != 0 || N.size() != 0)
	{
		while(N.size() != 0 && min_r(N) <=t)
		{
			new_j = min_r_idx(N);
			G.push_back(N[new_j]);
			N.erase(N.begin()+new_j);
		}
		if(G.size() != 0)
		{
			new_j=max_q_idx(G);
			Pi.push_back(G[new_j]);
			G.erase(G.begin()+new_j);
			t=t+N[new_j].p_j;
			k+=1;
		}
		else t = min_r(N);
	}
	return Pi;
}

void Kryt(vector<Zdarzenie> &wynik)
{
	int* S = new int [wynik.size()];
	int* C = new int [wynik.size()];
	int C_max, i;

	S[0] = wynik[0].r_j;
	C[0] = S[0] + wynik[0].p_j;
	C_max = C[0] + wynik[0].q_j;

	for(i = 1; i<wynik.size(); i++)
	{
		S[i] = wynik[i].r_j > C[i-1] ? wynik[i].r_j : C[i-1];
		C[i] = S[i] + wynik[i].p_j;
		C_max = C_max > C[i] + wynik[i].q_j ? C_max : C[i] + wynik[i].q_j;
	}

	cout << endl << "C_max = " << C_max << endl << endl;
	cout << "indx\tS_j\tC_j\tC_j+q_j" << endl;
	for(i = 0; i<wynik.size(); i++)
	{
		cout << i+1 << "\t" << S[i] << "\t" << C[i] << "\t" << C[i] + wynik[i].q_j << endl;
	}
	cout << endl;
	delete [] S;
	delete [] C;
}

vector<Zdarzenie> Schrage_alg2(vector<Zdarzenie> z1)
{
	int k = 0;
	int new_j;
	vector <Zdarzenie> G;
	vector <Zdarzenie> N = z1;
	vector <Zdarzenie> Pi;
	vector <Zdarzenie> tmp;
	int t = min_r(N);
	int t1;
	//cout << "t = [ "<< t << " ";
	
	//cout << "??: " <<(int) N.begin() << endl;
	//cout << G.size() << " " << N.size() << " " << t << endl;
	//cout << G.capacity() << " " << N.capacity() << " " << t << endl; 

	while ( G.size() != 0 || N.size() != 0)
	{
		//cout << "xd" << endl;
		while(N.size() != 0 && min_r(N) <=t)
		{
			new_j = min_r_idx(N);
			G.push_back(N[new_j]);
			N.erase(N.begin()+new_j);
			//cout << N.size() << endl;
			//Wyswietl(N,N.size());
		}
		if(G.size() != 0)
		{
			t1=t+G[new_j].p_j;
			new_j=max_q_idx(G);
			cout << "t = " << t << endl;
			t=t+N[new_j].p_j;
			
			cout << "t1 = " << t1 <<" r = "<< N[new_j].p_j<< endl;
			//cout << "t = " << t << endl;
			for(int kk = 0; kk <N.size(); kk++)
			{
				if(t>N[kk].r_j)
				{
					cout << t << " " << N[kk].r_j << endl;
					tmp.push_back(G[new_j]);
					tmp[0].p_j = t - N[kk].r_j;
					G.push_back(N[kk]);
					G.push_back(tmp[0]);
					N.erase(N.begin()+kk);
					tmp.erase(tmp.begin());
				}
			}

			//cout <<"idx G: " << new_j << endl;
			//cout << "G1: " << endl;
			//Wyswietl(G);
			Pi.push_back(G[new_j]);

			//cout << endl;
			G.erase(G.begin()+new_j);
			//cout << "G2: " << endl;
			//Wyswietl(G,G.size());
			
			k+=1;
			//cout << "Pi =" << endl;
			//Wyswietl(Pi,Pi.size());
			//cout << endl;
		}
		else t = min_r(N);
		//cout << t << " ";
	}
	//cout << "]";
	return Pi;
}