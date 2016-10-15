#!/bin/sh

if [ $1 -eq 0 ]; then
	echo "1"
	# PANCAKE
	make pancake24.act0
	make pancake24.act1
	make pancake24.act2

	make pancake28.act0
	make pancake28.act1
	make pancake28.act2

	# HANOI
	make hanoi-14-4.act0
	make hanoi-14-4.act1

	make hanoi-16-4.act0
	make hanoi-16-4.act1

	# TOPSPIN
	make topSpin22-4.act0
	make topSpin22-4.act1
	make topSpin22-4.act2

	make topSpin26-4.act0
	make topSpin26-4.act1
	make topSpin26-4.act2

elif [ $1 -eq 1 ]; then
	rm -rf resultados.txt
	touch resultados.txt

	I=0

	# PANCAKE
	D=6
	echo "-----------------------" >> resultados.txt
	echo "Pancake 24" >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "N=0" >> resultados.txt
	./pancake24.act0 $D $I >> resultados.txt
	echo >> resultados.txt
	echo "N=1" >> resultados.txt
	./pancake24.act1 $D $I >> resultados.txt
	echo >> resultados.txt
	echo "N=2" >> resultados.txt
	./pancake24.act2 $D $I >> resultados.txt

	echo >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "Pancake 28" >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "N=0" >> resultados.txt
	./pancake28.act0 $D $I >> resultados.txt
	echo >> resultados.txt
	echo "N=1" >> resultados.txt
	./pancake28.act1 $D $I >> resultados.txt
	echo >> resultados.txt
	echo "N=2" >> resultados.txt
	./pancake28.act2 $D $I >> resultados.txt

	# TOPSPIN
	D=7
	echo >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "TopSpin 22 4" >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "N=0" >> resultados.txt
	./topSpin22-4.act0 $D $I >> resultados.txt
	echo >> resultados.txt
	echo "N=1" >> resultados.txt
	./topSpin22-4.act1 $D $I >> resultados.txt
	echo >> resultados.txt
	echo "N=2" >> resultados.txt
	./topSpin22-4.act2 $D $I >> resultados.txt

	echo >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "TopSpin 26 4" >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "N=0" >> resultados.txt
	./topSpin26-4.act0 $D $I >> resultados.txt
	echo >> resultados.txt
	echo "N=1" >> resultados.txt
	./topSpin26-4.act1 $D $I >> resultados.txt
	echo >> resultados.txt
	echo "N=2" >> resultados.txt
	./topSpin26-4.act2 $D $I >> resultados.txt

	
	# HANOI
	D=12
	echo >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "Hanoi 14 4" >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "N=0" >> resultados.txt
	./hanoi-14-4.act0 $D $I >> resultados.txt
	echo >> resultados.txt
	echo "N=1" >> resultados.txt
	./hanoi-14-4.act1 $D $I >> resultados.txt

	echo >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "Hanoi 16 4" >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "N=0" >> resultados.txt
	./hanoi-16-4.act0 $D $I >> resultados.txt
	echo >> resultados.txt
	echo "N=1" >> resultados.txt
	./hanoi-16-4.act1 $D $I >> resultados.txt
fi

