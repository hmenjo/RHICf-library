void loop2(){
  char hname[255];
  string k;
  for(int i=0;i<20000;i++){
    k = Form("%06d", i);
    if(i<10000) cout << "./convertor -i /ccj/w/data61/RHICf/DATA1/DATA1/satoken/simdata_510GeVpp/qgs/middle_20190705/dir1/20190705_SIMF_QGSJET2_MIDDLE_" << k << ".root -o /ccj/w/r01/satoken/con_simdata/qgs/middle/CONVERT_20190705_SIMF_QGSJET2_MIDDLE" << k << ".root" << endl;   
    else if(10000 <= i && i<20000) cout << "./convertor -i /ccj/w/data61/RHICf/DATA1/DATA1/satoken/simdata_510GeVpp/qgs/middle_20190705/dir2/20190705_SIMF_QGSJET2_MIDDLE_" << k << ".root -o /ccj/w/r01/satoken/con_simdata/qgs/middle/CONVERT_20190705_SIMF_QGSJET2_MIDDLE" << k << ".root" << endl;

  }
}
