#!/bin/tcsh -f

set RUN=17151
set loop=0
set nloop=400

while($loop < $nloop)
  set indir=/home2/LHCf/Simulation/LHC/doublearm05
  set inname=darm_run${RUN}.out
  set infile=${indir}/${inname}
  set outdir=/home2/LHCf/Simulation/LHC/doublearm_root05
  set outname=darm_run${RUN}.root
  set outfile=${outdir}/${outname}
  set errdir=/home2/LHCf/Simulation/LHC/doublearm_root05
  set errname=err_darm_run${RUN}.out
  set errfile=${errdir}/${errname}

  rm -rf ${inname}*
  cp -f ${infile}* .
  gunzip ${inname}*
  ./darmbuild -run ${RUN} -i ${inname} -o ${outfile} -cutke 10.0 \
  -wCutbp -cutx 50. -offset_a1x -1.6 -offset_a2x -0.6
  rm -f ${inname}

  @ RUN = $RUN + 1
  @ loop = $loop + 1

end
