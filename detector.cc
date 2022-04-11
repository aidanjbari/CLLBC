#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name) {

}

MySensitiveDetector::~MySensitiveDetector() {

}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) {
	G4Track *track = aStep->GetTrack();
	
	G4double eDep = track->GetVertexKineticEnergy();
	
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	return true;
}
