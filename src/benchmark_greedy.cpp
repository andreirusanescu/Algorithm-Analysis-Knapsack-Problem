#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <benchmark/benchmark.h>

int N, G;
std::vector<std::vector<int>> pairs;
std::vector<int> selection;

/*********************** Greedy approach ***********************/

struct fcmp {
	bool operator()(const std::vector<int> &a, const std::vector<int> &b) {
		double r1 = (double)a[1] / (double)a[0];
		double r2 = (double)b[1] / (double)b[0];
		return r1 > r2;
	}
};

double knapsack() {
	std::sort(pairs.begin(), pairs.end(), fcmp());
	int current_weight = G;
	double res = 0;
	for (int i = 0; i < N; ++i) {
		if (pairs[i][0] <= current_weight) {
			current_weight -= pairs[i][0];
			selection.push_back(pairs[i][2]);
			res += pairs[i][1];
		} else {
			selection.push_back(pairs[i][2]);
			res += pairs[i][1] * ((double)current_weight) / (double)pairs[i][0];
			break;
		}
	}

	return res;
}

static inline void knapsack_handler_greedy(benchmark::State& state) {
	for (auto _ : state) {
		knapsack();
	}
}

BENCHMARK(knapsack_handler_greedy);

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Correct usage: ./knapsack <input_filename> <output_filename>");
		return -1;
	}

	std::ifstream fin(argv[1]);
	std::ofstream fout(argv[2]);

	fin >> N >> G;


	pairs.resize(N, std::vector<int>(3));

	for (int i = 0; i < N; ++i) {
		fin >> pairs[i][0] >> pairs[i][1];
		pairs[i][2] = i + 1;
	}

	fout << knapsack() << '\n';

	for (int &index : selection)
		fout << index << ' ';
	fout << '\n';

	fin.close();
	fout.close();

	benchmark::Initialize(&argc, argv);
	benchmark::RunSpecifiedBenchmarks();

	return 0;
}
