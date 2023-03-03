#!/bin/bash

make ft>/dev/null; make std>/dev/null;
./ft_test > log/ft && ./std_test > log/std
diff log/ft log/std
rm ft_test && rm std_test
