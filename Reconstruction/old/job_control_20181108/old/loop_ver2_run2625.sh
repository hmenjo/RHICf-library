#!/bin/sh

maxjobs=220
maxmyjobs=30
LOOP=0
NLOOP=0
nevent[0]=1262

run[0]=2625
#echo "${run[@]}"
tsleep=120

NLOOP=1262
while [ $LOOP -lt $NLOOP ]
do  
  njobs=`qstat |wc -l`
  nmyjobs=`qstat -au sato.kenta| wc -l`
  ##echo ${njobs}
	
  if [ $njobs -lt $maxjobs ] && [ $nmyjobs -lt $maxmyjobs ] ; then 
	start=$((LOOP*1000))
	end=$((LOOP*1000+1000))
	echo "START=${start}"
	echo "END=${end}"
	cd /mnt/lhcfs2/data1/sato.kenta/workspace/RHICf/Analysis/RHIC/Reconstruction/job_control
  	qsub ./qsub_rec.sh -v RUN=2625,START=${start},END=${end}
	LOOP=$((LOOP+1))
	sleep 1
  else
      
  ##endif
      echo Wait more $tsleep seconds
      sleep $tsleep
  fi
  
done

