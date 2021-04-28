#/bin/tcsh

set RUN=$argv[1]        #  RUN

set TMP='printf '%08d' $RUN';
set INPUTFILE="/mnt/lhcfs3/data5/RHICf_DATA1/RHICf_Op2017/root_files/run${TMP}.root"
set ANALBASEDIR="/data1/DATA1/RHICf_Op2017/quickanalysis_results"
set QUICKANALDIR="${ANALBASEDIR}/run${TMP}"
set RUNINFOFILE="${QUICKANALDIR}/runinfo_run${TMP}.dat"

./sample_eventloop -run $RUN -info $RUNINFOFILE
