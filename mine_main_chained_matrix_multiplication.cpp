#include <iostream>

#define N 6								// 곱할 행렬의 수를 정의

int Path[N][N];							// M[i][j]에 최소치를 주는 k의 값을 저장하는 배열 Path 정의

int minmult(int, int *, int[][N]);
void order(int, int);

int main(void)
{
	int column[7] = { 7, 3, 6, 2, 4, 3, 5 };		// 첫째 행렬의 행의 수와 전체 행렬의 열의 수를 정의
	int min;

	min = minmult(N, column, Path);		// minmult() 함수를 통해 최소 곱셈 횟수를 받아옴

	std::cout << "최소 곱셈 횟수 : " << min << std::endl;
	
	order(0, 5);						// order() 함수를 통해 최소 곱셈 횟수를 얻는 행렬의 곱셈 순서를 출력

	return 0;
}

int minmult(int n, int * d, int P[][N])
{
	int i, j, k, diagonal;
	int M[N][N];						// 최소 곱셈 횟수를 저장하는 배열

	for (i = 0; i < n; i++)				// 곱셈할 행렬이 하나밖에 없을 때 0으로 초기화
		M[i][i] = 0;

	for (diagonal = 1; diagonal <= n - 1; diagonal++) {				// 대각선 1부터 n-1까지 계산

		for (i = 0; i < n - diagonal; i++) {				// 0행부터 n-diagonal 행렬까지
			j = i + diagonal;			// j는 i+diagonal 값으로 초기화
			
			for (k = i; k < j; k++) {						// i부터 j-1사이에 k값중에

				if (k == i) {			// k의 첫번째 값에는 M[i][j]행렬과 P[i][j]을 초기화 해줌
					M[i][j] = M[i][k] + M[k + 1][j] + d[i] * d[k + 1] * d[j + 1];
					P[i][j] = k;
				}

				else if (M[i][j] > M[i][k] + M[k + 1][j] + d[i] * d[k + 1] * d[j + 1]) {		// 초기화된 M[i][j]값을 토대로 최소 곱셈 횟수를 갖는 k값을 P[i][j]에 넣고 M[i][j]값을 해당 값으로 바꿈
					M[i][j] = M[i][k] + M[k + 1][j] + d[i] * d[k + 1] * d[j + 1];
					P[i][j] = k;
				}
			}
		}
	}

	return M[0][n - 1];					// 최소 곱셈 횟수를 반환
}

void order(int i, int j)
{
	int k;

	if (i == j)					// i와 j가 같을 때, 'A'i+1을 출력
		std::cout << "A" << i+1;
	else
	{
		k = Path[i][j];			// Path[i][j]값을 k에 넣어줌
		std::cout << "(";
		order(i, k);			// order(i, k) 함수를 재귀호출
		order(k + 1, j);		// order(k + 1, j) 함수를 재귀호출
		std::cout << ")";
	}
}