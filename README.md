# Knapsack Problem

## Archive contents
- `raport.pdf` - PDF documentation of the project
- `raport.tex` - LaTeX code for the pdf
- `img` - Folder containing the graphs
- `other` - folder containing old implementations
- `src` - folder containing the source files, tests and their results
- `utils` - folder containing the benchmark

## Tests Documentation
Tests are generated with the script `tests_gen.py`. There are 28 tests of
sizes specified in the `ns` array, ranging from size 20 all the way up to
90. Initially I had bigger input sizes, but the backtracking solution 
would take forever. 2 more tests are used from an online resource 
documented in the `References` section of the pdf file. The maximum 
capacity of the knapsack is generated randomly between max_weight // 2
(max_weight is a 1000, but it can be changed fairly easy) and max_weight.
The weights of the objects are randomly generated between 1 and half of
max_weight and the values between 1 and 1000. More info about the tests
and their results is written in the pdf file.
