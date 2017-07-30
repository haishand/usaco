/*
ID:cyrano63
LANG:C++
TASK:twofive
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

#define FOR(i,j,k) for(i=j;i<=k;++i)
#define N	6

using namespace std;

char L;
int M;
string grid;
int l[6];
int x[26], y[26];
int dp[N][N][N][N][N];

int ans_W;
char ans_N[6][6];

int dfs(char c)
{
	int i;

	int &ans = dp[l[1]][l[2]][l[3]][l[4]][l[5]];
	if(ans == -1) {
        ans = 0;
		if(!x[c]) {
			FOR(i, 1, 5) {
				if(l[i]<l[i-1]) {
					++l[i];
					ans += dfs(c+1);
					--l[i];
				}
			}
		}else {
			if(l[x[c]]<l[x[c]-1] && l[x[c]]+1==y[c]) { // c should be put one by one
				++l[x[c]];
				ans += dfs(c+1);
				--l[x[c]];
			}
		}
	}

	return ans;
}

int compute()
{
	memset(l, 0, sizeof(l));
	memset(dp, -1, sizeof(dp));
	dp[5][5][5][5][5] = 1;
	l[0] = 5;
	return dfs(0);
}

void solve_N()
{
    int c, i, j, t;

	FOR(i, 1, 5) FOR(j, 1, 5) FOR(c, 0, 25) {
		if(!x[c]) {
			x[c] = i; y[c] = j;
			t = compute();
			if(M>t) M-=t;
			else break;
			x[c] = 0; y[c] = 0;
		}
	}

    FOR(c, 0, 25) ans_N[x[c]][y[c]] = c + 'A';
    FOR(i, 1, 5) {
        FOR(j, 1, 5) {
            putchar(ans_N[i][j]);
        }
    }
    printf("\n");
}


void solve_N1()
{


}

void solve_W()
{
    int c, n = 1;
    int i, j, k;

    int ng = 0;
    FOR(i, 1, 5) {
        FOR(j, 1, 5) {
            c = grid[ng++] - 'A';
            FOR(k, 0, c-1) {
                if(!x[k]) {
                    x[k] = i; y[k] = j;
                    n += compute();
                    x[k] = 0; y[k] = 0;
                }
            }
            x[c] = i; y[c] = j;
        }
    }
    printf("%d\n", n);
}


void output()
{
}

//#define DEBUG

int main(void)
{
#ifndef DEBUG
    freopen("twofive.in", "r", stdin);
    freopen("twofive.out", "w", stdout);
#endif

    scanf("%c\n", &L);
    switch(L) {
    case 'N':
        scanf("%d", &M);
        solve_N();
        break;
    case 'W':
        cin>>grid;
        solve_W();
        break;
    default:
        printf("error.\n");

    }

    return 0;
}

