#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction) {
	fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction() {

}

void MySteppingAction::UserSteppingAction(const G4Step *step) {
	G4Track *track = step->GetTrack();
	G4double energy = track->GetVertexKineticEnergy();
	
	G4double totalEdep = step->GetTotalEnergyDeposit();
	
	if (energy < 0.1*MeV) {
		track->SetTrackStatus(fStopAndKill);
		return;
	}
	
	G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	
	const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	
	G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();
	
	if(volume != fScoringVolume)
		return;
	
	fEventAction->AddEdep(totalEdep);
}
