
#TChain* tevent=new TChain("EventInfo","");
#  for(int ifile=first; ifile<=last; ifile++) {
#    if(ifile<20040000){
#      fs::path afile("171105QGSJET2_TS"+boost::lexical_cast<string>(ifile)+".root");
#      string fname=(fs::absolute(indir) / afile).string();
#      //cout <<"afile" << " " << afile << endl;
#     tevent->Add(fname.c_str());
#      }
#     else if(20039999<ifile && ifile <20050000){
#        fs::path afile("171111QGSJET2_TS"+boost::lexical_cast<string>(ifile)+".root");
#        string fname=(fs::absolute(indir) / afile).string();
#        tevent->Add(fname.c_str());
#     }
#      else if(20049999<ifile){
#      fs::path afile("171118QGSJET2_TS"+boost::lexical_cast<string>(ifile)+".root");
#      string fname=(fs::absolute(indir) / afile).string();
#      tevent->Add(fname.c_str());
#     }
