#include <iostream>
#include "MapArray.h"
#include "SetList.h"
#include <fstream>
using namespace std;

int main()
{
	ifstream f_sample_doc("sample_doc.txt");
	ifstream f_stopwords("stopwords.txt");
	SetList<string> stopwords;
	MapArray<string, int> freq;
	ofstream f_freq("frequency.txt");
	for_each(istream_iterator<string>(f_stopwords), istream_iterator<string>(), [&](string s) {stopwords.insert(s); });
	for_each(istream_iterator<string>(f_sample_doc), istream_iterator<string>(), [&](string s) 
	{
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		if (stopwords.find(s) == stopwords.end())
			freq[s] ++;
	});
	for_each(freq.begin(), freq.end(), [&](const pair<string,int>& e) {f_freq << e.first << " " << e.second << endl; });
	f_freq.close();
	return 0;
}