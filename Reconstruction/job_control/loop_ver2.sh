#!/bin/sh

maxjobs=220
maxmyjobs=20
LOOP=0
NLOOP=74

run[0]=2625
run[1]=2627
run[2]=2630
run[3]=2631
run[4]=2632
run[5]=2633
run[6]=2634
run[7]=2636
run[8]=2637
run[9]=2641
run[10]=2644
run[11]=2718
run[12]=2721
run[13]=2726
run[14]=2730
run[15]=2732
run[16]=2734
run[17]=2736
run[18]=2738
run[19]=2740
run[20]=2798
run[21]=2801
run[22]=2803
run[23]=2810
run[24]=2812
run[25]=2814
run[26]=2818
run[27]=2819
run[28]=2823
run[29]=2824
run[30]=2827
run[31]=2845
run[32]=2847
run[33]=2850
run[34]=2852
run[35]=2854
run[36]=2857
run[37]=2864
run[38]=2867
run[39]=2868
run[40]=2877
run[41]=2878
run[42]=2881
run[43]=2883
run[44]=2887
run[45]=2889
run[46]=2892
run[47]=2896
run[48]=2899
run[49]=2902
run[50]=2903
run[51]=2904
run[52]=2905
run[53]=2923
run[54]=2924
run[55]=2925
run[56]=2932
run[57]=2933
run[58]=2937
run[59]=2939
run[60]=2947
run[61]=2954
run[62]=2956
run[63]=2958
run[64]=2960
run[65]=2964
run[66]=2966
run[67]=2968
run[68]=2970
run[69]=2972
run[70]=2973
run[71]=2979
run[72]=2981
run[73]=2983
#echo "${run[@]}"
tsleep=120

while [ $LOOP -lt $NLOOP ]
do  
  njobs=`qstat |wc -l`
  nmyjobs=`qstat -au sato.kenta| wc -l`
  ##echo ${njobs}
	
  if [ $njobs -lt $maxjobs ] && [ $nmyjobs -eq 0 ] ; then
	echo "${run[$LOOP]}" 
  	#qsub ./qsub_rec.sh -v RUN=${run[$LOOP]}	 
	./loop_ver2_runloop.sh ${run[$LOOP]} 
	LOOP=$((LOOP+1))
	sleep 1
  else
      
  ##endif
      echo Wait more $tsleep seconds
      sleep $tsleep
  fi
  
done

