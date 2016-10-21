#!/bin/sh

if [ $1 -eq 0 ]; then
	# PANCAKE
	make pancake24.act0
	make pancake24.act1
	make pancake24.act2

	make pancake28.act0
	make pancake28.act1
	make pancake28.act2

	# TOPSPIN
	make topSpin22-4.act0
	make topSpin22-4.act1
	make topSpin22-4.act2

	make topSpin26-4.act0
	make topSpin26-4.act1
	make topSpin26-4.act2

	# 11puzzle
	make 11puzzle.act0
	make 11puzzle.act1
	make 11puzzle.act2

	# HANOI
	make hanoi-14-4.act0
	make hanoi-14-4.act1

	make hanoi-16-4.act0
	make hanoi-16-4.act1

elif [ $1 -eq 1 ]; then
	rm -rf resultados.txt
	touch resultados.txt

	# PANCAKE
	D=6
	echo "-----------------------" >> resultados.txt
	echo "Pancake 24" >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "N=0" >> resultados.txt
	printf "1 2 3 4 5 6 9 8 7 10 19 18 17 16 15 14 13 12 11 20 21 22 23 0" | ./pancake24.act0 $D >> resultados.txt
	echo >> resultados.txt
	echo "N=1" >> resultados.txt
	printf "1 2 3 4 5 6 9 8 7 10 19 18 17 16 15 14 13 12 11 20 21 22 23 0" | ./pancake24.act1 $D >> resultados.txt
	echo >> resultados.txt
	echo "N=2" >> resultados.txt
	printf "1 2 3 4 5 6 9 8 7 10 19 18 17 16 15 14 13 12 11 20 21 22 23 0" | ./pancake24.act2 $D >> resultados.txt

	echo >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "Pancake 28" >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "N=0" >> resultados.txt
	printf "4 15 0 8 2 27 22 21 7 26 13 17 3 11 20 24 1 23 25 5 18 14 9 16 6 10 12 19" | ./pancake28.act0 $D >> resultados.txt
	echo >> resultados.txt
	echo "N=1" >> resultados.txt
	printf "4 15 0 8 2 27 22 21 7 26 13 17 3 11 20 24 1 23 25 5 18 14 9 16 6 10 12 19" | ./pancake28.act1 $D >> resultados.txt
	echo >> resultados.txt
	echo "N=2" >> resultados.txt
	printf "4 15 0 8 2 27 22 21 7 26 13 17 3 11 20 24 1 23 25 5 18 14 9 16 6 10 12 19" | ./pancake28.act2 $D >> resultados.txt

	# TOPSPIN
	D=7
	echo >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "TopSpin 22 4" >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "N=0" >> resultados.txt
	printf "1 2 3 4 5 6 7 8 9 0 10 11 12 13 14 15 16 17 18 21 19 20" | ./topSpin22-4.act0 $D >> resultados.txt
	echo >> resultados.txt
	echo "N=1" >> resultados.txt
	printf "1 2 3 4 5 6 7 8 9 0 10 11 12 13 14 15 16 17 18 21 19 20" | ./topSpin22-4.act1 $D >> resultados.txt
	echo >> resultados.txt
	echo "N=2" >> resultados.txt
	printf "1 2 3 4 5 6 7 8 9 0 10 11 12 13 14 15 16 17 18 21 19 20" | ./topSpin22-4.act2 $D >> resultados.txt

	echo >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "TopSpin 26 4" >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "N=0" >> resultados.txt
	printf "1 2 3 4 5 6 7 8 9 0 10 11 12 13 14 15 16 22 23 24 25 17 18 21 19 20" | ./topSpin26-4.act0 $D >> resultados.txt
	echo >> resultados.txt
	echo "N=1" >> resultados.txt
	printf "1 2 3 4 5 6 7 8 9 0 10 11 12 13 14 15 16 22 23 24 25 17 18 21 19 20" | ./topSpin26-4.act1 $D >> resultados.txt
	echo >> resultados.txt
	echo "N=2" >> resultados.txt
	printf "1 2 3 4 5 6 7 8 9 0 10 11 12 13 14 15 16 22 23 24 25 17 18 21 19 20" | ./topSpin26-4.act2 $D >> resultados.txt
	
	
	# 11-PUZZLE
	D=20
	echo >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "PUZZLE" >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "N=0" >> resultados.txt
	printf "3 1 2 4 7 5 B 6 10 9 11 8" | ./11puzzle.act0 $D >> resultados.txt
	echo >> resultados.txt
	echo "N=1" >> resultados.txt
	printf "3 1 2 4 7 5 B 6 10 9 11 8" | ./11puzzle.act1 $D >> resultados.txt
	echo >> resultados.txt
	echo "N=2" >> resultados.txt
	printf "3 1 2 4 7 5 B 6 10 9 11 8" | ./11puzzle.act2 $D >> resultados.txt
	
	# HANOI
	D=12
	echo >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "Hanoi 14 4" >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "N=0" >> resultados.txt
	printf "1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0" | ./hanoi-14-4.act0 $D >> resultados.txt
	echo >> resultados.txt
	echo "N=1" >> resultados.txt
	printf "1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0" | ./hanoi-14-4.act1 $D >> resultados.txt

	echo >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "Hanoi 16 4" >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "N=0" >> resultados.txt
	printf "1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0" | ./hanoi-16-4.act0 $D >> resultados.txt
	echo >> resultados.txt
	echo "N=1" >> resultados.txt
	printf "1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0" | ./hanoi-16-4.act1 $D >> resultados.txt

fi

