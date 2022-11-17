#include <iostream>
#include <string>
#include <fstream>
#include <stack>

using namespace std;

class MyError {
protected:
	int line;
	string err;
public:
	MyError(string e, int l = -1) :line(l), err(e) {};
	friend ostream& operator<< (ostream& out, const MyError& e);
	string showErr() { return err; };
};

class Error_klamry:public MyError {
public:
	Error_klamry(int l = -1) : MyError("Blad w pisowni klamer w znaczniku!", l) {};
	string showErr() { return err; };
};

class Error_znacznik :public MyError {
public:
	Error_znacznik(int l = -1) : MyError("Rozne znaczniki poczatkowe i koncowe!", l) {};
	Error_znacznik(string er, int l = -1) : MyError(er, l) {};
	string showErr() { return err; };
};

class file_error :public MyError {
public:
	file_error(int l = -1) : MyError("Blad odczytu strumienia wejsciowego!", l) {};
	string showErr() { return err; };
};

ostream& operator<<(ostream& out, const MyError& e) {
	if (e.line > -1)
		out << "In line: " << e.line << endl;
	return out;
}

int check(istream& f) {
	try {
		if ((f.rdstate() & ifstream::failbit) != 0)
			throw file_error();

		string beg; //buffor do wczytywania linii
		bool EndFlag = false;
		int i = 1; //licznik linii

		getline(f, beg);
		if (beg != "<TABLE>")
			throw Error_znacznik("Plik nie zaczyna sie od <TABLE>!", 0);

		stack<string> znaczniki; //stos na znaczniki

		while (!f.eof()) {
			i++;
			getline(f, beg, '>');

			beg.erase(remove(beg.begin(), beg.end(), ' '), beg.end()); //usuwanie spacji i tabulatorów
			beg.erase(remove(beg.begin(), beg.end(), '\t'), beg.end());

			if (beg[0] != '<')
				throw Error_klamry(i);

			if (beg.find('\n') != string::npos || beg.length() > 8)
				throw Error_klamry(i);

			beg.erase(remove(beg.begin(), beg.end(), '<'), beg.end());

			if (beg == "/TABLE") {
				if (f.eof())
					break;

				EndFlag = true;
				if (!znaczniki.empty())
					throw MyError("Tabela zostala zakonczona bez zamykania poprzednich znacznikow!");
				break;
			}

			if (beg == "TR") {
				znaczniki.push(beg);
				getline(f, beg, '\n');
				continue;
			}

			if (beg == "/TR") {
				string buf;
				buf = znaczniki.top();
				znaczniki.pop();
				buf.erase(remove(buf.begin(), buf.end(), '/'));
				if (buf != buf)
					throw Error_znacznik(i);
				getline(f, beg, '\n');
				continue;
			}

			znaczniki.push(beg);

			getline(f, beg, '<'); //tresc pomiedzy znacznikami
			if (f.eof())
				break;

			if (beg[beg.length() - 1] == '\n')
				throw Error_klamry(i);

			getline(f, beg, '>');
			if (f.eof())
				break;
			beg.erase(remove(beg.begin(), beg.end(), ' '), beg.end());
			beg.erase(remove(beg.begin(), beg.end(), '\t'), beg.end());

			if (beg[0] != '/')
				throw Error_znacznik("Brak slasha w koncowym znaczniku!", i);

			if (beg.find('\n') != string::npos)
				throw Error_klamry(i);

			beg.erase(remove(beg.begin(), beg.end(), '/'), beg.end());

			if (beg != znaczniki.top()) {
				znaczniki.pop();
				throw Error_znacznik(i);
			}
			znaczniki.pop();

			getline(f, beg, '\n');
		}
		if (EndFlag == false)
			throw Error_znacznik("Brak znacznika </TABLE> na koncu pliku!");
		return 0;
	}

	catch (MyError& e) {
		cout << e << endl;
		throw;
	}
}

int main(void) {
	string name = "test.txt";
	ifstream stream;
	stream.open(name);
	try {
		if (check(stream) == 0)
			cout << "Tabele zapisane w pliku sa zgodne z jezykiem HTML" << endl;
		else
			cout << "Tabele zapisane w pliku NIE sa zgodne z jezykiem HTML" << endl << "Popraw powyzsze bledy!" << endl;
	}

	catch (Error_klamry& e) {
		cout << e.showErr() << endl << typeid(e).name() << endl;
		cout << "Tabele zapisane w pliku NIE sa zgodne z jezykiem HTML" << endl << "Popraw powyzsze bledy!" << endl;
	}
	catch (Error_znacznik& e) {
		cout << e.showErr() << endl << typeid(e).name()<< endl;
		cout << "Tabele zapisane w pliku NIE sa zgodne z jezykiem HTML" << endl << "Popraw powyzsze bledy!" << endl;
	}

	catch (file_error& e) {
		cout << e.showErr() << endl << typeid(e).name() << endl;
		cout << "Program zakonczyl swoje dzialanie w wyniku powzyszego bledu!" << endl;
		return -1;
	}

	catch (MyError& e) {
		cout << "Inny blad: " << e.showErr() << endl;
		cout << "Tabele zapisane w pliku NIE sa zgodne z jezykiem HTML" << endl << "Popraw powyzsze bledy!" << endl;
	}

	stream.close();
	return 0;
}