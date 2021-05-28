#!/bin/sh
python analyse.py $1
mv histoEnergy.root histoEnergy_$1.root
mv tree_run0.root tree_run0_$1.root

