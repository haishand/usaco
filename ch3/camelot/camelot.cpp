/*
ID:cyrano63
LANG:C++
TASK:camelot
*/

#include <iostream>  
#include <cmath>  
#include <cstdio>  
#include <cstring>  
#include <vector>  
#include <cassert>  
#include <string>  
#include <algorithm>  
#include <stack>  
#include <set>  
#include <queue>  
#include <map>
#include <climits>

using namespace std;

#define min(x, y) ({ \
	typeof(x) _min1 = (x); \
	typeof(y) _min2 = (y); \
	(void) (&_min1 == &_min2); \
	_min1 < _min2 ? _min1 : _min2; })

#define max(x, y) ({ \
	typeof(x) _max1 = (x); \
	typeof(y) _max2 = (y); \
	(void) (&_max1 == &_max2); \
	_max1 < _max2 ? _max2 : _max1; })
//#define min(x, y) ((x)>(y)?(y):(x))
//#define max(x, y) ((x)>(y)?(x):(y))

#define MAXR	40	// 30
#define MAXC	40	// 26

#define visited(v) visited[v.x][v.y]

typedef struct {
	int x, y;
}Point;

FILE *fin, *fout;
Point knight[1600];
int nknight;

// knight moves
int tx[8]={1, 2, 2, 1,-1,-2,-2,-1};
int ty[8]={2, 1,-1,-2,-2,-1, 1, 2};
//int tx[8]={-2,-2,-1,1,2,2,1,-1};
//int ty[8]={-1,1,2,2,1,-1,-2,-2};
// use easy data to test algorithm
//int tx[8]={0,1,1,1,0,-1,-1,-1};
//int ty[8]={1,1,0,-1,-1,-1,0,1};

int R, C;
int kx, ky;		// king's location
int d[40][40][40][40]; 	
bool visited[40][40];
int sum[40][40];	// the sum steps for all knights come to (i,j)
int ans;

void input()
{
	char c;
	int d;

	fin = fopen("camelot.in", "r");
	assert(fin != NULL);
	
	fscanf(fin, "%d %d\n", &R, &C);
	fscanf(fin, "%c %d", &c, &d);
	
	// be careful to row/col
	ky = c - 'A' + 1; kx = d;
	
	nknight = 0;
	while(fscanf(fin, "%c", &c) != EOF) {
		if (c<65 || c>90) continue;
		fscanf(fin, "%d", &d);
		// be careful about the row/col
		knight[nknight].y = c - 'A' + 1;
		knight[nknight].x = d;
		++nknight;
	}

	fclose(fin);
}


void spfa(int sx, int sy)
{
	// spfa algo
	Point u, v;
	queue<Point> q;

	for (int i=0; i<40; i++) {
		for (int j=0; j<40; j++) {
			visited[i][j] = false;
		}
	}

	Point s;
	s.x = sx; s.y = sy;
	q.push(s);

	d[sx][sy][sx][sy] = 0;
	while(!q.empty()) {
		u = q.front();
		q.pop();
		visited(u) = true;
		for (int i=0; i<8; i++) {
			v.x = u.x + tx[i];
			v.y = u.y + ty[i];
			if (v.x > 0 && v.x <= R && v.y > 0 && v.y <= C) {
				if (d[sx][sy][u.x][u.y] != INT_MAX && d[sx][sy][v.x][v.y] > d[sx][sy][u.x][u.y] + 1) {
					d[sx][sy][v.x][v.y] = d[sx][sy][u.x][u.y] + 1;
					if (!visited(v)) {
						visited(v) = true;
						q.push(v);
					}
				}
			}
		}	
	}

}

void test_func()
{
	spfa(1, 3);
	printf("debug\n");
	printf("%d\n",d[1][3][1][1]);
	printf("%d\n",d[1][1][1][8]);
	printf("%d\n",d[1][1][8][1]);
	printf("%d\n",d[1][1][5][5]);

	printf("%d\n", min(2,5));
	printf("%d\n", max(2,5));
	printf("debug end\n");
}

int cnt;
void check_spfa() 
{
	cnt = 0;
	for (int i=1; i<=R; i++) {
		for (int j=1; j<=C; j++) {
			for (int k=1; k<=R; k++) {
				for (int l=1; l<=C; l++) {
					if (d[i][j][k][l] == INT_MAX) {
						++cnt;
					}
				}
			}
		}
	}
	printf("cnt = %d\n", cnt);
}

void check_knights()
{
	for (int i=0; i<nknight; i++) {
		if (knight[i].x <1 || knight[i].x>R || 
				knight[i].y <1 || knight[i].y >C) {
			printf("%d knight:(%d, %d)\n", i, knight[i].x, knight[i].y);
		}
	}	
}

void solve()
{
	// spfa init
	for (int i=0; i<40; i++) {
		for (int j=0; j<40; j++) {
			for (int k=0; k<40; k++) {
				for (int l=0; l<40; l++) {
					d[i][j][k][l] = INT_MAX;
				}
			}
		}
	}

	// spfa
	for (int i=1; i<=R; i++) {
		for (int j=1; j<=C; j++) {
			spfa(i,j);
		}
	}

//	check_spfa();

	for (int i=1; i<=R; i++) {
		for(int j=1; j<=C; j++) {
			sum[i][j] = 0;
			for (int k=0; k<nknight; k++) {
				if (d[knight[k].x][knight[k].y][i][j] == INT_MAX) {
					sum[i][j] = INT_MAX;
					continue;
				}
//				assert(knight[k].x >= 1 && knight[k].x <=R);
//				assert(knight[k].y >= 1 && knight[k].y <=C);
				sum[i][j] += d[knight[k].x][knight[k].y][i][j];
//				assert(sum[i][j] != INT_MAX);
			}
		}	
	}

	ans = INT_MAX;

	// not bind with knight
	for (int i=1; i<=R; i++) {
		for (int j=1; j<=C; j++) {
			if (sum[i][j] == INT_MAX) continue;
			int dd = max(abs(kx-i), abs(ky-j)) + sum[i][j];
			if (dd<ans) {
				ans = dd;
			}
		}
	}

	// bind with knight
	for(int i=1; i<=R; i++) {
		for (int j=1; j<=C; j++) {
			if (sum[i][j] == INT_MAX) continue;
			for (int x=max(kx-2, 1); x<=min(kx+2, R); x++) {
				for (int y=max(ky-2, 1); y<=min(ky+2, C); y++) {
//			for (int x=1; x<=R; x++) {
//				for (int y=1; y<=C; y++) {
					for (int k=0; k<nknight; k++) {
						if (d[knight[k].x][knight[k].y][x][y] == INT_MAX || d[x][y][i][j] == INT_MAX || d[knight[k].x][knight[k].y][i][j] == INT_MAX) continue;
						int dd = max(abs(kx-x), abs(ky-y)) + d[knight[k].x][knight[k].y][x][y] + d[x][y][i][j] + sum[i][j] - d[knight[k].x][knight[k].y][i][j];
						if (dd < ans) {
							ans = dd;
						}
					}
				}
			}
		}
	}

}

void output()
{
	fout = fopen("camelot.out", "w");
	assert(fout != NULL);

	printf("%d\n", ans);
	fprintf(fout, "%d\n", ans);
	fclose(fout);
}

int main(void)
{
	input();
//	check_knights();
	if (nknight == 0) {
		ans =  0;
	}
	else {
		solve();
	}
//	test_func();
	output();

	return 0;
}
