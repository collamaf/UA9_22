{
    const int nbin=400;
    const char* fileNameIn1="../build/mUA9Align_Conf3b_CrystAng0_N10000.root";
    const char* fileNameIn2="../build/mUA9Align_Conf3b_CrystAng-40_N10000.root";
    const char* fileNameIn3="../build/mUA9Align_Conf3b_CrystAng-20_N10000.root";
    const char* fileNameIn4="../build/mUA9Align_Conf3b_CrystAng-10_N10000.root";
    const char* fileNameIn5="../build/mUA9Align_Conf3b_CrystAng-5_N10000.root";
    const char* fileNameIn6="../build/mUA9Align_Conf3b_CrystAng5_N10000.root";
    const char* fileNameIn7="../build/mUA9Align_Conf3b_CrystAng10_N10000.root";
    const char* fileNameIn8="../build/mUA9Align_Conf3b_CrystAng20_N10000.root";
    const char* fileNameIn9="../build/mUA9Align_Conf3b_CrystAng40_N10000.root";

    
//    TFile* fileOut=TFile::Open("AlignmentOut.root","RECREATE");

//    TH1F* histoXPl2_m40=new TH1F("histoXPl2_m40","X @ Pl2; x [mm];",nbin,1,-1);
//    TH1F* histoXPl2_m20=new TH1F("histoXPl2_m20","X @ Pl2; x [mm];",nbin,1,-1);
//    TH1F* histoXPl2_m10=new TH1F("histoXPl2_m10","X @ Pl2; x [mm];",nbin,1,-1);
//    TH1F* histoXPl2_m5=new TH1F("histoXPl2_m5","X @ Pl2; x [mm];",nbin,1,-1);
//    TH1F* histoXPl2_5=new TH1F("histoXPl2_5","X @ Pl2; x [mm];",nbin,1,-1);
//    TH1F* histoXPl2_10=new TH1F("histoXPl2_10","X @ Pl2; x [mm];",nbin,1,-1);
//    TH1F* histoXPl2_20=new TH1F("histoXPl2_20","X @ Pl2; x [mm];",nbin,1,-1);
//    TH1F* histoXPl2_40=new TH1F("histoXPl2_40","X @ Pl2; x [mm];",nbin,1,-1);

        gStyle->SetOptStat(kFALSE);

//    TFile *fileIn1 = TFile::Open(fileNameIn1);
//    Planes->Draw("CosX>>histo(400)","PlaneId==2");
//    TFile *fileIn2 = TFile::Open(fileNameIn2);
//    Planes->Draw("CosX","PlaneId==2", "samesPLC");
//    TFile *fileIn3 = TFile::Open(fileNameIn3);
//    Planes->Draw("CosX","PlaneId==2", "samesPLC");
//    TFile *fileIn4 = TFile::Open(fileNameIn4);
//    Planes->Draw("CosX","PlaneId==2", "samesPLC");
//    TFile *fileIn5 = TFile::Open(fileNameIn5);
//    Planes->Draw("CosX","PlaneId==2", "samesPLC");
//    TFile *fileIn6 = TFile::Open(fileNameIn6);
//    Planes->Draw("CosX","PlaneId==2", "samesPLC");
//    TFile *fileIn7 = TFile::Open(fileNameIn7);
//    Planes->Draw("CosX","PlaneId==2", "samesPLC");
//    TFile *fileIn8 = TFile::Open(fileNameIn8);
//    Planes->Draw("CosX","PlaneId==2", "samesPLC");
//    TFile *fileIn9 = TFile::Open(fileNameIn9);
//    Planes->Draw("CosX","PlaneId==2", "samesPLC");
    TCanvas * canvCosXPl2=new TCanvas("canvCosXPl2","canvCosXPl2");
    TFile *fileIn1 = TFile::Open(fileNameIn1);
    TH1F* histoXPl2_0=new TH1F("histoXPl2_0","X @ Pl2 Base; x [mm];",nbin,1,-1);
    Planes->Draw("X>>histoXPl2_0","PlaneId==2", "");
    histoXPl2_0->SetDirectory(0);
    
    TFile *fileIn2 = TFile::Open(fileNameIn2);
    TH1F* histoXPl2_m40=new TH1F("histoXPl2_m40","X @ Pl2 m40; x [mm];",nbin,1,-1);
    Planes->Draw("X>>histoXPl2_m40","PlaneId==2", "");
    histoXPl2_m40->SetDirectory(0);
    
    TFile *fileIn3 = TFile::Open(fileNameIn3);
    TH1F* histoXPl2_m20=new TH1F("histoXPl2_m20","X @ Pl2 m20; x [mm];",nbin,1,-1);
    Planes->Draw("X>>histoXPl2_m20","PlaneId==2", "");
    histoXPl2_m20->SetDirectory(0);
    
    TFile *fileIn4 = TFile::Open(fileNameIn4);
    TH1F* histoXPl2_m10=new TH1F("histoXPl2_m10","X @ Pl2 m10; x [mm];",nbin,1,-1);
    Planes->Draw("X>>histoXPl2_m10","PlaneId==2", "");
    histoXPl2_m10->SetDirectory(0);
    
    TFile *fileIn5 = TFile::Open(fileNameIn5);
    TH1F* histoXPl2_m5=new TH1F("histoXPl2_m5","X @ Pl2 m5; x [mm];",nbin,1,-1);
    Planes->Draw("X>>histoXPl2_m5","PlaneId==2", "");
    histoXPl2_m5->SetDirectory(0);
    
    TFile *fileIn6 = TFile::Open(fileNameIn6);
    TH1F* histoXPl2_5=new TH1F("histoXPl2_5","X @ Pl2 5; x [mm];",nbin,1,-1);
    Planes->Draw("X>>histoXPl2_5","PlaneId==2", "");
    histoXPl2_5->SetDirectory(0);
    
    TFile *fileIn7 = TFile::Open(fileNameIn7);
    TH1F* histoXPl2_10=new TH1F("histoXPl2_10","X @ Pl2 10; x [mm];",nbin,1,-1);
    Planes->Draw("X>>histoXPl2_10","PlaneId==2", "");
    histoXPl2_10->SetDirectory(0);
    
    TFile *fileIn8 = TFile::Open(fileNameIn8);
    TH1F* histoXPl2_20=new TH1F("histoXPl2_20","X @ Pl2 20; x [mm];",nbin,1,-1);
    Planes->Draw("X>>histoXPl2_20","PlaneId==2", "");
    histoXPl2_20->SetDirectory(0);
    
    TFile *fileIn9 = TFile::Open(fileNameIn9);
    TH1F* histoXPl2_40=new TH1F("histoXPl2_40","X @ Pl2 40; x [mm];",nbin,1,-1);
    Planes->Draw("X>>histoXPl2_40","PlaneId==2", "");
    histoXPl2_40->SetDirectory(0);

//    TFile *fileIn2 = TFile::Open(fileNameIn2);
//    Planes->Draw("CosX>>histoXPl2_m40","PlaneId==2", "goff");
//    TFile *fileIn3 = TFile::Open(fileNameIn3);
//    Planes->Draw("CosX>>histoXPl2_m20","PlaneId==2", "goff");
//    TFile *fileIn4 = TFile::Open(fileNameIn4);
//    Planes->Draw("CosX>>histoXPl2_m10","PlaneId==2", "goff");
//    TFile *fileIn5 = TFile::Open(fileNameIn5);
//    Planes->Draw("CosX>>histoXPl2_m5","PlaneId==2", "goff");
//    TFile *fileIn6 = TFile::Open(fileNameIn6);
//    Planes->Draw("CosX>>histoXPl2_5","PlaneId==2", "goff");
//    TFile *fileIn7 = TFile::Open(fileNameIn7);
//    Planes->Draw("CosX>>histoXPl2_10","PlaneId==2", "goff");
//    TFile *fileIn8 = TFile::Open(fileNameIn8);
//    Planes->Draw("CosX>>histoXPl2_20","PlaneId==2", "goff");
//    TFile *fileIn9 = TFile::Open(fileNameIn9);
//    Planes->Draw("CosX>>histoXPl2_40","PlaneId==2", "goff");
                 
    TCanvas * canvCosXPl2h=new TCanvas("canvCosXPl2h","canvCosXPl2h");
    histoXPl2_0->SetLineWidth(3);
    histoXPl2_0->Draw();
    histoXPl2_m5->Draw("SamesPLC");
    histoXPl2_5->Draw("SamesPLC");
    histoXPl2_m10->Draw("SamesPLC");
    histoXPl2_10->Draw("SamesPLC");
    histoXPl2_m20->Draw("SamesPLC");
    histoXPl2_20->Draw("SamesPLC");
    histoXPl2_m40->Draw("SamesPLC");
    histoXPl2_40->Draw("SamesPLC");
    
    canvCosXPl2h->SetLogy();
    canvCosXPl2h->BuildLegend();
    
    
    TCanvas * canvCosXPl2hCum=new TCanvas("canvCosXPl2hCum","canvCosXPl2hCum");
    TH1F* histoXPl2_0_Cum=(TH1F*)histoXPl2_0->GetCumulative(1);
    histoXPl2_0_Cum->Scale(1/histoXPl2_0_Cum->GetMaximum());
    TH1F* histoXPl2_m40_Cum=(TH1F*)histoXPl2_m40->GetCumulative(1);
    histoXPl2_m40_Cum->Scale(1/histoXPl2_m40_Cum->GetMaximum());
    TH1F* histoXPl2_m20_Cum=(TH1F*)histoXPl2_m20->GetCumulative(1);
    histoXPl2_m20_Cum->Scale(1/histoXPl2_m20_Cum->GetMaximum());
    TH1F* histoXPl2_m10_Cum=(TH1F*)histoXPl2_m10->GetCumulative(1);
    histoXPl2_m10_Cum->Scale(1/histoXPl2_m10_Cum->GetMaximum());
    TH1F* histoXPl2_m5_Cum=(TH1F*)histoXPl2_m5->GetCumulative(1);
    histoXPl2_m5_Cum->Scale(1/histoXPl2_m5_Cum->GetMaximum());
    TH1F* histoXPl2_5_Cum=(TH1F*)histoXPl2_5->GetCumulative(1);
    histoXPl2_5_Cum->Scale(1/histoXPl2_5_Cum->GetMaximum());
    TH1F* histoXPl2_10_Cum=(TH1F*)histoXPl2_10->GetCumulative(1);
    histoXPl2_10_Cum->Scale(1/histoXPl2_10_Cum->GetMaximum());
    TH1F* histoXPl2_20_Cum=(TH1F*)histoXPl2_20->GetCumulative(1);
    histoXPl2_20_Cum->Scale(1/histoXPl2_20_Cum->GetMaximum());
    TH1F* histoXPl2_40_Cum=(TH1F*)histoXPl2_40->GetCumulative(1);
    histoXPl2_40_Cum->Scale(1/histoXPl2_40_Cum->GetMaximum());

    histoXPl2_0_Cum->Draw();
    histoXPl2_0_Cum->SetLineWidth(3);
    histoXPl2_m5_Cum->Draw("samesPLC");
    histoXPl2_5_Cum->Draw("samesPLC");
    histoXPl2_m10_Cum->Draw("samesPLC");
    histoXPl2_10_Cum->Draw("samesPLC");
    histoXPl2_m20_Cum->Draw("samesPLC");
    histoXPl2_20_Cum->Draw("samesPLC");
    histoXPl2_m40_Cum->Draw("samesPLC");
    histoXPl2_40_Cum->Draw("samesPLC");
    canvCosXPl2hCum->BuildLegend();
//
//    TCanvas * canvXPl2=new TCanvas();
//    fileIn1->cd();
//    Planes->Draw("X","PlaneId==2");
//    fileIn2->cd();
//    Planes->Draw("X","PlaneId==2", "samesPLC");
//    fileIn3->cd();
//    Planes->Draw("X","PlaneId==2", "samesPLC");
//    fileIn4->cd();
//    Planes->Draw("X","PlaneId==2", "samesPLC");
//    fileIn5->cd();
//    Planes->Draw("X","PlaneId==2", "samesPLC");
//    fileIn6->cd();
//    Planes->Draw("X","PlaneId==2", "samesPLC");
//    fileIn7->cd();
//    Planes->Draw("X","PlaneId==2", "samesPLC");
//    fileIn8->cd();
//    Planes->Draw("X","PlaneId==2", "samesPLC");
//    fileIn9->cd();
//    Planes->Draw("X","PlaneId==2", "samesPLC");
//    canvXPl2->SetLogy();
//
//    TCanvas * canvXPl5=new TCanvas();
//    fileIn1->cd();
//    Planes->Draw("X","PlaneId==5");
//    fileIn2->cd();
//    Planes->Draw("X","PlaneId==5", "samesPLC");
//    fileIn3->cd();
//    Planes->Draw("X","PlaneId==5", "samesPLC");
//    fileIn4->cd();
//    Planes->Draw("X","PlaneId==5", "samesPLC");
//    fileIn5->cd();
//    Planes->Draw("X","PlaneId==5", "samesPLC");
//    fileIn6->cd();
//    Planes->Draw("X","PlaneId==5", "samesPLC");
//    fileIn7->cd();
//    Planes->Draw("X","PlaneId==5", "samesPLC");
//    fileIn8->cd();
//    Planes->Draw("X","PlaneId==5", "samesPLC");
//    fileIn9->cd();
//    Planes->Draw("X","PlaneId==5", "samesPLC");
//    canvXPl5->SetLogy();

}
