#!/bin/bash

(./simpledu -l . -L --max-depth=2 -a || echo $?) | sort -k2 > testeT_simpledu.txt
(du -l . -L --max-depth=2 -a || echo $?) | sort -k2 > testeT_du.txt
diff -q testeT_simpledu.txt testeT_du.txt > /dev/null 2>&1 && echo OK || echo FAILED
