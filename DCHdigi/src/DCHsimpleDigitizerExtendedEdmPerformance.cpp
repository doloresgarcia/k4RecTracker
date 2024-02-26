#include "DCHsimpleDigitizerExtendedEdmPerformance.h"

// DD4hep
#include "DD4hep/Detector.h"
#include "DDRec/Vector3D.h"

// ROOT
#include "Math/Cylindrical3D.h"

DECLARE_COMPONENT(DCHsimpleDigitizerExtendedEdmPerformance)

DCHsimpleDigitizerExtendedEdmPerformance::DCHsimpleDigitizerExtendedEdmPerformance(const std::string& aName, ISvcLocator* aSvcLoc)
    : GaudiAlgorithm(aName, aSvcLoc) {
  declareProperty("inputSimHits", m_input_sim_hits, "Input sim tracker hit collection name");
  declareProperty("inputDigiHits", m_input_digi_hits, "Input digitized drift chamber hit collection name");
  declareProperty("inputSimDigiAssociation", m_input_sim_digi_associations, "Input name of the association between digitized and simulated hit collections");
}

DCHsimpleDigitizerExtendedEdmPerformance::~DCHsimpleDigitizerExtendedEdmPerformance() {}

StatusCode DCHsimpleDigitizerExtendedEdmPerformance::initialize() {

  return StatusCode::SUCCESS;
}

StatusCode DCHsimpleDigitizerExtendedEdmPerformance::execute() {
  // Get the association collection
  auto input_sim_digi_associations = m_input_sim_digi_associations.get();
  // Inititalize user data collections
  auto leftHitSimHitSphericalDeltaR = m_leftHitSimHitSphericalDeltaR.createAndPut();
  // loop over associations and fill the variables
  for (const auto& input_sim_digi_association : *input_sim_digi_associations){
    auto input_sim_hit = input_sim_digi_association.getSim();
    dd4hep::rec::Vector3D simHitPositionVector(input_sim_hit.getPosition().x, input_sim_hit.getPosition().y, input_sim_hit.getPosition().z);
    auto input_digi_hit = input_sim_digi_association.getDigi();
    dd4hep::rec::Vector3D digiHitLeftPositionVector(input_digi_hit.getLeftPosition().x, input_digi_hit.getLeftPosition().y, input_digi_hit.getLeftPosition().z);
    leftHitSimHitSphericalDeltaR->push_back(simHitPositionVector.r() - digiHitLeftPositionVector.r());
  }

  return StatusCode::SUCCESS;
}

StatusCode DCHsimpleDigitizerExtendedEdmPerformance::finalize() { return StatusCode::SUCCESS; }
