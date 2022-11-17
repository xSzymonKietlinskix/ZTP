///* ==========================
//   (c) WMP.SNŒ UKSW, 2015
//========================== */
//#include<iostream>
//#include<fstream>
//#include<string>
//#include<limits>
//#include<exception>
//#include<iomanip> 
//
//using namespace std;
//
//class _Bazowe_Cechy {
//public:
//	// pola statyczne sta³e - dla sta³ych wartoœci ca³kowitych
//	static const bool _jest_liczba = false;
//	static const bool _nalezy_do_przedzialu = false;
//	static const bool _jest_liczba_calkowita = false;
//	static const int _liczba_miejsc_po_przecinku = 2;
//	static const bool _jest_wielokrotnoscia = false;
//	static const bool _czy_musi_byc_pierwsza = false;
//	static const bool _wymaga_przeliczenia = false;
//};
//
//template<typename T>
//class _Cechy : public _Bazowe_Cechy {
//public:
//	// metody statyczne - dla wartoœci innych typów ni¿ liczby ca³kowite
//	static const T _dolna_granica() { return T(); };
//	static const T _gorna_granica() { return T(); };
//};
//
//template<typename T>
//class Cechy : public _Cechy<T> {
//};
//
//class przyspieszenie {
//	double a;
//public:
//	przyspieszenie(double acc = 0) : a(acc) {};
//	double operator()() const { return a; };
//	przyspieszenie& operator=(double acc) { a = acc; return *this; };
//	bool operator<(const przyspieszenie& p) const { return (a < p.a); };
//	friend ostream& operator<<(ostream& os, const przyspieszenie&);
//};
//
//
//template<>
//class Cechy<przyspieszenie> : public _Cechy<przyspieszenie> {
//public:
//	static const bool _jest_liczba = true;
//	static const int _liczba_miejsc_po_przecinku = 2;
//};
//
//ostream& operator<<(ostream& os, const przyspieszenie& p) { return os << showpoint << fixed<< setprecision(Cechy<przyspieszenie>::_liczba_miejsc_po_przecinku) << p.a; };
//
//class temperatura_wody {
//	double t;
//public:
//	temperatura_wody(double temp = 50) : t(temp) {};
//	double operator()() const { return t; };
//	temperatura_wody& operator=(double temp) { t = temp; return *this; };
//	bool operator<(const temperatura_wody& tw) const { return (t < tw.t); };
//	friend ostream& operator<<(ostream& os, const temperatura_wody&);
//};
//
//template<>
//class Cechy<temperatura_wody> : public _Cechy<temperatura_wody> {
//public:
//	static const bool _jest_liczba = true;
//	static const bool _nalezy_do_przedzialu = true;
//	static const int _liczba_miejsc_po_przecinku = 1;
//	static const temperatura_wody _dolna_granica() { return temperatura_wody(0); };
//	static const temperatura_wody _gorna_granica() { return temperatura_wody(100); };
//};
//ostream& operator<<(ostream& os, const temperatura_wody& tw) { return os << showpoint << fixed << setprecision(Cechy<temperatura_wody>::_liczba_miejsc_po_przecinku) << tw.t; };
//
//class kostka_do_gry {
//	int n;
//public:
//	kostka_do_gry(int num = 1) : n(num) {};
//	int operator()() const { return n; };
//	kostka_do_gry& operator=(int num) { n = num; return *this; };
//	bool operator<(const kostka_do_gry& k) const { return (n < k.n); };
//	friend ostream& operator<<(ostream& os, const kostka_do_gry&);
//};
//
//template<>
//class Cechy<kostka_do_gry> : public _Cechy<kostka_do_gry> {
//public:
//	static const bool _jest_liczba = true;
//	static const bool _nalezy_do_przedzialu = true;
//	static const bool _jest_liczba_calkowita = true;
//	static const int _liczba_miejsc_po_przecinku = 0;
//	static const kostka_do_gry _dolna_granica() { return kostka_do_gry(1); };
//	static const kostka_do_gry _gorna_granica() { return kostka_do_gry(6); };
//};
//ostream& operator<<(ostream& os, const kostka_do_gry& k) { return os << showpoint << fixed << setprecision(Cechy<kostka_do_gry>::_liczba_miejsc_po_przecinku) << k.n; };
//
//class Przepelnienie : public exception {
//	char opis[100];
//public:
//	Przepelnienie(const char* o) { strcpy_s(opis, o); }
//	const char* what() const throw() { return opis; };
//};
//class BrakDanych : public exception {
//	char opis[100];
//public:
//	BrakDanych(const char* o) { strcpy_s(opis, o); }
//	const char* what() const throw() { return opis; };
//};
//
//
//
//class minuta_dnia {
//	int m;
//public:
//	minuta_dnia(int mm = 0) : m(mm) {};
//	int operator()() const { return m; };
//	minuta_dnia& operator=(int mm) { m = mm; return *this; };
//	bool operator<(const minuta_dnia& md) const { return (m < md.m); };
//	friend ostream& operator<<(ostream& os, const minuta_dnia& md);
//};
//
//template<>
//class Cechy<minuta_dnia> : public _Cechy<minuta_dnia> {
//public:
//	static const bool _jest_liczba = true;
//	static const bool _jest_liczba_calkowita = true;
//	static const bool _nalezy_do_przedzialu = true;
//	static const int _liczba_miejsc_po_przecinku = 2;
//	static const minuta_dnia _dolna_granica() { return minuta_dnia(0); };
//	static const minuta_dnia _gorna_granica() { return minuta_dnia(1440); };
//};
//
//ostream& operator<<(ostream& os, const minuta_dnia& md) {
//	return os  << showpoint << fixed << setprecision(Cechy<minuta_dnia>::_liczba_miejsc_po_przecinku) << md.m;
//};
//
//class sekudny_wybicia {
//	double s;
//public:
//	sekudny_wybicia(double se = 1.2) : s(se) {};
//	double operator()() const { return s; };
//	sekudny_wybicia& operator=(double ss) { s = ss; return *this; };
//	bool operator<(const sekudny_wybicia& sw) const { return (s < sw.s); };
//	friend ostream& operator<<(ostream& os, const sekudny_wybicia& md);
//};
//
//
//
//template<>
//class Cechy<sekudny_wybicia> : public _Cechy<sekudny_wybicia> {
//public:
//	static const bool _jest_liczba = true;
//	static const bool _nalezy_do_przedzialu = true;
//	static const int _liczba_miejsc_po_przecinku = 1;
//	static const bool _wymaga_przeliczenia = true;
//	static const sekudny_wybicia _dolna_granica() { return sekudny_wybicia(1.2); };
//	static const sekudny_wybicia _gorna_granica() { return sekudny_wybicia(24.0); };
//};
//
//ostream& operator<<(ostream& os, const sekudny_wybicia& sw) {
//	return os << showpoint << fixed << setprecision(Cechy<sekudny_wybicia>::_liczba_miejsc_po_przecinku) << sw.s;
//};
//
//class ilosc_piwa {
//	double litry;
//public:
//	ilosc_piwa(double l = 0.568) : litry(l) {};
//	double operator()() const { return litry; };
//	ilosc_piwa& operator=(double l) { litry = l; return *this; };
//	bool operator<(const ilosc_piwa& ip) const { return (litry < ip.litry); };
//	friend ostream& operator<<(ostream& os, const ilosc_piwa& md);
//};
//
//template<>
//class Cechy<ilosc_piwa> : public _Cechy<ilosc_piwa> {
//public:
//	static const bool _jest_liczba = true;
//	static const bool _nalezy_do_przedzialu = true;
//	static const int _liczba_miejsc_po_przecinku = 3;
//	static const bool _jest_wielokrotnoscia = true;
//	static const ilosc_piwa _dolna_granica() { return ilosc_piwa(0.568); };
//	static const ilosc_piwa _gorna_granica() { return ilosc_piwa((double)INT_MAX); }
//};
//
//ostream& operator<<(ostream& os, const ilosc_piwa& sw) {
//	return os << showpoint << fixed << setprecision(Cechy<ilosc_piwa>::_liczba_miejsc_po_przecinku) << sw.litry;
//};
//
//class l_pierwsza {
//	int lp;
//public:
//	l_pierwsza(int l = 2) : lp(l) {};
//	int operator()() const { return lp; };
//	l_pierwsza& operator=(int l) { lp = l; return *this; };
//	bool operator<(const l_pierwsza& _lp) const { return (lp < _lp.lp); };
//	friend ostream& operator<<(ostream& os, const l_pierwsza& md);
//};
//
//template<>
//class Cechy<l_pierwsza> : public _Cechy<l_pierwsza> {
//public:
//	static const bool _jest_liczba = true;
//	static const bool _jest_liczba_calkowita = true;
//	static const bool _czy_musi_byc_pierwsza = true;
//	static const int _liczba_miejsc_po_przecinku = 0;
//	static const l_pierwsza _dolna_granica() { return l_pierwsza(2); };
//	static const l_pierwsza _gorna_granica() { return l_pierwsza(INT_MAX); };
//};
//
//ostream& operator<<(ostream& os, const l_pierwsza& _lp) {
//	return os << showpoint << fixed << setprecision(Cechy<l_pierwsza>::_liczba_miejsc_po_przecinku) << _lp.lp;
//};
//
//
//template<typename T, int rozmiar, typename CechyT = Cechy<T>>
//class SzablonStosu {
//	T stos[rozmiar];
//	int top;
//public:
//	int zajetosc() { return top; };
//	SzablonStosu() : top(0) {}
//	void push(const T& i) {
//		if (top == rozmiar)
//			throw Przepelnienie(typeid(i).name());
//		stos[top++] = i;
//	}
//	void push(int i) {
//		bool valid = true;
//		if (top == rozmiar)
//			throw Przepelnienie(typeid(i).name());
//
//		// walidacja wartoœci przekazanej do zapisu
//		if (CechyT::_jest_liczba && CechyT::_jest_liczba_calkowita) {
//			if (CechyT::_czy_musi_byc_pierwsza) {
//				bool jest_pierwsza = true;
//				int l = i;
//				if (l == 0 || l == 1) {
//					jest_pierwsza = false;
//				}
//				for (int j = 2; j <= l / 2; ++j) {
//					if (l % j == 0) {
//						jest_pierwsza = false;
//						break;
//					}
//				}
//				if (!jest_pierwsza)
//					valid = false;
//			}
//			if (CechyT::_nalezy_do_przedzialu) {
//				if ((T(i) < CechyT::_dolna_granica()) || (CechyT::_gorna_granica() < T(i)))
//					valid = false;
//			}
//			if (valid == true)
//				stos[top++] = i;
//		}
//	}
//	void push(double i) {
//		bool valid = true;
//		if (top == rozmiar)
//			throw Przepelnienie(typeid(i).name());
//
//		// walidacja wartoœci przekazanej do zapisu
//		if (CechyT::_jest_liczba && !CechyT::_jest_liczba_calkowita) {
//			if (CechyT::_nalezy_do_przedzialu) {
//				if ((T(i) < CechyT::_dolna_granica()) || (CechyT::_gorna_granica() < T(i)))
//					valid = false;
//			}
//			if (CechyT::_jest_wielokrotnoscia) {
//				if (((i / 0.568) - (int)(i / 0.568)) > 0.01)
//					valid = false;
//			}
//			if (CechyT::_wymaga_przeliczenia) {
//				double x;
//				x = (i + 0.8) / (2.0);
//				if ((x - (int) x) > 0.01)
//					valid = false;
//			}
//			if (valid == true)
//				stos[top++] = i;
//		}
//	}
//	T pop() {
//		if (top == 0)
//			throw BrakDanych(typeid(stos[0]).name());
//
//		return stos[--top];
//	}
//	template<typename U1, int r, typename U2>
//	friend ostream& operator<<(ostream& os, const SzablonStosu<U1, r, U2>&);
//};
//template<typename U1, int r, typename U2>
//ostream& operator<<(ostream& os, const SzablonStosu<U1, r, U2>& S)
//{
//	for (int i = 0; i < S.top; i++) cout << S.stos[i] << endl;
//	return os;
//};
//
//int main() {
//	SzablonStosu<minuta_dnia, 5> K1;
//	SzablonStosu<sekudny_wybicia, 5> K2;
//	SzablonStosu<ilosc_piwa, 5> K3;
//	SzablonStosu<l_pierwsza, 5> K4;
//
//	K1.push(minuta_dnia(2));
//	K1.push(3.5); // nie akcpetowana bo double
//	K1.push(10000); //spoza przedzia³u
//	K1.push(134);
//	cout << K1;
//	cout << "Danych na stosie K1: " << K1.zajetosc() << endl << endl;
//
//	K2.push(2); //nie akceptuje bo int
//	K2.push(3.3); //nie przelicza siê na godziny 
//	K2.push(-3); //spoza przedzia³u
//	K2.push(sekudny_wybicia());
//	K2.push(5.2);
//	cout << K2;
//	cout << "Danych na stosie K2: " << K2.zajetosc() << endl << endl;
//
//
//	K3.push(ilosc_piwa());
//	K3.push(2.5); //nie akceptuje bo nie jest wielokrotnoscia pinty
//	K3.push(2*0.568);
//	cout << K3;
//	cout << "Danych na stosie K3: " << K3.zajetosc() << endl << endl;
//
//	K4.push(l_pierwsza());
//	K4.push(7);
//	K4.push(12); //nie akceptuje bo nie jest pierwsza
//	cout << K4;
//	cout << "Danych na stosie K4: " << K4.zajetosc() << endl << endl;
//
//	// opró¿nianie stosów
//	try {
//		while (true)
//			K1.pop();
//	}
//	catch (BrakDanych& e) {
//		cout << "K1 pusty: " << e.what() << endl;
//	}
//	try {
//		while (true)
//			K2.pop();
//	}
//	catch (BrakDanych& e) {
//		cout << "K2 pusty: " << e.what() << endl;
//	}
//	try {
//		while (true)
//			K3.pop();
//	}
//	catch (BrakDanych& e) {
//		cout << "K3 pusty: " << e.what() << endl;
//	}
//	try {
//		while (true)
//			K4.pop();
//	}
//	catch (BrakDanych& e) {
//		cout << "K4 pusty: " << e.what() << endl;
//	}
//
//	system("pause");
//	return 0;
//}