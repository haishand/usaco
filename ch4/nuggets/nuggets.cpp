/*
ID:cyrano63
LANG:C++
TASK:nuggets
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

#define MAXN    10

int N;
int box[MAXN];
int sum;
int ans;
set<int> s;

void input()
{
    scanf("%d", &N);

    sum = 0;
    for(int i=0; i<N; i++) {
        scanf("%d", &box[i]);
        sum += box[i];
    }
	sort(box, box+N);
}

int gcd(int x, int y)
{
   if(x==0) return y;
   else return gcd(y%x, x);
}

int lcm(int x, int y)
{
    return x*y/gcd(x,y);
}

bool can_rep(int num) 
{
	if(num==0) return true;

    bool flag = false;
    for(int i=0; i<N; i++) {
       if (num>=box[i]) {
           flag = can_rep(num-box[i]);
       }
       if(flag) return true;
    }
    return false;
}

void solve()
{
    for(int i=1; i<=sum; i++) {
        if(!can_rep(i)) {
            ans = i;
        }
    }
}

void solve2()
{
    int g = box[0];
    for(int j=1; j<N; j++) {
        g = gcd(g, box[j]);
    }
    if(g!=1) {
        ans = 0;
        return;
    }

    int min = box[0];
    for(int i=1; i<N; i++) {
        if (box[i]<min){
            min = box[i];
        } 
    }    

    s.clear();
    for(int i=1; i<min; i++) {
        s.insert(i);
    }
    ans = min-1;
    for(int i=min+1; i<=lcm(box[N-1], box[N-2]); i++) {
        bool found = false;
        for(int j=0; j<N; j++) {
            if(i-box[j]>=0) {
                found = (s.find(i-box[j]) != s.end());
                if(!found) break;
            }
        }
        if(found) {
            s.insert(i);
            ans = i;
        }
    }
}

void output()
{
    printf("%d\n", ans);
}

int main(void)
{
#ifndef DEBUG
	freopen("nuggets.in", "r", stdin);
	freopen("nuggets.out", "w", stdout);
#endif

	input();
	solve2();
	output();

	return 0;
}
