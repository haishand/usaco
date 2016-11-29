/*
ID:cyrano63
LANG:C++
TASK:fence6
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

#define MAXN    100
#define MAX_ITEM_NUM    8

typedef struct {
    int num;
    int segIds[MAXN];
}AdjSeg;

typedef struct {
    int len;
    AdjSeg h;
    AdjSeg t;
}Segment;

int N;
Segment seg[MAXN];
int minP;

void input()
{
    int id;
    int s, l, N1, N2;

    scanf("%d", &N);
	
    minP = 0;
    for(int i=0; i<N; i++) {
        scanf("%d %d %d %d", &s, &l, &N1, &N2);
        seg[s].len = l;
        minP += l;
        seg[s].h.num = N1;
        seg[s].t.num = N2;
        for(int j=0; j<N1; j++) {
            scanf("%d", &id);
            seg[s].h.segIds[j] = id;
        }
        for(int j=0; j<N2; j++) {
            scanf("%d", &id);
            seg[s].t.segIds[j] = id;
        }
    }
}

void solve(int s, int c, int perim)
{
    if (s == c) {
        if (perim < minP) {
            minP = perim;
        }
        return;
    }
    for(int i=0; i<seg[c].t.num; i++) {
        solve(s, i, perim+seg[c].t.segIds[i]);
    }
}

void output()
{
    printf("%d\n", minP);
}

//#define DEBUG
int main(void)
{
#ifndef DEBUG
	freopen("fence6.in", "r", stdin);
	freopen("fence6.out", "w", stdout);
#endif

	input();

    for(int i=0; i<N; i++)  {
        for(int j=0; j<seg[i].t.num; j++)
            solve(i, seg[i].t.segIds[j], seg[i].len);
    }

	output();

	return 0;
}

