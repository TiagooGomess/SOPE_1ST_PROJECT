#!/bin/bash

# flag -l is always set
echo "Compiling ..."
make
echo "Compiled!"


echo "Testing simple du ..."

# On TestDir
# flags -L -a -b (read bytes from all files)
echo "TEST1 | -a -b -L on TestDir"
(./simpledu -l ../TestDir -L -a -b || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../TestDir -L -a -b || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)

if [ "$DIFF" ]
then
	echo "FAIL"
else
	echo "OK"
fi


# On current folder
# flags -L -a -b (read bytes from all files)
echo "TEST2 | -a -b -L on Root"
(./simpledu -l . -L -a -b || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l . -L -a -b || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
	echo "OK"
fi

# On current folder/
# flags -L -a -b (read bytes from all files)
echo "TEST3 | -a -b -L on Root/"
(./simpledu -l ./ -L -a -b || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ./ -L -a -b || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
	echo "OK"
fi

# On Downloads folder
# flags -L -a -b (read bytes from all files)
echo "TEST4 | -a -b -L on Downloads"
(./simpledu -l /home/whitelizard/Downloads -L -a -b || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l /home/whitelizard/Downloads -L -a -b || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
	echo "OK"
fi


echo "TEST5 | -a -b on TestDir"
(./simpledu -l ../TestDir -a -b || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../TestDir -a -b || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi


echo "TEST6 | -a -b on TestDir/"
(./simpledu -l ../TestDir/ -a -b || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../TestDir/ -a -b || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST7 | -a -B 512 on TestDir/"
(./simpledu -l ../TestDir/ -a -B 512 || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../TestDir/ -a -B 512 || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST8 | -a -B 1024 on Root/"
(./simpledu -l . -a -B 1024 || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l . -a -B 1024 || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST9 | -a --block-size=2048 on Root/"
(./simpledu -l . -a --block-size=2048 || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l . -a --block-size=2048 || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST10 | --block-size=2048 on Root/"
(./simpledu -l . --block-size=2048 || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l . --block-size=2048 || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST11 | -L -b on TestDir/"
(./simpledu -l ../TestDir/ -L -b || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../TestDir/ -L -b || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST12 | -S -b -L on TestDir/"
(./simpledu -l ../TestDir/ -S -b -L || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../TestDir/ -S -b -L || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST13 | --max-depth=2 -S -L on TestDir/"
(./simpledu -l ../TestDir/ --max-depth=2 -S -L || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../TestDir/ --max-depth=2 -S -L || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST14 | -b -a on ../../"
(./simpledu -l ../../ -b -a || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../../ -b -a || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST15 | -B 4096 -a on ../../"
(./simpledu -l ../../ -B 4096 -a || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../../ -B 4096 -a || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST16 | -l on ."
(./simpledu -l . || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l . || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST17 | -l on ../"
(./simpledu -l ../ || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../ || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST18 | -l -b on ."
(./simpledu -l . -b || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l . -b || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST19 | -l -b -S on ../TestDir/"
(./simpledu -l ../TestDir/ -b -S || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../TestDir/ -b -S || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST20 | -l -b -S --max-depth=2 on ../TestDir/"
(./simpledu -l ../TestDir/ -b -S --max-depth=2 || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../TestDir/ -b -S --max-depth=2 || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST21 | -l -b -S --max-depth=2 on ../../../"
(./simpledu -l ../../../ -b -S --max-depth=2 || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../../../ -b -S --max-depth=2 || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi


echo "TEST22 | -l -B 1 on ../../../"
(./simpledu -l ../../../ -B 1 || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../../../ -B 1 || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST23 | -l -B 1 on ../TestDir"
(./simpledu -l ../TestDir -B 1 || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../TestDir -B 1 || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST24 | -l -a on ../TestDir"
(./simpledu -l ../TestDir -a || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../TestDir -a || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST25 | -l -a on ../../../"
(./simpledu -l ../../../ -a || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../../../ -a || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST26 | -l -a -L on ../TestDir/"
(./simpledu -l ../TestDir/ -a -L || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../TestDir/ -a -L || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST27 | -l -a -L on ../../"
(./simpledu -l ../../ -a -L || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../../ -a -L || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST28 | -l -a -L -b -S on ../../"
(./simpledu -l ../../ -a -L -b -S || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../../ -a -L -b -S || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST29 | -l -a -L -b -S on ../../../"
(./simpledu -l ../../../ -a -L -b -S || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../../../ -a -L -b -S || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST30 | -l -a -L -b --separate-dirs on ../../../"
(./simpledu -l ../../../ -a -L -b --separate-dirs || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../../../ -a -L -b --separate-dirs || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

echo "TEST31 | -l -a -L -b on ../../../../Downloads/"
(./simpledu -l ../../../../Downloads/ -a -L -b || echo $?) | sort -k2 > ~/tmp/teste_simpledu.txt
(du -l ../../../../Downloads/ -a -L -b || echo $?) | sort -k2 > ~/tmp/teste_du.txt

DIFF=$(diff -q ~/tmp/teste_simpledu.txt ~/tmp/teste_du.txt)
if [ "$DIFF" ]
then
	echo "FAIL"
else
  echo "OK"
fi

# clean
rm ~/tmp/teste* > /dev/null
make clean
