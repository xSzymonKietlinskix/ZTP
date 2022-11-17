#include <iostream>
#include <assert.h>

using namespace std;

template<typename T>
class kontener {
	kontener* head;
	kontener* tail;
	int liczba;
	T dane;
public:
	kontener() { head = tail = nast = NULL; liczba = 0; dane = 0; };
	kontener(T d) { head = new kontener; head->dane = d; nast = tail = new kontener; liczba = 1; tail->nast = NULL; };
	void push(T d);

	class iterator {
		kontener& k;
		kontener* cur; //wskaznik do aktualnego elementu w liscie
		int index;
	public:
		iterator(kontener& kk) : k(kk), index(0) { cur = k.head; };
		iterator(kontener& kk, bool) : k(kk), index(kk.liczba) { cur = k.head; };

		T operator++() { //prefix
			assert(index < k.liczba);
			if (index == 0)
				cur = k.head;
			index++;
			cur = cur->nast;
			return cur->dane;
		}

		T operator++(int) {
			assert(index < k.liczba);
			if (index == 0)
				cur = k.head;
			index++;
			T buf = cur->dane;
			cur = cur->nast;
			return buf;
		}

		bool operator!=(const iterator& v) const {
			return index != v.index;
		}

		iterator& operator=(const iterator& rv) {
			index = rv.index;
			return *this;
		}

		iterator& operator=(const T d) { //do przypisywania wartosci do danych
			cur->dane = d;
			return *this;
		}

		T operator*() {
			return cur->dane;
		}

	};

	iterator begin() { return iterator(*this); };
	iterator end() { return iterator(*this, true); };
	friend iterator;
	kontener* nast;

};

template<typename T>
void kontener<T>::push(T d) {
	if (head == NULL) {
		head = new kontener;
		head->dane = d;
		head->nast = new kontener;
		tail = head->nast;
		liczba++;
	}
	else {
		tail->nast = new kontener;
		tail->dane = d;
		tail = tail->nast;
		liczba++;
	}
}


double randdouble()
{
	return rand() / (double(RAND_MAX / 10.0));
}


template<typename dat, typename T>
void transformuj(T i1, T i2, T i3) {
	dat buf;
	while (i1 != i2) {
		if (*i1 < *i3) {
			buf = *i1;
			i1 = *i3;
			i3 = buf;
		}
		i1++;
		i3++;
	}
	
}

template<typename T>
void roznicuj(T i1, T i2, T i3) {
	while (i1 != i2) {
		i1 = *i1 - *i3;
		i1++;
		i3++;
	}
}

template<typename dat, typename T>
void objetnosc(T i1, T i2, dat &a) {
	while (i1 != i2) {
		a = a * (*i1);
		i1++;
	}
}

template<typename T>
void wypisz(T beg, T end) {
	cout.precision(2);
	cout.showpoint;
	while (beg != end) {
		cout << *beg << '\t';
		beg++;
	}
}

template<typename T>
class kalkulator {
public:
	static double MaxObjetoscChmury(typename kontener<kontener<T>>::iterator pierwszy, typename kontener<kontener<T>>::iterator drugi) {
		typename kontener<kontener<T>>::iterator bufor = pierwszy;
		
		kontener<T> first = *bufor;
		while (bufor != drugi) {
			kontener<T> buf = *bufor;
			transformuj<T>(buf.begin(), buf.end(), first.begin()); //szukanie najmniejszych wartoœci
			bufor++;
		}

		kontener<T> last = *drugi;

		bufor = pierwszy; //przechodzenie na ostatni, niepusty element w liœcie
		while (bufor != drugi) {
			bufor++;
			if (!(bufor != drugi))
				break;
			last = *bufor;
		}
		
		bufor = pierwszy;
		bufor++;
		while (bufor != drugi) {
			kontener<T> buf = *bufor;
			transformuj<T>(last.begin(), last.end(), buf.begin()); //szukanie najwiêkszych wartoœci
			bufor++;
		}

		cout << endl << "Posortowane: (kontenery ida poziomo, czyli pierwszy poziom to wartosci min)" << endl;
		while (pierwszy != drugi) {
			kontener<T> s = *pierwszy;
			wypisz(s.begin(), s.end());
			cout << endl;
			pierwszy++;
		}

		cout << endl << endl << "Liczenie dla wartosci granicznych: " <<endl;

		cout << endl << "p: ";
		wypisz(last.begin(), last.end());


		cout << endl << "q: ";
		wypisz(first.begin(), first.end());

		
		roznicuj(last.begin(), last.end(), first.begin());
		T a = 1.0;
		objetnosc<T>(last.begin(), last.end(), a);
		cout.precision(10);
		
		return a;
	}
};


int main(void) {
	srand((unsigned)time(NULL));
	

	int m = 6; //liczba punktów
	int n = 7; //liczba wymiarów

	kontener<kontener<double>> k;
	for (int i = 0; i < n; i++) {
		kontener<double> l;
		for (int j = 0; j < m; j++) {
			l.push(randdouble());
		}
		wypisz(l.begin(), l.end());
		cout << endl;
		k.push(l);
	}

	cout << endl << "objetosc to: " << kalkulator<double>::MaxObjetoscChmury(k.begin(), k.end()) << endl;

	return 0;
}