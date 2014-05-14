#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
	
	ifstream in("/root/Desktop/shallow-parser-hin-4.0.fc8/OUTPUT.tmp/postagger.tmp");
	string s;
	// Reading postagger.tmp and extracting all the tags, writing in tag.txt	
	ofstream out("tag.txt");
	int f = 0;
	while (getline(in, s)) {
		stringstream ss;
		ss.str(s);
		if (f != 0) {
			string tmp1, tmp2, tmp3;
			ss >> tmp1 >> tmp2 >> tmp3;
			if (!isdigit(tmp1[0])) {
				// Do nothing
			} else {
				out << tmp1 << "  " << tmp2 << "  " << tmp3 << "\n";
			}
		}
		f++;
	}
	return 0;
}
