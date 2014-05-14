/* Performing Top-Down parsing */

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <stack>
#include <queue>
#include <sstream>

using namespace std;

stack <string> s;
vector <string> vs;
queue <vector <string> > qu;
multimap <string, vector <string> > mm1;
multimap <string, string> mm2;
int i = 0;
int ans = 0;

void print()
{

	ofstream out("tree.txt");
	while (!qu.empty() && ans == 1) {
		vector <string> vv = qu.front();
		//cout << "(";
		out << " ( ";
		for (int i = 0; i < vv.size(); i++) {
			//cout << vv[i];
			out << vv[i] << " ";
		}
		//cout << ")";
		out << ")";
		qu.pop();

	}
	//cout << endl;
	out << endl;
}

void function()
{
	if (s.size() == 0 && i == vs.size()) {
		ans = 1;
		return;
	} else if (s.size() == 0) {
		return;
	}

	string str = s.top();
	s.pop();
	multimap <string, string> :: iterator it1;

	for (it1 = mm2.begin(); it1 != mm2.end(); it1++) {
		if (i < vs.size() && it1 -> first == str && it1 -> second == vs[i]) {
			vector <string> v;
			v.push_back(vs[i++]);
			queue <vector <string> > qu2 = qu;
			qu.push(v);
			queue <vector <string> > qu1 = qu;
			//print();
			qu = qu1;
			function();
			if (ans == 1) {
				return;
			}
			i--;
			qu = qu2;
			qu1 = qu;
			//print();
			qu = qu1;

		}
	}

	multimap <string, vector <string> > :: iterator it2;
	for (it2 = mm1.begin(); it2 != mm1.end(); it2++) {
		if (it2 -> first == str) {
			stack <string> s1 = s;
			for (int j = (it2 -> second).size() - 1; j >= 0; j--) {
				s.push((it2 -> second)[j]);
			}
			queue <vector <string> > qu2 = qu;
			qu.push(it2 -> second);
			queue <vector <string> > qu1 = qu;
			//print();
			qu = qu1;
			function();
			if (ans == 1) {
				return;
			}
			s = s1;
			qu = qu2;
			qu1 = qu;
			//print();
			qu = qu1;

		}
	}
}

int main()
{
	s.push("S");
	vector <string> v;
	v.push_back("S");
	qu.push(v);

	ifstream in("tag.txt");
	string str;
	while (getline(in, str)) {
		stringstream ssss;
		ssss.str(str);
		string tmp1, tmp2, tmp3;
		ssss >> tmp1 >> tmp2 >> tmp3;
		vs.push_back(tmp2);
	}
	
	ifstream pro("rules.txt");
	string s;
	while (getline(pro, s)) {
		stringstream ss;
		ss << s;
		string s1;
		ss >> s1;
		string s2;
		vector <string> v1;
		while (ss >> s2) {
			v1.push_back(s2);
		}

		mm1.insert(pair<string, vector <string> >(s1, v1));
	}
	in.close();
	in.open("tag.txt");
	while (getline(in, s)) {
		stringstream sgs;
		sgs.str(s);
		string tmp1, tmp2, tmp3;
		sgs >> tmp1 >> tmp2 >> tmp3;
		mm2.insert(pair<string, string>(tmp3, tmp2));
	}
	function();
	
	if (ans == 1) {
		print();
	} else { 
		cout << "No Parse Tree...\n";
	}

	return 0;
}
