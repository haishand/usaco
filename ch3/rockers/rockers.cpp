/*
ID:cyrano63
LANG:C++
TASK:rockers
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

#define DEBUG

using namespace std;

int N, T, M;
int ans;
int song[100];
int length[100];
int used[100];
int b[100];

int minT = 30;	// used for work2
void input()
{
	memset(used, 0, sizeof(used));
	scanf("%d %d %d", &N, &T, &M);
	for (int i=0; i<N; i++) {
		scanf("%d", &song[i]);
		length[i+1] = song[i];

		// used for work2()
		if (minT>length[i+1]) {
			minT = length[i+1];
		}
	}
	for (int i=0; i<M; i++) {
		b[i] = T;
	}
}

#define MAX(a, b) ((a)>(b)?(a):(b))

void pack01()
{
	int f[30][30];
	int g[30];

	for(int i=1; i<=N; i++) {
		for(int j=minT; j<=T; j++) {
			f[i][j] = MAX(f[i-1][j], f[i-1][j-length[i]]+1);
		}
	}
	printf("%d\n", f[N][T]);

	for(int i=1; i<=N; i++) {
		for(int j=T; j>=length[i]; j--) {
			g[j] = MAX(g[j], g[j-length[i]]+1);
		}
	}
	printf("%d\n", g[T]);
}

int f[30][30];
int g[30];
int ff[30][30];
int w[30][30];
void work2()
{
	memset(f, 0, sizeof(f));
	memset(ff, 0, sizeof(ff));
	memset(w, 0, sizeof(w));

	for(int i=1; i<=N; i++) {
		for(int j=i; j<=N; j++) {
			memset(f, 0, sizeof(f));
			memset(g, 0, sizeof(g));
			for(int a=i; a<=j; a++) {
				for(int b=i; b<=a; b++) {
					f[a][length[b]] = 1;
				}
			}
			for(int k=i; k<=j; k++) {
				for(int v=length[k]; v<=T; v++) {
					f[k][v] = MAX(f[k][v], MAX(f[k-1][v], f[k-1][v-length[k]] + 1));
				}	
				for(int v=T; v>=length[k]; v--) {
					g[v] = MAX(g[v], g[v-length[k]]+1);
				}
			}
//			printf("f[%d][T]=%d, g[T]=%d\n", j, f[j][T], g[T]);
//			assert(f[j][T] == g[T]);
			w[i][j] = f[j][T];
//			w[i][j] = g[T];
		}
	}

	/*
	for(int i=0; i<=N; i++) {
		for (int j=i; j<=N; j++) {
			printf("w[%d][%d]=%d\n", i, j, w[i][j]);
		}
	}
	*/
	
	/*
	for(int k=0; k<N; k++) {
		for(int i=k; i<N; i++) {
			for(int j=0; j+length[i]<=T; j++) {
				f[i+1][j+length[i]] = MAX(f[i][j+length[i]], f[i][j] + 1); 	
			}
		}		
		
	}

	for(int i=1; i<=N; i++) {
		for (int j=i; j<=N; j++) {
			if (i==j) {
				if (length[i]<=T)
					w[i][j] = 1;
			}
			else w[i][j] = f[j][T] - f[i-1][T];
			assert(w[i][j]>=0);
		}
	}
	*/

	for(int k=1; k<=M; k++) {
		for(int j=0; j<=N; j++) {
			int m = 0;
			for(int i=0; i<j; i++) {
				if (m<ff[k-1][i] + w[i+1][j]) {
					m = ff[k-1][i] + w[i+1][j];
				}
			}
			ff[k][j] = m;
		}
	}
//	printf("%d\n", f[N][T]);
//	printf("%d\n", w[0][N]);
//	printf("%d\n", ff[M][N]);
}

#define MAX(a, b) ((a)>(b)?(a):(b))
int dp[30][30][30];
int best = 0;
void work()
{
	for(int a=0; a<M; a++) {
		for(int b=0; b<=T; b++) {
			for(int c=0; c<=N; c++) {
				for(int d=c+1; d<=N; d++) {
					if (b+length[d]<=T) {
						if (dp[a][b+length[d]][d]<dp[a][b][c]+1) {
							dp[a][b+length[d]][d] = dp[a][b][c]+1;
						}
					}else {
						if (dp[a+1][length[d]][d] < dp[a][b][c]+1) {
							dp[a+1][length[d]][d] = dp[a][b][c]+1;
						}
					}
				}
				if (dp[a][b][c]>best) {
					best = dp[a][b][c];
				}
			}
		}
	}
}

void dfs(int k, int a, int b, int c)
{
//	if (f[k][a][b][c]) return;
//	f[k][a][b][c] = 1;
    if (c+N-a<ans) return;
	if (a==N || k==M) {
		// found a solution
		if (c>ans) {
			ans = c;
/*			printf("a=%d, k=%d, ans = %d:",a, k, ans);
			for(int j=0; j<N; j++) {
				if (used[j]) {
					printf("%d\t", song[j]);
				}
			}
			printf("\n"); */
		}
		return;
	}	

//	dfs(k, a+1, b, c);
	if (!used[a] && b+song[a]<=T) {
		used[a] = 1;
		dfs(k, a+1, b+song[a], c+1);
		used[a] = 0;
		dfs(k, a+1, b, c);
	}else {
		dfs(k+1, a, 0, c);
		dfs(k, a+1, b, c);
	}
/*	for(int i=a; i<N; i++) {
		dfs(k, a+1, b, c);
		if (!used[i] && b+song[i]<=T) {
			used[i] = 1;
			dfs(k, a+1, b+song[i], c+1);
			used[i] = 0;
		}else {
			dfs(k+1, 0, 0, c);
		}
	}
	*/
}

void solve()
{
//	ans = 0;
//	dfs(0, 0, 0, 0);
//	work();
//	work2();
	pack01();
}

void output()
{
	//printf("%d\n", ans);
//	printf("%d\n", best);
//	printf("%d\n", ff[M][N]);
}

int main(void)
{
#ifndef DEBUG
	freopen("rockers.in", "r", stdin);
	freopen("rockers.out", "w", stdout);
#endif

	input();
	solve();
	output();
	/*
#ifdef DEBUG
	stop = clock();
	double runtime = stop - start;
	printf("runtime: %lf\n", runtime);
#endif
*/
	return 0;
}
