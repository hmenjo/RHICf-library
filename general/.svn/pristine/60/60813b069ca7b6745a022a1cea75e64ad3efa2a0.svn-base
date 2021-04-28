#!/usr/bin/env python
# coding: UTF-8

import os
import sys

filename = sys.argv[1]
fin   = open(filename)
lines = fin.readlines();
fin.close()

for index, line in enumerate(lines):
    run, gnumber = line.split()
    print run, gnumber

    command = "LHCfprinteventview"
    command += " --type a1cal2 "
    command += " --run " + run
    command += " --gnumber " + gnumber
    command += " --form /mnt/lhcfs2/data5/pp13tev_rec/makino/v2.0_20160208/data/gc/run%5d_gc.root"
    print command
    os.system(command);
    

