#!/bin/bash
#PBS  -q three_hours
#PBS  -j oe
#PBS  -l nodes=1:ppn=10
#PBS  -o /crhome/sato.kenta/RHICf/data/log/job_${PBS_JOBID}.log 




LOG="/mnt/lhcfs2/data1/sato.kenta/workspace/RHICf/Analysis/RHIC/Reconstruction/job_control/selflog/reclog.txt"
source /crhome/sato.kenta/.bashrc

echo "JOBID=${PBS_JOBID}" >> ${LOG}
echo "HOST" $HOSTNAME >> ${LOG}

echo "START" >> ${LOG}
date >> ${LOG}

cd /mnt/lhcfs2/data1/sato.kenta/workspace/RHICf/Analysis/RHIC/Reconstruction
./reconstruction02.csh 2798 >> ${LOG}
#./reconstruction02_loop.csh >> ${LOG}

echo "END" >> ${LOG}
date >> ${LOG}
