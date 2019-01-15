#include <iostream>

#define N 6								// ���� ����� ���� ����

int Path[N][N];							// M[i][j]�� �ּ�ġ�� �ִ� k�� ���� �����ϴ� �迭 Path ����

int minmult(int, int *, int[][N]);
void order(int, int);

int main(void)
{
	int column[7] = { 7, 3, 6, 2, 4, 3, 5 };		// ù° ����� ���� ���� ��ü ����� ���� ���� ����
	int min;

	min = minmult(N, column, Path);		// minmult() �Լ��� ���� �ּ� ���� Ƚ���� �޾ƿ�

	std::cout << "�ּ� ���� Ƚ�� : " << min << std::endl;
	
	order(0, 5);						// order() �Լ��� ���� �ּ� ���� Ƚ���� ��� ����� ���� ������ ���

	return 0;
}

int minmult(int n, int * d, int P[][N])
{
	int i, j, k, diagonal;
	int M[N][N];						// �ּ� ���� Ƚ���� �����ϴ� �迭

	for (i = 0; i < n; i++)				// ������ ����� �ϳ��ۿ� ���� �� 0���� �ʱ�ȭ
		M[i][i] = 0;

	for (diagonal = 1; diagonal <= n - 1; diagonal++) {				// �밢�� 1���� n-1���� ���

		for (i = 0; i < n - diagonal; i++) {				// 0����� n-diagonal ��ı���
			j = i + diagonal;			// j�� i+diagonal ������ �ʱ�ȭ
			
			for (k = i; k < j; k++) {						// i���� j-1���̿� k���߿�

				if (k == i) {			// k�� ù��° ������ M[i][j]��İ� P[i][j]�� �ʱ�ȭ ����
					M[i][j] = M[i][k] + M[k + 1][j] + d[i] * d[k + 1] * d[j + 1];
					P[i][j] = k;
				}

				else if (M[i][j] > M[i][k] + M[k + 1][j] + d[i] * d[k + 1] * d[j + 1]) {		// �ʱ�ȭ�� M[i][j]���� ���� �ּ� ���� Ƚ���� ���� k���� P[i][j]�� �ְ� M[i][j]���� �ش� ������ �ٲ�
					M[i][j] = M[i][k] + M[k + 1][j] + d[i] * d[k + 1] * d[j + 1];
					P[i][j] = k;
				}
			}
		}
	}

	return M[0][n - 1];					// �ּ� ���� Ƚ���� ��ȯ
}

void order(int i, int j)
{
	int k;

	if (i == j)					// i�� j�� ���� ��, 'A'i+1�� ���
		std::cout << "A" << i+1;
	else
	{
		k = Path[i][j];			// Path[i][j]���� k�� �־���
		std::cout << "(";
		order(i, k);			// order(i, k) �Լ��� ���ȣ��
		order(k + 1, j);		// order(k + 1, j) �Լ��� ���ȣ��
		std::cout << ")";
	}
}