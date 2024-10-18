#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=20
#SBATCH --output=task2.output
#SBATCH --error=task2.err

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

if [ "$1" = "2c" ]; then
    g++ task2.cpp convolution.cpp -Wall -O3 -std=c++17 -o task2 -fopenmp
    n=1024
    for t in {1..20}; do
        echo "Running task2 for value n = 1024, t = $t"
        ./task2 $n $t
        echo 
    done
else 
    g++ task2.cpp convolution.cpp -Wall -O3 -std=c++17 -o task2 -fopenmp
    echo "Running task2 for value n = $1, t = $2"
    ./task2 $1 $2
fi