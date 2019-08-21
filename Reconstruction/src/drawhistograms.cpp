//
// Created by MENJO Hiroaki on 2017/05/26.
//

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include <TROOT.h>
#include <TApplication.h>
#include <TRint.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF2.h>
#include <TGraph2D.h>
#include <TFile.h>
#include <TStyle.h>
#include <TString.h>
#include <TMath.h>
#include <TDiamond.h>
#include <TLegend.h>

void DrawCalorimeterShape() {
  double   s2  = TMath::Sqrt(2.);
  TDiamond *ts = new TDiamond(-20. / s2, -20. / s2, 20. / s2, 20. / s2);
  TDiamond *tl = new TDiamond(-40. / s2, 20. / s2 + 5., 40. / s2, 100. / s2 + 5);
  ts->SetFillStyle(0);
  tl->SetFillStyle(0);
  ts->SetLineWidth(1);
  tl->SetLineWidth(1);
  ts->SetBorderSize(0);
  tl->SetBorderSize(0);
  ts->Draw();
  tl->Draw();
}

TGraph2D* ConvertCoord(const TH2D *histo){

  int npoint = 0;
  for(int i=1;i<=histo->GetXaxis()->GetNbins();i++){
    for(int j=1;j<=histo->GetYaxis()->GetNbins();j++){
      const double cont=histo->GetBinContent(i, j);
      if(cont>0.)
        npoint++;
    }
  }

  TGraph2D *graph = new TGraph2D(npoint);

  int ipoint=0;
  for(int i=1;i<=histo->GetXaxis()->GetNbins();i++){
    for(int j=1;j<=histo->GetYaxis()->GetNbins();j++){
      const double x=histo->GetXaxis()->GetBinCenter(i);
      const double y=histo->GetYaxis()->GetBinCenter(j);
      const double cont=histo->GetBinContent(i, j);
      if(cont>0.) {
        graph->SetPoint(ipoint, x, y, cont);
        ++ipoint;
      }
    }
  }

  return graph;
}

void CalcInitValues(const TH2D *histo, double &meanx, double &meany){
  int binx, biny, binz;
  histo->GetBinXYZ(histo->GetMaximumBin(), binx, biny, binz);
  meanx=histo->GetXaxis()->GetBinCenter(binx);
  meany=histo->GetYaxis()->GetBinCenter(biny);  

  //  double sumx=0,sumy=0;
  //  //  for(int biny=17;biny<23;biny++){
  //  //    sumx += histo->ProjectionX("",biny,biny)->GetMean();
  //  //  }
  //  //  for(int binx=22;binx<28;binx++){
  //  //    sumy += histo->GetYaxis()->GetBinCenter(histo->ProjectionY("",binx,binx)->GetMaximumBin());
  //  //  }
  //  //  double meanx = sumx/6.;
  //  //  double meany = sumy/6.;
  //  //  double sigmax = histo->GetRMS(1);
  //  //  double sigmay = histo->GetRMS(2);
  //  //  double covar = histo->GetCorrelationFactor();
}

TF2 *CalcBeamPos(TH2D *histo, const char *name){

  TGraph2D* graph_pos;
  graph_pos = (TGraph2D*) ConvertCoord(histo);

  graph_pos->SetName(Form("graph_%s", name));

  /*
     TCanvas *cc=new TCanvas("cc", "cc");
     cc->cd();
     graph_pos->Draw("COLZ");
     */

  double meanx, meany;
  CalcInitValues(histo, meanx, meany);

  // --- for new func ---
  TF2 *g2D = new TF2(Form("function_%s", name),"[0]*exp(-((x-[1])^2+(y-[3])^2)/(2*[2]*[2]))+[4]",-30.0,30.0,-20,80);
  g2D->SetParNames("Amp","Xpeak","sigma","Ypeak","const");

  cout << "Initial values are [" << meanx << ", " << meany << "]" << endl;

  g2D->SetParameters( 10 , meanx, 5.0, meany, 100 );
  //g2D->SetParLimits(0,  0,   10000);
  g2D->SetParLimits(1, -10, 10);
  g2D->SetParLimits(2,  0, 100);
  g2D->SetParLimits(3, -10, 70);
  g2D->SetParLimits(4,  0, 100000);

  graph_pos->Fit(g2D,"R0");

  cerr << "chi^2/ndf: " << g2D->GetChisquare() << " / " << g2D->GetNDF() << endl;
  double red_chi2 = g2D->GetChisquare()/g2D->GetNDF();

  if( 0.1 < red_chi2 && red_chi2 < 100.0 )
    cout << "Warning : reduced chi^2 is " << red_chi2 << endl;
  cout << "Beam Position is [" << g2D->GetParameter(1) << ", " << g2D->GetParameter(3) << "]" << endl;

  return g2D;
}

void SetStyle(TF2* g2D){

  //gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  gStyle->SetPalette(1);

  g2D->SetLineStyle(1);
  g2D->SetLineWidth(1);
  g2D->SetContour(8);
}

// ---------------------------------------------------------------------
//                                  MAIN
// ---------------------------------------------------------------------
int main(int argc, char **argv) {

  TString inputfilename = "";
  TString outputpath    = "./";

  for (int i = 1; i < argc; i++) {
    string ss = argv[i];

    if (ss == "-i" || ss == "--input") {
      inputfilename = argv[++i];
      strcpy(argv[i], "");
    }
    if (ss == "--path") {
      outputpath = argv[++i];
      strcpy(argv[i], "");
    }
  }

  TRint theApp("App", &argc, argv, 0, 0, kTRUE);

  TFile *file = new TFile(inputfilename);
  if (file->IsZombie()) {
    cerr << "Could not open " << inputfilename << endl;
    return -1;
  }

  file->ls();

  // Draw Spectra -----------------------------------------------------------------------
  TString title[5] = {"All", "Shower", "Spe1(Pi0)", "Spe2(HighEM)", "Pedestal"};
  Color_t color[5] = {kBlack, kBlue, kGreen + 2, kRed, kMagenta};

  TCanvas *c0 = new TCanvas("c0", "Spectrum", 1000, 1000);
  c0->Divide(2, 2, 0.001, 0.001);
  for (int tower = 0; tower < 2; ++tower) {
    for (int pid = 0; pid < 2; ++pid) {
      c0->cd(tower + pid * 2 + 1);
      gPad->SetLogy();

      TH1D     *h[5];
      for (int i = 0; i < 5; ++i) {
        h[i] = (TH1D *) file->Get(Form("h1_spectrum_%d_%d_%d", i, tower, pid));
        h[i]->SetTitle(title[i]);
        h[i]->SetLineColor(color[i]);
        h[i]->SetXTitle("Energy");
        h[i]->SetYTitle("#event/bin");
      }

      h[0]->Draw("hist");
      h[1]->Draw("same,hist");
      h[2]->Draw("same,hist");
      h[3]->Draw("same,hist");
      h[4]->Draw("same,hist");

      TH1D *hframe = h[0];

      if (tower == 0 && pid == 0) hframe->SetTitle("Spectrum: TS,Photon");
      if (tower == 1 && pid == 0) hframe->SetTitle("Spectrum: TL,Photon");
      if (tower == 0 && pid == 1) hframe->SetTitle("Spectrum: TS,Hadron");
      if (tower == 1 && pid == 1) hframe->SetTitle("Spectrum: TL,Hadron");
      if (pid == 0) hframe->GetXaxis()->SetRangeUser(0, 260);
      else hframe->GetXaxis()->SetRangeUser(0, 500);
      //if (pid == 0) hframe->GetXaxis()->SetRangeUser(0, 2000);
      //else hframe->GetXaxis()->SetRangeUser(0, 2000);
      
      if (pid == 0) hframe->GetYaxis()->SetRangeUser(3, 20000);
      else hframe->GetYaxis()->SetRangeUser(1, 6000);
      TLegend *legend = new TLegend(0.75,0.50,0.98,0.75);
      legend->AddEntry(h[0],"ALL");
      legend->AddEntry(h[1],"Shower");
      legend->AddEntry(h[2],"Special1(Type1 Pi0)");
      legend->AddEntry(h[3],"Special2(High EM)");
      legend->AddEntry(h[4],"Pedestal(Zero Bias)");
      legend->SetFillColor(kWhite);
      legend->SetBorderSize(1);
      legend->Draw();
    }
  }
  c0->Update();
  c0->Print(outputpath + Form("/energyspectra.gif"));

  //Hit map------------------------------------------------------------------------------
  TCanvas *c1 = new TCanvas("c1", "hitmap1", 1200, 700);
  c1->Divide(2, 1, 0.001, 0.001);
  for (int pid = 0; pid < 2; ++pid) {
    c1->cd(pid + 1);

    TH2D *h2 = (TH2D *) file->Get(Form("h2_hitmapall_%d_%d", 1, pid)); // Shower Trigger
    h2->Draw("COLZ");

    TH2D *hframe = h2;
    if (pid == 0) hframe->SetTitle("Shower Trg:Photon (>10GeV)");
    if (pid == 1) hframe->SetTitle("Shower Trg:Hadron (>200GeV)");
    hframe->SetXTitle("X [mm]");
    hframe->SetYTitle("Y [mm]");

    // Calculation for Beam Center
    if(h2->GetEntries()>0.) 
    {
      cout << "Compute beam center from " << (pid==0? " Photon" : "Hadron") << endl;
      TGraph2D* graph_pos;
      graph_pos = (TGraph2D*) ConvertCoord(h2);
      graph_pos->SetName(Form("graph_%s", pid==0? "Photon" : "Hadron"));
      double meanx, meany;
      CalcInitValues(h2, meanx, meany);
      // --- for new func ---
      TF2 *g2D = new TF2(Form("function_%s", pid==0? "Photon" : "Hadron"),"[0]*exp(-((x-[1])^2+(y-[3])^2)/(2*[2]*[2]))+[4]",-30.0,30.0,-20,80);
      g2D->SetParNames("Amp","Xpeak","sigma","Ypeak","const");
      cout << "Initial values are [" << meanx << ", " << meany << "]" << endl;
      g2D->SetParameters( 10 , meanx, 5.0, meany, 100 );
      //g2D->SetParLimits(0,  0,   10000);
      g2D->SetParLimits(1, -10, 10);
      g2D->SetParLimits(2,  0, 100);
      g2D->SetParLimits(3, -10, 70);
      g2D->SetParLimits(4,  0, 100000);
      graph_pos->Fit(g2D,"R0");
      cerr << "chi^2/ndf: " << g2D->GetChisquare() << " / " << g2D->GetNDF() << endl;
      double red_chi2 = g2D->GetChisquare()/g2D->GetNDF();
      g2D->Draw("same");
      SetStyle(g2D);
      TPaveText *pt = new TPaveText(0.7,0.7,0.9,0.9,"brNDC");
      pt->SetFillColor(18);
      pt->SetTextAlign(12);
      pt->AddText("Beam Center:");
      TString tmpstring;
      tmpstring = Form("%s %f+/-%f","X[mm]:",g2D->GetParameter(1), g2D->GetParError(1));
      pt->AddText(tmpstring);
      tmpstring = Form("%s %f+/-%f","Y[mm]:",g2D->GetParameter(3), g2D->GetParError(3));
      pt->AddText(tmpstring);
      pt->Draw();
    }
    DrawCalorimeterShape();
    gPad->Update();
  }
  c1->Update();
  c1->Print(outputpath + Form("/hitmap1.gif"));

  //Hit map2------------------------------------------------------------------------------
  TCanvas *c2 = new TCanvas("c2", "hitmap2", 1200, 900);
  c2->Divide(3, 2, 0.001, 0.001);
  for (int trg = 1; trg <= 3; ++trg) {
    for (int pid = 0; pid < 2; ++pid) {
      c2->cd(pid * 3 + (trg - 1) + 1);

      TH2D *h2 = (TH2D *) file->Get(Form("h2_hitmapall_%d_%d", trg, pid)); // Shower Trigger
      h2->Draw("COLZ");

      TH2D    *hframe = h2;
      TString tmp     = "";
      if (trg == 1) tmp += "Shower Trg:";
      if (trg == 2) tmp += "Spe1(Pi0):";
      if (trg == 3) tmp += "Spe2(HighEM):";
      if (pid == 0) tmp += " Photon (>10GeV)";
      if (pid == 1) tmp += " Hadron (>200GeV)";
      hframe->SetTitle(tmp);
      hframe->SetXTitle("X [mm]");
      hframe->SetYTitle("Y [mm]");

      DrawCalorimeterShape();
      gPad->Update();
    }
  }
  c2->Update();
  c2->Print(outputpath + Form("/hitmap2.gif"));

  // Hit Projection -------------------------------------------------------------
  TCanvas *c5 = new TCanvas("c5", "hithists_em", 1200, 800); 
  c5->Divide(3, 2, 0.001, 0.001);
  TCanvas *c6 = new TCanvas("c6", "hithists_had", 1200, 800); 
  c6->Divide(3, 2, 0.001, 0.001); 
  for(int tower=0;tower<2;tower++){
    for (int pid = 0; pid < 2; ++pid) {

      int trg = 1;
      TH2D *h2 = (TH2D *) file->Get(Form("h2_hitmap_%d_%d_%d", trg, tower, pid))->Clone(); // Shower Trigger
      h2->Rebin2D(2,2);
      TH1D *h1_projx = (TH1D*) h2->ProjectionX(Form("h1_projx_%d_%d_%d",trg,tower,pid));
      TH1D *h1_projy = (TH1D*) h2->ProjectionY(Form("h1_projy_%d_%d_%d",trg,tower,pid));

      TCanvas *c;
      if(tower==0)
        c = c5; 
      else
        c = c6;

      c->cd(3*pid + 1);
      gPad->SetGrid();
      gPad->SetLeftMargin(0.15);
      gPad->SetBottomMargin(0.15);
      h2->Draw("COLZ");
      h2->SetXTitle("X[mm]");
      h2->SetYTitle("Y[mm]");
      h2->GetXaxis()->SetTitleSize(0.06);
      h2->GetYaxis()->SetTitleSize(0.06);
      h2->GetYaxis()->SetTitleOffset(0.85);
      h2->GetXaxis()->SetLabelSize(0.05);
      h2->GetYaxis()->SetLabelSize(0.05);

      c->cd(3*pid + 2);
      gPad->SetGrid();
      gPad->SetLeftMargin(0.15);
      gPad->SetBottomMargin(0.15);
      h1_projx->Draw("hist");	
      h1_projx->SetTitle(Form("Proj.Y: %s %s",(tower==0?"TS":"TL"),(pid==0?"EM":"HAD")));
      h1_projx->SetXTitle("Y [mm]");
      h1_projx->SetYTitle("#Events (Shower Trg.)");
      h1_projx->GetXaxis()->SetTitleSize(0.06);
      h1_projx->GetYaxis()->SetTitleSize(0.06);
      h1_projx->GetYaxis()->SetTitleOffset(0.85);
      h1_projx->GetXaxis()->SetLabelSize(0.05);
      h1_projx->GetYaxis()->SetLabelSize(0.05);

      c->cd(3*pid + 3);
      gPad->SetGrid();
      gPad->SetLeftMargin(0.15);
      gPad->SetBottomMargin(0.15);
      h1_projy->Draw("hist");
      h1_projy->SetTitle(Form("Proj.Y: %s %s",(tower==0?"TS":"TL"),(pid==0?"EM":"HAD")));
      h1_projy->SetXTitle("Y [mm]");
      h1_projy->SetYTitle("#Events (Shower Trg.)");
      h1_projy->GetXaxis()->SetTitleSize(0.06);
      h1_projy->GetYaxis()->SetTitleSize(0.06);
      h1_projy->GetYaxis()->SetTitleOffset(0.85);
      h1_projy->GetXaxis()->SetLabelSize(0.05);
      h1_projy->GetYaxis()->SetLabelSize(0.05);
    }
  }

  c5->Update();
  c5->Print(outputpath + Form("/hitproj_shower_photon.gif")); 
  c6->Update();
  c6->Print(outputpath + Form("/hitproj_shower_neutron.gif")); 


  // Pi0 -------------------------------------------------------------------------
  TCanvas *c3 = new TCanvas("c3", "pi0", 900, 500);
  c3->Divide(2, 1, 0.001, 0.001);
  c3->cd(1);
  TH1D *hmass[3];
  TH1D *hpi0spe[3];
  for (int trg = 0; trg < 3; ++trg) {
    hmass[trg]   = (TH1D *) file->Get(Form("h1_mgg_%d", trg));
    hpi0spe[trg] = (TH1D *) file->Get(Form("h1_pi0spectrum_%d", trg));
    hmass[trg]->SetLineColor(color[trg]);
    hmass[trg]->Rebin(4);
  }

  hmass[0]->Draw("hist");
  hmass[1]->Draw("hist,same");
  hmass[2]->Draw("hist,same");

  hmass[0]->SetTitle("M_{gg}");
  hmass[0]->SetXTitle("M_{gg} [MeV]");
  hmass[0]->SetYTitle("Events");

  TLegend *legend_pi0 = new TLegend(0.7,0.5,0.97,0.7);
  legend_pi0->AddEntry(hmass[0],"All","L");
  legend_pi0->AddEntry(hmass[1],"Shower","L");
  legend_pi0->AddEntry(hmass[2],"Spe1(Pi0)","L");
  legend_pi0->SetFillColor(kWhite);
  legend_pi0->SetBorderSize(1);
  legend_pi0->Draw();

  c3->cd(2);
  gPad->SetLogy();
  hpi0spe[0]->Draw("hist");
  hpi0spe[1]->Draw("hist,same");
  hpi0spe[2]->Draw("hist,same");

  hpi0spe[0]->SetTitle("Pi0 Energy Spectrum");
  hpi0spe[0]->SetXTitle("Pi0 Energy [GeV]");
  hpi0spe[0]->SetYTitle("Events");

  c3->Update();
  c3->Print(outputpath + Form("/pi0.gif"));

  // PID ------------------------------------------------------------------------
  TCanvas *c4 = new TCanvas("c4", "PID", 1000, 1000);
  c4->Divide(2, 2, 0.001, 0.001);
  for (int tower = 0; tower < 2; ++tower) {
    for (int pid = 0; pid < 2; ++pid) {
      c4->cd(tower + pid * 2 + 1);

      TH1D     *h[5];
      for (int i = 0; i < 5; ++i) {
        h[i] = (TH1D *) file->Get(Form("h1_pid_%d_%d_%d", i, tower, pid));
        h[i]->SetTitle(title[i]);
        h[i]->SetLineColor(color[i]);
        h[i]->SetXTitle((pid==0?"L90%":"L20%"));
        h[i]->SetYTitle("#event/bin");
      }

      h[0]->Draw("hist");
      h[1]->Draw("same,hist");
      h[2]->Draw("same,hist");
      h[3]->Draw("same,hist");
      h[4]->Draw("same,hist");

      TH1D *hframe = h[0];

      if (tower == 0 && pid == 0) hframe->SetTitle("TS: L90%");
      if (tower == 1 && pid == 0) hframe->SetTitle("TL: L90%");
      if (tower == 0 && pid == 1) hframe->SetTitle("TS: L20%");
      if (tower == 1 && pid == 1) hframe->SetTitle("TL: L20%");
      hframe->GetXaxis()->SetRangeUser(0, 45);
    }
  }
  c4->Update();
  c4->Print(outputpath + Form("/pid.gif"));

  // Trigger Efficiency ------------------------------------------------------
  // Special1 (Pi0) 
  TCanvas *c7 = new TCanvas("c7", "Trg.", 1000, 400);
  c7->Divide(2, 1, 0.001, 0.001);    
  c7->cd(1);
  gPad->SetGrid();
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);
  gPad->SetLogy();

  TH1D* h1_pi0spe_shower    =  (TH1D*)file->Get("h1_pi0spectrum_1")->Clone("h1_pi0spe_shower");
  TH1D* h1_pi0spe_showerpi0 =  (TH1D*)file->Get("h1_pi0spectrum_5")->Clone("h1_pi0spe_showerpi0");  
  h1_pi0spe_shower->Rebin(2);
  h1_pi0spe_showerpi0->Rebin(2);
  h1_pi0spe_shower->Draw("hist");
  h1_pi0spe_showerpi0->Draw("hist,same");

  h1_pi0spe_showerpi0->SetLineColor(kRed);
  h1_pi0spe_shower->SetLineColor(kBlack);

  h1_pi0spe_shower->SetTitle("Pi0 Spectrum");
  h1_pi0spe_shower->SetXTitle("Pi0 Energy [GeV]");
  h1_pi0spe_shower->SetYTitle("# Pi0 Events");
  h1_pi0spe_shower->GetXaxis()->SetTitleSize(0.06);
  h1_pi0spe_shower->GetYaxis()->SetTitleSize(0.06);
  h1_pi0spe_shower->GetYaxis()->SetTitleOffset(0.85);
  h1_pi0spe_shower->GetXaxis()->SetLabelSize(0.05);
  h1_pi0spe_shower->GetYaxis()->SetLabelSize(0.05);

  TLegend *legend_eff = new TLegend(0.15,0.70,0.5,0.88);
  legend_eff->AddEntry(h1_pi0spe_shower,"Trig.:Shower","L");
  legend_eff->AddEntry(h1_pi0spe_showerpi0,"Trig.:Shower&Pi0","L");
  legend_eff->SetFillColor(kWhite);
  legend_eff->SetBorderSize(1);
  legend_eff->Draw();

  c7->cd(2);
  gPad->SetGrid();
  gPad->SetLeftMargin(0.15);
  gPad->SetBottomMargin(0.15);

  TH1D* h1_pi0eff = (TH1D*) h1_pi0spe_showerpi0->Clone("h1_pi0eff");
  h1_pi0eff->Divide(h1_pi0spe_shower);
  h1_pi0eff->Draw("hist");

  h1_pi0eff->SetLineColor(kBlack);
  h1_pi0eff->SetMaximum(1.1);
  h1_pi0eff->SetTitle("Pi0 Effeciency of Pi0 Trigger");
  h1_pi0eff->SetXTitle("Pi0 Energy [GeV]");
  h1_pi0eff->SetYTitle("Efficiency(=Shower&Pi0/Shower)");
  h1_pi0eff->GetXaxis()->SetTitleSize(0.06);
  h1_pi0eff->GetYaxis()->SetTitleSize(0.06);
  h1_pi0eff->GetYaxis()->SetTitleOffset(0.85);
  h1_pi0eff->GetXaxis()->SetLabelSize(0.05);
  h1_pi0eff->GetYaxis()->SetLabelSize(0.05);


  c7->Update();
  c7->Print(outputpath + Form("/trggereff_pi0.gif")); 

  TCanvas *c8 = new TCanvas("c8", "Trg.", 1000, 800);
  c8->Divide(2, 2, 0.001, 0.001);  
  for(int tower=0;tower<2;tower++){
    c8->cd(1+tower*2);
    gPad->SetGrid();
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    gPad->SetLogy();

    TH1D* h_shower = (TH1D *) file->Get(Form("h1_spectrum_%d_%d_%d", 1, tower, 0))->Clone();
    TH1D* h_showerhighEM = (TH1D *) file->Get(Form("h1_spectrum_%d_%d_%d", 6, tower, 0))->Clone();
    h_shower->Rebin(2);
    h_showerhighEM->Rebin(2);
    h_shower->Draw("hist");
    h_showerhighEM->Draw("hist,same");

    h_shower->SetLineColor(kBlack);
    h_showerhighEM->SetLineColor(kRed);

    h_shower->SetTitle(Form("Photon Spectrum (%s)",(tower==0?"TS":"TL")));
    h_shower->SetXTitle("Photon Energy [GeV]");
    h_shower->SetYTitle("#Events");  
    h_shower->GetXaxis()->SetRangeUser(0.,250.-1);
    h_shower->GetXaxis()->SetTitleSize(0.06);
    h_shower->GetYaxis()->SetTitleSize(0.06);
    h_shower->GetYaxis()->SetTitleOffset(0.85);
    h_shower->GetXaxis()->SetLabelSize(0.05);
    h_shower->GetYaxis()->SetLabelSize(0.05);

    TLegend *legend = new TLegend(0.60,0.60,0.98,0.75);
    legend->AddEntry(h_shower,"Trig.: Shower");
    legend->AddEntry(h_showerhighEM,"Trig.: Shower&HighEM");
    legend->SetFillColor(kWhite);
    legend->SetBorderSize(1);
    legend->Draw();

    c8->cd(2+tower*2);
    gPad->SetGrid();
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);

    TH1D* h_highEMeff = (TH1D *)h_showerhighEM->Clone();
    h_highEMeff->Divide(h_shower);
    h_highEMeff->Draw("hist");

    h_highEMeff->SetLineColor(kRed);
    h_highEMeff->SetTitle(Form("Photon Efficiency of High EM Trigger (%s)",(tower==0?"TS":"TL")));
    h_highEMeff->SetXTitle("Photon Energy [GeV]");
    h_highEMeff->SetYTitle("#Events");  
    h_highEMeff->SetMaximum(1.1);
    h_highEMeff->GetXaxis()->SetRangeUser(0.,250.-1);
    h_highEMeff->GetXaxis()->SetTitleSize(0.06);
    h_highEMeff->GetYaxis()->SetTitleSize(0.06);
    h_highEMeff->GetYaxis()->SetTitleOffset(1.0);
    h_highEMeff->GetXaxis()->SetLabelSize(0.05);
    h_highEMeff->GetYaxis()->SetLabelSize(0.05);
    gPad->Modified();
    gPad->Update();

  }
  c8->Update();
  c8->Print(outputpath + Form("/trggereff_highEM.gif")); 

  theApp.Run();

  return 0;
}
