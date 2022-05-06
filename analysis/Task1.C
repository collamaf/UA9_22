{
	const int caso=3; //3 o 7
	bool flagDet=true;
	const int nbin=500;
	double xmin=-5;
	double xmax=45;
	
	double xminZoom=-2;
	double xmaxZoom=2;
	TString fileInX="../build/mUA9_20_Conf3_SigmaX1Y0Z0_NoDet_N10000.root";
	TString fileInNoX="../build/mUA9_Conf3_SigmaX1Y0Z0_NoCryst2_NoDet_N10000.root";
	if (flagDet) {
		fileInX="../build/mUA9_Conf3_SigmaX1Y0Z0_N10000.root";
		fileInNoX="../build/mUA9_Conf3_SigmaX1Y0Z0_NoCryst2_N10000.root";
	}
	
	TString outFileName=Form("Task1_Pl%d_Det%d", caso, flagDet);

	if (caso==7) {
		cout<<"Chiesto caso 7"<<endl;
		xmin=-25;
		xmax=65;
		xminZoom=-2;
		xmaxZoom=2;
//		outFileName="Task1_Pl7";
	}
	
	char* cutPla3=Form("PlaneId==3");
	char* cutPla3Zoom=Form("PlaneId==3&&X<%f&&X>%f",xmaxZoom,xminZoom);
	
	char* cutPla7=Form("PlaneId==7");
	char* cutPla7Zoom=Form("PlaneId==7&&X<%f&&X>%f",xmaxZoom,xminZoom);
	
	
	char* cutToDo=cutPla3;
	char* cutToDoZoom=cutPla3Zoom;
	if (caso==7) {
		cutToDo=cutPla7;
		cutToDoZoom=cutPla7Zoom;
	}
	
	TFile* fout=new TFile(outFileName+".root","RECREATE");
//	TFile *inFileX = TFile::Open("../build/mUA9Rot3100u_20_Conf3_SigmaX1Y0Z0_NoDet_N10000.root");
	TFile *inFileX = TFile::Open(fileInX);
	
	TH1F* histoX=new TH1F("histoX","w/ X2; X [mm];",nbin,xmin,xmax);
	TH1F* histoXZoom=new TH1F("histoXZoom","w/ X2 Zoom; X [mm];",nbin,xminZoom,xmaxZoom);
	
	
	Planes->Draw("X>>histoX",cutToDo,"goff");
	Planes->Draw("X>>histoXZoom",cutToDoZoom,"goff");
	fout->cd();
	histoX->Write();
	
	TFile *inFileNoX = TFile::Open(fileInNoX);
	TH1F* histoNoX=new TH1F("histoNoX","w/o X2; X [mm];",nbin,xmin,xmax);
	TH1F* histoNoXZoom=new TH1F("histoNoXZoom","w/o X2 Zoom; X [mm];",nbin,xminZoom,xmaxZoom);
	
	Planes->Draw("X>>histoNoX",cutToDo,"goff");
	Planes->Draw("X>>histoNoXZoom",cutToDoZoom,"goff");
	fout->cd();
	histoNoX->Write();
	
	
	TCanvas* canvPos=new TCanvas("canvPos","canvPos");
	histoX->Draw();
	histoNoX->Draw("samesPLC");
	canvPos->BuildLegend();
	canvPos->SetLogy();
	
	TCanvas* canvPosZoom=new TCanvas("canvPosZoom","canvPosZoom");
	histoXZoom->Draw();
	histoNoXZoom->Draw("samesPLC");
	canvPosZoom->BuildLegend();
	canvPosZoom->SetLogy();
	
	TCanvas* canvBoth=new TCanvas("canvBoth","canvBoth");
	canvBoth->Divide(1,2);
	canvBoth->cd(1);
	canvBoth->BuildLegend();
	histoX->Draw();
	histoNoX->Draw("samesPLC");
	canvBoth->SetLogy();
	canvBoth->BuildLegend();
	
	TH1F* histoDiff = (TH1F*)histoX->Clone("histoDiff");
	histoDiff->SetLineColor(kBlack);
	histoDiff->SetTitle("w/ X2 - w/o X2; X[mm];");
	histoDiff->Add(histoNoX,-1);
	canvBoth->cd(2);
	histoDiff->DrawCopy();
	//	TCanvas* canvDiff=new TCanvas("canvDiff","canvDiff");
	//	histoDiff->GetXaxis()->SetRangeUser(-5,5);
	//	histoDiff->Draw();
	//	canvDiff->SetLogy();
	//	canvDiff->BuildLegend();
	
	TCanvas* canvBothZoom=new TCanvas("canvBothZoom","canvBothZoom");
	canvBothZoom->Divide(1,2);
	canvBothZoom->cd(1);
	histoXZoom->Draw();
	histoNoXZoom->Draw("samesPLC");
	canvBoth->SetLogy();
	canvBoth->BuildLegend();
	
	TH1F* histoDiffZoom = (TH1F*)histoXZoom->Clone("histoDiffZoom");
	histoDiffZoom->SetLineColor(kBlack);
	histoDiffZoom->SetTitle("w/ X2 - w/o X2 Zoom; X [mm];");
	histoDiffZoom->Add(histoNoXZoom,-1);
	canvBothZoom->cd(2);
	histoDiffZoom->DrawCopy();
	TCanvas* canvDiffZoom=new TCanvas("canvDiffZoom","canvDiffZoom");
//	histoDiffZoom->GetXaxis()->SetRangeUser(-5,5);
	histoDiffZoom->Draw();
	//	canvDiff->SetLogy();
	//	canvDiff->BuildLegend();
	
	fout->cd();
	histoNoXZoom->Write();
	histoXZoom->Write();
	histoDiff->Write();
	histoDiffZoom->Write();
	canvPos->Write();
	canvPosZoom->Write();
	canvBoth->Write();
	canvDiffZoom->Write();
	canvBothZoom->Write();
	canvPos->SaveAs(Form("%s_Pos.pdf",outFileName.Data()));
	canvPosZoom->SaveAs(Form("%s_PosZoom.pdf",outFileName.Data()));
	canvBoth->SaveAs(Form("%s_Both.pdf",outFileName.Data()));
	canvDiffZoom->SaveAs(Form("%s_DiffZoom.pdf",outFileName.Data()));
	canvBothZoom->SaveAs(Form("%s_BothZoom.pdf",outFileName.Data()));
}
