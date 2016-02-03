/*
ID:cyrano63
LANG:C++
TASK:game1
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
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MAXN	100
int N;
int board[MAXN];
int f[MAXN][MAXN];
int trace[MAXN][MAXN];
int sum[MAXN][MAXN];
int result;

void input()
{
	memset(board, 0, sizeof(board));
	scanf("%d\n", &N);
	for (int i=0; i<N; i++) {
		scanf("%d", &board[i]);
	}

	// init sum
	memset(sum, 0, sizeof(sum));
	for (int i=0; i<N; i++) {
		for (int j=i; j<N; j++) {
			int t = 0;
			for (int k=i; k<=j; k++) {
				t += board[k];
			}
			sum[i][j] = t;
		}
	}

	// init f, this is for memorize recursive algo
	// it will be reset by solve_non_rec()
//	memset(f, -1, sizeof(f));
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			f[i][j] = -1;
		}
	}
/*	for (int i=0; i<N; i++) {
		f[i][i]=board[i];
	}
	*/
}

int solve_non_rec() {
	//reset the change in input();
	memset(f, 0, sizeof(f));
	// init f
	f[0][0] = board[0];
	for (int i=1; i<N; i++) {
		f[0][i] = f[0][i-1] + board[i];
		f[i][i] = board[i];
	}

	for (int l=0; l<N; l++) {
		for (int i=0;i+l<N; i++) {
			int j = i+l;
			f[i][j] = MAX(sum[i][j]-f[i+1][j], sum[i][j]-f[i][j-1]);
		}
	}

	return f[0][N-1];
}

int solve1(int i, int j)
{
	if (i>j) return 0;
	if (i==j) return board[i];
	if (f[i][j] != -1) return f[i][j];
	int t1 = solve1(i+1, j);
	int t2 = solve1(i, j-1);
	if (t1>t2) f[i][j] = sum[i][j] - t2;
	else f[i][j] = sum[i][j] - t1;
//	f[i][j] = MAX(solve(i+1,j) + board[i], solve(i,j-1) + board[j]);
	return f[i][j];
}

int solve(int i, int j)
{
	if (i>j) return 0;
	if (i==j) return board[i];
	if (f[i][j] != -1) return f[i][j];
	int t1 = solve(i+1, j);
	int t2 = solve(i, j-1);
	if (sum[i+1][j] - t1 + board[i] > sum[i][j-1] - t2 + board[j]) {
		trace[i][j] = 0;
		f[i][j] = sum[i+1][j] - t1 + board[i];
	}
	else {
		trace[i][j] = 1;
		f[i][j] = sum[i][j-1] - t2 + board[j];
	}
//	f[i][j] = MAX(solve(i+1,j) + board[i], solve(i,j-1) + board[j]);
	return f[i][j];
}

void printTrace(int i, int j) {
	if (i>=j) return;
	if (trace[i][j] == 0) {
		printf("trace(%d, %d): %d\n", i, j, board[i]);
		printTrace(i+1, j);
	}else {
		printf("trace(%d, %d): %d\n", i, j, board[j]);
		printTrace(i, j-1);
	}
}

void output()
{
/*	int t;
	if (sum[0][N-1]-result > result) {
		t = sum[0][N-1]-result;}
	else t = result;
	*/
	printf("%d %d\n", result, sum[0][N-1]-result);

#ifdef DEBUG
	printf("result=%d\n", result);
	printf("sum[0,N-1]=%d\n", sum[0][N-1]);
	printTrace(0, N-1);
#endif
}

int main(void)
{
#ifndef DEBUG
	freopen("game1.in", "r", stdin);
	freopen("game1.out", "w", stdout);
#endif

	input();
//	result = solve1(0, N-1);
//	result = solve(0, N-1);
    result = solve_non_rec();
	output();

	return 0;
}
