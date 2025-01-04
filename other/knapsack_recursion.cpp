#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::vector<int> weights, values;

/*********************** Recursive approach ***********************/

int knapsack(int W, int n) {
	if (n == 0 || W == 0)
		return 0;

	if (weights[n - 1] > W)
		return knapsack(W, n - 1);

	return std::max(knapsack(W, n - 1),
					values[n - 1] + knapsack(W - weights[n - 1], n - 1));
}

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Correct usage: ./knapsack <input_filename> <output_filename>");
		return -1;
	}

	std::ifstream fin(argv[1]);
	std::ofstream fout(argv[2]);
	int N, G;

	fin >> N >> G;

	weights.resize(N);
	values.resize(N);

	for (int i = 0; i < N; ++i)
		fin >> weights[i] >> values[i];

	fout << knapsack(G, weights.size()) << '\n';

	fin.close();
	fout.close();

	return 0;
}
