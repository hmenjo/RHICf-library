#/bin/tcsh

#for ((i=2890; i< 2990; i++)) 
#do echo  "$i" >> param1.dat ;
#./sample_eventloop -i $rootdata/run0000"$i".root >> param1.dat
#done


./sample_eventloop -i $rootdata/run00002947.root >> param2947.dat
./sample_eventloop -i $rootdata/run00002954.root >> param2954.dat
./sample_eventloop -i $rootdata/run00002956.root >> param2956.dat
./sample_eventloop -i $rootdata/run00002958.root >> param2958.dat
./sample_eventloop -i $rootdata/run00002964.root >> param2964.dat
./sample_eventloop -i $rootdata/run00002966.root >> param2966.dat
./sample_eventloop -i $rootdata/run00002968.root >> param2968.dat
./sample_eventloop -i $rootdata/run00002970.root >> param2970.dat
./sample_eventloop -i $rootdata/run00002972.root >> param2972.dat
./sample_eventloop -i $rootdata/run00002973.root >> param2973.dat
./sample_eventloop -i $rootdata/run00002979.root >> param2979.dat
./sample_eventloop -i $rootdata/run00002981.root >> param2981.dat
./sample_eventloop -i $rootdata/run00002983.root >> param2983.dat
