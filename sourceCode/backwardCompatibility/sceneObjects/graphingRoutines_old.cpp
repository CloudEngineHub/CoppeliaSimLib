#include <graphingRoutines_old.h>
#include <simInternal.h>
#include <app.h>
#include <tt.h>
#include <simStrings.h>

CGraphingRoutines_old::CGraphingRoutines_old()
{
}

CGraphingRoutines_old::~CGraphingRoutines_old()
{
}

std::string CGraphingRoutines_old::getDataUnit(CGraphData_old* it)
{
    int dType = it->getDataType();
    if ((dType == GRAPH_SCENEOBJECT_ALL_X_ABS) || (dType == GRAPH_SCENEOBJECT_ALL_Y_ABS) ||
        (dType == GRAPH_SCENEOBJECT_ALL_Z_ABS) || (dType == GRAPH_SCENEOBJECT_ALL_X_REL) ||
        (dType == GRAPH_SCENEOBJECT_ALL_Y_REL) || (dType == GRAPH_SCENEOBJECT_ALL_Z_REL) ||
        (dType == GRAPH_SCENEOBJECT_PROXSENSOR_X_ABS) || (dType == GRAPH_SCENEOBJECT_PROXSENSOR_Y_ABS) ||
        (dType == GRAPH_SCENEOBJECT_PROXSENSOR_Z_ABS) || (dType == GRAPH_SCENEOBJECT_PROXSENSOR_X_REL) ||
        (dType == GRAPH_SCENEOBJECT_PROXSENSOR_Y_REL) || (dType == GRAPH_SCENEOBJECT_PROXSENSOR_Z_REL) ||
        (dType == GRAPH_SCENEOBJECT_PROXSENSOR_X_REL_TO_SENSOR) ||
        (dType == GRAPH_SCENEOBJECT_PROXSENSOR_Y_REL_TO_SENSOR) ||
        (dType == GRAPH_SCENEOBJECT_PROXSENSOR_Z_REL_TO_SENSOR) || (dType == GRAPH_SCENEOBJECT_PROXSENSOR_DIST) ||
        (dType == GRAPH_DISTANCE_DIST) || (dType == GRAPH_DISTANCE_SEG1_X_ABS) ||
        (dType == GRAPH_DISTANCE_SEG1_Y_ABS) || (dType == GRAPH_DISTANCE_SEG1_Z_ABS) ||
        (dType == GRAPH_DISTANCE_SEG2_X_ABS) || (dType == GRAPH_DISTANCE_SEG2_Y_ABS) ||
        (dType == GRAPH_DISTANCE_SEG2_Z_ABS) || (dType == GRAPH_DISTANCE_SEG1_X_REL) ||
        (dType == GRAPH_DISTANCE_SEG1_Y_REL) || (dType == GRAPH_DISTANCE_SEG1_Z_REL) ||
        (dType == GRAPH_DISTANCE_SEG2_X_REL) || (dType == GRAPH_DISTANCE_SEG2_Y_REL) ||
        (dType == GRAPH_DISTANCE_SEG2_Z_REL))
    {
        if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
            (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
            return ("Meters");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
            return ("Meters/Seconds");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
            return ("Meters*Seconds");
    }

    if ((dType == GRAPH_SCENEOBJECT_ALL_XVEL_ABS) || (dType == GRAPH_SCENEOBJECT_ALL_YVEL_ABS) ||
        (dType == GRAPH_SCENEOBJECT_ALL_ZVEL_ABS) || (dType == GRAPH_SCENEOBJECT_ALL_VEL_ABS))
    {
        if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
            (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
            return ("Meters/Seconds");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
            return ("Meters/s^2");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
            return ("Meters");
    }

    if (dType == GRAPH_SCENEOBJECT_ALL_ANGULAR_VEL_ABS)
    {
        if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
            (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
            return ("Degrees/Seconds");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
            return ("Degrees/s^2");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
            return ("Degrees");
    }

    if ((dType == GRAPH_SCENEOBJECT_ALL_ALPHA_ABS) || (dType == GRAPH_SCENEOBJECT_ALL_BETA_ABS) ||
        (dType == GRAPH_SCENEOBJECT_ALL_GAMMA_ABS) || (dType == GRAPH_SCENEOBJECT_ALL_ALPHA_REL) ||
        (dType == GRAPH_SCENEOBJECT_ALL_BETA_REL) || (dType == GRAPH_SCENEOBJECT_ALL_GAMMA_REL) ||
        (dType == GRAPH_SCENEOBJECT_PROXSENSOR_AZIMUTH) || (dType == GRAPH_SCENEOBJECT_PROXSENSOR_ELEVATION))
    {
        if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
            (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
            return ("Degrees");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
            return ("Degrees/Seconds");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
            return ("Degrees*Seconds");
    }
    if ((dType > GRAPH_SCENEOBJECT_JOINT_SUBSTART) && (dType < GRAPH_SCENEOBJECT_JOINT_SUBEND))
    {
        if (dType == GRAPH_SCENEOBJECT_JOINT_POSITION)
        {
            CJoint* act = App::currentWorld->sceneObjects->getJointFromHandle(it->getDataObjectID());
            if (act != nullptr)
            {
                if (act->getJointType() == sim_joint_prismatic)
                {
                    if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
                        (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
                        return ("Meters");
                    if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
                        return ("Meters/Seconds");
                    if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
                        return ("Meters*Seconds");
                }
                if (act->getJointType() == sim_joint_revolute)
                {
                    if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
                        (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
                        return ("Degrees");
                    if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
                        return ("Degrees/Seconds");
                    if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
                        return ("Degrees*Seconds");
                }
                if (act->getJointType() == sim_joint_spherical)
                {
                    if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
                        (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
                        return ("Null");
                    if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
                        return ("Null/Seconds");
                    if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
                        return ("Null*Seconds");
                }
            }
        }
        if (dType == GRAPH_SCENEOBJECT_JOINT_VELOCITY)
        {
            CJoint* act = App::currentWorld->sceneObjects->getJointFromHandle(it->getDataObjectID());
            if (act != nullptr)
            {
                if (act->getJointType() == sim_joint_prismatic)
                {
                    if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
                        (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
                        return ("Meters/Seconds");
                    if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
                        return ("Meters/s^2");
                    if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
                        return ("Meters");
                }
                if (act->getJointType() == sim_joint_revolute)
                {
                    if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
                        (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
                        return ("Degrees/Seconds");
                    if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
                        return ("Degrees/s^2");
                    if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
                        return ("Degrees");
                }
                if (act->getJointType() == sim_joint_spherical)
                {
                    if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
                        (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
                        return ("Null/Seconds");
                    if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
                        return ("Null/s^2");
                    if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
                        return ("Null");
                }
            }
        }
        if (dType == GRAPH_SCENEOBJECT_JOINT_DYN_POSITION_ERROR)
        {
            if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
                (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
                return ("Meters");
            if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
                return ("Meters/Seconds");
            if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
                return ("Meters*Seconds");
        }
        if (dType == GRAPH_SCENEOBJECT_JOINT_DYN_ORIENTATION_ERROR)
        {
            if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
                (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
                return ("Degrees");
            if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
                return ("Degrees/Seconds");
            if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
                return ("Degrees*Seconds");
        }
        if (dType == GRAPH_SCENEOBJECT_JOINT_DYN_FORCE_OR_TORQUE)
        { // New since 1/6/2011:
            CJoint* act = App::currentWorld->sceneObjects->getJointFromHandle(it->getDataObjectID());
            if (act != nullptr)
            {
                if (act->getJointType() == sim_joint_prismatic)
                {
                    std::string retV;
                    if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
                        (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
                        retV = "kg*m/s^2";
                    if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
                        retV = "kg*m/s^3";
                    if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
                        retV = "kg*m/s";
                    return (retV);
                }
                if (act->getJointType() == sim_joint_revolute)
                {
                    std::string retV;
                    if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
                        (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
                        retV = "kg*m^2/s^2";
                    if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
                        retV = "kg*m^2/s^3";
                    if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
                        retV = "kg*m^2/s";
                    return (retV);
                }
                if (act->getJointType() == sim_joint_spherical)
                {
                    if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
                        (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
                        return ("Null");
                    if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
                        return ("Null/Seconds");
                    if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
                        return ("Null*Seconds");
                }
            }
        }
    }

    if ((dType > GRAPH_SCENEOBJECT_FORCESENSOR_SUBSTART) && (dType < GRAPH_SCENEOBJECT_FORCESENSOR_SUBEND))
    {
        if ((dType == GRAPH_SCENEOBJECT_FORCESENSOR_FORCE_X) || (dType == GRAPH_SCENEOBJECT_FORCESENSOR_FORCE_Y) ||
            (dType == GRAPH_SCENEOBJECT_FORCESENSOR_FORCE_Z) || (dType == GRAPH_SCENEOBJECT_FORCESENSOR_FORCE_LENGTH))
        {
            std::string retV;
            if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
                (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
                retV = "kg*m/s^2";
            if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
                retV = "kg*m/s^3";
            if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
                retV = "kg*m/s";
            return (retV);
        }
        if ((dType == GRAPH_SCENEOBJECT_FORCESENSOR_TORQUE_X) || (dType == GRAPH_SCENEOBJECT_FORCESENSOR_TORQUE_Y) ||
            (dType == GRAPH_SCENEOBJECT_FORCESENSOR_TORQUE_Z) || (dType == GRAPH_SCENEOBJECT_FORCESENSOR_TORQUE_LENGTH))
        {
            std::string retV;
            if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
                (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
                retV = "kg*m^2/s^2";
            if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
                retV = "kg*m^2/s^3";
            if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
                retV = "kg*m^2/s";
            return (retV);
        }
        if (dType == GRAPH_SCENEOBJECT_FORCESENSOR_POSITION_ERROR)
        {
            std::string retV;
            if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
                (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
                retV = "Meters";
            if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
                retV = "Meters/Seconds";
            if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
                retV = "Meters*Seconds";
            return (retV);
        }
        if (dType == GRAPH_SCENEOBJECT_FORCESENSOR_ORIENTATION_ERROR)
        {
            std::string retV;
            if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
                (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
                retV = "Degrees";
            if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
                retV = "Degrees/Seconds";
            if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
                retV = "Degrees*Seconds";
            return (retV);
        }
        if (dType == GRAPH_SCENEOBJECT_FORCESENSOR_BROKEN)
        {
            std::string retV;
            if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
                (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
                retV = "Boolean state";
            if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
                retV = "Boolean state/Seconds";
            if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
                retV = "Boolean state*Seconds";
            return (retV);
        }
    }
    if ((dType == GRAPH_SCENEOBJECT_PATH_POSITION) || (dType == GRAPH_SCENEOBJECT_PATH_POSITION_LINEAR_COMPONENT))
    { // We have to check if this is a path:
        CPath_old* path = App::currentWorld->sceneObjects->getPathFromHandle(it->getDataObjectID());
        if (path != nullptr)
        {
            if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
                (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
                return ("Meters");
            if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
                return ("Meters/Seconds");
            if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
                return ("Meters*Seconds");
        }
    }
    if (dType == GRAPH_SCENEOBJECT_PATH_POSITION_ANGULAR_COMPONENT)
    { // We have to check if this is a path:
        CPath_old* path = App::currentWorld->sceneObjects->getPathFromHandle(it->getDataObjectID());
        if (path != nullptr)
        {
            if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
                (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
                return ("Degrees");
            if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
                return ("Degrees/Seconds");
            if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
                return ("Degrees*Seconds");
        }
    }
    if ((dType == GRAPH_NOOBJECT_TIME) || (dType == GRAPH_COLLISION_CALCULATION_TIME) ||
        (dType == GRAPH_NOOBJECT_COLLISION_OVERALL_CALCULATION_TIME) || (dType == GRAPH_DISTANCE_CALCULATION_TIME) ||
        (dType == GRAPH_NOOBJECT_DISTANCE_OVERALL_CALCULATION_TIME) ||
        (dType == GRAPH_SCENEOBJECT_PROXSENSOR_CALCULATION_TIME) ||
        (dType == GRAPH_NOOBJECT_PROXSENSOR_OVERALL_CALCULATION_TIME) ||
        (dType == GRAPH_SCENEOBJECT_MILL_CALCULATION_TIME) || (dType == GRAPH_NOOBJECT_MILL_OVERALL_CALCULATION_TIME) ||
        (dType == GRAPH_SCENEOBJECT_VISIONSENSOR_CALCULATION_TIME) ||
        (dType == GRAPH_NOOBJECT_VISIONSENSOR_OVERALL_CALCULATION_TIME) || (dType == GRAPH_IK_CALCULATION_TIME) ||
        (dType == GRAPH_NOOBJECT_IK_OVERALL_CALCULATION_TIME) ||
        (dType == GRAPH_NOOBJECT_DYNAMICS_OVERALL_CALCULATION_TIME) ||
        (dType == GRAPH_NOOBJECT_WORK_THREADS_EXECUTION_TIME) || (dType == GRAPH_NOOBJECT_RENDERING_TIME) ||
        (dType == GRAPH_NOOBJECT_MAINSCRIPT_EXECUTION_TIME) || (dType == GRAPH_NOOBJECT_SIMULATIONPASS_EXECUTION_TIME))
    {
        if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
            (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
            return ("Seconds");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
            return ("-"); //"Seconds/Seconds");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
            return ("Seconds*Seconds");
    }
    if (dType == GRAPH_NOOBJECT_COLLISION_QUANTITY)
    {
        if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
            (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
            return ("Count");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
            return ("Count/Seconds");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
            return ("Count*Seconds");
    }
    if ((dType == GRAPH_COLLISION_BOOLEAN) || (dType == GRAPH_SCENEOBJECT_PROXSENSOR_DETECTION_STATE) ||
        (dType == GRAPH_SCENEOBJECT_VISIONSENSOR_DETECTION_STATE))
    {
        if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
            (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
            return ("Boolean state");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
            return ("Boolean state/Seconds");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
            return ("Boolean state*Seconds");
    }
    if ((dType == GRAPH_SCENEOBJECT_VISIONSENSOR_MIN_RED) || (dType == GRAPH_SCENEOBJECT_VISIONSENSOR_MIN_GREEN) ||
        (dType == GRAPH_SCENEOBJECT_VISIONSENSOR_MIN_BLUE) || (dType == GRAPH_SCENEOBJECT_VISIONSENSOR_MIN_INTENSITY) ||
        (dType == GRAPH_SCENEOBJECT_VISIONSENSOR_MIN_DEPTH) || (dType == GRAPH_SCENEOBJECT_VISIONSENSOR_MAX_RED) ||
        (dType == GRAPH_SCENEOBJECT_VISIONSENSOR_MAX_GREEN) || (dType == GRAPH_SCENEOBJECT_VISIONSENSOR_MAX_BLUE) ||
        (dType == GRAPH_SCENEOBJECT_VISIONSENSOR_MAX_INTENSITY) ||
        (dType == GRAPH_SCENEOBJECT_VISIONSENSOR_MAX_DEPTH) || (dType == GRAPH_SCENEOBJECT_VISIONSENSOR_AVG_RED) ||
        (dType == GRAPH_SCENEOBJECT_VISIONSENSOR_AVG_GREEN) || (dType == GRAPH_SCENEOBJECT_VISIONSENSOR_AVG_BLUE) ||
        (dType == GRAPH_SCENEOBJECT_VISIONSENSOR_AVG_INTENSITY) || (dType == GRAPH_SCENEOBJECT_VISIONSENSOR_AVG_DEPTH))
    {
        if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
            (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
            return ("Floating point");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
            return ("Floating point/Seconds");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
            return ("Floating point*Seconds");
    }
    if (dType == GRAPH_NOOBJECT_USER_DEFINED)
    {
        if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
            (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
            return ("User unit");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
            return ("User unit/Seconds");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
            return ("User unit*Seconds");
        // was this before:     return("User unit");
    }

    if ((dType == GRAPH_SCENEOBJECT_MILL_CUT_SURFACE) || (dType == GRAPH_NOOBJECT_MILL_OVERALL_CUT_SURFACE))
    {
        if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
            (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
            return ("Square meters");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
            return ("Square meters/Seconds");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
            return ("Square meters*Seconds");
    }
    if ((dType == GRAPH_SCENEOBJECT_MILL_CUT_VOLUME) || (dType == GRAPH_NOOBJECT_MILL_OVERALL_CUT_VOLUME))
    {
        if ((it->getDerivativeIntegralAndCumulative() == sim_stream_transf_raw) ||
            (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_cumulative))
            return ("Cubic meters");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_derivative)
            return ("Cubic meters/Seconds");
        if (it->getDerivativeIntegralAndCumulative() == sim_stream_transf_integral)
            return ("Cubic meters*Seconds");
    }
    return ("Null");
}

void CGraphingRoutines_old::adjustDataToUserMetric(const CGraphData_old* it, double& v,
                                                   int derivativeIntegralOrCumulative)
{
    int dType = it->getDataType();

    if (dType == GRAPH_SCENEOBJECT_ALL_ANGULAR_VEL_ABS)
    {
        v *= radToDeg;
    }

    if ((dType == GRAPH_SCENEOBJECT_ALL_ALPHA_ABS) || (dType == GRAPH_SCENEOBJECT_ALL_BETA_ABS) ||
        (dType == GRAPH_SCENEOBJECT_ALL_GAMMA_ABS) || (dType == GRAPH_SCENEOBJECT_ALL_ALPHA_REL) ||
        (dType == GRAPH_SCENEOBJECT_ALL_BETA_REL) || (dType == GRAPH_SCENEOBJECT_ALL_GAMMA_REL) ||
        (dType == GRAPH_SCENEOBJECT_PROXSENSOR_AZIMUTH) || (dType == GRAPH_SCENEOBJECT_PROXSENSOR_ELEVATION))
    {
        v *= radToDeg;
    }
    if ((dType > GRAPH_SCENEOBJECT_JOINT_SUBSTART) && (dType < GRAPH_SCENEOBJECT_JOINT_SUBEND))
    {
        CJoint* act = App::currentWorld->sceneObjects->getJointFromHandle(it->getDataObjectID());
        if (dType == GRAPH_SCENEOBJECT_JOINT_POSITION)
        { // We have to check if this is a joint and what type:
            if (act != nullptr)
            {
                if (act->getJointType() == sim_joint_revolute)
                    v *= radToDeg;
            }
        }
        if (dType == GRAPH_SCENEOBJECT_JOINT_VELOCITY)
        { // We have to check if this is a joint and what type:
            if (act != nullptr)
            {
                if (act->getJointType() == sim_joint_revolute)
                    v *= radToDeg;
            }
        }
        if (dType == GRAPH_SCENEOBJECT_JOINT_DYN_ORIENTATION_ERROR)
            v *= radToDeg;
    }
    if ((dType > GRAPH_SCENEOBJECT_FORCESENSOR_SUBSTART) && (dType < GRAPH_SCENEOBJECT_FORCESENSOR_SUBEND))
    {
        if (dType == GRAPH_SCENEOBJECT_FORCESENSOR_ORIENTATION_ERROR)
            v *= radToDeg;
    }
    if (dType == GRAPH_SCENEOBJECT_PATH_POSITION_ANGULAR_COMPONENT)
    { // We have to check if this is a path:
        CPath_old* path = App::currentWorld->sceneObjects->getPathFromHandle(it->getDataObjectID());
        if (path != nullptr)
        {
            v *= radToDeg;
        }
    }
}

void CGraphingRoutines_old::getCyclicAndRangeValues(const CGraphData_old* it, bool& cyclic, double& range)
{
    int dType = it->getDataType();
    if ((dType == GRAPH_SCENEOBJECT_ALL_ALPHA_ABS) || (dType == GRAPH_SCENEOBJECT_ALL_GAMMA_ABS))
    {
        cyclic = true;
        range = 0.0; // means: piValT2;
        return;
    }
    if (dType == GRAPH_SCENEOBJECT_ALL_BETA_ABS)
    {
        cyclic = true;
        range = piValue;
        return;
    }
    if (dType == GRAPH_SCENEOBJECT_JOINT_POSITION)
    { // We have to check if this is a joint and is cyclic:
        CJoint* act = App::currentWorld->sceneObjects->getJointFromHandle(it->getDataObjectID());
        if (act != nullptr)
        {
            if (act->getIsCyclic())
            {
                cyclic = true;
                range = 0.0; // means: piValT2;
                return;
            }
        }
    }
    if (dType == GRAPH_SCENEOBJECT_PATH_POSITION)
    { // We have to check if this is a path and is cyclic:
        CPath_old* path = App::currentWorld->sceneObjects->getPathFromHandle(it->getDataObjectID());
        if (path != nullptr)
        {
            if ((path->pathContainer->getAttributes() & sim_pathproperty_closed_path) != 0)
            {
                cyclic = true;
                range = path->pathContainer->getBezierVirtualPathLength();
                return;
            }
        }
    }
    if (dType == GRAPH_SCENEOBJECT_PATH_POSITION_LINEAR_COMPONENT)
    { // We have to check if this is a path and is cyclic:
        CPath_old* path = App::currentWorld->sceneObjects->getPathFromHandle(it->getDataObjectID());
        if (path != nullptr)
        {
            if ((path->pathContainer->getAttributes() & sim_pathproperty_closed_path) != 0)
            {
                cyclic = true;
                range = path->pathContainer->getBezierNormalPathLength();
                return;
            }
        }
    }
    if (dType == GRAPH_SCENEOBJECT_PATH_POSITION_ANGULAR_COMPONENT)
    { // We have to check if this is a path and is cyclic:
        CPath_old* path = App::currentWorld->sceneObjects->getPathFromHandle(it->getDataObjectID());
        if (path != nullptr)
        {
            if ((path->pathContainer->getAttributes() & sim_pathproperty_closed_path) != 0)
            {
                cyclic = true;
                range = path->pathContainer->getBezierAngularPathLength();
                return;
            }
        }
    }
    cyclic = false;
}

bool CGraphingRoutines_old::getDataName(int dataIndex, std::string& dataName)
{ // If return value is true, dataName contains the text for the dataIndex (used by graphs)
    dataName = IDS_ERROR;
    if (dataIndex == GRAPH_COLLISION_BOOLEAN)
        dataName = IDS_COLLISION__COLLIDING_STATE;
    if (dataIndex == GRAPH_NOOBJECT_COLLISION_QUANTITY)
        dataName = IDS_COLLISION__NUMBER_OF_COLLISIONS;
    if (dataIndex == GRAPH_COLLISION_CALCULATION_TIME)
        dataName = IDS_COLLISION_CALCULATION_TIME;
    if (dataIndex == GRAPH_NOOBJECT_COLLISION_OVERALL_CALCULATION_TIME)
        dataName = IDS_COLLISION_OVERALL_CALCULATION_TIME;
    if (dataIndex == GRAPH_DISTANCE_DIST)
        dataName = IDS_DISTANCE__SEGMENT_LENGTH;
    if (dataIndex == GRAPH_DISTANCE_SEG1_X_ABS)
        dataName = IDS_DISTANCE__SEGMENT_SIDE_1_ABSOLUTE_X_POSITION;
    if (dataIndex == GRAPH_DISTANCE_SEG1_Y_ABS)
        dataName = IDS_DISTANCE__SEGMENT_SIDE_1_ABSOLUTE_Y_POSITION;
    if (dataIndex == GRAPH_DISTANCE_SEG1_Z_ABS)
        dataName = IDS_DISTANCE__SEGMENT_SIDE_1_ABSOLUTE_Z_POSITION;
    if (dataIndex == GRAPH_DISTANCE_SEG2_X_ABS)
        dataName = IDS_DISTANCE__SEGMENT_SIDE_2_ABSOLUTE_X_POSITION;
    if (dataIndex == GRAPH_DISTANCE_SEG2_Y_ABS)
        dataName = IDS_DISTANCE__SEGMENT_SIDE_2_ABSOLUTE_Y_POSITION;
    if (dataIndex == GRAPH_DISTANCE_SEG2_Z_ABS)
        dataName = IDS_DISTANCE__SEGMENT_SIDE_2_ABSOLUTE_Z_POSITION;
    if (dataIndex == GRAPH_DISTANCE_SEG1_X_REL)
        dataName = IDS_DISTANCE__SEGMENT_SIDE_1_X_POSITION_RELATIVE_TO_GRAPH;
    if (dataIndex == GRAPH_DISTANCE_SEG1_Y_REL)
        dataName = IDS_DISTANCE__SEGMENT_SIDE_1_Y_POSITION_RELATIVE_TO_GRAPH;
    if (dataIndex == GRAPH_DISTANCE_SEG1_Z_REL)
        dataName = IDS_DISTANCE__SEGMENT_SIDE_1_Z_POSITION_RELATIVE_TO_GRAPH;
    if (dataIndex == GRAPH_DISTANCE_SEG2_X_REL)
        dataName = IDS_DISTANCE__SEGMENT_SIDE_2_X_POSITION_RELATIVE_TO_GRAPH;
    if (dataIndex == GRAPH_DISTANCE_SEG2_Y_REL)
        dataName = IDS_DISTANCE__SEGMENT_SIDE_2_Y_POSITION_RELATIVE_TO_GRAPH;
    if (dataIndex == GRAPH_DISTANCE_SEG2_Z_REL)
        dataName = IDS_DISTANCE__SEGMENT_SIDE_2_Z_POSITION_RELATIVE_TO_GRAPH;
    if (dataIndex == GRAPH_DISTANCE_CALCULATION_TIME)
        dataName = IDS_DISTANCE_CALCULATION_TIME;
    if (dataIndex == GRAPH_NOOBJECT_DISTANCE_OVERALL_CALCULATION_TIME)
        dataName = IDS_DISTANCE_OVERALL_CALCULATION_TIME;
    if (dataIndex == GRAPH_NOOBJECT_TIME)
        dataName = IDS_SIMULATION__TIME;
    if (dataIndex == GRAPH_NOOBJECT_USER_DEFINED)
        dataName = IDS_VARIOUS__USER_DEFINED;
    if (dataIndex == GRAPH_SCENEOBJECT_ALL_X_ABS)
        dataName = IDS_OBJECT__ABSOLUTE_X_POSITION;
    if (dataIndex == GRAPH_SCENEOBJECT_ALL_Y_ABS)
        dataName = IDS_OBJECT__ABSOLUTE_Y_POSITION;
    if (dataIndex == GRAPH_SCENEOBJECT_ALL_Z_ABS)
        dataName = IDS_OBJECT__ABSOLUTE_Z_POSITION;
    if (dataIndex == GRAPH_SCENEOBJECT_ALL_X_REL)
        dataName = IDS_OBJECT__X_POSITION_RELATIVE_TO_GRAPH;
    if (dataIndex == GRAPH_SCENEOBJECT_ALL_Y_REL)
        dataName = IDS_OBJECT__Y_POSITION_RELATIVE_TO_GRAPH;
    if (dataIndex == GRAPH_SCENEOBJECT_ALL_Z_REL)
        dataName = IDS_OBJECT__Z_POSITION_RELATIVE_TO_GRAPH;
    if (dataIndex == GRAPH_SCENEOBJECT_ALL_ALPHA_ABS)
        dataName = IDS_OBJECT__ABSOLUTE_ALPHA_ORIENTATION;
    if (dataIndex == GRAPH_SCENEOBJECT_ALL_BETA_ABS)
        dataName = IDS_OBJECT__ABSOLUTE_BETA_ORIENTATION;
    if (dataIndex == GRAPH_SCENEOBJECT_ALL_GAMMA_ABS)
        dataName = IDS_OBJECT__ABSOLUTE_GAMMA_ORIENTATION;

    if (dataIndex == GRAPH_SCENEOBJECT_ALL_ALPHA_REL)
        dataName = IDS_OBJECT__ALPHA_ORIENTATION_RELATIVE_TO_GRAPH;
    if (dataIndex == GRAPH_SCENEOBJECT_ALL_BETA_REL)
        dataName = IDS_OBJECT__BETA_ORIENTATION_RELATIVE_TO_GRAPH;
    if (dataIndex == GRAPH_SCENEOBJECT_ALL_GAMMA_REL)
        dataName = IDS_OBJECT__GAMMA_ORIENTATION_RELATIVE_TO_GRAPH;

    if (dataIndex == GRAPH_SCENEOBJECT_JOINT_POSITION)
        dataName = IDS_JOINT__POSITION;
    if (dataIndex == GRAPH_SCENEOBJECT_JOINT_VELOCITY)
        dataName = IDS_JOINT__VELOCITY;
    if (dataIndex == GRAPH_SCENEOBJECT_JOINT_DYN_POSITION_ERROR)
        dataName = IDS_JOINT__DYN_POSITION_ERROR;
    if (dataIndex == GRAPH_SCENEOBJECT_JOINT_DYN_ORIENTATION_ERROR)
        dataName = IDS_JOINT__DYN_ORIENTATION_ERROR;
    if (dataIndex == GRAPH_SCENEOBJECT_JOINT_DYN_FORCE_OR_TORQUE)
        dataName = IDS_JOINT__FORCE_OR_TORQUE;

    if (dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_FORCE_X)
        dataName = IDS_FORCE_SENSOR__FORCE_X;
    if (dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_FORCE_Y)
        dataName = IDS_FORCE_SENSOR__FORCE_Y;
    if (dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_FORCE_Z)
        dataName = IDS_FORCE_SENSOR__FORCE_Z;
    if (dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_FORCE_LENGTH)
        dataName = IDS_FORCE_SENSOR__FORCE;
    if (dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_TORQUE_X)
        dataName = IDS_FORCE_SENSOR__TORQUE_X;
    if (dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_TORQUE_Y)
        dataName = IDS_FORCE_SENSOR__TORQUE_Y;
    if (dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_TORQUE_Z)
        dataName = IDS_FORCE_SENSOR__TORQUE_Z;
    if (dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_TORQUE_LENGTH)
        dataName = IDS_FORCE_SENSOR__TORQUE;

    if (dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_POSITION_ERROR)
        dataName = IDS_FORCE_SENSOR__POSITION_ERROR;
    if (dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_ORIENTATION_ERROR)
        dataName = IDS_FORCE_SENSOR__ORIENTATION_ERROR;
    if (dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_BROKEN)
        dataName = IDS_FORCE_SENSOR__BROKEN_STATE;

    if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_X_REL_TO_SENSOR)
        dataName = IDS_PROXSENSOR__DETECTION_POSITION_X_RELATIVE_TO_SENSOR;
    if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_Y_REL_TO_SENSOR)
        dataName = IDS_PROXSENSOR__DETECTION_POSITION_Y_RELATIVE_TO_SENSOR;
    if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_Z_REL_TO_SENSOR)
        dataName = IDS_PROXSENSOR__DETECTION_POSITION_Z_RELATIVE_TO_SENSOR;

    if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_X_ABS)
        dataName = IDS_PROXSENSOR__ABSOLUTE_DETECTION_POSITION_X;
    if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_Y_ABS)
        dataName = IDS_PROXSENSOR__ABSOLUTE_DETECTION_POSITION_Y;
    if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_Z_ABS)
        dataName = IDS_PROXSENSOR__ABSOLUTE_DETECTION_POSITION_Z;

    if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_X_REL)
        dataName = IDS_PROXSENSOR__DETECTION_POSITION_X_RELATIVE_TO_GRAPH;
    if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_Y_REL)
        dataName = IDS_PROXSENSOR__DETECTION_POSITION_Y_RELATIVE_TO_GRAPH;
    if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_Z_REL)
        dataName = IDS_PROXSENSOR__DETECTION_POSITION_Z_RELATIVE_TO_GRAPH;
    if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_DIST)
        dataName = IDS_PROXSENSOR__DETECTION_DISTANCE;
    if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_AZIMUTH)
        dataName = IDS_PROXSENSOR__DETECTION_AZIMUTH;
    if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_ELEVATION)
        dataName = IDS_PROXSENSOR__DETECTION_ELEVATION;
    if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_DETECTION_STATE)
        dataName = IDS_PROXSENSOR__DETECTION_STATE;
    if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_CALCULATION_TIME)
        dataName = IDS_PROXSENSOR_CALCULATION_TIME;
    if (dataIndex == GRAPH_NOOBJECT_PROXSENSOR_OVERALL_CALCULATION_TIME)
        dataName = IDS_PROXSENSOR_OVERALL_CALCULATION_TIME;

    if (dataIndex == GRAPH_SCENEOBJECT_MILL_CUT_SURFACE)
        dataName = IDS_MILL_CUT_SURFACE;
    if (dataIndex == GRAPH_SCENEOBJECT_MILL_CUT_VOLUME)
        dataName = IDS_MILL_CUT_VOLUME;
    if (dataIndex == GRAPH_SCENEOBJECT_MILL_CALCULATION_TIME)
        dataName = IDS_MILL_CALCULATION_TIME;
    if (dataIndex == GRAPH_NOOBJECT_MILL_OVERALL_CUT_SURFACE)
        dataName = IDS_MILL_OVERALL_CUT_SURFACE;
    if (dataIndex == GRAPH_NOOBJECT_MILL_OVERALL_CUT_VOLUME)
        dataName = IDS_MILL_OVERALL_CUT_VOLUME;
    if (dataIndex == GRAPH_NOOBJECT_MILL_OVERALL_CALCULATION_TIME)
        dataName = IDS_MILL_OVERALL_CALCULATION_TIME;

    if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_MIN_RED)
        dataName = IDS_VISIONSENS_GRAPH_MIN_RED;
    if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_MIN_GREEN)
        dataName = IDS_VISIONSENS_GRAPH_MIN_GREEN;
    if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_MIN_BLUE)
        dataName = IDS_VISIONSENS_GRAPH_MIN_BLUE;
    if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_MIN_INTENSITY)
        dataName = IDS_VISIONSENS_GRAPH_MIN_INTENSITY;
    if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_MIN_DEPTH)
        dataName = IDS_VISIONSENS_GRAPH_MIN_DEPTH;
    if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_MAX_RED)
        dataName = IDS_VISIONSENS_GRAPH_MAX_RED;
    if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_MAX_GREEN)
        dataName = IDS_VISIONSENS_GRAPH_MAX_GREEN;
    if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_MAX_BLUE)
        dataName = IDS_VISIONSENS_GRAPH_MAX_BLUE;
    if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_MAX_INTENSITY)
        dataName = IDS_VISIONSENS_GRAPH_MAX_INTENSITY;
    if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_MAX_DEPTH)
        dataName = IDS_VISIONSENS_GRAPH_MAX_DEPTH;
    if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_AVG_RED)
        dataName = IDS_VISIONSENS_GRAPH_AVG_RED;
    if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_AVG_GREEN)
        dataName = IDS_VISIONSENS_GRAPH_AVG_GREEN;
    if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_AVG_BLUE)
        dataName = IDS_VISIONSENS_GRAPH_AVG_BLUE;
    if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_AVG_INTENSITY)
        dataName = IDS_VISIONSENS_GRAPH_AVG_INTENSITY;
    if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_AVG_DEPTH)
        dataName = IDS_VISIONSENS_GRAPH_AVG_DEPTH;
    if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_DETECTION_STATE)
        dataName = IDS_VISIONSENS_GRAPH_DETECTION_STATE;
    if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_CALCULATION_TIME)
        dataName = IDS_VISIONSENS_CALCULATION_TIME;
    if (dataIndex == GRAPH_NOOBJECT_VISIONSENSOR_OVERALL_CALCULATION_TIME)
        dataName = IDS_VISIONSENS_OVERALL_CALCULATION_TIME;
    if (dataIndex == GRAPH_SCENEOBJECT_PATH_POSITION)
        dataName = IDS_PATH_GRAPH_POSITION;
    if (dataIndex == GRAPH_SCENEOBJECT_PATH_POSITION_LINEAR_COMPONENT)
        dataName = IDS_PATH_GRAPH_POSITION_LINEAR_COMPONENT;
    if (dataIndex == GRAPH_SCENEOBJECT_PATH_POSITION_ANGULAR_COMPONENT)
        dataName = IDS_PATH_GRAPH_POSITION_ANGULAR_COMPONENT;
    if (dataIndex == GRAPH_IK_CALCULATION_TIME)
        dataName = IDS_IK_CALCULATION_TIME;
    if (dataIndex == GRAPH_NOOBJECT_IK_OVERALL_CALCULATION_TIME)
        dataName = IDS_IK_OVERALL_CALCULATION_TIME;
    if (dataIndex == GRAPH_NOOBJECT_DYNAMICS_OVERALL_CALCULATION_TIME)
        dataName = IDS_DYNAMICS_OVERALL_CALCULATION_TIME;
    if (dataIndex == GRAPH_NOOBJECT_WORK_THREADS_EXECUTION_TIME)
        dataName = IDS_WORK_THREADS_EXECUTION_TIME;
    if (dataIndex == GRAPH_NOOBJECT_RENDERING_TIME)
        dataName = IDS_RENDERING_TIME;
    if (dataIndex == GRAPH_NOOBJECT_MAINSCRIPT_EXECUTION_TIME)
        dataName = IDS_MAIN_SCRIPT_EXECUTION_TIME;
    if (dataIndex == GRAPH_NOOBJECT_SIMULATIONPASS_EXECUTION_TIME)
        dataName = IDS_SIMULATION_PASS_EXECUTION_TIME;

    if (dataIndex == GRAPH_SCENEOBJECT_ALL_XVEL_ABS)
        dataName = IDS_OBJECT__ABSOLUTE_X_VELOCITY;
    if (dataIndex == GRAPH_SCENEOBJECT_ALL_YVEL_ABS)
        dataName = IDS_OBJECT__ABSOLUTE_Y_VELOCITY;
    if (dataIndex == GRAPH_SCENEOBJECT_ALL_ZVEL_ABS)
        dataName = IDS_OBJECT__ABSOLUTE_Z_VELOCITY;
    if (dataIndex == GRAPH_SCENEOBJECT_ALL_VEL_ABS)
        dataName = IDS_OBJECT__ABSOLUTE_VELOCITY;
    if (dataIndex == GRAPH_SCENEOBJECT_ALL_ANGULAR_VEL_ABS)
        dataName = IDS_OBJECT__ANGULAR_VELOCITY;

    return (dataName != std::string(IDS_ERROR));
}

bool CGraphingRoutines_old::getDataValue(int dataIndex, int objectID, double& value, const C7Vector* graphCTM)
{ // If return value is true, value contains the asked value (used by graphs)
    // If return value is false, the value can't be found here. If it can't be
    // found anywhere, use the default value!
    // graphCTM is nullptr by default

    if ((dataIndex > GRAPH_NOOBJECT_START) && (dataIndex < GRAPH_NOOBJECT_END))
    {
        if (dataIndex == GRAPH_NOOBJECT_IK_OVERALL_CALCULATION_TIME)
        {
            value = 0.0; // App::worldContainer->calcInfo->getIkCalculationTime();
            return (true);
        }
        if (dataIndex == GRAPH_NOOBJECT_DYNAMICS_OVERALL_CALCULATION_TIME)
        {
            value = App::worldContainer->calcInfo->getDynamicsCalculationTime();
            return (true);
        }
        if (dataIndex == GRAPH_NOOBJECT_MAINSCRIPT_EXECUTION_TIME)
        {
            value = App::worldContainer->calcInfo->getMainScriptExecutionTime();
            return (true);
        }
        if (dataIndex == GRAPH_NOOBJECT_RENDERING_TIME)
        {
            value = App::worldContainer->calcInfo->getRenderingDuration();
            return (true);
        }
        if (dataIndex == GRAPH_NOOBJECT_WORK_THREADS_EXECUTION_TIME)
        {
            value = 0.0; // for backward compatibility
            return (true);
        }
        if (dataIndex == GRAPH_NOOBJECT_SIMULATIONPASS_EXECUTION_TIME)
        {
            value = App::worldContainer->calcInfo->getSimulationPassExecutionTime() +
                    App::worldContainer->calcInfo->getRenderingDuration(); // added second part on 3/4/2013
            return (true);
        }
        if (dataIndex == GRAPH_NOOBJECT_COLLISION_QUANTITY)
        {
            int q = 0;
            for (size_t i = 0; i < App::currentWorld->collisions_old->getObjectCount(); i++)
            {
                CCollisionObject_old* aColl = App::currentWorld->collisions_old->getObjectFromIndex(i);
                if (aColl != nullptr)
                    if (aColl->getCollisionResult())
                        q++;
            }
            value = (double)q;
            return (true);
        }
        if (dataIndex == GRAPH_NOOBJECT_COLLISION_OVERALL_CALCULATION_TIME)
        {
            value = 0.0; // App::worldContainer->calcInfo->getCollisionCalculationTime();
            return (true);
        }
        if (dataIndex == GRAPH_NOOBJECT_DISTANCE_OVERALL_CALCULATION_TIME)
        {
            value = 0.0; // App::worldContainer->calcInfo->getDistanceCalculationTime();
            return (true);
        }
        if (dataIndex == GRAPH_NOOBJECT_PROXSENSOR_OVERALL_CALCULATION_TIME)
        {
            value = App::worldContainer->calcInfo->getProximitySensorCalculationTime();
            return (true);
        }
        if (dataIndex == GRAPH_NOOBJECT_VISIONSENSOR_OVERALL_CALCULATION_TIME)
        {
            value = App::worldContainer->calcInfo->getVisionSensorCalculationTime();
            return (true);
        }
        if (dataIndex == GRAPH_NOOBJECT_MILL_OVERALL_CALCULATION_TIME)
        {
            value = 0.0; // App::worldContainer->calcInfo->getMillingCalculationTime();
            return (true);
        }
        if ((dataIndex == GRAPH_NOOBJECT_MILL_OVERALL_CUT_SURFACE) ||
            (dataIndex == GRAPH_NOOBJECT_MILL_OVERALL_CUT_VOLUME))
        {
            bool validData = false;
            double totV = 0.0;
            for (size_t i = 0; i < App::currentWorld->sceneObjects->getObjectCount(sim_sceneobject_mill); i++)
            {
                double v;
                CMill* it = App::currentWorld->sceneObjects->getMillFromIndex(i);
                if (dataIndex == GRAPH_NOOBJECT_MILL_OVERALL_CUT_VOLUME)
                {
                    if (it->getMilledVolume(v))
                    {
                        validData = true;
                        totV += v;
                    }
                }
                else
                {
                    if (it->getMilledSurface(v))
                    {
                        validData = true;
                        totV += v;
                    }
                }
            }
            if (validData)
                value = totV;
            return (validData);
        }

        if (dataIndex == GRAPH_NOOBJECT_USER_DEFINED)
            return (false); // We want a default value
        if (dataIndex == GRAPH_NOOBJECT_TIME)
        { // We handle this case in CGraph::addNextPoint!!!! (this is an exception!)
            return (true);
        }
        return (false);
    }

    if ((dataIndex > GRAPH_IK_START) && (dataIndex < GRAPH_IK_END))
    {
        CIkGroup_old* it = App::currentWorld->ikGroups_old->getObjectFromHandle(objectID);
        if (it == nullptr)
            return (false);
        if (dataIndex == GRAPH_IK_CALCULATION_TIME)
        {
            value = it->getCalculationTime();
            return (true);
        }
        return (false);
    }

    if ((dataIndex > GRAPH_GCS_START_old) && (dataIndex < GRAPH_GCS_END_old))
        return (false); // not supported anymore

    if ((dataIndex > GRAPH_COLLISION_START) && (dataIndex < GRAPH_COLLISION_END))
    {
        CCollisionObject_old* it = App::currentWorld->collisions_old->getObjectFromHandle(objectID);
        if (it == nullptr)
            return (false);
        if (dataIndex == GRAPH_COLLISION_BOOLEAN)
        {
            if (!it->isCollisionResultValid())
                return (false);
            if (it->getCollisionResult())
                value = 1.0;
            else
                value = 0.0;
            return (true);
        }
        if (dataIndex == GRAPH_COLLISION_CALCULATION_TIME)
        {
            if (!it->isCollisionResultValid())
                return (false);
            value = it->getCalculationTime();
            return (true);
        }
        return (false);
    }
    if ((dataIndex > GRAPH_DISTANCE_START) && (dataIndex < GRAPH_DISTANCE_END))
    {
        CDistanceObject_old* it = App::currentWorld->distances_old->getObjectFromHandle(objectID);
        if (it == nullptr)
            return (false);
        double dist[7];
        bool validResult = it->getDistanceResult(dist);
        if (dataIndex == GRAPH_DISTANCE_DIST)
        {
            value = dist[6];
            return (validResult);
        }
        if (dataIndex == GRAPH_DISTANCE_CALCULATION_TIME)
        {
            value = it->getCalculationTime();
            return (true);
        }
        if (dataIndex == GRAPH_DISTANCE_SEG1_X_ABS)
        {
            value = dist[0];
            return (validResult);
        }
        if (dataIndex == GRAPH_DISTANCE_SEG1_Y_ABS)
        {
            value = dist[1];
            return (validResult);
        }
        if (dataIndex == GRAPH_DISTANCE_SEG1_Z_ABS)
        {
            value = dist[2];
            return (validResult);
        }
        if (dataIndex == GRAPH_DISTANCE_SEG2_X_ABS)
        {
            value = dist[3];
            return (validResult);
        }
        if (dataIndex == GRAPH_DISTANCE_SEG2_Y_ABS)
        {
            value = dist[4];
            return (validResult);
        }
        if (dataIndex == GRAPH_DISTANCE_SEG2_Z_ABS)
        {
            value = dist[5];
            return (validResult);
        }
        if ((dataIndex == GRAPH_DISTANCE_SEG1_X_REL) || (dataIndex == GRAPH_DISTANCE_SEG1_Y_REL) ||
            (dataIndex == GRAPH_DISTANCE_SEG1_Z_REL) || (dataIndex == GRAPH_DISTANCE_SEG2_X_REL) ||
            (dataIndex == GRAPH_DISTANCE_SEG2_Y_REL) || (dataIndex == GRAPH_DISTANCE_SEG2_Z_REL))
        {
            if (!validResult)
                return (validResult);
            if (graphCTM == nullptr)
                return (false);
            C7Vector graphInv(graphCTM->getInverse());
            C3Vector d0(dist);
            C3Vector d1(dist + 3);
            d0 *= graphInv;
            d1 *= graphInv;
            d0.getData(dist);
            d1.getData(dist + 3);
            if (dataIndex == GRAPH_DISTANCE_SEG1_X_REL)
                value = dist[0];
            if (dataIndex == GRAPH_DISTANCE_SEG1_Y_REL)
                value = dist[1];
            if (dataIndex == GRAPH_DISTANCE_SEG1_Z_REL)
                value = dist[2];
            if (dataIndex == GRAPH_DISTANCE_SEG2_X_REL)
                value = dist[3];
            if (dataIndex == GRAPH_DISTANCE_SEG2_Y_REL)
                value = dist[4];
            if (dataIndex == GRAPH_DISTANCE_SEG2_Z_REL)
                value = dist[5];
            return (validResult);
        }
        return (false);
    }

    if ((dataIndex > GRAPH_SCENEOBJECT_JOINT_SUBSTART) && (dataIndex < GRAPH_SCENEOBJECT_JOINT_SUBEND))
    {
        CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(objectID);
        if (it == nullptr)
            return (false);
        if (dataIndex == GRAPH_SCENEOBJECT_JOINT_POSITION)
        {
            value = it->getPosition();
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_JOINT_VELOCITY)
        {
            value = it->getMeasuredJointVelocity();
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_JOINT_DYN_POSITION_ERROR)
        {
            double dummyVal;
            it->getDynamicJointErrors(value, dummyVal);
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_JOINT_DYN_ORIENTATION_ERROR)
        {
            double dummyVal;
            it->getDynamicJointErrors(dummyVal, value);
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_JOINT_DYN_FORCE_OR_TORQUE)
        { // New since 1/6/2011
            double dummyVal;
            if (it->getDynamicForceOrTorque(dummyVal, false))
            {
                value = dummyVal;
                return (true);
            }
            return (false);
        }
        return (false);
    }
    if ((dataIndex > GRAPH_SCENEOBJECT_FORCESENSOR_SUBSTART) && (dataIndex < GRAPH_SCENEOBJECT_FORCESENSOR_SUBEND))
    {
        CForceSensor* it = App::currentWorld->sceneObjects->getForceSensorFromHandle(objectID);
        if (it == nullptr)
            return (false);
        C3Vector forces;
        C3Vector torques;
        bool validForces = it->getDynamicForces(forces, false);
        bool validTorques = it->getDynamicTorques(torques, false);
        if ((dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_FORCE_X) && validForces)
        {
            value = forces(0);
            return (true);
        }
        if ((dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_FORCE_Y) && validForces)
        {
            value = forces(1);
            return (true);
        }
        if ((dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_FORCE_Z) && validForces)
        {
            value = forces(2);
            return (true);
        }
        if ((dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_FORCE_LENGTH) && validForces)
        {
            value = forces.getLength();
            return (true);
        }
        if ((dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_TORQUE_X) && validTorques)
        {
            value = torques(0);
            return (true);
        }
        if ((dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_TORQUE_Y) && validTorques)
        {
            value = torques(1);
            return (true);
        }
        if ((dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_TORQUE_Z) && validTorques)
        {
            value = torques(2);
            return (true);
        }
        if ((dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_TORQUE_LENGTH) && validTorques)
        {
            value = torques.getLength();
            return (true);
        }

        if (dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_POSITION_ERROR)
        {
            value = it->getDynamicPositionError();
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_ORIENTATION_ERROR)
        {
            value = it->getDynamicOrientationError();
            return (true);
        }

        if (dataIndex == GRAPH_SCENEOBJECT_FORCESENSOR_BROKEN)
        {
            value = 0.0;
            CSceneObject* child = it->getChildFromIndex(0);
            if (child == nullptr)
                value = 1.0;
            return (true);
        }

        return (false);
    }

    if ((dataIndex > GRAPH_SCENEOBJECT_PATH_SUBSTART) && (dataIndex < GRAPH_SCENEOBJECT_PATH_SUBEND))
    {
        CPath_old* it = App::currentWorld->sceneObjects->getPathFromHandle(objectID);
        if (it == nullptr)
            return (false);
        if (dataIndex == GRAPH_SCENEOBJECT_PATH_POSITION)
        {
            value = double(it->pathContainer->getPosition());
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_PATH_POSITION_LINEAR_COMPONENT)
        {
            value = double(it->pathContainer->getPosition_linearComponentOnly());
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_PATH_POSITION_ANGULAR_COMPONENT)
        {
            value = double(it->pathContainer->getPosition_angularComponentOnly());
            return (true);
        }
        return (false);
    }

    if ((dataIndex > GRAPH_SCENEOBJECT_PROXSENSOR_SUBSTART) && (dataIndex < GRAPH_SCENEOBJECT_PROXSENSOR_SUBEND))
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(objectID);
        if (it == nullptr)
            return (false);
        if (it->getObjectType() != sim_sceneobject_proximitysensor)
            return (false);
        CProxSensor* sens = (CProxSensor*)it;
        if ((dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_X_REL_TO_SENSOR) ||
            (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_Y_REL_TO_SENSOR) ||
            (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_Z_REL_TO_SENSOR))
        {
            C3Vector pt;
            if (sens->getSensedData(pt))
            {
                if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_X_REL_TO_SENSOR)
                    value = pt(0);
                if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_Y_REL_TO_SENSOR)
                    value = pt(1);
                if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_Z_REL_TO_SENSOR)
                    value = pt(2);
                return (true);
            }
            else
                return (false); // didn't sense anything
        }
        if ((dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_X_REL) || (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_Y_REL) ||
            (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_Z_REL))
        {
            if (graphCTM == nullptr)
                return (false);
            C3Vector pt;
            if (sens->getSensedData(pt))
            {
                C7Vector sensCTM(sens->getCumulativeTransformation());
                C7Vector graphInv(graphCTM->getInverse());
                sensCTM = graphInv * sensCTM;
                pt = sensCTM * pt;
                if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_X_REL)
                    value = pt(0);
                if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_Y_REL)
                    value = pt(1);
                if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_Z_REL)
                    value = pt(2);
                return (true);
            }
            else
                return (false); // didn't sense anything
        }
        if ((dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_X_ABS) || (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_Y_ABS) ||
            (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_Z_ABS))
        {
            C3Vector pt;
            if (sens->getSensedData(pt))
            {
                C4X4Matrix sensCTM(sens->getCumulativeTransformation().getMatrix());
                pt = sensCTM * pt;
                if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_X_ABS)
                    value = pt(0);
                if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_Y_ABS)
                    value = pt(1);
                if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_Z_ABS)
                    value = pt(2);
                return (true);
            }
            else
                return (false); // didn't sense anything
        }
        if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_DIST)
        {
            C3Vector pt;
            if (sens->getSensedData(pt))
            {
                value = pt.getLength();
                return (true);
            }
            else
            {
                return (false); // didn't sense anything
            }
        }
        if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_CALCULATION_TIME)
        {
            value = sens->getCalculationTime();
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_DETECTION_STATE)
        {
            C3Vector pt;
            if (sens->getSensedData(pt))
                value = 1.0;
            else
                value = 0.0;
            return (true);
        }
        if ((dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_AZIMUTH) ||
            (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_ELEVATION))
        {
            C3Vector pt;
            if (sens->getSensedData(pt))
            {
                if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_ELEVATION)
                {
                    double r = pt.getLength();
                    double el = robustAsin(pt(1) / r);
                    value = el;
                }
                if (dataIndex == GRAPH_SCENEOBJECT_PROXSENSOR_AZIMUTH)
                {
                    double az;
                    if (pt(2) != 0.0)
                        az = atan(-pt(0) / pt(2));
                    else
                    {
                        if (pt(0) >= 0.0)
                            az = piValD2;
                        else
                            az = -piValD2;
                    }
                    value = az;
                }
                return (true);
            }
            else
                return (false); // didn't sense anything
        }
        return (false);
    }
    if ((dataIndex > GRAPH_SCENEOBJECT_MILL_SUBSTART) && (dataIndex < GRAPH_SCENEOBJECT_MILL_SUBEND))
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(objectID);
        if (it == nullptr)
            return (false);
        if (it->getObjectType() != sim_sceneobject_mill)
            return (false);
        CMill* mill = (CMill*)it;
        if (dataIndex == GRAPH_SCENEOBJECT_MILL_CUT_SURFACE)
        {
            if (mill->getMilledSurface(value))
                return (true);
            else
                return (false); // not valid data
        }
        if (dataIndex == GRAPH_SCENEOBJECT_MILL_CUT_VOLUME)
        {
            if (mill->getMilledVolume(value))
                return (true);
            else
                return (false); // not valid data
        }
        if (dataIndex == GRAPH_SCENEOBJECT_MILL_CALCULATION_TIME)
        {
            double dummy;
            if (mill->getMilledSurface(dummy))
            {
                value = mill->getCalculationTime();
                return (true);
            }
            else
                return (false); // not valid data
        }
        return (false);
    }
    if ((dataIndex > GRAPH_SCENEOBJECT_VISIONSENSOR_SUBSTART) && (dataIndex < GRAPH_SCENEOBJECT_VISIONSENSOR_SUBEND))
    {
        CVisionSensor* it = App::currentWorld->sceneObjects->getVisionSensorFromHandle(objectID);
        if (it == nullptr)
            return (false);
        SHandlingResult* r = &it->sensorResult;
        if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_MIN_RED)
        {
            if (!r->sensorResultIsValid)
                return (false);
            value = double(r->sensorDataRed[0]) / 255.0;
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_MIN_GREEN)
        {
            if (!r->sensorResultIsValid)
                return (false);
            value = double(r->sensorDataGreen[0]) / 255.0;
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_MIN_BLUE)
        {
            if (!r->sensorResultIsValid)
                return (false);
            value = double(r->sensorDataBlue[0]) / 255.0;
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_MIN_INTENSITY)
        {
            if (!r->sensorResultIsValid)
                return (false);
            value = double(r->sensorDataIntensity[0]) / 255.0;
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_MIN_DEPTH)
        {
            if (!r->sensorResultIsValid)
                return (false);
            value = r->sensorDataDepth[0];
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_MAX_RED)
        {
            if (!r->sensorResultIsValid)
                return (false);
            value = double(r->sensorDataRed[1]) / 255.0;
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_MAX_GREEN)
        {
            if (!r->sensorResultIsValid)
                return (false);
            value = double(r->sensorDataGreen[1]) / 255.0;
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_MAX_BLUE)
        {
            if (!r->sensorResultIsValid)
                return (false);
            value = double(r->sensorDataBlue[1]) / 255.0;
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_MAX_INTENSITY)
        {
            if (!r->sensorResultIsValid)
                return (false);
            value = double(r->sensorDataIntensity[1]) / 255.0;
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_MAX_DEPTH)
        {
            if (!r->sensorResultIsValid)
                return (false);
            value = r->sensorDataDepth[1];
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_AVG_RED)
        {
            if (!r->sensorResultIsValid)
                return (false);
            value = double(r->sensorDataRed[2]) / 255.0;
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_AVG_GREEN)
        {
            if (!r->sensorResultIsValid)
                return (false);
            value = double(r->sensorDataGreen[2]) / 255.0;
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_AVG_BLUE)
        {
            if (!r->sensorResultIsValid)
                return (false);
            value = double(r->sensorDataBlue[2]) / 255.0;
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_AVG_INTENSITY)
        {
            if (!r->sensorResultIsValid)
                return (false);
            value = double(r->sensorDataIntensity[2]) / 255.0;
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_AVG_DEPTH)
        {
            if (!r->sensorResultIsValid)
                return (false);
            value = r->sensorDataDepth[2];
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_DETECTION_STATE)
        {
            if (!r->sensorResultIsValid)
                return (false);
            if (r->sensorWasTriggered)
                value = 1.0;
            else
                value = 0.0;
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_VISIONSENSOR_CALCULATION_TIME)
        {
            if (!r->sensorResultIsValid)
                return (false);
            value = it->getCalculationTime();
            return (true);
        }
        return (false);
    }

    // DO FOLLOWING ONLY AFTER HAVING HANDLED ALL SCENEOBJECT SUB_CATEGORIES (e.g. Joints, paths, sensors, etc.)
    if ((dataIndex > GRAPH_SCENEOBJECT_START) && (dataIndex < GRAPH_SCENEOBJECT_END))
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(objectID);
        if (it == nullptr)
            return (false);
        if ((dataIndex == GRAPH_SCENEOBJECT_ALL_X_ABS) || (dataIndex == GRAPH_SCENEOBJECT_ALL_Y_ABS) ||
            (dataIndex == GRAPH_SCENEOBJECT_ALL_Z_ABS) || (dataIndex == GRAPH_SCENEOBJECT_ALL_ALPHA_ABS) ||
            (dataIndex == GRAPH_SCENEOBJECT_ALL_BETA_ABS) || (dataIndex == GRAPH_SCENEOBJECT_ALL_GAMMA_ABS))
        {
            C7Vector itCTM(it->getCumulativeTransformation());
            C3Vector euler(itCTM.Q.getEulerAngles());
            if (dataIndex == GRAPH_SCENEOBJECT_ALL_X_ABS)
                value = itCTM.X(0);
            if (dataIndex == GRAPH_SCENEOBJECT_ALL_Y_ABS)
                value = itCTM.X(1);
            if (dataIndex == GRAPH_SCENEOBJECT_ALL_Z_ABS)
                value = itCTM.X(2);
            if (dataIndex == GRAPH_SCENEOBJECT_ALL_ALPHA_ABS)
                value = euler(0);
            if (dataIndex == GRAPH_SCENEOBJECT_ALL_BETA_ABS)
                value = euler(1);
            if (dataIndex == GRAPH_SCENEOBJECT_ALL_GAMMA_ABS)
                value = euler(2);
            return (true);
        }
        if ((dataIndex == GRAPH_SCENEOBJECT_ALL_X_REL) || (dataIndex == GRAPH_SCENEOBJECT_ALL_Y_REL) ||
            (dataIndex == GRAPH_SCENEOBJECT_ALL_Z_REL) || (dataIndex == GRAPH_SCENEOBJECT_ALL_ALPHA_REL) ||
            (dataIndex == GRAPH_SCENEOBJECT_ALL_BETA_REL) || (dataIndex == GRAPH_SCENEOBJECT_ALL_GAMMA_REL))
        {
            C7Vector itCTM(it->getCumulativeTransformation());
            if (graphCTM == nullptr)
                return (false);
            C7Vector graphInv(graphCTM->getInverse());
            itCTM = graphInv * itCTM;
            C3Vector euler(itCTM.Q.getEulerAngles());
            if (dataIndex == GRAPH_SCENEOBJECT_ALL_X_REL)
                value = itCTM.X(0);
            if (dataIndex == GRAPH_SCENEOBJECT_ALL_Y_REL)
                value = itCTM.X(1);
            if (dataIndex == GRAPH_SCENEOBJECT_ALL_Z_REL)
                value = itCTM.X(2);
            if (dataIndex == GRAPH_SCENEOBJECT_ALL_ALPHA_REL)
                value = euler(0);
            if (dataIndex == GRAPH_SCENEOBJECT_ALL_BETA_REL)
                value = euler(1);
            if (dataIndex == GRAPH_SCENEOBJECT_ALL_GAMMA_REL)
                value = euler(2);
            return (true);
        }
        if ((dataIndex == GRAPH_SCENEOBJECT_ALL_XVEL_ABS) || (dataIndex == GRAPH_SCENEOBJECT_ALL_YVEL_ABS) ||
            (dataIndex == GRAPH_SCENEOBJECT_ALL_ZVEL_ABS) || (dataIndex == GRAPH_SCENEOBJECT_ALL_VEL_ABS))
        {
            C3Vector v(it->getMeasuredLinearVelocity());
            if (dataIndex == GRAPH_SCENEOBJECT_ALL_XVEL_ABS)
                value = v(0);
            if (dataIndex == GRAPH_SCENEOBJECT_ALL_YVEL_ABS)
                value = v(1);
            if (dataIndex == GRAPH_SCENEOBJECT_ALL_ZVEL_ABS)
                value = v(2);
            if (dataIndex == GRAPH_SCENEOBJECT_ALL_VEL_ABS)
                value = v.getLength();
            return (true);
        }
        if (dataIndex == GRAPH_SCENEOBJECT_ALL_ANGULAR_VEL_ABS)
        {
            value = it->getMeasuredAngularVelocity();
            return (true);
        }
        return (false);
    }

    return (false);
}
bool CGraphingRoutines_old::getGraphObjectName(int dataIndex, int objectID, std::string& objName)
{ // Returns the name of an object being graphed (name of Scene object, sensor, collision partn., etc)
    // objName is valid only if return value is true
    if ((dataIndex > GRAPH_IK_START) && (dataIndex < GRAPH_IK_END))
    {
        CIkGroup_old* it = App::currentWorld->ikGroups_old->getObjectFromHandle(objectID);
        if (it == nullptr)
            return (false);
        objName = it->getObjectName();
        return (true);
    }
    if ((dataIndex > GRAPH_GCS_START_old) && (dataIndex < GRAPH_GCS_END_old))
        return (false); // not supported anymore
    if ((dataIndex > GRAPH_COLLISION_START) && (dataIndex < GRAPH_COLLISION_END))
    {
        CCollisionObject_old* it = App::currentWorld->collisions_old->getObjectFromHandle(objectID);
        if (it == nullptr)
            return (false);
        objName = it->getObjectName();
        return (true);
    }
    if ((dataIndex > GRAPH_DISTANCE_START) && (dataIndex < GRAPH_DISTANCE_END))
    {
        CDistanceObject_old* it = App::currentWorld->distances_old->getObjectFromHandle(objectID);
        if (it == nullptr)
            return (false);
        objName = it->getObjectName();
        return (true);
    }
    if ((dataIndex > GRAPH_SCENEOBJECT_START) && (dataIndex < GRAPH_SCENEOBJECT_END))
    {
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(objectID);
        if (it == nullptr)
            return (false);
        objName = it->getObjectName_old();
        return (true);
    }
    if ((dataIndex == GRAPH_NOOBJECT_IK_OVERALL_CALCULATION_TIME) ||
        (dataIndex == GRAPH_NOOBJECT_DYNAMICS_OVERALL_CALCULATION_TIME) ||
        (dataIndex == GRAPH_NOOBJECT_PROXSENSOR_OVERALL_CALCULATION_TIME) ||
        (dataIndex == GRAPH_NOOBJECT_VISIONSENSOR_OVERALL_CALCULATION_TIME) ||
        (dataIndex == GRAPH_NOOBJECT_COLLISION_OVERALL_CALCULATION_TIME) ||
        (dataIndex == GRAPH_NOOBJECT_MILL_OVERALL_CALCULATION_TIME) ||
        (dataIndex == GRAPH_NOOBJECT_DISTANCE_OVERALL_CALCULATION_TIME))
    {
        objName = IDS_OVERALL_CALCULATION_TIME;
        return (true);
    }
    if (dataIndex == GRAPH_NOOBJECT_MILL_OVERALL_CUT_SURFACE)
    {
        objName = IDS_OVERALL_CUT_SURFACE;
        return (true);
    }
    if (dataIndex == GRAPH_NOOBJECT_MILL_OVERALL_CUT_VOLUME)
    {
        objName = IDS_OVERALL_CUT_VOLUME;
        return (true);
    }
    if (dataIndex == GRAPH_NOOBJECT_MAINSCRIPT_EXECUTION_TIME)
    {
        objName = IDS_EXECUTION_TIME;
        return (true);
    }
    if (dataIndex == GRAPH_NOOBJECT_WORK_THREADS_EXECUTION_TIME)
    {
        objName = IDS_EXECUTION_TIME;
        return (true);
    }
    if (dataIndex == GRAPH_NOOBJECT_RENDERING_TIME)
    {
        objName = IDS_EXECUTION_TIME;
        return (true);
    }
    if (dataIndex == GRAPH_NOOBJECT_SIMULATIONPASS_EXECUTION_TIME)
    {
        objName = IDS_EXECUTION_TIME;
        return (true);
    }
    if (dataIndex == GRAPH_NOOBJECT_COLLISION_QUANTITY)
    {
        objName = IDS_OVERALL_COLLISION_COUNT;
        return (true);
    }
    if (dataIndex == GRAPH_NOOBJECT_TIME)
    {
        objName = IDS_SIMULATION_TIME;
        return (true);
    }
    if (dataIndex == GRAPH_NOOBJECT_USER_DEFINED)
    {
        objName = IDS_USER_DATA;
        return (true);
    }
    return (false);
}

bool CGraphingRoutines_old::getObjectsFromGraphCategory(int index, int dataIndex, int& objectID)
{ // Returns the objectID and auxDat for all objects concerned by the category 'dataIndex'
    // Loop through this function beginning with index=0 and incrementing it as long
    // as the return value is true
    if (index < 0)
        return (false);

    if ((dataIndex > GRAPH_NOOBJECT_START) && (dataIndex < GRAPH_NOOBJECT_END))
    {
        objectID = -1;
        if (index == 0)
            return (true);
        return (false);
    }
    if ((dataIndex > GRAPH_IK_START) && (dataIndex < GRAPH_IK_END))
    {
        if (index >= int(App::currentWorld->ikGroups_old->getObjectCount()))
            return (false);
        CIkGroup_old* it = App::currentWorld->ikGroups_old->getObjectFromIndex(index);
        if (it == nullptr)
            return (false);
        objectID = it->getObjectHandle();
        return (true);
    }
    if ((dataIndex > GRAPH_GCS_START_old) && (dataIndex < GRAPH_GCS_END_old))
        return (false); // not supported anymore
    if ((dataIndex > GRAPH_COLLISION_START) && (dataIndex < GRAPH_COLLISION_END))
    {
        if (index >= int(App::currentWorld->collisions_old->getObjectCount()))
            return (false);
        CCollisionObject_old* it = App::currentWorld->collisions_old->getObjectFromIndex(index);
        if (it == nullptr)
            return (false);
        objectID = it->getObjectHandle();
        return (true);
    }
    if ((dataIndex > GRAPH_DISTANCE_START) && (dataIndex < GRAPH_DISTANCE_END))
    {
        if (index >= int(App::currentWorld->distances_old->getObjectCount()))
            return (false);
        CDistanceObject_old* it = App::currentWorld->distances_old->getObjectFromIndex(index);
        if (it == nullptr)
            return (false);
        objectID = it->getObjectHandle();
        return (true);
    }

    // HERE WE HAVE ALL SCENEOBJECT SUB-CATEGORIES (IMPORTANT TO PUT THEM BEFORE SCENEOBJECT IN GENERAL!)
    if ((dataIndex > GRAPH_SCENEOBJECT_JOINT_SUBSTART) && (dataIndex < GRAPH_SCENEOBJECT_JOINT_SUBEND))
    {
        if (index >= int(App::currentWorld->sceneObjects->getObjectCount(sim_sceneobject_joint)))
            return (false);
        objectID = App::currentWorld->sceneObjects->getJointFromIndex(index)->getObjectHandle();
        return (true);
    }
    if ((dataIndex > GRAPH_SCENEOBJECT_PATH_SUBSTART) && (dataIndex < GRAPH_SCENEOBJECT_PATH_SUBEND))
    {
        if (index >= int(App::currentWorld->sceneObjects->getObjectCount(sim_sceneobject_path)))
            return (false);
        objectID = App::currentWorld->sceneObjects->getPathFromIndex(index)->getObjectHandle();
        return (true);
    }
    if ((dataIndex > GRAPH_SCENEOBJECT_PROXSENSOR_SUBSTART) && (dataIndex < GRAPH_SCENEOBJECT_PROXSENSOR_SUBEND))
    {
        if (index >= int(App::currentWorld->sceneObjects->getObjectCount(sim_sceneobject_proximitysensor)))
            return (false);
        objectID = App::currentWorld->sceneObjects->getProximitySensorFromIndex(index)->getObjectHandle();
        return (true);
    }
    if ((dataIndex > GRAPH_SCENEOBJECT_MILL_SUBSTART) && (dataIndex < GRAPH_SCENEOBJECT_MILL_SUBEND))
    {
        if (index >= int(App::currentWorld->sceneObjects->getObjectCount(sim_sceneobject_mill)))
            return (false);
        objectID = App::currentWorld->sceneObjects->getMillFromIndex(index)->getObjectHandle();
        return (true);
    }
    if ((dataIndex > GRAPH_SCENEOBJECT_FORCESENSOR_SUBSTART) && (dataIndex < GRAPH_SCENEOBJECT_FORCESENSOR_SUBEND))
    {
        if (index >= int(App::currentWorld->sceneObjects->getObjectCount(sim_sceneobject_forcesensor)))
            return (false);
        objectID = App::currentWorld->sceneObjects->getForceSensorFromIndex(index)->getObjectHandle();
        return (true);
    }
    if ((dataIndex > GRAPH_SCENEOBJECT_VISIONSENSOR_SUBSTART) && (dataIndex < GRAPH_SCENEOBJECT_VISIONSENSOR_SUBEND))
    {
        if (index >= int(App::currentWorld->sceneObjects->getObjectCount(sim_sceneobject_visionsensor)))
            return (false);
        objectID = App::currentWorld->sceneObjects->getVisionSensorFromIndex(index)->getObjectHandle();
        return (true);
    }

    // FOLLOWING HAS TO COME AFTER ALL OTHER SCENEOBJECT SUB-CATEGORIES (e.g. GRAPH_#DOBJECT_JOINT_SUBSTART/SUBEND,
    // etc.)
    if ((dataIndex > GRAPH_SCENEOBJECT_START) && (dataIndex < GRAPH_SCENEOBJECT_END))
    {
        if (index >= int(App::currentWorld->sceneObjects->getObjectCount()))
            return (false);
        objectID = App::currentWorld->sceneObjects->getObjectFromIndex(index)->getObjectHandle();
        return (true);
    }
    return (false);
}

bool CGraphingRoutines_old::loopThroughAllAndGetDataName(int dataIndex, std::string& dataName)
{ // If return value is true, dataName contains the text for the dataIndex (used by graphs)
    if (CGraphingRoutines_old::getDataName(dataIndex, dataName))
        return (true);
    return (false);
}

bool CGraphingRoutines_old::loopThroughAllAndGetDataValue(int dataIndex, int objectID, double& value,
                                                          const C7Vector* graphCTM)
{ // If return value is true, value contains the asked value (used by graphs)
    // If return value is false, the value couldn't be found and you have to use
    // the default value!
    // graphCTM is nullptr by default
    if (CGraphingRoutines_old::getDataValue(dataIndex, objectID, value, graphCTM))
        return (true);
    return (false);
}

bool CGraphingRoutines_old::loopThroughAllAndGetGraphObjectName(int dataIndex, int objectID, std::string& objName)
{ // Returns the name of an object being graphed (name of scene object, sensor, collision partn., etc)
    // objName is valid only if return value is true
    if (CGraphingRoutines_old::getGraphObjectName(dataIndex, objectID, objName))
        return (true);
    return (false);
}
bool CGraphingRoutines_old::loopThroughAllAndGetObjectsFromGraphCategory(int index, int dataIndex, int& objectID)
{ // Returns the objectID and auxDat for all objects concerned by the category 'dataIndex'
    // Loop through this function beginning with index=0 and incrementing it as long
    // as the return value is true
    if (CGraphingRoutines_old::getObjectsFromGraphCategory(index, dataIndex, objectID))
        return (true);
    return (false);
}
