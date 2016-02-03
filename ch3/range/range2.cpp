/*
ID:cyrano63
LANG:C++
TASK:range
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

//#define DEBUG 
#define MAXN	250	
int dp[MAXN][MAXN];		// biggest square with lower right corner(i,j)
int m[MAXN][MAXN];
int cnt[MAXN];
int N;

void input()
{
	memset(dp, 0, sizeof(dp));

	scanf("%d\n", &N);
	char c;

	for (int i=1; i<=N; i++) {
		for (int j=1; j<=N; j++) {
			dp[0][i][j] = m[i][j] = (getc(stdin) == '1');
		}
		assert(getc(stdin) == '\n');
	}
}

void solve()
{
	memset(cnt, 0, sizeof(cnt));

	for (int i=1; i<=N; i++) {
		for (int j=1; j<=N; j++) {
			

		}
	}
}

int main(void)
{
#ifndef DEBUG
	freopen("range.in", "r", stdin);
	freopen("range.out", "w", stdout);
#endif

	input();
	solve();
	output();

	return 0;
}
