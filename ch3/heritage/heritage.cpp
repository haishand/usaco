/*
ID:cyrano63
LANG:C++
TASK:heritage
*/

#include <iostream>  
#include <cmath>  
#include <cstdio>  
#include <cstdlib>
#include <cstring>  
#include <vector>  
#include <cassert>  
#include <string>  
#include <algorithm>  
#include <stack>  
#include <set>  
#include <queue>  
#include <map>

//#define DEBUG

using namespace std;

string s1, s2;
string s;

string makePostOrder(string inOrder, string preOrder)
{
	if (inOrder.empty() || preOrder.empty()) return "";
	char root = preOrder[0];
	int k = inOrder.find(root);
	if (k == string::npos) return "";
	string left = inOrder.substr(0, k);
	string right = inOrder.substr(k+1, inOrder.size());
	string postOrder = makePostOrder(left, preOrder.substr(1, left.size()+1)) +
		makePostOrder(right, preOrder.substr(left.size()+1)) + root;
	return postOrder;
}

void input()
{
	cin>>s1;
	cin>>s2;
}

void solve()
{
	s = makePostOrder(s1, s2);
}

void output()
{
	cout<<s<<endl;
}

int main(void)
{
#ifndef DEBUG
	freopen("heritage.in", "r", stdin);
	freopen("heritage.out", "w", stdout);
#endif

	input();
	solve();
	output();

	return 0;
}
