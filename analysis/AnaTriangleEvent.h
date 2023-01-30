//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Apr 19 10:09:00 2022 by ROOT version 6.24/06
// from TTree Planes/Dummy planes scoring
// found on file: mUA9Pla_Conf3_SigmaX1Y0Z0_NoDet_N10000.root
//////////////////////////////////////////////////////////

#ifndef AnaTriangleEvent_h
#define AnaTriangleEvent_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "c++/v1/vector"

class AnaTriangleEvent {
	public :
	TTree          *fChain;   //!pointer to the analyzed TTree or TChain
	Int_t           fCurrent; //!current Tree number in a TChain
	
	// Fixed size dimensions of array or collections stored in the TTree if any.
	
	// Declaration of leaf types
	vector<double>  *X;
	vector<double>  *Y;
	vector<double>  *Z;
	vector<double>  *CosX;
	vector<double>  *CosY;
	vector<double>  *CosZ;
	vector<double>  *P;
	vector<double>  *Ene;
	vector<double>  *Part;
	vector<double>  *Time;
	vector<double>  *PlaneId;
	vector<double>  *crystAngX;
	
	// List of branches
	TBranch        *b_X;   //!
	TBranch        *b_Y;   //!
	TBranch        *b_Z;   //!
	TBranch        *b_CosX;   //!
	TBranch        *b_CosY;   //!
	TBranch        *b_CosZ;   //!
	TBranch        *b_P;   //!
	TBranch        *b_Ene;   //!
	TBranch        *b_Part;   //!
	TBranch        *b_Time;   //!
	TBranch        *b_PlaneId;   //!
	TBranch        *b_crystAngX;   //!
	
	AnaTriangleEvent(TTree *tree=0);
	virtual ~AnaTriangleEvent();
	virtual Int_t    Cut(Long64_t entry);
	virtual Int_t    GetEntry(Long64_t entry);
	virtual Long64_t LoadTree(Long64_t entry);
	virtual void     Init(TTree *tree);
	virtual void     Loop();
	virtual Bool_t   Notify();
	virtual void     Show(Long64_t entry = -1);
	TFile* fileOut;
	FILE* textOut;
	TString runName;
};

#endif

#ifdef AnaTriangleEvent_cxx
AnaTriangleEvent::AnaTriangleEvent(TTree *tree) : fChain(0)
{
	// if parameter tree is not specified (or zero), connect the file
	// used to generate this class and read the Tree.
//	runName="TrEv_"+theRunName;
    TString outFileName=gROOT->GetListOfFiles()->First()->GetName();
    outFileName=outFileName.Remove(outFileName.Length()-5,outFileName.Length()); //remove ".root"
    runName=outFileName;
	cout<<"AAAAAA "<<runName.Data()<<endl;
	if (tree == 0) {
		TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../build/mUA9Pla_Conf3_SigmaX1Y0Z0_NoDet_N10000.root");
		if (!f || !f->IsOpen()) {
			f = new TFile("../build/mUA9Pla_Conf3_SigmaX1Y0Z0_NoDet_N10000.root");
		}
		f->GetObject("Planes",tree);
		
	}
	Init(tree);
	fileOut=TFile::Open(Form("%s_out.root",runName.Data()),"RECREATE");
	
	textOut=fopen(Form("%s_out.txt",runName.Data()),"wt");
	fprintf(textOut,"RUN NAME: %s\n",runName.Data());
	//	fprintf(textOut,"INPUT FILE NAME: %s\n",fileNameIn);
}

AnaTriangleEvent::~AnaTriangleEvent()
{
	if (!fChain) return;
	delete fChain->GetCurrentFile();
}

Int_t AnaTriangleEvent::GetEntry(Long64_t entry)
{
	// Read contents of entry.
	if (!fChain) return 0;
	return fChain->GetEntry(entry);
}
Long64_t AnaTriangleEvent::LoadTree(Long64_t entry)
{
	// Set the environment to read one entry
	if (!fChain) return -5;
	Long64_t centry = fChain->LoadTree(entry);
	if (centry < 0) return centry;
	if (fChain->GetTreeNumber() != fCurrent) {
		fCurrent = fChain->GetTreeNumber();
		Notify();
	}
	return centry;
}

void AnaTriangleEvent::Init(TTree *tree)
{
	// The Init() function is called when the selector needs to initialize
	// a new tree or chain. Typically here the branch addresses and branch
	// pointers of the tree will be set.
	// It is normally not necessary to make changes to the generated
	// code, but the routine can be extended by the user if needed.
	// Init() will be called many times when running on PROOF
	// (once per file to be processed).
	
	// Set object pointer
	X = 0;
	Y = 0;
	Z = 0;
	CosX = 0;
	CosY = 0;
	CosZ = 0;
	P = 0;
	Ene = 0;
	Part = 0;
	Time = 0;
	PlaneId = 0;
	crystAngX = 0;
	// Set branch addresses and branch pointers
	if (!tree) return;
	fChain = tree;
	fCurrent = -1;
	fChain->SetMakeClass(1);
	
	fChain->SetBranchAddress("X", &X, &b_X);
	fChain->SetBranchAddress("Y", &Y, &b_Y);
	fChain->SetBranchAddress("Z", &Z, &b_Z);
	fChain->SetBranchAddress("CosX", &CosX, &b_CosX);
	fChain->SetBranchAddress("CosY", &CosY, &b_CosY);
	fChain->SetBranchAddress("CosZ", &CosZ, &b_CosZ);
	fChain->SetBranchAddress("P", &P, &b_P);
	fChain->SetBranchAddress("Ene", &Ene, &b_Ene);
	fChain->SetBranchAddress("Part", &Part, &b_Part);
	fChain->SetBranchAddress("Time", &Time, &b_Time);
	fChain->SetBranchAddress("PlaneId", &PlaneId, &b_PlaneId);
	fChain->SetBranchAddress("crystAngX", &crystAngX, &b_crystAngX);
	Notify();
}

Bool_t AnaTriangleEvent::Notify()
{
	// The Notify() function is called when a new file is opened. This
	// can be either for a new TTree in a TChain or when when a new TTree
	// is started when using PROOF. It is normally not necessary to make changes
	// to the generated code, but the routine can be extended by the
	// user if needed. The return value is currently not used.
	
	return kTRUE;
}

void AnaTriangleEvent::Show(Long64_t entry)
{
	// Print contents of entry.
	// If entry is not specified, print current entry
	if (!fChain) return;
	fChain->Show(entry);
}
Int_t AnaTriangleEvent::Cut(Long64_t entry)
{
	// This function may be called from Loop.
	// returns  1 if entry is accepted.
	// returns -1 otherwise.
	return 1;
}
#endif // #ifdef AnaTriangleEvent_cxx
