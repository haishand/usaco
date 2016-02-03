/*
ID:cyrano63
LANG:C++
TASK:fence9
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

int N, M, P;
int ans;

void input()
{
	scanf("%d %d %d", &N, &M, &P);
}

void solve()
{
	double x1, x2;
	ans = 0;
	for (int y=1; y<M; y++) {
		x1 = (double)N*y/M;
		x2 = (double)(N-P)*y/M + P;
		ans += ceil(x2) - floor(x1) - 1;
//		printf("y=%d: x2 = %f, x1 = %f\n", y, x2, x1);
	}
}

void output()
{
	printf("%d\n", ans);
}

int main(void)
{
#ifndef DEBUG
	freopen("fence9.in", "r", stdin);
	freopen("fence9.out", "w", stdout);
#endif

	input();
	solve();
	output();

	return 0;
}
