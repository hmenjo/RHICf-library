#!/bin/sh
LOOP=0
NLOOP=1775
START=0
END=0
while [ $LOOP -lt $NLOOP ]
do
START=$((LOOP*1000))
END=$((LOOP*1000+1000))
../reconstruction02.csh 2732 $START $END
LOOP=$((LOOP+1))
done
