#include <iostream>

#define N 5						// A�迭�� R�迭�� ��� ���� ���� ��������

void optsearchtree(int, const float [], float&, int[][N]);

int main(void)
{
	const float Percentage[N-1] = { 0.375, 0.375, 0.125, 0.125 };				// �� Ű�� ã���� Ȯ���� ���
	int Root[N][N] = {};
	float m_a;					// �ּ� ��� Ž�� Ƚ���� ������ ����

	optsearchtree(N - 1, Percentage, m_a, Root);							// optsearchtree() �Լ� ����

	std::cout << "R�迭" << std::endl;					// R�迭�� ������ ���
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			std::cout << Root[i][j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "�ּ� ��� Ž�� �ð� : " << m_a << std::endl;				// �ּ� ��� Ž�� Ƚ���� ���� ���

	return 0;
}

void optsearchtree(int n, const float p[], float& minavg, int R[][N])
{
	int i, j, k, diagonal;
	float A[N][N] = {}, sum = 0;

	for (i = 0; i < n; i++)				// A�迭�� R�迭���� Ʈ���� Ư�� �ε��� ���� �ش��ϴ� Ű�ۿ� ���� �� Ȯ���� ��Ʈ Ʈ������ ���
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
			
			for (int a = i; a < j; a++)				// i���� j-1������ Ȯ���� ���ؼ� sum ������ ���
				sum += p[a];
			
			for (k = i; k < j; k++) {				// k�� i���� j-1������ ��
				
				if (k == i) {						// �ʱ� ���� ���
					A[i][j] = A[i][k] + A[k + 1][j] + sum;
					R[i][j] = k + 1;
				}

				else if (A[i][j] > A[i][k] + A[k + 1][j] + sum) {			// �ʱ� ���� ���� �޶��� k������ ���� �ٲ� ���� ���� �۴ٸ� �ٽ� ���
					A[i][j] = A[i][k] + A[k + 1][j] + sum;
					R[i][j] = k + 1;
				}
			}

			sum = 0;								// i�� ���� �޶��� ������ sum ���� 0���� �ʱ�ȭ
		}
	}

	std::cout << "A�迭" << std::endl;				// A�迭�� ������ ���
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			std::cout << A[i][j] << "	";
		std::cout << std::endl;
	}
	std::cout << std::endl;

	minavg = A[0][n];								// �ּ� ��� Ž�� Ƚ�� ���� ��ȯ
}