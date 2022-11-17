#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <chrono>
using namespace std;


int losuj(bool &zla) {
	int tim = 0;
	char litera;
	int odp;
	litera = rand() % 25 + 97;
	cout << "wylosowana litera to: " << litera <<endl;
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	cin >> odp;
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	tim = chrono::duration_cast<std::chrono::seconds>(end - begin).count();
	cin.clear();
	if (odp == litera) {
		zla = false;
		return tim;
	}

	if (zla == true)
		throw runtime_error("CHuj mi w dupe");
	zla = true;
	
}

int main(void) {
	bool zla = false;
	srand(time(NULL));
	try {
		while (true)
			cout << "czas: " << losuj(zla) << endl;
	}
	catch (runtime_error& e) {
		cout << e.what() << endl;
		cout << "czy chcesz grac dalej?" << endl;
		string wybor;
		cin >> wybor;
		if (wybor == "tak") {
			main();
		}
	}
	return 0;
}