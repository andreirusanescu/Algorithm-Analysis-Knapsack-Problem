import os
import random

def generate_knapsack_test(filename, n, max_weight):
	with open(filename, 'w') as file:
		W = random.randint(max_weight // 2, max_weight)
		file.write(f"{n} {W}\n")
		for _ in range(n):
			weight = random.randint(1, max_weight // 2)
			value = random.randint(1, 1000)
			file.write(f"{weight} {value}\n")

def main():
	max_weight = 1000
	ns = [20, 23, 27, 29,
	   	  30, 32, 36, 39,
		  40, 42, 46, 48,
		  50, 51, 55, 57,
		  60, 62, 65, 67,
		  70, 73, 74, 78,
		  80, 81, 86, 89]
	num_tests = len(ns)

	input_folder = "tests/input"
	os.makedirs(input_folder, exist_ok=True)

	for test_index in range(1, num_tests + 1):
		filename = os.path.join(input_folder, f"test_{test_index}.in")

		generate_knapsack_test(filename, ns[test_index - 1], max_weight)

if __name__ == "__main__":
	main()
