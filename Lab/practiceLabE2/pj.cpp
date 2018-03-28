//https://www.codechef.com/problems/CL16BF
#include <bits/stdc++.h>
using namespace std;

struct trie
{
  trie* next[26];
};

trie* new_trie()
{
  trie* temp = new trie;

  for (int i=0; i<26; i++)
    temp->next[i] = NULL;

  return temp;
}

void insert(trie* root, string name)
{
  trie* temp1 = root;
  for (int i = 0; i < name.length(); i++)
  {
    int index = name[i] - 'a';
    if (temp1->next[index] == NULL)
      temp1->next[index] = new_trie();
    temp1 = temp1->next[index];
  }

}

set <string> keys;

void search(trie* root, string key)
{
    trie* pCrawl = root;
  int i;
    for (i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->next[index])
        {
          break;
        }
        pCrawl = pCrawl->next[index];
    }

    if(i == key.length()) { cout<<"-1\n"; exit(0); }

    keys.insert(key.substr(0,i+1));
}

trie* root = new_trie();

int main()
{
  set <string> blocked;

  int n;
  char c;
  string temp;

  cin >> n;
  for (int i = 0; i < n; ++i)
  {
    cin >> c >> temp;
    if(c == '+')
      insert(root,temp);
    else
      blocked.insert(temp);
  }

  for (set<string>::iterator it = blocked.begin(); it != blocked.end(); it++ )
        search(root,*it);

  cout << keys.size() << '\n';

  for (set<string>::iterator it = keys.begin(); it != keys.end(); it++ )
        cout << *it <<'\n';

  return 0;
} 
