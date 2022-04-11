#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator() {
	fParticleSource = new G4GeneralParticleSource;
}

MyPrimaryGenerator::~MyPrimaryGenerator() {
	delete fParticleSource;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent) {
	G4ThreeVector pos(0.,0.,0.);
	
	fParticleSource->SetParticlePosition(pos);
	
	fParticleSource->GeneratePrimaryVertex(anEvent);
}
