#!/bin/bash

valgrind --tool=massif --time-unit=B ./bin/01*

valgrind --tool=massif --time-unit=B ./bin/02*

