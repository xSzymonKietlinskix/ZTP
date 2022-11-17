#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class MyError {
	string er_name;
	int line;
public:
	MyError(string s) { er_name = s; line = -1; };
	MyError(string s, int i) { er_name = s; line = i; };
	friend ostream& operator<<(ostream& out, const MyError& er) {
		out << "blad: " << er.er_name << endl;
		if(er.line >= 0)
			out << "W linii: " << er.line << endl;
		return out; };
};


void check(string s, int line) {
	string przed;
	string po;
	
	if (s[0] != '<')
		throw MyError("Brak nawiasu otwierajacego!", line); //brak bracketa

	przed = s.substr(s.find('<'),s.find('>') + 1);
	po = s.substr(s.rfind('<'), s.rfind('>') + 1);

	if (po[0] != '<' || po[1] != '/' || po[po.length()-1] != '>')
		throw MyError("Blad w zakonczeniu linii!", line);

	s = s.substr(przed.length(), s.length()-przed.length() - po.length());
	przed = przed.substr(przed.find('<') + 1, przed.length() - 2);
	po = po.substr(po.find('/') + 1, po.length() - 3);

	if (przed != po)
		throw MyError("Otwarcie i zakonczenie linii nie sa identyczne!", line);



}

int fun(string name, ifstream &file) {
	try {
		if (!file.is_open())
			throw runtime_error("Blad otwarcia pliku!");
		string buf;
		
		file >> buf;
		int i = 1; //counter lini
		while (buf != "<math") {
			file >> buf;
			i++;
			if (file.eof())
				throw MyError("Brak <math w pliku!"); //nie ma w pliku <math
		}

		file >> buf;
	
		bool flag_ending = false;
		while (!file.eof()) {
			file >> buf;
			i++;
			if (buf == "</math>") {
				flag_ending = true;
				break;
			}
			if (buf == "<msup>") {
				for (int j = 0; j < 2; j++) {
					file >> buf;
					i++;
					check(buf, i);
				}
				file >> buf;
				i++;
				if (buf != "</msup>")
					throw MyError("Blad w sekcji potegi!", i);
				continue;
			}
			check(buf,i);
		}
		if (flag_ending == false)
			throw MyError("Brak </math> na koncu sekcji!"); //brak zakonczenia sekcji
		return 0;
	}
	catch (MyError &e) {
		cout << e << endl;
	}
	catch (runtime_error &r) {
		cout << r.what() << endl;
	}
	
}


int main(void) {
	string name;
	
	try {
		cout << "wprowadz nazwe pliku do sprawdzenia: ";
		cin >> name;
		ifstream file;
		file.open(name);
		if (fun("test.txt",file) != 0)
			throw exception("Plik niezgodny z systemem MathMl");
		else
			cout << "Plik zgodny z system MathML" << endl;
		file.close();
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	
	return 0;
}