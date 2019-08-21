#####################################################################

#-------------------------------------------------------------------

INC_DIR       = ./include
SRC_DIR       = ./src
LIB_DIR       = $(PWD)/lib
#-------------------------------------------------------------------

LIBNAME          = libLHCfEvent
# For EventBuild
LIBEVENT_HLIST  =  LHCfEvent.h 
LIBEVENT_HLISTS =  $(INC_DIR)/LHCfEvent.h
LIBEVENT_LIBS   =  $(SRC_DIR)/LHCfEvent.o
# For Definition
LIBEVENT_HLIST  +=  LHCfDef.h  
LIBEVENT_HLISTS +=  $(INC_DIR)/LHCfDef.h
# ARM1
LIBEVENT_HLIST  +=  A1Raw.h  A1Cal1.h A1Cal2.h A1Cal2M.h A1Phys.h 
LIBEVENT_HLIST  +=  A1Info.h A1Scl.h A1Rec1.h A1Rec2.h
LIBEVENT_HLISTS +=  $(INC_DIR)/A1Raw.h $(INC_DIR)/A1Cal1.h
LIBEVENT_HLISTS +=  $(INC_DIR)/A1Cal2.h $(INC_DIR)/A1Cal2M.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/A1Phys.h
LIBEVENT_HLISTS +=  $(INC_DIR)/A1Info.h $(INC_DIR)/A1Scl.h
LIBEVENT_HLISTS +=  $(INC_DIR)/A1Rec1.h $(INC_DIR)/A1Rec2.h 
LIBEVENT_LIBS   +=  $(SRC_DIR)/A1Raw.o $(SRC_DIR)/A1Cal1.o
LIBEVENT_LIBS   +=  $(SRC_DIR)/A1Cal2.o $(SRC_DIR)/A1Cal2M.o 
LIBEVENT_LIBS   +=  $(SRC_DIR)/A1Phys.o
LIBEVENT_LIBS   +=  $(SRC_DIR)/A1Info.o $(SRC_DIR)/A1Scl.o
LIBEVENT_LIBS   +=  $(SRC_DIR)/A1Rec1.o $(SRC_DIR)/A1Rec2.o
# ARM2
LIBEVENT_HLIST  +=  A2Raw.h  A2Cal1.h A2Cal2.h  A2Cal2M.h A2Phys.h 
LIBEVENT_HLIST  +=  A2Rec1.h A2Rec2.h A2Rec3.h A2Info.h A2Scl.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/A2Raw.h $(INC_DIR)/A2Cal1.h
LIBEVENT_HLISTS +=  $(INC_DIR)/A2Cal2.h $(INC_DIR)/A2Cal2M.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/A2Phys.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/A2Rec1.h $(INC_DIR)/A2Rec2.h
LIBEVENT_HLISTS +=  $(INC_DIR)/A2Rec3.h
LIBEVENT_HLISTS +=  $(INC_DIR)/A2Info.h $(INC_DIR)/A2Scl.h
LIBEVENT_LIBS   +=  $(SRC_DIR)/A2Raw.o $(SRC_DIR)/A2Cal1.o
LIBEVENT_LIBS   +=  $(SRC_DIR)/A2Cal2.o $(SRC_DIR)/A2Cal2M.o 
LIBEVENT_LIBS   +=  $(SRC_DIR)/A2Phys.o 
LIBEVENT_LIBS   +=  $(SRC_DIR)/A2Rec1.o $(SRC_DIR)/A2Rec2.o 
LIBEVENT_LIBS   +=  $(SRC_DIR)/A2Rec3.o 
LIBEVENT_LIBS   +=  $(SRC_DIR)/A2Info.o $(SRC_DIR)/A2Scl.o
# For p-Pb 2013 operation
LIBEVENT_HLIST  +=  A2Raw_pPb2013.h
LIBEVENT_HLISTS +=  $(INC_DIR)/A2Raw_pPb2013.h
LIBEVENT_LIBS   +=  $(SRC_DIR)/A2Raw_pPb2013.o
# For p-p 2015 operation
LIBEVENT_HLIST  +=  A1Raw_pp2015.h  A2Raw_pp2015.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/A1Raw_pp2015.h $(INC_DIR)/A2Raw_pp2015.h 
LIBEVENT_LIBS   +=  $(SRC_DIR)/A1Raw_pp2015.o $(SRC_DIR)/A2Raw_pp2015.o
LIBEVENT_HLIST  +=  A1Scl_pp2015.h A2Scl_pp2015.h
LIBEVENT_HLISTS +=  $(INC_DIR)/A1Scl_pp2015.h $(INC_DIR)/A2Scl_pp2015.h 
LIBEVENT_LIBS   +=  $(SRC_DIR)/A1Scl_pp2015.o $(SRC_DIR)/A2Scl_pp2015.o
# For p-Pb 2016 operation
LIBEVENT_HLIST  +=  A2Raw_pPb2016.h
LIBEVENT_HLISTS +=  $(INC_DIR)/A2Raw_pPb2016.h
LIBEVENT_LIBS   +=  $(SRC_DIR)/A2Raw_pPb2016.o
# For RHICf operation 
LIBEVENT_HLIST  +=  RHICfRaw_Op2017.h  RHICfScl_Op2017.h  
LIBEVENT_HLISTS +=  $(INC_DIR)/RHICfRaw_Op2017.h $(INC_DIR)/RHICfScl_Op2017.h 
LIBEVENT_LIBS   +=  $(SRC_DIR)/RHICfRaw_Op2017.o $(SRC_DIR)/RHICfScl_Op2017.o 
# Common
LIBEVENT_HLIST  +=  RawL1T.h SclL1T.h Rec0.h
LIBEVENT_HLISTS +=  $(INC_DIR)/RawL1T.h  $(INC_DIR)/SclL1T.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/Rec0.h
LIBEVENT_LIBS   +=  $(SRC_DIR)/RawL1T.o  $(SRC_DIR)/SclL1T.o
LIBEVENT_LIBS   +=  $(SRC_DIR)/Rec0.o 
# Graphs
LIBEVENT_HLIST  +=  A1Cal1AccumHist.h A2Cal1AccumHist.h
LIBEVENT_HLIST  +=  A1Cal2AccumHist.h A2Cal2AccumHist.h
LIBEVENT_HLIST  +=  A1PhysAccumHist.h A2PhysAccumHist.h
LIBEVENT_HLIST  +=  A1CountArray.h A2CountArray.h
LIBEVENT_HLIST  +=  A1CalEventHist.h A2CalEventHist.h
LIBEVENT_HLISTS +=  $(INC_DIR)/A1Cal1AccumHist.h $(INC_DIR)/A2Cal1AccumHist.h
LIBEVENT_HLISTS +=  $(INC_DIR)/A1CalEventHist.h $(INC_DIR)/A2CalEventHist.h
LIBEVENT_HLISTS +=  $(INC_DIR)/A1Cal2AccumHist.h $(INC_DIR)/A2Cal2AccumHist.h
LIBEVENT_HLISTS +=  $(INC_DIR)/A1PhysAccumHist.h $(INC_DIR)/A2PhysAccumHist.h
LIBEVENT_HLISTS +=  $(INC_DIR)/A1CountArray.h $(INC_DIR)/A2CountArray.h
LIBEVENT_LIBS   +=  $(SRC_DIR)/A1Cal1AccumHist.o $(SRC_DIR)/A2Cal1AccumHist.o 
LIBEVENT_LIBS   +=  $(SRC_DIR)/A1CalEventHist.o $(SRC_DIR)/A2CalEventHist.o
LIBEVENT_LIBS   +=  $(SRC_DIR)/A1Cal2AccumHist.o $(SRC_DIR)/A2Cal2AccumHist.o
LIBEVENT_LIBS   +=  $(SRC_DIR)/A1PhysAccumHist.o $(SRC_DIR)/A2PhysAccumHist.o
LIBEVENT_LIBS   +=  $(SRC_DIR)/A1CountArray.o $(SRC_DIR)/A2CountArray.o
# For Simulation 
LIBEVENT_HLIST  +=  SimP.h SimIncidents.h
LIBEVENT_HLISTS +=  $(INC_DIR)/SimP.h  $(INC_DIR)/SimIncidents.h
LIBEVENT_LIBS   +=  $(SRC_DIR)/SimP.o  $(SRC_DIR)/SimIncidents.o
# The Others
LIBEVENT_HLIST  +=  GParam.h GParamD64.h
LIBEVENT_HLISTS +=  $(INC_DIR)/GParam.h $(INC_DIR)/GParamD64.h
LIBEVENT_LIBS   +=  $(SRC_DIR)/GParam.o $(SRC_DIR)/GParamD64.o
# For data of beam test
LIBEVENT_HLIST  +=  SPSAdamo.h SPSAdamoRec0.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/SPSAdamo.h $(INC_DIR)/SPSAdamoRec0.h 
LIBEVENT_LIBS   +=  $(SRC_DIR)/SPSAdamo.o $(SRC_DIR)/SPSAdamoRec0.o
LIBEVENT_HLIST  +=  SPSAdamoHist.h 
LIBEVENT_HLISTS +=  $(INC_DIR)/SPSAdamoHist.h 
LIBEVENT_LIBS   +=  $(SRC_DIR)/SPSAdamoHist.o 


#
LIBEVENT_LIBS   +=  $(SRC_DIR)/$(LIBNAME).o 

INCALL += -I$(INC_DIR) 

#------------------------------------------------
#
# Configuration for each architecture
# (Updated for  ROOT version > 5.32)

MAKEARCH        :=      $(shell find $(ROOTSYS)/test -name Makefile.arch)
ifeq ($(MAKEARCH), )
# 41594 or later
MAKEARCH        :=      $(shell find $(ROOTSYS)/etc -name Makefile.arch)
endif

#include $(ROOTSYS)/test/Makefile.arch
include $(MAKEARCH)

# For MAC OS X users 
ifneq (,$(filter $(ARCH),macosx macosx64))
SOFLAGS  += -install_name $(LIB_DIR)/$(LIBNAME).so
endif

#-------------------------------------------------

CXXFLAGS  += $(INCALL)

all: dict

$(SRC_DIR)/%.o	:  $(SRC_DIR)/%.cpp  
	$(CXX) $(CXXFLAGS)  -c $< -o $@

$(SRC_DIR)/%.o	:  $(SRC_DIR)/%.cpp  $(INC_DIR)/%.h
	$(CXX) $(CXXFLAGS)  -c $< -o $@

$(SRC_DIR)/A2Cal2M.o : $(INC_DIR)/A2Cal2.h $(INC_DIR)/Rec0.h

$(SRC_DIR)/A2Rec1.o : $(INC_DIR)/Rec0.h

$(SRC_DIR)/A2Rec2.o : $(INC_DIR)/Rec0.h $(INC_DIR)/A2Rec1.h

$(SRC_DIR)/SimIncidents.o :  $(INC_DIR)/SimP.h

$(INC_DIR)/$(LIBNAME).h : $(LIBEVENT_HLISTS) $(INC_DIR)/LinkDef.h
	rootcint -f $(LIBNAME).cpp -c -I$(INC_DIR) -I$(SRC_DIR) \
	$(LIBEVENT_HLIST) $(INC_DIR)/LinkDef.h
	mv $(LIBNAME).h $(INC_DIR)/
	mv $(LIBNAME).cpp $(SRC_DIR)/

$(SRC_DIR)/$(LIBNAME).o :  $(INC_DIR)/$(LIBNAME).h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/$(LIBNAME).cpp -o $@

$(LIB_DIR)/$(LIBNAME).so : $(LIBEVENT_LIBS)
	$(LD) $(LDFLAGS) $(SOFLAGS) $^ -o $@ $(EXPLLINKLIBS)

dict: 	$(LIB_DIR)/$(LIBNAME).so

$(INC_DIR)/%.h :

clean:
	rm -f $(INC_DIR)/$(LIBNAME).h
	rm -f $(SRC_DIR)/$(LIBNAME).cpp
	rm -f $(LIBEVENT_LIBS)
	rm -f $(LIB_DIR)/$(LIBNAME).so

print:
	echo $(CFLAGS)
	echo $LIBS


