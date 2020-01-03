 
#!/bin/bash

valgrind --tool=massif --time-unit=B  ./../build/bin/02*

###use massif-visualizer to view output file.
