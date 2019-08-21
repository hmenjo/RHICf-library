#!/bin/sh

maxjobs=220
maxmyjobs=30
LOOP=0
NLOOP=75
while [ $LOOP -lt $NLOOP ]
do  
  njobs=`qstat |wc -l`
  nmyjobs=`qstat -au sato.kenta| wc -l`
  ##echo ${njobs}
	
  if [ $njobs -lt $maxjobs ] ; then
    if [ $nmyjobs -lt $maxmyjobs ] ; then
      if [ $LOOP -eq 0 ]; then 
	RUN=2625
        qsub ./qsub_rec.sh -v RUN=2625   
      elif [ $LOOP -eq 1 ]; then
	RUN=2627
	qsub ./qsub_rec.sh -v RUN=2627
      elif [ $LOOP -eq 2 ]; then
	RUN=2630
	qsub ./qsub_rec.sh -v RUN=2630
      elif [ $LOOP -eq 3 ]; then
	RUN=2631
	qsub ./qsub_rec.sh -v RUN=2631
      elif [ $LOOP -eq 4 ]; then
	RUN=2632
        qsub ./qsub_rec.sh -v RUN=2632
      elif [ $LOOP -eq 5 ]; then
	RUN=2633
	qsub ./qsub_rec.sh -v RUN=2633
      elif [ $LOOP -eq 6 ]; then
	RUN=2634
	qsub ./qsub_rec.sh -v RUN=2634
      elif [ $LOOP -eq 7 ]; then
	RUN=2636
	qsub ./qsub_rec.sh -v RUN=2636
      elif [ $LOOP -eq 8 ]; then
	RUN=2637
	qsub ./qsub_rec.sh -v RUN=2637
	elif [ $LOOP -eq 9 ]; then
	RUN=2641
	qsub ./qsub_rec.sh -v RUN=2641
	elif [ $LOOP -eq 10 ]; then
	RUN=2644
	qsub ./qsub_rec.sh -v RUN=2644
	elif [ $LOOP -eq 11 ]; then
	RUN=2718
	qsub ./qsub_rec.sh -v RUN=2718
	elif [ $LOOP -eq 12 ]; then
	RUN=2721
	qsub ./qsub_rec.sh -v RUN=2721
	elif [ $LOOP -eq 13 ]; then
	RUN=2726
	qsub ./qsub_rec.sh -v RUN=2726
	elif [ $LOOP -eq 14 ]; then
	RUN=2730
	qsub ./qsub_rec.sh -v RUN=2730
	elif [ $LOOP -eq 15 ]; then
	RUN=2732
	qsub ./qsub_rec.sh -v RUN=2732
	elif [ $LOOP -eq 16 ]; then
	RUN=2734
	qsub ./qsub_rec.sh -v RUN=2734
	elif [ $LOOP -eq 17 ]; then
	RUN=2736
	qsub ./qsub_rec.sh -v RUN=2736
	elif [ $LOOP -eq 18 ]; then
	RUN=2738
	qsub ./qsub_rec.sh -v RUN=2738
	elif [ $LOOP -eq 19 ]; then
	RUN=2740
	qsub ./qsub_rec.sh -v RUN=2740
	elif [ $LOOP -eq 20 ]; then
	RUN=2798
	qsub ./qsub_rec.sh -v RUN=2798
	elif [ $LOOP -eq 21 ]; then
	RUN=2801
	qsub ./qsub_rec.sh -v RUN=2801
	elif [ $LOOP -eq 22 ]; then
	RUN=2803
	qsub ./qsub_rec.sh -v RUN=2803
	elif [ $LOOP -eq 23 ]; then
	RUN=2810
	qsub ./qsub_rec.sh -v RUN=2810
	elif [ $LOOP -eq 24 ]; then
	RUN=2812
	qsub ./qsub_rec.sh -v RUN=2812
	elif [ $LOOP -eq 25 ]; then
	RUN=2814
	qsub ./qsub_rec.sh -v RUN=2814
	elif [ $LOOP -eq 26 ]; then
	RUN=2818
	qsub ./qsub_rec.sh -v RUN=2818
	elif [ $LOOP -eq 27 ]; then
	RUN=2819
	qsub ./qsub_rec.sh -v RUN=2819
	elif [ $LOOP -eq 28 ]; then
	RUN=2823
	qsub ./qsub_rec.sh -v RUN=2823
	elif [ $LOOP -eq 29 ]; then
	RUN=2824
	qsub ./qsub_rec.sh -v RUN=2824
	elif [ $LOOP -eq 30 ]; then
	RUN=2827
	qsub ./qsub_rec.sh -v RUN=2827
	elif [ $LOOP -eq 31 ]; then
	RUN=2845
	qsub ./qsub_rec.sh -v RUN=2845
	elif [ $LOOP -eq 32 ]; then
	RUN=2847
	qsub ./qsub_rec.sh -v RUN=2847
	elif [ $LOOP -eq 33 ]; then
	RUN=2850
	qsub ./qsub_rec.sh -v RUN=2850
	elif [ $LOOP -eq 34 ]; then
	RUN=2852
	qsub ./qsub_rec.sh -v RUN=2852
	elif [ $LOOP -eq 35 ]; then
	RUN=2854
	qsub ./qsub_rec.sh -v RUN=2854
	elif [ $LOOP -eq 36 ]; then
	RUN=2857
	qsub ./qsub_rec.sh -v RUN=2857
	elif [ $LOOP -eq 37 ]; then
	RUN=2864
	qsub ./qsub_rec.sh -v RUN=2864
	elif [ $LOOP -eq 38 ]; then
	RUN=2867
	qsub ./qsub_rec.sh -v RUN=2867
	elif [ $LOOP -eq 39 ]; then
	RUN=2868
	qsub ./qsub_rec.sh -v RUN=2868
	elif [ $LOOP -eq 40 ]; then
	RUN=2877
	qsub ./qsub_rec.sh -v RUN=2877
	elif [ $LOOP -eq 41 ]; then
	RUN=2878
	qsub ./qsub_rec.sh -v RUN=2878
	elif [ $LOOP -eq 42 ]; then
	RUN=2881
	qsub ./qsub_rec.sh -v RUN=2881
	elif [ $LOOP -eq 43 ]; then
	RUN=2883
	qsub ./qsub_rec.sh -v RUN=2883
	elif [ $LOOP -eq 44 ]; then
	RUN=2887
	qsub ./qsub_rec.sh -v RUN=2887
	elif [ $LOOP -eq 45 ]; then
	RUN=2889
	qsub ./qsub_rec.sh -v RUN=2889
	elif [ $LOOP -eq 46 ]; then
	RUN=2892
	qsub ./qsub_rec.sh -v RUN=2892
	elif [ $LOOP -eq 47 ]; then
	RUN=2896
	qsub ./qsub_rec.sh -v RUN=2896
	elif [ $LOOP -eq 48 ]; then
	RUN=2899
	qsub ./qsub_rec.sh -v RUN=2899
	elif [ $LOOP -eq 49 ]; then
	RUN=2902
	qsub ./qsub_rec.sh -v RUN=2902
	elif [ $LOOP -eq 50 ]; then
	RUN=2903
	qsub ./qsub_rec.sh -v RUN=2903
	elif [ $LOOP -eq 51 ]; then
	RUN=2904
	qsub ./qsub_rec.sh -v RUN=2904
	elif [ $LOOP -eq 52 ]; then
	RUN=2905
	qsub ./qsub_rec.sh -v RUN=2905
	elif [ $LOOP -eq 53 ]; then
	RUN=2923
	qsub ./qsub_rec.sh -v RUN=2923
	elif [ $LOOP -eq 54 ]; then
	RUN=2924
	qsub ./qsub_rec.sh -v RUN=2924
	elif [ $LOOP -eq 55 ]; then
	RUN=2925
	qsub ./qsub_rec.sh -v RUN=2925
	elif [ $LOOP -eq 56 ]; then
	RUN=2932
	qsub ./qsub_rec.sh -v RUN=2932
	elif [ $LOOP -eq 57 ]; then
	RUN=2933
	qsub ./qsub_rec.sh -v RUN=2933
	elif [ $LOOP -eq 58 ]; then
	RUN=2937
	qsub ./qsub_rec.sh -v RUN=2937
	elif [ $LOOP -eq 59 ]; then
	RUN=2939
	qsub ./qsub_rec.sh -v RUN=2939
	elif [ $LOOP -eq 60 ]; then
	RUN=2947
	qsub ./qsub_rec.sh -v RUN=2947
	elif [ $LOOP -eq 61 ]; then
	RUN=2954
	qsub ./qsub_rec.sh -v RUN=2954
	elif [ $LOOP -eq 62 ]; then
	RUN=2956
	qsub ./qsub_rec.sh -v RUN=2956
	elif [ $LOOP -eq 63 ]; then
	RUN=2958
	qsub ./qsub_rec.sh -v RUN=2958
	elif [ $LOOP -eq 64 ]; then
	RUN=2960
	qsub ./qsub_rec.sh -v RUN=2960
	elif [ $LOOP -eq 65 ]; then
	RUN=2964
	qsub ./qsub_rec.sh -v RUN=2964
	elif [ $LOOP -eq 66 ]; then
	RUN=2966
	qsub ./qsub_rec.sh -v RUN=2966
	elif [ $LOOP -eq 67 ]; then
	RUN=2968
	qsub ./qsub_rec.sh -v RUN=2968
	elif [ $LOOP -eq 68 ]; then
	RUN=2970
	qsub ./qsub_rec.sh -v RUN=2970
	elif [ $LOOP -eq 69 ]; then
	RUN=2972
	qsub ./qsub_rec.sh -v RUN=2972
	elif [ $LOOP -eq 70 ]; then
	RUN=2973
	qsub ./qsub_rec.sh -v RUN=2973
	elif [ $LOOP -eq 71 ]; then
	RUN=2979
	qsub ./qsub_rec.sh -v RUN=2979
	elif [ $LOOP -eq 72 ]; then
	RUN=2981
	qsub ./qsub_rec.sh -v RUN=2981
	elif [ $LOOP -eq 73 ]; then
	RUN=2983
  	qsub ./qsub_rec.sh -v RUN=2983	
   fi
    LOOP=$((LOOP+1)) 	
    sleep 1
    
  fi
  else
      
  ##endif
      echo Wait more $tsleep seconds
      sleep $tsleep
  fi
  
done

