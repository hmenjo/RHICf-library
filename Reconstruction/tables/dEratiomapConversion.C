int dEratiomapConversion(){

	TH2D* h2_20mm[16];

	TFile* fdEratiomap = new TFile("dEratiomap.root");

	for(int i=0;i<16;i++){

		h2_20mm[i] = new TH2D(Form("h2_20mm_%d", i), "", 20, 0, 20, 20, 0, 20);
	}

	for(int ix=1;ix<=20;ix++){

		for(int iy=1;iy<=20;iy++){

			h2_20mm[0] -> SetBinContent(ix, iy, h2_dEratioTS_0->GetBinContent(ix, iy));
			h2_20mm[1] -> SetBinContent(ix, iy, h2_dEratioTS_1->GetBinContent(ix, iy));
			h2_20mm[2] -> SetBinContent(ix, iy, h2_dEratioTS_2->GetBinContent(ix, iy));
			h2_20mm[3] -> SetBinContent(ix, iy, h2_dEratioTS_3->GetBinContent(ix, iy));
			h2_20mm[4] -> SetBinContent(ix, iy, h2_dEratioTS_4->GetBinContent(ix, iy));
			h2_20mm[5] -> SetBinContent(ix, iy, h2_dEratioTS_5->GetBinContent(ix, iy));
			h2_20mm[6] -> SetBinContent(ix, iy, h2_dEratioTS_6->GetBinContent(ix, iy));
			h2_20mm[7] -> SetBinContent(ix, iy, h2_dEratioTS_7->GetBinContent(ix, iy));
			h2_20mm[8] -> SetBinContent(ix, iy, h2_dEratioTS_8->GetBinContent(ix, iy));
			h2_20mm[9] -> SetBinContent(ix, iy, h2_dEratioTS_9->GetBinContent(ix, iy));
			h2_20mm[10] -> SetBinContent(ix, iy, h2_dEratioTS_10->GetBinContent(ix, iy));
			h2_20mm[11] -> SetBinContent(ix, iy, h2_dEratioTS_11->GetBinContent(ix, iy));
			h2_20mm[12] -> SetBinContent(ix, iy, h2_dEratioTS_12->GetBinContent(ix, iy));
			h2_20mm[13] -> SetBinContent(ix, iy, h2_dEratioTS_13->GetBinContent(ix, iy));
			h2_20mm[14] -> SetBinContent(ix, iy, h2_dEratioTS_14->GetBinContent(ix, iy));
			h2_20mm[15] -> SetBinContent(ix, iy, h2_dEratioTS_15->GetBinContent(ix, iy));
		}	
	}

	TFile* f20 = new TFile("dEratiomap_20mm_verTH2D.root", "RECREATE");
	f20 -> cd();
	for(int i=0;i<16;i++){

                if(i<10) h2_20mm[i] -> Write(Form("h2map_tg0_0%d", i));
		else h2_20mm[i] -> Write(Form("h2map_tg0_%d", i));
        }
	f20 -> Close();
	delete f20;

	TH2D* h2_40mm[16];

	for(int i=0;i<16;i++){

                h2_40mm[i] = new TH2D(Form("h2_40mm_%d", i), "", 40, 0, 40, 40, 0, 40);
        }

	fdEratiomap -> cd();

        for(int ix=1;ix<=40;ix++){

                for(int iy=1;iy<=40;iy++){

                        h2_40mm[0] -> SetBinContent(ix, iy, h2_dEratioTL_0->GetBinContent(ix, iy));
                        h2_40mm[1] -> SetBinContent(ix, iy, h2_dEratioTL_1->GetBinContent(ix, iy));
                        h2_40mm[2] -> SetBinContent(ix, iy, h2_dEratioTL_2->GetBinContent(ix, iy));
                        h2_40mm[3] -> SetBinContent(ix, iy, h2_dEratioTL_3->GetBinContent(ix, iy));
                        h2_40mm[4] -> SetBinContent(ix, iy, h2_dEratioTL_4->GetBinContent(ix, iy));
                        h2_40mm[5] -> SetBinContent(ix, iy, h2_dEratioTL_5->GetBinContent(ix, iy));
                        h2_40mm[6] -> SetBinContent(ix, iy, h2_dEratioTL_6->GetBinContent(ix, iy));
                        h2_40mm[7] -> SetBinContent(ix, iy, h2_dEratioTL_7->GetBinContent(ix, iy));
                        h2_40mm[8] -> SetBinContent(ix, iy, h2_dEratioTL_8->GetBinContent(ix, iy));
                        h2_40mm[9] -> SetBinContent(ix, iy, h2_dEratioTL_9->GetBinContent(ix, iy));
                        h2_40mm[10] -> SetBinContent(ix, iy, h2_dEratioTL_10->GetBinContent(ix, iy));
                        h2_40mm[11] -> SetBinContent(ix, iy, h2_dEratioTL_11->GetBinContent(ix, iy));
                        h2_40mm[12] -> SetBinContent(ix, iy, h2_dEratioTL_12->GetBinContent(ix, iy));
                        h2_40mm[13] -> SetBinContent(ix, iy, h2_dEratioTL_13->GetBinContent(ix, iy));
                        h2_40mm[14] -> SetBinContent(ix, iy, h2_dEratioTL_14->GetBinContent(ix, iy));
                        h2_40mm[15] -> SetBinContent(ix, iy, h2_dEratioTL_15->GetBinContent(ix, iy));
                }       
        }

	TFile* f40 = new TFile("dEratiomap_40mm_verTH2D.root", "RECREATE");
        f40 -> cd();
	for(int i=0;i<16;i++){

                if(i<10) h2_40mm[i] -> Write(Form("h2map_tg1_0%d", i));
                else h2_40mm[i] -> Write(Form("h2map_tg1_%d", i));
        }
        f40 -> Close();
        delete f40;	

	return 0;
}
