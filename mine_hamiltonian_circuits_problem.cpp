#include <iostream>

#define N 4

int W[N][N] = { {0,1,1,1},{1,0,1,1},{1,1,0,1}, {1,1,1,0} };
int vindex[N] = { 1, 0, 0, 0 };

bool promising(int);
void hamiltonian(int);

int main(void)
{
	hamiltonian(0);

	return 0;
}

void hamiltonian(int i)
{
	int j;

	if (promising(i))
	{
		if (i == N - 1)
		{
			for (int a = 1; a < N; a++)
				std::cout << vindex[a] << std::endl;
			std::cout << std::endl;
		}
		else
		{
			for (j = 2; j <= N; j++)
			{
				vindex[i + 1] = j;
				hamiltonian(i + 1);
			}
		}
	}
}

bool promising(int i)
{
	int j;
	bool swch;

	if ((i == N - 1) && (!W[vindex[N - 1] - 1][vindex[0] - 1]))
		swch = false;
	else if ((i > 0) && (!W[vindex[i - 1] - 1][vindex[i] - 1]))
		swch = false;
	else
	{
		swch = true;
		j = 1;

		while ((j < i) && swch)
		{
			if (vindex[i] == vindex[j])
				swch = false;
			j++;
		}
	}

	return swch;
}