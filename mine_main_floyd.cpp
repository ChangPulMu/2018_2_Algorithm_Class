#include <iostream>

#define N 5
#define INFI 1000

void floyd2(int, int [][N], int [][N], int [][N]);
void path(int, int);

int Path[N][N];

int main(void) {
	int a, b;

	int Way[N][N];
	int Direct_G[N][N];

	
	Way[0][0] = 0, Way[0][1] = INFI, Way[0][2] = INFI, Way[0][3] = 3, Way[0][4] = 7;
	Way[1][0] = 4, Way[1][1] = 0, Way[1][2] = 9, Way[1][3] = INFI, Way[1][4] = 1;
	Way[2][0] = INFI, Way[2][1] = 3, Way[2][2] = 0, Way[2][3] = INFI, Way[2][4] = INFI;
	Way[3][0] = 8, Way[3][1] = 5, Way[3][2] = INFI, Way[3][3] = 0, Way[3][4] = INFI;
	Way[4][0] = INFI, Way[4][1] = 2, Way[4][2] = INFI, Way[4][3] = 1, Way[4][4] = 0;

	floyd2(5, Way, Direct_G, Path);

	for (a = 0; a < 5; a++) {
		for (b = 0; b < 5; b++) {
			std::cout << Direct_G[a][b] << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;


	for (a = 0; a < 5; a++) {
		for (b = 0; b < 5; b++) {
			std::cout << Path[a][b] << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (a = 0; a < 5; a++) {
		for (b = 0; b < 5; b++) {
			if (a != b) {
				std::cout << " v" << a + 1;
				path(a, b);
				std::cout << " v" << b + 1 << std::endl;
			}
		}
	}

	return 0;
}

void path(int q, int r) {
	if (Path[q][r] != 0)
	{
		path(q, Path[q][r]-1);
		std::cout << " v" << Path[q][r];
		path(Path[q][r]-1, r);
	}
}

void floyd2(int n, int W[][N], int D[][N], int P[][N])
{
	int i, j, k;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			P[i][j] = 0;
		}
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			D[i][j] = W[i][j];
		}
	}

	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (D[i][k] + D[k][j] < D[i][j])
				{
					P[i][j] = k + 1;
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}
}