#include <benchmark/benchmark.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

/*********************** Backtracking approach ***********************/

int N, G;
int maxW, maxx, size;
std::vector<int> weights, values;
std::vector<int> selection, current_selection;

int knapsack(int index, int curr_weight, int curr_profit) {
	if (index == size) {
		if (curr_profit > maxx) {
			maxx = curr_profit;
			selection = current_selection;
		}
		return maxx;
	}

	if (curr_weight + weights[index] <= maxW) {
		current_selection.push_back(index + 1);
		maxx = std::max(maxx, knapsack(index + 1, curr_weight + weights[index], curr_profit + values[index]));
		current_selection.pop_back();
	}
	return std::max(maxx, knapsack(index + 1, curr_weight, curr_profit));
}

static inline void knapsack_handler_backtracking(benchmark::State& state) {
	for (auto _ : state) {
		knapsack(0, 0, 0);
	}
}

BENCHMARK(knapsack_handler_backtracking);

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

	maxW = G;
	size = N;

	for (int i = 0; i < N; ++i)
		fin >> weights[i] >> values[i];

	fout << knapsack(0, 0, 0) << '\n';

	for (int &index : selection)
		fout << index << ' ';
	fout << '\n';

	fin.close();
	fout.close();

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();

	return 0;
}
