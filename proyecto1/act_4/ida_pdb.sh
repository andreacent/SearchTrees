#!/bin/bash
#PBS -l nodes=1:ppn=1,pmem=2GB,walltime=01:00:00
#PBS -m n

# $1 nombre de la instancia

MAXMEM_MB=2048

make $1.ida_pdb
	
rm $1_ida_pdb_$2.csv
touch $1_ida_pdb_$2.csv

echo $1

echo "grupo, algorithm, heuristic, domain, instance, cost, h0, generated, time, gen_per_sec" >> $1_ida_pdb_$2.csv

while IFS='' read -r line || [[ -n "$line" ]]; do
	ulimit -Sv $(($MAXMEM_MB*1024))
	echo "$line"
	printf "$line" | gtimeout --signal=SIGKILL 10s ./$1.ida_pdb $2 >> $1_ida_pdb_$2.csv
	ulimit -Sv unlimited
done < "../instances/$1.txt"
