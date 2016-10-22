#!/bin/bash
#PBS -l nodes=1:ppn=1,pmem=2GB,walltime=01:00:00
#PBS -m n

# $1 nombre de la instancia

MAXMEM_MB=2048

make $1.a_est_mhttn
	
rm $1_a_est_mhttn.csv
touch $1_a_est_mhttn.csv

echo $1

echo "grupo, algorithm, heuristic, domain, instance, cost, h0, generated, time, gen_per_sec" >> $1_a_est_mhttn.csv

while IFS='' read -r line || [[ -n "$line" ]]; do
	ulimit -Sv $(($MAXMEM_MB*1024))
	echo "$line"
	printf "$line" | timeout --signal=SIGKILL 10s ./$1.a_est_mhttn >> $1_a_est_mhttn.csv
	ulimit -Sv unlimited
done < "../instances/$1.txt"