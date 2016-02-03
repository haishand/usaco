/*
ID:cyrano63
LANG:C++
TASK:shopping
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

using namespace std;

int S;	// special offers
int num[5] = {0};
int price[5] = {0};
int special[100][6] = {0};	// special[x][5] stands for the reduce price
FILE *fin, *fout;
int code_map[1000] = {0};
struct item_data {
	int code, num;
};
struct raw_data {
	struct item_data item[100];
	int n;
	int price;
};
struct raw_data raw[100];

int f[6][6][6][6][6];

void input() 
{
	int c, k, p, n, B;

	fin = fopen("shopping.in", "r");
	assert(fin != NULL);

	fscanf(fin, "%d\n", &S);
	for (int i=0; i<S; i++) {
		fscanf(fin, "%d", &n);
		raw[i].n = n;
		for (int j=0; j<n; j++) {
			fscanf(fin, "%d %d", &c, &k);
			raw[i].item[j].code = c;
			raw[i].item[j].num = k;
		}
		fscanf(fin, "%d\n", &p);
		raw[i].price = p;
	}

	fscanf(fin, "%d\n", &B);
	for (int i=0; i<B; i++) {
		fscanf(fin, "%d %d %d", &c, &k, &p);
		code_map[c]=i;
		num[code_map[c]] = k;
		price[code_map[c]] = p;
	}

	// convert raw to special
	for (int i=0; i<S; i++) {
		for (int j=0; j<raw[i].n; j++) {
			special[i][code_map[raw[i].item[j].code]] = raw[i].item[j].num;
		}
		special[i][5] = raw[i].price;
	}
	fclose(fin);
}

void solve()
{
	// init
	for(int a=0; a<6; a++) {
		for (int b=0; b<6; b++) {
			for (int c=0; c<6; c++) {
				for (int d=0; d<6; d++){
					for (int e=0; e<6; e++) {
						f[a][b][c][d][e] = price[0]*a + price[1]*b + price[2]*c + price[3]*d + price[4]*e;
					}
				}
			}
		}
	}

	// solve
	for(int a=0; a<=num[0]; a++) {
		for(int b=0; b<=num[1]; b++) {
			for(int c=0; c<=num[2]; c++) {
				for(int d=0; d<=num[3]; d++) {
					for (int e=0; e<=num[4]; e++) {
						for(int i=0; i<S; i++) {
							if (a-special[i][0]>=0 && b-special[i][1]>=0 &&
								c-special[i][2]>=0 && d-special[i][3]>=0 &&
								e-special[i][4]>=0) {
								if (f[a][b][c][d][e] > f[a-special[i][0]][b-special[i][1]][c-special[i][2]][d-special[i][3]][e-special[i][4]] + special[i][5]){
									f[a][b][c][d][e] = f[a-special[i][0]][b-special[i][1]][c-special[i][2]][d-special[i][3]][e-special[i][4]] + special[i][5];
								} 
							}	
						}
					}
				}
			}
		}	
	}	
}

void output()
{
	fout = fopen("shopping.out", "w");
	assert(fout != NULL);
	fprintf(fout, "%d\n", f[num[0]][num[1]][num[2]][num[3]][num[4]]);
	fclose(fout);
}

int main(void)
{
	input();
	solve();
	output();

	return 0;
}
