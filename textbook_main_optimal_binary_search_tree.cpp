#include <iostream>

#define N 5						// A배열과 R배열의 행과 열의 값을 정의해줌

void optsearchtree(int, const float [], float&, int[][N]);

int main(void)
{
	const float Percentage[N-1] = { 0.375, 0.375, 0.125, 0.125 };				// 각 키가 찾아질 확률을 배당
	int Root[N][N] = {};
	float m_a;					// 최소 평균 탐색 횟수를 저장할 변수

	optsearchtree(N - 1, Percentage, m_a, Root);							// optsearchtree() 함수 실행

	std::cout << "R배열" << std::endl;					// R배열의 값들을 출력
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			std::cout << Root[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "최소 평균 탐색 시간 : " << m_a << std::endl;				// 최소 평균 탐색 횟수의 값을 출력

	return 0;
}

void optsearchtree(int n, const float p[], float& minavg, int R[][N])
{
	int i, j, k, diagonal;
	float A[N][N] = {}, sum = 0;

	for (i = 0; i < n; i++)				// A배열과 R배열에서 트리에 특정 인덱스 값에 해당하는 키밖에 없을 때 확률과 루트 트리값을 배당
	{
		A[i][i] = 0;
		R[i][i] = 0;
		A[i][i + 1] = p[i];
		R[i][i + 1] = i + 1;
	}

	A[n][n] = 0;
	R[n][n] = 0;

	for (diagonal = 2; diagonal <= n; diagonal++) {

		for (i = 0; i <= n - diagonal; i++) {

			j = i + diagonal;
			
			for (int a = i; a < j; a++)				// i부터 j-1까지의 확률을 더해서 sum 변수에 배당
				sum += p[a];
			
			for (k = i; k < j; k++) {				// k는 i부터 j-1까지의 값
				
				if (k == i) {						// 초기 값을 배당
					A[i][j] = A[i][k] + A[k + 1][j] + sum;
					R[i][j] = k + 1;
				}

				else if (A[i][j] > A[i][k] + A[k + 1][j] + sum) {			// 초기 값에 비해 달라진 k값으로 인해 바뀐 식의 값이 작다면 다시 배당
					A[i][j] = A[i][k] + A[k + 1][j] + sum;
					R[i][j] = k + 1;
				}
			}

			sum = 0;								// i의 값이 달라질 때마다 sum 변수 0으로 초기화
		}
	}

	std::cout << "A배열" << std::endl;				// A배열의 값들을 출력
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			std::cout << A[i][j] << "	";
		std::cout << std::endl;
	}
	std::cout << std::endl;

	minavg = A[0][n];								// 최소 평균 탐색 횟수 값을 반환
}