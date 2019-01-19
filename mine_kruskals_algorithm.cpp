#include <iostream>
#define N 5						// �׷��� ������ ����
#define M 7						// �׷��� �������� ����

typedef struct {				// �������� ���� ������ �� ���� �� ����ġ�� ��Ÿ���� Edge ����ü
	int start;
	int end;
	int weight;
}Edge;

typedef struct { int parent; int depth; }nodetype;				// Disjoint Set Data Structure2������ ���̿� �θ�(���ԵǴ� ������ �ǹ�)�� ��Ÿ���� nodetype ����ü

typedef int set_pointer;		// set_pointer�� int������ ����

Edge Eg[M] = { {0,1,3},{0,2,2},{1,3,2},{1,4,5},{2,3,1},{2,4,4},{3,4,3} };			// �׷����� ��� ������ ������ �迭�� ����

class Structure2				// Disjoint Set Data Structure2
{
public:
	nodetype U[N];				// �׷��� ������ ������ ��Ÿ��
	void makeset(int i)			// ������ �θ� �ڽ����� �ʱ�ȭ�ϰ� ���̸� 0���� �ʱ�ȭ
	{
		U[i].parent = i;
		U[i].depth = 0;
	}
	void initial(int n)			// �׷��� ������ ������ �ʱ�ȭ
	{
		int i;
		for (i = 0; i < n; i++)
			makeset(i);
	}
	bool equal(set_pointer p, set_pointer q)			// ���� ���տ� �ҼӵǾ� �ִ��� Ȯ��
	{
		if (p == q)
			return true;
		else
			return false;
	}
	set_pointer find(int i)		// ������ �ֻ��� �θ� ã�Ƽ� � ���տ� ���ϴ����� ��ȯ
	{
		int j;
		j = i;
		while (U[j].parent != j)
			j = U[j].parent;
		return j;
	}
	void merge(set_pointer p, set_pointer q)			// �� ������ ������ �պ�
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

void merge(int h, int m, Edge* U, Edge* V, Edge* S)		// ������ �պ� ����
{
	int i, j, k;
	i = 0, j = 0, k = 0;

	while ((i < h) && (j < m))
	{
		if (U[i].weight < V[j].weight)					// weight�� ���� �񳻸��������� ����
		{
			S[k] = U[i];
			i++;
		}
		else if (U[i].weight == V[j].weight)			// weight�� ���� ����
		{
			if (U[i].start < V[j].start)				// start�� ���� �񳻸��������� ����
			{
				S[k] = U[i];
				i++;
			}
			else if (U[i].start == V[j].start)			// start�� ���� ����
			{
				if (U[i].end < V[j].end)				// end�� ���� �񳻸��������� ����
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

void mergesort(int n, Edge* edge)				// ������ �պ� ����
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

	mergesort(m, E);			// �������� weight �������� �񳻸��������� ����

	for (int a = 0; a < n - 1; a++)			// �������� ���� �迭 F�� �ʱ�ȭ ������
	{
		F[a].start = 0;
		F[a].end = 0;
		F[a].weight = 0;
	}
	str.initial(n);				// Disjoint Set �ʱ�ȭ

	while (F[n - 2].weight == 0)			// �迭 F�� ������ �׸� ���� �ԷµǱ� ������
	{
		e = E[count];			// ���ĵ� �������� ���տ��� �ε����� ���� �׸���� ����
		i = e.start;			// ������
		j = e.end;				// ����

		p = str.find(i);		// �������� ������ ã��
		q = str.find(j);		// ������ ������ ã��
		if (!str.equal(p, q))	// �������� ������ ������ ���� �ʴٸ�
		{
			str.merge(p, q);	// �������� ������ ������ �պ�
			F[F_count] = e;		// �ش� �������� �迭 F�� �߰�
			F_count++;
		}
		count++;
	}
}

int main(void)
{
	Edge f[N-1];
	kruskal(N, M, Eg, f);		// kruskal �˰��� ȣ��

	for (int i = 0; i < N - 1; i++)				// f �迭�� ���� ���� ���
	{
		std::cout << "v" << f[i].start + 1 << "�� v" << f[i].end + 1 << "���� ������ ����ġ : " << f[i].weight << std::endl;
	}
	
	return 0;
}