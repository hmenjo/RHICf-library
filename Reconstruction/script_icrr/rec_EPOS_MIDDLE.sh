#!/bin/csh
#------ pjsub option --------#
#PJM -L "rscgrp=B" 
#PJM -L "vnode=1" 
#PJM -L "vnode-core=1"
#PJM -j
#PJM -o "./log/EPOS_MIDDLE_run$argv[1]_%j.out" 
#------- Program execution -------#

source /etc/profile.d/modules.csh 
source /usr/local/gcc485/ROOT/5.34.36/bin/thisroot.csh /usr/local/gcc485/ROOT/5.34.36/ 

set RUN=$argv[1]        #  RUN
set START=0      
set END=1000000         

set WORKDIR="/home/menjo/RHICf/Op2017/RHICf-library/Reconstruction/"
set BINDIR=${WORKDIR}/bin

source $WORKDIR/script_icrr/base.sh

set TMP=`/usr/bin/printf '%08d' $RUN`;
set TMPSTART=`/usr/bin/printf '%08d' $START`
set TMPEND=`/usr/bin/printf '%08d' $END`
#INPUTFILE PATH
set INPUTFILE="/disk/lhcf/rhicf/SimulationData/pp510GeV_new/EPOS/MIDDLE/20190709/dir${RUN}/CONVERT_20190709_SIMF_EPOSLHC_MIDDLE_${RUN}.root"
set PEDEFILE="/disk/lhcf/rhicf/RHICf_Op2017/quickanalysis_results/run00002798/pede_run00002798.root"
set AVEPEDEFILE="./tables/average_pedestal/average_pedestal_run2798.dat"
#OUTPUT DIRECTORY PATH
set ANALBASEDIR="${RECBASEDIR}/EPOS-LHC/MIDDLE/"
set ANALDIR="${ANALBASEDIR}"
set RECFILE="${ANALDIR}/REC_20190709_SIMF_EPOSLHC_MIDDLE_${RUN}.root"
#set PEDELIST="${RECBASEDIR}/Op2017/MIDDLE_1/run00002798/run00002798_pedelist.root"
set PEDELIST="${RECBASEDIR}/Op2017/Pedelist/pedelist_MIDDLE.root"

# Clear Comment
#/bin/rm -f $COMFILE; echo ""

# CHIECK EXISTANCE OF DATA FILE
if(! -e $INPUTFILE )then
  echo  $INPUTFILE  " do not exist."
  exit
endif

# MAKE DIRECTORY FOR QUICK ANALYSIS RESULTS
if( ! -d $ANALDIR ) then
    /bin/mkdir -p $ANALDIR
endif
  
cd $WORKDIR 

/bin/date
echo "--------------Reconstruction -------------------------------"
#$BINDIR/reconstruction02 -r TS -i $INPUTFILE -o $RECFILE -p $PEDEFILE -avep $AVEPEDEFILE -f ${START} -t ${END} --simtrue --all -q -b 

$BINDIR/reconstruction02 -r TS -i $INPUTFILE -o $RECFILE -p $PEDEFILE -avep $AVEPEDEFILE -f ${START} -t ${END} --simped --pedelist "${PEDELIST}" --all -q -b 

/bin/date

endif

