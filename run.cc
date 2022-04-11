#include "run.hh"

MyRunAction::MyRunAction() {

}

MyRunAction::~MyRunAction() {

}

void MyRunAction::BeginOfRunAction(const G4Run* run) {
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->OpenFile("output.root");
	
	man->CreateNtuple("Scoring", "Scoring");
	man->CreateNtupleDColumn("fEdep");
	man->FinishNtuple(0);
	
	man->CreateH1("fEdep", "Energy Deposition", 1000, 0.,  0.7*MeV);
} 

void MyRunAction::EndOfRunAction(const G4Run*) {
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->Write();
	man->CloseFile();
} 
