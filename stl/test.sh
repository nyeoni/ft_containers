#!/bin/bash

make ft>/dev/null; make std>/dev/null;
./ft_test > ft && ./std_test > std
diff ft std
rm ft_test && rm std_test
