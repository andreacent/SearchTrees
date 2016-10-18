#!/bin/sh

for x in pancake16 hanoi-14-4 11puzzle; do
	make $x.act1
done

for x in pancake16 hanoi-14-4 11puzzle; do
	
	rm $x.csv
	touch $x.csv

	echo $x

	echo "grupo, algorithm, domain, instance, cost, generated, time, gen_per_sec" >> $x.csv

	while IFS='' read -r line || [[ -n "$line" ]]; do
		printf "$line" | timeout --signal=SIGINT 10m ./$x.act1 >> $x.csv
	done < "../instances/$x.txt"
done 