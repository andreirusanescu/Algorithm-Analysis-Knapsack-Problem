#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <benchmark/benchmark.h>

int N, G;
std::vector<std::vector<int>> dp;
std::vector<int> weights, values;

/*********************** Tabulation DP approach ***********************/
inline int knapsack() {
	for (int i = 0; i <= N; ++i)
		dp[i][0] = 0;
	for (int j = 0; j <= G; ++j)
		dp[0][j] = 0;

	for (int i = 1; i <= N; ++i) {
		for (int w = 1; w <= G; ++w) {
			if (weights[i - 1] <= w)
				dp[i][w] = std::max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
			else
				dp[i][w] = dp[i - 1][w];
		}
	}
	return dp[N][G];
}

inline std::vector<int> find_objects() {
	std::vector<int> res;
	int m = N, n = G;
	while (n > 0 && m > 0) {
		if (dp[m][n] != dp[m - 1][n]) {
			n -= weights[m - 1];
			res.push_back(m);
		}
		--m;
	}
	std::reverse(res.begin(), res.end());
	return res;
}

static inline void knapsack_handler_tabulation(benchmark::State& state) {
	for (auto _ : state) {
		knapsack();
		find_objects();
	}
}

BENCHMARK(knapsack_handler_tabulation);

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Correct usage: ./knapsack <input_filename> <output_filename>");
		return -1;
	}

	std::ifstream fin(argv[1]);
	std::ofstream fout(argv[2]);

	fin >> N >> G;

	dp.resize(N + 1, std::vector<int>(G + 1));
	weights.resize(N);
	values.resize(N);

	for (int i = 0; i < N; ++i)
		fin >> weights[i] >> values[i];

	fout << knapsack() << '\n';

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
