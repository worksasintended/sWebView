#!/bin/bash
make -j 4 && ./slurm_gui --docroot www/ --http-address 0.0.0.0 --http-port 8080 --approot app/
