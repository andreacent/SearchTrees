#!/bin/sh

if [ $1 -eq 0 ]; then
	echo "1"
	# PANCAKE
	make pancake24.iddfs0
	make pancake24.iddfs1
	make pancake24.iddfs2

	make pancake28.iddfs0
	make pancake28.iddfs1
	make pancake28.iddfs2

	# HANOI
	make hanoi-14-4.iddfs0
	make hanoi-14-4.iddfs1

	make hanoi-16-4.iddfs0
	make hanoi-16-4.iddfs1

	# TOPSPIN
	make topSpin22-4.iddfs0
	make topSpin22-4.iddfs1
	make topSpin22-4.iddfs2

	make topSpin26-4.iddfs0
	make topSpin26-4.iddfs1
	make topSpin26-4.iddfs2

elif [ $1 -eq 1 ]; then
	touch clean.txt

	I=0

	# PANCAKE
	D=6
	echo "-----------------------"
	echo "Pancake 24"
	echo "-----------------------"
	echo "N=0"
	./pancake24.iddfs0 $D $I >> clean.txt
	echo
	echo "N=1"
	./pancake24.iddfs1 $D $I >> clean.txt
	echo
	echo "N=2"
	./pancake24.iddfs2 $D $I >> clean.txt

	echo
	echo "-----------------------"
	echo "Pancake 28"
	echo "-----------------------"
	echo "N=0"
	./pancake28.iddfs0 $D $I >> clean.txt
	echo
	echo "N=1"
	./pancake28.iddfs1 $D $I >> clean.txt
	echo
	echo "N=2"
	./pancake28.iddfs2 $D $I >> clean.txt

	# HANOI
	D=12
	echo
	echo "-----------------------"
	echo "Hanoi 14 4"
	echo "-----------------------"
	echo "N=0"
	./hanoi-14-4.iddfs0 $D $I >> clean.txt
	echo
	echo "N=1"
	./hanoi-14-4.iddfs1 $D $I >> clean.txt

	echo
	echo "-----------------------"
	echo "Hanoi 16 4"
	echo "-----------------------"
	echo "N=0"
	./hanoi-16-4.iddfs0 $D $I >> clean.txt
	echo
	echo "N=1"
	./hanoi-16-4.iddfs1 $D $I >> clean.txt

	# TOPSPIN
	D=7
	echo
	echo "-----------------------"
	echo "TopSpin 22 4"
	echo "-----------------------"
	echo "N=0"
	./topSpin22-4.iddfs0 $D $I >> clean.txt
	echo
	echo "N=1"
	./topSpin22-4.iddfs1 $D $I >> clean.txt
	echo
	echo "N=2"
	./topSpin22-4.iddfs2 $D $I >> clean.txt

	echo
	echo "-----------------------"
	echo "TopSpin 26 4"
	echo "-----------------------"
	echo "N=0"
	./topSpin26-4.iddfs0 $D $I >> clean.txt
	echo
	echo "N=1"
	./topSpin26-4.iddfs1 $D $I >> clean.txt
	echo
	echo "N=2"
	./topSpin26-4.iddfs2 $D $I >> clean.txt

	rm -rf clean.txt
fi

