#include <iostream>
#include <fstream>
#include<assert.h>
#include <time.h>
#include <math.h>


using namespace std;

template<typename T>
class kontener {
	T dane;
	kontener* head;
	kontener* tail;
	int liczba;
public:
	kontener() { head = nast = tail = NULL; liczba = 0; dane = 0; };
	kontener(T d) { head = nast = tail = NULL; liczba = 0; push(d); };
	void push(T d);
	T get_dane() { return dane; };
	int get_liczba(){ return liczba; };
	
	kontener* nast;

	class iterator {
		kontener& k;
		int index;
	public:
		iterator(kontener& kk) : k(kk), index(0) {};
		iterator(kontener& kk, bool) : k(kk), index(kk.liczba) {};
		T operator++() {
			index++;
			assert(index < k.liczba);
			kontener* wsk = k.head;
			for (int i = 0; i < index; i++)
				wsk = wsk->nast;
			return wsk->dane;
		}
		T operator++(int) {
			assert(index < k.liczba);
			kontener* wsk = k.head;
			for (int i = 0; i < index; i++)
				wsk = wsk->nast;
			index++;
			return wsk->dane;
		}


		iterator& operator =(T cos) {
			kontener* wsk = k.head;
			for (int i = 0; i < index; i++)
				wsk = wsk->nast;
			wsk->dane = cos;
			return *this;
		}

		iterator& operator=(const iterator& rv) {
			index = rv.index;
			return *this;
		}

		friend ostream& operator << (ostream& out, const iterator& i) {
			return out << i.k.get_dane();
		}

		bool operator==(const iterator& v) const {
			return index == v.index;
		}

		bool operator!=(const iterator& v) const {
			return index != v.index;
		}

		T operator*() const { 
			assert(index < k.liczba);
			kontener* wsk = k.head;
			for (int i = 0; i < index; i++)
				wsk = wsk->nast;
			return wsk->dane;
		}
	
	};
	iterator begin() { return iterator(*this); };
	iterator end() { return iterator(*this, true); }
	friend iterator;
};

template<typename T>
void kontener<T>::push(T d) {
	if (head == NULL) {
		head = new kontener<T>;
		head->dane = d;
		head->nast = new kontener<T>;
		tail = head->nast;
		liczba++;
	}
	else {
		tail->nast = new kontener<T>;
		tail->dane = d;
		tail = tail->nast;
		liczba++;
	}
}

double randdouble()
{
	return rand() / (double(RAND_MAX/10.0));
}

template<typename T>
T roznicuj1(T i1, T i2, T i3) {
	while (i1 != i2) {
		i1 = *i1 - *i3;
		i1++;
		i3++;
	}
	
	return i1;
}

template<typename T, typename D>
T roznicuj2(T i1, T i2, D d) {
	while (i1 != i2) {
		i1 = *i1 - d;
		i1++;
	}

	return i1;
}

template<typename T>
T dokwadratu(T i1, T i2) {
	while (i1 != i2) {
		i1 = *i1 * *i1;
		i1++;
	}

	return i1;
}

void algorytm() {
	kontener<double> przed;
	kontener<double> po;
	kontener<double>::iterator it_przed = przed.begin();
	kontener<double>::iterator it_po = po.begin();

	//for (int i = 0; i < 4; i++) {
	//	przed.push(randdouble());
	//	po.push(randdouble());
	//}

	przed.push(2.2);
	przed.push(2.3);
	przed.push(3.7);
	przed.push(7.4);
	po.push(2.5);
	po.push(1.1);
	po.push(4.2);
	po.push(8.8);

	cout.precision(2);
	cout << "Przed badaniem: ";
	while (it_przed != przed.end())
		cout << it_przed++ << "   ";

	cout << endl << "Po badaniu: ";
	while (it_po != po.end())
		cout << it_po++ << "   ";
	cout << endl;

	double D = 0;
	int n = przed.get_liczba();

	roznicuj1(przed.begin(), przed.end(), po.begin());

	it_przed = przed.begin();
	while (it_przed != przed.end()) {
		D += *it_przed;
		it_przed++;
	}
	D = D / n;

	cout << endl << "to jest D: " << D << endl;

	roznicuj2(przed.begin(), przed.end(), D);
	dokwadratu(przed.begin(), przed.end());
	double S = 0;

	it_przed = przed.begin();
	while(it_przed != przed.end()){
		S += *it_przed;
		it_przed++;
	}

	S = sqrt(S / (n - 1.0));

	cout << "To jest S: " << S << endl;

	double T;

	T = D / (S / sqrt(n));
	cout << "to jest T: " << T << endl;
}


int main(void) {
	srand((unsigned) time(NULL));
	
	algorytm();


	return 0;
}