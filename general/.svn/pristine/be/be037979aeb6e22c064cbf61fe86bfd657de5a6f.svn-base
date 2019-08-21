##############################################
#     SET SLOWCONTROL LIBRARY VERSION
# sc_op2010_05 : most of period of operation in 2010
# sc_op2013_01 : for Operation of p-Pb in 2013
# sc_op2015_02 : for Operation of pp in 2015
SCDIR=sc_old/sc_op2015_02/
##############################################

.PHONY: dict sc func 

all:    dict sc func

dict:
	#make -C ./dict
	cd ./dict;  make 
sc:
	rm -rf sc;
	ln -s $(SCDIR) sc; 
	#make -C ./sc
	cd ./sc;  make

func:
	#make -C ./func
	cd ./func;  make;


clean:
	make -C ./dict     clean
	make -C ./sc       clean
	make -C ./func     clean



