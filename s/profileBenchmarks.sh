#!/bin/bash

valgrind --tool=callgrind ./bin/01*

valgrind --tool=callgrind ./bin/02*

