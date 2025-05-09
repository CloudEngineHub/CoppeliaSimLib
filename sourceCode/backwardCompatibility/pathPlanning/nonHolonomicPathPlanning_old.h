#pragma once

#include <pathPlanning_old.h>
#include <nonHolonomicPathNode_old.h>
#include <dummyClasses.h>
#include <vector>
#include <simMath/7Vector.h>

class CNonHolonomicPathPlanning_old : public CPathPlanning_old
{
  public:
    CNonHolonomicPathPlanning_old(int theStartDummyID, int theGoalDummyID, int theRobotCollectionID,
                                  int theObstacleCollectionID, int ikGroupID, double theAngularCoeff,
                                  double theSteeringAngleCoeff, double theMaxSteeringAngleVariation,
                                  double theMaxSteeringAngle, double theStepSize, const double theSearchMinVal[2],
                                  const double theSearchRange[2], const int theDirectionConstraints[2],
                                  const double clearanceAndMaxDistance[2]);
    virtual ~CNonHolonomicPathPlanning_old();

    // Following functions are inherited from CPathPlanning:
    int searchPath(int maxTimePerPass) override;
    bool setPartialPath() override;
    int smoothFoundPath(int steps, int maxTimePerPass) override;
    void getPathData(std::vector<double>& data) override;
    void getSearchTreeData(std::vector<double>& data, bool fromStart) override;

    void setStepSize(double size);

    std::vector<CNonHolonomicPathNode_old*> fromStart;
    std::vector<CNonHolonomicPathNode_old*> fromGoal;
    std::vector<CNonHolonomicPathNode_old*> foundPath;

  private:
    bool doCollide(double* dist) override;

    CNonHolonomicPathNode_old* getClosestNode(std::vector<CNonHolonomicPathNode_old*>& nodes,
                                              CNonHolonomicPathNode_old* sample, bool forward, bool forConnection);
    CNonHolonomicPathNode_old* extend(std::vector<CNonHolonomicPathNode_old*>* currentList,
                                      CNonHolonomicPathNode_old* toBeExtended, CNonHolonomicPathNode_old* extention,
                                      bool forward, CXDummy* startDummy);
    CNonHolonomicPathNode_old* connect(std::vector<CNonHolonomicPathNode_old*>* currentList,
                                       std::vector<CNonHolonomicPathNode_old*>* nextList,
                                       CNonHolonomicPathNode_old* toBeExtended, CNonHolonomicPathNode_old* extention,
                                       bool forward, bool connect, bool test, CXDummy* startDummy);

    int _startDummyID;
    double angularCoeff;
    double steeringAngleCoeff;
    double maxSteeringAngleVariation;
    double maxSteeringAngle;
    double minTurningRadius;
    double stepSize;
    int DoF;
    double searchMinVal[2];
    double searchRange[2];
    C7Vector _startDummyCTM;
    C7Vector _startDummyLTM;

    int numberOfRandomConnectionTries_forSteppedSmoothing;
    int numberOfRandomConnectionTriesLeft_forSteppedSmoothing;
    std::vector<int> foundPathSameStraightLineID_forSteppedSmoothing;
    int sameStraightLineNextID_forSteppedSmoothing;
    int nextIteration_forSteppedSmoothing;

    double _startConfInterferenceState;

    int directionConstraints[2]; // WRONG!!! NOT USED NOW!!! 0 is for vehicle direction, 1 is for steering direction
};
