CC=g++
CFLAGS=-Wall -Wextra
BENCHMARK_FLAGS=-std=c++11 -isystem ../utils/benchmark/include -L../utils/benchmark/build/src -lbenchmark -lpthread

BACK=knapsack_backtracking
TAB=knapsack_tabulation
GREEDY=knapsack_greedy
BACK_BENCH=benchmark_backtracking
TAB_BENCH=benchmark_tabulation
GREEDY_BENCH=benchmark_greedy

.PHONY: build clean

build: $(BACK) $(GREEDY) $(TAB) $(BACK_BENCH) $(TAB_BENCH) $(GREEDY_BENCH)

$(BACK): $(BACK).cpp
	$(CC) $(CFLAGS) -o $@ $<
$(TAB): $(TAB).cpp
	$(CC) $(CFLAGS) -o $@ $<
$(GREEDY): $(GREEDY).cpp
	$(CC) $(CFLAGS) -o $@ $<
$(BACK_BENCH): $(BACK_BENCH).cpp
	$(CC) $< $(BENCHMARK_FLAGS) -o $@
$(TAB_BENCH): $(TAB_BENCH).cpp
	$(CC) $< $(BENCHMARK_FLAGS) -o $@
$(GREEDY_BENCH): $(GREEDY_BENCH).cpp
	$(CC) $< $(BENCHMARK_FLAGS) -o $@

clean:
	rm -f $(BACK) $(TAB) $(GREEDY) $(BACK_BENCH) $(TAB_BENCH) $(GREEDY_BENCH)

