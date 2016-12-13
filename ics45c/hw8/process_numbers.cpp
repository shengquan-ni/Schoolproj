#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iterator>
using namespace std;

int main()
{
	ifstream f_numbers("rand_numbers.txt");
	vector<int> numbers;
	for_each(istream_iterator<int>(f_numbers), istream_iterator<int>(), [&](int i) {numbers.push_back(i); });
	sort(numbers.begin(), numbers.end());
	ofstream f_odd("odd.txt");
	ofstream f_even("even.txt");
	for_each(numbers.begin(), numbers.end(), [&](int i) {if (i % 2)f_odd << i << " "; else f_even << i << endl; });
	f_odd.close();
	f_even.close();
	return 0;
}