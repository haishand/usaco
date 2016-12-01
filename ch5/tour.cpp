/*
ID:cyrano63
LANG:C++
TASK:tour
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

int N, V;
map<string, int> city_no;
int airline[MAXN][MAXN];

void print(int (*p)[MAXN]) {

    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            printf("%d", p[i][j]);
        }
        printf("\n");
    }
}

void input()
{
	string city;

	cin>>N>>V;
	for(int i=0; i<N; i++) {
		cin>>city;
		city_no[city] = i+1;	// make sure city number start from 1
	}

	string from, to;
	memset(airline, 0, sizeof(airline));
	for(int i=0; i<V; i++) {
		cin>>from>>to;
		airline[city_no[from]][city_no[to]] = 1;
		airline[city_no[to]][city_no[from]] = 1;
	}
//    print(airline);
}

int f[MAXN][MAXN];	
void solve()
{
	memset(f, 0, sizeof(f));

	f[1][1] = 1;
	for(int i=1; i<N; i++) {
		for(int j=i+1; j<=N; j++) {
			for(int k=1; k<j; k++) {
				if(airline[k][j] && f[i][k]>0) {
					f[i][j] = max(f[i][j], f[i][k]+1);
				}
			}
            f[j][i] = f[i][j];

		}
	}

}

void output()
{
    int ans = 0;
    for(int i=1; i<N; i++) {
        if(airline[i][N] && ans < f[i][N]) {
            ans = f[i][N];
        }
    }
    printf("%d\n", ans>1?ans:1);
}

//#define DEBUG
int main(void)
{
#ifndef DEBUG
	freopen("tour.in", "r", stdin);
	freopen("tour.out", "w", stdout);
#endif

	input();
	solve();
	output();

	return 0;
}
