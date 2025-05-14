#!/bin/bash
#SBATCH --account=csc4760-001-2025s
#SBATCH --cpus-per-task=1
#SBATCH --ntasks=4
#SBATCH --mem=32G

spack load openmpi

echo "Running Makefile"

make all

echo "Running Script"

make run

echo "Clean"

make clean

echo "All Finished"
