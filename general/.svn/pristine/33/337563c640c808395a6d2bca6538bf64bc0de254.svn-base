#!/bin/tcsh -f

set SRUN=29101
set ERUN=29200
set loop=0
set nloop=10

set datapath=/home2/LHCf/Simulation/LHC/end2end_root10

while($loop < $nloop)
  set outdir=/home2/LHCf/Simulation/LHC/tmp
  set outname=darm_run${SRUN}_${ERUN}.root
  set outfile=${outdir}/${outname}

  ./combine -s $SRUN -e $ERUN -t end2end -p ${datapath} -o ${outfile}

  @ SRUN = $SRUN + 100
  @ ERUN = $ERUN + 100
  @ loop = $loop + 1

end
