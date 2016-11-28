/*
ID:cyrano63
LANG:C++
TASK:bigbrn
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

using namespace std;

#define MAXN    1001

int N, T;
int map[MAXN][MAXN];

void input()
{
    memset(map, 0, sizeof(map));
    scanf("%d %d", &N, &T);
    for(int i=0; i<T; i++) {
        scanf("%d %d", &x, &y);
        map[x][y] = 1;
    }    
}

void solve()
{
}

void output()
{
}

int main(void)
{
#ifndef DEBUG
	freopen("bigbrn.in", "r", stdin);
	freopen("bigbrn.out", "w", stdout);
#endif

	input();
	solve();
	output();

	return 0;
}
