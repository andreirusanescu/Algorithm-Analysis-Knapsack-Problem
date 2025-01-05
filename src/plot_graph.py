import re
import numpy as np
import matplotlib.pyplot as plt

table_data = """
Benchmark                 Time             CPU   Iterations
-----------------------------------------------------------
knapsack_handler_tabulation     397274 ns       397277 ns         1851
knapsack_handler_tabulation     451001 ns       450761 ns         1728
knapsack_handler_tabulation     381943 ns       381887 ns         1507
knapsack_handler_tabulation     489491 ns       489492 ns         1326
knapsack_handler_tabulation     493156 ns       493152 ns         1298
knapsack_handler_tabulation     435406 ns       435404 ns         1636
knapsack_handler_tabulation     650042 ns       650031 ns          917
knapsack_handler_tabulation     532384 ns       532373 ns         1252
knapsack_handler_tabulation     516264 ns       516259 ns         1470
knapsack_handler_tabulation     562368 ns       562380 ns         1237
knapsack_handler_tabulation     883800 ns       883352 ns          735
knapsack_handler_tabulation     473825 ns       473815 ns         1522
knapsack_handler_tabulation     701742 ns       701745 ns          875
knapsack_handler_tabulation     639519 ns       639524 ns         1058
knapsack_handler_tabulation     962106 ns       962057 ns          658
knapsack_handler_tabulation     929154 ns       929151 ns          827
knapsack_handler_tabulation     698738 ns       698732 ns         1040
knapsack_handler_tabulation     793952 ns       793950 ns          869
knapsack_handler_tabulation     902861 ns       902869 ns          714
knapsack_handler_tabulation     624316 ns       624326 ns         1126
knapsack_handler_tabulation    1089568 ns      1089519 ns          594
knapsack_handler_tabulation     843631 ns       843624 ns          876
knapsack_handler_tabulation     884242 ns       884247 ns          717
knapsack_handler_tabulation     729051 ns       728534 ns          866
knapsack_handler_tabulation    1303246 ns      1303232 ns          550
knapsack_handler_tabulation    1288841 ns      1288492 ns          539
knapsack_handler_tabulation     741127 ns       741112 ns          834
knapsack_handler_tabulation    1092041 ns      1092014 ns          606
knapsack_handler_tabulation     399632 ns       399628 ns         1952
knapsack_handler_tabulation     294332 ns       294297 ns         2375
"""

iterations_pattern = r'\s+(\d+)\s*$'
iterations = re.findall(iterations_pattern, table_data, re.MULTILINE)
iterations = [int(iteration) for iteration in iterations]

time_values = []
pattern = r"\s(\d+)\s+ns"

for line in table_data.splitlines():
    match = re.search(pattern, line)
    if match:
        time_values.append(int(match.group(1)))

average_times = [time / iter_count for time, iter_count in zip(time_values, iterations)]

input_counts = []
for i in range(1, 31):
    filename = f"test_{i}.in"
    try:
        with open(filename, 'r') as file:
            inputs = file.readlines()
            input_counts.append(len(inputs))
    except FileNotFoundError:
        print(f"File {filename} not found.")
        input_counts.append(0)

paired_values = list(zip(input_counts, average_times))

sorted_pairs = sorted(paired_values, key=lambda x: x[0])

sorted_input_counts, sorted_time_values = zip(*sorted_pairs)

sorted_input_counts = list(sorted_input_counts)
sorted_time_values = list(sorted_time_values)

slope, intercept = np.polyfit(sorted_input_counts, sorted_time_values, 1)

regression_line = np.polyval([slope, intercept], sorted_input_counts)

plt.figure(figsize=(10, 6))
plt.plot(sorted_input_counts, sorted_time_values, marker='o', linestyle='-', color='b', label='Algorithm Runtime')

plt.plot(sorted_input_counts, regression_line, color='red', linestyle='--', label='Linear Regression')

plt.xlabel('Number of Inputs')
plt.ylabel('Time (ns)')
plt.grid(True)
plt.legend()

plt.tight_layout()
plt.show()