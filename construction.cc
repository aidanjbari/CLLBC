#include "construction.hh"

//Website for refractive index : refractiveindex.info

MyDetectorConstruction::MyDetectorConstruction() {

}

MyDetectorConstruction::~MyDetectorConstruction() {

}

G4VPhysicalVolume* MyDetectorConstruction::Construct() {
	G4NistManager *nist = G4NistManager::Instance();
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	
	G4double worldEnergy[2] = {1.239841939*eV/0.2, 1.239841939*eV/0.9};
	G4double rindexWorld[2] = {1.0, 1.0};
	
	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", worldEnergy, rindexWorld, 2);
	worldMat->SetMaterialPropertiesTable(mptWorld);
	
	G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);
	
	G4Material *Cllbc = new G4Material("Cllbc", 4.0*g/cm3, 5);
	Cllbc->AddElement(nist->FindOrBuildElement("Cs"), 2);
	Cllbc->AddElement(nist->FindOrBuildElement("La"), 1);
	Cllbc->AddElement(nist->FindOrBuildElement("Br"), 6);
	Cllbc->AddElement(nist->FindOrBuildElement("Cl"), 6);
	
	G4Isotope *Li6 = new G4Isotope("Li6", 3, 6, 6.015122*g/mole);
	G4Isotope *Li7 = new G4Isotope("Li7", 3, 7, 7.016004*g/mole);
	G4Element *Li = new G4Element("Li", "Li", 2);
	Li->AddIsotope(Li6, 95.*perCent);
	Li->AddIsotope(Li7, 5.*perCent);
	Cllbc->AddElement(Li, 1);
	
	G4double rEnergy[1] = {3.06133809*eV};
	G4double rindexCllbc[1] = {1.81};
	G4double absLengthE[2] = {100000.*eV, 662000.*eV};
	G4double absLength[2] = {0.18215*cm, 3.355705*cm};
	G4double scintEnergy[1] = {3.0240047*eV};
	G4double scintIntensity[1] = {1.0};
	
	G4MaterialPropertiesTable *mptCllbc = new G4MaterialPropertiesTable();
	mptCllbc->AddProperty("SCINTILLATIONCOMPONENT1", scintEnergy, scintIntensity, 1);
	mptCllbc->AddProperty("RINDEX", rEnergy, rindexCllbc, 1);
	mptCllbc->AddProperty("ABSLENGTH", absLengthE, absLength, 1);
	mptCllbc->AddConstProperty("SCINTILLATIONYIELD", 45./keV);
	mptCllbc->AddConstProperty("RESOLUTIONSCALE", 1.0);
	mptCllbc->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 150.*ns);
	mptCllbc->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
	Cllbc->SetMaterialPropertiesTable(mptCllbc);
	
	G4Tubs *solidCllbc = new G4Tubs("solidCllbc", 0.*cm, 5.08*cm, 5.08*cm, 0.*deg, 360.*deg);
	logicCllbc = new G4LogicalVolume(solidCllbc, Cllbc, "logicCllbc");
	fScoringVolume = logicCllbc;
	G4VPhysicalVolume *physCllbc = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.3*m), logicCllbc, "physCllbc", logicWorld, false, 1, true);
	
	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField() {
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
	
	logicCllbc->SetSensitiveDetector(sensDet);
}
