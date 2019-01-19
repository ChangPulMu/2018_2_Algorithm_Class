#include <iostream>

#define N 4
#define M 3

int W[N][N] = { {0,1,1,1}, {1,0,1,0}, {1,1,0,1}, {1,0,1,0} }, vcolor[N];

void m_coloring(int);
bool promising(int);

int main(void)
{
	m_coloring(0);

	return 0;
}

void m_coloring(int i)
{
	int color;
	if (promising(i))
	{
		if (i == N)
		{
			for (int a = 0; a < i; a++)
				std::cout << vcolor[a] << std::endl;
			std::cout << std::endl;
		}
		else
		{
			for (color = 1; color <= M; color++)
			{
				vcolor[i] = color;
				m_coloring(i + 1);
			}
		}
	}
}

bool promising(int i)
{
	int j = 1;
	bool swch = true;

	while ((j < i) && swch)
	{
		if (W[i - 1][j - 1] && (vcolor[i - 1] == vcolor[j - 1]))
			swch = false;
		j++;
	}

	return swch;
}