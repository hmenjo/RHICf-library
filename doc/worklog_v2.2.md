# Memo and Log
This is for development to v2.1

## Log
- 2021/06/03 Menjo
  - in Reconstruction/src/A1Calibration.cpp  
    - Update the ADC range file; adcrange_002_100412.dat -> adcrange_003_20151120.dat
    - Update cable attenuation factor : 0.908 -> 1.00 **Big impact on energy scale** 
  - in Reconstruction/src/A1Reconstruction.cpp 
    - Modify A1Reconstruction::ReconstructEnergy() to avoid unphysical outputs  
      Clear the position dependent correction in each step to avoid multiple corrections. Added ```fCal->copydata(fCalOrg, A1Cal2::CAL);```. 
    - Modify A1Reconstruction::ReconstructEnergyPhotonDouble  
      In deep layers, the shower leak in and out parameters seems to be unrealistic (> 1). In layer >=11, shower leak out parameter use the one of layer = 10. In layer >=9, leak-in parameter use the one of layer = 8. 
  - Energy rescaling implemeted in reconstruction02.cpp 
    - Overall rescale factor from pi0 analysis, fixed by Minho 
    - Layer-by-layer factor from dE comparisons, fixed by Menjo (not final) 
- 2021/06/04
  - Change L90% caliculation algorithm from ParticleID01 to ParticleID02. 
  - git tag dev_menjo_20210604

- 2021/06/06
  - Fixed bugs of reconstruction02.cpp (energy rescale functions)
 


