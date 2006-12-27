#ifndef CD_KFTrajectorySmoother_H_
#define CD_KFTrajectorySmoother_H_

#include "TrackingTools/PatternTools/interface/TrajectorySmoother.h"
#include "TrackingTools/PatternTools/interface/TrajectoryStateUpdator.h"
#include "TrackingTools/GeomPropagators/interface/Propagator.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"
#include "TrackingTools/TrajectoryState/interface/FreeTrajectoryState.h"
#include "TrackingTools/PatternTools/interface/MeasurementEstimator.h"
#include "TrackingTools/PatternTools/interface/TrajectoryMeasurement.h"

/** A Standard Kalman smoother. The forward fit is not redone,
 *  only the backward smoothing.
 */

class KFTrajectorySmoother : public TrajectorySmoother {

private:

  typedef TrajectoryStateOnSurface TSOS;
  typedef FreeTrajectoryState FTS;
  typedef TrajectoryMeasurement TM;

public:

  KFTrajectorySmoother(const Propagator& aPropagatorAlong,
		       const Propagator& aPropagatorOpposite,
                       const TrajectoryStateUpdator& aUpdator,
                       const MeasurementEstimator& aEstimator,
		       float errorRescaling = 100.f) :
    thePropagatorAlongMomentum(aPropagatorAlong.clone()),
    thePropagatorOppositeToMomentum(aPropagatorOpposite.clone()),
    theUpdator(aUpdator.clone()),
    theEstimator(aEstimator.clone()),
    theErrorRescaling(errorRescaling) {}


  KFTrajectorySmoother(const Propagator* aPropagatorAlong,
		       const Propagator* aPropagatorOpposite, 
		       const TrajectoryStateUpdator* aUpdator, 
		       const MeasurementEstimator* aEstimator,
		       float errorRescaling = 100.f) :
    thePropagatorAlongMomentum(aPropagatorAlong->clone()),
    thePropagatorOppositeToMomentum(aPropagatorOpposite->clone()),
    theUpdator(aUpdator->clone()),
    theEstimator(aEstimator->clone()),
    theErrorRescaling(errorRescaling)  {}

  virtual ~KFTrajectorySmoother();

  virtual std::vector<Trajectory> trajectories(const Trajectory& aTraj) const;

  const Propagator* propagatorAlongMomentum() const {return thePropagatorAlongMomentum;}
  const Propagator* propagatorOppositeToMomentum() const {return thePropagatorOppositeToMomentum;}
  const TrajectoryStateUpdator* updator() const {return theUpdator;}
  const MeasurementEstimator* estimator() const {return theEstimator;}

  virtual KFTrajectorySmoother* clone() const{
    return new KFTrajectorySmoother(thePropagatorAlongMomentum,
				    thePropagatorOppositeToMomentum,
				    theUpdator,theEstimator);
  }

private:

  const Propagator* thePropagatorAlongMomentum;
  const Propagator* thePropagatorOppositeToMomentum;
  const TrajectoryStateUpdator* theUpdator;
  const MeasurementEstimator* theEstimator;
  float theErrorRescaling;

};

#endif //CD_KFTrajectorySmoother_H_
