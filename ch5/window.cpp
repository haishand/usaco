/*
ID:cyrano63
LANG:C++
TASK:window
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

FILE *fin, *fout;
char s[100];

struct Window {
    char id;
    int x1, y1, x2, y2;
};

int nwin;
Window win[100];

double dfs(int , int, int, int, int);
void create() {
    char id;
    int x1, y1, x2, y2;

    sscanf(s, "w(%c,%d,%d,%d,%d)",
        &id, &x1, &y1, &x2, &y2);

    win[nwin] = (Window){id, x1, y1, x2, y2};
    ++nwin;
}

void top() {
    char id;
    int i, j;

    sscanf(s, "t(%c)", &id);

    for(i=0; i<nwin; i++) {
        if(win[i].id == id) break;
    }
    if(i<nwin) {
        Window t = win[i];
        for(j=i; j<nwin-1; j++) {
            win[j] = win[j+1];
        }
        win[nwin-1] = t;
    }
}

void bottom() {
    char id;
    int i, j;

    sscanf(s, "b(%c)", &id);

    for(i=0; i<nwin; i++) {
        if(win[i].id == id) break;
    }
    if(i<nwin) {
        Window t = win[i];
        for(j=i; j>=0; j--) {
            win[j] = win[j-1];
        }
        win[0] = t;
    }
}

void destroy() {
    char id;
    int i, j;

    sscanf(s, "d(%c)", &id);

    for(i=0; i<nwin; i++) {
        if(win[i].id == id) break;
    }
    if(i<nwin) {
        for(j=i; j<nwin; j++) {
            win[j] = win[j+1];
        }
        --nwin;
    }
}

void output() {
    char id;
    int i;
    double varea = 0, area;

    sscanf(s, "s(%c)", &id);
    for(i=0; i<nwin; i++) {
        if(win[i].id == id) break;
    }
    varea = dfs(i+1, win[i].x1, win[i].y1, win[i].x2, win[i].y2);
    area = abs((win[i].x1-win[i].x2) * (win[i].y1-win[i].y2));
    printf("varea/area = %.3f\n", varea/area * 100);
}

double dfs(int k, int x1, int y1, int x2, int y2)
{
    double varea = 0;

    if(k==nwin) {
        varea = abs((x1-x2)*(y1-y2));
    }else {

        if(win[k].x1>x2 || win[k].x2<x1 || win[k].y2>y1 || win[k].y1<y2) {
            // no block
            varea = dfs(k+1, x1, y1, x2, y2);
        }else {
            // block
            if(win[k].x1>x1) {
                varea += dfs(k+1, x1, y1, win[k].x1, y2);
            }
            if(win[k].x2<x2) {
                varea += dfs(k+1, win[k].x2, y1, x2, y2);
            }
            if(win[k].y1<y1) {
                varea += dfs(k+1, win[k].x1, y1, win[k].x2, win[k].y1);
            }
            if(win[k].y2>y2) {
                varea += dfs(k+1, win[k].x1, win[k].y2, win[k].x2, y2);
            }
        }
    }

    return varea;
}

void loop()
{
    nwin = 0;
    while(scanf("%s", s) != EOF) {
        switch(s[0]) {
            case 'w':
                create();
                break;
            case 't':
                top();
                break;
            case 'b':
                bottom();
                break;
            case 'd':
                destroy();
                break;
            case 's':
                output();
                break;

        }
    }
    fclose(fin);
}

#define DEBUG
int main(void)
{
#ifndef DEBUG
	freopen("window.in", "r", stdin);
	freopen("window.out", "w", stdout);
#endif

	loop();

	return 0;
}
