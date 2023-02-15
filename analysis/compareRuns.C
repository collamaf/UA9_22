#include <TH1F.h>
#include <TFile.h>
#include <TCanvas.h>

void compareRuns()
{
    const char* runName="CompareCut";
//
//    const char* myFiles[]={
//        "mUA9TriAlign_Wide_ShiftX2_Conf3b_SigmaX31Y44Z0_CrystAng-5_N100000_out.root",
//        "mUA9TriAlign_Wide_ShiftX2_Conf3b_SigmaX31Y44Z0_CrystAng-5_X2Offset50_N100000_out.root",
//        "mUA9TriAlign_Wide_ShiftX2_Conf3b_SigmaX31Y44Z0_CrystAng-5_X2Offset100_N100000_out.root",
//        "mUA9TriAlign_Wide_ShiftX2_Conf3b_SigmaX31Y44Z0_CrystAng-5_X2Offset250_N100000_out.root",
//        "mUA9TriAlign_Wide_ShiftX2_Conf3b_SigmaX31Y44Z0_CrystAng-5_X2Offset350_N100000_out.root",
//        "mUA9TriAlign_Wide_ShiftX2_Conf3b_SigmaX31Y44Z0_CrystAng-5_X2Offset500_N100000_out.root",
//        "mUA9TriAlign_Wide_ShiftX2_Conf3b_SigmaX31Y44Z0_CrystAng-5_X2Offset750_N100000_out.root",
//        "mUA9TriAlign_Wide_ShiftX2_Conf3b_SigmaX31Y44Z0_CrystAng-5_X2Offset1000_N100000_out.root",
//        "mUA9TriAlign_Wide_ShiftX2_Conf3b_SigmaX31Y44Z0_CrystAng-5_X2Offset-50_N100000_out.root",
//        "mUA9TriAlign_Wide_ShiftX2_Conf3b_SigmaX31Y44Z0_CrystAng-5_X2Offset-100_N100000_out.root",
//        "mUA9TriAlign_Wide_ShiftX2_Conf3b_SigmaX31Y44Z0_CrystAng-5_X2Offset-250_N100000_out.root",
//        "mUA9TriAlign_Wide_ShiftX2_Conf3b_SigmaX31Y44Z0_CrystAng-5_X2Offset-350_N100000_out.root",
//        "mUA9TriAlign_Wide_ShiftX2_Conf3b_SigmaX31Y44Z0_CrystAng-5_X2Offset-500_N100000_out.root",
//        "mUA9TriAlign_Wide_ShiftX2_Conf3b_SigmaX31Y44Z0_CrystAng-5_X2Offset-750_N100000_out.root",
//        "mUA9TriAlign_Wide_ShiftX2_Conf3b_SigmaX31Y44Z0_CrystAng-5_X2Offset-1000_N100000_out.root",
//    };
    
    const char* myFiles[]={
        "mUA9TriAlign_Wide_Conf3b_SigmaX31Y44Z0_N100000Cut_out.root",
        "mUA9TriAlign_Wide_Conf3b_SigmaX31Y44Z0_N100000_out.root",
    };
    
//    std::map<TString, TString> files;
//    files["uno"] = "mUA9TriAlign_Wide_ShiftX2_Conf3b_SigmaX31Y44Z0_CrystAng-5_N100000_out.root";
//    files["due"] = "mUA9TriAlign_Wide_ShiftX2_Conf3b_SigmaX31Y44Z0_CrystAng-5_X2Offset50_N100000_out.root";

    std::map<TString, std::map<TString, TH1F *> > hists;
    TFile* fOut=new TFile(Form("%s.root",runName),"RECREATE");
    for (auto &file : myFiles) {
        TFile *f = TFile::Open(file);
        cout<<"Apro file: "<<file<<endl;
        TIter next(f->GetListOfKeys());
        TKey *key;
        while ((key = (TKey *)next())) {
            if (strcmp(key->GetClassName(),"TH1F")==0) {
                const TString newname = TString::Format("%s_%s", file, key->GetName());
                cout<<"Histo: "<<newname<<endl;
                hists[key->GetName()][file] = (TH1F *)key->ReadObj()->Clone(newname);
                hists[key->GetName()][file]->SetDirectory(0);
                fOut->cd();
                hists[key->GetName()][file]->Write();
            }
        }
        f->Close();
        SafeDelete(f);
    }

    std::map<TString, TCanvas*> canvases;
    for (auto &hist : hists) {
        canvases[hist.first] = new TCanvas(hist.first, hist.first, 800, 600);
        cout<<"Disegno histo "<<hist.first<<endl;
        int i = 0;
        for (auto &h : hist.second) {
            cout<<"Per il file "<<h.second->GetName()<<endl;
            if (i==0) h.second->SetLineColor(kRed);
            const TString opt = (i == 0) ? "" : "samesPLC";
//            h.second->SetLineColor((i == 0) ? kRed : kBlue);
            h.second->SetTitle(Form("%s",h.second->GetName()));
            h.second->Draw(opt);
            i++;
        }
        canvases[hist.first]->BuildLegend();
        canvases[hist.first]->SetLogy();
        canvases[hist.first]->Write();
        const TString imgname2 = TString::Format("%s_%s.png",runName, hist.first.Data());
        canvases[hist.first]->SaveAs(imgname2);
    }

//    for (auto &canvas: canvases) {
//        const TString imgname = TString::Format("%s.png", canvas.first.Data());
//        cout
//        canvas.second->SaveAs(imgname);
//        canvas.second->Close();
//    }
}
