#!/bin/csh
#PBS  -q one_day
#PBS  -j oe
#PBS  -l nodes=1:ppn=10
#PBS  -o /mnt/lhcfs2/data1/sato.kenta/workspace/RHICf/Analysis/RHIC/Reconstruction/job_control/log/job_${PBS_JOBID}.log 


setenv LOG="/mnt/lhcfs2/data1/sato.kenta/workspace/RHICf/Analysis/RHIC/Reconstruction/job_control/selflog/reclog_20181010_${RUN}.txt"
source /crhome/sato.kenta/.bashrc

echo "JOBID=${PBS_JOBID}" >> ${LOG}
echo "HOST" $HOSTNAME >> ${LOG}

echo "START" >> ${LOG}
date >> ${LOG}
echo "RUN=${RUN}"

cd /mnt/lhcfs2/data1/sato.kenta/workspace/RHICf/Analysis/RHIC/Reconstruction
/mnt/lhcfs2/data1/sato.kenta/workspace/RHICf/Analysis/RHIC/Reconstruction/rec_csh/reconstruction02_loop_2798.sh >> ${LOG}
#./reconstruction02_loop.csh >> ${LOG}

echo "END" >> ${LOG}
date >> ${LOG}
