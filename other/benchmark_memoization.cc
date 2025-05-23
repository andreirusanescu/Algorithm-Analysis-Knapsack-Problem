#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <benchmark/benchmark.h>

int N, G;
std::vector<std::vector<int>> memo;
std::vector<int> weights, values;

/*********************** Memoization DP - approach ***********************/
int knapsack(int W, int index) {
	if (index < 0)
		return 0;
	
	if (memo[index][W] != -1)
		return memo[index][W];

	if (weights[index] > W)
		return memo[index][W] = knapsack(W, index - 1);

	return memo[index][W] = std::max(
		knapsack(W, index - 1),
		values[index] + knapsack(W - weights[index], index - 1));
}

inline std::vector<int> find_objects() {
	std::vector<int> res;
	int index = weights.size() - 1, n = G;
	while (n > 0 && index >= 0) {
		if (index == 0 || memo[index][n] != memo[index - 1][n]) {
			n -= weights[index];
			res.push_back(index + 1);
		}
		--index;
	}
	std::reverse(res.begin(), res.end());
	return res;
}

static inline void knapsack_handler_memoization(benchmark::State& state) {
    for (auto _ : state) {
        knapsack(G, N - 1);
        find_objects();
    }
}

BENCHMARK(knapsack_handler_memoization);

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Correct usage: ./knapsack <input_filename> <output_filename>");
		return -1;
	}

	std::ifstream fin(argv[1]);
	std::ofstream fout(argv[2]);

	fin >> N >> G;

	weights.resize(N);
	values.resize(N);
	memo.resize(N + 1, std::vector<int>(G + 1, -1));

	for (int i = 0; i < N; ++i)
		fin >> weights[i] >> values[i];

	fout << knapsack(G, N - 1) << '\n';

	std::vector<int> chosen_objects = find_objects();

	for (int &index : chosen_objects)
		fout << index << ' ';
	fout << '\n';

	fin.close();
	fout.close();

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();

	return 0;
}
