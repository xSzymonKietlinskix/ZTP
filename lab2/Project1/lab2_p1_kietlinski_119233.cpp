#include <iostream>
#include <string>
#include <fstream>
#include <stack>

using namespace std;

class MyError {
	int line;
	string err;
public:
	MyError(string e, int l = -1) :line(l), err(e) {};
	friend ostream& operator<< (ostream& out, const MyError& e);
};

ostream& operator<<(ostream& out, const MyError& e) {
	out << "Error: " << e.err << endl;
	if (e.line > -1)
		out << "In line: " << e.line << endl;
	return out;
}

int check(istream &f) {
	try {
		if ((f.rdstate() & ifstream::failbit) != 0)
			throw runtime_error("Blad otwierania pliku!");

		string beg; //buffor do wczytywania linii
		bool EndFlag = false;
		int i = 1; //licznik linii

		getline(f,beg);
		if (beg != "<TABLE>")
			throw MyError("Plik nie zaczyna sie od <TABLE>!", 0);

		stack<string> znaczniki; //stos na znaczniki

		while (!f.eof()) {
			i++;
			getline(f, beg, '>');
			
			beg.erase(remove(beg.begin(), beg.end(), ' '), beg.end()); //usuwanie spacji i tabulatorów
			beg.erase(remove(beg.begin(), beg.end(), '\t'), beg.end());

			if (beg[0] != '<')
				throw MyError("Brak nawiasu rozpoczynajcego pocztakowy znacznik!", i);

			if (beg.find('\n') != string::npos || beg.length() > 8)
				throw MyError("Brak nawiasu konczacego poczatkowy znacznik!", i);

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
					throw MyError("Znacznik poczatkowy jest rozny od znacznika koncowego!", i);
				getline(f, beg, '\n');
				continue;
			}

			znaczniki.push(beg);

			getline(f, beg, '<'); //tresc pomiedzy znacznikami
			if (f.eof())
				break;

			if (beg[beg.length() - 1] == '\n')
				throw MyError("Brak nawiasu rozpoczynajacego koncowy znacznik!", i);

			getline(f, beg, '>');
			if (f.eof())
				break;
			beg.erase(remove(beg.begin(), beg.end(), ' '), beg.end());
			beg.erase(remove(beg.begin(), beg.end(), '\t'), beg.end());

			if (beg[0] != '/')
				throw MyError("Brak slasha w koncowym znaczniku!", i);

			if (beg.find('\n') != string:: npos)
				throw MyError("Brak nawiasu konczacego koncowy znacznik!", i);

			beg.erase(remove(beg.begin(), beg.end(), '/'), beg.end());
			
			if (beg != znaczniki.top()) {
				znaczniki.pop();
				throw MyError("Znacznik poczatkowy jest rozny od znacznika koncowego!", i);
			}
			znaczniki.pop();

			getline(f, beg, '\n');
		}
		if (EndFlag == false)
			throw MyError("Brak znacznika </TABLE> na koncu pliku!");
		return 0;
	}

	catch (MyError& e) {
		cout << e << endl;
	}
	catch (runtime_error& e) {
		cout << e.what() << endl;
	}
}

int main(void) {
	string name = "test.txt";
	ifstream stream;
	stream.open(name);

	if (check(stream) == 0)
		cout << "Tabele zapisane w pliku sa zgodne z jezykiem HTML" << endl;
	else
		cout << "Tabele zapisane w pliku NIE sa zgodne z jezykiem HTML" << endl << "Popraw powyzsze bledy!" <<endl;

	stream.close();
	return 0;
}