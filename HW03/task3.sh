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
cd repo759/HW03

if [ "$1" = "c1" ]; then
    g++ task3.cpp msort.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp
    for i in {1..10}; do
        ts=$((2**i))
        echo "Running task3 for n = 10^6, t = 8, ts = $ts"
        ./task3 1000000 8 $ts
    done
elif [ "$1" = "c2" ]; then
    g++ task3.cpp msort.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp
    for i in {1..20}; do
        echo "Running task3 for n = 10^6, t = $i, best_ts = 1024"
        ./task3 1000000 $i 1024
    done
else
    g++ task3.cpp msort.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp
    echo "Running task3 for value n = $1, t = $2, ts = $3"
    ./task3 $1 $2 $3
fi