/*
ID:cyrano63
LANG:C++
TASK:shopping
*/

#include <iostream>  
#include <cmath>  
#include <cstdio>  
#include <cstring>  
#include <vector>  
#include <cassert>  
#include <string>  
#include <algorithm>  
#include <stack>  
#include <set>  
#include <queue>  
#include <map>

using namespace std;

FILE *fin, *fout;

void input()
{
	fin = fopen("camelot.in", "r");
	assert(fin != NULL);

	fclose(fin);
}

void solve()
{
	
}

void output()
{
	fout = fopen("camelot.out", "w");
	assert(fout != NULL);

	fclose(fout);
}

int main(void)
{
	input();
	solve();
	output();

	return 0;
}
