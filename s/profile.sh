#!/bin/bash

valgrind --tool=callgrind ./../build/bin/02*

###use kCachegrind to view output file.
