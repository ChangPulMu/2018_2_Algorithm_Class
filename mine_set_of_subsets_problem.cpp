#include <iostream>
#include <string>

#define N 4

int w[N] = { 1,3,5,7 }, W = 8;
std::string include[N+1];

void sum_of_subsets(int, int, int);
bool promising(int, int, int);

int main(void)
{
	int sum = 0;

	for (int i = 0; i < N; i++)
		sum += w[i];

	sum_of_subsets(0, 0, sum);

	return 0;
}

void sum_of_subsets(int i, int weight, int total)
{
	if (promising(i, weight, total))
	{
		if (weight == W)
		{
			for (int j = 1; j <= i; j++)
				std::cout << include[j] << std::endl;
			std::cout << std::endl;
		}
		else
		{
			include[i + 1] = "yes";
			sum_of_subsets(i + 1, weight + w[i], total - w[i]);
			include[i + 1] = "no";
			sum_of_subsets(i + 1, weight, total - w[i]);
		}
	}
}

bool promising(int i, int weight, int total)
{
	return ((((weight + total) >= W)) && ((weight == W) || ((weight + w[i]) <= W)));
}