#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip> 


using namespace std;
#define R 20;

struct Dane {
	Dane() { id = 0; temp = 0; pojemn = 0; strcpy(nazwa, "brak"); };
	int id;
	char nazwa[10];
	double temp;
	double pojemn;
	friend ostream& operator<< (ostream& out, const Dane& d) {
	
		out << '|' << setw(6) <<setfill('0') << d.id << setfill(' ') <<'|';
	
		out << setw(10) << left << d.nazwa << '|';
		out << setw(7) << showpoint << setprecision(1) << right << fixed << d.temp << '|';
		out << setw(6) << right << setprecision(0) << noshowpoint <<d.pojemn << '|';
		return out;
	}
	Dane& operator += (const Dane& d) {
		id += d.id;
		temp += d.temp;
		pojemn += d.pojemn;
		return *this;
	}
};

template <typename T, int rozmiar>
class Tablica {
	T A[rozmiar];
public:
	T& operator[](int index);
};

template <typename T, int rozmiar>
T& Tablica<T, rozmiar>::operator[](int index)
{
	if (index >= rozmiar || index < 0)
		return A[0];
	else
		return A[index];
}

template<int r>
class Tablica<Dane, r> {
	Dane A[r];
public:
	int rozmiar = r;
	Dane& operator[](int index) {
		if (index >= r || index < 0)
			return A[0];
		else
			return A[index];
	};
};

int to_file(Tablica<Dane, 10>& tab, string nazwa, string dostep) {
	if (dostep != "nowy" && dostep != "dolacz") {
		cout << "BLEDNY TRYB DOSTEPU DO PLIKU!" << endl;
		return -1;
	}
	ofstream f;
	if (dostep == "nowy") {
		f.open(nazwa, fstream::out);
	}
	else {
		f.open(nazwa, fstream::app);
	}
	time_t czas;
	time(&czas);
	//nag³ówek
	f  <<  setw(35) << right << ctime(&czas) <<endl;
	f << left << getenv("COMPUTERNAME");

	f << endl << '+' << "------" << '+' << "----------" << '+'<< "-------+------+" << endl;

	f << '|' << setw(6) << internal << "ID" << '|' << setw(10) << "nazwa" << '|' << setw(7) << "temp." << '|' << setw(6) << "pojemn" << '|' <<endl ;

	f  << '+' << "------" << '+' << "----------" << '+' << "-------+------+" << endl;
	//treœæ
	for (int i = 0; i < tab.rozmiar; i++)
		f << tab[i] << endl;

	f << '+' << "------" << '+' << "----------" << '+' << "-------+------+" << endl;

	Dane suma;
	for (int i = 0; i < tab.rozmiar; i++) {
		suma += tab[i];
	}
	//stopka
	f << suma << endl;

	f << '+' << "------" << '+' << "----------" << '+' << "-------+------+" << endl;
	return 0;
}

int main(void) {
	Tablica<Dane, 10> T;
	for (int i = 0; i < T.rozmiar; i++) {
		T[i].id = i;
		strcpy_s(T[i].nazwa, "test");
		T[i].pojemn = (double)i * 10;
		T[i].temp = (double)i * 100;
	
	}

	string nazwa = "test.txt";
	cout << "Podaj nazwe pliku do zapisu:";
	cin >> nazwa;

	if (to_file(T, nazwa, "dolacz") != 0) {
		cout<<"BLAD PROGRAMU!";
		return -1;
	}

	return 0;
}