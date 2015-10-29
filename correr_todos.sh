#!/bin/bash

if [ "$1" == "" ]; then
  echo "Ingresa el numero de filas como primer argumento"
fi

if [ "$2" == "" ]; then
  echo "Ingresa el numero de threads como segundo argumento"
fi

rm resultados.txt
touch resultados.txt
echo 'cpu_fil ' >> resultados.txt
./cpu_fil $1 $1 >> resultados.txt
echo 'cpu_col ' >> resultados.txt
./cpu_col $1 $1 >> resultados.txt
echo 'cpu_mutex ' >> resultados.txt
./cpu_mutex $1 $1 $2 >> resultados.txt
echo 'cpu_threads ' >> resultados.txt
./cpu_threads $1 $1 $2 >> resultados.txt
echo 'cpu_local ' >> resultados.txt
./cpu_local $1 $1 $2 >> resultados.txt
echo 'es_fil' >> resultados.txt
./es_fil masc_sentences.tsv >> resultados.txt
echo 'es_fil' >> resultados.txt
./es_threads masc_sentences.tsv $2 >> resultados.txt
