void loop(){
  char hname[255];
  for(int i=250;i<69429;i++){
    k = Form("%07d", i);
    //cout << "./convertor -i /ccj/w/data61/RHICf/DATA1/DATA1/satoken/simdata_510GeVpp/qgs/middle/20190512QGSJET2_" << k << ".root -o /ccj/w/r01/satoken/con_simdata/qgs/middle/CONVERT_20190512_QGSJET2_MIDDLE_" << k << ".root" << endl;   
  }

  for(int i=0;i<36254;i++){
    k = Form("%07d", i);
    //cout << "./convertor -i /ccj/w/data61/RHICf/DATA1/DATA1/satoken/simdata_510GeVpp/qgs/middle/20190516QGSJET2_" << k << ".root -o /ccj/w/r01/satoken/con_simdata/qgs/middle/CONVERT_20190516_QGSJET2_MIDDLE_" << k << ".root" << endl;
  }

  for(int i=0;i<72032;i++){
    k = Form("%06d", i);
    //cout << "./convertor -i /ccj/w/data61/RHICf/DATA1/DATA1/satoken/simdata_510GeVpp/qgs/middle2/20190522QGSJET2_" << k << ".root -o /ccj/w/r01/satoken/con_simdata/qgs/middle2/CONVERT_20190522_QGSJET2_MIDDLE_" << k <<".root" << endl;
  }

  for(int i=72032;i<110000;i++){
    k = Form("%06d", i);
    //cout << "./convertor -i /ccj/w/data61/RHICf/DATA1/DATA1/satoken/simdata_510GeVpp/qgs/middle_20190604/20190604QGSJET2_" << k << ".root -o /ccj/w/r01/satoken/con_simdata/qgs/middle_20190604/CONVERT_20190604_QGSJET2_MIDDLE_" << k <<".root" << endl;
  }

  for(int i=110000;i<156152;i++){
    k = Form("%06d", i);
    cout << "./convertor -i /ccj/w/data61/RHICf/DATA1/DATA1/satoken/simdata_510GeVpp/qgs/middle_20190604/20190604QGSJET2_" << k << ".root -o /ccj/w/r01/satoken/con_simdata/qgs/middle_20190604/CONVERT_20190604_QGSJET2_MIDDLE_" << k <<".root" << endl;
  }
  
  for(int i=0;i<68503;i++){
    k = Form("%06d", i);
    //cout << "./convertor -i /ccj/w/data61/RHICf/DATA1/DATA1/satoken/simdata_510GeVpp/qgs/middle_20190613/20190613QGSJET2_" << k << ".root -o /ccj/w/r01/satoken/con_simdata/qgs/middle_20190613/CONVERT_20190613_QGSJET2_MIDDLE_" << k <<".root" << endl;
  }

  for(int i=0;i<50727;i++){
    k = Form("%06d", i);
    //cout << "./convertor -i /ccj/w/data61/RHICf/DATA1/DATA1/satoken/simdata_copy/qgs/middle_rhicf10fast/20190619_SIMF_QGSJET2_MIDDLE_" << k << ".root -o /ccj/w/r01/satoken/con_simdata/qgs/middle_20190619/CONVERT_20190619_SIMF_QGSJET2_MIDDLE_" << k <<".root" << endl;
  }
  
  for(int i=0;i<50000;i++){
    k = Form("%05d", i);
    //cout << "./convertor -i /ccj/w/data61/RHICf/DATA1/DATA1/suzuki/EPOS_LHC_FULL_TS/run100"<< k << ".root -o /ccj/w/r01/satoken/con_simdata/epos/middle/CONVERT_EPOSLHC_MIDDLE_" << k <<".root" << endl;
  }



}
