#!/bin/bash

(./simpledu -l ../TestDir -L -a -B19 --count-links -S || echo $?) | sort -k2 > testeT_simpledu.txt
(du -l ../TestDir -L -a -B19 --count-links -S || echo $?) | sort -k2 > testeT_du.txt
diff -q testeT_simpledu.txt testeT_du.txt > /dev/null 2>&1 && echo OK || echo FAILED
