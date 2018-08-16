#include<iostream>
#include<string>
#include<cmath>
using namespace std;

int main() {
	int N;
	cin >> N;
	int a = (int)log2(N);
	for (int i = a; i >= 0; --i) {
		int j = pow(2, i);
		if (N -j >= 0) {
			N =N - j;
			cout << 1;
		}
		else {
			cout << 0;
		}
	}
	system("pause");
	return 0;
}