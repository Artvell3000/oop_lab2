#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <map>
using namespace std;

class SBase {
public:
	int Get() {
		return 0;
	}
};

class SKbrd : public SBase {
public:
	int Get() {
		if (cin.peek() == '\n')
			return -1;
		else {
			int number;
			cin >> number;
			return number;
		}
	}
};

class SFile : public SBase {
	fstream f;
	string path;

public:
	SFile(string p) {
		path = p;
		f.open(p);
	}
	~SFile() {
		f.close();
	}

	void restart() {
		f.close();
		f.open(path);
	}

	void new_file(string p) {
		f.close();
		f.open(p);
	}

	int Get() {
		int i;
		if (!f.eof())
			f >> i;
		else
			return -1;
		return abs(i);
	}
};

class SQueue : public SBase {
	int* que, length, current;
public:
	SQueue(int leng) {
		length = leng;
		que = new int[length];
		for (int i = 0;i < leng;i++) {
			que[i] = rand() % 10;
		}
		current = 0;
	}
	~SQueue() {
		delete[] que;
	}

	void roll_back() {
		current = 0;
	}

	int Get() {
		if (current == length) return -1;
		current++;
		return que[current - 1];
	}

	friend ostream& operator<<(ostream& stream, SQueue& obj) {
		stream << "SQueue:\n";
		for (int i = 0;i < obj.length;i++) {
			stream << obj.que[i] << " ";
		}
		return stream;
	}
};

class Freq {
	int sum = 0;
protected:
	map<int, int> counts;
public:
	void Calc(SBase* obj) {
		for (int i = obj->Get();i != -1;i = obj->Get()) {
			sum += i;
			if (counts.find(i) != counts.end()) {
				counts[i]++;
			}
			else {
				counts[i] = 1;
			}
		}
	}

	friend ostream& operator<<(ostream& stream, Freq& obj) {
		for (auto i : obj.counts)
		{
			stream << i.first << " : " << i.second << "\n";
		}
		stream << "sum : " << obj.sum << '\n';
		return stream;
	}
};

class Diap : public Freq {
	int Min = INT_MAX, Max = INT_MIN, quantity = 0;
public:
	void Calc(SBase* obj) {
		Freq::Calc(obj);

		for (auto i : counts) {
			quantity += i.second;
			Min = min(Min, i.first);
			Max = max(Max, i.first);
		}
	}

	friend ostream& operator<<(ostream& stream, Diap& obj) {
		stream << "quantity : " << obj.quantity << '\n';
		stream << "min : " << obj.Min << '\n';
		stream << "max : " << obj.Max << '\n';
		return stream;
	}
};

int main() {
	srand(time(NULL));
	SKbrd sk;
	SFile sf("1.txt");
	SQueue sq(10);

	Freq a1;
	a1.Calc(&sf);
	cout << a1 << '\n';
	cout << "\n\n";

	cout << sq << '\n';
	Diap a2;
	a2.Calc(&sq);
	cout << a2 << '\n';
	cout << "\n\n";

	Diap a3;
	a3.Calc(&sk);
	cout << a3 << '\n';
	cout << "\n\n";
}
