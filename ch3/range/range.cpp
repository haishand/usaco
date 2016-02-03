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
char dp[2][MAXN][MAXN];
char m[MAXN][MAXN];
int cnt[MAXN];
int N;

void input()
{
	memset(dp, 0, sizeof(dp));

	scanf("%d\n", &N);
	char c;

	/*
	// my way, looks ugly
	for (int i=1; i<=N; i++) {
		for (int j=1; j<=N; j++) {
			scanf("%c", &c);
			m[i][j] = c-'0';
			if (m[i][j]==1)
				dp[0][i][j]=1;
		}
		scanf("%c", &c);	// /n
	}
	*/

	// more elegent way
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

	for (int l=2; l<=N; l++) {
		for (int i=1; i<=N; i++) {
			for (int j=1; j<=N; j++) {
				if (i+l-1>N || j+l-1>N || !dp[0][i][j]) continue;
				for (int k=0; k<l-1; k++) {
					dp[0][i][j] &= m[i+k][j+l-1] & m[i+l-1][j+k];	
				}
				/*
				for (int k=0; k<l-1; k++) {
					dp[0][i][j] &= m[i+l-1][j+k];
				}
				*/
				if (dp[0][i][j] && m[i+l-1][j+l-1]) {
					dp[1][i][j] = 1;
					++cnt[l];
				}
			}
		}
		for (int i=1; i<=N; i++) {
			for (int j=1; j<=N; j++) {
				dp[0][i][j] = dp[1][i][j];
				dp[1][i][j] = 0;
			}
		}

		if (cnt[l] == 0) {
			break;
		}
		else {
			printf("%d %d\n", l, cnt[l]);
		}
		
	}	
}

void output()
{
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
