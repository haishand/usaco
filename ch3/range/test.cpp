#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("range.in");
ofstream fout("range.out");

const unsigned short maxn = 250 + 5;

unsigned short n;
char fieldpr;
unsigned short sq[maxn]; // biggest-square values
unsigned short sqpr;
unsigned short numsq[maxn]; // number of squares of each size

unsigned short
min3(unsigned short a, unsigned short b, unsigned short c)
{
	if ((a <= b) && (a <= c))
		return a;
	else 
		return (b <= c) ? b : c;
}

int
main()
{
	unsigned short r, c;
	unsigned short i;
	unsigned short tmp;

	fin >> n;

	for (c = 1; c <= n; c++)
		sq[c] = 0;

	for (i = 2; i <= n; i++)
		numsq[i] = 0;

	for (r = 1; r <= n; r++)
	{
		sqpr = 0;
		sq[0] = 0;
		for (c = 1; c <= n; c++)
		{
			fin >> fieldpr;
			if (!(fieldpr - '0'))
			{
				sqpr = sq[c];
				sq[c] = 0;
				continue;
			}

			// Only three values needed.
			tmp = 1 + min3(sq[c-1], sqpr, sq[c]);
			sqpr = sq[c];
			sq[c] = tmp;

			// Only count maximal squares, for now.
			if (sq[c] >= 2)
				numsq[ sq[c] ]++;
		}
	}

	// Count all squares, not just maximal. 
	for (i = n-1; i >= 2; i--)
		numsq[i] += numsq[i+1];

	for (i = 2; i <= n && numsq[i]; i++)
		fout << i << ' ' << numsq[i] << endl;
	return 0;
}
