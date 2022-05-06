{
//	const char* fileNameIn="../build/mUA9_Conf3_NoDet_N10000.root";
//	const char* runName="Tr_Ideal";
	
	const char* fileNameIn="../build/mUA9_Conf3_SigmaX1Y0Z0_NoDet_N10000.root";
	const char* runName="Tr_PointSigma1em6";

//	const char* fileNameIn="../build/mUA9Pla_Conf3_SigmaX1Y0Z0_NoDet_N10000.root";
//	const char* runName="Tr_PlaSigma1em6";
	
//	const char* fileNameIn="../build/mUA9NoCh_Conf3_NoDet_N1000.root";
//	const char* runName="Tr_BasePlaNoCh";
	
	const int nbin=400;
	int nprim=10000;
	double peakCenter=0;
	double peakRight=2;
	double peakLeft=-2;
	FILE* textOut=fopen(Form("%s_out.txt",runName),"wt");
	fprintf(textOut,"RUN NAME: %s\n",runName);
	fprintf(textOut,"INPUT FILE NAME: %s\n",fileNameIn);
	double widthCenter=0;
	double widthRight=2;
	double widthLeft=-2;
	double funcGausWidth=0.2;
	
	TFile *fileIn = TFile::Open(fileNameIn);

	TH1F* histoSourceX=new TH1F("histoSourceX","Source X; x [mm];",nbin,1,-1);
	TH1F* histoSourceCosX=new TH1F("histoSourceCosX","Source Angle; #theta [rad]",100,1,-1);
	
	TH1F* histoAnglePostX1=new TH1F("histoAnglePostX1","Angle post X1; #theta [mrad]",nbin,1,-1);
	TH1F* histoAnglePostX2=new TH1F("histoAnglePostX2","Angle post X2; #theta [mrad]",nbin,1,-1);
	TH1F* histoAnglePostX3=new TH1F("histoAnglePostX3","Angle post X3; #theta [mrad]",nbin,1,-1);
	
	nprim=Beam->GetEntries();
	Beam->Draw("X>>histoSourceX","","goff");
	Beam->Draw("CosX>>histoSourceCosX","","goff");
	Planes->Draw("1000*CosX>>histoAnglePostX1","PlaneId==2","goff");
	Planes->Draw("1000*CosX>>histoAnglePostX2","PlaneId==5","goff");
	Planes->Draw("1000*CosX>>histoAnglePostX3","PlaneId==3","goff");
	
	TFile* fileOut=TFile::Open(Form("%s_out.root",runName),"RECREATE");

	TCanvas* canvBeam=new TCanvas("canvBeam","canvBeam");
	canvBeam->Divide(1,2);
	canvBeam->cd(1);
	histoSourceX->Draw();
	canvBeam->cd(2);
	histoSourceCosX->Draw();
	

//
//	TH1F* histoAnglePostX1_c=new TH1F();
//	histoAnglePostX1_c=(TH1F*)histoAnglePostX1->GetCumulative();
//	TH1* histoAnglePostX2_c=histoAnglePostX2->GetCumulative();
//	TH1* histoAnglePostX3_c=histoAnglePostX3->GetCumulative();
//	histoAnglePostX1_c->Scale(1./histoAnglePostX1_c->GetMaximum());
//	histoAnglePostX2_c->Scale(1./histoAnglePostX2_c->GetMaximum());
//	histoAnglePostX3_c->Scale(1./histoAnglePostX3_c->GetMaximum());
//	histoAnglePostX1_c->Write();
//	histoAnglePostX2_c->Write();
//	histoAnglePostX3_c->Write();
	
	TCanvas* canvXAll=new TCanvas("canvXAll","canvXAll");
	histoAnglePostX3->Draw();
	histoAnglePostX2->Draw("samesPLC");
	histoAnglePostX1->Draw("samesPLC");
	canvXAll->SetLogy(1);
	canvXAll->SaveAs(Form("%s_XAll.pdf",runName));
	canvXAll->Write();
	//	DoublePrint(textOut, "CIAOOOOOO");
	
	double myArea0=0;
	double myArea20=0;
	double myAreaM20=0;
	//	TF1* funcGaus0=new TF1("funcGaus0","[0]*exp(-0.5*((x-[1])/[2])**2)",-funcGausWidth,funcGausWidth);
	//	TF1* funcGaus20=new TF1("funcGaus20","[0]*exp(-0.5*((x-[1])/[2])**2)",peakRight-funcGausWidth,peakRight+funcGausWidth);
	//	TF1* funcGausM20=new TF1("funcGausM20","[0]*exp(-0.5*((x-[1])/[2])**2)",peakLeft-funcGausWidth,peakLeft+funcGausWidth);
	
	TF1* funcGaus1_0=new TF1("funcGaus1_0","[0]*exp(-0.5*((x-[1])/[2])**2)",-funcGausWidth,funcGausWidth);
	TF1* funcGaus1_20=new TF1("funcGaus1_20","[0]*exp(-0.5*((x-[1])/[2])**2)",peakRight-funcGausWidth,peakRight+funcGausWidth);
	
	TF1* funcGaus2_0=new TF1("funcGaus2_0","[0]*exp(-0.5*((x-[1])/[2])**2)",-funcGausWidth,funcGausWidth);
	TF1* funcGaus2_20=new TF1("funcGaus2_20","[0]*exp(-0.5*((x-[1])/[2])**2)",peakRight-funcGausWidth,peakRight+funcGausWidth);
	TF1* funcGaus2_M20=new TF1("funcGaus2_M20","[0]*exp(-0.5*((x-[1])/[2])**2)",peakLeft-funcGausWidth,peakLeft+funcGausWidth);
	
	TF1* funcGaus3_0=new TF1("funcGaus3_0","[0]*exp(-0.5*((x-[1])/[2])**2)",-funcGausWidth,funcGausWidth);
	TF1* funcGaus3_20=new TF1("funcGaus3_20","[0]*exp(-0.5*((x-[1])/[2])**2)",peakRight-funcGausWidth,peakRight+funcGausWidth);
	TF1* funcGaus3_M20=new TF1("funcGaus3_M20","[0]*exp(-0.5*((x-[1])/[2])**2)",peakLeft-funcGausWidth,peakLeft+funcGausWidth);
	
	//	TF1* funcGaus0=new TF1("funcGaus0","gaus",-funcGausWidth,funcGausWidth);
	//	TF1* funcGaus20=new TF1("funcGaus20","gaus",peakRight-funcGausWidth,peakRight+funcGausWidth);
	//	TF1* funcGausM20=new TF1("funcGausM20","gaus",peakLeft-2*funcGausWidth,peakLeft+2*funcGausWidth);
	
	funcGaus1_0->SetParameter(0,histoAnglePostX1->GetBinContent(histoAnglePostX1->FindBin(widthCenter)));
	funcGaus1_20->SetParameter(0,histoAnglePostX1->GetBinContent(histoAnglePostX1->FindBin(widthRight)));
	funcGaus1_0->SetParLimits(0,10,10000);
	funcGaus1_20->SetParLimits(0,10,10000);
	
	funcGaus1_0->FixParameter(1,0);
	funcGaus1_20->FixParameter(1,2);
	
	funcGaus1_0->SetParameter(2,0.01);
	funcGaus1_0->SetParLimits(2,0,0.1);
	funcGaus1_20->SetParameter(2,0.005);
	funcGaus1_20->SetParLimits(2,0,0.1);

	cout<<"#######################\nFITTING X1\n####################"<<endl;
	fprintf(textOut,"\n####### After X1\n");
	
	TCanvas* canvX1=new TCanvas("canvX1","canvX1");
	histoAnglePostX1->Draw();
	canvX1->SetLogy(1);
	histoAnglePostX1->Fit(funcGaus1_0,"N","",-0.05,0.05);
	histoAnglePostX1->Fit(funcGaus1_20,"N","",peakRight-0.03,peakRight+0.03);
	funcGaus1_0->Draw("same");
	funcGaus1_20->Draw("same");
	myArea0=funcGaus1_0->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus1_0->GetParameter(2)/histoAnglePostX1->GetBinWidth(1);
	myArea20=funcGaus1_20->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus1_20->GetParameter(2)/histoAnglePostX1->GetBinWidth(1);
	
	
	cout<<"\n####### After X1"<<endl;
	
	printf("Frac. Am1:\t%.1f %% (mean: %.1f [mrad], sigma: %.1e [mrad])\n", myArea0/nprim*100, funcGaus1_0->GetParameter(1),funcGaus1_0->GetParameter(2));
	printf("Frac. Ch1:\t%.1f %% (%.1f [mrad], sigma: %.1e [mrad]))\n\n", myArea20/nprim*100, funcGaus1_20->GetParameter(1),funcGaus1_20->GetParameter(2));
	fprintf(textOut,"Frac. Am1:\t%.1f %% (%.1f [mrad], sigma: %.1e [mrad]))\n", myArea0/nprim*100, funcGaus1_0->GetParameter(1),funcGaus1_0->GetParameter(2));
	fprintf(textOut,"Frac. Ch1:\t%.1f %% (%.1f [mrad], sigma: %.1e [mrad]))\n\n", myArea20/nprim*100, funcGaus1_20->GetParameter(1),funcGaus1_20->GetParameter(2));
	canvX1->SaveAs(Form("%s_X1.pdf",runName));
	canvX1->Write();
#if 1
	
	funcGaus2_0->SetParameter(0,histoAnglePostX2->GetBinContent(histoAnglePostX2->FindBin(widthCenter)));
	funcGaus2_20->SetParameter(0,histoAnglePostX2->GetBinContent(histoAnglePostX2->FindBin(widthRight)));
	funcGaus2_M20->SetParameter(0,histoAnglePostX2->GetBinContent(histoAnglePostX2->FindBin(widthLeft)));
	funcGaus2_0->SetParLimits(0,10,10000);
	funcGaus2_20->SetParLimits(0,10,10000);
	funcGaus2_M20->SetParLimits(0,histoAnglePostX2->GetBinContent(histoAnglePostX2->FindBin(widthLeft))*0.8,10000);
	
	funcGaus2_0->FixParameter(1,0);
	funcGaus2_20->FixParameter(1,2);
	funcGaus2_M20->FixParameter(1,-2);
	
	funcGaus2_0->SetParameter(2,0.01);
	funcGaus2_20->SetParameter(2,0.005);
	funcGaus2_M20->SetParameter(2,0.01);
	funcGaus2_0->SetParLimits(2,0.5*histoAnglePostX2->GetBinWidth(1),0.1);
	funcGaus2_20->SetParLimits(2,0.5*histoAnglePostX2->GetBinWidth(1),0.1);
	funcGaus2_M20->SetParLimits(2,0.5*histoAnglePostX2->GetBinWidth(1),0.1);

	cout<<"#######################\nFITTING X2\n####################"<<endl;
	fprintf(textOut,"\n####### After X2\n");
	TCanvas* canvX2=new TCanvas("canvX2","canvX2");
	//	TF1* funcGaus0=new TF1("funcGaus0","gaus",-0.05,0.05);
	//	TF1* funcGaus20=new TF1("funcGaus20","gaus",2-0.05,2+0.05);
	histoAnglePostX2->Draw();
	canvX2->SetLogy(1);
	histoAnglePostX2->Fit(funcGaus2_0,"N","",-0.05,0.05);
	histoAnglePostX2->Fit(funcGaus2_20,"N","",peakRight-0.05,peakRight+0.05);
	//	histoAnglePostX2->Fit(funcGausM20,"N","",-2.04,-1.96);
	histoAnglePostX2->Fit(funcGaus2_M20,"N","",peakLeft-0.04,peakLeft+0.04);
	funcGaus2_0->Draw("same");
	funcGaus2_20->Draw("same");
	funcGaus2_M20->Draw("same");
	
	myArea0=funcGaus2_0->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus2_0->GetParameter(2)/histoAnglePostX2->GetBinWidth(1);
	myArea20=funcGaus2_20->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus2_20->GetParameter(2)/histoAnglePostX2->GetBinWidth(1);
	myAreaM20=funcGaus2_M20->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus2_M20->GetParameter(2)/histoAnglePostX2->GetBinWidth(1);
	
	//	cout<<"\n####### After X2\nAm. Frac.: "<<myArea0/nprim*100<<endl<<"Ch.1 Frac.:"<<myArea20/nprim*100<<endl<<"Ch.1 Frac.:"<<myAreaM20/nprim*100<<endl<<endl<<endl;
	cout<<"\n####### After X2"<<endl;
	//	cout<<"Frac. Am1:\t"<<myArea0/nprim*100<<endl;
	//	cout<<"Frac. Ch1+Am2:\t"<<myArea20/nprim*100<<endl;
	//	cout<<"Frac. Ch1+Ch2:\t"<<myAreaM20/nprim*100<<endl<<endl<<endl;
	printf("Frac. Am1:\t%.1f %% (mean: %.1f [mrad], sigma: %.1e [mrad])\n", myArea0/nprim*100, funcGaus2_0->GetParameter(1),funcGaus2_0->GetParameter(2));
	printf("Frac. Ch1+Am2:\t%.1f %% (mean: %.1f [mrad], sigma: %.1e [mrad])\n", myArea20/nprim*100, funcGaus2_20->GetParameter(1),funcGaus2_20->GetParameter(2));
	printf("Frac. Ch1+Ch2:\t%.1f %% (mean: %.1f [mrad], sigma: %.1e [mrad])\n\n", myAreaM20/nprim*100, funcGaus2_M20->GetParameter(1),funcGaus2_M20->GetParameter(2));
	fprintf(textOut,"Frac. Am1:\t%.1f %% (mean: %.1f [mrad], sigma: %.1e [mrad])\n", myArea0/nprim*100, funcGaus2_0->GetParameter(1),funcGaus2_0->GetParameter(2));
	fprintf(textOut,"Frac. Ch1+Am2:\t%.1f %% (mean: %.1f [mrad], sigma: %.1e [mrad])\n", myArea20/nprim*100, funcGaus2_20->GetParameter(1),funcGaus2_20->GetParameter(2));
	fprintf(textOut,"Frac. Ch1+Ch2:\t%.1f %% (mean: %.1f [mrad], sigma: %.1e [mrad])\n\n", myAreaM20/nprim*100, funcGaus2_M20->GetParameter(1),funcGaus2_M20->GetParameter(2));
	canvX2->SaveAs(Form("%s_X2.pdf",runName));
	canvX2->Write();
#endif
	
#if 1
	
	funcGaus3_0->SetParameter(0,histoAnglePostX3->GetBinContent(histoAnglePostX3->FindBin(widthCenter)));
	funcGaus3_20->SetParameter(0,histoAnglePostX3->GetBinContent(histoAnglePostX3->FindBin(widthRight)));
	funcGaus3_M20->SetParameter(0,histoAnglePostX3->GetBinContent(histoAnglePostX3->FindBin(widthLeft)));
	
	funcGaus3_0->SetParLimits(0,10,10000);
	funcGaus3_20->SetParLimits(0,10,10000);
	funcGaus3_M20->SetParLimits(0,10,10000);
	
	funcGaus3_0->FixParameter(1,0);
	funcGaus3_20->FixParameter(1,2);
	funcGaus3_M20->FixParameter(1,-2);
	
	funcGaus3_0->SetParameter(2,0.01);
	funcGaus3_20->SetParameter(2,0.005);
	funcGaus3_M20->SetParameter(2,0.01);
	funcGaus3_0->SetParLimits(2,0,0.1);
	funcGaus3_20->SetParLimits(2,0,0.1);
	funcGaus3_M20->SetParLimits(2,0,0.1);
	
	cout<<"#######################\nFITTING X3\n####################"<<endl;
	fprintf(textOut,"\n####### After X3\n");
	TCanvas* canvX3=new TCanvas("canvX3","canvX3");
	histoAnglePostX3->Draw();
	canvX3->SetLogy(1);
	histoAnglePostX3->Fit(funcGaus3_0,"N","",-0.05,0.05);
	histoAnglePostX3->Fit(funcGaus3_20,"N","",peakRight-0.05,peakRight+0.05);
	//	histoAnglePostX2->Fit(funcGausM20,"N","",-2.04,-1.96);
	histoAnglePostX3->Fit(funcGaus3_M20,"N","",peakLeft-0.04,peakLeft+0.04);
	funcGaus3_0->Draw("same");
	funcGaus3_20->Draw("same");
	funcGaus3_M20->Draw("same");
	
	myArea0=funcGaus3_0->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus3_0->GetParameter(2)/histoAnglePostX3->GetBinWidth(1);
	myArea20=funcGaus3_20->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus3_20->GetParameter(2)/histoAnglePostX3->GetBinWidth(1);
	myAreaM20=funcGaus3_M20->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus3_M20->GetParameter(2)/histoAnglePostX3->GetBinWidth(1);
	
	//	cout<<"\n####### After X3\nAm. Frac.: "<<myArea0/nprim*100<<endl<<"Ch.1 Frac.:"<<myArea20/nprim*100<<endl<<"Ch.1 Frac.:"<<myAreaM20/nprim*100<<endl<<endl<<endl;
	cout<<"\n####### After X3"<<endl;
	//	cout<<"Am. Frac.: "<<myArea0/nprim*100<<endl;
	//	cout<<"Ch.1 Frac.:"<<myArea20/nprim*100<<endl;
	//	cout<<"Ch.1 Frac.:"<<myAreaM20/nprim*100<<endl<<endl<<endl;
	printf("Frac. Am1+Am3|Ch1+Ch2+Ch3:\t%.1f %% (mean: %.1f [mrad], sigma: %.1e [mrad])\n", myArea0/nprim*100, funcGaus3_0->GetParameter(1), funcGaus3_0->GetParameter(2));
	printf("Frac. Ch1+Am2:\t\t\t%.1f %% (mean: %.1f [mrad], sigma: %.1e [mrad])\n", myArea20/nprim*100, funcGaus3_20->GetParameter(1),funcGaus3_20->GetParameter(2));
	printf("Frac. Ch1+Ch2+Am3:\t\t%.1f %% (mean: %.1f [mrad], sigma: %.1e [mrad])\n\n", myAreaM20/nprim*100, funcGaus3_M20->GetParameter(1), funcGaus3_M20->GetParameter(2));
	fprintf(textOut,"Frac. Am1+Am3|Ch1+Ch2+Ch3:\t%.1f %% (mean: %.1f [mrad], sigma: %.1e [mrad])\n", myArea0/nprim*100, funcGaus3_0->GetParameter(1), funcGaus3_0->GetParameter(2));
	fprintf(textOut,"Frac. Ch1+Am2:\t\t\t%.1f %% (mean: %.1f [mrad], sigma: %.1e [mrad])\n", myArea20/nprim*100, funcGaus3_20->GetParameter(1), funcGaus3_20->GetParameter(2));
	fprintf(textOut,"Frac. Ch1+Ch2+Am3:\t\t%.1f %% (mean: %.1f [mrad], sigma: %.1e [mrad])\n\n", myAreaM20/nprim*100, funcGaus3_M20->GetParameter(1), funcGaus3_M20->GetParameter(2));
	canvX3->SaveAs(Form("%s_X3.pdf",runName));
	canvX3->Write();
#endif
	histoSourceX->Write();
	histoSourceCosX->Write();
	histoAnglePostX1->Write();
	histoAnglePostX2->Write();
	histoAnglePostX3->Write();
	
	TCanvas* canvCum=new TCanvas("canvCum","canvCum",0,0,400,1200);
	canvCum->Divide(1,3);
	TH1F* histoAnglePostX1Cum=(TH1F*)histoAnglePostX1->GetCumulative(1);
	histoAnglePostX1Cum->Scale(1/histoAnglePostX1Cum->GetMaximum());
	histoAnglePostX1Cum->Write();
	
	TH1F* histoAnglePostX2Cum=(TH1F*)histoAnglePostX2->GetCumulative(1);
	histoAnglePostX2Cum->Scale(1/histoAnglePostX2Cum->GetMaximum());
	histoAnglePostX2Cum->Write();
	
	TH1F* histoAnglePostX3Cum=(TH1F*)histoAnglePostX3->GetCumulative(1);
	histoAnglePostX3Cum->Scale(1/histoAnglePostX3Cum->GetMaximum());
	histoAnglePostX3Cum->Write();
	
	canvCum->cd(1);
	histoAnglePostX1Cum->SetStats(0);
	histoAnglePostX1Cum->Draw();
	canvCum->cd(2);
	histoAnglePostX2Cum->SetStats(0);
	histoAnglePostX2Cum->Draw();
	canvCum->cd(3);
	histoAnglePostX3Cum->SetStats(0);
	histoAnglePostX3Cum->Draw();
	canvCum->SaveAs(Form("%s_Cum.pdf",runName));
	canvCum->Write();
}
