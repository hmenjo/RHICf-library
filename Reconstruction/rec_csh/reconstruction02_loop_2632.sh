#!/bin/sh
LOOP=0
NLOOP=821
START=0
END=0
while [ $LOOP -lt $NLOOP ]
do
START=$((LOOP*1000))
END=$((LOOP*1000+1000))
../reconstruction02.csh 2632 $START $END
LOOP=$((LOOP+1))
done
