#!/usr/bin/env zsh
#SBATCH -p instruction
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
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
cd repo759/HW02

g++ task3.cpp matmul.cpp -Wall -O3 -std=c++17 -o task3

if [ "$1" -ge 1000 ]; then
  ./task3 "$1"
else
  echo "The dimension has to be >= 1000"
fi