#include <iostream>
#include <assert.h>


using namespace std;


template<typename T, int rozmiar>
class kontener {
	T data[rozmiar];
	int top;
public:
	kontener() :top(0) {};
	void push(const T& d) { data[top++] = d; };
	T pop() { return data[--top]; };
	
	class iterator {
		kontener<T, rozmiar> k;
		int index;
	public:
		iterator(kontener& kk) : k(kk), index(0) {};
		iterator(kontener& kk, bool b) : k(kk), index(k.top) {};

		T operator++() { //prefix
			assert(index < k.top);
			return k.data[++index];
		}

		T operator++(int) { //postfix
			assert(index < k.top);
			return k.data[index++];
		}

		T operator*() const {
			return k.data[index];
		}

		iterator& operator =(const iterator& it) {
			k.data[index] = it.k.data[it.index];
			index = it.index;
			return *this;
		}

		iterator& operator =(const T &dana) {
			k.data[index] = dana;
			return *this;
		}

		bool operator < (const iterator& it) {
			return k.data[index] < it.k.data[it.index];
		}

		bool operator < (const T& dana) {
			return k.data[index] < dana;
		}
		bool operator !=(const iterator& it) {
			return index != it.index;
		}
		
	};

	iterator begin() { return iterator(*this); };
	iterator end() { return iterator(*this, true); };
	friend iterator;
};



double randdouble() {
	return rand() / (double(RAND_MAX/10.0));
}

template<typename T, typename K>
T max(K beg, K end) {
	T max = -RAND_MAX;
	while (beg != end) {
		if (*beg > max)
			max = *beg;
		beg++;
	}
	return max;
}

template<typename T, typename K>
T min(K beg, K end) {
	T min = RAND_MAX;
	while (beg != end) {
		if (*beg < min)
			min = *beg;
		beg++;
	}
	return min;
}

template<typename T>
void swapp(T& a, T& b) {
	T c;
	c = a;
	a = b;
	b = c;
}

template<typename T, typename K>
T mediana(K beg, K end) {
	T med = 0;
	T mini = RAND_MAX;
	K buf(beg);
	K ktory = beg;
	K trzmaj = beg;
	while (beg != end) {
		buf = beg;
		while (buf != end) {
			if (*buf < mini) {
				mini = *buf;
				ktory = buf;
			}
			buf++;
		}
		buf = beg;
		if (mini < *beg) {
			beg = ktory;
			ktory = buf;
		}
		beg++;
	}


	while (trzmaj != end)
		cout << trzmaj++ << endl;

	return med;
}




int main(void) {
	srand(unsigned(time(NULL)));
	kontener<double, 10> k;
	
	for (int i = 0; i < 10; i++)
		k.push(randdouble());

	kontener<double,10>::iterator it(k);

	while (it != k.end())
		cout << it++ << endl;

	cout << endl << "wartosc max: " << max<double>(k.begin(), k.end());
	cout << endl << "wartosc min: " << min<double>(k.begin(), k.end()) << endl;
	
	mediana<double>(k.begin(), k.end());

	it = k.begin();


	return 0;
}