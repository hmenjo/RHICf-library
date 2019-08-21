#!/bin/bash
#PBS  -q one_day
#PBS  -j oe
#PBS  -l nodes=1:ppn=1
#PBS  -o ./log/job_${PBS_JOBID}.log 


LOG="/mnt/lhcfs2/data1/sato.kenta/workspace/RHICf/Analysis/RHIC/Reconstruction/job_control/script/selflog/qsublog_${RUN}.txt"
REC_LOG="/mnt/lhcfs2/data1/sato.kenta/workspace/RHICf/Analysis/RHIC/Reconstruction/job_control/script/selflog/reclog_${RUN}.txt"
source /crhome/sato.kenta/.bashrc

echo "JOBID=${PBS_JOBID}" > ${LOG}
echo "HOST" $HOSTNAME >> ${LOG}
echo "RUN" ${RUN} >> ${LOG}
echo "START" >> ${LOG}
date >> ${LOG}

cd /mnt/lhcfs2/data1/sato.kenta/workspace/RHICf/Analysis/RHIC/Reconstruction
./reconstruction02.csh ${RUN} > ${REC_LOG}

#./reconstruction02_loop.csh >> ${LOG}

echo "END" >> ${LOG}
date >> ${LOG}
