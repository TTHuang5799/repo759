#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=20
#SBATCH --output=task3.output
#SBATCH --error=task3.err

cd $SLURM_SUBMIT_DIR

module load gcc/13.2.0
module load nvidia/cuda

if [ -d "repo759" ]; then
  cd repo759
  rm -rf .git
  cd ..
  rm -r repo759
fi


git clone https://github.com/TTHuang5799/repo759.git
echo "repository exists"
cd repo759/HW04

OUTPUT_DIR="."

# Create empty result files inside the HW04 directory
touch "${OUTPUT_DIR}/results_static.txt"
touch "${OUTPUT_DIR}/results_dynamic.txt"
touch "${OUTPUT_DIR}/results_guided.txt"

g++ task3.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp

if [ "$1" = "p4" ]; then
    for policy in static dynamic guided; do
        for threads in {1..8}; do
            echo "Running $policy scheduling with number of particles: 100, simulation end time: 100, and $threads threads"
            ./task3 100 100 $threads $policy >> "${OUTPUT_DIR}/results_${policy}.txt"
        done
    done
fi
