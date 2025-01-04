#!/bin/bash

make

benchmark_file="tests/benchmarks/benchmark_tabulation"
echo "Benchmark                 Time             CPU   Iterations" > $benchmark_file
echo "-----------------------------------------------------------" >> $benchmark_file

for i in {1..30}
do
	input_file="tests/input/test_${i}.in"
	output_file="tests/output/tabulation/test_${i}.out"

	if [[ -f "$input_file" ]]; then
		echo "Running tabulation benchmark for $input_file..."
		./benchmark_tabulation "$input_file" "$output_file" | tail -n 1 >> $benchmark_file
	else
		echo "Input file $input_file not found, skipping..."
	fi
done

benchmark_file="tests/benchmarks/benchmark_backtracking"
echo "Benchmark                 Time             CPU   Iterations" > $benchmark_file
echo "-----------------------------------------------------------" >> $benchmark_file
for i in {1..30}
do
	input_file="tests/input/test_${i}.in"
	output_file="tests/output/backtracking/test_${i}.out"
	if [[ -f "$input_file" ]]; then
		echo "Running backtracking benchmark for $input_file..."
		./benchmark_backtracking "$input_file" "$output_file" | tail -1 >> $benchmark_file
	else
		echo "Input file $input_file not found, skipping..."
	fi
done

benchmark_file="tests/benchmarks/benchmark_greedy"
echo "Benchmark                 Time             CPU   Iterations" > $benchmark_file
echo "-----------------------------------------------------------" >> $benchmark_file
for i in {1..30}
do
	input_file="tests/input/test_${i}.in"
	output_file="tests/output/greedy/test_${i}.out"
	if [[ -f "$input_file" ]]; then
		echo "Running greedy benchmark for $input_file..."
		./benchmark_greedy "$input_file" "$output_file" | tail -1 >> $benchmark_file
	else
		echo "Input file $input_file not found, skipping..."
	fi
done

make clean
