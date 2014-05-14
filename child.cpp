#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cctype>
#include <queue>
#include <map>
using namespace std;

int cnt = 0;
map <int, string> mp;
vector <vector <string> > vv;

//List of All Tags
string ar[100] = {"S", "QCC", "NP", "VP", "RBP", "JJP", "NN","NST","NNP","PRP","DEM", "VM", "VAUX", "JJ", "NNPC", "RB", "PSP", "RP", "CC", "WQ", "QF", "QC", "QO", "CL", "INTF", "INJ", "NEG", "UT", "SYM", "C", "RDP", "ECH", "UNK", "X", "Y", "Z", "A", "B", "NNC", "D", "E", "F"};
ofstream out("graph.dot");

//Structuring for the nodes of the Tree
struct node {
	string sym;
	node *l[8];		//Pointer to children (Considering maximum 8 children of a node )
	node *parent;
	int label;		//Label = i, Denotes i'th child of its parent
	int counter;		//Distinguishing between 2 same nodes, e.g. 2 VP nodes as VP_1, VP_2 (used for making correct graphs)
};

bool present(string x)
{
	for (int i = 0; i < 100; i++) {
		if (ar[i] == x) return true;
	}
	return false;
}

int index = 1;

void create(node *r)
{
	if (r == NULL) return;
	
	string txt;
	txt = r -> sym;
	
	if (!present(txt)) {
		return;
	}
	int j = index;
	for (int i = 0; i < vv[j].size(); i++) {
		r -> l[i] = new node();
		r -> l[i] -> sym = vv[index][i];
		r -> l[i] -> parent = r;
		r -> l[i] -> label = i;
		r -> l[i] -> counter = cnt;
		mp[cnt] = r -> l[i] -> sym;
		cnt++;
		for (int k = 0; k < 8; k++) {
			r -> l[i] -> l[k] = NULL;
		}
	}
	for (int i = 0; i < vv[j].size(); i++) {
		if (present(r -> l[i] -> sym)) {
			index++;
			create(r -> l[i]);
		}
	}
}

//Pre order Traversal to write in dot file
void pre(node *r)
{
	if (r) {
		if (r -> parent) {
			out << mp[r -> parent -> counter] << "_" << r -> parent -> counter << " -> ";
		}
		if (!present(mp[r -> counter])) {
			out << mp[r -> counter] << "_" << r -> counter << "[color=red]" << endl;
		} else {
			out << mp[r -> counter] << "_" << r -> counter << endl;
		}

		for (int i = 0; i < 8; i++) {
			pre(r -> l[i]);
		}
	}
}

//Irrelevant code, just for level order printing
void print(node *r)
{
	queue <node *> q;
	q.push(r);
	q.push(NULL);
	while (!q.empty()) {
		node *tmp = q.front();
		q.pop();
		if (tmp != NULL) {
			for (int i = 0; i < 8; i++) {
				if (tmp -> l[i] != NULL) {
					q.push(tmp -> l[i]);
				}
			}
		} else {
			if (!q.empty()) q.push(NULL);
		}
	}
}

int main()
{
	ifstream in("tree.txt");
	string s = "";
	
	out << "digraph {\nsize=\"18,22\"\nedge [color=black]\nnode [color=green, style=bold]\n";
	
	getline(in, s);
	stringstream ss;
	ss.str(s);
	string tmp;
	while (ss >> s) {
		vector <string> v;
		if (s == "(") {
			while (1) {
				ss >> tmp;
				if (tmp == ")") break;
				v.push_back(tmp);
			}
		}
		vv.push_back(v);
		v.clear();
	}

	node *root = NULL;
	root = new node();
	for (int i = 0; i < 8; i++) {
		root -> l[i] = NULL;
	}
	root -> sym = "S";
	root -> parent = NULL;
	root -> label = -1;
	root -> counter = cnt;
	mp[cnt] = root -> sym;
	cnt++;
	create(root);
	pre(root);
	
	out << "}\n";
}


