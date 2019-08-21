#!/bin/csh

#set RUN=$argv[1]        #  RUN
#set COMFILE=$argv[2]   #  COMMENT FILE
#set OPTION=$argv[3]      #  FORCE OR NONE

set WORKDIR="/crhome/sato.kenta/RHICf/Analysis/RHIC/Reconstruction"
set BINDIR=${WORKDIR}/bin

#set TMP=`/usr/bin/printf '%08d' $RUN`;
#set INPUTFILE="/data1/DATA1/RHICf_Op2017/root_files/run${TMP}.root"
set INPUTFILE="/mnt/lhcfs3/data5/RHICf_DATA1/RHICf_Op2017/root_files/run00002924.root"
#set INPUTFILE="/mnt/lhcfs3/data5/RHICf_DATA1/RHICf_Op2017/root_files/run${TMP}.root"
#set ANALBASEDIR="/data1/DATA1/RHICf_Op2017/quickanalysis_results/"

set ANALBASEDIR="/crhome/sato.kenta/RHICf/data/rhicf_2017_reconstruct"
#set INITRUNFILE="${ANALBASEDIR}/.initrun.out"
#set QUICKANALDIR="${ANALBASEDIR}/run${TMP}"
#set OUTPUTDIR="${QUICKANALDIR}/hists_run${TMP}"
#set PEDEFILE="${QUICKANALDIR}/pede_run${TMP}.root"
#set RECFILE="${QUICKANALDIR}/run${TMP}_rec.root"
#set PHYSHISTFILE="${OUTPUTDIR}/physhists_run${TMP}.root"
set INITRUNFILE="${ANALBASEDIR}/.initrun.out"
set QUICKANALDIR="${ANALBASEDIR}/run00002924"
set OUTPUTDIR="${QUICKANALDIR}/hists_run00002924"
set PEDEFILE="${QUICKANALDIR}/pede_run00002924.root"
set RECFILE="${QUICKANALDIR}/run00002924_rec.root"
set PHYSHISTFILE="${OUTPUTDIR}/physhists_run2924.root"

#FOR PEDESTAL FILE
set HISTFILE_NOR="${OUTPUTDIR}/hist_run00002924.root"
set HISTFILE_SUB="${OUTPUTDIR}/hist_run00002924_sub.root"
set RUNINFOFILE="/mnt/lhcfs3/data5/RHICf_DATA1/RHICf_Op2017/quickanalysis_results/run00002924/runinfo_run00002924.dat"
set RUNDATAFILE="/mnt/lhcfs3/data5/RHICf_DATA1/RHICf_Op2017/quickanalysis_results/run00002924/rundata_run00002924.root"


# Clear Comment
#/bin/rm -f $COMFILE; echo ""

# CHIECK EXISTANCE OF DATA FILE
if(! -e $INPUTFILE )then
  echo  $INPUTFILE  " do not exist."
  exit
endif

#which /usr/bin/mkdir


# MAKE DIRECTORY FOR QUICK ANALYSIS RESULTS
if( ! -d $QUICKANALDIR ) then
    /bin/mkdir -p $QUICKANALDIR
endif

# MAKE DIRECTORY FOR HISTOGRAMS
if( ! -d $OUTPUTDIR ) then
    /bin/mkdir -p $OUTPUTDIR
endif

#if( ! -e $RECFILE || $OPTION == "FORCE" )then
  
cd $WORKDIR 

/bin/date


# MAKE Pedestalfile
#  /bin/rm -f $COMFILE; echo "Making hists(nor)." > $COMFILE
  $BINDIR/adchists -i $INPUTFILE -o $HISTFILE_NOR -opede $PEDEFILE \
             -nodraw -q -b

#  /bin/rm -f $COMFILE; echo "Making hists(sub)." > $COMFILE
  $BINDIR/adchists -i $INPUTFILE -o $HISTFILE_SUB -opede $PEDEFILE \
             -ipede $PEDEFILE -runinfo $RUNINFOFILE -rundata $RUNDATAFILE \
             -subd -nodraw -q -b

# Quick Reconstruction 
#/bin/rm -f $COMFILE; echo "Doing Quick Reconstruction" > $COMFILE
echo "Quick Reconstruction -------------------------------"
$BINDIR/reconstruction02 -i $INPUTFILE -o $RECFILE -p $PEDEFILE 
#     -b -q 

# Make Physics Histograms 
#/bin/rm -f $COMFILE; echo "Making Physics Histograms" > $COMFILE
echo "Make Histograms ------------------------------------"
$BINDIR/makehistograms -i $RECFILE -o $PHYSHISTFILE -q -b

# Draw Histograms
#/bin/rm -f $COMFILE; echo "Drawing Physics Histograms" > $COMFILE
#echo "Draw Histograms ------------------------------------"
#$BINDIR/drawhistograms -i $PHYSHISTFILE --path $OUTPUTDIR -q -b
#$BINDIR/drawhistograms -i $PHYSHISTFILE --path $OUTPUTDIR  #comment out in 2017/12/26

# Draw Histograms
#/bin/rm -f $COMFILE; echo "Drawing Physics Histograms" > $COMFILE
#echo "Draw Cal Histograms ------------------------------------"
#$BINDIR/drawcalhists -i $RECFILE --path $OUTPUTDIR -q -b  #comment out in 2017/12/26

#/usr/bin/date

endif

