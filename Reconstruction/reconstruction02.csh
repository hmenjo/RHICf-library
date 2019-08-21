#!/bin/csh

set RUN=$argv[1]        #  RUN
set START=$argv[2]        #  RUN
set END=$argv[3]        #  RUN

set WORKDIR="./"
set BINDIR=${WORKDIR}/bin

set TMP=`/usr/bin/printf '%08d' $RUN`;
#INPUTFILE PATH
set INPUTFILE="/mnt/lhcfs3/data5/RHICf_DATA1/RHICf_Op2017/root_files/run${TMP}.root"
set PEDEFILE="/mnt/lhcfs3/data5/RHICf_DATA1/RHICf_Op2017/quickanalysis_results/run${TMP}/pede_run${TMP}.root"
#OUTPUT DIRECTORY PATH
set ANALBASEDIR="/crhome/sato.kenta/RHICf/data/rhicf_2017_reconstruct_lhcfs2"
set ANALDIR="${ANALBASEDIR}/run${TMP}"
set RECFILE="${ANALDIR}/run${TMP}_rec_${START}_${END}.root"


# Clear Comment
#/bin/rm -f $COMFILE; echo ""

# CHIECK EXISTANCE OF DATA FILE
if(! -e $INPUTFILE )then
  echo  $INPUTFILE  " do not exist."
  exit
endif

# MAKE DIRECTORY FOR QUICK ANALYSIS RESULTS
if( ! -d $QUICKANALDIR ) then
    /bin/mkdir -p $QUICKANALDIR
endif

# MAKE DIRECTORY FOR HISTOGRAMS
if( ! -d $OUTPUTDIR ) then
    /bin/mkdir -p $OUTPUTDIR
endif
  
cd $WORKDIR 

/bin/date
echo "--------------Reconstruction -------------------------------"
$BINDIR/reconstruction02 -i $INPUTFILE -o $RECFILE -p $PEDEFILE -avep $AVEPEDEFILE -run ${RUN} -f ${START} -t ${END}     -b -q 

/bin/date

endif

