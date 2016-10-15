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

	#11-PUZZLE
	make 11puzzle.iddfs0
	make 11puzzle.iddfs1
	make 11puzzle.iddfs2

elif [ $1 -eq 1 ]; then
	rm -rf resultados_iddfs.txt
	touch resultados_iddfs.txt

	I=0

	# PANCAKE
	D=6
	echo "-----------------------" >> resultados_iddfs.txt
	echo "Pancake 24" >> resultados_iddfs.txt
	echo "-----------------------" >> resultados_iddfs.txt
	echo "N=0" >> resultados_iddfs.txt
	./pancake24.iddfs0 $D $I >> resultados_iddfs.txt
	echo >> resultados_iddfs.txt
	echo "N=1" >> resultados_iddfs.txt
	./pancake24.iddfs1 $D $I >> resultados_iddfs.txt
	echo >> resultados_iddfs.txt
	echo "N=2" >> resultados_iddfs.txt
	./pancake24.iddfs2 $D $I >> resultados_iddfs.txt

	echo >> resultados_iddfs.txt
	echo "-----------------------" >> resultados_iddfs.txt
	echo "Pancake 28" >> resultados_iddfs.txt
	echo "-----------------------" >> resultados_iddfs.txt
	echo "N=0" >> resultados_iddfs.txt
	./pancake28.iddfs0 $D $I >> resultados_iddfs.txt
	echo >> resultados_iddfs.txt
	echo "N=1" >> resultados_iddfs.txt
	./pancake28.iddfs1 $D $I >> resultados_iddfs.txt
	echo >> resultados_iddfs.txt
	echo "N=2" >> resultados_iddfs.txt
	./pancake28.iddfs2 $D $I >> resultados_iddfs.txt

	# TOPSPIN
	D=7
	echo >> resultados_iddfs.txt
	echo "-----------------------" >> resultados_iddfs.txt
	echo "TopSpin 22 4" >> resultados_iddfs.txt
	echo "-----------------------" >> resultados_iddfs.txt
	echo "N=0" >> resultados_iddfs.txt
	./topSpin22-4.iddfs0 $D $I >> resultados_iddfs.txt
	echo >> resultados_iddfs.txt
	echo "N=1" >> resultados_iddfs.txt
	./topSpin22-4.iddfs1 $D $I >> resultados_iddfs.txt
	echo >> resultados_iddfs.txt
	echo "N=2" >> resultados_iddfs.txt
	./topSpin22-4.iddfs2 $D $I >> resultados_iddfs.txt

	echo >> resultados_iddfs.txt
	echo "-----------------------" >> resultados_iddfs.txt
	echo "TopSpin 26 4" >> resultados_iddfs.txt
	echo "-----------------------" >> resultados_iddfs.txt
	echo "N=0" >> resultados_iddfs.txt
	./topSpin26-4.iddfs0 $D $I >> resultados_iddfs.txt
	echo >> resultados_iddfs.txt
	echo "N=1" >> resultados_iddfs.txt
	./topSpin26-4.iddfs1 $D $I >> resultados_iddfs.txt
	echo >> resultados_iddfs.txt
	echo "N=2" >> resultados_iddfs.txt
	./topSpin26-4.iddfs2 $D $I >> resultados_iddfs.txt

	# HANOI
	D=12
	echo >> resultados_iddfs.txt
	echo "-----------------------" >> resultados_iddfs.txt
	echo "Hanoi 14 4" >> resultados_iddfs.txt
	echo "-----------------------" >> resultados_iddfs.txt
	echo "N=0" >> resultados_iddfs.txt
	./hanoi-14-4.iddfs0 $D $I >> resultados_iddfs.txt
	echo >> resultados_iddfs.txt
	echo "N=1" >> resultados_iddfs.txt
	./hanoi-14-4.iddfs1 $D $I >> resultados_iddfs.txt

	echo >> resultados_iddfs.txt
	echo "-----------------------" >> resultados_iddfs.txt
	echo "Hanoi 16 4" >> resultados_iddfs.txt
	echo "-----------------------" >> resultados_iddfs.txt
	echo "N=0" >> resultados_iddfs.txt
	./hanoi-16-4.iddfs0 $D $I >> resultados_iddfs.txt
	echo >> resultados_iddfs.txt
	echo "N=1" >> resultados_iddfs.txt
	./hanoi-16-4.iddfs1 $D $I >> resultados_iddfs.txt

	# 11-PUZZLE
	D=20
	echo >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "TopSpin 22 4" >> resultados.txt
	echo "-----------------------" >> resultados.txt
	echo "N=0" >> resultados.txt
	./11puzzle.iddfs0 $D $I >> resultados.txt
	echo >> resultados.txt
	echo "N=1" >> resultados.txt
	./11puzzle.iddfs1 $D $I >> resultados.txt
	echo >> resultados.txt
	echo "N=2" >> resultados.txt
	./11puzzle.iddfs2 $D $I >> resultados.txt

fi

