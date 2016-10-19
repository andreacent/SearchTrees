#!/bin/sh

make $1.act1
	
rm $1.csv
touch $1.csv

echo $1

echo "grupo, algorithm, domain, instance, cost, generated, time, gen_per_sec" >> $1.csv

while IFS='' read -r line || [[ -n "$line" ]]; do
	printf "$line" | timeout --signal=SIGINT 10m ./$1.act1 >> $1.csv
done < "../instances/$1.txt"