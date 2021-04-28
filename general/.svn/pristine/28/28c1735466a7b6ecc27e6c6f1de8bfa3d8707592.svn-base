#!/bin/tcsh -f

set RUN=90038
set A1RUN=90038
set A2RUN=20301
set loop=0
set nloop=15

while($loop < $nloop)

  set indir=/home2/LHCf/Simulation/LHC/end2end90
  set inname=end2end_run${A1RUN}.out
  set infile=${indir}/${inname}
  set outdir=/home2/LHCf/Simulation/LHC/end2end_root90
  set outname=end2end_run${A1RUN}.root
  set outfile=${outdir}/${outname}
  set errdir=/home2/LHCf/Simulation/LHC/end2end_root90
  set errname=err_end2end_run${A1RUN}.out
  set errfile=${errdir}/${errname}

  # cp -f ${infile}* .
  # gunzip ${inname}*
  # ./simbuild -run ${RUN} -a1 ${inname} -o ${outfile} -cutke 10.0 -cuty 8.0
  # rm -f ${inname}
  
  ./simbuild -run ${RUN} -a1 ${infile} -o ${outfile} -cutke 10.0 -cuty 8.0

  @ RUN = $RUN + 1
  @ A1RUN = $A1RUN + 1
  @ A2RUN = $A2RUN + 1
  @ loop = $loop + 1
end

