#!/bin/sh
#SBATCH -n 40
#SBATCH -o Hello-%j.out
#SBATCH -e Hello-%j.err
./main 1000
