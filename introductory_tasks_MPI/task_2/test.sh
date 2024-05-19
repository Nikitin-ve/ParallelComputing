#!/bin/sh
#SBATCH -n 40
#SBATCH -o Hello-%j.out
#SBATCH -e Hello-%j.err
mpiexec -n 40 ./main 1000
