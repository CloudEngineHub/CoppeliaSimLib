#pragma once

#include <sceneObject.h>

struct SJointProperty {
    const char* name;
    int type;
    int flags;
    int oldEnums[5];
    const char* shortInfoTxt;
    const char* infoTxt;
};

// ----------------------------------------------------------------------------------------------
// flags: bit0: not writable, bit1: not readable, bit2: removable
#define DEFINE_PROPERTIES \
    FUNCX(propJoint_length,                    "jointLength",                                sim_propertytype_float,     0, -1, -1, -1, -1, -1, "Size", "Joint size") \
    FUNCX(propJoint_diameter,                  "jointDiameter",                              sim_propertytype_float,     0, -1, -1, -1, -1, -1, "Size", "Joint size") \
    FUNCX(propJoint_position,                  "jointPosition",                              sim_propertytype_float,     0, -1, -1, -1, -1, -1, "Position", "Joint linear/angular displacement") \
    FUNCX(propJoint_quaternion,                "quaternion",                                 sim_propertytype_quaternion,0, -1, -1, -1, -1, -1, "Spherical joint quaternion", "") \
    FUNCX(propJoint_screwLead,                 "screwLead",                                  sim_propertytype_float,     0, -1, -1, -1, -1, -1, "Screw lead", "") \
    FUNCX(propJoint_intrinsicError,            "intrinsicError",                             sim_propertytype_pose,      sim_propertyinfo_notwritable, -1, -1, -1, -1, -1, "Intrinsic error", "Intrinsic error, generated by some physics engines") \
    FUNCX(propJoint_intrinsicPose,             "intrinsicPose",                              sim_propertytype_pose,      sim_propertyinfo_notwritable, -1, -1, -1, -1, -1, "Intrinsic pose", "Intrinsic pose (includes a possible intrinsic error)") \
    FUNCX(propJoint_calcVelocity,              "calcVelocity",                               sim_propertytype_float,     sim_propertyinfo_notwritable, -1, -1, -1, -1, -1, "Velocity", "Calculated joint linear or angular velocity") \
    FUNCX(propJoint_jointType,                 "jointType",                                  sim_propertytype_int,       sim_propertyinfo_notwritable, -1, -1, -1, -1, -1, "Type", "Joint type") \
    FUNCX(propJoint_cyclic,                    "cyclic",                                     sim_propertytype_bool,      0, -1, -1, -1, -1, -1, "Cyclic", "Cyclic revolute joint, has no limits") \
    FUNCX(propJoint_interval,                  "interval",                                   sim_propertytype_floatarray,0, -1, -1, -1, -1, -1, "Interval", "Joint limits (lower and upper bounds)") \
    FUNCX(propJoint_targetPos,                 "targetPos",                                  sim_propertytype_float,     0, -1, -1, -1, -1, -1, "Target position", "Position to reach by controller") \
    FUNCX(propJoint_targetVel,                 "targetVel",                                  sim_propertytype_float,     0, -1, -1, -1, -1, -1, "Target velocity", "Velocity to reach by controller") \
    FUNCX(propJoint_targetForce,               "targetForce",                                sim_propertytype_float,     0, -1, -1, -1, -1, -1, "Target force", "Maximum force to exert") \
    FUNCX(propJoint_jointForce,                "jointForce",                                 sim_propertytype_float,     sim_propertyinfo_notwritable, -1, -1, -1, -1, -1, "Force", "Force applied") \
    FUNCX(propJoint_averageJointForce,         "averageJointForce",                          sim_propertytype_float,     sim_propertyinfo_notwritable, -1, -1, -1, -1, -1, "Average force", "Force applied on average (in a simulation step)") \
    FUNCX(propJoint_jointMode,                 "jointMode",                                  sim_propertytype_int,       0, -1, -1, -1, -1, -1, "Mode", "Joint mode") \
    FUNCX(propJoint_dynCtrlMode,               "dynCtrlMode",                                sim_propertytype_int,       0, -1, -1, -1, -1, -1, "Control mode", "Joint control mode, when in dynamic mode") \
    FUNCX(propJoint_dependencyMaster,          "dependencyMasterHandle",                     sim_propertytype_int,       0, -1, -1, -1, -1, -1, "Dependency master", "Handle of master joint (in a dependency relationship)") \
    FUNCX(propJoint_dependencyParams,          "dependencyParams",                           sim_propertytype_floatarray,0, -1, -1, -1, -1, -1, "Dependency parameters", "Dependency parameters (offset and coefficient)") \
    FUNCX(propJoint_maxVelAccelJerk,           "maxVelAccelJerk",                            sim_propertytype_floatarray,0, -1, -1, -1, -1, -1, "Maximum velocity, acceleration and jerk", "") \
    FUNCX(propJoint_springDamperParams,        "springDamperParams",                         sim_propertytype_floatarray,0, -1, -1, -1, -1, -1, "Spring damper parameters", "") \
    FUNCX(propJoint_dynVelMode,                "dynVelMode",                                 sim_propertytype_int,       0, -1, -1, -1, -1, -1, "Dynamic velocity mode", "Dynamic velocity mode (0: default, 1: Ruckig)") \
    FUNCX(propJoint_dynPosMode,                "dynPosMode",                                 sim_propertytype_int,       0, -1, -1, -1, -1, -1, "Dynamic position mode", "Dynamic position mode (0: default, 1: Ruckig)") \
    FUNCX(propJoint_engineProperties,          "engineProperties",                           sim_propertytype_string,    0, -1, -1, -1, -1, -1, "Engine properties", "Engine properties as JSON text") \
    FUNCX(propJoint_bulletStopErp,             "bullet.stopErp",                              sim_propertytype_float,     0, sim_bullet_joint_stoperp, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_bulletStopCfm,             "bullet.stopCfm",                              sim_propertytype_float,     0, sim_bullet_joint_stopcfm, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_bulletNormalCfm,           "bullet.normalCfm",                            sim_propertytype_float,     0, sim_bullet_joint_normalcfm, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_bulletPosPid,              "bullet.posPid",                               sim_propertytype_floatarray,   0, sim_bullet_joint_pospid1, sim_bullet_joint_pospid2, sim_bullet_joint_pospid3, -1, -1, "", "") \
    FUNCX(propJoint_odeStopErp,                "ode.stopErp",                                 sim_propertytype_float,     0, sim_ode_joint_stoperp, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_odeStopCfm,                "ode.stopCfm",                                 sim_propertytype_float,     0, sim_ode_joint_stopcfm, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_odeNormalCfm,              "ode.normalCfm",                               sim_propertytype_float,     0, sim_ode_joint_normalcfm, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_odeBounce,                 "ode.bounce",                                  sim_propertytype_float,     0, sim_ode_joint_bounce, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_odeFudgeFactor,            "ode.fudge",                                   sim_propertytype_float,     0, sim_ode_joint_fudgefactor, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_odePosPid,                 "ode.posPid",                                  sim_propertytype_floatarray,   0, sim_ode_joint_pospid1, sim_ode_joint_pospid2, sim_ode_joint_pospid3, -1, -1, "", "") \
    FUNCX(propJoint_vortexLowerLimitDamping,   "vortex.axisLimitsLowerDamping",                     sim_propertytype_float,     0, sim_vortex_joint_lowerlimitdamping, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexUpperLimitDamping,   "vortex.axisLimitsUpperDamping",                     sim_propertytype_float,     0, sim_vortex_joint_upperlimitdamping, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexLowerLimitStiffness, "vortex.axisLimitsLowerStiffness",                   sim_propertytype_float,     0, sim_vortex_joint_lowerlimitstiffness, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexUpperLimitStiffness, "vortex.axisLimitsUpperStiffness",                   sim_propertytype_float,     0, sim_vortex_joint_upperlimitstiffness, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexLowerLimitRestitution, "vortex.axisLimitsLowerRestitution",               sim_propertytype_float,     0, sim_vortex_joint_lowerlimitrestitution, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexUpperLimitRestitution, "vortex.axisLimitsUpperRestitution",               sim_propertytype_float,     0, sim_vortex_joint_upperlimitrestitution, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexLowerLimitMaxForce,  "vortex.axisLimitsLowerMaxForce",                    sim_propertytype_float,     0, sim_vortex_joint_lowerlimitmaxforce, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexUpperLimitMaxForce,  "vortex.axisLimitsUpperMaxForce",                    sim_propertytype_float,     0, sim_vortex_joint_upperlimitmaxforce, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexAxisFrictionEnabled,     "vortex.axisFrictionEnabled",                        sim_propertytype_bool,      0, sim_vortex_joint_motorfrictionenabled, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexAxisFrictionProportional,"vortex.axisFrictionProportional",                   sim_propertytype_bool,      0, sim_vortex_joint_proportionalmotorfriction, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexAxisFrictionCoeff,       "vortex.axisFrictionValue",                          sim_propertytype_float,     0, sim_vortex_joint_motorconstraintfrictioncoeff, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexAxisFrictionMaxForce,    "vortex.axisFrictionMaxForce",                       sim_propertytype_float,     0, sim_vortex_joint_motorconstraintfrictionmaxforce, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexAxisFrictionLoss,        "vortex.axisFrictionLoss",                           sim_propertytype_float,     0, sim_vortex_joint_motorconstraintfrictionloss, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexRelaxationEnabledBits,    "vortex.relaxationEnabledBits",                  sim_propertytype_int,      0, sim_vortex_joint_relaxationenabledbc, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexFrictionEnabledBits,      "vortex.frictionEnabledBits",                    sim_propertytype_int,      0, sim_vortex_joint_frictionenabledbc, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexFrictionProportionalBits, "vortex.frictionProportionalBits",               sim_propertytype_int,      0, sim_vortex_joint_frictionproportionalbc, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexXAxisPosRelaxationStiffness,  "vortex.xAxisPosRelaxationStiffness",                sim_propertytype_float,     0, sim_vortex_joint_p0stiffness, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexXAxisPosRelaxationDamping,    "vortex.xAxisPosRelaxationDamping",                  sim_propertytype_float,     0, sim_vortex_joint_p0damping, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexXAxisPosRelaxationLoss,       "vortex.xAxisPosRelaxationLoss",                     sim_propertytype_float,     0, sim_vortex_joint_p0loss, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexXAxisPosFrictionCoeff,        "vortex.xAxisPosFrictionCoeff",                      sim_propertytype_float,     0, sim_vortex_joint_p0frictioncoeff, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexXAxisPosFrictionMaxForce,     "vortex.xAxisPosFrictionMaxForce",                   sim_propertytype_float,     0, sim_vortex_joint_p0frictionmaxforce, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexXAxisPosFrictionLoss,         "vortex.xAxisPosFrictionLoss",                       sim_propertytype_float,     0, sim_vortex_joint_p0frictionloss, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexYAxisPosRelaxationStiffness, "vortex.yAxisPosRelaxationStiffness",                sim_propertytype_float,     0, sim_vortex_joint_p1stiffness, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexYAxisPosRelaxationDamping,   "vortex.yAxisPosRelaxationDamping",                  sim_propertytype_float,     0, sim_vortex_joint_p1damping, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexYAxisPosRelaxationLoss,      "vortex.yAxisPosRelaxationLoss",                     sim_propertytype_float,     0, sim_vortex_joint_p1loss, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexYAxisPosFrictionCoeff,       "vortex.yAxisPosFrictionCoeff",                      sim_propertytype_float,     0, sim_vortex_joint_p1frictioncoeff, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexYAxisPosFrictionMaxForce,    "vortex.yAxisPosFrictionMaxForce",                   sim_propertytype_float,     0, sim_vortex_joint_p1frictionmaxforce, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexYAxisPosFrictionLoss,        "vortex.yAxisPosFrictionLoss",                       sim_propertytype_float,     0, sim_vortex_joint_p1frictionloss, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexZAxisPosRelaxationStiffness, "vortex.zAxisPosRelaxationStiffness",                sim_propertytype_float,     0, sim_vortex_joint_p2stiffness, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexZAxisPosRelaxationDamping,   "vortex.zAxisPosRelaxationDamping",                  sim_propertytype_float,     0, sim_vortex_joint_p2damping, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexZAxisPosRelaxationLoss,      "vortex.zAxisPosRelaxationLoss",                     sim_propertytype_float,     0, sim_vortex_joint_p2loss, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexZAxisPosFrictionCoeff,       "vortex.zAxisPosFrictionCoeff",                      sim_propertytype_float,     0, sim_vortex_joint_p2frictioncoeff, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexZAxisPosFrictionMaxForce,    "vortex.zAxisPosFrictionMaxForce",                   sim_propertytype_float,     0, sim_vortex_joint_p2frictionmaxforce, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexZAxisPosFrictionLoss,        "vortex.zAxisPosFrictionLoss",                       sim_propertytype_float,     0, sim_vortex_joint_p2frictionloss, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexXAxisOrientRelaxStiffness,"vortex.xAxisOrientRelaxationStiffness",            sim_propertytype_float,     0, sim_vortex_joint_a0stiffness, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexXAxisOrientRelaxDamping, "vortex.xAxisOrientRelaxationDamping",               sim_propertytype_float,     0, sim_vortex_joint_a0damping, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexXAxisOrientRelaxLoss,    "vortex.xAxisOrientRelaxationLoss",                  sim_propertytype_float,     0, sim_vortex_joint_a0loss, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexXAxisOrientFrictionCoeff,"vortex.xAxisOrientFrictionCoeff",                   sim_propertytype_float,     0, sim_vortex_joint_a0frictioncoeff, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexXAxisOrientFrictionMaxTorque,"vortex.xAxisOrientFrictionMaxTorque",           sim_propertytype_float,     0, sim_vortex_joint_a0frictionmaxforce, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexXAxisOrientFrictionLoss, "vortex.xAxisOrientFrictionLoss",                    sim_propertytype_float,     0, sim_vortex_joint_a0frictionloss, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexYAxisOrientRelaxStiffness,"vortex.yAxisOrientRelaxationStiffness",            sim_propertytype_float,     0, sim_vortex_joint_a1stiffness, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexYAxisOrientRelaxDamping, "vortex.yAxisOrientRelaxationDamping",               sim_propertytype_float,     0, sim_vortex_joint_a1damping, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexYAxisOrientRelaxLoss,    "vortex.yAxisOrientRelaxationLoss",                  sim_propertytype_float,     0, sim_vortex_joint_a1loss, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexYAxisOrientFrictionCoeff,"vortex.yAxisOrientFrictionCoeff",                   sim_propertytype_float,     0, sim_vortex_joint_a1frictioncoeff, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexYAxisOrientFrictionMaxTorque,"vortex.yAxisOrientFrictionMaxTorque",           sim_propertytype_float,     0, sim_vortex_joint_a1frictionmaxforce, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexYAxisOrientFrictionLoss, "vortex.yAxisOrientFrictionLoss",                    sim_propertytype_float,     0, sim_vortex_joint_a1frictionloss, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexZAxisOrientRelaxStiffness,"vortex.zAxisOrientRelaxationStiffness",            sim_propertytype_float,     0, sim_vortex_joint_a2stiffness, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexZAxisOrientRelaxDamping, "vortex.zAxisOrientRelaxationDamping",               sim_propertytype_float,     0, sim_vortex_joint_a2damping, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexZAxisOrientRelaxLoss,    "vortex.zAxisOrientRelaxationLoss",                  sim_propertytype_float,     0, sim_vortex_joint_a2loss, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexZAxisOrientFrictionCoeff,"vortex.zAxisOrientFrictionCoeff",                   sim_propertytype_float,     0, sim_vortex_joint_a2frictioncoeff, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexZAxisOrientFrictionMaxTorque,"vortex.zAxisOrientFrictionMaxTorque",           sim_propertytype_float,     0, sim_vortex_joint_a2frictionmaxforce, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexZAxisOrientFrictionLoss, "vortex.zAxisOrientFrictionLoss",                    sim_propertytype_float,     0, sim_vortex_joint_a2frictionloss, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_vortexPosPid,                  "vortex.posPid",                                     sim_propertytype_floatarray,   0, sim_vortex_joint_pospid1, sim_vortex_joint_pospid2, sim_vortex_joint_pospid3, -1, -1, "", "") \
    FUNCX(propJoint_newtonPosPid,                  "newton.posPid",                                     sim_propertytype_floatarray,   0, sim_newton_joint_pospid1, sim_newton_joint_pospid2, sim_newton_joint_pospid3, -1, -1, "", "") \
    FUNCX(propJoint_mujocoArmature,                "mujoco.armature",                                   sim_propertytype_float,     0, sim_mujoco_joint_armature, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_mujocoMargin,                  "mujoco.margin",                                     sim_propertytype_float,     0, sim_mujoco_joint_margin, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_mujocoFrictionLoss,            "mujoco.frictionLoss",                               sim_propertytype_float,     0, sim_mujoco_joint_frictionloss, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_mujocoSpringStiffness,         "mujoco.springStiffness",                            sim_propertytype_float,     0, sim_mujoco_joint_stiffness, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_mujocoSpringDamping,           "mujoco.springDamping",                              sim_propertytype_float,     0, sim_mujoco_joint_damping, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_mujocoSpringRef,               "mujoco.springRef",                                  sim_propertytype_float,     0, sim_mujoco_joint_springref, -1, -1, -1, -1, "", "") \
    FUNCX(propJoint_mujocoPosPid,                  "mujoco.posPid",                                     sim_propertytype_floatarray,   0, sim_mujoco_joint_pospid1, sim_mujoco_joint_pospid2, sim_mujoco_joint_pospid3, -1, -1, "", "") \
    FUNCX(propJoint_mujocoLimitsSolRef,            "mujoco.limitsSolref",                               sim_propertytype_floatarray,0, sim_mujoco_joint_solreflimit1, sim_mujoco_joint_solreflimit2, -1, -1, -1, "", "") \
    FUNCX(propJoint_mujocoLimitsSolImp,            "mujoco.limitsSolimp",                               sim_propertytype_floatarray,    0, sim_mujoco_joint_solimplimit1, sim_mujoco_joint_solimplimit2, sim_mujoco_joint_solimplimit3, sim_mujoco_joint_solimplimit4, sim_mujoco_joint_solimplimit5, "", "") \
    FUNCX(propJoint_mujocoFrictionSolRef,          "mujoco.frictionSolref",                             sim_propertytype_floatarray,   0, sim_mujoco_joint_solreffriction1, sim_mujoco_joint_solreffriction2, -1, -1, -1, "", "") \
    FUNCX(propJoint_mujocoFrictionSolImp,          "mujoco.frictionSolimp",                             sim_propertytype_floatarray,    0, sim_mujoco_joint_solimpfriction1, sim_mujoco_joint_solimpfriction2, sim_mujoco_joint_solimpfriction3, sim_mujoco_joint_solimpfriction4, sim_mujoco_joint_solimpfriction5, "", "") \
    FUNCX(propJoint_mujocoSpringDamper,            "mujoco.springSpringDamper",                         sim_propertytype_floatarray,   0, sim_mujoco_joint_springdamper1, sim_mujoco_joint_springdamper2, -1, -1, -1, "", "") \
    FUNCX(propJoint_mujocoDependencyPolyCoef,      "mujoco.dependencyPolyCoeff",                        sim_propertytype_floatarray,    0, sim_mujoco_joint_polycoef1, sim_mujoco_joint_polycoef2, sim_mujoco_joint_polycoef3, sim_mujoco_joint_polycoef4, sim_mujoco_joint_polycoef5, "", "") \

#define FUNCX(name, str, v1, v2, w0, w1, w2, w3, w4, t1, t2) const SJointProperty name = {str, v1, v2, {w0, w1, w2, w3, w4}, t1, t2};
DEFINE_PROPERTIES
#undef FUNCX
#define FUNCX(name, str, v1, v2, w0, w1, w2, w3, w4, t1, t2) name,
const std::vector<SJointProperty> allProps_joint = { DEFINE_PROPERTIES };
#undef FUNCX
#undef DEFINE_PROPERTIES
// ----------------------------------------------------------------------------------------------


enum
{ /* Bullet joint double params */
    simi_bullet_joint_stoperp = 0,
    simi_bullet_joint_stopcfm,
    simi_bullet_joint_normalcfm,
    simi_bullet_joint_free1,
    simi_bullet_joint_free2,
    simi_bullet_joint_pospid1,
    simi_bullet_joint_pospid2,
    simi_bullet_joint_pospid3,
};

enum
{ /* Ode joint double params */
    simi_ode_joint_stoperp = 0,
    simi_ode_joint_stopcfm,
    simi_ode_joint_bounce,
    simi_ode_joint_fudgefactor,
    simi_ode_joint_normalcfm,
    simi_ode_joint_pospid1,
    simi_ode_joint_pospid2,
    simi_ode_joint_pospid3,
};

enum
{ /* Vortex joint double params */
    simi_vortex_joint_lowerlimitdamping = 0,
    simi_vortex_joint_upperlimitdamping,
    simi_vortex_joint_lowerlimitstiffness,
    simi_vortex_joint_upperlimitstiffness,
    simi_vortex_joint_lowerlimitrestitution,
    simi_vortex_joint_upperlimitrestitution,
    simi_vortex_joint_lowerlimitmaxforce,
    simi_vortex_joint_upperlimitmaxforce,
    simi_vortex_joint_motorconstraintfrictioncoeff,
    simi_vortex_joint_motorconstraintfrictionmaxforce,
    simi_vortex_joint_motorconstraintfrictionloss,
    simi_vortex_joint_p0loss,
    simi_vortex_joint_p0stiffness,
    simi_vortex_joint_p0damping,
    simi_vortex_joint_p0frictioncoeff,
    simi_vortex_joint_p0frictionmaxforce,
    simi_vortex_joint_p0frictionloss,
    simi_vortex_joint_p1loss,
    simi_vortex_joint_p1stiffness,
    simi_vortex_joint_p1damping,
    simi_vortex_joint_p1frictioncoeff,
    simi_vortex_joint_p1frictionmaxforce,
    simi_vortex_joint_p1frictionloss,
    simi_vortex_joint_p2loss,
    simi_vortex_joint_p2stiffness,
    simi_vortex_joint_p2damping,
    simi_vortex_joint_p2frictioncoeff,
    simi_vortex_joint_p2frictionmaxforce,
    simi_vortex_joint_p2frictionloss,
    simi_vortex_joint_a0loss,
    simi_vortex_joint_a0stiffness,
    simi_vortex_joint_a0damping,
    simi_vortex_joint_a0frictioncoeff,
    simi_vortex_joint_a0frictionmaxforce,
    simi_vortex_joint_a0frictionloss,
    simi_vortex_joint_a1loss,
    simi_vortex_joint_a1stiffness,
    simi_vortex_joint_a1damping,
    simi_vortex_joint_a1frictioncoeff,
    simi_vortex_joint_a1frictionmaxforce,
    simi_vortex_joint_a1frictionloss,
    simi_vortex_joint_a2loss,
    simi_vortex_joint_a2stiffness,
    simi_vortex_joint_a2damping,
    simi_vortex_joint_a2frictioncoeff,
    simi_vortex_joint_a2frictionmaxforce,
    simi_vortex_joint_a2frictionloss,
    simi_vortex_joint_dependencyfactor, // deprecated
    simi_vortex_joint_dependencyoffset, // deprecated
    simi_vortex_joint_free1,
    simi_vortex_joint_free2,
    simi_vortex_joint_pospid1,
    simi_vortex_joint_pospid2,
    simi_vortex_joint_pospid3,
};

enum
{ /* Vortex joint int params */
    simi_vortex_joint_bitcoded = 0,
    simi_vortex_joint_relaxationenabledbc,
    simi_vortex_joint_frictionenabledbc,
    simi_vortex_joint_frictionproportionalbc,
    simi_vortex_joint_objectid,         // deprecated
    simi_vortex_joint_dependentobjectid // deprecated
};

enum
{ /* Vortex joint bit params */
    simi_vortex_joint_motorfrictionenabled = 1,
    simi_vortex_joint_proportionalmotorfriction = 2
};

enum
{                                           /* Newton joint double params */
    simi_newton_joint_dependencyfactor = 0, // deprecated
    simi_newton_joint_dependencyoffset,     // deprecated
    simi_newton_joint_pospid1,
    simi_newton_joint_pospid2,
    simi_newton_joint_pospid3,
};

enum
{                                       /* Newton joint int params */
    simi_newton_joint_objectid = 0,     // deprecated
    simi_newton_joint_dependentobjectid // deprecated
};

enum
{ /* Mujoco joint double params */
    simi_mujoco_joint_solreflimit1 = 0,
    simi_mujoco_joint_solreflimit2,
    simi_mujoco_joint_solimplimit1,
    simi_mujoco_joint_solimplimit2,
    simi_mujoco_joint_solimplimit3,
    simi_mujoco_joint_solimplimit4,
    simi_mujoco_joint_solimplimit5,
    simi_mujoco_joint_frictionloss,
    simi_mujoco_joint_solreffriction1,
    simi_mujoco_joint_solreffriction2,
    simi_mujoco_joint_solimpfriction1,
    simi_mujoco_joint_solimpfriction2,
    simi_mujoco_joint_solimpfriction3,
    simi_mujoco_joint_solimpfriction4,
    simi_mujoco_joint_solimpfriction5,
    simi_mujoco_joint_stiffness,
    simi_mujoco_joint_damping,
    simi_mujoco_joint_springref,
    simi_mujoco_joint_springdamper1,
    simi_mujoco_joint_springdamper2,
    simi_mujoco_joint_armature,
    simi_mujoco_joint_margin,
    simi_mujoco_joint_polycoef1, // deprecated
    simi_mujoco_joint_polycoef2, // deprecated
    simi_mujoco_joint_polycoef3,
    simi_mujoco_joint_polycoef4,
    simi_mujoco_joint_polycoef5,
    simi_mujoco_joint_pospid1,
    simi_mujoco_joint_pospid2,
    simi_mujoco_joint_pospid3,
};

enum
{                                       /* Mujoco joint int params */
    simi_mujoco_joint_objectid = 0,     // deprecated
    simi_mujoco_joint_dependentobjectid // deprecated
};

class CJoint : public CSceneObject
{
  public:
    CJoint(); // default, use only during serialization!
    CJoint(int jointType);
    virtual ~CJoint();

    void buildOrUpdate_oldIk();
    void connect_oldIk();

    // Following functions are inherited from CSceneObject
    void addSpecializedObjectEventData(CCbor *ev);
    CSceneObject *copyYourself();
    void removeSceneDependencies();
    void scaleObject(double scalingFactor);
    void serialize(CSer &ar);
    void announceCollectionWillBeErased(int groupID, bool copyBuffer);
    void announceCollisionWillBeErased(int collisionID, bool copyBuffer);
    void announceDistanceWillBeErased(int distanceID, bool copyBuffer);
    void announceObjectWillBeErased(const CSceneObject *object, bool copyBuffer);
    void announceIkObjectWillBeErased(int ikGroupID, bool copyBuffer);
    void performObjectLoadingMapping(const std::map<int, int> *map, bool loadingAmodel);
    void performIkLoadingMapping(const std::map<int, int> *map, bool loadingAmodel);
    void performCollectionLoadingMapping(const std::map<int, int> *map, bool loadingAmodel);
    void performCollisionLoadingMapping(const std::map<int, int> *map, bool loadingAmodel);
    void performDistanceLoadingMapping(const std::map<int, int> *map, bool loadingAmodel);
    void performTextureObjectLoadingMapping(const std::map<int, int> *map);
    void performDynMaterialObjectLoadingMapping(const std::map<int, int> *map);
    void simulationAboutToStart();
    void simulationEnded();
    void initializeInitialValues(bool simulationAlreadyRunning);
    void computeBoundingBox();
    void setIsInScene(bool s);

    int setBoolProperty(const char* pName, bool pState, CCbor* eev = nullptr);
    int getBoolProperty(const char* pName, bool& pState) const;
    int setIntProperty(const char* pName, int pState, CCbor* eev = nullptr);
    int getIntProperty(const char* pName, int& pState) const;
    int setFloatProperty(const char* pName, double pState, CCbor* eev = nullptr);
    int getFloatProperty(const char* pName, double& pState) const;
    int setIntArray2Property(const char* pName, const int* pState, CCbor* eev = nullptr);
    int getIntArray2Property(const char* pName, int* pState) const;
    int setVector2Property(const char* pName, const double* pState, CCbor* eev = nullptr);
    int getVector2Property(const char* pName, double* pState) const;
    int setVector3Property(const char* pName, const C3Vector& pState, CCbor* eev = nullptr);
    int getVector3Property(const char* pName, C3Vector& pState) const;
    int setStringProperty(const char* pName, const char* pState);
    int getStringProperty(const char* pName, std::string& pState) const;
    int setQuaternionProperty(const char* pName, const C4Vector& pState);
    int getQuaternionProperty(const char* pName, C4Vector& pState) const;
    int getPoseProperty(const char* pName, C7Vector& pState) const;
    int setColorProperty(const char* pName, const float* pState);
    int getColorProperty(const char* pName, float* pState) const;
    int setFloatArrayProperty(const char* pName, const double* v, int vL, CCbor* eev = nullptr);
    int getFloatArrayProperty(const char* pName, std::vector<double>& pState) const;
    int getPropertyName(int& index, std::string& pName, std::string& appartenance) const;
    static int getPropertyName_static(int& index, std::string& pName, std::string& appartenance);
    int getPropertyInfo(const char* pName, int& info, std::string& infoTxt) const;
    static int getPropertyInfo_static(const char* pName, int& info, std::string& infoTxt);
    // Some helpers:
    bool getBoolPropertyValue(const char* pName) const;
    int getIntPropertyValue(const char* pName) const;
    double getFloatPropertyValue(const char* pName) const;

    // Overridden from CSceneObject:
    virtual C7Vector getIntrinsicTransformation(bool includeDynErrorComponent, bool *available = nullptr) const;
    virtual C7Vector getFullLocalTransformation() const;

    std::string getObjectTypeInfo() const;
    std::string getObjectTypeInfoExtended() const;

    double getLength() const;
    double getDiameter() const;
    double getPosition() const;
    double getTargetVelocity() const;
    bool getMotorLock() const;
    double getTargetForce(bool signedValue) const;
    int getDynCtrlMode() const;
    int getDynVelCtrlType() const;
    int getDynPosCtrlType() const;
    double getEngineFloatParam_old(int what, bool *ok) const;
    int getEngineIntParam_old(int what, bool *ok) const;
    bool getEngineBoolParam_old(int what, bool *ok) const;

    void getVortexFloatParams(std::vector<double> &p) const;
    void getVortexIntParams(std::vector<int> &p) const;
    void getNewtonFloatParams(std::vector<double> &p) const;
    void getNewtonIntParams(std::vector<int> &p) const;
    int getVortexDependentJointId() const;
    int getNewtonDependentJointId() const;
    int getMujocoDependentJointId() const;
    void getMaxVelAccelJerk(double maxVelAccelJerk[3]) const;
    double getScrewLead() const;
    int getJointType() const;
    C4Vector getSphericalTransformation() const;
    bool getIsCyclic() const;
    void getInterval(double& minV, double& maxV) const;
    int getJointMode() const;
    int getDependencyMasterJointHandle() const;
    void getDependencyParams(double& off, double& mult) const;
    void getPid(double &p_param, double &i_param, double &d_param, int engine = -1) const;
    void getKc(double &k_param, double &c_param) const;
    double getTargetPosition() const;
    CColorObject *getColor(bool part2);

    double getMeasuredJointVelocity() const;
    std::string getDependencyJointLoadAlias() const;
    int getJointCallbackCallOrder_backwardCompatibility() const;
    void setDirectDependentJoints(const std::vector<CJoint *> &joints);

    void setInterval(double minV, double maxV);
    void setIsCyclic(bool isCyclic);
    void setSize(double l = 0.0, double d = 0.0);
    void setMaxVelAccelJerk(const double maxVelAccelJerk[3]);
    bool setScrewLead(double lead);
    void setDependencyMasterJointHandle(int depJointID);
    void setDependencyParams(double off, double mult);
    void setVelocity(double vel, const CJoint *masterJoint = nullptr);
    void setPosition(double pos, const CJoint *masterJoint = nullptr, bool setDirect = false);
    void setSphericalTransformation(const C4Vector &tr);
    void setJointMode(int theMode);

    void setIntrinsicTransformationError(const C7Vector &tr);

    void setTargetVelocity(double v);
    void setTargetPosition(double pos);
    void setKc(double k_param, double c_param);
    void setTargetForce(double f, bool isSigned);
    void setDynCtrlMode(int mode);
    void setDynVelCtrlType(int mode);
    void setDynPosCtrlType(int mode);

    bool setJointMode_noDynMotorTargetPosCorrection(int newMode);

    void setMotorLock(bool e);

    void measureJointVelocity(double simTime);

    void getDynamicJointErrors(double &linear, double &angular) const;
    void getDynamicJointErrorsFull(C3Vector &linear, C3Vector &angular) const;

    void handleMotion();
    int handleDynJoint(int flags, const int intVals[3], double currentPosVelAccel[3], double effort, double dynStepSize, double errorV, double velAndForce[2]);

    void setDynamicMotorReflectedPosition_useOnlyFromDynamicPart(double rfp, double simTime);

    void addCumulativeForceOrTorque(double forceOrTorque, int countForAverage);
    bool getDynamicForceOrTorque(double &forceOrTorque, bool dynamicStepValue) const;
    void setForceOrTorqueNotValid();

    void setKinematicMotionType(int t, bool reset, double initVel = 0.0);
    int getKinematicMotionType() const;

    bool setEngineFloatParam_old(int what, double v);
    bool setEngineIntParam_old(int what, int v);
    bool setEngineBoolParam_old(int what, bool v);

    void copyEnginePropertiesTo(CJoint *target);

    // DEPRECATED:
    bool getHybridFunctionality_old() const;
    double getIKWeight_old() const;
    double getMaxStepSize_old() const;
    std::string getDependencyJointLoadName_old() const;
    void setIKWeight_old(double newWeight);
    void setMaxStepSize_old(double stepS);
    void setHybridFunctionality_old(bool h);
    void setExplicitHandling_DEPRECATED(bool explicitHandl);
    bool getExplicitHandling_DEPRECATED();
    void resetJoint_DEPRECATED();
    void handleJoint_DEPRECATED(double deltaTime);
    void setUnlimitedAcceleration_DEPRECATED(bool unlimited);
    bool getUnlimitedAcceleration_DEPRECATED();
    void setInvertTargetVelocityAtLimits_DEPRECATED(bool invert);
    bool getInvertTargetVelocityAtLimits_DEPRECATED();
    void setMaxAcceleration_DEPRECATED(double maxAccel);
    double getMaxAcceleration_DEPRECATED();
    void setVelocity_DEPRECATED(double vel);
    double getVelocity_DEPRECATED();
    void setPid_old(double p_param, double i_param, double d_param);

  protected:
    void _setForceOrTorque(bool valid, double f = 0.0);
    void _setFilteredForceOrTorque(bool valid, double f = 0.0);
    void _sendEngineString(CCbor* eev = nullptr);
    std::string _enumToProperty(int oldEnum, int type, int& indexWithArrays) const;
    void updateSelfAsSlave();
    void _fixVortexInfVals();

    void _commonInit();

    std::vector<CJoint *> _directDependentJoints;

    std::string _dependencyJointLoadAlias;

    double _initialPosition;
    double _initialTargetPosition;
    double _initialTargetVelocity;
    C4Vector _initialSphericalJointTransformation;
    int _initialJointMode;

    int _initialDynCtrlMode;
    int _initialDynVelocityCtrlType;
    int _initialDynPositionCtrlType;
    bool _initialDynCtrl_lockAtVelZero;
    double _initialDynCtrl_force;
    double _initialDynCtrl_kc[3];

    bool _initialHybridOperation;

    double _initialMaxVelAccelJerk[3];

    double _velCalc_vel;
    double _velCalc_prevPos;
    double _velCalc_prevSimTime;
    bool _velCalc_prevPosValid;

    double _dynPosCtrl_currentVelAccel[2];
    double _dynVelCtrl_currentVelAccel[2];
    double _dynCtrl_previousVelForce[2];

    double _filteredForceOrTorque;
    bool _filteredForceOrTorqueValid;
    double _cumulativeForceOrTorqueTmp;
    int _kinematicMotionType; // 0=none, 1=pos ctrl, 2=vel ctrl, bit4 (16): reset motion
    double _kinematicMotionInitVel;

    int _jointType;
    double _length;
    double _diameter;
    C4Vector _sphericalTransf; // spherical joints don't have a range anymore since 22.10.2022
    bool _isCyclic;
    double _screwLead; // distance along the screw's axis for one complete rotation of the screw
    double _posMin;
    double _posRange;
    double _pos;
    double _targetVel; // signed. Should be same sign as _targetForce (however _targetVel has precedence when conflict)
    double _targetPos;
    int _jointMode;
    int _dependencyMasterJointHandle;
    double _dependencyJointMult;
    double _dependencyJointOffset;

    double _maxVelAccelJerk[3];

    CColorObject _color;
    CColorObject _color_removeSoon;

    bool _motorLock;     // deprecated, should not be used anymore
    double _targetForce; // signed. Should be same sign as _targetVel (however _targetVel has precedence when conflict)
    double _dynCtrl_pid_cumulErr;

    double _dynCtrl_kc[2];
    int _dynCtrlMode;
    int _dynPositionCtrlType; // built-in position mode + pos PID (0) or Ruckig (1)
    int _dynVelocityCtrlType; // built-in velocity mode (0) or Ruckig (1)

    bool _jointHasHybridFunctionality;

    std::vector<double> _bulletFloatParams;
    std::vector<int> _bulletIntParams;

    std::vector<double> _odeFloatParams;
    std::vector<int> _odeIntParams;

    std::vector<double> _vortexFloatParams;
    std::vector<int> _vortexIntParams;

    std::vector<double> _newtonFloatParams;
    std::vector<int> _newtonIntParams;

    std::vector<double> _mujocoFloatParams;
    std::vector<int> _mujocoIntParams;

    C7Vector _intrinsicTransformationError; // from physics engine

    // Following is the force/torque acquired during a single dyn. calculation step:
    double _lastForceOrTorque_dynStep;
    bool _lastForceOrTorqueValid_dynStep;

    // DEPRECATED:
    void _sendDependencyChange_old() const;
    void _setPositionIntervalMin_sendOldIk(double min) const;
    void _setPositionIntervalRange_sendOldIk(double range) const;
    void _setPositionIsCyclic_sendOldIk(bool isCyclic) const;
    void _setScrewPitch_sendOldIk(double pitch) const;
    void _setDependencyJointHandle_sendOldIk(int depJointID) const;
    void _setDependencyJointMult_sendOldIk(double coeff) const;
    void _setDependencyJointOffset_sendOldIk(double off) const;
    void _setIkWeight_sendOldIk(double newWeight) const;
    void _setMaxStepSize_sendOldIk(double stepS) const;
    void _setPosition_sendOldIk(double pos) const;
    void _setSphericalTransformation_sendOldIk(const C4Vector &tr) const;
    void _setJointMode_sendOldIk(int theMode) const;
    double _maxStepSize_old;
    double _ikWeight_old;
    std::string _dependencyJointLoadName_old;
    double _jointPositionForMotionHandling_DEPRECATED;
    double _velocity_DEPRECATED;
    bool _explicitHandling_DEPRECATED;
    bool _unlimitedAcceleration_DEPRECATED;
    bool _invertTargetVelocityAtLimits_DEPRECATED;
    double _maxAcceleration_DEPRECATED;
    int _jointCallbackCallOrder_backwardCompatibility;
    double _initialVelocity_DEPRECATED;
    bool _initialExplicitHandling_DEPRECATED;

#ifdef SIM_WITH_GUI
  public:
    void display(CViewableBase *renderingObject, int displayAttrib);
#endif
};
