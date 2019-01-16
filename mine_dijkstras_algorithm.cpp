#include <iostream>

#define N 5					// �׷��� ������ ����
#define INF 1000			// ���Ѵ븦 1000���� �ӽ� ����

typedef struct {			// ���� ������ �� ����, ����ġ ��Ҹ� ���� �������� ����ü ����
	int start;
	int end;
	int weight;
}Edge;

void dijkstra(int, int[][N], Edge[]);

int main(void)
{
	int Weight[N][N];				// �ʱ� �׷����� ���� ��Ľ� �迭
	Edge Edge_Set[N - 1];			// ������ �����ϴ� �׷����� ������ �迭

	Weight[0][0] = 0, Weight[0][1] = 9, Weight[0][2] = 3, Weight[0][3] = 4, Weight[0][4] = 8;				// �ʱ� �׷����� ���� ��Ľ� �迭�� ���� ����
	Weight[1][0] = INF, Weight[1][1] = 0, Weight[1][2] = INF, Weight[1][3] = INF, Weight[1][4] = INF;
	Weight[2][0] = INF, Weight[2][1] = 1, Weight[2][2] = 0, Weight[2][3] = 5, Weight[2][4] = 2;
	Weight[3][0] = INF, Weight[3][1] = INF, Weight[3][2] = INF, Weight[3][3] = 0, Weight[3][4] = 3;
	Weight[4][0] = INF, Weight[4][1] = INF, Weight[4][2] = INF, Weight[4][3] = INF, Weight[4][4] = 0;

	dijkstra(N, Weight, Edge_Set);	// dijkstra's algorithm

	for (int i = 0; i < N - 1; i++)	// ������ �����ϴ� �׷����� ���������� ȭ�鿡 ���
	{
		std::cout << "V" << Edge_Set[i].start + 1 << " -> V" << Edge_Set[i].end + 1 << " �� ����ġ : " << Edge_Set[i].weight << std::endl;
	}

	return 0;
}

void dijkstra(int n, int W[][N], Edge F[])
{
	int i, vnear, min, touch[N], length[N], count = 0;
	Edge e;

	for (int a = 0; a < n - 1; a++)			// ������ �����ϴ� �׷����� ���������� ǥ���� �迭�� �ʱ�ȭ
	{
		F[a].start = 0;
		F[a].end = 0;
		F[a].weight = 0;
	}

	for (i = 1; i < n; i++)					// touch �迭�� v1�� ���İ��� ������ �ʱ�ȭ, length �迭�� v1���� ������ �������� ���� ����ġ�� �ʱ�ȭ
	{
		touch[i] = 0;
		length[i] = W[0][i];
	}

	for (int t = 0; t < n - 1; t++)			// �� n-1���� �������� �ʿ�
	{
		min = INF;							// min���� ���Ѵ�� �ʱ�ȭ
		
		for (i = 1; i < n; i++)
		{
			if ((0 <= length[i]) && (length[i] <= min))			// length[i]���� 0���� ũ�� min������ ���� ��
			{
				min = length[i];			// min���� length[i]������ �ʱ�ȭ�ϰ� vnear���� i������ �ʱ�ȭ
				vnear = i;
			}
		}
		
		int tmp = touch[vnear];

		e.start = tmp;					// e�� touch[vnear]�� ���������� ������ vnear�� �������� ���� ���������� �ʱ�ȭ
		e.end = vnear;
		e.weight = W[tmp][vnear];

		F[count] = e;					// �迭 F�� ������ e�� �߰�
		count++;

		for (i = 1; i < n; i++)
		{
			if (length[vnear] + W[vnear][i] < length[i])			// vnear�� ������ ���� ���� ����ġ�� �� �۴ٸ�
			{
				length[i] = length[vnear] + W[vnear][i];			// �� ������ length[i]�� �ʱ�ȭ�ϰ� touch[i]�� vnear�� �ʱ�ȭ
				touch[i] = vnear;
			}
		}

		length[vnear] = -1;				// vnear�� �������� ���� �ּ� ��θ� ã�ұ� ������ length[vnear]�� -1�� �ʱ�ȭ
	}
}