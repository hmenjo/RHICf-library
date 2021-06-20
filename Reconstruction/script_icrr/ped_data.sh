#!/bin/csh
#------ pjsub option --------#
#PJM -L "rscgrp=lhcf" 
#PJM -L "vnode=1" 
#PJM -L "vnode-core=1"
#PJM -j
#PJM -o "./log/pede_run$argv[1]_%j.out" 
#------- Program execution -------#

source /etc/profile.d/modules.csh 
source /usr/local/gcc485/ROOT/5.34.36/bin/thisroot.csh /usr/local/gcc485/ROOT/5.34.36/ 

set RUN=$argv[1]        #  RUN
set DATATAG=$argv[2]
#set START=$argv[2]      #  RUN
#set END=$argv[3]        #  RUN
set START=0
set END=1000000000

set WORKDIR="/home/menjo/RHICf/Op2017/RHICf-library/Reconstruction/"
set BINDIR=${WORKDIR}/bin

source $WORKDIR/script_icrr/base.sh

set TMP=`/usr/bin/printf '%08d' $RUN`;
set TMPSTART=`/usr/bin/printf '%08d' $START`
set TMPEND=`/usr/bin/printf '%08d' $END`
#INPUTFILE PATH
set INPUTFILE="/disk/lhcf/rhicf/RHICf_Op2017/root_files/run${TMP}.root"
set PEDEFILE="/disk/lhcf/rhicf/RHICf_Op2017/quickanalysis_results/run${TMP}/pede_run${TMP}.root"
set AVEPEDEFILE="./tables/average_pedestal/average_pedestal_run${RUN}.dat"
#OUTPUT DIRECTORY PATH
set ANALBASEDIR="${RECBASEDIR}/Op2017/${DATATAG}"
set ANALDIR="${ANALBASEDIR}/run${TMP}"
set RECFILE="${ANALDIR}/run${TMP}_pedelist.root"
#set RECFILE="test.root"

set TMPFILE="./tmp_run${RUN}.root"
set HISTFILE="${ANALDIR}/run${TMP}_pedehist.root"
set PEDEOUTFILE="${ANALDIR}/run${TMP}_pede.root"


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
$BINDIR/reconstruction02 -r TS -i $INPUTFILE -o $TMPFILE -p $PEDEFILE -avep $AVEPEDEFILE -f ${START} -t ${END} --pedestal_forsim -b -q

$BINDIR/checkpedelist -i $TMPFILE  -o $HISTFILE  --pedelist $RECFILE --avpede $PEDEOUTFILE -b -q   

/bin/rm -f $TMPFILE

/bin/date

endif

