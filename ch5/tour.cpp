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

void input()
{
	string city;

	cin>>N>>V;
	for(int i=0; i<N; i++) {
		cin>>city;
		city_no["city"] = i+1;	// make sure city number start from 1
	}

	string from, to;
	memset(airline, 0, sizeof(airline));
	for(int i=0; i<V; i++) {
		cin>>from>>to;
		airline[city_no[from]][city_no[to]] = 1;
	}
}

int f[MAXN][MAXN];	// f[i][j] = max{f[ ]}
void solve()
{
    int k1, k2, temp1, temp2;

	memset(f, 0, sizeof(f));

	f[1][1] = 1;
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=N; j++) {
			temp1 = 0, temp2 = 0;
			for(int k1=1; k1<i; k1++) {
				if(airline[k1][i]) {
					temp1 = max(temp1, f[k1][j]);
				}
			}
			for(int k2=i+1; k2<j; k2++) {
				if(airline[k2][j]) {
					temp2 = max(temp2, f[i][k2]);
				}
			}
			f[i][j] = max(f[i][j], max(temp1, temp2)+1);
		}
	}

}

void output()
{
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            cout<<f[i][j]<<endl;
        }
    }

}

#define DEBUG
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
