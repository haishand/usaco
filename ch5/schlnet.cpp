/*
ID:cyrano63
LANG:C++
TASK:schlnet
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

#define MAXN	101

int N;
bool g[MAXN][MAXN];
int sol1 = 0, sol2 = 0;

void input()
{
    int recv;

	scanf("%d", &N);
	memset(g, false, sizeof(g));
	for(int i=0; i<N; i++) {
		scanf("%d", &recv);
		while(recv != 0) {
			g[i][recv] = true;
			g[recv][i] = true;
			scanf("%d", &recv);
		}
	}
}

bool visited[MAXN];

void dfs(int v)
{
	visited[v] = true;
	for(int u=0; u<N; u++) {
		if(g[v][u]) {
			dfs(u);
		}
	}
}

void solve()
{
    // task 1
    memset(visited, false, sizeof(visited));
	for(int v = 0; v<N; v++) {
		if(!visited[v]) {
			dfs(v);
			++sol1;
		}
	}
}

void output()
{
	printf("%d\n", sol1);
}

#define DEBUG
int main(void)
{
#ifndef DEBUG
	freopen("schlnet.in", "r", stdin);
	freopen("schlnet.out", "w", stdout);
#endif

	input();
	solve();
	output();

	return 0;
}
