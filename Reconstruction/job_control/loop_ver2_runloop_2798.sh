#!/bin/sh

maxjobs=220
maxmyjobs=20
LOOP=963
NLOOP=0

nevent[2625]=1262
nevent[2627]=949
nevent[2630]=311
nevent[2631]=840
nevent[2632]=821
nevent[2633]=808
nevent[2634]=814
nevent[2636]=840
nevent[2637]=816
nevent[2641]=815
nevent[2644]=551
nevent[2718]=939
nevent[2721]=733
nevent[2726]=791
nevent[2730]=1909
nevent[2732]=1833
nevent[2734]=1831
nevent[2736]=1829
nevent[2738]=1777
nevent[2740]=1181
nevent[2798]=1537
nevent[2801]=1655
nevent[2803]=1275
nevent[2810]=531
nevent[2812]=964
nevent[2814]=852
nevent[2818]=1589
nevent[2819]=1630
nevent[2823]=785
nevent[2824]=1572
nevent[2827]=1536
nevent[2845]=1762
nevent[2847]=1701
nevent[2850]=1647
nevent[2852]=1615
nevent[2854]=727
nevent[2857]=1569
nevent[2864]=1739
nevent[2867]=1067
nevent[2868]=1734
nevent[2877]=370
nevent[2878]=1659
nevent[2881]=1647
nevent[2883]=1217
nevent[2887]=1586
nevent[2889]=1568
nevent[2892]=892
nevent[2896]=1551
nevent[2899]=1597
nevent[2902]=184
nevent[2903]=1560
nevent[2904]=181
nevent[2905]=1578
nevent[2923]=311
nevent[2924]=1390
nevent[2925]=501
nevent[2932]=1787
nevent[2933]=1738
nevent[2937]=1696
nevent[2939]=1745
nevent[2947]=1791
nevent[2954]=1745
nevent[2956]=1732
nevent[2958]=1432
nevent[2960]=584
nevent[2964]=847
nevent[2966]=1677
nevent[2968]=1664
nevent[2970]=1270
nevent[2972]=819
nevent[2973]=900
nevent[2979]=1874
nevent[2981]=1860
nevent[2983]=1508	
#echo "${run[@]}"
tsleep=120
run=$1
echo "${run}"
NLOOP=${nevent[${run}]}
echo "${NLOOP}"
while [ $LOOP -lt $NLOOP ]
do  
  njobs=`qstat |wc -l`
  nmyjobs=`qstat -au sato.kenta| wc -l`
  ##echo ${njobs}
	
  if [ $njobs -lt $maxjobs ] && [ $nmyjobs -lt $maxmyjobs ] ; then 
	start=$((LOOP*1000))
	end=$((LOOP*1000+1000))
	echo "RUN=${run}, START=${start}, END=${end}"
	
	cd /mnt/lhcfs2/data1/sato.kenta/workspace/RHICf/Analysis/RHIC/Reconstruction/job_control
  	qsub ./qsub_rec.sh -v RUN=${run},START=${start},END=${end}
	LOOP=$((LOOP+1))
	sleep 1
  else
      
  ##endif
      echo Wait more $tsleep seconds
      sleep $tsleep
  fi
  
done

