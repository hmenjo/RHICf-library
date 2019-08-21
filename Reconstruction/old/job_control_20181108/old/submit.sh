#!/bin/sh
#PBS -q one_day
#PBS -j oe
#PBS -l nodes=1:ppn=1
#PBS -o /mnt/lhcfs2/data1/sato.kenta/workspace/RHICf/Analysis/RHIC/Reconstruction/job_control/log/job_${PBS_JOBID}.log

#source /crhome/sato.kenta/.bashrc

echo "LHC SIMULATION"
pwd
echo "HOST" $HOSTNAME
echo "START"
date

date
echo "End"
