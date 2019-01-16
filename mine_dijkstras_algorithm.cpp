#include <iostream>

#define N 5					// 그래프 정점의 갯수
#define INF 1000			// 무한대를 1000으로 임시 정의

typedef struct {			// 시작 정점과 끝 정점, 가중치 요소를 가진 이음선의 구조체 정의
	int start;
	int end;
	int weight;
}Edge;

void dijkstra(int, int[][N], Edge[]);

int main(void)
{
	int Weight[N][N];				// 초기 그래프의 인접 행렬식 배열
	Edge Edge_Set[N - 1];			// 문제를 만족하는 그래프의 이음선 배열

	Weight[0][0] = 0, Weight[0][1] = 9, Weight[0][2] = 3, Weight[0][3] = 4, Weight[0][4] = 8;				// 초기 그래프의 인접 행렬식 배열의 값을 정의
	Weight[1][0] = INF, Weight[1][1] = 0, Weight[1][2] = INF, Weight[1][3] = INF, Weight[1][4] = INF;
	Weight[2][0] = INF, Weight[2][1] = 1, Weight[2][2] = 0, Weight[2][3] = 5, Weight[2][4] = 2;
	Weight[3][0] = INF, Weight[3][1] = INF, Weight[3][2] = INF, Weight[3][3] = 0, Weight[3][4] = 3;
	Weight[4][0] = INF, Weight[4][1] = INF, Weight[4][2] = INF, Weight[4][3] = INF, Weight[4][4] = 0;

	dijkstra(N, Weight, Edge_Set);	// dijkstra's algorithm

	for (int i = 0; i < N - 1; i++)	// 문제를 만족하는 그래프의 이음선들을 화면에 출력
	{
		std::cout << "V" << Edge_Set[i].start + 1 << " -> V" << Edge_Set[i].end + 1 << " 의 가중치 : " << Edge_Set[i].weight << std::endl;
	}

	return 0;
}

void dijkstra(int n, int W[][N], Edge F[])
{
	int i, vnear, min, touch[N], length[N], count = 0;
	Edge e;

	for (int a = 0; a < n - 1; a++)			// 문제를 만족하는 그래프의 이음선들을 표현할 배열을 초기화
	{
		F[a].start = 0;
		F[a].end = 0;
		F[a].weight = 0;
	}

	for (i = 1; i < n; i++)					// touch 배열을 v1로 거쳐가는 것으로 초기화, length 배열을 v1에서 각각의 정점으로 가는 가중치로 초기화
	{
		touch[i] = 0;
		length[i] = W[0][i];
	}

	for (int t = 0; t < n - 1; t++)			// 총 n-1개의 이음선이 필요
	{
		min = INF;							// min값을 무한대로 초기화
		
		for (i = 1; i < n; i++)
		{
			if ((0 <= length[i]) && (length[i] <= min))			// length[i]값이 0보다 크고 min값보다 작을 때
			{
				min = length[i];			// min값을 length[i]값으로 초기화하고 vnear값을 i값으로 초기화
				vnear = i;
			}
		}
		
		int tmp = touch[vnear];

		e.start = tmp;					// e를 touch[vnear]을 시작점으로 가지고 vnear을 끝점으로 갖는 이음선으로 초기화
		e.end = vnear;
		e.weight = W[tmp][vnear];

		F[count] = e;					// 배열 F에 이음선 e를 추가
		count++;

		for (i = 1; i < n; i++)
		{
			if (length[vnear] + W[vnear][i] < length[i])			// vnear의 정점을 지날 때가 가중치가 더 작다면
			{
				length[i] = length[vnear] + W[vnear][i];			// 그 값으로 length[i]를 초기화하고 touch[i]를 vnear로 초기화
				touch[i] = vnear;
			}
		}

		length[vnear] = -1;				// vnear의 정점으로 가는 최소 경로를 찾았기 때문에 length[vnear]을 -1로 초기화
	}
}