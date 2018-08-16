#include<iostream>
#include<string>
#include<vector>
#include<cmath>
using namespace std;

bool	Cont(vector<string> words, string word) {
	for (auto s : words) {
		if (s == word) {
			return true;
		}
		
	}
	return false;
}

int main() {
	cout << Cont({ "kek","perekek","sosi" }, "sosi");
	system("pause");
	return 0;
}