#!/bin/bash
myDir=$PWD
valgrind --tool=cachegrind --branch-sim=yes --cache-sim=yes ./../build/bin/01*
cg_annotate cachegrind.out.* ${PWD}/experiments/basicBenchmarks/remove100StructFList.cpp 
cg_annotate cachegrind.out.* ${PWD}/experiments/basicBenchmarks/remove100StructVector.cpp #must be abolute path, no ./../. in path either this is a bit of a bug.
