#!/bin/bash
#PBS  -q one_day
#PBS  -j oe
#PBS  -l nodes=1:ppn=1
#PBS  -o /crhome/sato.kenta/RHICf/data/log/job_${PBS_JOBID}.out 

LOG="/mnt/lhcfs2/data1/sato.kenta/workspace/RHICf/Analysis/RHIC/Reconstruction/job_control/selflog/reclog_${PBS_JOBID}.txt"
source /crhome/sato.kenta/.bashrc

echo "JOBID=${PBS_JOBID}" > ${LOG}
echo "HOST" $HOSTNAME >> ${LOG}
echo "RUN START END=${RUN} ${START} ${END}" >> ${LOG}
	
echo "START" >> ${LOG}
date >> ${LOG}

cd /mnt/lhcfs2/data1/sato.kenta/workspace/RHICf/Analysis/RHIC/Reconstruction
./reconstruction02.csh $RUN $START $END>> ${LOG}

#./reconstruction02_loop.csh >> ${LOG}

echo "END" >> ${LOG}
date >> ${LOG}
echo " " >> ${LOG}
