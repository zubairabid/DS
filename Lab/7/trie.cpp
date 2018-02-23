#include<bits/stdc++.h>
using namespace std;
#define MAXM 26

struct Node {
	struct Node* ptr[MAXM];
	int count, finish;
	Node() {
		count = 0, finish = 0;
		for(int i = 0; i < MAXM; i++) ptr[i] = NULL;
	}

	void insert(string& str, int i=0) {
		int index = str[i] - 'a';
		count ++;
		if (ptr[index] == NULL) {
			ptr[index] = new Node();
		}
		if (i != str.length() - 1) {
			ptr[index]->insert(str, i+1);
		}
		else {
			ptr[index]->finish ++;
		}
	}

	void print() {
		for (int i=0; i<MAXM; i++) {
			if (ptr[i] == NULL) continue;
			char c = 'a' + i;
			cout << c << endl;
			ptr[i]->print();
		}
	}

	void print_full(string prefix = ""){
		for (int i=0; i<finish; i++) cout << prefix << endl;
		for (int i=0; i<MAXM; i++) {
			if (ptr[i] == NULL) continue;
			char c = 'a' + i;
			ptr[i]->print_full(prefix + c);
		}
	}

	bool search(string str, int i = 0) {
		if (i == str.length()) 
			return finish > 0;

		int index = str[i] - 'a';
		if (ptr[index] == NULL) return false;
		return ptr[index]->search(str, i+1);
	}

	bool del(string str, int i = 0) {
		if (i == str.length()) { 
			finish --;
			return finish <= 0;
		}
		int index = str[i] - 'a';
		if (ptr[index]->del(str, i+1)) {
			delete(ptr[index]);
			ptr[index] = NULL;
		}
		return false;
	}
};

int main(){
	Node root;
	string q;
	char f;
	while((cin >> f) && (f != 'q')) {
		switch (f) {
			case 'i':
				cin >> q;
				root.insert(q);
				break;
			case 'f':
				root.print_full();
				break;
			case 'p':
				root.print();
				break;
			case 's':
				cin >> q;
				cout << root.search(q) << endl;
				break;
			case 'd':
				cin >> q;
				root.del(q);
		}
	}
	return 0;
}
