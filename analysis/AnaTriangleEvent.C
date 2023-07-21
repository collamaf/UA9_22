#define AnaTriangleEvent_cxx
#include "AnaTriangleEvent.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void AnaTriangleEvent::Loop()
{
	cout<<"Analizzo run: "<<runName.Data()<<endl;

	double convFactor=1e3; //from rad to mrad
	const int nbin=200;
	int nprim=10000;
	double peakCenter=0;
	double peakRight=2;
	double peakLeft=-2;

	double widthCenter=0;
	double widthRight=2;
	double widthLeft=-2;
	double funcGausWidth=0.2;
	
	double chCutoffAngle=0.8; //fraction of bending angle to identify a channeled particle
    double thetaBending1=2; //in mrad
    double thetaBending2=3.6; //in mrad
    double thetaBending3=1.6; //in mrad
    
    double x1SizeX=1.5; //in mm - to apply xcut
    
    bool printFlag=true;
    
    const double xMax=6;
    const double xMin=-6;
    const double thetaXBeamMax=0.2;
    const double thetaXBeamMin=-0.2;
    double thetaXMax=2.1;
    double thetaXMin=-2.1;
    double XMax=71;
    double XMin=-10;
    bool isOffAxisTriangle=true;
    if (isOffAxisTriangle) {
        thetaXMax=4.1;
        thetaXMin=-4.1;
        thetaBending1=2; //potrebbero essere diversi
        thetaBending2=3.6;
        thetaBending3=1.6;
    }
    
	TH1F* histoSourceX=new TH1F("histoSourceX","Source X; x [mm];",nbin,xMin,xMax);
    TH1F* histoSourceCosX=new TH1F("histoSourceCosX","Source Angle Y; #theta [mrad]",100,thetaXBeamMin, thetaXBeamMax);
    TH1F* histoSourceY=new TH1F("histoSourceY","Source Y; y [mm];",nbin,xMin,xMax);
    TH1F* histoSourceCosY=new TH1F("histoSourceCosY","Source Angle Y; #theta [mrad]",100,thetaXBeamMin, thetaXBeamMax);
	
    TH1F* histoAnglePostX1=new TH1F("histoAnglePostX1","Angle post X1; #theta [mrad]",nbin,thetaXMin, thetaXMax);
    TH1F* histoAnglePostX2=new TH1F("histoAnglePostX2","Angle post X2; #theta [mrad]",nbin,thetaXMin, thetaXMax);
    TH1F* histoAnglePostX3=new TH1F("histoAnglePostX3","Angle post X3; #theta [mrad]",nbin,thetaXMin, thetaXMax);
    TH1F* histoAnglePostX3Ch=new TH1F("histoAnglePostX3Ch","Angle post X3 if Ch; #theta [mrad]",nbin,thetaXMin, thetaXMax);
    TH1F* histoAnglePostX3ChCh=new TH1F("histoAnglePostX3ChCh","Angle post X3 if ChCh; #theta [mrad]",nbin,thetaXMin, thetaXMax);
    TH1F* histoAnglePostX3ChChCh=new TH1F("histoAnglePostX3ChChCh","Angle post X3 if ChChCh; #theta [mrad]",nbin,thetaXMin, thetaXMax);
	histoAnglePostX3ChChCh->SetLineColor(kMagenta);
    TH1F* histoAnglePostX3OCh=new TH1F("histoAnglePostX3OCh","Angle post X3 only Ch; #theta [mrad]",nbin,thetaXMin, thetaXMax);
    TH1F* histoAnglePostX3OChCh=new TH1F("histoAnglePostX3OChCh","Angle post X3 only ChCh; #theta [mrad]",nbin,thetaXMin, thetaXMax);
    TH1F* histoAnglePostX3OChChCh=new TH1F("histoAnglePostX3OChChCh","Angle post X3 only ChChCh; #theta [mrad]",nbin,thetaXMin, thetaXMax);
    TH1F* histoAnglePostX3OAmChCh=new TH1F("histoAnglePostX3OAmChCh","Angle post X3 only AmChCh; #theta [mrad]",nbin,thetaXMin, thetaXMax);
    TH1F* histoAnglePostX3OAmChAm=new TH1F("histoAnglePostX3OAmChAm","Angle post X3 only AmChAm; #theta [mrad]",nbin,thetaXMin, thetaXMax);

    TH1F* histoXPostX1=new TH1F("histoXPostX1","X post X1; x [mm]",nbin,1,-1);
    TH1F* histoXPreX2=new TH1F("histoXPreX2","X pre X2; x [mm]",nbin,1,-1);
    TH1F* histoXPostX2=new TH1F("histoXPostX2","X post X2; x [mm]",nbin,1,-1);
    TH1F* histoXPreX3=new TH1F("histoXPreX3","X pre X3; x [mm]",nbin,1,-1);
    TH1F* histoXPostX3=new TH1F("histoXPostX3","X post X3; x [mm]",nbin,1,-1);
    TH1F* histoXPostX3Ch=new TH1F("histoXPostX3Ch","X post X3 if Ch; x [mm]",nbin,1,-1);
    TH1F* histoXPostX3ChCh=new TH1F("histoXPostX3ChCh","X post X3 if ChCh; x [mm]",nbin,1,-1);
    TH1F* histoXPostX3ChChCh=new TH1F("histoXPostX3ChChCh","X post X3 if ChChCh; x [mm]",nbin,1,-1);
    TH1F* histoXEnd=new TH1F("histoXEnd","X pos at the end; X [mm]",nbin, XMin, XMax);
    TH1F* histoXEndChChCh=new TH1F("histoXEndChChCh","X pos at the end only ChChCh; x [mm]",nbin,XMin, XMax);
    TH1F* histoXEndChNoAm=new TH1F("histoXEndChNoAm","X pos at the end only ChNoAm; x [mm]",nbin,XMin, XMax);
    TH1F* histoXEndAmAmNo=new TH1F("histoXEndAmAmNo","X pos at the end only AmAmNo; x [mm]",nbin,XMin, XMax);
    TH1F* histoXEndAmChAm=new TH1F("histoXEndAmChAm","X pos at the end only AmChAM; x [mm]",nbin,XMin, XMax);
//	histoXEndChChCh->SetLineColor(kMagenta);
    TH1F* histoXEndAmChCh=new TH1F("histoXEndAmChCh","X pos at the end only AmChCh; x [mm]",nbin,XMin, XMax);

	TH1F* histoExpAnglEnd=new TH1F("histoExpAnglEnd","Experimental Angle at the End; #theta [mrad]",nbin,1,-1);

	
    bool flagCh1=false;
    bool flagCh2=false;
	bool flagCh3=false;
	bool flagPlane3hit=false;
	bool flagPlane7hit=false;

	if (fChain == 0) return;
	
	Long64_t nentries = fChain->GetEntriesFast();
	nprim=nentries;
	Long64_t nbytes = 0, nb = 0;
    
    // Codifica piani per caso base
//    int planeIdSource=0;
//    int planeIdPostX1=2;
//    int planeIdPostX2=5;
//    int planeIdPostX3=3;
//    int planeIdLast=7;
    
    // Codifica piani per caso 2023 - buono anche per triangolo disassato
    int planeIdSource=0;
    int planeIdPreX1=1;
    int planeIdPostX1=6;
    int planeIdPreX2=2;
    int planeIdPostX2=3;
    int planeIdPreX3=7;
    int planeIdPostX3=4;
    int planeIdLast=5;
    
    double thetaX1In;
    double thetaX1Out;
    double thetaX2In;
    double thetaX2Out;
    double thetaX3In;
    double thetaX3Out;
    
    
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
        flagCh1=false;
        flagCh2=false;
		flagCh3=false;
		flagPlane3hit=false;
		flagPlane7hit=false;
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		
		double z3=0, z7=0, x3=0, x7=0, expTheta=0;
        cout<<"\nEntro in evento: "<<jentry<<endl;

		for (int ii=0; ii<X->size();ii++) { //Loop on each info of a given entry
			if (PlaneId->at(ii)==planeIdSource) {
                histoSourceX->Fill(X->at(ii));
                histoSourceCosX->Fill(convFactor*CosX->at(ii));
                histoSourceY->Fill(Y->at(ii));
				histoSourceCosY->Fill(convFactor*CosY->at(ii));
			}
            // X 1
            if (PlaneId->at(ii)==planeIdPreX1) {
                thetaX1In=convFactor*CosX->at(ii);
                if (fabs(X->at(ii))>x1SizeX*0.5) { //Check if is in X acceptance of X1
                    if (printFlag) cout<<"Traccia che NON entra in X1: "<< jentry<<endl;
                    if (applyXCut) break;
                }
            }
            if (PlaneId->at(ii)==planeIdPostX1) {
                histoAnglePostX1->Fill(convFactor*CosX->at(ii));
                histoXPostX1->Fill(X->at(ii));
                thetaX1Out=convFactor*CosX->at(ii);
                double thetaX1Diff=thetaX1Out-thetaX1In;
                if (fabs(thetaX1Diff)>chCutoffAngle*thetaBending1) {
                    flagCh1=true;
                    cout<<"Fatto CHX1! "<< jentry<<endl;
                }
            }

            // X 2
            if (PlaneId->at(ii)==planeIdPreX2) {
                histoXPreX2->Fill(X->at(ii));
                thetaX2In=convFactor*CosX->at(ii);
            }
			if (PlaneId->at(ii)==planeIdPostX2) {
				histoAnglePostX2->Fill(convFactor*CosX->at(ii));
                histoXPostX2->Fill(X->at(ii));
                thetaX2Out=convFactor*CosX->at(ii);
                double thetaX2Diff=thetaX2Out-thetaX2In;
                if (fabs(thetaX2Diff)>chCutoffAngle*thetaBending2){
                    flagCh2=true;
                    cout<<"Fatto CHX2! "<< jentry<<endl;
                };
                if (printFlag) printf("PostX2##, AngIn:\t%.3e mRad\tAngOut:\t%.3e mRad\tDiff:\t%.3e mRad\tFlagCH2:%d\n", thetaX2In,thetaX2Out, thetaX2Diff,flagCh2);
			}
            
            // X 3
            if (PlaneId->at(ii)==planeIdPreX3) {
                histoXPreX3->Fill(X->at(ii));
                thetaX3In=convFactor*CosX->at(ii);
            }
			if (PlaneId->at(ii)==planeIdPostX3) {
				flagPlane3hit=true; //significa che ha toccato il PIANO 3
				x3=X->at(ii);
				z3=Z->at(ii); //fisso in realtà
				histoAnglePostX3->Fill(convFactor*CosX->at(ii));
                thetaX3Out=convFactor*CosX->at(ii);
                double thetaX3Diff=thetaX3Out-thetaX3In;
                if (fabs(thetaX3Diff)>chCutoffAngle*thetaBending3) {
                    flagCh3=true;
                    cout<<"Fatto CHX3! "<< jentry<<endl;
                }
//                if (thetaX3Out-thetaX3In!=0) {
                    if (printFlag) printf("PostX3##, AngIn:\t%.3e mRad\tAngOut:\t%.3e mRad\tDiff:\t%.3e mRad\tFlagCH3:%d\n", thetaX3In,thetaX3Out, thetaX3Out-thetaX3In,flagCh3);
//                } else {
//                    if (printFlag) printf("PostX3, AngIn:\t%.3e\tAngOut:\t%.3e\tDiff:\t%.3e\n", thetaX3In,thetaX3Out, thetaX3Out-thetaX3In);
//                }

//                    cout<<"ThetaX3Out: "<<thetaX3Out<<" In: "<<thetaX3In<<", Diff: "<<thetaX3Out-thetaX3In<<endl;
                
                //Fill histos for different combination of Ch (NOT EXCLUSIVE)
                if (flagCh1)  {
                    histoXPostX3Ch->Fill(X->at(ii));
                    histoAnglePostX3Ch->Fill(convFactor*CosX->at(ii));
                }
                if (flagCh1&&flagCh2)  {
                    histoXPostX3ChCh->Fill(X->at(ii));
                    histoAnglePostX3ChCh->Fill(convFactor*CosX->at(ii));
                }
                if (flagCh1&&flagCh2&&flagCh3)  {
                    histoXPostX3ChChCh->Fill(X->at(ii));
                    histoAnglePostX3ChChCh->Fill(convFactor*CosX->at(ii));
                }
                
                
                //Fill histos for different combination of Ch (EXCLUSIVE -> "O"="OnlyCH1" etc)

                if (flagCh1&&flagCh2&&flagCh3)  {
                    //                    histoXPostX3ChChCh->Fill(X->at(ii));
                    histoAnglePostX3OChChCh->Fill(convFactor*CosX->at(ii));
                } else if (!flagCh1&&flagCh2&&flagCh3)  {
                    histoAnglePostX3OAmChCh->Fill(convFactor*CosX->at(ii));
                } else if (!flagCh1&&flagCh2&&!flagCh3)  {
                    histoAnglePostX3OAmChAm->Fill(convFactor*CosX->at(ii));
                } else if (flagCh1&&flagCh2)  {
                    histoAnglePostX3OChCh->Fill(convFactor*CosX->at(ii));
                } else if (flagCh1)  {
                    histoAnglePostX3OCh->Fill(convFactor*CosX->at(ii));
                }
                histoXPostX3->Fill(X->at(ii));
            }
            
            // LAST PLANE
            if (PlaneId->at(ii)==planeIdLast) {
                flagPlane7hit=true;
                x7=X->at(ii);
                z7=Z->at(ii); //fisso in realtà
                histoXEnd->Fill(X->at(ii));
                
                
//                cout<<"INSALATA FLAG: "<<flagCh1<<" "<<flagCh2<<" "<<flagCh3<<endl;
                if (flagCh1&&flagCh2&&flagCh3)  {
                    histoXEndChChCh->Fill(X->at(ii));
                }
               else  if (!flagCh1&&flagCh2&&flagCh3)  {
                    histoXEndAmChCh->Fill(X->at(ii));
                }
                else if (!flagCh1&&flagCh2&&!flagCh3)  {
                    histoXEndAmChAm->Fill(X->at(ii));
                }
                else if (flagCh1&&flagCh2&&!flagCh3)  {
                    //none
                }
                else if (flagCh1&&!flagCh2&&!flagCh3)  {
                    histoXEndChNoAm->Fill(X->at(ii));
                } else
                 if (!flagCh1&&!flagCh2&&!flagCh3) {
                    histoXEndAmAmNo->Fill(X->at(ii));
                }

			}
		}
		expTheta=convFactor*TMath::ATan((x7-x3)/(z7-z3));
		if (flagPlane3hit&&flagPlane7hit) histoExpAnglEnd->Fill(expTheta);
//		printf("x3=%f\tz3=%f\tx7=%f\tz7=%f\texpTheta=%f\n",x3, z3, x7, z7, expTheta);
		
		// if (Cut(ientry) < 0) continue;
	}
	
	
	TCanvas* canvBeam=new TCanvas("canvBeam","canvBeam",0,0,600,800);
	canvBeam->Divide(1,2);
	canvBeam->cd(1);
    histoSourceX->Draw();
    histoSourceY->SetLineColor(kRed);
    histoSourceY->Draw("sames");
	canvBeam->cd(2);
	histoSourceCosX->Draw();
    histoSourceCosY->SetLineColor(kRed);
    histoSourceCosY->Draw("sames");
    canvBeam->SaveAs(Form("%s_Beam.pdf",runName.Data()));
	canvBeam->Write();
	
	TCanvas* canvAngAll=new TCanvas("canvAngAll","canvAngAll");
	histoAnglePostX3->Draw("PLC");
	histoAnglePostX2->Draw("samesPLC");
	histoAnglePostX1->Draw("samesPLC");
    canvAngAll->BuildLegend();
    canvAngAll->SetLogy(1);
    canvAngAll->SaveAs(Form("%s_AngAll.pdf",runName.Data()));
    canvAngAll->Write();
    
    TCanvas* canvX3All=new TCanvas("canvX3All","canvX3All");
//    histoXPostX3->SetLineColor(kRed);
    histoXPostX3->Draw("PLC");
    histoXPostX3ChChCh->SetLineColor(kRed);
    histoXPostX3ChChCh->Draw("sames");
    histoXPreX3->Draw("samesPLC");
    histoXPostX2->Draw("samesPLC");
    histoXPreX2->Draw("samesPLC");
//    histoXPostX1->SetLineColor(kBlue);
    histoXPostX1->Draw("samesPLC");
    canvX3All->SetLogy(1);
    canvX3All->BuildLegend();
    canvX3All->SaveAs(Form("%s_XAll.pdf",runName.Data()));
    canvX3All->Write();
    
    
    TCanvas* canvX3IfCh=new TCanvas("canvX3IfCh","canvX3IfCh"); //Posizione post X3 se ha fatto ch, chch o chchch
//    histoXPostX3->SetLineColor(kRed);
    histoXPostX3->Draw("PLC");
    histoXPostX3ChChCh->SetLineColor(kRed);
    histoXPostX3ChChCh->Draw("sames");
//    histoXPostX3ChCh->SetLineColor(kGreen);
    histoXPostX3ChCh->Draw("samesPLC");
//    histoXPostX3Ch->SetLineColor(kCyan);
    histoXPostX3Ch->Draw("samesPLC");
    canvX3IfCh->SetLogy(1);
    canvX3IfCh->BuildLegend();
    canvX3IfCh->SaveAs(Form("%s_XIfCh.pdf",runName.Data()));
    canvX3IfCh->Write();
	
    
    TCanvas* canvAngX3IfCh=new TCanvas("canvAngX3IfCh","canvAngX3IfCh",0,0,600,800);
    canvAngX3IfCh->Divide(1,2);
    
    TVirtualPad* padAngIfCh = canvAngX3IfCh->cd(1);
//    TCanvas* canvAngIfCh=new TCanvas("canvAngIfCh","canvAngIfCh");
//    histoXPostX3->SetLineColor(kRed);
    histoAnglePostX3->Draw("PLC");
    histoAnglePostX3ChChCh->SetLineColor(kRed);
    histoAnglePostX3ChChCh->Draw("sames");
//    histoAnglePostX3ChCh->SetLineColor(kGreen);
    histoAnglePostX3ChCh->Draw("samesPLC");
//    histoAnglePostX3Ch->SetLineColor(kCyan);
    histoAnglePostX3Ch->Draw("samesPLC");
    padAngIfCh->SetLogy(1);
    padAngIfCh->BuildLegend();
    padAngIfCh->SaveAs(Form("%s_AngX3IfCh.pdf",runName.Data()));
//    padAngIfCh->Write();
    
    
//    TCanvas* canvAngOCh=new TCanvas("canvAngOCh","canvAngOCh"); //Posizione post X3 se ha fatto SOLO ch, SOLO chch o SOLO chchch
//    histoXPostX3->SetLineColor(kRed);
    TVirtualPad* padAngOCh = canvAngX3IfCh->cd(2);
    histoAnglePostX3->Draw();
    histoAnglePostX3OChChCh->SetLineColor(kRed);
    histoAnglePostX3OChChCh->Draw("sames");
    histoAnglePostX3OChCh->SetLineColor(kGreen);
    histoAnglePostX3OChCh->Draw("sames");
    histoAnglePostX3OCh->SetLineColor(kCyan);
    histoAnglePostX3OCh->Draw("sames");
    histoAnglePostX3OAmChCh->SetLineColor(kMagenta);
    histoAnglePostX3OAmChCh->Draw("sames");
    histoAnglePostX3OAmChAm->SetLineColor(kBlue);
    histoAnglePostX3OAmChAm->Draw("sames");
    padAngOCh->SetLogy(1);
    padAngOCh->BuildLegend();
    padAngOCh->SaveAs(Form("%s_AngOCh.pdf",runName.Data()));
    canvAngX3IfCh->Write();
    

	double myArea0=0;
	double myArea0ChCh=0;
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
	TF1* funcGaus3_0ChCh=new TF1("funcGaus3_0ChCh","[0]*exp(-0.5*((x-[1])/[2])**2)",-funcGausWidth,funcGausWidth);
	TF1* funcGaus3_20=new TF1("funcGaus3_20","[0]*exp(-0.5*((x-[1])/[2])**2)",peakRight-funcGausWidth,peakRight+funcGausWidth);
	TF1* funcGaus3_M20=new TF1("funcGaus3_M20","[0]*exp(-0.5*((x-[1])/[2])**2)",peakLeft-funcGausWidth,peakLeft+funcGausWidth);
	
	//	TF1* funcGaus0=new TF1("funcGaus0","gaus",-funcGausWidth,funcGausWidth);
	//	TF1* funcGaus20=new TF1("funcGaus20","gaus",peakRight-funcGausWidth,peakRight+funcGausWidth);
	//	TF1* funcGausM20=new TF1("funcGausM20","gaus",peakLeft-2*funcGausWidth,peakLeft+2*funcGausWidth);
	
	funcGaus1_0->SetParameter(0,histoAnglePostX1->GetBinContent(histoAnglePostX1->FindBin(widthCenter)));
	funcGaus1_20->SetParameter(0,histoAnglePostX1->GetBinContent(histoAnglePostX1->FindBin(widthRight)));
	funcGaus1_0->SetParLimits(0,10,10000);
	funcGaus1_20->SetParLimits(0,10,10000);
	
//	funcGaus1_0->FixParameter(1,0);
//	funcGaus1_20->FixParameter(1,2);
	funcGaus1_0->SetParameter(1,0);
	funcGaus1_20->SetParameter(1,2);
	
	funcGaus1_0->SetParameter(2,0.01);
	funcGaus1_0->SetParLimits(2,0,0.1);
	funcGaus1_20->SetParameter(2,0.005);
	funcGaus1_20->SetParLimits(2,0,0.1);

	if (printFlag) cout<<"#######################\nFITTING X1\n####################"<<endl;
    if (printFlag) fprintf(textOut,"\n####### After X1\n");

    TCanvas* canvXAllSingle=new TCanvas("canvXAllSingle","canvXAllSingle",0,0,600,1200);
    canvXAllSingle->Divide(1,3);
    canvXAllSingle->cd(1);

//    TCanvas* canvX1=new TCanvas("canvX1","canvX1");
	histoAnglePostX1->Draw();
    TVirtualPad* padX1 = canvXAllSingle->cd(1);
    padX1->SetLogy(1);
	histoAnglePostX1->Fit(funcGaus1_0,"N","",-0.05,0.05);
	histoAnglePostX1->Fit(funcGaus1_20,"N","",peakRight-0.03,peakRight+0.03);
	funcGaus1_0->Draw("same");
	funcGaus1_20->Draw("same");
	myArea0=funcGaus1_0->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus1_0->GetParameter(2)/histoAnglePostX1->GetBinWidth(1);
	myArea20=funcGaus1_20->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus1_20->GetParameter(2)/histoAnglePostX1->GetBinWidth(1);
	
	
    if (printFlag) cout<<"\n####### After X1"<<endl;
	
    if (printFlag) printf("Frac. Am1:\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n", myArea0/nprim*100, funcGaus1_0->GetParameter(1),funcGaus1_0->GetParameter(2));
    if (printFlag) printf("Frac. Ch1:\t%.1f %% (%.2f [mrad], sigma: %.1e [mrad]))\n\n", myArea20/nprim*100, funcGaus1_20->GetParameter(1),funcGaus1_20->GetParameter(2));
    if (printFlag) fprintf(textOut,"Frac. Am1:\t%.1f %% (%.2f [mrad], sigma: %.1e [mrad]))\n", myArea0/nprim*100, funcGaus1_0->GetParameter(1),funcGaus1_0->GetParameter(2));
    if (printFlag) fprintf(textOut,"Frac. Ch1:\t%.1f %% (%.2f [mrad], sigma: %.1e [mrad]))\n\n", myArea20/nprim*100, funcGaus1_20->GetParameter(1),funcGaus1_20->GetParameter(2));
//	canvX1->SaveAs(Form("%s_X1.pdf",runName.Data()));
//	canvX1->Write();
#if 1
	
	funcGaus2_0->SetParameter(0,histoAnglePostX2->GetBinContent(histoAnglePostX2->FindBin(widthCenter)));
	funcGaus2_20->SetParameter(0,histoAnglePostX2->GetBinContent(histoAnglePostX2->FindBin(widthRight)));
	funcGaus2_M20->SetParameter(0,histoAnglePostX2->GetBinContent(histoAnglePostX2->FindBin(widthLeft)));
	funcGaus2_0->SetParLimits(0,10,10000);
	funcGaus2_20->SetParLimits(0,10,10000);
	funcGaus2_M20->SetParLimits(0,histoAnglePostX2->GetBinContent(histoAnglePostX2->FindBin(widthLeft))*0.8,10000);
	
//	funcGaus2_0->FixParameter(1,0);
//	funcGaus2_20->FixParameter(1,2);
//	funcGaus2_M20->FixParameter(1,-2);
	funcGaus2_0->SetParameter(1,0);
	funcGaus2_20->SetParameter(1,2);
	funcGaus2_M20->SetParameter(1,-2);

	
	funcGaus2_0->SetParameter(2,0.01);
	funcGaus2_20->SetParameter(2,0.005);
	funcGaus2_M20->SetParameter(2,0.01);
	funcGaus2_0->SetParLimits(2,0.5*histoAnglePostX2->GetBinWidth(1),0.1);
	funcGaus2_20->SetParLimits(2,0.5*histoAnglePostX2->GetBinWidth(1),0.1);
	funcGaus2_M20->SetParLimits(2,0.5*histoAnglePostX2->GetBinWidth(1),0.1);

    if (printFlag) cout<<"#######################\nFITTING X2\n####################"<<endl;
    if (printFlag) fprintf(textOut,"\n####### After X2\n");
//	TCanvas* canvX2=new TCanvas("canvX2","canvX2");
    TVirtualPad* padX2 = canvXAllSingle->cd(2);
	//	TF1* funcGaus0=new TF1("funcGaus0","gaus",-0.05,0.05);
	//	TF1* funcGaus20=new TF1("funcGaus20","gaus",2-0.05,2+0.05);
	histoAnglePostX2->Draw();
    padX2->SetLogy(1);
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
    if (printFlag) cout<<"\n####### After X2"<<endl;
	//	cout<<"Frac. Am1:\t"<<myArea0/nprim*100<<endl;
	//	cout<<"Frac. Ch1+Am2:\t"<<myArea20/nprim*100<<endl;
	//	cout<<"Frac. Ch1+Ch2:\t"<<myAreaM20/nprim*100<<endl<<endl<<endl;
    if (printFlag) printf("Frac. Am1:\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n", myArea0/nprim*100, funcGaus2_0->GetParameter(1),funcGaus2_0->GetParameter(2));
    if (printFlag) printf("Frac. Ch1+Am2:\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n", myArea20/nprim*100, funcGaus2_20->GetParameter(1),funcGaus2_20->GetParameter(2));
    if (printFlag) printf("Frac. Ch1+Ch2:\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n\n", myAreaM20/nprim*100, funcGaus2_M20->GetParameter(1),funcGaus2_M20->GetParameter(2));
    if (printFlag) fprintf(textOut,"Frac. Am1:\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n", myArea0/nprim*100, funcGaus2_0->GetParameter(1),funcGaus2_0->GetParameter(2));
    if (printFlag) fprintf(textOut,"Frac. Ch1+Am2:\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n", myArea20/nprim*100, funcGaus2_20->GetParameter(1),funcGaus2_20->GetParameter(2));
    if (printFlag) fprintf(textOut,"Frac. Ch1+Ch2:\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n\n", myAreaM20/nprim*100, funcGaus2_M20->GetParameter(1),funcGaus2_M20->GetParameter(2));
//	canvX2->SaveAs(Form("%s_X2.pdf",runName.Data()));
//	canvX2->Write();
#endif
	
#if 1
	
	funcGaus3_0->SetParameter(0,histoAnglePostX3->GetBinContent(histoAnglePostX3->FindBin(widthCenter)));
	funcGaus3_0ChCh->SetParameter(0,histoAnglePostX3->GetBinContent(histoAnglePostX3->FindBin(widthCenter)));
	funcGaus3_20->SetParameter(0,histoAnglePostX3->GetBinContent(histoAnglePostX3->FindBin(widthRight)));
	funcGaus3_M20->SetParameter(0,histoAnglePostX3->GetBinContent(histoAnglePostX3->FindBin(widthLeft)));
	
	funcGaus3_0->SetParLimits(0,10,10000);
	funcGaus3_0ChCh->SetParLimits(0,10,10000);
	funcGaus3_20->SetParLimits(0,10,10000);
	funcGaus3_M20->SetParLimits(0,10,10000);
	
//	funcGaus3_0->FixParameter(1,0);
//	funcGaus3_0ChCh->FixParameter(1,0);
//	funcGaus3_20->FixParameter(1,2);
//	funcGaus3_M20->FixParameter(1,-2);
	funcGaus3_0->SetParameter(1,0);
	funcGaus3_0ChCh->SetParameter(1,0);
	funcGaus3_20->SetParameter(1,2);
	funcGaus3_M20->SetParameter(1,-2);
	
	funcGaus3_0->SetParameter(2,0.01);
	funcGaus3_0ChCh->SetParameter(2,0.01);
	funcGaus3_20->SetParameter(2,0.005);
	funcGaus3_M20->SetParameter(2,0.01);
	funcGaus3_0->SetParLimits(2,0,0.1);
	funcGaus3_0ChCh->SetParLimits(2,0,0.1);
	funcGaus3_20->SetParLimits(2,0,0.1);
	funcGaus3_M20->SetParLimits(2,0,0.1);
	
    if (printFlag) cout<<"#######################\nFITTING X3\n####################"<<endl;
    if (printFlag) fprintf(textOut,"\n####### After X3\n");
//	TCanvas* canvX3=new TCanvas("canvX3","canvX3");
    TVirtualPad* padX3 = canvXAllSingle->cd(3);
	histoAnglePostX3->Draw();
	histoAnglePostX3ChChCh->Draw("sames");
    padX3->SetLogy(1);
	histoAnglePostX3->Fit(funcGaus3_0,"N","",-0.05,0.05);
	histoAnglePostX3ChChCh->Fit(funcGaus3_0ChCh,"N","",-0.05,0.05);
	histoAnglePostX3->Fit(funcGaus3_20,"N","",peakRight-0.05,peakRight+0.05);
	//	histoAnglePostX2->Fit(funcGausM20,"N","",-2.04,-1.96);
	histoAnglePostX3->Fit(funcGaus3_M20,"N","",peakLeft-0.04,peakLeft+0.04);
	funcGaus3_0->Draw("same");
	funcGaus3_0ChCh->SetLineColor(kMagenta);
	funcGaus3_0ChCh->Draw("same");
	funcGaus3_20->Draw("same");
	funcGaus3_M20->Draw("same");
	
	myArea0=funcGaus3_0->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus3_0->GetParameter(2)/histoAnglePostX3->GetBinWidth(1);
	myArea0ChCh=funcGaus3_0ChCh->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus3_0ChCh->GetParameter(2)/histoAnglePostX3ChChCh->GetBinWidth(1);
	myArea20=funcGaus3_20->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus3_20->GetParameter(2)/histoAnglePostX3->GetBinWidth(1);
	myAreaM20=funcGaus3_M20->GetParameter(0)*sqrt(2*TMath::Pi())*funcGaus3_M20->GetParameter(2)/histoAnglePostX3->GetBinWidth(1);
	
	//	cout<<"\n####### After X3\nAm. Frac.: "<<myArea0/nprim*100<<endl<<"Ch.1 Frac.:"<<myArea20/nprim*100<<endl<<"Ch.1 Frac.:"<<myAreaM20/nprim*100<<endl<<endl<<endl;
    if (printFlag) cout<<"\n####### After X3"<<endl;
	//	cout<<"Am. Frac.: "<<myArea0/nprim*100<<endl;
	//	cout<<"Ch.1 Frac.:"<<myArea20/nprim*100<<endl;
	//	cout<<"Ch.1 Frac.:"<<myAreaM20/nprim*100<<endl<<endl<<endl;
    if (printFlag) printf("Frac. Am1+Am3|Ch1+Ch2+Ch3:\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n", myArea0/nprim*100, funcGaus3_0->GetParameter(1), funcGaus3_0->GetParameter(2));
    if (printFlag) printf("Frac. Ch1+Ch2+Ch3:\t\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n", myArea0ChCh/nprim*100, funcGaus3_0ChCh->GetParameter(1), funcGaus3_0ChCh->GetParameter(2));
    if (printFlag) printf("Frac. Ch1+Am2:\t\t\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n", myArea20/nprim*100, funcGaus3_20->GetParameter(1),funcGaus3_20->GetParameter(2));
    if (printFlag) printf("Frac. Ch1+Ch2+Am3:\t\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n\n", myAreaM20/nprim*100, funcGaus3_M20->GetParameter(1), funcGaus3_M20->GetParameter(2));
    if (printFlag) fprintf(textOut,"Frac. Am1+Am3|Ch1+Ch2+Ch3:\t%.1f %% (mean: %.1f [mrad], sigma: %.1e [mrad])\n", myArea0/nprim*100, funcGaus3_0->GetParameter(1), funcGaus3_0->GetParameter(2));
    if (printFlag) fprintf(textOut,"Frac. Ch1+Ch2+Ch3:\t\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n", myArea0ChCh/nprim*100, funcGaus3_0ChCh->GetParameter(1), funcGaus3_0ChCh->GetParameter(2));
    if (printFlag) fprintf(textOut,"Frac. Ch1+Am2:\t\t\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n", myArea20/nprim*100, funcGaus3_20->GetParameter(1), funcGaus3_20->GetParameter(2));
    if (printFlag) fprintf(textOut,"Frac. Ch1+Ch2+Am3:\t\t%.1f %% (mean: %.2f [mrad], sigma: %.1e [mrad])\n\n", myAreaM20/nprim*100, funcGaus3_M20->GetParameter(1), funcGaus3_M20->GetParameter(2));
//	canvX3->SaveAs(Form("%s_X3.pdf",runName.Data()));
//	canvX3->Write();
    canvXAllSingle->Write();

#endif
    
    
    
	TCanvas* canvCum=new TCanvas("canvCum","canvCum",0,0,600,1200);
	canvCum->Divide(1,3);
	TH1F* histoAnglePostX1Cum=(TH1F*)histoAnglePostX1->GetCumulative(1);
	histoAnglePostX1Cum->Scale(1/histoAnglePostX1Cum->GetMaximum());
	
	TH1F* histoAnglePostX2Cum=(TH1F*)histoAnglePostX2->GetCumulative(1);
	histoAnglePostX2Cum->Scale(1/histoAnglePostX2Cum->GetMaximum());
	
	TH1F* histoAnglePostX3Cum=(TH1F*)histoAnglePostX3->GetCumulative(1);
	histoAnglePostX3Cum->Scale(1/histoAnglePostX3Cum->GetMaximum());
	
	TH1F* histoAnglePostX3ChChChCum=(TH1F*)histoAnglePostX3ChChCh->GetCumulative(1);
	histoAnglePostX3ChChChCum->Scale(1/histoAnglePostX3ChChChCum->GetMaximum());
	
	canvCum->cd(1);
	histoAnglePostX1Cum->SetStats(0);
	histoAnglePostX1Cum->Draw();
	canvCum->cd(2);
	histoAnglePostX2Cum->SetStats(0);
	histoAnglePostX2Cum->Draw();
	canvCum->cd(3);
	histoAnglePostX3Cum->SetStats(0);
	histoAnglePostX3Cum->Draw();
	histoAnglePostX3ChChChCum->SetStats(0);
	histoAnglePostX3ChChChCum->Draw("same");
	canvCum->SaveAs(Form("%s_Cum.pdf",runName.Data()));
	canvCum->Write();
	
    TCanvas* canvExpTheta=new TCanvas("canvExpTheta","canvExpTheta");
    histoExpAnglEnd->Draw();
    histoExpAnglEnd->Write();
    canvExpTheta->SetLogy(1);
    canvExpTheta->SaveAs(Form("%s_ExpTheta.pdf",runName.Data()));
    canvExpTheta->Write();
	
    TCanvas* canvFinal=new TCanvas("canvFinal","canvFinal",0,0,1200,600);
  
    //    if (!isOffAxisTriangle) {
    canvFinal->Divide(2,1);
    TVirtualPad* padEndX = canvFinal->cd(1);
    
    //    TCanvas* canvX3ChChCh=new TCanvas("canvX3ChChCh","canvX3ChChCh");
    histoAnglePostX3->Draw();
    if (!isOffAxisTriangle) {
        histoAnglePostX3ChChCh->Draw("sames");
    } else {
        histoAnglePostX3OCh->Draw("sames");
        histoAnglePostX3OAmChCh->Draw("sames");
    }
    padEndX->BuildLegend();
    //    padEndX->Write();
    padEndX->SetLogy();
    padEndX->SaveAs(Form("%s_X3ChChCh.pdf",runName.Data()));
    
    //    TCanvas* canvPosEnd=new TCanvas("canvPosEnd","canvPosEnd");
    TVirtualPad* padEndPos = canvFinal->cd(2);
    histoXEnd->Draw();
    histoXEndChChCh->SetLineColor(kRed);
    if (!isOffAxisTriangle) {
        histoXEndChChCh->Draw("sames");
    } else {
        histoXEndAmChCh->Draw("samesPLC");
        histoXEndAmChAm->Draw("samesPLC");
        histoXEndChNoAm->Draw("samesPLC");
        histoXEndAmAmNo->Draw("samesPLC");
    }
    
    padEndPos->BuildLegend();
    padEndPos->SetLogy();
    padEndPos->SaveAs(Form("%s_PosEnd.pdf",runName.Data()));
    canvFinal->Write();
    //    } else {
    ////        canvFinal->cd(0);
    //        histoAnglePostX3->Draw();
    //        histoAnglePostX3OCh->Draw("sames");
    //        histoAnglePostX3OAmChCh->Draw("sames");
    //        histoAnglePostX3OAmChAm->Draw("sames");
    //        canvFinal->BuildLegend();
    //        //    padEndX->Write();
    //        canvFinal->SetLogy();
    //        canvFinal->SaveAs(Form("%s_AllAnglesPostX3.pdf",runName.Data()));
    //    }
    
    


    
    histoSourceX->Write();
    histoSourceCosX->Write();
    histoSourceY->Write();
    histoSourceCosY->Write();
    
    histoXPostX1->Write();
    histoXPostX2->Write();
    histoXPostX3->Write();
    histoXPreX2->Write();
    histoXPreX3->Write();
    histoXPostX3ChChCh->Write();
    histoXPostX3ChCh->Write();
    histoXPostX3Ch->Write();
    
    histoXEndChChCh->Write();
    histoXEndAmChCh->Write();
    histoXEndAmChAm->Write();
    histoXEndChNoAm->Write();
    histoXEndAmAmNo->Write();

    histoAnglePostX1->Write();
    histoAnglePostX2->Write();
    histoAnglePostX3->Write();

    histoAnglePostX3ChChCh->Write();
    histoAnglePostX3ChCh->Write();
    histoAnglePostX3Ch->Write();
    histoAnglePostX3OChChCh->Write();
    histoAnglePostX3OChCh->Write();
    histoAnglePostX3OCh->Write();
    histoAnglePostX3OAmChCh->Write();
    histoAnglePostX3OAmChAm->Write();

    histoAnglePostX1Cum->Write();
    histoAnglePostX2Cum->Write();
    histoAnglePostX3Cum->Write();
    histoAnglePostX3ChChChCum->Write();
	
}
