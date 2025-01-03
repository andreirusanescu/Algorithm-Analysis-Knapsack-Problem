#include <iostream>
#include <vector>
#include <chrono>

/*********************** Dynamic programming approach ***********************/
int knapsack(const int &maxWeight, std::vector<int> &weights, std::vector<int> &values) {
	int n = weights.size();

	std::vector<std::vector<int>> dp(n + 1, std::vector<int>(maxWeight + 1));

	for (int i = 0; i <= n; ++i)
		dp[i][0] = 0;
	for (int j = 0; j <= maxWeight; ++j)
		dp[0][j] = 0;
	
	for (int i = 1; i <= n; ++i) {
		for (int w = 1; w <= maxWeight; ++w) {
			if (weights[i - 1] <= w)
				dp[i][w] = std::max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
			else
				dp[i][w] = dp[i - 1][w];
		}
	}

	return dp[n][maxWeight];
}

/*********************** Memoization DP - approach ***********************/
int knapSackMemo(int W, std::vector<int> &weights, std::vector<int> &vals, int index, std::vector<std::vector<int>> &memo) {
	if (index < 0)
		return 0;
	
	if (memo[index][W] != -1)
		return memo[index][W];

	if (weights[index] > W)
		return memo[index][W] = knapSackMemo(W, weights, vals, index - 1, memo);

	return memo[index][W] = std::max(
		knapSackMemo(W, weights, vals, index - 1, memo),
		vals[index] + knapSackMemo(W - weights[index], weights, vals, index - 1, memo));
}

inline int knapSackMemoHelper(int W, std::vector<int> &weights, std::vector<int> &vals) {
	int n = weights.size();
	std::vector<std::vector<int>> memo(n, std::vector<int>(W + 1, -1));
	return knapSackMemo(W, weights, vals, n - 1, memo);
}

/*********************** Backtracking approach ***********************/

int maxxW, maxx, size;
std::vector<int> ws, vals;

void back(int index, int currWeight, int currProfit) {
	if (currWeight <= maxxW)
		maxx = std::max(maxx, currProfit);
	else return;

	if (index == size) {
		return;
	}

	for (int i = index; i < size; ++i) {
		currProfit += vals[i];
		currWeight += ws[i];
		back(i + 1, currWeight, currProfit);
		currProfit -= vals[i];
		currWeight -= ws[i];
	}
}

inline int knapsack_back(const int &maxWeight, std::vector<int> &weights, std::vector<int> &values) {
	maxx = 0;
	maxxW = maxWeight;
	ws = weights;
	vals = values;
	size = weights.size();
	back(0, 0, 0);
	return maxx;
}

/*********************** Recursive approach ***********************/

int knapSack(int W, std::vector<int> &weights, std::vector<int> &vals, int n) {
	if (n == 0 || W == 0)
		return 0;

	if (weights[n - 1] > W)
		return knapSack(W, weights, vals, n - 1);

	return std::max(knapSack(W, weights, vals, n - 1),
					vals[n - 1] + knapSack(W - weights[n - 1], weights, vals, n - 1));
}

int main() {
	/* Test de marime 20 */
	std::vector<int> weight = {3, 2, 4, 5, 9, 7, 8, 10, 15, 1, 12, 6, 13, 11, 14, 17, 18, 16, 19, 20, 
								22, 24, 21, 25, 27, 29, 28, 30, 31, 26, 33, 35, 34, 36, 37, 39, 38, 40, 41, 42};
	std::vector<int> profit =  {5, 3, 7, 9, 11, 8, 14, 16, 23, 1, 21, 10, 18, 13, 22, 28, 30, 25, 29, 31, 
								34, 37, 36, 39, 42, 45, 44, 46, 50, 43, 48, 52, 49, 53, 55, 58, 57, 60, 62, 65};
	const int W = 100;

	/* Test de marime 10 */
	// std::vector<int> weight = {3, 2, 4, 5, 9, 7, 8, 10, 15, 1, 12, 6, 13, 11, 14, 17, 18, 16, 19, 20};
	// std::vector<int> profit =  {5, 3, 7, 9, 11, 8, 14, 16, 23, 1, 21, 10, 18, 13, 22, 28, 30, 25, 29, 31};
	// const int W = 50;

	std::chrono::steady_clock sc;
	auto start = sc.now();
	std::cout << knapsack(W, weight, profit) << std::endl;
	auto end = sc.now();
	auto time_span = static_cast<std::chrono::duration<double>>(end - start);
	std::cout << "DP took: " << time_span.count() << " seconds !!!\n";


	start = sc.now();
	std::cout << knapSackMemoHelper(W, weight, profit) << std::endl;
	end = sc.now();
	time_span = static_cast<std::chrono::duration<double>>(end - start);
	std::cout << "DP - Memo took: " << time_span.count() << " seconds !!!\n";


	start = sc.now();
	std::cout << knapsack_back(W, weight, profit) << std::endl;
	end = sc.now();
	time_span = static_cast<std::chrono::duration<double>>(end - start);
	std::cout << "Backtrack took: " << time_span.count() << " seconds !!!\n";


	start = sc.now();
	std::cout << knapSack(W, weight, profit, weight.size()) << std::endl;
	end = sc.now();
	time_span = static_cast<std::chrono::duration<double>>(end - start);
	std::cout << "Recursion took: " << time_span.count() << " seconds !!!\n";

	return 0;
}
