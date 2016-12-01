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
int barn[MAXN][MAXN];


void print_barn() {
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            printf("%d", barn[i][j]);
        }
        printf("\n");
    }
}

void input()
{
    int x, y;
    memset(barn, 0, sizeof(barn));
    scanf("%d %d", &N, &T);
    for(int i=0; i<T; i++) {
        scanf("%d %d", &x, &y);
        barn[x-1][y-1] = 1;
    }
//    print_barn();
}

int f[MAXN][MAXN];
int ans;

void solve()
{
    memset(f, 0, sizeof(f));

    ans = 0;
    for(int i=0; i<N; i++) {
        if(barn[i][0] == 0) {
            f[i][0] = 1;
        }else {
            f[i][0] = 0;
        }

        if(barn[0][i] == 0) {
            f[0][i] = 1;
        }else {
            f[0][i] = 0;
        }

        if(ans<f[i][0]) {
            ans = f[i][0];
        }
        if(ans<f[0][i]) {
            ans = f[0][i];
        }
    }
    
    for(int i=1; i<N; i++) {
        for(int j=1; j<N; j++) {
            if(barn[i][j] == 0) {
                f[i][j] = min(f[i-1][j-1], 
                    min(f[i-1][j], f[i][j-1])) + 1;
            }else {
                f[i][j] = 0;
            }
            if(f[i][j]>ans) {
                ans = f[i][j];
            }
        }
    }
}

void output()
{
    printf("%d\n", ans);
}

//#define DEBUG
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
