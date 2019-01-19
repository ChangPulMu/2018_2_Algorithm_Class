#include <iostream>
#define N 5						// 그래프 정점의 갯수
#define M 7						// 그래프 이음선의 갯수

typedef struct {				// 이음선의 시작 정점과 끝 정점 및 가중치를 나타내는 Edge 구조체
	int start;
	int end;
	int weight;
}Edge;

typedef struct { int parent; int depth; }nodetype;				// Disjoint Set Data Structure2에서의 깊이와 부모(포함되는 집합을 의미)를 나타내는 nodetype 구조체

typedef int set_pointer;		// set_pointer을 int형으로 정의

Edge Eg[M] = { {0,1,3},{0,2,2},{1,3,2},{1,4,5},{2,3,1},{2,4,4},{3,4,3} };			// 그래프의 모든 이음선 집합을 배열로 만듬

class Structure2				// Disjoint Set Data Structure2
{
public:
	nodetype U[N];				// 그래프 각각의 정점을 나타냄
	void makeset(int i)			// 정점의 부모를 자신으로 초기화하고 깊이를 0으로 초기화
	{
		U[i].parent = i;
		U[i].depth = 0;
	}
	void initial(int n)			// 그래프 각각의 정점을 초기화
	{
		int i;
		for (i = 0; i < n; i++)
			makeset(i);
	}
	bool equal(set_pointer p, set_pointer q)			// 같은 집합에 소속되어 있는지 확인
	{
		if (p == q)
			return true;
		else
			return false;
	}
	set_pointer find(int i)		// 정점의 최상위 부모를 찾아서 어떤 집합에 속하는지를 반환
	{
		int j;
		j = i;
		while (U[j].parent != j)
			j = U[j].parent;
		return j;
	}
	void merge(set_pointer p, set_pointer q)			// 두 정점의 집합을 합병
	{
		if (U[p].depth == U[q].depth)
		{
			U[p].depth += 1;
			U[q].parent = p;
		}
		else if (U[p].depth < U[q].depth)
			U[p].parent = q;
		else
			U[q].parent = p;
	}
};

void merge(int h, int m, Edge* U, Edge* V, Edge* S)		// 이음선 합병 정렬
{
	int i, j, k;
	i = 0, j = 0, k = 0;

	while ((i < h) && (j < m))
	{
		if (U[i].weight < V[j].weight)					// weight에 따라 비내림차순으로 정렬
		{
			S[k] = U[i];
			i++;
		}
		else if (U[i].weight == V[j].weight)			// weight가 같을 때는
		{
			if (U[i].start < V[j].start)				// start에 따라 비내림차순으로 정렬
			{
				S[k] = U[i];
				i++;
			}
			else if (U[i].start == V[j].start)			// start가 같을 때는
			{
				if (U[i].end < V[j].end)				// end에 따라 비내림차순으로 정렬
				{
					S[k] = U[i];
					i++;
				}
				else
				{
					S[k] = V[j];
					j++;
				}
			}
			else
			{
				S[k] = V[j];
				j++;
			}
		}
		else
		{
			S[k] = V[j];
			j++;
		}
		k++;
	}

	if (i >= h)
	{
		while (j < m)
		{
			S[k] = V[j];
			k++, j++;
		}
	}
	else
	{
		while (i < h)
		{
			S[k] = U[i];
			k++, i++;
		}
	}
}

void mergesort(int n, Edge* edge)				// 이음선 합병 정렬
{
	int i = 0, j = 0;

	if (n > 1) {
		int h = n / 2;
		int m = n - h;
		Edge* U = new Edge[h];
		Edge* V = new Edge[m];

		while(i < h)
		{
			U[i] = edge[i];
			i++;
		}
		while (i < n)
		{
			V[j] = edge[i];
			i++, j++;
		}

		mergesort(h, U);
		mergesort(m, V);
		merge(h, m, U, V, edge);

		delete[] U;
		delete[] V;
	}
}

void kruskal(int n, int m, Edge* E, Edge* F)
{
	int i, j, count = 0, F_count = 0;
	set_pointer p, q;
	Edge e, tmp;
	Structure2 str;

	mergesort(m, E);			// 이음선을 weight 기준으로 비내림차순으로 정렬

	for (int a = 0; a < n - 1; a++)			// 이음선의 집합 배열 F를 초기화 시켜줌
	{
		F[a].start = 0;
		F[a].end = 0;
		F[a].weight = 0;
	}
	str.initial(n);				// Disjoint Set 초기화

	while (F[n - 2].weight == 0)			// 배열 F의 마지막 항목에 값이 입력되기 전까지
	{
		e = E[count];			// 정렬된 이음선의 집합에서 인덱스가 낮은 항목부터 꺼냄
		i = e.start;			// 시작점
		j = e.end;				// 끝점

		p = str.find(i);		// 시작점의 집합을 찾음
		q = str.find(j);		// 끝점의 집합을 찾음
		if (!str.equal(p, q))	// 시작점과 끝점의 집합이 같지 않다면
		{
			str.merge(p, q);	// 시작점과 끝점의 집합을 합병
			F[F_count] = e;		// 해당 이음선을 배열 F에 추가
			F_count++;
		}
		count++;
	}
}

int main(void)
{
	Edge f[N-1];
	kruskal(N, M, Eg, f);		// kruskal 알고리즘 호출

	for (int i = 0; i < N - 1; i++)				// f 배열에 대한 정보 출력
	{
		std::cout << "v" << f[i].start + 1 << "와 v" << f[i].end + 1 << "사이 이음선 가중치 : " << f[i].weight << std::endl;
	}
	
	return 0;
}