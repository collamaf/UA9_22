#define AnaMuEvent_cxx
#include "AnaMuEvent.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void AnaMuEvent::Loop()
{
	cout<<"Analizzo run: "<<runName.Data()<<endl;

	double convFactor=1e3; //from rad to mrad
	const int nbin=100;
	int nprim=10000;
	double peakCenter=0;
	double peakRight=2;
	double peakLeft=-2;

	double widthCenter=0;
	double widthRight=2;
	double widthLeft=-2;
	double funcGausWidth=0.2;
	
//	double chCutoffAngle=1.8; //in mrad
	double chCutoffAngle=7.8; //in mrad

	TH1F* histoSourceX=new TH1F("histoSourceX","Source X; x [mm];",nbin,-80,80);
	TH1F* histoSourceCosX=new TH1F("histoSourceCosX","Source X-Angle; #theta [mrad]",100,-1,1);
	
	TH1F* histoSourceY=new TH1F("histoSourceY","Source Y; x [mm];",nbin,-80,80);
	TH1F* histoSourceCosY=new TH1F("histoSourceCosY","Source Y-Angle; #theta [mrad]",100,-1,1);
	
	TH2F* histoSourceXY=new TH2F("histoSourceXY","Source X-Y; x [mm];y [mm]",nbin,-80,80,nbin,-80,80);

	
//	TH1F* histoAnglePostX1=new TH1F("histoAnglePostX1","Angle post X1; #theta [mrad]",nbin,1,-1);
//	TH1F* histoAnglePostX2=new TH1F("histoAnglePostX2","Angle post X2; #theta [mrad]",nbin,1,-1);
//	TH1F* histoAnglePostX3=new TH1F("histoAnglePostX3","Angle post X3; #theta [mrad]",nbin,1,-1);
//	TH1F* histoAnglePostX3ChChCh=new TH1F("histoAnglePostX3ChChCh","Angle post X3 only ChChCh; #theta [mrad]",nbin,1,-1);
//	histoAnglePostX3ChChCh->SetLineColor(kMagenta);

	TH1F* histoXEnd=new TH1F("histoXEnd","X pos at the end; X [mm]",nbin,-80,80);
	TH1F* histoXEndCh=new TH1F("histoXEndCh","X pos at the end only Ch; X [mm]",nbin,-80,80);
	histoXEndCh->SetLineColor(kMagenta);
	TH1F* histoXEndNoCh=new TH1F("histoXEndNoCh","X pos at the end only NoCh; X [mm]",nbin,-80,80);
	histoXEndNoCh->SetLineColor(kGreen);

	THStack *histoXEndStack = new THStack("histoXEndStack","X pos at the end STACK");

	TH1F* histoAnglEnd=new TH1F("histoAnglEnd","Angle at the End; #theta_{Fin} [mrad]",nbin,-1,2.1);
	TH1F* histoAnglEndCh=new TH1F("histoAnglEndCh","Angle at the End if Channeled; #theta_{Fin} [mrad]",nbin,-1,2.1);
	
	TH1F* histoDAnglEnd=new TH1F("histoDAnglEnd","Delta Angle at the End; #theta_{Fin}-#theta_{In} [mrad]",nbin,-1,2.1);
	TH1F* histoDAnglEndCh=new TH1F("histoDAnglEndCh","Delta Angle at the End if Channeled; #theta_{Fin}-#theta_{In} [mrad]",nbin,-1,2.1);
	


//	TH1F* histoExpAnglEnd=new TH1F("histoExpAnglEnd","Experimental Angle at the End; #theta [mrad]",nbin,1,-1);
	
	TH2F* histoXCosX=new TH2F("histoXCosX","X vs CosX at the end; x [mm]; #theta_{Fin} [mrad]",nbin,-80,80,nbin,-1,2.1);
	TH2F* histoXDeltaCosX=new TH2F("histoXDeltaCosX","X vs DeltaCosX at the end; x [mm]; #theta_{Fin}-#theta_{In} [mrad]",nbin,-80,80,nbin,-1,2.1);

	TH2F* histoCosXDeltaCosX=new TH2F("histoCosXDeltaCosX","CosX vs DeltaCosX at the end; #theta_{In} [mrad]; #theta_{Fin}-#theta_{In} [mrad]",nbin,-1,1,nbin,-1,2.1);

	
	bool flagCh1=false;
	bool flagX3hit=false;
	bool flagX7hit=false;

	if (fChain == 0) return;
	
	Long64_t nentries = fChain->GetEntriesFast();
	nprim=nentries;
	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		flagCh1=false;
		flagX3hit=false;
		flagX7hit=false;
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		
		double z3=0, z7=0, x3=0, x7=0, expTheta=0, cosXin=0, cosYin=0;
		
		for (int ii=0; ii<X->size();ii++) { //Loop on each info of a given entry
			if (PlaneId->at(ii)==0) {
				histoSourceX->Fill(X->at(ii));
				histoSourceCosX->Fill(convFactor*CosX->at(ii));
				histoSourceY->Fill(Y->at(ii));
				histoSourceCosY->Fill(convFactor*CosY->at(ii));
				histoSourceXY->Fill(X->at(ii),Y->at(ii));
				cosXin=convFactor*CosX->at(ii);
				cosYin=convFactor*CosY->at(ii);
			}
			
			if (PlaneId->at(ii)==2) {
//				histoAnglePostX1->Fill(convFactor*CosX->at(ii)-cosXin);
//				if (convFactor*CosX->at(ii)>chCutoffAngle) flagCh1=true;
				if (convFactor*CosX->at(ii)-cosXin>chCutoffAngle) flagCh1=true;

			}
//			if (PlaneId->at(ii)==5) {
//				histoAnglePostX2->Fill(convFactor*CosX->at(ii));
//			}
			if (PlaneId->at(ii)==4) {
				histoXEnd->Fill(X->at(ii));
				histoAnglEnd->Fill(convFactor*CosX->at(ii));
				histoDAnglEnd->Fill(convFactor*CosX->at(ii)-cosXin);
				if (flagCh1) {
					histoAnglEndCh->Fill(convFactor*CosX->at(ii));
					histoDAnglEndCh->Fill(convFactor*CosX->at(ii)-cosXin);
					histoXEndCh->Fill(X->at(ii));
				} else {
					histoXEndNoCh->Fill(X->at(ii));

				}
				histoXCosX->Fill(X->at(ii),convFactor*CosX->at(ii));
				histoXDeltaCosX->Fill(X->at(ii),convFactor*CosX->at(ii)-cosXin);
				histoCosXDeltaCosX->Fill(cosXin,convFactor*CosX->at(ii)-cosXin);
			}
			
		}
//		expTheta=convFactor*TMath::ATan((x7-x3)/(z7-z3));
//		if (flagX3hit&&flagX7hit) histoExpAnglEnd->Fill(expTheta);
//		printf("x3=%f\tz3=%f\tx7=%f\tz7=%f\texpTheta=%f\n",x3, z3, x7, z7, expTheta);
		
		// if (Cut(ientry) < 0) continue;
	}
	
	
	TCanvas* canvBeam=new TCanvas("canvBeam","canvBeam",0,0,1000,1000);
	canvBeam->Divide(2,2);
	canvBeam->cd(1);
	histoSourceX->Draw();
	histoSourceY->Draw("samesPLC");
	canvBeam->cd(2);
	histoSourceCosX->Draw();
	canvBeam->cd(3);
	histoSourceXY->Draw("colz");
	canvBeam->cd(4);
	histoSourceCosY->Draw();
	canvBeam->SaveAs(Form("%s_Beam.pdf",runName.Data()));
	canvBeam->Write();
	
//	TCanvas* canvXAll=new TCanvas("canvXAll","canvXAll");
//	histoAnglePostX3->Draw();
//	histoAnglePostX2->Draw("samesPLC");
//	histoAnglePostX1->Draw("samesPLC");
//	canvXAll->SetLogy(1);
//	canvXAll->SaveAs(Form("%s_XAll.pdf",runName.Data()));
//	canvXAll->Write();
//
//
//	double myArea0=0;
//	double myArea0ChCh=0;
//	double myArea20=0;
//	double myAreaM20=0;
//	//	TF1* funcGaus0=new TF1("funcGaus0","[0]*exp(-0.5*((x-[1])/[2])**2)",-funcGausWidth,funcGausWidth);
//	//	TF1* funcGaus20=new TF1("funcGaus20","[0]*exp(-0.5*((x-[1])/[2])**2)",peakRight-funcGausWidth,peakRight+funcGausWidth);
//	//	TF1* funcGausM20=new TF1("funcGausM20","[0]*exp(-0.5*((x-[1])/[2])**2)",peakLeft-funcGausWidth,peakLeft+funcGausWidth);
//
//	TF1* funcGaus1_0=new TF1("funcGaus1_0","[0]*exp(-0.5*((x-[1])/[2])**2)",-funcGausWidth,funcGausWidth);
//	TF1* funcGaus1_20=new TF1("funcGaus1_20","[0]*exp(-0.5*((x-[1])/[2])**2)",peakRight-funcGausWidth,peakRight+funcGausWidth);
//
//	TF1* funcGaus2_0=new TF1("funcGaus2_0","[0]*exp(-0.5*((x-[1])/[2])**2)",-funcGausWidth,funcGausWidth);
//	TF1* funcGaus2_20=new TF1("funcGaus2_20","[0]*exp(-0.5*((x-[1])/[2])**2)",peakRight-funcGausWidth,peakRight+funcGausWidth);
//	TF1* funcGaus2_M20=new TF1("funcGaus2_M20","[0]*exp(-0.5*((x-[1])/[2])**2)",peakLeft-funcGausWidth,peakLeft+funcGausWidth);
//
//	TF1* funcGaus3_0=new TF1("funcGaus3_0","[0]*exp(-0.5*((x-[1])/[2])**2)",-funcGausWidth,funcGausWidth);
//	TF1* funcGaus3_0ChCh=new TF1("funcGaus3_0ChCh","[0]*exp(-0.5*((x-[1])/[2])**2)",-funcGausWidth,funcGausWidth);
//	TF1* funcGaus3_20=new TF1("funcGaus3_20","[0]*exp(-0.5*((x-[1])/[2])**2)",peakRight-funcGausWidth,peakRight+funcGausWidth);
//	TF1* funcGaus3_M20=new TF1("funcGaus3_M20","[0]*exp(-0.5*((x-[1])/[2])**2)",peakLeft-funcGausWidth,peakLeft+funcGausWidth);
//
//	//	TF1* funcGaus0=new TF1("funcGaus0","gaus",-funcGausWidth,funcGausWidth);
//	//	TF1* funcGaus20=new TF1("funcGaus20","gaus",peakRight-funcGausWidth,peakRight+funcGausWidth);
//	//	TF1* funcGausM20=new TF1("funcGausM20","gaus",peakLeft-2*funcGausWidth,peakLeft+2*funcGausWidth);
//
//	funcGaus1_0->SetParameter(0,histoAnglePostX1->GetBinContent(histoAnglePostX1->FindBin(widthCenter)));
//	funcGaus1_20->SetParameter(0,histoAnglePostX1->GetBinContent(histoAnglePostX1->FindBin(widthRight)));
//	funcGaus1_0->SetParLimits(0,10,10000);
//	funcGaus1_20->SetParLimits(0,10,10000);
//
////	funcGaus1_0->FixParameter(1,0);
////	funcGaus1_20->FixParameter(1,2);
//	funcGaus1_0->SetParameter(1,0);
//	funcGaus1_20->SetParameter(1,2);
//
//	funcGaus1_0->SetParameter(2,0.01);
//	funcGaus1_0->SetParLimits(2,0,0.1);
//	funcGaus1_20->SetParameter(2,0.005);
//	funcGaus1_20->SetParLimits(2,0,0.1);
//
//	cout<<"#######################\nFITTING X1\n####################"<<endl;
//	fprintf(textOut,"\n####### After X1\n");
//
//	TCanvas* canvX1=new TCanvas("canvX1","canvX1");
//	histoAnglePostX1->Draw();
//	canvX1->SetLogy(1);
//	histoAnglePostX1->Fit(funcGaus1_0,"N","",-0.05,0.05);
//	histoAnglePostX1->Fit(funcGaus1_20,"N","",peakRight-0.03,peakRight+0.03);
//	funcGaus1_0->Draw("same");
//	funcGaus1_20->Draw("same");
//	myArea0=funcGaus1_0->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus1_0->GetParameter(2)/histoAnglePostX1->GetBinWidth(1);
//	myArea20=funcGaus1_20->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus1_20->GetParameter(2)/histoAnglePostX1->GetBinWidth(1);
//
//
//	cout<<"\n####### After X1"<<endl;
//
//	printf("Frac. Am1:\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n", myArea0/nprim*100, funcGaus1_0->GetParameter(1),funcGaus1_0->GetParameter(2));
//	printf("Frac. Ch1:\t%.1f %% (%.2f [mrad], sigma: %.1e [mrad]))\n\n", myArea20/nprim*100, funcGaus1_20->GetParameter(1),funcGaus1_20->GetParameter(2));
//	fprintf(textOut,"Frac. Am1:\t%.1f %% (%.2f [mrad], sigma: %.1e [mrad]))\n", myArea0/nprim*100, funcGaus1_0->GetParameter(1),funcGaus1_0->GetParameter(2));
//	fprintf(textOut,"Frac. Ch1:\t%.1f %% (%.2f [mrad], sigma: %.1e [mrad]))\n\n", myArea20/nprim*100, funcGaus1_20->GetParameter(1),funcGaus1_20->GetParameter(2));
//	canvX1->SaveAs(Form("%s_X1.pdf",runName.Data()));
//	canvX1->Write();
//#if 1
//
//	funcGaus2_0->SetParameter(0,histoAnglePostX2->GetBinContent(histoAnglePostX2->FindBin(widthCenter)));
//	funcGaus2_20->SetParameter(0,histoAnglePostX2->GetBinContent(histoAnglePostX2->FindBin(widthRight)));
//	funcGaus2_M20->SetParameter(0,histoAnglePostX2->GetBinContent(histoAnglePostX2->FindBin(widthLeft)));
//	funcGaus2_0->SetParLimits(0,10,10000);
//	funcGaus2_20->SetParLimits(0,10,10000);
//	funcGaus2_M20->SetParLimits(0,histoAnglePostX2->GetBinContent(histoAnglePostX2->FindBin(widthLeft))*0.8,10000);
//
////	funcGaus2_0->FixParameter(1,0);
////	funcGaus2_20->FixParameter(1,2);
////	funcGaus2_M20->FixParameter(1,-2);
//	funcGaus2_0->SetParameter(1,0);
//	funcGaus2_20->SetParameter(1,2);
//	funcGaus2_M20->SetParameter(1,-2);
//
//
//	funcGaus2_0->SetParameter(2,0.01);
//	funcGaus2_20->SetParameter(2,0.005);
//	funcGaus2_M20->SetParameter(2,0.01);
//	funcGaus2_0->SetParLimits(2,0.5*histoAnglePostX2->GetBinWidth(1),0.1);
//	funcGaus2_20->SetParLimits(2,0.5*histoAnglePostX2->GetBinWidth(1),0.1);
//	funcGaus2_M20->SetParLimits(2,0.5*histoAnglePostX2->GetBinWidth(1),0.1);
//
//	cout<<"#######################\nFITTING X2\n####################"<<endl;
//	fprintf(textOut,"\n####### After X2\n");
//	TCanvas* canvX2=new TCanvas("canvX2","canvX2");
//	//	TF1* funcGaus0=new TF1("funcGaus0","gaus",-0.05,0.05);
//	//	TF1* funcGaus20=new TF1("funcGaus20","gaus",2-0.05,2+0.05);
//	histoAnglePostX2->Draw();
//	canvX2->SetLogy(1);
//	histoAnglePostX2->Fit(funcGaus2_0,"N","",-0.05,0.05);
//	histoAnglePostX2->Fit(funcGaus2_20,"N","",peakRight-0.05,peakRight+0.05);
//	//	histoAnglePostX2->Fit(funcGausM20,"N","",-2.04,-1.96);
//	histoAnglePostX2->Fit(funcGaus2_M20,"N","",peakLeft-0.04,peakLeft+0.04);
//	funcGaus2_0->Draw("same");
//	funcGaus2_20->Draw("same");
//	funcGaus2_M20->Draw("same");
//
//	myArea0=funcGaus2_0->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus2_0->GetParameter(2)/histoAnglePostX2->GetBinWidth(1);
//	myArea20=funcGaus2_20->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus2_20->GetParameter(2)/histoAnglePostX2->GetBinWidth(1);
//	myAreaM20=funcGaus2_M20->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus2_M20->GetParameter(2)/histoAnglePostX2->GetBinWidth(1);
//
//	//	cout<<"\n####### After X2\nAm. Frac.: "<<myArea0/nprim*100<<endl<<"Ch.1 Frac.:"<<myArea20/nprim*100<<endl<<"Ch.1 Frac.:"<<myAreaM20/nprim*100<<endl<<endl<<endl;
//	cout<<"\n####### After X2"<<endl;
//	//	cout<<"Frac. Am1:\t"<<myArea0/nprim*100<<endl;
//	//	cout<<"Frac. Ch1+Am2:\t"<<myArea20/nprim*100<<endl;
//	//	cout<<"Frac. Ch1+Ch2:\t"<<myAreaM20/nprim*100<<endl<<endl<<endl;
//	printf("Frac. Am1:\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n", myArea0/nprim*100, funcGaus2_0->GetParameter(1),funcGaus2_0->GetParameter(2));
//	printf("Frac. Ch1+Am2:\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n", myArea20/nprim*100, funcGaus2_20->GetParameter(1),funcGaus2_20->GetParameter(2));
//	printf("Frac. Ch1+Ch2:\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n\n", myAreaM20/nprim*100, funcGaus2_M20->GetParameter(1),funcGaus2_M20->GetParameter(2));
//	fprintf(textOut,"Frac. Am1:\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n", myArea0/nprim*100, funcGaus2_0->GetParameter(1),funcGaus2_0->GetParameter(2));
//	fprintf(textOut,"Frac. Ch1+Am2:\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n", myArea20/nprim*100, funcGaus2_20->GetParameter(1),funcGaus2_20->GetParameter(2));
//	fprintf(textOut,"Frac. Ch1+Ch2:\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n\n", myAreaM20/nprim*100, funcGaus2_M20->GetParameter(1),funcGaus2_M20->GetParameter(2));
//	canvX2->SaveAs(Form("%s_X2.pdf",runName.Data()));
//	canvX2->Write();
//#endif
//
//#if 1
//
//	funcGaus3_0->SetParameter(0,histoAnglePostX3->GetBinContent(histoAnglePostX3->FindBin(widthCenter)));
//	funcGaus3_0ChCh->SetParameter(0,histoAnglePostX3->GetBinContent(histoAnglePostX3->FindBin(widthCenter)));
//	funcGaus3_20->SetParameter(0,histoAnglePostX3->GetBinContent(histoAnglePostX3->FindBin(widthRight)));
//	funcGaus3_M20->SetParameter(0,histoAnglePostX3->GetBinContent(histoAnglePostX3->FindBin(widthLeft)));
//
//	funcGaus3_0->SetParLimits(0,10,10000);
//	funcGaus3_0ChCh->SetParLimits(0,10,10000);
//	funcGaus3_20->SetParLimits(0,10,10000);
//	funcGaus3_M20->SetParLimits(0,10,10000);
//
////	funcGaus3_0->FixParameter(1,0);
////	funcGaus3_0ChCh->FixParameter(1,0);
////	funcGaus3_20->FixParameter(1,2);
////	funcGaus3_M20->FixParameter(1,-2);
//	funcGaus3_0->SetParameter(1,0);
//	funcGaus3_0ChCh->SetParameter(1,0);
//	funcGaus3_20->SetParameter(1,2);
//	funcGaus3_M20->SetParameter(1,-2);
//
//	funcGaus3_0->SetParameter(2,0.01);
//	funcGaus3_0ChCh->SetParameter(2,0.01);
//	funcGaus3_20->SetParameter(2,0.005);
//	funcGaus3_M20->SetParameter(2,0.01);
//	funcGaus3_0->SetParLimits(2,0,0.1);
//	funcGaus3_0ChCh->SetParLimits(2,0,0.1);
//	funcGaus3_20->SetParLimits(2,0,0.1);
//	funcGaus3_M20->SetParLimits(2,0,0.1);
//
//	cout<<"#######################\nFITTING X3\n####################"<<endl;
//	fprintf(textOut,"\n####### After X3\n");
//	TCanvas* canvX3=new TCanvas("canvX3","canvX3");
//	histoAnglePostX3->Draw();
//	histoAnglePostX3ChChCh->Draw("sames");
//	canvX3->SetLogy(1);
//	histoAnglePostX3->Fit(funcGaus3_0,"N","",-0.05,0.05);
//	histoAnglePostX3ChChCh->Fit(funcGaus3_0ChCh,"N","",-0.05,0.05);
//	histoAnglePostX3->Fit(funcGaus3_20,"N","",peakRight-0.05,peakRight+0.05);
//	//	histoAnglePostX2->Fit(funcGausM20,"N","",-2.04,-1.96);
//	histoAnglePostX3->Fit(funcGaus3_M20,"N","",peakLeft-0.04,peakLeft+0.04);
//	funcGaus3_0->Draw("same");
//	funcGaus3_0ChCh->SetLineColor(kMagenta);
//	funcGaus3_0ChCh->Draw("same");
//	funcGaus3_20->Draw("same");
//	funcGaus3_M20->Draw("same");
//
//	myArea0=funcGaus3_0->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus3_0->GetParameter(2)/histoAnglePostX3->GetBinWidth(1);
//	myArea0ChCh=funcGaus3_0ChCh->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus3_0ChCh->GetParameter(2)/histoAnglePostX3ChChCh->GetBinWidth(1);
//	myArea20=funcGaus3_20->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus3_20->GetParameter(2)/histoAnglePostX3->GetBinWidth(1);
//	myAreaM20=funcGaus3_M20->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus3_M20->GetParameter(2)/histoAnglePostX3->GetBinWidth(1);
//
//	//	cout<<"\n####### After X3\nAm. Frac.: "<<myArea0/nprim*100<<endl<<"Ch.1 Frac.:"<<myArea20/nprim*100<<endl<<"Ch.1 Frac.:"<<myAreaM20/nprim*100<<endl<<endl<<endl;
//	cout<<"\n####### After X3"<<endl;
//	//	cout<<"Am. Frac.: "<<myArea0/nprim*100<<endl;
//	//	cout<<"Ch.1 Frac.:"<<myArea20/nprim*100<<endl;
//	//	cout<<"Ch.1 Frac.:"<<myAreaM20/nprim*100<<endl<<endl<<endl;
//	printf("Frac. Am1+Am3|Ch1+Ch2+Ch3:\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n", myArea0/nprim*100, funcGaus3_0->GetParameter(1), funcGaus3_0->GetParameter(2));
//	printf("Frac. Ch1+Ch2+Ch3:\t\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n", myArea0ChCh/nprim*100, funcGaus3_0ChCh->GetParameter(1), funcGaus3_0ChCh->GetParameter(2));
//	printf("Frac. Ch1+Am2:\t\t\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n", myArea20/nprim*100, funcGaus3_20->GetParameter(1),funcGaus3_20->GetParameter(2));
//	printf("Frac. Ch1+Ch2+Am3:\t\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n\n", myAreaM20/nprim*100, funcGaus3_M20->GetParameter(1), funcGaus3_M20->GetParameter(2));
//	fprintf(textOut,"Frac. Am1+Am3|Ch1+Ch2+Ch3:\t%.1f %% (mean: %.1f [mrad], sigma: %.1e [mrad])\n", myArea0/nprim*100, funcGaus3_0->GetParameter(1), funcGaus3_0->GetParameter(2));
//	fprintf(textOut,"Frac. Ch1+Ch2+Ch3:\t\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n", myArea0ChCh/nprim*100, funcGaus3_0ChCh->GetParameter(1), funcGaus3_0ChCh->GetParameter(2));
//	fprintf(textOut,"Frac. Ch1+Am2:\t\t\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n", myArea20/nprim*100, funcGaus3_20->GetParameter(1), funcGaus3_20->GetParameter(2));
//	fprintf(textOut,"Frac. Ch1+Ch2+Am3:\t\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n\n", myAreaM20/nprim*100, funcGaus3_M20->GetParameter(1), funcGaus3_M20->GetParameter(2));
//	canvX3->SaveAs(Form("%s_X3.pdf",runName.Data()));
//	canvX3->Write();
//#endif
	histoSourceX->Write();
	histoSourceCosX->Write();
	histoSourceY->Write();
	histoSourceCosY->Write();
	histoAnglEnd->Write();
	histoAnglEndCh->Write();
	histoDAnglEnd->Write();
	histoDAnglEndCh->Write();
//	histoAnglePostX1->Write();
//	histoAnglePostX2->Write();
//	histoAnglePostX3->Write();
	
//	TCanvas* canvCum=new TCanvas("canvCum","canvCum",0,0,400,1200);
//	canvCum->Divide(1,3);
//	TH1F* histoAnglePostX1Cum=(TH1F*)histoAnglePostX1->GetCumulative(1);
//	histoAnglePostX1Cum->Scale(1/histoAnglePostX1Cum->GetMaximum());
//	histoAnglePostX1Cum->Write();
//
//	TH1F* histoAnglePostX2Cum=(TH1F*)histoAnglePostX2->GetCumulative(1);
//	histoAnglePostX2Cum->Scale(1/histoAnglePostX2Cum->GetMaximum());
//	histoAnglePostX2Cum->Write();
//
//	TH1F* histoAnglePostX3Cum=(TH1F*)histoAnglePostX3->GetCumulative(1);
//	histoAnglePostX3Cum->Scale(1/histoAnglePostX3Cum->GetMaximum());
//	histoAnglePostX3Cum->Write();
//
//	TH1F* histoAnglePostX3ChChChCum=(TH1F*)histoAnglePostX3ChChCh->GetCumulative(1);
//	histoAnglePostX3ChChChCum->Scale(1/histoAnglePostX3ChChChCum->GetMaximum());
//	histoAnglePostX3ChChChCum->Write();
//
//	canvCum->cd(1);
//	histoAnglePostX1Cum->SetStats(0);
//	histoAnglePostX1Cum->Draw();
//	canvCum->cd(2);
//	histoAnglePostX2Cum->SetStats(0);
//	histoAnglePostX2Cum->Draw();
//	canvCum->cd(3);
//	histoAnglePostX3Cum->SetStats(0);
//	histoAnglePostX3Cum->Draw();
//	histoAnglePostX3ChChChCum->SetStats(0);
//	histoAnglePostX3ChChChCum->Draw("same");
//	canvCum->SaveAs(Form("%s_Cum.pdf",runName.Data()));
//	canvCum->Write();
//
//
//	TCanvas* canvX3ChChCh=new TCanvas("canvX3ChChCh","canvX3ChChCh");
//	histoAnglePostX3->Draw();
//	histoAnglePostX3ChChCh->Draw("sames");
//	canvX3ChChCh->BuildLegend();
//	canvX3ChChCh->Write();
//	canvX3ChChCh->SetLogy();
//	canvX3ChChCh->SaveAs(Form("%s_X3ChChCh.pdf",runName.Data()));

	TCanvas* canvPosEnd=new TCanvas("canvPosEnd","canvPosEnd");
	histoXEnd->Write();
	histoXEndCh->Write();
	histoXEndNoCh->Write();
	histoXEnd->DrawCopy();
	histoXEndCh->DrawCopy("sames");
	histoXEndNoCh->DrawCopy("sames");
	canvPosEnd->BuildLegend();
	canvPosEnd->Write();
	canvPosEnd->SetLogy();
	canvPosEnd->SaveAs(Form("%s_PosEnd.pdf",runName.Data()));
	
	TCanvas* canvPosStack=new TCanvas("canvPosStack","canvPosStack");
	histoXEndCh->SetFillColor(kMagenta);
	histoXEndNoCh->SetFillColor(kGreen);
//	histoXEndStack->Add(histoXEnd);
	histoXEndStack->Add(histoXEndNoCh);
	histoXEndStack->Add(histoXEndCh);
	histoXEndStack->Draw();
	histoXEndStack->Write();
	canvPosStack->SaveAs(Form("%s_PosStack.pdf",runName.Data()));

	TCanvas* canvXCosX=new TCanvas("canvXCosX","canvXCosX");
	histoXCosX->Draw("colz");
	histoXCosX->Write();
	canvXCosX->SaveAs(Form("%s_EndXCosX.pdf",runName.Data()));
	
	TCanvas* canvXDeltaCosX=new TCanvas("canvXDeltaCosX","canvXDeltaCosX");
	histoXDeltaCosX->Draw("colz");
	histoXDeltaCosX->Write();
	canvXDeltaCosX->SaveAs(Form("%s_EndXDeltaCosX.pdf",runName.Data()));
	
	TCanvas* canvCosXDeltaCosX=new TCanvas("canvCosXDeltaCosX","canvCosXDeltaCosX");
	histoCosXDeltaCosX->Draw("colz");
	histoCosXDeltaCosX->Write();
	canvCosXDeltaCosX->SaveAs(Form("%s_EndCosXDeltaCosX.pdf",runName.Data()));

//
//	TCanvas* canvExpTheta=new TCanvas("canvExpTheta","canvExpTheta");
//	histoExpAnglEnd->Draw();
//	histoExpAnglEnd->Write();
//	canvExpTheta->SetLogy(1);
//	canvExpTheta->SaveAs(Form("%s_ExpTheta.pdf",runName.Data()));
//	canvExpTheta->Write();
	
//
//	TCanvas* canvThetaEnd=new TCanvas("canvThetaEnd","canvThetaEnd");
//	histoAnglEnd->Draw();
//	histoAnglEnd->Write();
//	canvThetaEnd->SetLogy(1);
//	canvThetaEnd->SaveAs(Form("%s_ThetaEnd.pdf",runName.Data()));
//	canvThetaEnd->Write();
//
}
