#pragma once

// GAUDI
#include "Gaudi/Property.h"
#include "GaudiAlg/GaudiAlgorithm.h"

// K4FWCORE
#include "k4FWCore/DataHandle.h"
#include "k4Interface/IGeoSvc.h"

// EDM4HEP & PODIO
#include "edm4hep/SimTrackerHitCollection.h"
#include "podio/UserDataCollection.h"

// EDM4HEP extension
#include "extension/DriftChamberDigiCollection.h"
#include "extension/MCRecoDriftChamberDigiAssociationCollection.h"

/** @class DCHsimpleDigitizerExtendedEdmPerformance
 *
 *  Technical skeleton to show how to create performance plots for the DCHsimpleDigitizerExtendedEdm
 *  
 *  @author Brieuc Francois
 *  @date   2023-03
 *
 */

class DCHsimpleDigitizerExtendedEdmPerformance : public GaudiAlgorithm {
public:
  explicit DCHsimpleDigitizerExtendedEdmPerformance(const std::string&, ISvcLocator*);
  virtual ~DCHsimpleDigitizerExtendedEdmPerformance();
  /**  Initialize.
   *   @return status code
   */
  virtual StatusCode initialize() final;
  /**  Execute.
   *   @return status code
   */
  virtual StatusCode execute() final;
  /**  Finalize.
   *   @return status code
   */
  virtual StatusCode finalize() final;

private:
  // Input sim tracker hit collection name
  DataHandle<edm4hep::SimTrackerHitCollection> m_input_sim_hits{"inputSimHits", Gaudi::DataHandle::Reader, this};
  // Input digitized tracker hit collection name
  DataHandle<extension::DriftChamberDigiCollection> m_input_digi_hits{"inputDigiHits", Gaudi::DataHandle::Reader, this};
  // Input association between digitized and simulated hit collections
  DataHandle<extension::MCRecoDriftChamberDigiAssociationCollection> m_input_sim_digi_associations{"inputSimDigiAssociations", Gaudi::DataHandle::Reader, this};

  // Output performance metrics
  DataHandle<podio::UserDataCollection<double>> m_leftHitSimHitSphericalDeltaR{"leftHitSimHitSphericalDeltaR", Gaudi::DataHandle::Writer, this}; // mm

};
