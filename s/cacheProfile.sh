#!/bin/bash
myDir=$PWD
valgrind --tool=cachegrind --branch-sim=yes --cache-sim=yes ./../build/bin/02*
#cg_annotate cachegrind.out.5306 ${PWD}/../build/bin/02* #must be abolute path, no ./../. in path either this is a bit of a bug.
