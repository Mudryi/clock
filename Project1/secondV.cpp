#include<iostream>
#include<string>
#include<cmath>
using namespace std;

int main() {
	string a;
	cin >> a;
	int v = -2;
	int k = 0;
	for (int i = 0; i <a.size(); ++i) {
		if (a[i] == 'f') {
			v = -1;
			for (int j = i+1; j < a.size(); ++j) {
				if (a[j] == 'f') {
					cout << j;
					k = 1;
					break;
				}
			}break;
		}
	}
	if (k != 1) {
		cout << v;
	}
	system("pause");
	return 0;
}