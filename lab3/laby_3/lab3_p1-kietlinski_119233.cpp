//#include <iostream>
//#include <assert.h>
//
//using namespace std;
//
//template<typename T>
//class kontener {
//	T dane;
//	kontener* head;
//	kontener* tail;
//	int liczba;
//public:
//	kontener() { head = tail = nast = NULL; liczba = 0; dane = 0; };
//	kontener(T d) { head = new kontener; head->dane = d; nast = tail = new kontener; liczba = 1; tail->nast = NULL; };
//	void push(T d);
//
//	class iterator {
//		kontener& k;
//		kontener* cur; //wskaznik do aktualnego elementu w liscie
//		int index;
//	public:
//		iterator(kontener& kk) : k(kk), index(0) { cur = k.head; };
//		iterator(kontener& kk, bool) : k(kk), index(kk.liczba) { cur = k.head; };
//
//		T operator++() { //prefix
//			assert(index < k.liczba);
//			if (index == 0)
//				cur = k.head;
//			index++;
//			cur = cur->nast;
//			return cur->dane;
//		}
//
//		T operator++(int) {
//			assert(index < k.liczba);
//			if (index == 0)
//				cur = k.head;
//			index++;
//			T buf = cur->dane;
//			cur = cur->nast;
//			return buf;
//		}
//
//		bool operator!=(const iterator& v) const {
//			return index != v.index;
//		}
//
//		iterator& operator=(const iterator& rv) {
//			index = rv.index;
//			return *this;
//		}
//
//		iterator& operator=(const T d) { //do przypisywania wartosci do danych
//			cur->dane = d;
//			return *this;
//		}
//
//		T operator*() {
//			return cur->dane;
//		}
//	};
//
//	iterator begin() { return iterator(*this); };
//	iterator end() { return iterator(*this, true); };
//	friend iterator;
//	kontener* nast;
//
//
//};
//
//template<typename T>
//void kontener<T>::push(T d) {
//	if (head == NULL) {
//		head = new kontener;
//		head->dane = d;
//		head->nast = new kontener;
//		tail = head->nast;
//		liczba++;
//	}
//	else {
//		tail->nast = new kontener;
//		tail->dane = d;
//		tail = tail->nast;
//		liczba++;
//	}
//}
//
//
//double randdouble()
//{
//	return rand() / (double(RAND_MAX / 10.0));
//}
//
//
//template<typename dat, typename T>
//void transformuj(T i1, T i2, T i3) {
//	dat buf;
//	while (i1 != i2) {
//		if (*i1 < *i3) {
//			buf = *i1;
//			i1 = *i3;
//			i3 = buf;
//		}
//		i1++;
//		i3++;
//	}
//}
//
//template<typename T>
//void roznicuj(T i1, T i2, T i3) {
//	while (i1 != i2) {
//		i1 = *i1 - *i3;
//		i1++;
//		i3++;
//	}
//}
//
//template<typename dat, typename T>
//void objetnosc(T i1, T i2, dat &a) {
//	while (i1 != i2) {
//		a = a * (*i1);
//		i1++;
//	}
//}
//
//template<typename T>
//void wypisz(T beg, T end) {
//	cout.precision(2);
//	cout.showpoint;
//	while (beg != end) {
//		cout << *beg << '\t';
//		beg++;
//	}
//}
//
//
//int main(void) {
//	srand((unsigned)time(NULL));
//	kontener<double> p;
//	kontener<double>::iterator i_p = p.begin();
//	kontener<double> q;
//	kontener<double>::iterator i_q = q.begin();
//
//	int n = 8; //liczba losowych liczb
//
//	for (int i = 0; i < n; i++) {
//		p.push(randdouble());
//		q.push(randdouble());
//	}
//	
//	cout << "p: ";
//	wypisz(p.begin(), p.end());
//	
//	cout << endl << "q: ";
//	wypisz(q.begin(), q.end());
//
//	transformuj<double>(p.begin(), p.end(), q.begin());
//
//	cout << endl << endl << "Po transformacji: " << endl;
//	cout << "p: ";
//	wypisz(p.begin(), p.end());
//	cout << endl << "q: ";
//	wypisz(q.begin(), q.end());
//	cout << endl;
//
//	roznicuj(p.begin(), p.end(), q.begin());
//	double a = 1.0;
//	objetnosc<double>(p.begin(), p.end(),a);
//	cout.precision(10);
//	cout  <<"objetosc to: " << a << endl;
//
//	return 0;
//}