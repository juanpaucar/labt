#!/bin/bash

rm resultados.txt
touch resultados.txt
echo 'cpu_fil ' >> resultados.txt
./cpu_fil 200 200 >> resultados.txt
echo 'cpu_col ' >> resultados.txt
./cpu_col 200 200 >> resultados.txt
echo 'cpu_mutex ' >> resultados.txt
./cpu_mutex 200 200 4 >> resultados.txt
echo 'cpu_threads ' >> resultados.txt
./cpu_threads 200 200 4 >> resultados.txt
echo 'cpu_local ' >> resultados.txt
./cpu_local 200 200 4 >> resultados.txt
