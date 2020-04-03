#!/bin/bash

(./simpledu -l ./test --max-depth=2 -a -B kB || echo $?) | sort -k2 > testeT_simpledu.txt
(du -l ./test --max-depth=2 -a -B kB || echo $?) | sort -k2 > testeT_du.txt
diff -q testeT_simpledu.txt testeT_du.txt > /dev/null 2>&1 && echo OK || echo FAILED
