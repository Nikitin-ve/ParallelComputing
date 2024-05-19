#!/bin/sh
#SBATCH -n 40
#SBATCH -o matrix.txt
./gen 100 100 100
