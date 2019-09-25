#!/bin/bash

valgrind --tool=memcheck --leak-check=yes ./bin/07*
