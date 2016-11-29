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

#define MAXN	200

int N;
bool g[MAXN][MAXN];
bool rg[MAXN][MAXN];    // transpose graph
bool ng[MAXN][MAXN];

void input()
{
    int recv;

	scanf("%d", &N);
	memset(g, false, sizeof(g));
	memset(rg, false, sizeof(rg));
	for(int i=1; i<=N; i++) {
		scanf("%d", &recv);
		while(recv != 0) {
			g[i][recv] = true;
			rg[recv][i] = true;
			scanf("%d", &recv);
		}
	}
}

bool visited[MAXN];
vector<int> post;

void dfs1(int v)
{
	visited[v] = true;
	for(int u=1; u<=N; u++) {
		if(g[v][u] && !visited[u]) {
			dfs1(u);
		}
	}
	post.push_back(v);
}

int comp[MAXN];		// component index
int ncomp;

void dfs2(int v, int k) {
	comp[v] = k;
	for(int u=1; u<=N; u++) {
		if(rg[v][u] && comp[u] == 0) {
			dfs2(u, k);
		}
	}
}

void scc() {

	// dfs original graph and generate post order
	memset(visited, false, sizeof(visited));
	for(int v=1; v<=N; v++) {
		if(!visited[v]) {
			dfs1(v);
		}
	}

	// dfs transpose graph by post order
	memset(comp, 0, sizeof(comp));
	ncomp = 0;
	for(int i=post.size()-1; i>=0; i--) {
//		printf("*%d\n", post[i]);
		if(comp[post[i]] == 0)
			dfs2(post[i], ++ncomp);
	}
}

int sol1, sol2;
void solve()
{
	scc();

	// generate scc graph
	int in[MAXN], out[MAXN];
	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));
	for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            if(g[i][j]) {
                ng[comp[i]][comp[j]] = true;
                if(comp[i]!=comp[j]) {
                    ++in[comp[j]];
                    ++out[comp[i]];
                }
            }
        }
	}

	sol1 = 0; sol2 = 0;
    for(int i=1; i<=ncomp; i++) {
        if(in[i] == 0)
            ++sol1;
        if(out[i] == 0)
            ++sol2;
    }
}

void output()
{
    if(ncomp == 1) {
        printf("%d\n", 1);
        printf("%d\n", 0);
    }else {
        printf("%d\n", sol1);
        printf("%d\n", max(sol1, sol2));
    }
}

//#define DEBUG
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
