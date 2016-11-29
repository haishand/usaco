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

#define N    5

int graph[N][N];
int visited[N];

void dfs(int v)
{
    visited[v] = 1;
    for(int u=0; u<N; u++){
        if(graph[v][u] && !visited[u]) {
            dfs(u);
            printf("%d\n", u);
        }
    }
}

int main(void)
{
    memset(graph, 0, sizeof(graph));

    graph[0][2] = 1;
    graph[0][3] = 1;
    graph[1][0] = 1;
    graph[2][1] = 1;
    graph[3][4] = 1;

    memset(visited, 0, sizeof(visited));

    dfs(0);

    return 0;
}
