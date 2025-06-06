const SLuaCommands simLuaCommandsOldApi[] =
    { // Following for backward compatibility (has now a new notation (see 'simLuaCommands'))
        {"sim0.simHandlePath", _simHandlePath},
        {"sim0.simHandleJoint", _simHandleJoint},
        {"sim0.simGetScriptName", _simGetScriptName},
        {"sim0.simGetObjectAssociatedWithScript", _simGetObjectAssociatedWithScript},
        {"sim0.simGetScriptAssociatedWithObject", _simGetScriptAssociatedWithObject},
        {"sim0.simGetCustomizationScriptAssociatedWithObject", _simGetCustomizationScriptAssociatedWithObject},
        {"sim0.simOpenModule", _simOpenModule},
        {"sim0.simCloseModule", _simCloseModule},
        {"sim0.simHandleModule", _simHandleModule},
        {"sim0.simHandleDynamics", _simHandleDynamics},
        {"sim0.simHandleProximitySensor", _simHandleProximitySensor},
        {"sim0.simReadProximitySensor", _simReadProximitySensor},
        {"sim0.simResetProximitySensor", _simResetProximitySensor},
        {"sim0.simCheckProximitySensor", _simCheckProximitySensor},
        {"sim0.simCheckProximitySensorEx", _simCheckProximitySensorEx},
        {"sim0.simCheckProximitySensorEx2", _simCheckProximitySensorEx2},
        {"sim0.simGetObjectHandle", _sim_getObjectHandle},
        {"sim0.simAddScript", _simAddScript},
        {"sim0.simAssociateScriptWithObject", _simAssociateScriptWithObject},
        {"sim0.simSetScriptText", _simSetScriptText},
        {"sim0.simGetScriptHandle", _simGetScriptHandle},
        {"sim0.simGetObjectPosition", _simGetObjectPosition},
        {"sim0.simGetObjectOrientation", _simGetObjectOrientation},
        {"sim0.simSetObjectPosition", _simSetObjectPosition},
        {"sim0.simSetObjectOrientation", _simSetObjectOrientation},
        {"sim0.simGetJointPosition", _simGetJointPosition},
        {"sim0.simSetJointPosition", _simSetJointPosition},
        {"sim0.simSetJointTargetPosition", _simSetJointTargetPosition},
        {"sim0.simGetJointTargetPosition", _simGetJointTargetPosition},
        {"sim0.simSetJointForce", _simSetJointMaxForce},
        {"sim0.simSetJointTargetVelocity", _simSetJointTargetVelocity},
        {"sim0.simGetJointTargetVelocity", _simGetJointTargetVelocity},
        {"sim0.simGetObjectName", _simGetObjectName},
        {"sim0.simSetObjectName", _simSetObjectName},
        {"sim0.simRemoveObject", _simRemoveObject},
        {"sim0.simRemoveModel", _simRemoveModel},
        {"sim0.simGetSimulationTime", _simGetSimulationTime},
        {"sim0.simGetSimulationState", _simGetSimulationState},
        {"sim0.simGetSystemTime", _simGetSystemTime},
        {"sim0.simGetSystemTimeInMs", _simGetSystemTimeInMs},
        {"sim0.simCheckCollision", _simCheckCollision},
        {"sim0.simCheckCollisionEx", _simCheckCollisionEx},
        {"sim0.simCheckDistance", _simCheckDistance},
        {"sim0.simGetObjectConfiguration", _simGetObjectConfiguration},
        {"sim0.simSetObjectConfiguration", _simSetObjectConfiguration},
        {"sim0.simGetConfigurationTree", _simGetConfigurationTree},
        {"sim0.simSetConfigurationTree", _simSetConfigurationTree},
        {"sim0.simGetSimulationTimeStep", _simGetSimulationTimeStep},
        {"sim0.simGetSimulatorMessage", _simGetSimulatorMessage},
        {"sim0.simResetGraph", _simResetGraph},
        {"sim0.simHandleGraph", _simHandleGraph},
        {"sim0.simGetLastError", _simGetLastError},
        {"sim0.simGetObjects", _simGetObjects},
        {"sim0.simRefreshDialogs", _simRefreshDialogs},
        {"sim0.simGetModuleName", _simGetPluginName},
        {"sim0.simRemoveScript", _simRemoveScript},
        {"sim0.simStopSimulation", _simStopSimulation},
        {"sim0.simPauseSimulation", _simPauseSimulation},
        {"sim0.simStartSimulation", _simStartSimulation},
        {"sim0.simGetObjectMatrix", _simGetObjectMatrix},
        {"sim0.simSetObjectMatrix", _simSetObjectMatrix},
        {"sim0.simGetJointMatrix", _simGetJointMatrix},
        {"sim0.simSetSphericalJointMatrix", _simSetSphericalJointMatrix},
        {"sim0.simBuildIdentityMatrix", _simBuildIdentityMatrix},
        {"sim0.simBuildMatrix", _simBuildMatrix},
        {"sim0.simGetEulerAnglesFromMatrix", _simGetEulerAnglesFromMatrix},
        {"sim0.simInvertMatrix", _simInvertMatrix},
        {"sim0.simMultiplyMatrices", _simMultiplyMatrices},
        {"sim0.simInterpolateMatrices", _simInterpolateMatrices},
        {"sim0.simMultiplyVector", _simMultiplyVector},
        {"sim0.simGetObjectChild", _simGetObjectChild},
        {"sim0.simGetObjectParent", _simGetObjectParent},
        {"sim0.simSetObjectParent", _simSetObjectParent},
        {"sim0.simGetObjectType", _simGetObjectType},
        {"sim0.simGetJointType", _simGetJointType},
        {"sim0.simSetBoolParameter", _simSetBoolParam},
        {"sim0.simGetBoolParameter", _simGetBoolParam},
        {"sim0.simSetInt32Parameter", _simSetInt32Param},
        {"sim0.simGetInt32Parameter", _simGetInt32Param},
        {"sim0.simSetFloatParameter", _simSetFloatParam},
        {"sim0.simGetFloatParameter", _simGetFloatParam},
        {"sim0.simSetStringParameter", _simSetStringParam},
        {"sim0.simGetStringParameter", _simGetStringParam},
        {"sim0.simSetArrayParameter", _simSetArrayParam},
        {"sim0.simGetArrayParameter", _simGetArrayParam},
        {"sim0.simGetJointInterval", _simGetJointInterval},
        {"sim0.simSetJointInterval", _simSetJointInterval},
        {"sim0.simLoadScene", _simLoadScene},
        {"sim0.simSaveScene", _simSaveScene},
        {"sim0.simLoadModel", _simLoadModel},
        {"sim0.simSaveModel", _simSaveModel},
        {"sim0.simIsObjectInSelection", _simIsObjectInSelection},
        {"sim0.simAddObjectToSelection", _simAddObjectToSelection},
        {"sim0.simRemoveObjectFromSelection", _simRemoveObjectFromSelection},
        {"sim0.simGetObjectSelection", _simGetObjectSel},
        {"sim0.simGetRealTimeSimulation", _simGetRealTimeSimulation},
        {"sim0.simSetNavigationMode", _simSetNavigationMode},
        {"sim0.simGetNavigationMode", _simGetNavigationMode},
        {"sim0.simSetPage", _simSetPage},
        {"sim0.simGetPage", _simGetPage},
        {"sim0.simCopyPasteObjects", _simCopyPasteObjects},
        {"sim0.simScaleObjects", _simScaleObjects},
        {"sim0.simGetObjectUniqueIdentifier", _simGetObjectUniqueIdentifier},
        {"sim0.simSetThreadAutomaticSwitch", _setAutoYield},
        {"sim0.simGetThreadAutomaticSwitch", _getAutoYield},
        {"sim0.simSetThreadSwitchTiming", _simSetThreadSwitchTimingOLD},
        {"sim0.simSwitchThread", _simSwitchThread},
        {"sim0.simSaveImage", _simSaveImage},
        {"sim0.simLoadImage", _simLoadImage},
        {"sim0.simGetScaledImage", _simGetScaledImage},
        {"sim0.simTransformImage", _simTransformImage},
        {"sim0.simGetQHull", _sim_qhull},
        {"sim0.simGetDecimatedMesh", _simGetDecimatedMesh},
        {"sim0.simPackInt32Table", _simPackInt32Table},
        {"sim0.simPackUInt32Table", _simPackUInt32Table},
        {"sim0.simPackFloatTable", _simPackFloatTable},
        {"sim0.simPackDoubleTable", _simPackDoubleTable},
        {"sim0.simPackUInt8Table", _simPackUInt8Table},
        {"sim0.simPackUInt16Table", _simPackUInt16Table},
        {"sim0.simUnpackInt32Table", _simUnpackInt32Table},
        {"sim0.simUnpackUInt32Table", _simUnpackUInt32Table},
        {"sim0.simUnpackFloatTable", _simUnpackFloatTable},
        {"sim0.simUnpackDoubleTable", _simUnpackDoubleTable},
        {"sim0.simUnpackUInt8Table", _simUnpackUInt8Table},
        {"sim0.simUnpackUInt16Table", _simUnpackUInt16Table},
        {"sim0.simPackTable", _simPackTable},
        {"sim0.simUnpackTable", _simUnpackTable},
        {"sim0.simTransformBuffer", _simTransformBuffer},
        {"sim0.simCombineRgbImages", _simCombineRgbImages},
        {"sim0.simGetVelocity", _simGetVelocity},
        {"sim0.simGetObjectVelocity", _simGetObjectVelocity},
        {"sim0.simAddForceAndTorque", _simAddForceAndTorque},
        {"sim0.simAddForce", _simAddForce},
        {"sim0.simSetExplicitHandling", _simSetExplicitHandling},
        {"sim0.simGetExplicitHandling", _simGetExplicitHandling},
        {"sim0.simAddDrawingObject", _simAddDrawingObject},
        {"sim0.simRemoveDrawingObject", _simRemoveDrawingObject},
        {"sim0.simAddDrawingObjectItem", _simAddDrawingObjectItem},
        {"sim0.simAddParticleObject", _simAddParticleObject},
        {"sim0.simRemoveParticleObject", _simRemoveParticleObject},
        {"sim0.simAddParticleObjectItem", _simAddParticleObjectItem},
        {"sim0.simGetObjectSizeFactor", _simGetObjectSizeFactor},
        {"sim0.simSetIntegerSignal", _simSetInt32Signal},
        {"sim0.simGetIntegerSignal", _simGetInt32Signal},
        {"sim0.simClearIntegerSignal", _simClearInt32Signal},
        {"sim0.simSetFloatSignal", _simSetFloatSignal},
        {"sim0.simGetFloatSignal", _simGetFloatSignal},
        {"sim0.simClearFloatSignal", _simClearFloatSignal},
        {"sim0.simSetStringSignal", _simSetStringSignal},
        {"sim0.simGetStringSignal", _simGetStringSignal},
        {"sim0.simClearStringSignal", _simClearStringSignal},
        {"sim0.simGetSignalName", _simGetSignalName},
        {"sim0.simPersistentDataWrite", _simPersistentDataWrite},
        {"sim0.simPersistentDataRead", _simPersistentDataRead},
        {"sim0.simSetObjectProperty", _simSetObjectProperty},
        {"sim0.simGetObjectProperty", _simGetObjectProperty},
        {"sim0.simSetObjectSpecialProperty", _simSetObjectSpecialProperty},
        {"sim0.simGetObjectSpecialProperty", _simGetObjectSpecialProperty},
        {"sim0.simSetModelProperty", _simSetModelProperty},
        {"sim0.simGetModelProperty", _simGetModelProperty},
        {"sim0.simReadForceSensor", _simReadForceSensor},
        {"sim0.simBreakForceSensor", _simBreakForceSensor},
        {"sim0.simGetLightParameters", _simGetLightParameters},
        {"sim0.simSetLightParameters", _simSetLightParameters},
        {"sim0.simGetLinkDummy", _simGetLinkDummy},
        {"sim0.simSetLinkDummy", _simSetLinkDummy},
        {"sim0.simSetShapeColor", _simSetShapeColor},
        {"sim0.simGetShapeColor", _simGetShapeColor},
        {"sim0.simResetDynamicObject", _simResetDynamicObject},
        {"sim0.simSetJointMode", _simSetJointMode},
        {"sim0.simGetJointMode", _simGetJointMode},
        {"sim0.simSerialSend", _simSerialSend},
        {"sim0.simSerialCheck", _simSerialCheck},
        {"sim0.simGetContactInfo", _simGetContactInfo},
        {"sim0.simAuxiliaryConsoleOpen", _simAuxiliaryConsoleOpen},
        {"sim0.simAuxiliaryConsoleClose", _simAuxiliaryConsoleClose},
        {"sim0.simAuxiliaryConsolePrint", _simAuxiliaryConsolePrint},
        {"sim0.simAuxiliaryConsoleShow", _simAuxiliaryConsoleShow},
        {"sim0.simImportShape", _simImportShape},
        {"sim0.simImportMesh", _simImportMesh},
        {"sim0.simExportMesh", _simExportMesh},
        {"sim0.simCreateMeshShape", _simCreateMeshShape},
        {"sim0.simGetShapeMesh", _simGetShapeMesh},
        {"sim0.simCreatePureShape", _simCreatePureShape},
        {"sim0.simCreateHeightfieldShape", _simCreateHeightfieldShape},
        {"sim0.simCreateJoint", _simCreateJoint},
        {"sim0.simCreateDummy", _simCreateDummy},
        {"sim0.simCreateProximitySensor", _simCreateProximitySensor},
        {"sim0.simCreateForceSensor", _simCreateForceSensor},
        {"sim0.simCreateVisionSensor", _simCreateVisionSensor},
        {"sim0.simFloatingViewAdd", _simFloatingViewAdd},
        {"sim0.simFloatingViewRemove", _simFloatingViewRemove},
        {"sim0.simAdjustView", _simAdjustView},
        {"sim0.simCameraFitToView", _simCameraFitToView},
        {"sim0.simAnnounceSceneContentChange", _simAnnounceSceneContentChange},
        {"sim0.simGetObjectInt32Parameter", _simGetObjectInt32Parameter},
        {"sim0.simSetObjectInt32Parameter", _simSetObjectInt32Param},
        {"sim0.simGetObjectFloatParameter", _simGetObjectFloatParameter},
        {"sim0.simSetObjectFloatParameter", _simSetObjectFloatParam},
        {"sim0.simGetObjectStringParameter", _simGetObjectStringParam},
        {"sim0.simSetObjectStringParameter", _simSetObjectStringParam},
        {"sim0.simGetRotationAxis", _simGetRotationAxis},
        {"sim0.simRotateAroundAxis", _simRotateAroundAxis},
        {"sim0.simLaunchExecutable", _simLaunchExecutable},
        {"sim0.simGetJointForce", _simGetJointForce},
        {"sim0.simIsHandleValid", _simIsHandleValid},
        {"sim0.simGetObjectQuaternion", _simGetObjectQuaternion},
        {"sim0.simSetObjectQuaternion", _simSetObjectQuaternion},
        {"sim0.simSetShapeMassAndInertia", _simSetShapeMassAndInertia},
        {"sim0.simGetShapeMassAndInertia", _simGetShapeMassAndInertia},
        {"sim0.simGroupShapes", _simGroupShapes},
        {"sim0.simUngroupShape", _simUngroupShape},
        {"sim0.simQuitSimulator", _quitSimulator},
        {"sim0.simGetThreadId", _simGetThreadId},
        {"sim0.simSetShapeMaterial", _simSetShapeMaterial},
        {"sim0.simGetTextureId", _simGetTextureId},
        {"sim0.simReadTexture", _simReadTexture},
        {"sim0.simWriteTexture", _simWriteTexture},
        {"sim0.simCreateTexture", _simCreateTexture},
        {"sim0.simWriteCustomDataBlock", _simWriteCustomStringData},
        {"sim0.simReadCustomDataBlock", _simReadCustomStringData},
        {"sim0.simReadCustomDataBlockTags", _simReadCustomDataTags},
        {"sim0.simGetShapeGeomInfo", _simGetShapeGeomInfo},
        {"sim0.simGetObjectsInTree", _simGetObjectsInTree},
        {"sim0.simSetObjectSizeValues", _simSetObjectSizeValues},
        {"sim0.simGetObjectSizeValues", _simGetObjectSizeValues},
        {"sim0.simScaleObject", _simScaleObject},
        {"sim0.simSetShapeTexture", _simSetShapeTexture},
        {"sim0.simGetShapeTextureId", _simGetShapeTextureId},
        {"sim0.simGetCollectionObjects", _simGetCollectionObjects},
        {"sim0.simHandleCustomizationScripts", _simHandleCustomizationScripts},
        {"sim0.simSetScriptAttribute", _simSetScriptAttribute},
        {"sim0.simGetScriptAttribute", _simGetScriptAttribute},
        {"sim0.simHandleChildScripts", _simHandleSimulationScripts},
        {"sim0.simReorientShapeBoundingBox", _simReorientShapeBoundingBox},
        {"sim0.simHandleVisionSensor", _simHandleVisionSensor},
        {"sim0.simReadVisionSensor", _simReadVisionSensor},
        {"sim0.simResetVisionSensor", _simResetVisionSensor},
        {"sim0.simGetVisionSensorResolution", _simGetVisionSensorResolution},
        {"sim0.simGetVisionSensorImage", _simGetVisionSensorImage},
        {"sim0.simSetVisionSensorImage", _simSetVisionSensorImage},
        {"sim0.simGetVisionSensorCharImage", _simGetVisionSensorCharImage},
        {"sim0.simSetVisionSensorCharImage", _simSetVisionSensorCharImage},
        {"sim0.simGetVisionSensorDepthBuffer", _simGetVisionSensorDepthBuffer},
        {"sim0.simCheckVisionSensor", _simCheckVisionSensor},
        {"sim0.simCheckVisionSensorEx", _simCheckVisionSensorEx},
        {"sim0.simRMLPos", _simRuckigPos},
        {"sim0.simRMLVel", _simRuckigVel},
        {"sim0.simRMLStep", _simRuckigStep},
        {"sim0.simRMLRemove", _simRuckigRemove},
        {"sim0.simBuildMatrixQ", _simBuildMatrixQ},
        {"sim0.simGetQuaternionFromMatrix", _simGetQuaternionFromMatrix},
        {"sim0.simFileDialog", _simFileDialog},
        {"sim0.simMsgBox", _simMsgBox},
        {"sim0.simLoadModule", _simLoadModule},
        {"sim0.simUnloadModule", _simUnloadModule},
        {"sim0.simCallScriptFunction", _simCallScriptFunction},
        {"sim0.simGetExtensionString", _simGetExtensionString},
        {"sim0.simComputeMassAndInertia", _simComputeMassAndInertia},
        {"sim0.simSetScriptVariable", _simSetScriptVariable},
        {"sim0.simGetEngineFloatParameter", _simGetEngineFloatParam},
        {"sim0.simGetEngineInt32Parameter", _simGetEngineInt32Param},
        {"sim0.simGetEngineBoolParameter", _simGetEngineBoolParam},
        {"sim0.simSetEngineFloatParameter", _simSetEngineFloatParam},
        {"sim0.simSetEngineInt32Parameter", _simSetEngineInt32Param},
        {"sim0.simSetEngineBoolParameter", _simSetEngineBoolParam},
        {"sim0.simCreateOctree", _simCreateOctree},
        {"sim0.simCreatePointCloud", _simCreatePointCloud},
        {"sim0.simSetPointCloudOptions", _simSetPointCloudOptions},
        {"sim0.simGetPointCloudOptions", _simGetPointCloudOptions},
        {"sim0.simInsertVoxelsIntoOctree", _simInsertVoxelsIntoOctree},
        {"sim0.simRemoveVoxelsFromOctree", _simRemoveVoxelsFromOctree},
        {"sim0.simInsertPointsIntoPointCloud", _simInsertPointsIntoPointCloud},
        {"sim0.simRemovePointsFromPointCloud", _simRemovePointsFromPointCloud},
        {"sim0.simIntersectPointsWithPointCloud", _simIntersectPointsWithPointCloud},
        {"sim0.simGetOctreeVoxels", _simGetOctreeVoxels},
        {"sim0.simGetPointCloudPoints", _simGetPointCloudPoints},
        {"sim0.simInsertObjectIntoOctree", _simInsertObjectIntoOctree},
        {"sim0.simSubtractObjectFromOctree", _simSubtractObjectFromOctree},
        {"sim0.simInsertObjectIntoPointCloud", _simInsertObjectIntoPointCloud},
        {"sim0.simSubtractObjectFromPointCloud", _simSubtractObjectFromPointCloud},
        {"sim0.simCheckOctreePointOccupancy", _simCheckOctreePointOccupancy},
        {"sim0.simOpenTextEditor", _simOpenTextEditor},
        {"sim0.simSetVisionSensorFilter", _simSetVisionSensorFilter},
        {"sim0.simGetVisionSensorFilter", _simGetVisionSensorFilter},
        {"sim0.simGetScriptSimulationParameter", _simGetScriptSimulationParameter},
        {"sim0.simSetScriptSimulationParameter", _simSetScriptSimulationParameter},
        {"sim0.simHandleSimulationStart", _simHandleSimulationStart},
        {"sim0.simHandleSensingStart", _simHandleSensingStart},
        {"sim0.simAuxFunc", _simAuxFunc},
        {"sim0.simSetReferencedHandles", _simSetReferencedHandles},
        {"sim0.simGetReferencedHandles", _simGetReferencedHandles},
        {"sim0.simGetGraphCurve", _simGetGraphCurve},
        {"sim0.simTest", _simTest},
        {"sim0.simAddStatusbarMessage", _simAddStatusbarMessage},
        // Following deprecated since 21/05/2017:
        {"sim0.simGetObjectSelectionSize", _simGetObjectSelectionSize},
        {"sim0.simGetObjectLastSelection", _simGetObjectLastSelection},
        {"sim0.simReleaseScriptRawBuffer", _simReleaseScriptRawBuffer},
        // Following deprecated since V3.3.0:
        {"sim0.simGetPathPlanningHandle", _simGetPathPlanningHandle},
        {"sim0.simSearchPath", _simSearchPath},
        {"sim0.simInitializePathSearch", _simInitializePathSearch},
        {"sim0.simPerformPathSearchStep", _simPerformPathSearchStep},
        // Following deprecated since 09/02/2017:
        {"sim0.simLoadUI", _simLoadUI},
        {"sim0.simSaveUI", _simSaveUI},
        {"sim0.simRemoveUI", _simRemoveUI},
        {"sim0.simCreateUI", _simCreateUI},
        {"sim0.simCreateUIButton", _simCreateUIButton},
        {"sim0.simGetUIPosition", _simGetUIPosition},
        {"sim0.simSetUIPosition", _simSetUIPosition},
        {"sim0.simGetUIHandle", _simGetUIHandle},
        {"sim0.simGetUIProperty", _simGetUIProperty},
        {"sim0.simGetUIEventButton", _simGetUIEventButton},
        {"sim0.simSetUIProperty", _simSetUIProperty},
        {"sim0.simGetUIButtonProperty", _simGetUIButtonProperty},
        {"sim0.simSetUIButtonProperty", _simSetUIButtonProperty},
        {"sim0.simGetUIButtonSize", _simGetUIButtonSize},
        {"sim0.simSetUIButtonLabel", _simSetUIButtonLabel},
        {"sim0.simGetUIButtonLabel", _simGetUIButtonLabel},
        {"sim0.simSetUISlider", _simSetUISlider},
        {"sim0.simGetUISlider", _simGetUISlider},
        {"sim0.simSetUIButtonColor", _simSetUIButtonColor},
        {"sim0.simCreateUIButtonArray", _simCreateUIButtonArray},
        {"sim0.simSetUIButtonArrayColor", _simSetUIButtonArrayColor},
        {"sim0.simDeleteUIButtonArray", _simDeleteUIButtonArray},
        // Following for backward compatibility (nov-dec 2011):
        {"sim0.simGet2DElementHandle", _simGetUIHandle},
        {"sim0.simGet2DElementProperty", _simGetUIProperty},
        {"sim0.simGet2DElementEventButton", _simGetUIEventButton},
        {"sim0.simSet2DElementProperty", _simSetUIProperty},
        {"sim0.simGet2DElementButtonProperty", _simGetUIButtonProperty},
        {"sim0.simSet2DElementButtonProperty", _simSetUIButtonProperty},
        {"sim0.simGet2DElementButtonSize", _simGetUIButtonSize},
        {"sim0.simSet2DElementButtonLabel", _simSetUIButtonLabel},
        {"sim0.simGet2DElementButtonLabel", _simGetUIButtonLabel},
        {"sim0.simSet2DElementSlider", _simSetUISlider},
        {"sim0.simGet2DElementSlider", _simGetUISlider},
        {"sim0.simSet2DElementButtonColor", _simSetUIButtonColor},
        {"sim0.simCreate2DElementButtonArray", _simCreateUIButtonArray},
        {"sim0.simSet2DElementButtonArrayColor", _simSetUIButtonArrayColor},
        {"sim0.simDelete2DElementButtonArray", _simDeleteUIButtonArray},
        {"sim0.simRemove2DElement", _simRemoveUI},
        {"sim0.simCreate2DElement", _simCreateUI},
        {"sim0.simCreate2DElementButton", _simCreateUIButton},
        {"sim0.simGet2DElementPosition", _simGetUIPosition},
        {"sim0.simSet2DElementPosition", _simSetUIPosition},
        // Following deprecated since 26/12/2016:
        {"sim0.simAddSceneCustomData", _simAddSceneCustomData},
        {"sim0.simGetSceneCustomData", _simGetSceneCustomData},
        {"sim0.simAddObjectCustomData", _simAddObjectCustomData},
        {"sim0.simGetObjectCustomData", _simGetObjectCustomData},
        // Following deprecated since 29/10/2016:
        {"sim0.simGetMaterialId", _simGetMaterialId},
        {"sim0.simGetShapeMaterial", _simGetShapeMaterial},
        {"sim0.simHandleVarious", _simHandleVarious},
        // Following deprecated since 13/9/2016:
        {"sim0.simPackInts", _simPackInt32Table},
        {"sim0.simPackUInts", _simPackUInt32Table},
        {"sim0.simPackFloats", _simPackFloatTable},
        {"sim0.simPackDoubles", _simPackDoubleTable},
        {"sim0.simPackBytes", _simPackUInt8Table},
        {"sim0.simPackWords", _simPackUInt16Table},
        {"sim0.simUnpackInts", _simUnpackInt32Table},
        {"sim0.simUnpackUInts", _simUnpackUInt32Table},
        {"sim0.simUnpackFloats", _simUnpackFloatTable},
        {"sim0.simUnpackDoubles", _simUnpackDoubleTable},
        {"sim0.simUnpackBytes", _simUnpackUInt8Table},
        {"sim0.simUnpackWords", _simUnpackUInt16Table},
        // Following deprecated:
        {"sim0.simGetInvertedMatrix", _simGetInvertedMatrix},
        {"sim0.simEnableWorkThreads", _simEnableWorkThreads},
        {"sim0.simWaitForWorkThreads", _simWaitForWorkThreads},
        {"sim0.simFindIkPath", _simFindIkPath},
        {"sim0.simHandleChildScript", _simHandleChildScript},
        {"sim0.simHandleSensingChildScripts", _simHandleSensingChildScripts},
        {"sim0.simDelegateChildScriptExecution", _simDelegateChildScriptExecution},
        {"sim0.simResetTracing", _simResetTracing},
        {"sim0.simHandleTracing", _simHandleTracing},
        {"sim0.simCopyPasteSelectedObjects", _simCopyPasteSelectedObjects},
        {"sim0.simGetShapeVertex", _simGetShapeVertex},
        {"sim0.simGetShapeTriangle", _simGetShapeTriangle},
        {"sim0.simGetInstanceIndex", _simGetInstanceIndex},
        {"sim0.simGetVisibleInstanceIndex", _simGetVisibleInstanceIndex},
        {"sim0.simGetSystemTimeInMilliseconds", _simGetSystemTimeInMilliseconds},
        {"sim0.simLockInterface", _simLockInterface},
        {"sim0.simJointGetForce", _simJointGetForce},
        {"sim0.simScaleSelectedObjects", _simScaleSelectedObjects},
        {"sim0.simDeleteSelectedObjects", _simDeleteSelectedObjects},
        {"sim0.simResetPath", _simResetPath},
        {"sim0.simResetJoint", _simResetJoint},
        {"sim0.simGetMpConfigForTipPose", _simGetMpConfigForTipPose},
        // Following for backward compatibility (June 2020):
        {"sim0.simGetNameSuffix", _simGetNameSuffix},
        {"sim0.simSetNameSuffix", _simSetNameSuffix},
        // Following for backward compatibility (Dec 2015):
        {"sim0.simSetBooleanParameter", _simSetBoolParam},
        {"sim0.simGetBooleanParameter", _simGetBoolParam},
        {"sim0.simSetIntegerParameter", _simSetInt32Param},
        {"sim0.simGetIntegerParameter", _simGetInt32Param},
        {"sim0.simSetFloatingParameter", _simSetFloatParam},
        {"sim0.simGetFloatingParameter", _simGetFloatParam},
        {"sim0.simGetObjectIntParameter", _simGetObjectInt32Parameter},
        {"sim0.simSetObjectIntParameter", _simSetObjectInt32Param},
        // Following for backward compatibility:
        {"sim0.simHandleRenderingSensor", _simHandleVisionSensor},
        {"sim0.simReadRenderingSensor", _simReadVisionSensor},
        {"sim0.simResetRenderingSensor", _simResetVisionSensor},
        {"sim0.simGetRenderingSensorResolution", _simGetVisionSensorResolution},
        {"sim0.simGetRenderingSensorImage", _simGetVisionSensorImage},
        {"sim0.simSetRenderingSensorImage", _simSetVisionSensorImage},
        {"sim0.simGetRenderingSensorDepthBuffer", _simGetVisionSensorDepthBuffer},
        {"sim0.simCheckRenderingSensor", _simCheckVisionSensor},
        {"sim0.simCheckRenderingSensorEx", _simCheckVisionSensorEx},

        {"sim0.simCheckIkGroup", _simCheckIkGroup},
        {"sim0.simCreateIkGroup", _simCreateIkGroup},
        {"sim0.simRemoveIkGroup", _simRemoveIkGroup},
        {"sim0.simCreateIkElement", _simCreateIkElement},
        {"sim0.simExportIk", _simExportIk},
        {"sim0.simComputeJacobian", _simComputeJacobian},
        {"sim0.simGetConfigForTipPose", _simGetConfigForTipPose},
        {"sim0.simGenerateIkPath", _simGenerateIkPath},
        {"sim0.simGetIkGroupHandle", _simGetIkGroupHandle},
        {"sim0.simGetIkGroupMatrix", _simGetIkGroupMatrix},
        {"sim0.simHandleIkGroup", _simHandleIkGroup},
        {"sim0.simSetIkGroupProperties", _simSetIkGroupProperties},
        {"sim0.simSetIkElementProperties", _simSetIkElementProperties},
        {"sim0.simTubeRead", _simTubeRead},
        {"sim0.simTubeOpen", _simTubeOpen},
        {"sim0.simTubeClose", _simTubeClose},
        {"sim0.simTubeWrite", _simTubeWrite},
        {"sim0.simTubeStatus", _simTubeStatus},
        {"sim0.simSendData", _simSendData},
        {"sim0.simReceiveData", _simReceiveData},
        {"sim0.simGetPathPosition", _simGetPathPosition},
        {"sim0.simSetPathPosition", _simSetPathPosition},
        {"sim0.simGetPathLength", _simGetPathLength},
        {"sim0.simGetDataOnPath", _simGetDataOnPath},
        {"sim0.simGetPositionOnPath", _simGetPositionOnPath},
        {"sim0.simGetOrientationOnPath", _simGetOrientationOnPath},
        {"sim0.simGetClosestPositionOnPath", _simGetClosestPositionOnPath},
        {"sim0.simCreatePath", _sim_CreatePath},
        {"sim0.simInsertPathCtrlPoints", _simInsertPathCtrlPoints},
        {"sim0.simCutPathCtrlPoints", _simCutPathCtrlPoints},
        {"sim0.simGetScriptExecutionCount", _simGetScriptExecutionCount},
        {"sim0.simIsScriptExecutionThreaded", _simIsScriptExecutionThreaded},
        {"sim0.simIsScriptRunningInThread", _simIsScriptRunningInThread},
        {"sim0.simSetThreadResumeLocation", _simSetThreadResumeLocation},
        {"sim0.simResumeThreads", _simResumeThreads},
        {"sim0.simLaunchThreadedChildScripts", _simLaunchThreadedChildScripts},
        {"sim0.simGetCollectionHandle", _simGetCollectionHandle},
        {"sim0.simRemoveCollection", _simRemoveCollection},
        {"sim0.simEmptyCollection", _simEmptyCollection},
        {"sim0.simGetCollectionName", _simGetCollectionName},
        {"sim0.simSetCollectionName", _simSetCollectionName},
        {"sim0.simCreateCollection", _sim_CreateCollection},
        {"sim0.simAddObjectToCollection", _simAddObjectToCollection},
        {"sim0.simHandleDistance", _simHandleDistance},
        {"sim0.simReadDistance", _simReadDistance},
        {"sim0.simHandleCollision", _simHandleCollision},
        {"sim0.simReadCollision", _simReadCollision},
        {"sim0.simResetCollision", _simResetCollision},
        {"sim0.simResetDistance", _simResetDistance},
        {"sim0.simGetCollisionHandle", _simGetCollisionHandle},
        {"sim0.simGetDistanceHandle", _simGetDistanceHandle},
        {"sim0.simAddBanner", _simAddBanner},
        {"sim0.simRemoveBanner", _simRemoveBanner},
        {"sim0.simAddGhost", _simAddGhost},
        {"sim0.simModifyGhost", _simModifyGhost},
        {"sim0.simAddPointCloud", _simAddPointCloud},
        {"sim0.simModifyPointCloud", _simModifyPointCloud},
        {"sim0.simSetGraphUserData", _simSetGraphUserData},
        {"sim0.simCopyMatrix", _simCopyMatrix},
        {"", nullptr}};

const SLuaVariables simLuaVariablesOldApi[] = { // Following for backward compatibility (see newer equivalent commands
                                                // ('simLuaVariables'))
    {"sim0.sim_sceneobject_shape", sim_sceneobject_shape},
    {"sim0.sim_sceneobject_joint", sim_sceneobject_joint},
    {"sim0.sim_sceneobject_graph", sim_sceneobject_graph},
    {"sim0.sim_sceneobject_camera", sim_sceneobject_camera},
    {"sim0.sim_sceneobject_dummy", sim_sceneobject_dummy},
    {"sim0.sim_sceneobject_proximitysensor", sim_sceneobject_proximitysensor},
    {"sim0.sim_sceneobject_path", sim_sceneobject_path},
    {"sim0.sim_object_renderingsensor_type", sim_sceneobject_visionsensor},
    {"sim0.sim_sceneobject_visionsensor", sim_sceneobject_visionsensor},
    {"sim0.sim_sceneobject_mill", sim_sceneobject_mill},
    {"sim0.sim_sceneobject_forcesensor", sim_sceneobject_forcesensor},
    {"sim0.sim_sceneobject_light", sim_sceneobject_light},
    {"sim0.sim_sceneobject_mirror", sim_sceneobject_mirror},
    {"sim0.sim_sceneobject_octree", sim_sceneobject_octree},
    {"sim0.sim_sceneobject_pointcloud", sim_sceneobject_pointcloud},
    {"sim0.sim_light_omnidirectional", sim_light_omnidirectional},
    {"sim0.sim_light_spot", sim_light_spot},
    {"sim0.sim_light_directional", sim_light_directional},
    {"sim0.sim_joint_revolute", sim_joint_revolute},
    {"sim0.sim_joint_prismatic", sim_joint_prismatic},
    {"sim0.sim_joint_spherical", sim_joint_spherical},
    {"sim0.sim_shape_simple", sim_shape_simple},
    {"sim0.sim_shape_compound", sim_shape_compound},
    {"sim0.sim_proximitysensor_pyramid", sim_proximitysensor_pyramid},
    {"sim0.sim_proximitysensor_cylinder", sim_proximitysensor_cylinder},
    {"sim0.sim_proximitysensor_disc", sim_proximitysensor_disc},
    {"sim0.sim_proximitysensor_cone", sim_proximitysensor_cone},
    {"sim0.sim_proximitysensor_ray", sim_proximitysensor_ray},
    {"sim0.sim_mill_pyramid_subtype", sim_mill_pyramid_subtype},
    {"sim0.sim_mill_cylinder_subtype", sim_mill_cylinder_subtype},
    {"sim0.sim_mill_disc_subtype", sim_mill_disc_subtype},
    {"sim0.sim_mill_cone_subtype", sim_mill_cone_subtype},
    {"sim0.sim_object_no_subtype", sim_object_no_subtype},
    {"sim0.sim_objecttype_sceneobject", sim_objecttype_sceneobject},
    {"sim0.sim_appobj_collision_type", sim_appobj_collision_type},
    {"sim0.sim_appobj_distance_type", sim_appobj_distance_type},
    {"sim0.sim_appobj_simulation_type", sim_appobj_simulation_type},
    {"sim0.sim_appobj_ik_type", sim_appobj_ik_type},
    {"sim0.sim_objecttype_collection", sim_objecttype_collection},
    {"sim0.sim_appobj_2delement_type", sim_appobj_ui_type}, // for backward compatibility
    {"sim0.sim_appobj_ui_type", sim_appobj_ui_type},
    {"sim0.sim_appobj_script_type", sim_appobj_script_type},
    {"sim0.sim_appobj_pathplanning_type", sim_appobj_pathplanning_type},
    {"sim0.sim_objecttype_texture", sim_objecttype_texture},
    {"sim0.sim_ik_pseudo_inverse_method", sim_ik_pseudo_inverse_method},
    {"sim0.sim_ik_damped_least_squares_method", sim_ik_damped_least_squares_method},
    {"sim0.sim_ik_jacobian_transpose_method", sim_ik_jacobian_transpose_method},
    {"sim0.sim_ik_x_constraint", sim_ik_x_constraint},
    {"sim0.sim_ik_y_constraint", sim_ik_y_constraint},
    {"sim0.sim_ik_z_constraint", sim_ik_z_constraint},
    {"sim0.sim_ik_alpha_beta_constraint", sim_ik_alpha_beta_constraint},
    {"sim0.sim_ik_gamma_constraint", sim_ik_gamma_constraint},
    {"sim0.sim_ikresult_not_performed", sim_ikresult_not_performed},
    {"sim0.sim_ikresult_success", sim_ikresult_success},
    {"sim0.sim_ikresult_fail", sim_ikresult_fail},
    {"sim0.sim_message_ui_button_state_change", sim_message_ui_button_state_change},
    {"sim0.sim_message_model_loaded", sim_message_model_loaded},
    {"sim0.sim_message_scene_loaded", sim_message_scene_loaded},
    {"sim0.sim_message_object_selection_changed", sim_message_object_selection_changed},
    {"sim0.sim_message_keypress", sim_message_keypress},
    {"sim0.sim_message_bannerclicked", sim_message_bannerclicked},
    {"sim0.sim_message_prox_sensor_select_down", sim_message_prox_sensor_select_down},
    {"sim0.sim_message_prox_sensor_select_up", sim_message_prox_sensor_select_up},
    {"sim0.sim_message_pick_select_down", sim_message_pick_select_down},
    {"sim0.sim_buttonproperty_button", sim_buttonproperty_button},
    {"sim0.sim_buttonproperty_label", sim_buttonproperty_label},
    {"sim0.sim_buttonproperty_editbox", sim_buttonproperty_editbox},
    {"sim0.sim_buttonproperty_slider", sim_buttonproperty_slider},
    {"sim0.sim_buttonproperty_staydown", sim_buttonproperty_staydown},
    {"sim0.sim_buttonproperty_enabled", sim_buttonproperty_enabled},
    {"sim0.sim_buttonproperty_borderless", sim_buttonproperty_borderless},
    {"sim0.sim_buttonproperty_horizontallycentered", sim_buttonproperty_horizontallycentered},
    {"sim0.sim_buttonproperty_ignoremouse", sim_buttonproperty_ignoremouse},
    {"sim0.sim_buttonproperty_isdown", sim_buttonproperty_isdown},
    {"sim0.sim_buttonproperty_transparent", sim_buttonproperty_transparent},
    {"sim0.sim_buttonproperty_nobackgroundcolor", sim_buttonproperty_nobackgroundcolor},
    {"sim0.sim_buttonproperty_rollupaction", sim_buttonproperty_rollupaction},
    {"sim0.sim_buttonproperty_closeaction", sim_buttonproperty_closeaction},
    {"sim0.sim_buttonproperty_verticallycentered", sim_buttonproperty_verticallycentered},
    {"sim0.sim_buttonproperty_downupevent", sim_buttonproperty_downupevent},
    {"sim0.sim_objectproperty_collapsed", sim_objectproperty_collapsed},
    {"sim0.sim_objectproperty_selectable", sim_objectproperty_selectable},
    {"sim0.sim_objectproperty_selectmodelbaseinstead", sim_objectproperty_selectmodelbaseinstead},
    {"sim0.sim_objectproperty_dontshowasinsidemodel", sim_objectproperty_dontshowasinsidemodel},
    {"sim0.sim_objectproperty_canupdatedna", sim_objectproperty_canupdatedna},
    {"sim0.sim_objectproperty_selectinvisible", sim_objectproperty_selectinvisible},
    {"sim0.sim_objectproperty_depthinvisible", sim_objectproperty_depthinvisible},
    {"sim0.sim_objectproperty_cannotdelete", sim_objectproperty_cannotdelete},
    {"sim0.sim_simulation_stopped", sim_simulation_stopped},
    {"sim0.sim_simulation_paused", sim_simulation_paused},
    {"sim0.sim_simulation_advancing", sim_simulation_advancing},
    {"sim0.sim_simulation_advancing_firstafterstop", sim_simulation_advancing_firstafterstop},
    {"sim0.sim_simulation_advancing_running", sim_simulation_advancing_running},
    {"sim0.sim_simulation_advancing_lastbeforepause", sim_simulation_advancing_lastbeforepause},
    {"sim0.sim_simulation_advancing_firstafterpause", sim_simulation_advancing_firstafterpause},
    {"sim0.sim_simulation_advancing_abouttostop", sim_simulation_advancing_abouttostop},
    {"sim0.sim_simulation_advancing_lastbeforestop", sim_simulation_advancing_lastbeforestop},
    {"sim0.sim_texturemap_plane", sim_texturemap_plane},
    {"sim0.sim_texturemap_cylinder", sim_texturemap_cylinder},
    {"sim0.sim_texturemap_sphere", sim_texturemap_sphere},
    {"sim0.sim_texturemap_cube", sim_texturemap_cube},
    {"sim0.sim_scripttype_main", sim_scripttype_main},
    {"sim0.sim_scripttype_simulation", sim_scripttype_simulation},
    {"sim0.sim_scripttype_addon", sim_scripttype_addon},
    {"sim0.sim_scripttype_addonfunction", sim_scripttype_addonfunction},
    {"sim0.sim_scripttype_customization", sim_scripttype_customization},
    {"sim0.sim_scripttype_threaded", sim_scripttype_threaded_old},
    {"sim0.sim_mainscriptcall_initialization", sim_syscb_init},
    {"sim0.sim_mainscriptcall_cleanup", sim_syscb_cleanup},
    {"sim0.sim_mainscriptcall_regular", sim_syscb_actuation},
    {"sim0.sim_childscriptcall_initialization", sim_syscb_init},
    {"sim0.sim_childscriptcall_cleanup", sim_syscb_cleanup},
    {"sim0.sim_childscriptcall_actuation", sim_syscb_actuation},
    {"sim0.sim_childscriptcall_sensing", sim_syscb_sensing},
    {"sim0.sim_childscriptcall_threaded", -1},
    {"sim0.sim_customizationscriptcall_initialization", sim_syscb_init},
    {"sim0.sim_customizationscriptcall_cleanup", sim_syscb_cleanup},
    {"sim0.sim_customizationscriptcall_nonsimulation", sim_syscb_nonsimulation},
    {"sim0.sim_customizationscriptcall_lastbeforesimulation", sim_syscb_beforesimulation},
    {"sim0.sim_customizationscriptcall_firstaftersimulation", sim_syscb_aftersimulation},
    {"sim0.sim_customizationscriptcall_simulationactuation", sim_syscb_actuation},
    {"sim0.sim_customizationscriptcall_simulationsensing", sim_syscb_sensing},
    {"sim0.sim_customizationscriptcall_simulationpause", sim_syscb_suspended},
    {"sim0.sim_customizationscriptcall_simulationpausefirst", sim_syscb_suspend},
    {"sim0.sim_customizationscriptcall_simulationpauselast", sim_syscb_resume},
    {"sim0.sim_customizationscriptcall_lastbeforeinstanceswitch", sim_syscb_beforeinstanceswitch},
    {"sim0.sim_customizationscriptcall_firstafterinstanceswitch", sim_syscb_afterinstanceswitch},
    {"sim0.sim_addonscriptcall_initialization", sim_syscb_init},
    {"sim0.sim_addonscriptcall_suspend", sim_syscb_aos_suspend},
    {"sim0.sim_addonscriptcall_restarting", sim_syscb_aos_resume},
    {"sim0.sim_addonscriptcall_cleanup", sim_syscb_cleanup},
    {"sim0.sim_customizationscriptattribute_activeduringsimulation",
     sim_customizationscriptattribute_activeduringsimulation},
    {"sim0.sim_scriptattribute_executionorder", sim_scriptattribute_executionorder},
    {"sim0.sim_scriptattribute_executioncount", sim_scriptattribute_executioncount},
    {"sim0.sim_childscriptattribute_automaticcascadingcalls", sim_childscriptattribute_automaticcascadingcalls},
    {"sim0.sim_childscriptattribute_enabled", sim_childscriptattribute_enabled},
    {"sim0.sim_scriptattribute_enabled", sim_scriptattribute_enabled},
    {"sim0.sim_customizationscriptattribute_cleanupbeforesave", sim_customizationscriptattribute_cleanupbeforesave},
    {"sim0.sim_scriptexecorder_first", sim_scriptexecorder_first},
    {"sim0.sim_scriptexecorder_normal", sim_scriptexecorder_normal},
    {"sim0.sim_scriptexecorder_last", sim_scriptexecorder_last},
    {"sim0.sim_scriptthreadresume_allnotyetresumed", sim_scriptthreadresume_allnotyetresumed},
    {"sim0.sim_scriptthreadresume_default", sim_scriptthreadresume_default},
    {"sim0.sim_scriptthreadresume_actuation_first", sim_scriptthreadresume_actuation_first},
    {"sim0.sim_scriptthreadresume_actuation_last", sim_scriptthreadresume_actuation_last},
    {"sim0.sim_scriptthreadresume_sensing_first", sim_scriptthreadresume_sensing_first},
    {"sim0.sim_scriptthreadresume_sensing_last", sim_scriptthreadresume_sensing_last},
    {"sim0.sim_scriptthreadresume_custom", sim_scriptthreadresume_custom},
    {"sim0.sim_callbackid_rossubscriber", sim_callbackid_rossubscriber},
    {"sim0.sim_callbackid_dynstep", sim_callbackid_dynstep},
    {"sim0.sim_callbackid_userdefined", sim_callbackid_userdefined},
    {"sim0.sim_script_no_error", sim_script_no_error},
    {"sim0.sim_script_main_script_nonexistent", sim_script_main_script_nonexistent},
    {"sim0.sim_script_main_not_called", sim_script_main_script_not_called},
    {"sim0.sim_script_reentrance_error", sim_script_reentrance_error},
    {"sim0.sim_script_lua_error", sim_script_lua_error},
    {"sim0.sim_script_call_error", sim_script_call_error},
    {"sim0.sim_api_error_report", sim_api_error_report},
    {"sim0.sim_api_error_output", sim_api_error_output},
    {"sim0.sim_api_warning_output", sim_api_warning_output},
    {"sim0.sim_handle_all", sim_handle_all},
    {"sim0.sim_handle_all_except_explicit", sim_handle_all_except_explicit},
    {"sim0.sim_handle_self", sim_handle_self},
    {"sim0.sim_handle_main_script", sim_handle_main_script},
    {"sim0.sim_handle_tree", sim_handle_tree},
    {"sim0.sim_handle_chain", sim_handle_chain},
    {"sim0.sim_handle_single", sim_handle_single},
    {"sim0.sim_handle_default", sim_handle_default},
    {"sim0.sim_handle_all_except_self", sim_handle_all_except_self},
    {"sim0.sim_handle_parent", sim_handle_parent},
    {"sim0.sim_handle_scene", sim_handle_scene},
    {"sim0.sim_handle_app", sim_handle_app},
    {"sim0.sim_handleflag_assembly", sim_handleflag_assembly},
    {"sim0.sim_handleflag_camera", sim_handleflag_camera},
    {"sim0.sim_handleflag_togglevisibility", sim_handleflag_togglevisibility},
    {"sim0.sim_handleflag_extended", sim_handleflag_extended},
    {"sim0.sim_handleflag_greyscale", sim_handleflag_greyscale},
    {"sim0.sim_handleflag_codedstring", sim_handleflag_codedstring},
    {"sim0.sim_handleflag_model", sim_handleflag_model},
    {"sim0.sim_handleflag_rawvalue", sim_handleflag_rawvalue},
    {"sim0.sim_objectspecialproperty_collidable", sim_objectspecialproperty_collidable},
    {"sim0.sim_objectspecialproperty_measurable", sim_objectspecialproperty_measurable},
    {"sim0.sim_objectspecialproperty_detectable_ultrasonic", sim_objectspecialproperty_detectable_ultrasonic},
    {"sim0.sim_objectspecialproperty_detectable_infrared", sim_objectspecialproperty_detectable_infrared},
    {"sim0.sim_objectspecialproperty_detectable_laser", sim_objectspecialproperty_detectable_laser},
    {"sim0.sim_objectspecialproperty_detectable_inductive", sim_objectspecialproperty_detectable_inductive},
    {"sim0.sim_objectspecialproperty_detectable_capacitive", sim_objectspecialproperty_detectable_capacitive},
    {"sim0.sim_objectspecialproperty_renderable", sim_objectspecialproperty_renderable},
    {"sim0.sim_objectspecialproperty_detectable_all", sim_objectspecialproperty_detectable},
    {"sim0.sim_objectspecialproperty_pathplanning_ignored", sim_objectspecialproperty_pathplanning_ignored},
    {"sim0.sim_modelproperty_not_collidable", sim_modelproperty_not_collidable},
    {"sim0.sim_modelproperty_not_measurable", sim_modelproperty_not_measurable},
    {"sim0.sim_modelproperty_not_renderable", sim_modelproperty_not_renderable},
    {"sim0.sim_modelproperty_not_detectable", sim_modelproperty_not_detectable},
    {"sim0.sim_modelproperty_not_dynamic", sim_modelproperty_not_dynamic},
    {"sim0.sim_modelproperty_not_respondable", sim_modelproperty_not_respondable},
    {"sim0.sim_modelproperty_not_reset", sim_modelproperty_not_reset},
    {"sim0.sim_modelproperty_not_visible", sim_modelproperty_not_visible},
    {"sim0.sim_modelproperty_scripts_inactive", sim_modelproperty_scripts_inactive},
    {"sim0.sim_modelproperty_not_showasinsidemodel", sim_modelproperty_not_showasinsidemodel},
    {"sim0.sim_modelproperty_not_model", sim_modelproperty_not_model},
    {"sim0.sim_dlgstyle_message", sim_dlgstyle_message},
    {"sim0.sim_dlgstyle_input", sim_dlgstyle_input},
    {"sim0.sim_dlgstyle_ok", sim_dlgstyle_ok},
    {"sim0.sim_dlgstyle_ok_cancel", sim_dlgstyle_ok_cancel},
    {"sim0.sim_dlgstyle_yes_no", sim_dlgstyle_yes_no},
    {"sim0.sim_dlgstyle_dont_center", sim_dlgstyle_dont_center},
    {"sim0.sim_dlgret_still_open", sim_dlgret_still_open},
    {"sim0.sim_dlgret_ok", sim_dlgret_ok},
    {"sim0.sim_dlgret_cancel", sim_dlgret_cancel},
    {"sim0.sim_dlgret_yes", sim_dlgret_yes},
    {"sim0.sim_dlgret_no", sim_dlgret_no},
    {"sim0.sim_pathproperty_show_line", sim_pathproperty_show_line},
    {"sim0.sim_pathproperty_show_orientation", sim_pathproperty_show_orientation},
    {"sim0.sim_pathproperty_closed_path", sim_pathproperty_closed_path},
    {"sim0.sim_pathproperty_automatic_orientation", sim_pathproperty_automatic_orientation},
    {"sim0.sim_pathproperty_flat_path", sim_pathproperty_flat_path},
    {"sim0.sim_pathproperty_show_position", sim_pathproperty_show_position},
    {"sim0.sim_pathproperty_keep_x_up", sim_pathproperty_keep_x_up},
    {"sim0.sim_distcalcmethod_dl", sim_distcalcmethod_dl},
    {"sim0.sim_distcalcmethod_dac", sim_distcalcmethod_dac},
    {"sim0.sim_distcalcmethod_max_dl_dac", sim_distcalcmethod_max_dl_dac},
    {"sim0.sim_distcalcmethod_dl_and_dac", sim_distcalcmethod_dl_and_dac},
    {"sim0.sim_distcalcmethod_sqrt_dl2_and_dac2", sim_distcalcmethod_sqrt_dl2_and_dac2},
    {"sim0.sim_distcalcmethod_dl_if_nonzero", sim_distcalcmethod_dl_if_nonzero},
    {"sim0.sim_distcalcmethod_dac_if_nonzero", sim_distcalcmethod_dac_if_nonzero},
    {"sim0.sim_boolparam_hierarchy_visible", sim_boolparam_hierarchy_visible},
    {"sim0.sim_boolparam_console_visible", sim_boolparam_console_visible},
    {"sim0.sim_boolparam_collision_handling_enabled", sim_boolparam_collision_handling_enabled},
    {"sim0.sim_boolparam_distance_handling_enabled", sim_boolparam_distance_handling_enabled},
    {"sim0.sim_boolparam_ik_handling_enabled", sim_boolparam_ik_handling_enabled},
    {"sim0.sim_boolparam_gcs_handling_enabled", sim_boolparam_gcs_handling_enabled},
    {"sim0.sim_boolparam_dynamics_handling_enabled", sim_boolparam_dynamics_handling_enabled},
    {"sim0.sim_boolparam_proximity_sensor_handling_enabled", sim_boolparam_proximity_sensor_handling_enabled},
    {"sim0.sim_boolparam_vision_sensor_handling_enabled", sim_boolparam_vision_sensor_handling_enabled},
    {"sim0.sim_boolparam_rendering_sensor_handling_enabled", sim_boolparam_vision_sensor_handling_enabled},
    {"sim0.sim_boolparam_mill_handling_enabled", sim_boolparam_mill_handling_enabled},
    {"sim0.sim_boolparam_browser_visible", sim_boolparam_browser_visible},
    {"sim0.sim_boolparam_scene_and_model_load_messages", sim_boolparam_scene_and_model_load_messages},
    {"sim0.sim_boolparam_shape_textures_are_visible", sim_boolparam_shape_textures_are_visible},
    {"sim0.sim_boolparam_display_enabled", sim_boolparam_display_enabled},
    {"sim0.sim_boolparam_infotext_visible", sim_boolparam_infotext_visible},
    {"sim0.sim_boolparam_statustext_open", sim_boolparam_statustext_open},
    {"sim0.sim_boolparam_fog_enabled", sim_boolparam_fog_enabled},
    {"sim0.sim_boolparam_rml2_available", sim_boolparam_rml2_available},
    {"sim0.sim_boolparam_rml4_available", sim_boolparam_rml4_available},
    {"sim0.sim_boolparam_mirrors_enabled", sim_boolparam_mirrors_enabled},
    {"sim0.sim_boolparam_aux_clip_planes_enabled", sim_boolparam_aux_clip_planes_enabled},
    {"sim0.sim_boolparam_full_model_copy_from_api", sim_boolparam_reserved3},
    {"sim0.sim_boolparam_realtime_simulation", sim_boolparam_realtime_simulation},
    {"sim0.sim_boolparam_use_glfinish_cmd", sim_boolparam_use_glfinish_cmd},
    {"sim0.sim_boolparam_force_show_wireless_emission", sim_boolparam_force_show_wireless_emission},
    {"sim0.sim_boolparam_force_show_wireless_reception", sim_boolparam_force_show_wireless_reception},
    {"sim0.sim_boolparam_video_recording_triggered", sim_boolparam_video_recording_triggered},
    {"sim0.sim_boolparam_fullscreen", sim_boolparam_fullscreen},
    {"sim0.sim_boolparam_headless", sim_boolparam_headless},
    {"sim0.sim_boolparam_hierarchy_toolbarbutton_enabled", sim_boolparam_hierarchy_toolbarbutton_enabled},
    {"sim0.sim_boolparam_browser_toolbarbutton_enabled", sim_boolparam_browser_toolbarbutton_enabled},
    {"sim0.sim_boolparam_objectshift_toolbarbutton_enabled", sim_boolparam_objectshift_toolbarbutton_enabled},
    {"sim0.sim_boolparam_objectrotate_toolbarbutton_enabled", sim_boolparam_objectrotate_toolbarbutton_enabled},
    {"sim0.sim_boolparam_force_calcstruct_all_visible", sim_boolparam_force_calcstruct_all_visible},
    {"sim0.sim_boolparam_force_calcstruct_all", sim_boolparam_force_calcstruct_all},
    {"sim0.sim_boolparam_exit_request", sim_boolparam_exit_request},
    {"sim0.sim_boolparam_play_toolbarbutton_enabled", sim_boolparam_play_toolbarbutton_enabled},
    {"sim0.sim_boolparam_pause_toolbarbutton_enabled", sim_boolparam_pause_toolbarbutton_enabled},
    {"sim0.sim_boolparam_stop_toolbarbutton_enabled", sim_boolparam_stop_toolbarbutton_enabled},
    {"sim0.sim_boolparam_waiting_for_trigger", sim_boolparam_waiting_for_trigger},
    {"sim0.sim_boolparam_objproperties_toolbarbutton_enabled", sim_boolparam_objproperties_toolbarbutton_enabled},
    {"sim0.sim_boolparam_calcmodules_toolbarbutton_enabled", sim_boolparam_calcmodules_toolbarbutton_enabled},
    {"sim0.sim_boolparam_rosinterface_donotrunmainscript", sim_boolparam_rosinterface_donotrunmainscript},
    {"sim0.sim_intparam_error_report_mode", sim_intparam_error_report_mode},
    {"sim0.sim_intparam_program_version", sim_intparam_program_version},
    {"sim0.sim_intparam_compilation_version", sim_intparam_compilation_version},
    {"sim0.sim_intparam_current_page", sim_intparam_current_page},
    {"sim0.sim_intparam_flymode_camera_handle", sim_intparam_flymode_camera_handle},
    {"sim0.sim_intparam_dynamic_step_divider", sim_intparam_dynamic_step_divider},
    {"sim0.sim_intparam_dynamic_engine", sim_intparam_dynamic_engine},
    {"sim0.sim_intparam_server_port_start", sim_intparam_server_port_start},
    {"sim0.sim_intparam_server_port_range", sim_intparam_server_port_range},
    {"sim0.sim_intparam_server_port_next", sim_intparam_server_port_next},
    {"sim0.sim_intparam_visible_layers", sim_intparam_visible_layers},
    {"sim0.sim_intparam_infotext_style", sim_intparam_infotext_style},
    {"sim0.sim_intparam_settings", sim_intparam_settings},
    {"sim0.sim_intparam_qt_version", sim_intparam_qt_version},
    {"sim0.sim_intparam_platform", sim_intparam_platform},
    {"sim0.sim_intparam_scene_unique_id", sim_intparam_scene_unique_id},
    {"sim0.sim_intparam_edit_mode_type", sim_intparam_edit_mode_type},
    {"sim0.sim_intparam_work_thread_count", sim_intparam_work_thread_count}, // deprecated
    {"sim0.sim_intparam_mouse_x", sim_intparam_mouse_x},
    {"sim0.sim_intparam_mouse_y", sim_intparam_mouse_y},
    {"sim0.sim_intparam_core_count", sim_intparam_core_count},
    {"sim0.sim_intparam_work_thread_calc_time_ms", sim_intparam_work_thread_calc_time_ms}, // deprecated
    {"sim0.sim_intparam_idle_fps", sim_intparam_idle_fps},
    {"sim0.sim_intparam_prox_sensor_select_down", sim_intparam_prox_sensor_select_down},
    {"sim0.sim_intparam_prox_sensor_select_up", sim_intparam_prox_sensor_select_up},
    {"sim0.sim_intparam_stop_request_counter", sim_intparam_stop_request_counter},
    {"sim0.sim_intparam_program_revision", sim_intparam_program_revision},
    {"sim0.sim_intparam_mouse_buttons", sim_intparam_mouse_buttons},
    {"sim0.sim_intparam_dynamic_warning_disabled_mask", sim_intparam_dynamic_warning_disabled_mask},
    {"sim0.sim_intparam_simulation_warning_disabled_mask", sim_intparam_simulation_warning_disabled_mask},
    {"sim0.sim_intparam_scene_index", sim_intparam_scene_index},
    {"sim0.sim_intparam_motionplanning_seed", sim_intparam_motionplanning_seed},
    {"sim0.sim_intparam_speedmodifier", sim_intparam_speedmodifier},
    {"sim0.sim_intparam_dynamic_iteration_count", sim_intparam_dynamic_iteration_count},
    {"sim0.sim_floatparam_rand", sim_floatparam_rand},
    {"sim0.sim_floatparam_simulation_time_step", sim_floatparam_simulation_time_step},
    {"sim0.sim_floatparam_stereo_distance", sim_floatparam_stereo_distance},
    {"sim0.sim_floatparam_dynamic_step_size", sim_floatparam_dynamic_step_size},
    {"sim0.sim_floatparam_mouse_wheel_zoom_factor", sim_floatparam_mouse_wheel_zoom_factor},
    {"sim0.sim_arrayparam_gravity", sim_arrayparam_gravity},
    {"sim0.sim_arrayparam_fog", sim_arrayparam_fog},
    {"sim0.sim_arrayparam_fog_color", sim_arrayparam_fog_color},
    {"sim0.sim_arrayparam_background_color1", sim_arrayparam_background_color1},
    {"sim0.sim_arrayparam_background_color2", sim_arrayparam_background_color2},
    {"sim0.sim_arrayparam_ambient_light", sim_arrayparam_ambient_light},
    {"sim0.sim_arrayparam_random_euler", sim_arrayparam_random_euler},
    {"sim0.sim_stringparam_application_path", sim_stringparam_application_path},
    {"sim0.sim_stringparam_video_filename", sim_stringparam_video_filename},
    {"sim0.sim_stringparam_app_arg1", sim_stringparam_app_arg1},
    {"sim0.sim_stringparam_app_arg2", sim_stringparam_app_arg2},
    {"sim0.sim_stringparam_app_arg3", sim_stringparam_app_arg3},
    {"sim0.sim_stringparam_app_arg4", sim_stringparam_app_arg4},
    {"sim0.sim_stringparam_app_arg5", sim_stringparam_app_arg5},
    {"sim0.sim_stringparam_app_arg6", sim_stringparam_app_arg6},
    {"sim0.sim_stringparam_app_arg7", sim_stringparam_app_arg7},
    {"sim0.sim_stringparam_app_arg8", sim_stringparam_app_arg8},
    {"sim0.sim_stringparam_app_arg9", sim_stringparam_app_arg9},
    {"sim0.sim_stringparam_scene_path_and_name", sim_stringparam_scene_path_and_name},
    {"sim0.sim_stringparam_remoteapi_temp_file_dir", sim_stringparam_remoteapi_temp_file_dir},
    {"sim0.sim_stringparam_scene_path", sim_stringparam_scene_path},
    {"sim0.sim_stringparam_scene_name", sim_stringparam_scene_name},
    {"sim0.sim_displayattribute_renderpass", sim_displayattribute_renderpass},
    {"sim0.sim_displayattribute_depthpass", sim_displayattribute_depthpass},
    {"sim0.sim_displayattribute_pickpass", sim_displayattribute_pickpass},
    {"sim0.sim_displayattribute_selected", sim_displayattribute_selected},
    {"sim0.sim_displayattribute_mainselection", sim_displayattribute_mainselection},
    {"sim0.sim_displayattribute_forcewireframe", sim_displayattribute_forcewireframe},
    {"sim0.sim_displayattribute_forbidwireframe", sim_displayattribute_forbidwireframe},
    {"sim0.sim_displayattribute_forbidedges", sim_displayattribute_forbidedges},
    {"sim0.sim_displayattribute_originalcolors", sim_displayattribute_originalcolors},
    {"sim0.sim_displayattribute_ignorelayer", sim_displayattribute_ignorelayer},
    {"sim0.sim_displayattribute_forvisionsensor", sim_displayattribute_forvisionsensor},
    {"sim0.sim_displayattribute_colorcodedpickpass", sim_displayattribute_colorcodedpickpass},
    {"sim0.sim_displayattribute_colorcoded", sim_displayattribute_colorcoded},
    {"sim0.sim_displayattribute_trianglewireframe", sim_displayattribute_trianglewireframe},
    {"sim0.sim_displayattribute_thickEdges", sim_displayattribute_thickEdges},
    {"sim0.sim_displayattribute_dynamiccontentonly", sim_displayattribute_dynamiccontentonly},
    {"sim0.sim_displayattribute_mirror", sim_displayattribute_mirror},
    {"sim0.sim_displayattribute_useauxcomponent", sim_displayattribute_useauxcomponent},
    {"sim0.sim_displayattribute_ignorerenderableflag", sim_displayattribute_ignorerenderableflag},
    {"sim0.sim_displayattribute_noopenglcallbacks", sim_displayattribute_noopenglcallbacks},
    {"sim0.sim_displayattribute_noghosts", sim_displayattribute_noghosts},
    {"sim0.sim_displayattribute_nopointclouds", sim_displayattribute_nopointclouds},
    {"sim0.sim_displayattribute_nodrawingobjects", sim_displayattribute_nodrawingobjects},
    {"sim0.sim_displayattribute_noparticles", sim_displayattribute_noparticles},
    {"sim0.sim_displayattribute_colorcodedtriangles", sim_displayattribute_colorcodedtriangles},
    {"sim0.sim_navigation_passive", sim_navigation_passive},
    {"sim0.sim_navigation_camerashift", sim_navigation_camerashift},
    {"sim0.sim_navigation_camerarotate", sim_navigation_camerarotate},
    {"sim0.sim_navigation_camerazoom", sim_navigation_camerazoom},
    {"sim0.sim_navigation_cameratilt", sim_navigation_cameratilt},
    {"sim0.sim_navigation_cameraangle", sim_navigation_cameraangle},
    {"sim0.sim_navigation_objectshift", sim_navigation_objectshift},
    {"sim0.sim_navigation_objectrotate", sim_navigation_objectrotate},
    {"sim0.sim_navigation_createpathpoint", sim_navigation_createpathpoint},
    {"sim0.sim_navigation_clickselection", sim_navigation_clickselection},
    {"sim0.sim_navigation_ctrlselection", sim_navigation_ctrlselection},
    {"sim0.sim_navigation_shiftselection", sim_navigation_shiftselection},
    {"sim0.sim_navigation_camerazoomwheel", sim_navigation_camerazoomwheel},
    {"sim0.sim_navigation_camerarotaterightbutton", sim_navigation_camerarotaterightbutton},
    {"sim0.sim_navigation_camerarotatemiddlebutton", sim_navigation_camerarotatemiddlebutton},
    {"sim0.sim_drawing_points", sim_drawing_points},
    {"sim0.sim_drawing_lines", sim_drawing_lines},
    {"sim0.sim_drawing_triangles", sim_drawing_triangles},
    {"sim0.sim_drawing_trianglepoints", sim_drawing_trianglepoints},
    {"sim0.sim_drawing_quadpoints", sim_drawing_quadpoints},
    {"sim0.sim_drawing_discpoints", sim_drawing_discpoints},
    {"sim0.sim_drawing_cubepoints", sim_drawing_cubepoints},
    {"sim0.sim_drawing_spherepoints", sim_drawing_spherepoints},
    {"sim0.sim_drawing_itemcolors", sim_drawing_itemcolors},
    {"sim0.sim_drawing_vertexcolors", sim_drawing_vertexcolors},
    {"sim0.sim_drawing_itemsizes", sim_drawing_itemsizes},
    {"sim0.sim_drawing_backfaceculling", sim_drawing_backfaceculling},
    {"sim0.sim_drawing_wireframe", sim_drawing_wireframe},
    {"sim0.sim_drawing_painttag", sim_drawing_painttag},
    {"sim0.sim_drawing_followparentvisibility", sim_drawing_followparentvisibility},
    {"sim0.sim_drawing_cyclic", sim_drawing_cyclic},
    {"sim0.sim_drawing_50percenttransparency", sim_drawing_50percenttransparency},
    {"sim0.sim_drawing_25percenttransparency", sim_drawing_25percenttransparency},
    {"sim0.sim_drawing_12percenttransparency", sim_drawing_12percenttransparency},
    {"sim0.sim_drawing_emissioncolor", sim_drawing_emissioncolor},
    {"sim0.sim_drawing_facingcamera", sim_drawing_facingcamera},
    {"sim0.sim_drawing_overlay", sim_drawing_overlay},
    {"sim0.sim_drawing_itemtransparency", sim_drawing_itemtransparency},
    {"sim0.sim_drawing_persistent", sim_drawing_persistent},
    {"sim0.sim_drawing_auxchannelcolor1", sim_drawing_auxchannelcolor1},
    {"sim0.sim_drawing_auxchannelcolor2", sim_drawing_auxchannelcolor2},
    {"sim0.sim_particle_points1", sim_particle_points1},
    {"sim0.sim_particle_points2", sim_particle_points2},
    {"sim0.sim_particle_points4", sim_particle_points4},
    {"sim0.sim_particle_roughspheres", sim_particle_roughspheres},
    {"sim0.sim_particle_spheres", sim_particle_spheres},
    {"sim0.sim_particle_respondable1to4", sim_particle_respondable1to4},
    {"sim0.sim_particle_respondable5to8", sim_particle_respondable5to8},
    {"sim0.sim_particle_particlerespondable", sim_particle_particlerespondable},
    {"sim0.sim_particle_ignoresgravity", sim_particle_ignoresgravity},
    {"sim0.sim_particle_invisible", sim_particle_invisible},
    {"sim0.sim_particle_painttag", sim_particle_painttag},
    {"sim0.sim_particle_itemsizes", sim_particle_itemsizes},
    {"sim0.sim_particle_itemdensities", sim_particle_itemdensities},
    {"sim0.sim_particle_itemcolors", sim_particle_itemcolors},
    {"sim0.sim_particle_cyclic", sim_particle_cyclic},
    {"sim0.sim_particle_emissioncolor", sim_particle_emissioncolor},
    {"sim0.sim_particle_water", sim_particle_water},
    {"sim0.sim_jointmode_kinematic", sim_jointmode_kinematic},
    {"sim0.sim_jointmode_ik", sim_jointmode_ik_deprecated},
    {"sim0.sim_jointmode_ikdependent", sim_jointmode_reserved_previously_ikdependent},
    {"sim0.sim_jointmode_dependent", sim_jointmode_dependent},
    {"sim0.sim_jointmode_dynamic", sim_jointmode_dynamic},
    {"sim0.sim_filedlg_type_load", sim_filedlg_type_load},
    {"sim0.sim_filedlg_type_save", sim_filedlg_type_save},
    {"sim0.sim_filedlg_type_load_multiple", sim_filedlg_type_load_multiple},
    {"sim0.sim_filedlg_type_folder", sim_filedlg_type_folder},
    {"sim0.sim_msgbox_type_info", sim_msgbox_type_info},
    {"sim0.sim_msgbox_type_question", sim_msgbox_type_question},
    {"sim0.sim_msgbox_type_warning", sim_msgbox_type_warning},
    {"sim0.sim_msgbox_type_critical", sim_msgbox_type_critical},
    {"sim0.sim_msgbox_buttons_ok", sim_msgbox_buttons_ok},
    {"sim0.sim_msgbox_buttons_yesno", sim_msgbox_buttons_yesno},
    {"sim0.sim_msgbox_buttons_yesnocancel", sim_msgbox_buttons_yesnocancel},
    {"sim0.sim_msgbox_buttons_okcancel", sim_msgbox_buttons_okcancel},
    {"sim0.sim_msgbox_return_cancel", sim_msgbox_return_cancel},
    {"sim0.sim_msgbox_return_no", sim_msgbox_return_no},
    {"sim0.sim_msgbox_return_yes", sim_msgbox_return_yes},
    {"sim0.sim_msgbox_return_ok", sim_msgbox_return_ok},
    {"sim0.sim_msgbox_return_error", sim_msgbox_return_error},
    {"sim0.sim_physics_bullet", sim_physics_bullet},
    {"sim0.sim_physics_ode", sim_physics_ode},
    {"sim0.sim_physics_vortex", sim_physics_vortex},
    {"sim0.sim_physics_newton", sim_physics_newton},
    {"sim0.sim_pure_primitive_none", sim_primitiveshape_none},
    {"sim0.sim_pure_primitive_plane", sim_primitiveshape_plane},
    {"sim0.sim_pure_primitive_disc", sim_primitiveshape_disc},
    {"sim0.sim_pure_primitive_cuboid", sim_primitiveshape_cuboid},
    {"sim0.sim_pure_primitive_spheroid", sim_primitiveshape_spheroid},
    {"sim0.sim_pure_primitive_cylinder", sim_primitiveshape_cylinder},
    {"sim0.sim_pure_primitive_cone", sim_primitiveshape_cone},
    {"sim0.sim_pure_primitive_heightfield", sim_primitiveshape_heightfield},
    {"sim0.sim_dummy_linktype_dynamics_loop_closure", sim_dummytype_dynloopclosure},
    {"sim0.sim_dummy_linktype_dynamics_force_constraint", sim_dummy_linktype_dynamics_force_constraint},
    {"sim0.sim_dummy_linktype_gcs_loop_closure", sim_dummy_linktype_gcs_loop_closure},
    {"sim0.sim_dummy_linktype_gcs_tip", sim_dummy_linktype_gcs_tip},
    {"sim0.sim_dummy_linktype_gcs_target", sim_dummy_linktype_gcs_target},
    {"sim0.sim_dummy_linktype_ik_tip_target", sim_dummy_linktype_ik_tip_target},
    {"sim0.sim_colorcomponent_ambient", sim_colorcomponent_ambient},
    {"sim0.sim_colorcomponent_ambient_diffuse", sim_colorcomponent_ambient_diffuse},
    {"sim0.sim_colorcomponent_diffuse", sim_colorcomponent_diffuse},
    {"sim0.sim_colorcomponent_specular", sim_colorcomponent_specular},
    {"sim0.sim_colorcomponent_emission", sim_colorcomponent_emission},
    {"sim0.sim_colorcomponent_transparency", sim_colorcomponent_transparency},
    {"sim0.sim_colorcomponent_auxiliary", sim_colorcomponent_auxiliary},
    {"sim0.sim_volume_ray", sim_volume_ray},
    {"sim0.sim_volume_randomizedray", sim_volume_randomizedray},
    {"sim0.sim_volume_pyramid", sim_volume_pyramid},
    {"sim0.sim_volume_cylinder", sim_volume_cylinder},
    {"sim0.sim_volume_disc", sim_volume_disc},
    {"sim0.sim_volume_cone", sim_volume_cone},
    {"sim0.sim_objintparam_visibility_layer", sim_objintparam_visibility_layer},
    {"sim0.sim_objfloatparam_abs_x_velocity", sim_objfloatparam_abs_x_velocity},
    {"sim0.sim_objfloatparam_abs_y_velocity", sim_objfloatparam_abs_y_velocity},
    {"sim0.sim_objfloatparam_abs_z_velocity", sim_objfloatparam_abs_z_velocity},
    {"sim0.sim_objfloatparam_abs_rot_velocity", sim_objfloatparam_abs_rot_velocity},
    {"sim0.sim_objfloatparam_objbbox_min_x", sim_objfloatparam_objbbox_min_x},
    {"sim0.sim_objfloatparam_objbbox_min_y", sim_objfloatparam_objbbox_min_y},
    {"sim0.sim_objfloatparam_objbbox_min_z", sim_objfloatparam_objbbox_min_z},
    {"sim0.sim_objfloatparam_objbbox_max_x", sim_objfloatparam_objbbox_max_x},
    {"sim0.sim_objfloatparam_objbbox_max_y", sim_objfloatparam_objbbox_max_y},
    {"sim0.sim_objfloatparam_objbbox_max_z", sim_objfloatparam_objbbox_max_z},
    {"sim0.sim_objfloatparam_modelbbox_min_x", sim_objfloatparam_modelbbox_min_x},
    {"sim0.sim_objfloatparam_modelbbox_min_y", sim_objfloatparam_modelbbox_min_y},
    {"sim0.sim_objfloatparam_modelbbox_min_z", sim_objfloatparam_modelbbox_min_z},
    {"sim0.sim_objfloatparam_modelbbox_max_x", sim_objfloatparam_modelbbox_max_x},
    {"sim0.sim_objfloatparam_modelbbox_max_y", sim_objfloatparam_modelbbox_max_y},
    {"sim0.sim_objfloatparam_modelbbox_max_z", sim_objfloatparam_modelbbox_max_z},
    {"sim0.sim_objintparam_collection_self_collision_indicator",
     sim_objintparam_collection_self_collision_indicator},
    {"sim0.sim_objfloatparam_transparency_offset", sim_objfloatparam_transparency_offset},
    {"sim0.sim_objintparam_child_role", sim_objintparam_child_role},
    {"sim0.sim_objintparam_parent_role", sim_objintparam_parent_role},
    {"sim0.sim_objintparam_manipulation_permissions", sim_objintparam_manipulation_permissions},
    {"sim0.sim_objintparam_illumination_handle", sim_objintparam_illumination_handle},
    {"sim0.sim_objstringparam_dna", sim_objstringparam_dna},
    {"sim0.sim_visionfloatparam_near_clipping", sim_visionfloatparam_near_clipping},
    {"sim0.sim_visionfloatparam_far_clipping", sim_visionfloatparam_far_clipping},
    {"sim0.sim_visionintparam_resolution_x", sim_visionintparam_resolution_x},
    {"sim0.sim_visionintparam_resolution_y", sim_visionintparam_resolution_y},
    {"sim0.sim_visionfloatparam_perspective_angle", sim_visionfloatparam_perspective_angle},
    {"sim0.sim_visionfloatparam_ortho_size", sim_visionfloatparam_ortho_size},
    {"sim0.sim_visionintparam_disabled_light_components", sim_visionintparam_disabled_light_components},
    {"sim0.sim_visionintparam_rendering_attributes", sim_visionintparam_rendering_attributes},
    {"sim0.sim_visionintparam_entity_to_render", sim_visionintparam_entity_to_render},
    {"sim0.sim_visionintparam_windowed_size_x", sim_visionintparam_windowed_size_x},
    {"sim0.sim_visionintparam_windowed_size_y", sim_visionintparam_windowed_size_y},
    {"sim0.sim_visionintparam_windowed_pos_x", sim_visionintparam_windowed_pos_x},
    {"sim0.sim_visionintparam_windowed_pos_y", sim_visionintparam_windowed_pos_y},
    {"sim0.sim_visionintparam_pov_focal_blur", sim_visionintparam_pov_focal_blur},
    {"sim0.sim_visionfloatparam_pov_blur_distance", sim_visionfloatparam_pov_blur_distance},
    {"sim0.sim_visionfloatparam_pov_aperture", sim_visionfloatparam_pov_aperture},
    {"sim0.sim_visionintparam_pov_blur_sampled", sim_visionintparam_pov_blur_sampled},
    {"sim0.sim_visionintparam_render_mode", sim_visionintparam_render_mode},
    {"sim0.sim_jointintparam_motor_enabled", sim_jointintparam_motor_enabled},
    {"sim0.sim_jointintparam_ctrl_enabled", sim_jointintparam_ctrl_enabled},
    {"sim0.sim_jointfloatparam_pid_p", sim_jointfloatparam_pid_p},
    {"sim0.sim_jointfloatparam_pid_i", sim_jointfloatparam_pid_i},
    {"sim0.sim_jointfloatparam_pid_d", sim_jointfloatparam_pid_d},
    {"sim0.sim_jointfloatparam_intrinsic_x", sim_jointfloatparam_intrinsic_x},
    {"sim0.sim_jointfloatparam_intrinsic_y", sim_jointfloatparam_intrinsic_y},
    {"sim0.sim_jointfloatparam_intrinsic_z", sim_jointfloatparam_intrinsic_z},
    {"sim0.sim_jointfloatparam_intrinsic_qx", sim_jointfloatparam_intrinsic_qx},
    {"sim0.sim_jointfloatparam_intrinsic_qy", sim_jointfloatparam_intrinsic_qy},
    {"sim0.sim_jointfloatparam_intrinsic_qz", sim_jointfloatparam_intrinsic_qz},
    {"sim0.sim_jointfloatparam_intrinsic_qw", sim_jointfloatparam_intrinsic_qw},
    {"sim0.sim_jointfloatparam_velocity", sim_jointfloatparam_velocity},
    {"sim0.sim_jointfloatparam_spherical_qx", sim_jointfloatparam_spherical_qx},
    {"sim0.sim_jointfloatparam_spherical_qy", sim_jointfloatparam_spherical_qy},
    {"sim0.sim_jointfloatparam_spherical_qz", sim_jointfloatparam_spherical_qz},
    {"sim0.sim_jointfloatparam_spherical_qw", sim_jointfloatparam_spherical_qw},
    {"sim0.sim_jointfloatparam_upper_limit", sim_jointfloatparam_upper_limit},
    {"sim0.sim_jointfloatparam_kc_k", sim_jointfloatparam_kc_k},
    {"sim0.sim_jointfloatparam_kc_c", sim_jointfloatparam_kc_c},
    {"sim0.sim_jointfloatparam_ik_weight", sim_jointfloatparam_ik_weight},
    {"sim0.sim_jointfloatparam_error_x", sim_jointfloatparam_error_x},
    {"sim0.sim_jointfloatparam_error_y", sim_jointfloatparam_error_y},
    {"sim0.sim_jointfloatparam_error_z", sim_jointfloatparam_error_z},
    {"sim0.sim_jointfloatparam_error_a", sim_jointfloatparam_error_a},
    {"sim0.sim_jointfloatparam_error_b", sim_jointfloatparam_error_b},
    {"sim0.sim_jointfloatparam_error_g", sim_jointfloatparam_error_g},
    {"sim0.sim_jointfloatparam_error_pos", sim_jointfloatparam_error_pos},
    {"sim0.sim_jointfloatparam_error_angle", sim_jointfloatparam_error_angle},
    {"sim0.sim_jointintparam_velocity_lock", sim_jointintparam_velocity_lock},
    {"sim0.sim_jointintparam_vortex_dep_handle", sim_jointintparam_vortex_dep_handle},
    {"sim0.sim_jointfloatparam_vortex_dep_multiplication", sim_jointfloatparam_vortex_dep_multiplication},
    {"sim0.sim_jointfloatparam_vortex_dep_offset", sim_jointfloatparam_vortex_dep_offset},
    {"sim0.sim_shapefloatparam_init_velocity_x", sim_shapefloatparam_init_velocity_x},
    {"sim0.sim_shapefloatparam_init_velocity_y", sim_shapefloatparam_init_velocity_y},
    {"sim0.sim_shapefloatparam_init_velocity_z", sim_shapefloatparam_init_velocity_z},
    {"sim0.sim_shapeintparam_static", sim_shapeintparam_static},
    {"sim0.sim_shapeintparam_respondable", sim_shapeintparam_respondable},
    {"sim0.sim_shapefloatparam_mass", sim_shapefloatparam_mass},
    {"sim0.sim_shapefloatparam_texture_x", sim_shapefloatparam_texture_x},
    {"sim0.sim_shapefloatparam_texture_y", sim_shapefloatparam_texture_y},
    {"sim0.sim_shapefloatparam_texture_z", sim_shapefloatparam_texture_z},
    {"sim0.sim_shapefloatparam_texture_a", sim_shapefloatparam_texture_a},
    {"sim0.sim_shapefloatparam_texture_b", sim_shapefloatparam_texture_b},
    {"sim0.sim_shapefloatparam_texture_g", sim_shapefloatparam_texture_g},
    {"sim0.sim_shapefloatparam_texture_scaling_x", sim_shapefloatparam_texture_scaling_x},
    {"sim0.sim_shapefloatparam_texture_scaling_y", sim_shapefloatparam_texture_scaling_y},
    {"sim0.sim_shapeintparam_culling", sim_shapeintparam_culling},
    {"sim0.sim_shapeintparam_wireframe", sim_shapeintparam_wireframe},
    {"sim0.sim_shapeintparam_compound", sim_shapeintparam_compound},
    {"sim0.sim_shapeintparam_convex", sim_shapeintparam_convex},
    {"sim0.sim_shapeintparam_convex_check", sim_shapeintparam_convex_check},
    {"sim0.sim_shapeintparam_respondable_mask", sim_shapeintparam_respondable_mask},
    {"sim0.sim_shapefloatparam_init_velocity_a", sim_shapefloatparam_init_ang_velocity_x},
    {"sim0.sim_shapefloatparam_init_velocity_b", sim_shapefloatparam_init_ang_velocity_y},
    {"sim0.sim_shapefloatparam_init_velocity_g", sim_shapefloatparam_init_ang_velocity_z},
    {"sim0.sim_shapestringparam_color_name", sim_shapestringparam_color_name},
    {"sim0.sim_shapeintparam_edge_visibility", sim_shapeintparam_edge_visibility},
    {"sim0.sim_shapefloatparam_shading_angle", sim_shapefloatparam_shading_angle},
    {"sim0.sim_shapefloatparam_edge_angle", sim_shapefloatparam_edge_angle},
    {"sim0.sim_shapeintparam_edge_borders_hidden", sim_shapeintparam_edge_borders_hidden},
    {"sim0.sim_proxintparam_ray_invisibility", sim_proxintparam_ray_invisibility},
    {"sim0.sim_proxintparam_volume_type", sim_proxintparam_volume_type},
    {"sim0.sim_proxintparam_entity_to_detect", sim_proxintparam_entity_to_detect},
    {"sim0.sim_forcefloatparam_error_x", sim_forcefloatparam_error_x},
    {"sim0.sim_forcefloatparam_error_y", sim_forcefloatparam_error_y},
    {"sim0.sim_forcefloatparam_error_z", sim_forcefloatparam_error_z},
    {"sim0.sim_forcefloatparam_error_a", sim_forcefloatparam_error_a},
    {"sim0.sim_forcefloatparam_error_b", sim_forcefloatparam_error_b},
    {"sim0.sim_forcefloatparam_error_g", sim_forcefloatparam_error_g},
    {"sim0.sim_forcefloatparam_error_pos", sim_forcefloatparam_error_pos},
    {"sim0.sim_forcefloatparam_error_angle", sim_forcefloatparam_error_angle},
    {"sim0.sim_lightintparam_pov_casts_shadows", sim_lightintparam_pov_casts_shadows},
    {"sim0.sim_cameraintparam_disabled_light_components", sim_cameraintparam_disabled_light_components},
    {"sim0.sim_camerafloatparam_perspective_angle", sim_camerafloatparam_perspective_angle},
    {"sim0.sim_camerafloatparam_ortho_size", sim_camerafloatparam_ortho_size},
    {"sim0.sim_cameraintparam_rendering_attributes", sim_cameraintparam_rendering_attributes},
    {"sim0.sim_cameraintparam_pov_focal_blur", sim_cameraintparam_pov_focal_blur},
    {"sim0.sim_camerafloatparam_pov_blur_distance", sim_camerafloatparam_pov_blur_distance},
    {"sim0.sim_camerafloatparam_pov_aperture", sim_camerafloatparam_pov_aperture},
    {"sim0.sim_cameraintparam_pov_blur_samples", sim_cameraintparam_pov_blur_samples},
    {"sim0.sim_dummyintparam_link_type", sim_dummyintparam_dummytype},
    {"sim0.sim_dummyintparam_follow_path", sim_dummyintparam_follow_path},
    {"sim0.sim_dummyfloatparam_follow_path_offset", sim_dummyfloatparam_follow_path_offset},
    {"sim0.sim_millintparam_volume_type", sim_millintparam_volume_type},
    {"sim0.sim_mirrorfloatparam_width", sim_mirrorfloatparam_width},
    {"sim0.sim_mirrorfloatparam_height", sim_mirrorfloatparam_height},
    {"sim0.sim_mirrorfloatparam_reflectance", sim_mirrorfloatparam_reflectance},
    {"sim0.sim_mirrorintparam_enable", sim_mirrorintparam_enable},
    {"sim0.sim_bullet_global_stepsize", sim_bullet_global_stepsize},
    {"sim0.sim_bullet_global_internalscalingfactor", sim_bullet_global_internalscalingfactor},
    {"sim0.sim_bullet_global_collisionmarginfactor", sim_bullet_global_collisionmarginfactor},
    {"sim0.sim_bullet_global_constraintsolvingiterations", sim_bullet_global_constraintsolvingiterations},
    {"sim0.sim_bullet_global_bitcoded", sim_bullet_global_bitcoded},
    {"sim0.sim_bullet_global_constraintsolvertype", sim_bullet_global_constraintsolvertype},
    {"sim0.sim_bullet_global_fullinternalscaling", sim_bullet_global_fullinternalscaling},
    {"sim0.sim_bullet_joint_stoperp", sim_bullet_joint_stoperp},
    {"sim0.sim_bullet_joint_stopcfm", sim_bullet_joint_stopcfm},
    {"sim0.sim_bullet_joint_normalcfm", sim_bullet_joint_normalcfm},
    {"sim0.sim_bullet_body_restitution", sim_bullet_body_restitution},
    {"sim0.sim_bullet_body_oldfriction", sim_bullet_body_oldfriction},
    {"sim0.sim_bullet_body_friction", sim_bullet_body_friction},
    {"sim0.sim_bullet_body_lineardamping", sim_bullet_body_lineardamping},
    {"sim0.sim_bullet_body_angulardamping", sim_bullet_body_angulardamping},
    {"sim0.sim_bullet_body_nondefaultcollisionmargingfactor", sim_bullet_body_nondefaultcollisionmargingfactor},
    {"sim0.sim_bullet_body_nondefaultcollisionmargingfactorconvex",
     sim_bullet_body_nondefaultcollisionmargingfactorconvex},
    {"sim0.sim_bullet_body_bitcoded", sim_bullet_body_bitcoded},
    {"sim0.sim_bullet_body_sticky", sim_bullet_body_sticky},
    {"sim0.sim_bullet_body_usenondefaultcollisionmargin", sim_bullet_body_usenondefaultcollisionmargin},
    {"sim0.sim_bullet_body_usenondefaultcollisionmarginconvex", sim_bullet_body_usenondefaultcollisionmarginconvex},
    {"sim0.sim_bullet_body_autoshrinkconvex", sim_bullet_body_autoshrinkconvex},
    {"sim0.sim_ode_global_stepsize", sim_ode_global_stepsize},
    {"sim0.sim_ode_global_internalscalingfactor", sim_ode_global_internalscalingfactor},
    {"sim0.sim_ode_global_cfm", sim_ode_global_cfm},
    {"sim0.sim_ode_global_erp", sim_ode_global_erp},
    {"sim0.sim_ode_global_constraintsolvingiterations", sim_ode_global_constraintsolvingiterations},
    {"sim0.sim_ode_global_bitcoded", sim_ode_global_bitcoded},
    {"sim0.sim_ode_global_randomseed", sim_ode_global_randomseed},
    {"sim0.sim_ode_global_fullinternalscaling", sim_ode_global_fullinternalscaling},
    {"sim0.sim_ode_global_quickstep", sim_ode_global_quickstep},
    {"sim0.sim_ode_joint_stoperp", sim_ode_joint_stoperp},
    {"sim0.sim_ode_joint_stopcfm", sim_ode_joint_stopcfm},
    {"sim0.sim_ode_joint_bounce", sim_ode_joint_bounce},
    {"sim0.sim_ode_joint_fudgefactor", sim_ode_joint_fudgefactor},
    {"sim0.sim_ode_joint_normalcfm", sim_ode_joint_normalcfm},
    {"sim0.sim_ode_body_friction", sim_ode_body_friction},
    {"sim0.sim_ode_body_softerp", sim_ode_body_softerp},
    {"sim0.sim_ode_body_softcfm", sim_ode_body_softcfm},
    {"sim0.sim_ode_body_lineardamping", sim_ode_body_lineardamping},
    {"sim0.sim_ode_body_angulardamping", sim_ode_body_angulardamping},
    {"sim0.sim_ode_body_maxcontacts", sim_ode_body_maxcontacts},
    {"sim0.sim_vortex_global_stepsize", sim_vortex_global_stepsize},
    {"sim0.sim_vortex_global_internalscalingfactor", sim_vortex_global_internalscalingfactor},
    {"sim0.sim_vortex_global_contacttolerance", sim_vortex_global_contacttolerance},
    {"sim0.sim_vortex_global_constraintlinearcompliance", sim_vortex_global_constraintlinearcompliance},
    {"sim0.sim_vortex_global_constraintlineardamping", sim_vortex_global_constraintlineardamping},
    {"sim0.sim_vortex_global_constraintlinearkineticloss", sim_vortex_global_constraintlinearkineticloss},
    {"sim0.sim_vortex_global_constraintangularcompliance", sim_vortex_global_constraintangularcompliance},
    {"sim0.sim_vortex_global_constraintangulardamping", sim_vortex_global_constraintangulardamping},
    {"sim0.sim_vortex_global_constraintangularkineticloss", sim_vortex_global_constraintangularkineticloss},
    {"sim0.sim_vortex_global_bitcoded", sim_vortex_global_bitcoded},
    {"sim0.sim_vortex_global_autosleep", sim_vortex_global_autosleep},
    {"sim0.sim_vortex_global_multithreading", sim_vortex_global_multithreading},
    {"sim0.sim_vortex_joint_lowerlimitdamping", sim_vortex_joint_lowerlimitdamping},
    {"sim0.sim_vortex_joint_upperlimitdamping", sim_vortex_joint_upperlimitdamping},
    {"sim0.sim_vortex_joint_lowerlimitstiffness", sim_vortex_joint_lowerlimitstiffness},
    {"sim0.sim_vortex_joint_upperlimitstiffness", sim_vortex_joint_upperlimitstiffness},
    {"sim0.sim_vortex_joint_lowerlimitrestitution", sim_vortex_joint_lowerlimitrestitution},
    {"sim0.sim_vortex_joint_upperlimitrestitution", sim_vortex_joint_upperlimitrestitution},
    {"sim0.sim_vortex_joint_lowerlimitmaxforce", sim_vortex_joint_lowerlimitmaxforce},
    {"sim0.sim_vortex_joint_upperlimitmaxforce", sim_vortex_joint_upperlimitmaxforce},
    {"sim0.sim_vortex_joint_motorconstraintfrictioncoeff", sim_vortex_joint_motorconstraintfrictioncoeff},
    {"sim0.sim_vortex_joint_motorconstraintfrictionmaxforce", sim_vortex_joint_motorconstraintfrictionmaxforce},
    {"sim0.sim_vortex_joint_motorconstraintfrictionloss", sim_vortex_joint_motorconstraintfrictionloss},
    {"sim0.sim_vortex_joint_p0loss", sim_vortex_joint_p0loss},
    {"sim0.sim_vortex_joint_p0stiffness", sim_vortex_joint_p0stiffness},
    {"sim0.sim_vortex_joint_p0damping", sim_vortex_joint_p0damping},
    {"sim0.sim_vortex_joint_p0frictioncoeff", sim_vortex_joint_p0frictioncoeff},
    {"sim0.sim_vortex_joint_p0frictionmaxforce", sim_vortex_joint_p0frictionmaxforce},
    {"sim0.sim_vortex_joint_p0frictionloss", sim_vortex_joint_p0frictionloss},
    {"sim0.sim_vortex_joint_p1loss", sim_vortex_joint_p1loss},
    {"sim0.sim_vortex_joint_p1stiffness", sim_vortex_joint_p1stiffness},
    {"sim0.sim_vortex_joint_p1damping", sim_vortex_joint_p1damping},
    {"sim0.sim_vortex_joint_p1frictioncoeff", sim_vortex_joint_p1frictioncoeff},
    {"sim0.sim_vortex_joint_p1frictionmaxforce", sim_vortex_joint_p1frictionmaxforce},
    {"sim0.sim_vortex_joint_p1frictionloss", sim_vortex_joint_p1frictionloss},
    {"sim0.sim_vortex_joint_p2loss", sim_vortex_joint_p2loss},
    {"sim0.sim_vortex_joint_p2stiffness", sim_vortex_joint_p2stiffness},
    {"sim0.sim_vortex_joint_p2damping", sim_vortex_joint_p2damping},
    {"sim0.sim_vortex_joint_p2frictioncoeff", sim_vortex_joint_p2frictioncoeff},
    {"sim0.sim_vortex_joint_p2frictionmaxforce", sim_vortex_joint_p2frictionmaxforce},
    {"sim0.sim_vortex_joint_p2frictionloss", sim_vortex_joint_p2frictionloss},
    {"sim0.sim_vortex_joint_a0loss", sim_vortex_joint_a0loss},
    {"sim0.sim_vortex_joint_a0stiffness", sim_vortex_joint_a0stiffness},
    {"sim0.sim_vortex_joint_a0damping", sim_vortex_joint_a0damping},
    {"sim0.sim_vortex_joint_a0frictioncoeff", sim_vortex_joint_a0frictioncoeff},
    {"sim0.sim_vortex_joint_a0frictionmaxforce", sim_vortex_joint_a0frictionmaxforce},
    {"sim0.sim_vortex_joint_a0frictionloss", sim_vortex_joint_a0frictionloss},
    {"sim0.sim_vortex_joint_a1loss", sim_vortex_joint_a1loss},
    {"sim0.sim_vortex_joint_a1stiffness", sim_vortex_joint_a1stiffness},
    {"sim0.sim_vortex_joint_a1damping", sim_vortex_joint_a1damping},
    {"sim0.sim_vortex_joint_a1frictioncoeff", sim_vortex_joint_a1frictioncoeff},
    {"sim0.sim_vortex_joint_a1frictionmaxforce", sim_vortex_joint_a1frictionmaxforce},
    {"sim0.sim_vortex_joint_a1frictionloss", sim_vortex_joint_a1frictionloss},
    {"sim0.sim_vortex_joint_a2loss", sim_vortex_joint_a2loss},
    {"sim0.sim_vortex_joint_a2stiffness", sim_vortex_joint_a2stiffness},
    {"sim0.sim_vortex_joint_a2damping", sim_vortex_joint_a2damping},
    {"sim0.sim_vortex_joint_a2frictioncoeff", sim_vortex_joint_a2frictioncoeff},
    {"sim0.sim_vortex_joint_a2frictionmaxforce", sim_vortex_joint_a2frictionmaxforce},
    {"sim0.sim_vortex_joint_a2frictionloss", sim_vortex_joint_a2frictionloss},
    {"sim0.sim_vortex_joint_dependencyfactor", sim_vortex_joint_dependencyfactor},
    {"sim0.sim_vortex_joint_dependencyoffset", sim_vortex_joint_dependencyoffset},
    {"sim0.sim_vortex_joint_bitcoded", sim_vortex_joint_bitcoded},
    {"sim0.sim_vortex_joint_relaxationenabledbc", sim_vortex_joint_relaxationenabledbc},
    {"sim0.sim_vortex_joint_frictionenabledbc", sim_vortex_joint_frictionenabledbc},
    {"sim0.sim_vortex_joint_frictionproportionalbc", sim_vortex_joint_frictionproportionalbc},
    {"sim0.sim_vortex_joint_objectid", sim_vortex_joint_objectid},
    {"sim0.sim_vortex_joint_dependentobjectid", sim_vortex_joint_dependentobjectid},
    {"sim0.sim_vortex_joint_motorfrictionenabled", sim_vortex_joint_motorfrictionenabled},
    {"sim0.sim_vortex_joint_proportionalmotorfriction", sim_vortex_joint_proportionalmotorfriction},
    {"sim0.sim_vortex_body_primlinearaxisfriction", sim_vortex_body_primlinearaxisfriction},
    {"sim0.sim_vortex_body_seclinearaxisfriction", sim_vortex_body_seclinearaxisfriction},
    {"sim0.sim_vortex_body_primangularaxisfriction", sim_vortex_body_primangularaxisfriction},
    {"sim0.sim_vortex_body_secangularaxisfriction", sim_vortex_body_secangularaxisfriction},
    {"sim0.sim_vortex_body_normalangularaxisfriction", sim_vortex_body_normalangularaxisfriction},
    {"sim0.sim_vortex_body_primlinearaxisstaticfrictionscale", sim_vortex_body_primlinearaxisstaticfrictionscale},
    {"sim0.sim_vortex_body_seclinearaxisstaticfrictionscale", sim_vortex_body_seclinearaxisstaticfrictionscale},
    {"sim0.sim_vortex_body_primangularaxisstaticfrictionscale", sim_vortex_body_primangularaxisstaticfrictionscale},
    {"sim0.sim_vortex_body_secangularaxisstaticfrictionscale", sim_vortex_body_secangularaxisstaticfrictionscale},
    {"sim0.sim_vortex_body_normalangularaxisstaticfrictionscale",
     sim_vortex_body_normalangularaxisstaticfrictionscale},
    {"sim0.sim_vortex_body_compliance", sim_vortex_body_compliance},
    {"sim0.sim_vortex_body_damping", sim_vortex_body_damping},
    {"sim0.sim_vortex_body_restitution", sim_vortex_body_restitution},
    {"sim0.sim_vortex_body_restitutionthreshold", sim_vortex_body_restitutionthreshold},
    {"sim0.sim_vortex_body_adhesiveforce", sim_vortex_body_adhesiveforce},
    {"sim0.sim_vortex_body_linearvelocitydamping", sim_vortex_body_linearvelocitydamping},
    {"sim0.sim_vortex_body_angularvelocitydamping", sim_vortex_body_angularvelocitydamping},
    {"sim0.sim_vortex_body_primlinearaxisslide", sim_vortex_body_primlinearaxisslide},
    {"sim0.sim_vortex_body_seclinearaxisslide", sim_vortex_body_seclinearaxisslide},
    {"sim0.sim_vortex_body_primangularaxisslide", sim_vortex_body_primangularaxisslide},
    {"sim0.sim_vortex_body_secangularaxisslide", sim_vortex_body_secangularaxisslide},
    {"sim0.sim_vortex_body_normalangularaxisslide", sim_vortex_body_normalangularaxisslide},
    {"sim0.sim_vortex_body_primlinearaxisslip", sim_vortex_body_primlinearaxisslip},
    {"sim0.sim_vortex_body_seclinearaxisslip", sim_vortex_body_seclinearaxisslip},
    {"sim0.sim_vortex_body_primangularaxisslip", sim_vortex_body_primangularaxisslip},
    {"sim0.sim_vortex_body_secangularaxisslip", sim_vortex_body_secangularaxisslip},
    {"sim0.sim_vortex_body_normalangularaxisslip", sim_vortex_body_normalangularaxisslip},
    {"sim0.sim_vortex_body_autosleeplinearspeedthreshold", sim_vortex_body_autosleeplinearspeedthreshold},
    {"sim0.sim_vortex_body_autosleeplinearaccelthreshold", sim_vortex_body_autosleeplinearaccelthreshold},
    {"sim0.sim_vortex_body_autosleepangularspeedthreshold", sim_vortex_body_autosleepangularspeedthreshold},
    {"sim0.sim_vortex_body_autosleepangularaccelthreshold", sim_vortex_body_autosleepangularaccelthreshold},
    {"sim0.sim_vortex_body_skinthickness", sim_vortex_body_skinthickness},
    {"sim0.sim_vortex_body_autoangulardampingtensionratio", sim_vortex_body_autoangulardampingtensionratio},
    {"sim0.sim_vortex_body_primaxisvectorx", sim_vortex_body_primaxisvectorx},
    {"sim0.sim_vortex_body_primaxisvectory", sim_vortex_body_primaxisvectory},
    {"sim0.sim_vortex_body_primaxisvectorz", sim_vortex_body_primaxisvectorz},
    {"sim0.sim_vortex_body_primlinearaxisfrictionmodel", sim_vortex_body_primlinearaxisfrictionmodel},
    {"sim0.sim_vortex_body_seclinearaxisfrictionmodel", sim_vortex_body_seclinearaxisfrictionmodel},
    {"sim0.sim_vortex_body_primangulararaxisfrictionmodel", sim_vortex_body_primangulararaxisfrictionmodel},
    {"sim0.sim_vortex_body_secmangulararaxisfrictionmodel", sim_vortex_body_secmangulararaxisfrictionmodel},
    {"sim0.sim_vortex_body_normalmangulararaxisfrictionmodel", sim_vortex_body_normalmangulararaxisfrictionmodel},
    {"sim0.sim_vortex_body_bitcoded", sim_vortex_body_bitcoded},
    {"sim0.sim_vortex_body_autosleepsteplivethreshold", sim_vortex_body_autosleepsteplivethreshold},
    {"sim0.sim_vortex_body_materialuniqueid", sim_vortex_body_materialuniqueid},
    {"sim0.sim_vortex_body_pureshapesasconvex", sim_vortex_body_pureshapesasconvex},
    {"sim0.sim_vortex_body_convexshapesasrandom", sim_vortex_body_convexshapesasrandom},
    {"sim0.sim_vortex_body_randomshapesasterrain", sim_vortex_body_randomshapesasterrain},
    {"sim0.sim_vortex_body_fastmoving", sim_vortex_body_fastmoving},
    {"sim0.sim_vortex_body_autoslip", sim_vortex_body_autoslip},
    {"sim0.sim_vortex_body_seclinaxissameasprimlinaxis", sim_vortex_body_seclinaxissameasprimlinaxis},
    {"sim0.sim_vortex_body_secangaxissameasprimangaxis", sim_vortex_body_secangaxissameasprimangaxis},
    {"sim0.sim_vortex_body_normangaxissameasprimangaxis", sim_vortex_body_normangaxissameasprimangaxis},
    {"sim0.sim_vortex_body_autoangulardamping", sim_vortex_body_autoangulardamping},
    {"sim0.sim_newton_global_stepsize", sim_newton_global_stepsize},
    {"sim0.sim_newton_global_contactmergetolerance", sim_newton_global_contactmergetolerance},
    {"sim0.sim_newton_global_constraintsolvingiterations", sim_newton_global_constraintsolvingiterations},
    {"sim0.sim_newton_global_bitcoded", sim_newton_global_bitcoded},
    {"sim0.sim_newton_global_multithreading", sim_newton_global_multithreading},
    {"sim0.sim_newton_global_exactsolver", sim_newton_global_exactsolver},
    {"sim0.sim_newton_global_highjointaccuracy", sim_newton_global_highjointaccuracy},
    {"sim0.sim_newton_joint_dependencyfactor", sim_newton_joint_dependencyfactor},
    {"sim0.sim_newton_joint_dependencyoffset", sim_newton_joint_dependencyoffset},
    {"sim0.sim_newton_joint_objectid", sim_newton_joint_objectid},
    {"sim0.sim_newton_joint_dependentobjectid", sim_newton_joint_dependentobjectid},
    {"sim0.sim_newton_body_staticfriction", sim_newton_body_staticfriction},
    {"sim0.sim_newton_body_kineticfriction", sim_newton_body_kineticfriction},
    {"sim0.sim_newton_body_restitution", sim_newton_body_restitution},
    {"sim0.sim_newton_body_lineardrag", sim_newton_body_lineardrag},
    {"sim0.sim_newton_body_angulardrag", sim_newton_body_angulardrag},
    {"sim0.sim_newton_body_bitcoded", sim_newton_body_bitcoded},
    {"sim0.sim_newton_body_fastmoving", sim_newton_body_fastmoving},
    {"sim0.sim_vortex_bodyfrictionmodel_box", sim_vortex_bodyfrictionmodel_box},
    {"sim0.sim_vortex_bodyfrictionmodel_scaledbox", sim_vortex_bodyfrictionmodel_scaledbox},
    {"sim0.sim_vortex_bodyfrictionmodel_proplow", sim_vortex_bodyfrictionmodel_proplow},
    {"sim0.sim_vortex_bodyfrictionmodel_prophigh", sim_vortex_bodyfrictionmodel_prophigh},
    {"sim0.sim_vortex_bodyfrictionmodel_scaledboxfast", sim_vortex_bodyfrictionmodel_scaledboxfast},
    {"sim0.sim_vortex_bodyfrictionmodel_neutral", sim_vortex_bodyfrictionmodel_neutral},
    {"sim0.sim_vortex_bodyfrictionmodel_none", sim_vortex_bodyfrictionmodel_none},
    {"sim0.sim_bullet_constraintsolvertype_sequentialimpulse", sim_bullet_constraintsolvertype_sequentialimpulse},
    {"sim0.sim_bullet_constraintsolvertype_nncg", sim_bullet_constraintsolvertype_nncg},
    {"sim0.sim_bullet_constraintsolvertype_dantzig", sim_bullet_constraintsolvertype_dantzig},
    {"sim0.sim_bullet_constraintsolvertype_projectedgaussseidel",
     sim_bullet_constraintsolvertype_projectedgaussseidel},
    {"sim0.sim_filtercomponent_originalimage", sim_filtercomponent_originalimage_deprecated},
    {"sim0.sim_filtercomponent_originaldepth", sim_filtercomponent_originaldepth_deprecated},
    {"sim0.sim_filtercomponent_uniformimage", sim_filtercomponent_uniformimage_deprecated},
    {"sim0.sim_filtercomponent_tooutput", sim_filtercomponent_tooutput_deprecated},
    {"sim0.sim_filtercomponent_tobuffer1", sim_filtercomponent_tobuffer1_deprecated},
    {"sim0.sim_filtercomponent_tobuffer2", sim_filtercomponent_tobuffer2_deprecated},
    {"sim0.sim_filtercomponent_frombuffer1", sim_filtercomponent_frombuffer1_deprecated},
    {"sim0.sim_filtercomponent_frombuffer2", sim_filtercomponent_frombuffer2_deprecated},
    {"sim0.sim_filtercomponent_swapbuffers", sim_filtercomponent_swapbuffers_deprecated},
    {"sim0.sim_filtercomponent_addbuffer1", sim_filtercomponent_addbuffer1_deprecated},
    {"sim0.sim_filtercomponent_subtractbuffer1", sim_filtercomponent_subtractbuffer1_deprecated},
    {"sim0.sim_filtercomponent_multiplywithbuffer1", sim_filtercomponent_multiplywithbuffer1_deprecated},
    {"sim0.sim_filtercomponent_horizontalflip", sim_filtercomponent_horizontalflip_deprecated},
    {"sim0.sim_filtercomponent_verticalflip", sim_filtercomponent_verticalflip_deprecated},
    {"sim0.sim_filtercomponent_rotate", sim_filtercomponent_rotate_deprecated},
    {"sim0.sim_filtercomponent_shift", sim_filtercomponent_shift_deprecated},
    {"sim0.sim_filtercomponent_resize", sim_filtercomponent_resize_deprecated},
    {"sim0.sim_filtercomponent_3x3filter", sim_filtercomponent_3x3filter_deprecated},
    {"sim0.sim_filtercomponent_5x5filter", sim_filtercomponent_5x5filter_deprecated},
    {"sim0.sim_filtercomponent_sharpen", sim_filtercomponent_sharpen_deprecated},
    {"sim0.sim_filtercomponent_edge", sim_filtercomponent_edge_deprecated},
    {"sim0.sim_filtercomponent_rectangularcut", sim_filtercomponent_rectangularcut_deprecated},
    {"sim0.sim_filtercomponent_circularcut", sim_filtercomponent_circularcut_deprecated},
    {"sim0.sim_filtercomponent_normalize", sim_filtercomponent_normalize_deprecated},
    {"sim0.sim_filtercomponent_intensityscale", sim_filtercomponent_intensityscale_deprecated},
    {"sim0.sim_filtercomponent_keeporremovecolors", sim_filtercomponent_keeporremovecolors_deprecated},
    {"sim0.sim_filtercomponent_scaleandoffsetcolors", sim_filtercomponent_scaleandoffsetcolors_deprecated},
    {"sim0.sim_filtercomponent_binary", sim_filtercomponent_binary_deprecated},
    {"sim0.sim_filtercomponent_swapwithbuffer1", sim_filtercomponent_swapwithbuffer1_deprecated},
    {"sim0.sim_filtercomponent_addtobuffer1", sim_filtercomponent_addtobuffer1_deprecated},
    {"sim0.sim_filtercomponent_subtractfrombuffer1", sim_filtercomponent_subtractfrombuffer1_deprecated},
    {"sim0.sim_filtercomponent_correlationwithbuffer1", sim_filtercomponent_correlationwithbuffer1_deprecated},
    {"sim0.sim_filtercomponent_colorsegmentation", sim_filtercomponent_colorsegmentation_deprecated},
    {"sim0.sim_filtercomponent_blobextraction", sim_filtercomponent_blobextraction_deprecated},
    {"sim0.sim_filtercomponent_imagetocoord", sim_filtercomponent_imagetocoord_deprecated},
    {"sim0.sim_filtercomponent_pixelchange", sim_filtercomponent_pixelchange_deprecated},
    {"sim0.sim_filtercomponent_velodyne", sim_filtercomponent_velodyne_deprecated},
    {"sim0.sim_filtercomponent_todepthoutput", sim_filtercomponent_todepthoutput_deprecated},
    {"sim0.sim_filtercomponent_customized", sim_filtercomponent_customized_deprecated},
    {"sim0.sim_buffer_uint8", sim_buffer_uint8},
    {"sim0.sim_buffer_int8", sim_buffer_int8},
    {"sim0.sim_buffer_uint16", sim_buffer_uint16},
    {"sim0.sim_buffer_int16", sim_buffer_int16},
    {"sim0.sim_buffer_uint32", sim_buffer_uint32},
    {"sim0.sim_buffer_int32", sim_buffer_int32},
    {"sim0.sim_buffer_float", sim_buffer_float},
    {"sim0.sim_buffer_double", sim_buffer_double},
    {"sim0.sim_buffer_uint8rgb", sim_buffer_uint8rgb},
    {"sim0.sim_buffer_uint8bgr", sim_buffer_uint8bgr},
    {"sim0.sim_imgcomb_vertical", sim_imgcomb_vertical},
    {"sim0.sim_imgcomb_horizontal", sim_imgcomb_horizontal},
    {"sim0.sim_dynmat_default", sim_dynmat_default},
    {"sim0.sim_dynmat_highfriction", sim_dynmat_highfriction},
    {"sim0.sim_dynmat_lowfriction", sim_dynmat_lowfriction},
    {"sim0.sim_dynmat_nofriction", sim_dynmat_nofriction},
    {"sim0.sim_dynmat_reststackgrasp", sim_dynmat_reststackgrasp},
    {"sim0.sim_dynmat_foot", sim_dynmat_foot},
    {"sim0.sim_dynmat_wheel", sim_dynmat_wheel},
    {"sim0.sim_dynmat_gripper", sim_dynmat_gripper},
    {"sim0.sim_dynmat_floor", sim_dynmat_floor},
    // for backward compatibility:
    {"sim0.sim_pplanfloatparam_x_min", sim_pplanfloatparam_x_min},
    {"sim0.sim_pplanfloatparam_x_range", sim_pplanfloatparam_x_range},
    {"sim0.sim_pplanfloatparam_y_min", sim_pplanfloatparam_y_min},
    {"sim0.sim_pplanfloatparam_y_range", sim_pplanfloatparam_y_range},
    {"sim0.sim_pplanfloatparam_z_min", sim_pplanfloatparam_z_min},
    {"sim0.sim_pplanfloatparam_z_range", sim_pplanfloatparam_z_range},
    {"sim0.sim_pplanfloatparam_delta_min", sim_pplanfloatparam_delta_min},
    {"sim0.sim_pplanfloatparam_delta_range", sim_pplanfloatparam_delta_range},
    {"sim0.sim_ui_menu_title", sim_ui_menu_title},
    {"sim0.sim_ui_menu_minimize", sim_ui_menu_minimize},
    {"sim0.sim_ui_menu_close", sim_ui_menu_close},
    {"sim0.sim_api_errormessage_ignore", sim_api_errormessage_ignore},
    {"sim0.sim_api_errormessage_report", sim_api_errormessage_report},
    {"sim0.sim_api_errormessage_output", sim_api_errormessage_output},
    {"sim0.sim_ui_property_visible", sim_ui_property_visible},
    {"sim0.sim_ui_property_visibleduringsimulationonly", sim_ui_property_visibleduringsimulationonly},
    {"sim0.sim_ui_property_moveable", sim_ui_property_moveable},
    {"sim0.sim_ui_property_relativetoleftborder", sim_ui_property_relativetoleftborder},
    {"sim0.sim_ui_property_relativetotopborder", sim_ui_property_relativetotopborder},
    {"sim0.sim_ui_property_fixedwidthfont", sim_ui_property_fixedwidthfont},
    {"sim0.sim_ui_property_systemblock", sim_ui_property_systemblock},
    {"sim0.sim_ui_property_settocenter", sim_ui_property_settocenter},
    {"sim0.sim_ui_property_rolledup", sim_ui_property_rolledup},
    {"sim0.sim_ui_property_selectassociatedobject", sim_ui_property_selectassociatedobject},
    {"sim0.sim_ui_property_visiblewhenobjectselected", sim_ui_property_visiblewhenobjectselected},
    {"sim0.sim_ui_property_systemblockcanmovetofront", sim_ui_property_systemblockcanmovetofront},
    {"sim0.sim_ui_property_pauseactive", sim_ui_property_pauseactive},
    {"sim0.sim_2delement_menu_title", sim_ui_menu_title},
    {"sim0.sim_2delement_menu_minimize", sim_ui_menu_minimize},
    {"sim0.sim_2delement_menu_close", sim_ui_menu_close},
    {"sim0.sim_2delement_property_visible", sim_ui_property_visible},
    {"sim0.sim_2delement_property_visibleduringsimulationonly", sim_ui_property_visibleduringsimulationonly},
    {"sim0.sim_2delement_property_moveable", sim_ui_property_moveable},
    {"sim0.sim_2delement_property_relativetoleftborder", sim_ui_property_relativetoleftborder},
    {"sim0.sim_2delement_property_relativetotopborder", sim_ui_property_relativetotopborder},
    {"sim0.sim_2delement_property_fixedwidthfont", sim_ui_property_fixedwidthfont},
    {"sim0.sim_2delement_property_systemblock", sim_ui_property_systemblock},
    {"sim0.sim_2delement_property_settocenter", sim_ui_property_settocenter},
    {"sim0.sim_2delement_property_rolledup", sim_ui_property_rolledup},
    {"sim0.sim_2delement_property_selectassociatedobject", sim_ui_property_selectassociatedobject},
    {"sim0.sim_2delement_property_visiblewhenobjectselected", sim_ui_property_visiblewhenobjectselected},
    {"sim0.sim_pathproperty_invert_velocity", sim_pathproperty_invert_velocity_deprecated},
    {"sim0.sim_pathproperty_infinite_acceleration", sim_pathproperty_infinite_acceleration_deprecated},
    {"sim0.sim_pathproperty_auto_velocity_profile_translation",
     sim_pathproperty_auto_velocity_profile_translation_deprecated},
    {"sim0.sim_pathproperty_auto_velocity_profile_rotation",
     sim_pathproperty_auto_velocity_profile_rotation_deprecated},
    {"sim0.sim_pathproperty_endpoints_at_zero", sim_pathproperty_endpoints_at_zero_deprecated},
    {"sim0.sim_boolparam_joint_motion_handling_enabled", sim_boolparam_joint_motion_handling_enabled_deprecated},
    {"sim0.sim_boolparam_path_motion_handling_enabled", sim_boolparam_path_motion_handling_enabled_deprecated},
    {"sim0.sim_jointmode_motion", sim_jointmode_motion_deprecated},
    {"sim0.sim_addonscriptcall_run", sim_syscb_aos_run_old},
    {"sim0.sim_navigation_camerafly", sim_navigation_camerafly_old},
    {"sim0.sim_banner_left", sim_banner_left},
    {"sim0.sim_banner_right", sim_banner_right},
    {"sim0.sim_banner_nobackground", sim_banner_nobackground},
    {"sim0.sim_banner_overlay", sim_banner_overlay},
    {"sim0.sim_banner_followparentvisibility", sim_banner_followparentvisibility},
    {"sim0.sim_banner_clickselectsparent", sim_banner_clickselectsparent},
    {"sim0.sim_banner_clicktriggersevent", sim_banner_clicktriggersevent},
    {"sim0.sim_banner_facingcamera", sim_banner_facingcamera},
    {"sim0.sim_banner_fullyfacingcamera", sim_banner_fullyfacingcamera},
    {"sim0.sim_banner_backfaceculling", sim_banner_backfaceculling},
    {"sim0.sim_banner_keepsamesize", sim_banner_keepsamesize},
    {"sim0.sim_banner_bitmapfont", sim_banner_bitmapfont},
    {"", -1}};

bool isObjectAssociatedWithThisThreadedChildScriptValid_old(luaWrap_lua_State* L)
{
    int id = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
    CScriptObject* script = App::worldContainer->getScriptObjectFromHandle(id);
    if (script == nullptr)
        return (false);
    int h = script->getObjectHandleThatScriptIsAttachedTo(sim_scripttype_simulation);
    return (h != -1);
}

void pushCorrectTypeOntoLuaStack_old(luaWrap_lua_State* L, const std::string& buff)
{ // Pushes nil, false, true, number or string (in that order!!) onto the stack depending on the buff content!
    int t = getCorrectType_old(buff);
    if (t == 0)
        luaWrap_lua_pushnil(L);
    if (t == 1)
        luaWrap_lua_pushboolean(L, 0);
    if (t == 2)
        luaWrap_lua_pushboolean(L, 1);
    if (t == 3)
    {
        double floatVal;
        tt::getValidFloat(buff.c_str(), floatVal);
        luaWrap_lua_pushnumber(L, floatVal);
    }
    if (t == 4)
        luaWrap_lua_pushbinarystring(L, buff.c_str(), buff.length()); // push binary string for backw. comp.
}

int getCorrectType_old(const std::string& buff)
{ // returns 0=nil, 1=boolean false, 2=boolean true, 3=number or 4=string (in that order!!) depending on the buff
    // content!
    if (buff.length() != 0)
    {
        if (buff.length() != strlen(buff.c_str()))
            return (4); // We have embedded zeros, this has definitively to be a string:
    }
    if (strcmp(buff.c_str(), "nil") == 0)
        return (0);
    if (strcmp(buff.c_str(), "false") == 0)
        return (1);
    if (strcmp(buff.c_str(), "true") == 0)
        return (2);
    double floatVal;
    if (tt::getValidFloat(buff.c_str(), floatVal))
        return (3);
    return (4);
}

void getScriptTree_old(luaWrap_lua_State* L, bool selfIncluded, std::vector<int>& scriptHandles)
{ // Returns all scripts that are built under the current one
    scriptHandles.clear();
    int currentScriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);

    CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(currentScriptID);
    if (it != nullptr)
    {
        if (it->getScriptType() == sim_scripttype_main)
        { // we have a main script here
            if (selfIncluded)
                scriptHandles.push_back(currentScriptID);
            for (size_t i = 0; i < App::currentWorld->sceneObjects->getObjectCount(); i++)
            {
                CSceneObject* q = App::currentWorld->sceneObjects->getObjectFromIndex(i);
                CScriptObject* lso = App::currentWorld->sceneObjects->embeddedScriptContainer->getScriptFromObjectAttachedTo(
                    sim_scripttype_simulation, q->getObjectHandle());
                if (lso != nullptr)
                    scriptHandles.push_back(lso->getScriptHandle());
            }
        }

        if (it->getScriptType() == sim_scripttype_simulation)
        { // we have a simulation script
            CSceneObject* obj = App::currentWorld->sceneObjects->getObjectFromHandle(
                it->getObjectHandleThatScriptIsAttachedTo(sim_scripttype_simulation));
            if (obj != nullptr)
            { // should always pass
                if (selfIncluded)
                    scriptHandles.push_back(currentScriptID);

                std::vector<CSceneObject*> objList;
                obj->getAllObjectsRecursive(&objList, false);
                for (int i = 0; i < int(objList.size()); i++)
                {
                    CScriptObject* lso = App::currentWorld->sceneObjects->embeddedScriptContainer->getScriptFromObjectAttachedTo(
                        sim_scripttype_simulation, objList[i]->getObjectHandle());
                    if (lso != nullptr)
                        scriptHandles.push_back(lso->getScriptHandle());
                }
            }
        }

        if (it->getScriptType() == sim_scripttype_customization)
        { // we have a customization script
            CSceneObject* obj = App::currentWorld->sceneObjects->getObjectFromHandle(
                it->getObjectHandleThatScriptIsAttachedTo(sim_scripttype_customization));
            if (obj != nullptr)
            { // should always pass
                if (selfIncluded)
                {
                    CScriptObject* aScript = App::currentWorld->sceneObjects->embeddedScriptContainer->getScriptFromObjectAttachedTo(
                        sim_scripttype_simulation, obj->getObjectHandle());
                    if (aScript != nullptr)
                        scriptHandles.push_back(aScript->getScriptHandle());
                }

                std::vector<CSceneObject*> objList;
                obj->getAllObjectsRecursive(&objList, false);
                for (int i = 0; i < int(objList.size()); i++)
                {
                    CScriptObject* lso = App::currentWorld->sceneObjects->embeddedScriptContainer->getScriptFromObjectAttachedTo(
                        sim_scripttype_simulation, objList[i]->getObjectHandle());
                    if (lso != nullptr)
                    {
                        scriptHandles.push_back(lso->getScriptHandle());
                    }
                }
            }
        }
    }
}

void getScriptChain_old(luaWrap_lua_State* L, bool selfIncluded, bool mainIncluded, std::vector<int>& scriptHandles)
{ // Returns all script IDs that are parents (or grand-parents,grand-grand-parents, etc.) of the current one
    scriptHandles.clear();
    int currentScriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);

    CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(currentScriptID);

    if (it != nullptr)
    {
        if (it->getScriptType() == sim_scripttype_main)
        { // we have a main script here
            if (selfIncluded && mainIncluded)
                scriptHandles.push_back(currentScriptID);
        }

        if (it->getScriptType() == sim_scripttype_simulation)
        { // we have a simulation script here
            CSceneObject* obj = App::currentWorld->sceneObjects->getObjectFromHandle(
                it->getObjectHandleThatScriptIsAttachedTo(sim_scripttype_simulation));
            if (obj != nullptr)
            {
                if (selfIncluded)
                    scriptHandles.push_back(currentScriptID);
                while (obj->getParent() != nullptr)
                {
                    obj = obj->getParent();
                    CScriptObject* lso = App::currentWorld->sceneObjects->embeddedScriptContainer->getScriptFromObjectAttachedTo(
                        sim_scripttype_simulation, obj->getObjectHandle());
                    if (lso != nullptr)
                        scriptHandles.push_back(lso->getScriptHandle());
                }
                if (mainIncluded)
                {
                    CScriptObject* lso = App::currentWorld->sceneObjects->embeddedScriptContainer->getMainScript();
                    if (lso != nullptr)
                        scriptHandles.push_back(lso->getScriptHandle());
                }
            }
        }

        if (it->getScriptType() == sim_scripttype_customization)
        { // we have a customization script here
            CSceneObject* obj = App::currentWorld->sceneObjects->getObjectFromHandle(
                it->getObjectHandleThatScriptIsAttachedTo(sim_scripttype_customization));
            if (obj != nullptr)
            {
                if (selfIncluded)
                {
                    CScriptObject* aScript = App::currentWorld->sceneObjects->embeddedScriptContainer->getScriptFromObjectAttachedTo(
                        sim_scripttype_simulation, obj->getObjectHandle());
                    if (aScript != nullptr)
                        scriptHandles.push_back(aScript->getScriptHandle());
                }
                while (obj->getParent() != nullptr)
                {
                    obj = obj->getParent();
                    CScriptObject* lso = App::currentWorld->sceneObjects->embeddedScriptContainer->getScriptFromObjectAttachedTo(
                        sim_scripttype_simulation, obj->getObjectHandle());
                    if (lso != nullptr)
                        scriptHandles.push_back(lso->getScriptHandle());
                }
                if (mainIncluded)
                {
                    CScriptObject* lso = App::currentWorld->sceneObjects->embeddedScriptContainer->getMainScript();
                    if (lso != nullptr)
                        scriptHandles.push_back(lso->getScriptHandle());
                }
            }
        }
    }
}
bool readCustomFunctionDataFromStack_old(luaWrap_lua_State* L, int ind, int dataType, std::vector<char>& inBoolVector,
                                         std::vector<int>& inIntVector, std::vector<float>& inFloatVector,
                                         std::vector<double>& inDoubleVector, std::vector<std::string>& inStringVector,
                                         std::vector<std::string>& inCharVector, std::vector<int>& inInfoVector)
{ // return value false means there is no more data on the stack
    if (luaWrap_lua_gettop(L) < ind)
        return (false);                             // not enough data on the stack
    inInfoVector.push_back(sim_script_arg_invalid); // Dummy value for type
    inInfoVector.push_back(0);                      // dummy value for size
    if (luaWrap_lua_isnil(L, ind))
    { // Special case: nil should not generate a sim_script_arg_invalid type!
        inInfoVector[inInfoVector.size() - 2] = sim_script_arg_null;
        return (true);
    }
    if (dataType & sim_script_arg_table)
    { // we have to read a table:
        dataType ^= sim_script_arg_table;
        if (!luaWrap_lua_isnonbuffertable(L, ind))
            return (true); // this is not a table
        int dataSize = int(luaWrap_lua_rawlen(L, ind));
        std::vector<char> boolV;
        std::vector<int> intV;
        std::vector<float> floatV;
        std::vector<double> doubleV;
        std::vector<std::string> stringV;
        for (int i = 0; i < dataSize; i++)
        {
            luaWrap_lua_rawgeti(L, ind, i + 1);
            if (dataType == sim_script_arg_bool)
            {
                if (!luaWrap_lua_isboolean(L, -1))
                {
                    luaWrap_lua_pop(L, 1); // we have to pop the value that was pushed with luaWrap_lua_rawgeti
                    return (true);         // we don't have the correct data type
                }
                boolV.push_back(luaToBool(L, -1));
            }
            else if (dataType == sim_script_arg_int32)
            {
                if (!luaWrap_lua_isnumber(L, -1))
                {
                    luaWrap_lua_pop(L, 1); // we have to pop the value that was pushed with luaWrap_lua_rawgeti
                    return (true);         // we don't have the correct data type
                }
                intV.push_back(luaToInt(L, -1));
            }
            else if (dataType == sim_script_arg_float)
            {
                if (!luaWrap_lua_isnumber(L, -1))
                {
                    luaWrap_lua_pop(L, 1); // we have to pop the value that was pushed with luaWrap_lua_rawgeti
                    return (true);         // we don't have the correct data type
                }
                floatV.push_back(luaToDouble(L, -1));
            }
            else if (dataType == sim_script_arg_double)
            {
                if (!luaWrap_lua_isnumber(L, -1))
                {
                    luaWrap_lua_pop(L, 1); // we have to pop the value that was pushed with luaWrap_lua_rawgeti
                    return (true);         // we don't have the correct data type
                }
                doubleV.push_back(luaToDouble(L, -1));
            }
            else if (dataType == sim_script_arg_string)
            {
                if (!luaWrap_lua_isstring(L, -1))
                {
                    luaWrap_lua_pop(L, 1); // we have to pop the value that was pushed with luaWrap_lua_rawgeti
                    return (true);         // we don't have the correct data type
                }
                stringV.push_back(std::string(luaWrap_lua_tostring(L, -1)));
            }
            else
            {
                luaWrap_lua_pop(L, 1); // we have to pop the value that was pushed with luaWrap_lua_rawgeti
                return (true);         // data type not recognized!
            }
            luaWrap_lua_pop(L, 1); // we have to pop the value that was pushed with luaWrap_lua_rawgeti
        }
        // All values in the tables passed the check!
        for (int i = 0; i < int(boolV.size()); i++)
            inBoolVector.push_back(boolV[i]);
        for (int i = 0; i < int(intV.size()); i++)
            inIntVector.push_back(intV[i]);
        for (int i = 0; i < int(floatV.size()); i++)
            inFloatVector.push_back(floatV[i]);
        for (int i = 0; i < int(doubleV.size()); i++)
            inDoubleVector.push_back(doubleV[i]);
        for (int i = 0; i < int(stringV.size()); i++)
            inStringVector.push_back(stringV[i]);
        inInfoVector[inInfoVector.size() - 1] = dataSize;                        // Size of the table
        inInfoVector[inInfoVector.size() - 2] = dataType | sim_script_arg_table; // Type
        return (true);
    }
    else
    { // we have simple data here (not a table)
        if (dataType == sim_script_arg_bool)
        {
            if (!luaWrap_lua_isboolean(L, ind))
                return (true); // we don't have the correct data type
            inBoolVector.push_back(luaToBool(L, ind));
            inInfoVector[inInfoVector.size() - 2] = dataType;
        }
        else if (dataType == sim_script_arg_int32)
        {
            if (!luaWrap_lua_isnumber(L, ind))
                return (true); // we don't have the correct data type
            inIntVector.push_back(luaToInt(L, ind));
            inInfoVector[inInfoVector.size() - 2] = dataType;
        }
        else if (dataType == sim_script_arg_float)
        {
            if (!luaWrap_lua_isnumber(L, ind))
                return (true); // we don't have the correct data type
            inFloatVector.push_back(luaToDouble(L, ind));
            inInfoVector[inInfoVector.size() - 2] = dataType;
        }
        else if (dataType == sim_script_arg_double)
        {
            if (!luaWrap_lua_isnumber(L, ind))
                return (true); // we don't have the correct data type
            inDoubleVector.push_back(luaToDouble(L, ind));
            inInfoVector[inInfoVector.size() - 2] = dataType;
        }
        else if (dataType == sim_script_arg_string)
        {
            if (!luaWrap_lua_isstring(L, ind))
                return (true); // we don't have the correct data type
            inStringVector.push_back(std::string(luaWrap_lua_tostring(L, ind)));
            inInfoVector[inInfoVector.size() - 2] = dataType;
        }
        else if (dataType == sim_script_arg_charbuff)
        {
            if (!luaWrap_lua_isstring(L, ind))
                return (true); // we don't have the correct data type
            size_t dataLength;
            char* data = (char*)luaWrap_lua_tobuffer(L, ind, &dataLength);
            inCharVector.push_back(std::string(data, dataLength));
            inInfoVector[inInfoVector.size() - 2] = dataType;
            inInfoVector[inInfoVector.size() - 1] = int(dataLength);
        }
        return (true); // data type not recognized!
    }
    return (true);
}

void writeCustomFunctionDataOntoStack_old(luaWrap_lua_State* L, int dataType, int dataSize, bool* boolData,
                                          int& boolDataPos, int* intData, int& intDataPos, float* floatData,
                                          int& floatDataPos, double* doubleData, int& doubleDataPos, char* stringData,
                                          int& stringDataPos, char* charData, int& charDataPos)
{
    if (((dataType | sim_script_arg_table) - sim_script_arg_table) == sim_script_arg_charbuff)
    {                                                                      // special handling here
        luaWrap_lua_pushbinarystring(L, charData + charDataPos, dataSize); // push binary string for backw. comp.
        charDataPos += dataSize;
    }
    else
    {
        int newTablePos = 0;
        bool weHaveATable = false;
        if (dataType & sim_script_arg_table)
        { // we have a table
            luaWrap_lua_newtable(L);
            newTablePos = luaWrap_lua_gettop(L);
            dataType ^= sim_script_arg_table;
            weHaveATable = true;
        }
        else
            dataSize = 1;
        for (int i = 0; i < dataSize; i++)
        {
            if (dataType == sim_script_arg_bool)
                luaWrap_lua_pushboolean(L, boolData[boolDataPos++]);
            else if (dataType == sim_script_arg_int32)
                luaWrap_lua_pushinteger(L, intData[intDataPos++]);
            else if (dataType == sim_script_arg_float)
                luaWrap_lua_pushnumber(L, floatData[floatDataPos++]);
            else if (dataType == sim_script_arg_double)
                luaWrap_lua_pushnumber(L, doubleData[doubleDataPos++]);
            else if (dataType == sim_script_arg_string)
            {
                luaWrap_lua_pushtext(L, stringData + stringDataPos);
                stringDataPos += (int)strlen(stringData + stringDataPos) +
                                 1; // Thanks to Ulrich Schwesinger for noticing a bug here!
            }
            else
                luaWrap_lua_pushnil(L); // that is an error!

            if (weHaveATable) // that's when we have a table
                luaWrap_lua_rawseti(L, newTablePos, i + 1);
        }
    }
}
int _simResetMill(luaWrap_lua_State* L)
{ // DEPRECATED since V4.0.1. has no effect anymore
    LUA_START("sim.ResetMill");
    LUA_END(0);
}

int _simHandleMill(luaWrap_lua_State* L)
{ // DEPRECATED since V4.0.1. has no effect anymore
    LUA_START("sim.HandleMill");
    LUA_END(0);
}

int _simResetMilling(luaWrap_lua_State* L)
{ // DEPRECATED since V4.0.1. has no effect anymore
    LUA_START("sim.ResetMilling");
    LUA_END(0);
}

int _simOpenTextEditor(luaWrap_lua_State* L)
{ // DEPRECATED since V3.6.0
    TRACE_LUA_API;
    LUA_START("sim.openTextEditor");

    if (checkInputArguments(L, &errorString, lua_arg_string, 0))
    {
        std::string initText(luaWrap_lua_tostring(L, 1));
        int res = checkOneGeneralInputArgument(L, 2, lua_arg_string, 0, true, true, &errorString);
        if (res >= 0)
        {
            std::string xml;
            const char* _xml = nullptr;
            if (res == 2)
            {
                xml = luaWrap_lua_tostring(L, 2);
                _xml = xml.c_str();
            }
            int res = checkOneGeneralInputArgument(L, 3, lua_arg_string, 0, true, true, &errorString);
            if (res != 2)
            { // Modal dlg
                int various[4];
                char* outText = simOpenTextEditor_internal(initText.c_str(), _xml, various);
                if (outText != nullptr)
                {
                    luaWrap_lua_pushtext(L, outText);
                    delete[] outText;
                    pushIntTableOntoStack(L, 2, various + 0);
                    pushIntTableOntoStack(L, 2, various + 2);
                    LUA_END(3);
                }
            }
            else
            { // non-modal dlg
                int handle = -1;
                CScriptObject* it =
                    App::worldContainer->getScriptObjectFromHandle(CScriptObject::getScriptHandleFromInterpreterState_lua(L));
                if (it != nullptr)
                {
                    std::string callbackFunction(luaWrap_lua_tostring(L, 3));
#ifdef SIM_WITH_GUI
                    if (GuiApp::mainWindow != nullptr)
                        handle = GuiApp::mainWindow->codeEditorContainer->openTextEditor_old(
                            initText.c_str(), xml.c_str(), callbackFunction.c_str(), it);
#endif
                }
                luaWrap_lua_pushinteger(L, handle);
                LUA_END(1);
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simCloseTextEditor(luaWrap_lua_State* L)
{ // DEPRECATED since V3.6.0
    TRACE_LUA_API;
    LUA_START("sim.closeTextEditor");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_bool, 0))
    {
        int h = luaToInt(L, 1);
        bool ignoreCb = luaToBool(L, 2);
        int res = 0;
        std::string txt;
        std::string cb;
        int posAndSize[4];
#ifdef SIM_WITH_GUI
        if (GuiApp::mainWindow != nullptr)
        {
            if (GuiApp::mainWindow->codeEditorContainer->close(h, posAndSize, &txt, &cb))
                res = 1;
        }
#endif
        if ((res > 0) && (!ignoreCb))
        { // We call the callback directly from here:
            CScriptObject* it =
                App::worldContainer->getScriptObjectFromHandle(CScriptObject::getScriptHandleFromInterpreterState_lua(L));
            if (it != nullptr)
            {
                CInterfaceStack* stack = App::worldContainer->interfaceStackContainer->createStack();
                stack->pushTextOntoStack(txt.c_str());
                stack->pushInt32ArrayOntoStack(posAndSize + 0, 2);
                stack->pushInt32ArrayOntoStack(posAndSize + 2, 2);
                it->callCustomScriptFunction(cb.c_str(), stack);
                App::worldContainer->interfaceStackContainer->destroyStack(stack);
            }
        }
        luaWrap_lua_pushinteger(L, res);
        LUA_END(1);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simHandleVarious(luaWrap_lua_State* L)
{ // DEPRECATED since V3.4.0
    TRACE_LUA_API;
    LUA_START("simHandleVarious");

    int retVal = simHandleVarious_internal();

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetMpConfigForTipPose(luaWrap_lua_State* L)
{ // DEPRECATED since V3.3.0
    TRACE_LUA_API;
    LUA_START("simGetMpConfigForTipPose");
    errorString = "not supported anymore.";
    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, -1);
    LUA_END(1);
}

int _simResetPath(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("simResetPath");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
        retVal = simResetPath_internal(luaToInt(L, 1));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simHandlePath(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("simHandlePath");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
        retVal = simHandlePath_internal(luaToInt(L, 1), luaToDouble(L, 2));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simResetJoint(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("simResetJoint");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
        retVal = simResetJoint_internal(luaToInt(L, 1));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simHandleJoint(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("simHandleJoint");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
        retVal = simHandleJoint_internal(luaToInt(L, 1), luaToDouble(L, 2));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simResetTracing(luaWrap_lua_State* L)
{ // deprecated
    TRACE_LUA_API;
    LUA_START("simResetTracing");

    warningString = SIM_ERROR_FUNCTION_DEPRECATED_AND_HAS_NO_EFFECT;

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simHandleTracing(luaWrap_lua_State* L)
{ // deprecated
    TRACE_LUA_API;
    LUA_START("simHandleTracing");

    warningString = SIM_ERROR_FUNCTION_DEPRECATED_AND_HAS_NO_EFFECT;

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

static int _nextMemHandle_old = 0;
static std::vector<int> _memHandles_old;
static std::vector<void*> _memBuffers_old;

typedef struct
{
    double accel;
    double vdl;
    double currentPos;
    double lastTime;
    double maxVelocity;
    double currentVel;
    C7Vector startTr;
    C7Vector targetTr;
    int objID;
    CSceneObject* object;
    int relativeToObjID;
    CSceneObject* relToObject;
    unsigned char posAndOrient;
} simMoveToPosData_old;

typedef struct
{
    double lastTime;
    bool sameTimeFinish;
    int maxVirtualDistIndex;
    double maxVelocity;
    double accel;
    std::vector<int> jointHandles;
    std::vector<double> jointCurrentVirtualPositions;
    std::vector<double> jointCurrentVirtualVelocities;
    std::vector<double> jointStartPositions;
    std::vector<double> jointTargetPositions;
    std::vector<double> jointVirtualDistances;
    std::vector<double> jointMaxVelocities;
    std::vector<double> jointAccels;
} simMoveToJointPosData_old;

int _sim_moveToPos_1(luaWrap_lua_State* L)
{ // for backward compatibility with simMoveToPosition on old threaded scripts
    TRACE_LUA_API;
    LUA_START("sim._moveToPos_1");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    { // Those are the arguments that are always required! (the rest can be ignored or set to nil!
        int objID = luaToInt(L, 1);
        int relativeToObjID = luaToInt(L, 2);
        double posTarget[3];
        double eulerTarget[3];
        double maxVelocity;
        CSceneObject* object = App::currentWorld->sceneObjects->getObjectFromHandle(objID);
        CSceneObject* relToObject = nullptr;
        double accel = 0.0;                                    // means infinite accel!! (default value)
        double angleToLinearCoeff = 0.1 / (90.0 * degToRad);   // (default value)
        int distCalcMethod = sim_distcalcmethod_dl_if_nonzero; // (default value)
        bool foundError = false;
        if ((!foundError) && (object == nullptr))
        {
            errorString = SIM_ERROR_OBJECT_INEXISTANT;
            foundError = true;
        }
        if ((!foundError) && (relativeToObjID == sim_handle_parent))
        {
            relativeToObjID = -1;
            CSceneObject* parent = object->getParent();
            if (parent != nullptr)
                relativeToObjID = parent->getObjectHandle();
        }
        if ((!foundError) && (relativeToObjID != -1))
        {
            relToObject = App::currentWorld->sceneObjects->getObjectFromHandle(relativeToObjID);
            if (relToObject == nullptr)
            { // error, object doesn't exist!
                errorString = SIM_ERROR_OBJECT_INEXISTANT;
                foundError = true;
            }
        }

        // Now check the optional arguments:
        int res;
        unsigned char posAndOrient = 0;
        if (!foundError) // position argument:
        {
            res = checkOneGeneralInputArgument(L, 3, lua_arg_number, 3, true, true, &errorString);
            if (res == 2)
            { // get the data
                getDoublesFromTable(L, 3, 3, posTarget);
                posAndOrient |= 1;
            }
            foundError = (res == -1);
        }
        if (!foundError) // orientation argument:
        {
            res = checkOneGeneralInputArgument(L, 4, lua_arg_number, 3, true, true, &errorString);
            if (res == 2)
            { // get the data
                getDoublesFromTable(L, 4, 3, eulerTarget);
                posAndOrient |= 2;
            }
            foundError = (res == -1);
        }
        if ((!foundError) && (posAndOrient == 0))
        {
            foundError = true;
            errorString = "target position and/or target orientation has to be specified.";
        }
        if (!foundError) // target velocity argument:
        {
            res = checkOneGeneralInputArgument(L, 5, lua_arg_number, 0, false, false, &errorString);
            if (res == 2)
            { // get the data
                maxVelocity = luaToDouble(L, 5);
            }
            else
                foundError = true;
        }
        if (!foundError) // Accel argument:
        {
            res = checkOneGeneralInputArgument(L, 6, lua_arg_number, 0, true, true, &errorString);
            if (res == 2)
            { // get the data
                accel = fabs(luaToDouble(L, 6));
            }
            foundError = (res == -1);
        }
        if (!foundError) // distance method:
        {
            res = checkOneGeneralInputArgument(L, 7, lua_arg_number, 2, true, true, &errorString);
            if (res == 2)
            { // get the data
                double tmpF[2];
                getDoublesFromTable(L, 7, 2, tmpF);
                angleToLinearCoeff = tmpF[1];
                getIntsFromTable(L, 7, 1, &distCalcMethod);
            }
            foundError = (res == -1);
        }
        if (!foundError)
        { // do the job here!
            C7Vector startTr(object->getCumulativeTransformation());
            C7Vector relTr;
            relTr.setIdentity();
            if (relToObject != nullptr)
                relTr = relToObject->getFullCumulativeTransformation();
            startTr = relTr.getInverse() * startTr;

            C7Vector targetTr(startTr);
            if (posAndOrient & 1)
                targetTr.X.setData(posTarget);
            if (posAndOrient & 2)
                targetTr.Q.setEulerAngles(eulerTarget[0], eulerTarget[1], eulerTarget[2]);
            double currentVel = 0.0;
            CVThreadData* threadData = CThreadPool_old::getCurrentThreadData();

            double dl = (targetTr.X - startTr.X).getLength();
            double da = targetTr.Q.getAngleBetweenQuaternions(startTr.Q) * angleToLinearCoeff;
            double vdl = dl;
            if (distCalcMethod == sim_distcalcmethod_dl)
                vdl = dl;
            if (distCalcMethod == sim_distcalcmethod_dac)
                vdl = da;
            if (distCalcMethod == sim_distcalcmethod_max_dl_dac)
                vdl = std::max<double>(dl, da);
            if (distCalcMethod == sim_distcalcmethod_dl_and_dac)
                vdl = dl + da;
            if (distCalcMethod == sim_distcalcmethod_sqrt_dl2_and_dac2)
                vdl = sqrt(dl * dl + da * da);
            if (distCalcMethod == sim_distcalcmethod_dl_if_nonzero)
            {
                vdl = dl;
                if (dl < 0.00005) // Was dl==0.0 before (tolerance problem). Changed on 1/4/2011
                    vdl = da;
            }
            if (distCalcMethod == sim_distcalcmethod_dac_if_nonzero)
            {
                vdl = da;
                if (da < 0.01 * degToRad) // Was da==0.0 before (tolerance problem). Changed on 1/4/2011
                    vdl = dl;
            }
            // vld is the totalvirtual distance
            double currentPos = 0.0;
            bool movementFinished = false;

            if (vdl == 0.0)
            { // if the path length is 0 (the two positions might still be not-coincident, depending on the calculation
                // method!)
                if (App::currentWorld->sceneObjects->getObjectFromHandle(objID) ==
                    object) // make sure the object is still valid (running in a thread)
                {
                    if (relToObject == nullptr)
                    { // absolute
                        C7Vector parentInv(object->getFullParentCumulativeTransformation().getInverse());
                        object->setLocalTransformation(parentInv * targetTr);
                    }
                    else
                    { // relative to a specific object (2009/11/17)
                        if (App::currentWorld->sceneObjects->getObjectFromHandle(relativeToObjID) ==
                            relToObject) // make sure the object is still valid (running in a thread)
                        {                // ok
                            C7Vector relToTr(relToObject->getFullCumulativeTransformation());
                            targetTr = relToTr * targetTr;
                            C7Vector parentInv(object->getFullParentCumulativeTransformation().getInverse());
                            object->setLocalTransformation(parentInv * targetTr);
                        }
                    }
                }
                movementFinished = true;
            }

            if (movementFinished)
                luaWrap_lua_pushinteger(L, -1);
            else
            {
                _memHandles_old.push_back(_nextMemHandle_old);
                simMoveToPosData_old* mem = new simMoveToPosData_old();
                mem->accel = accel;
                mem->vdl = vdl;
                mem->currentPos = currentPos;
                mem->lastTime = App::currentWorld->simulation->getSimulationTime();
                mem->maxVelocity = maxVelocity;
                mem->currentVel = currentVel;
                mem->startTr = startTr;
                mem->targetTr = targetTr;
                mem->objID = objID;
                mem->object = object;
                mem->relativeToObjID = relativeToObjID;
                mem->relToObject = relToObject;
                mem->posAndOrient = posAndOrient;

                _memBuffers_old.push_back(mem);
                luaWrap_lua_pushinteger(L, _nextMemHandle_old);
                _nextMemHandle_old++;
            }
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED();
    LUA_END(0);
}

int _sim_moveToPos_2(luaWrap_lua_State* L)
{ // for backward compatibility with simMoveToPosition on old threaded scripts
    TRACE_LUA_API;
    LUA_START("sim._moveToPos_2");
    if (checkInputArguments(L, &errorString, lua_arg_integer, 0))
    {
        int h = luaToInt(L, 1);
        simMoveToPosData_old* mem = nullptr;
        for (size_t i = 0; i < _memHandles_old.size(); i++)
        {
            if (_memHandles_old[i] == h)
            {
                mem = (simMoveToPosData_old*)_memBuffers_old[i];
                break;
            }
        }
        if (mem != nullptr)
        {
            bool err = false;
            bool movementFinished = false;
            double currentTime =
                App::currentWorld->simulation->getSimulationTime() + App::currentWorld->simulation->getTimeStep();
            double dt = currentTime - mem->lastTime;
            mem->lastTime = currentTime;

            if (mem->accel == 0.0)
            { // Means infinite acceleration
                double timeNeeded = (mem->vdl - mem->currentPos) / mem->maxVelocity;
                mem->currentVel = mem->maxVelocity;
                if (timeNeeded > dt)
                {
                    mem->currentPos += dt * mem->maxVelocity;
                    dt = 0.0; // this is what is left
                }
                else
                {
                    mem->currentPos = mem->vdl;
                    if (timeNeeded >= 0.0)
                        dt -= timeNeeded;
                }
            }
            else
            {
                double p = mem->currentPos;
                double v = mem->currentVel;
                double t = dt;
                CLinMotionRoutines::getNextValues(p, v, mem->maxVelocity, mem->accel, 0.0, mem->vdl, 0.0, 0.0, t);
                mem->currentPos = double(p);
                mem->currentVel = double(v);
                dt = double(t);
            }

            // Now check if we are within tolerances:
            if (fabs(mem->currentPos - mem->vdl) <= 0.00001) // tol[0])
                movementFinished = true;

            // Set the new configuration of the object:
            double ll = mem->currentPos / mem->vdl;
            if (ll > 1.0)
                ll = 1.0;
            C7Vector newAbs;
            newAbs.buildInterpolation(mem->startTr, mem->targetTr, ll);
            if (App::currentWorld->sceneObjects->getObjectFromHandle(mem->objID) ==
                mem->object) // make sure the object is still valid (running in a thread)
            {
                if ((mem->relToObject != nullptr) &&
                    (App::currentWorld->sceneObjects->getObjectFromHandle(mem->relativeToObjID) != mem->relToObject))
                    movementFinished = true; // the object was destroyed during execution of the command!
                else
                {
                    C7Vector parentInv(mem->object->getFullParentCumulativeTransformation().getInverse());
                    C7Vector currAbs(mem->object->getCumulativeTransformation());
                    C7Vector relToTr;
                    relToTr.setIdentity();
                    if (mem->relToObject != nullptr)
                        relToTr = mem->relToObject->getFullCumulativeTransformation();
                    currAbs = relToTr.getInverse() * currAbs;
                    if ((mem->posAndOrient & 1) == 0)
                        newAbs.X = currAbs.X;
                    if ((mem->posAndOrient & 2) == 0)
                        newAbs.Q = currAbs.Q;
                    newAbs = relToTr * newAbs;
                    mem->object->setLocalTransformation(parentInv * newAbs);
                }
            }
            else
                movementFinished = true; // the object was destroyed during execution of the command!

            if (!movementFinished)
            {
                luaWrap_lua_pushinteger(L, 0); // mov. not yet finished
                LUA_END(1);
            }
            if (!err)
            {
                luaWrap_lua_pushinteger(L, 1); // mov. finished
                luaWrap_lua_pushnumber(L, dt); // success (deltaTime left)
                LUA_END(2);
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED();
    LUA_END(0);
}

int _sim_del(luaWrap_lua_State* L)
{ // for backward compatibility with simMoveToPosition on old threaded scripts
    TRACE_LUA_API;
    LUA_START("sim._del");
    if (checkInputArguments(L, &errorString, lua_arg_integer, 0))
    {
        int h = luaToInt(L, 1);
        for (size_t i = 0; i < _memHandles_old.size(); i++)
        {
            if (_memHandles_old[i] == h)
            {
                delete _memBuffers_old[i];
                _memHandles_old.erase(_memHandles_old.begin() + i);
                _memBuffers_old.erase(_memBuffers_old.begin() + i);
                break;
            }
        }
    }
    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED();
    LUA_END(0);
}

int _sim_moveToJointPos_1(luaWrap_lua_State* L)
{ // for backward compatibility with simMoveToJointPositions on old threaded scripts
    TRACE_LUA_API;
    LUA_START("sim._moveToJointPos_1");
    if (!((!luaWrap_lua_isnonbuffertable(L, 1)) || (!luaWrap_lua_isnonbuffertable(L, 2)) ||
          (luaWrap_lua_rawlen(L, 1) > luaWrap_lua_rawlen(L, 2)) || (luaWrap_lua_rawlen(L, 1) == 0)))
    { // Ok we have 2 tables with same sizes.
        int tableLen = (int)luaWrap_lua_rawlen(L, 1);
        bool sameTimeFinish = true;
        double maxVelocity = 0.0;
        double accel = 0.0; // means infinite accel!! (default value)
        bool accelTablePresent = false;
        double angleToLinearCoeff = 1.0;
        bool foundError = false;
        // Now check the other arguments:
        int res;
        if (luaWrap_lua_isnonbuffertable(L, 3))
            sameTimeFinish = false; // we do not finish at the same time!
        if (!foundError)            // velocity or velocities argument (not optional!):
        {
            if (sameTimeFinish)
            {
                res = checkOneGeneralInputArgument(L, 3, lua_arg_number, 0, false, false, &errorString);
                if (res == 2)
                    maxVelocity = luaToDouble(L, 3);
                else
                    foundError = true;
            }
            else
            {
                res = checkOneGeneralInputArgument(L, 3, lua_arg_number, tableLen, false, false, &errorString);
                if (res != 2)
                    foundError = true;
            }
        }
        if (!foundError) // Accel argument:
        {
            if (sameTimeFinish)
            {
                res = checkOneGeneralInputArgument(L, 4, lua_arg_number, 0, true, true, &errorString);
                if (res == 2)
                { // get the data
                    accel = fabs(luaToDouble(L, 4));
                }
                foundError = (res == -1);
            }
            else
            {
                res = checkOneGeneralInputArgument(L, 4, lua_arg_number, tableLen, true, true, &errorString);
                if (res == 2)
                    accelTablePresent = true;
                foundError = (res == -1);
            }
        }
        if (!foundError) // angleToLinearCoeff argument:
        {
            if (sameTimeFinish)
            {
                res = checkOneGeneralInputArgument(L, 5, lua_arg_number, 0, true, true, &errorString);
                if (res == 2)
                { // get the data
                    angleToLinearCoeff = fabs(luaToDouble(L, 5));
                }
                foundError = (res == -1);
            }
            else
                angleToLinearCoeff = 1.0; // no conversion!
        }
        if (!foundError)
        { // do the job here!
            std::vector<int> jointHandles;
            jointHandles.resize(tableLen);
            std::vector<double> jointCurrentVirtualPositions;
            jointCurrentVirtualPositions.resize(tableLen);
            std::vector<double> jointCurrentVirtualVelocities;
            jointCurrentVirtualVelocities.resize(tableLen);
            std::vector<double> jointStartPositions;
            jointStartPositions.resize(tableLen);
            std::vector<double> jointTargetPositions;
            jointTargetPositions.resize(tableLen);
            std::vector<double> jointVirtualDistances;
            jointVirtualDistances.resize(tableLen);
            std::vector<double> jointMaxVelocities;
            jointMaxVelocities.resize(tableLen);
            std::vector<double> jointAccels;
            jointAccels.resize(tableLen);

            getIntsFromTable(L, 1, tableLen, &jointHandles[0]);
            getDoublesFromTable(L, 2, tableLen, &jointTargetPositions[0]);
            if (!sameTimeFinish)
            {
                getDoublesFromTable(L, 3, tableLen, &jointMaxVelocities[0]);
                for (int i = 0; i < tableLen; i++)
                    jointMaxVelocities[i] = fabs(jointMaxVelocities[i]);
                if (accelTablePresent)
                {
                    getDoublesFromTable(L, 4, tableLen, &jointAccels[0]);
                    for (int i = 0; i < tableLen; i++)
                        jointAccels[i] = fabs(jointAccels[i]);
                }
            }
            double maxVirtualDist = 0.0;
            int maxVirtualDistIndex = 0;
            for (int i = 0; i < tableLen; i++)
            {
                jointCurrentVirtualPositions[i] = 0.0;
                jointCurrentVirtualVelocities[i] = 0.0;
                if (sameTimeFinish)
                    jointMaxVelocities[i] = maxVelocity;
                if (!accelTablePresent)
                    jointAccels[i] = accel;

                CJoint* it = App::currentWorld->sceneObjects->getJointFromHandle(jointHandles[i]);
                if ((it != nullptr) && (it->getJointType() != sim_joint_spherical))
                { // make sure target is within allowed range, and check the maximum virtual distance:
                    jointStartPositions[i] = it->getPosition();
                    double minP, maxP;
                    it->getInterval(minP, maxP);
                    if (it->getIsCyclic())
                    {
                        double da = tt::getAngleMinusAlpha(jointTargetPositions[i], jointStartPositions[i]);
                        jointTargetPositions[i] = jointStartPositions[i] + da;
                    }
                    else
                    {
                        if (minP > jointTargetPositions[i])
                            jointTargetPositions[i] = minP;
                        if (maxP < jointTargetPositions[i])
                            jointTargetPositions[i] = maxP;
                    }
                    double d = fabs(jointTargetPositions[i] - jointStartPositions[i]);
                    if (it->getJointType() == sim_joint_revolute)
                        d *= angleToLinearCoeff;
                    jointVirtualDistances[i] = d;
                    if (d > maxVirtualDist)
                    {
                        maxVirtualDist = d;
                        maxVirtualDistIndex = i;
                    }
                }
                else
                {
                    // Following are default values in case the joint doesn't exist or is spherical:
                    jointStartPositions[i] = 0.0;
                    jointTargetPositions[i] = 0.0;
                    jointVirtualDistances[i] = 0.0;
                }
            }
            double lastTime = App::currentWorld->simulation->getSimulationTime();
            bool movementFinished = false;
            double dt = App::currentWorld->simulation->getTimeStep(); // this is the time left if we leave here

            if (maxVirtualDist == 0.0)
                luaWrap_lua_pushinteger(L, -1);
            else
            {
                _memHandles_old.push_back(_nextMemHandle_old);
                simMoveToJointPosData_old* mem = new simMoveToJointPosData_old();
                mem->lastTime = lastTime;
                mem->sameTimeFinish = sameTimeFinish;
                mem->maxVirtualDistIndex = maxVirtualDistIndex;
                mem->maxVelocity = maxVelocity;
                mem->accel = accel;
                mem->jointHandles.assign(jointHandles.begin(), jointHandles.end());
                mem->jointCurrentVirtualPositions.assign(jointCurrentVirtualPositions.begin(),
                                                         jointCurrentVirtualPositions.end());
                mem->jointCurrentVirtualVelocities.assign(jointCurrentVirtualVelocities.begin(),
                                                          jointCurrentVirtualVelocities.end());
                mem->jointStartPositions.assign(jointStartPositions.begin(), jointStartPositions.end());
                mem->jointTargetPositions.assign(jointTargetPositions.begin(), jointTargetPositions.end());
                mem->jointVirtualDistances.assign(jointVirtualDistances.begin(), jointVirtualDistances.end());
                mem->jointMaxVelocities.assign(jointMaxVelocities.begin(), jointMaxVelocities.end());
                mem->jointAccels.assign(jointAccels.begin(), jointAccels.end());

                _memBuffers_old.push_back(mem);
                luaWrap_lua_pushinteger(L, _nextMemHandle_old);
                _nextMemHandle_old++;
            }
            LUA_END(1);
        }
    }
    else
        errorString = "one of the function's argument type is not correct or table sizes are invalid or do not match";

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _sim_moveToJointPos_2(luaWrap_lua_State* L)
{ // for backward compatibility with simMoveToJointPositions on old threaded scripts
    TRACE_LUA_API;
    LUA_START("sim._moveToJointPos_2");

    if (checkInputArguments(L, &errorString, lua_arg_integer, 0))
    {
        int h = luaToInt(L, 1);
        simMoveToJointPosData_old* mem = nullptr;
        for (size_t i = 0; i < _memHandles_old.size(); i++)
        {
            if (_memHandles_old[i] == h)
            {
                mem = (simMoveToJointPosData_old*)_memBuffers_old[i];
                break;
            }
        }
        if (mem != nullptr)
        {
            int tableLen = int(mem->jointHandles.size());
            bool err = false;
            bool movementFinished = false;
            double currentTime =
                App::currentWorld->simulation->getSimulationTime() + App::currentWorld->simulation->getTimeStep();
            double dt = currentTime - mem->lastTime;
            double minTimeLeft = dt;
            mem->lastTime = currentTime;
            if (mem->sameTimeFinish)
            {
                double timeLeftLocal = dt;
                // 1. handle the joint with longest distance first:
                // Does the main joint still exist?
                if (App::currentWorld->sceneObjects->getJointFromHandle(mem->jointHandles[mem->maxVirtualDistIndex]) !=
                    nullptr)
                {
                    if (mem->accel == 0.0)
                    { // means infinite accel
                        double timeNeeded = (mem->jointVirtualDistances[mem->maxVirtualDistIndex] -
                                             mem->jointCurrentVirtualPositions[mem->maxVirtualDistIndex]) /
                                            mem->maxVelocity;
                        mem->jointCurrentVirtualVelocities[mem->maxVirtualDistIndex] = mem->maxVelocity;
                        if (timeNeeded > timeLeftLocal)
                        {
                            mem->jointCurrentVirtualPositions[mem->maxVirtualDistIndex] +=
                                timeLeftLocal * mem->maxVelocity;
                            timeLeftLocal = 0.0; // this is what is left
                        }
                        else
                        {
                            mem->jointCurrentVirtualPositions[mem->maxVirtualDistIndex] =
                                mem->jointVirtualDistances[mem->maxVirtualDistIndex];
                            if (timeNeeded >= 0.0)
                                timeLeftLocal -= timeNeeded;
                        }
                    }
                    else
                    {
                        double p = mem->jointCurrentVirtualPositions[mem->maxVirtualDistIndex];
                        double v = mem->jointCurrentVirtualVelocities[mem->maxVirtualDistIndex];
                        double t = timeLeftLocal;
                        CLinMotionRoutines::getNextValues(p, v, mem->maxVelocity, mem->accel, 0.0,
                                                          mem->jointVirtualDistances[mem->maxVirtualDistIndex], 0.0,
                                                          0.0, t);
                        mem->jointCurrentVirtualPositions[mem->maxVirtualDistIndex] = double(p);
                        mem->jointCurrentVirtualVelocities[mem->maxVirtualDistIndex] = double(v);
                        timeLeftLocal = double(t);
                    }
                    minTimeLeft = timeLeftLocal;
                    // 2. We adjust the other joints accordingly:
                    double f = 1;
                    if (mem->jointVirtualDistances[mem->maxVirtualDistIndex] != 0.0)
                        f = mem->jointCurrentVirtualPositions[mem->maxVirtualDistIndex] /
                            mem->jointVirtualDistances[mem->maxVirtualDistIndex];
                    for (int i = 0; i < tableLen; i++)
                    {
                        if (i != mem->maxVirtualDistIndex)
                            mem->jointCurrentVirtualPositions[i] = mem->jointVirtualDistances[i] * f;
                    }
                    // 3. Check if within tolerance:
                    if (fabs(mem->jointCurrentVirtualPositions[mem->maxVirtualDistIndex] -
                             mem->jointVirtualDistances[mem->maxVirtualDistIndex]) <= 0.00001)
                        movementFinished = true;
                }
                else
                { // the main joint was removed. End here!
                    movementFinished = true;
                }
            }
            else
            {
                bool withinTolerance = true;
                for (int i = 0; i < tableLen; i++)
                {
                    if (App::currentWorld->sceneObjects->getJointFromHandle(mem->jointHandles[i]) != nullptr)
                    {
                        // Check if within tolerance (before):
                        if (fabs(mem->jointCurrentVirtualPositions[i] - mem->jointVirtualDistances[i]) > 0.00001)
                        {
                            double timeLeftLocal = dt;
                            if (mem->jointAccels[i] == 0.0)
                            { // means infinite accel
                                double timeNeeded =
                                    (mem->jointVirtualDistances[i] - mem->jointCurrentVirtualPositions[i]) /
                                    mem->jointMaxVelocities[i];
                                mem->jointCurrentVirtualVelocities[i] = mem->jointMaxVelocities[i];
                                if (timeNeeded > timeLeftLocal)
                                {
                                    mem->jointCurrentVirtualPositions[i] += timeLeftLocal * mem->jointMaxVelocities[i];
                                    timeLeftLocal = 0.0; // this is what is left
                                }
                                else
                                {
                                    mem->jointCurrentVirtualPositions[i] = mem->jointVirtualDistances[i];
                                    if (timeNeeded >= 0.0)
                                        timeLeftLocal -= timeNeeded;
                                }
                            }
                            else
                            {
                                double p = mem->jointCurrentVirtualPositions[i];
                                double v = mem->jointCurrentVirtualVelocities[i];
                                double t = timeLeftLocal;
                                CLinMotionRoutines::getNextValues(p, v, mem->jointMaxVelocities[i], mem->jointAccels[i],
                                                                  0.0, mem->jointVirtualDistances[i], 0.0, 0.0, t);
                                mem->jointCurrentVirtualPositions[i] = double(p);
                                mem->jointCurrentVirtualVelocities[i] = double(v);
                                timeLeftLocal = double(t);
                            }
                            if (timeLeftLocal < minTimeLeft)
                                minTimeLeft = timeLeftLocal;
                            // Check if within tolerance (after):
                            if (fabs(mem->jointCurrentVirtualPositions[i] - mem->jointVirtualDistances[i]) > 0.00001)
                                withinTolerance = false;
                        }
                    }
                }
                if (withinTolerance)
                    movementFinished = true;
            }
            dt = minTimeLeft;

            // We set all joint positions:
            for (int i = 0; i < tableLen; i++)
            {
                CJoint* joint = App::currentWorld->sceneObjects->getJointFromHandle(mem->jointHandles[i]);
                if ((joint != nullptr) && (joint->getJointType() != sim_joint_spherical) &&
                    (mem->jointVirtualDistances[i] != 0.0))
                {
                    joint->setTargetPosition(mem->jointStartPositions[i] +
                                             (mem->jointTargetPositions[i] - mem->jointStartPositions[i]) *
                                                 mem->jointCurrentVirtualPositions[i] / mem->jointVirtualDistances[i]);
                    if (joint->getJointMode() == sim_jointmode_kinematic)
                        joint->setPosition(mem->jointStartPositions[i] +
                                           (mem->jointTargetPositions[i] - mem->jointStartPositions[i]) *
                                               mem->jointCurrentVirtualPositions[i] / mem->jointVirtualDistances[i]);
                }
            }

            if (!movementFinished)
            {
                luaWrap_lua_pushinteger(L, 0); // mov. not yet finished
                LUA_END(1);
            }
            if (!err)
            {
                luaWrap_lua_pushinteger(L, 1); // mov. finished
                luaWrap_lua_pushnumber(L, dt); // success (deltaTime left)
                LUA_END(2);
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simGetInstanceIndex(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("");

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, 0);
    LUA_END(1);
}

int _simGetVisibleInstanceIndex(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("");

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, 0);
    LUA_END(1);
}

int _simGetSystemTimeInMilliseconds(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("simGetSystemTimeInMilliseconds");

    int res = checkOneGeneralInputArgument(L, 1, lua_arg_number, 0, true, false, &errorString);
    if (res == 0)
    {
        luaWrap_lua_pushinteger(L, VDateTime::getTimeInMs());
        LUA_END(1);
    }
    if (res == 2)
    {
        int lastTime = luaToInt(L, 1);
        luaWrap_lua_pushinteger(L, VDateTime::getTimeDiffInMs(lastTime));
        LUA_END(1);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simLockInterface(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("simLockInterface");

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, -1);
    LUA_END(1);
}

int _simJointGetForce(luaWrap_lua_State* L)
{ // DEPRECATED since release 3.1.2
    TRACE_LUA_API;
    LUA_START("simJointGetForce");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        double jointF[1];
        if (simGetJointForce_internal(luaToInt(L, 1), jointF) > 0)
        {
            luaWrap_lua_pushnumber(L, jointF[0]);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simCopyPasteSelectedObjects(luaWrap_lua_State* L)
{ // DEPRECATED since release 3.1.3
    TRACE_LUA_API;
    LUA_START("simCopyPasteSelectedObjects");

    int retVal = simCopyPasteSelectedObjects_internal();

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simFindIkPath(luaWrap_lua_State* L)
{ // DEPRECATED since 3.3.0
    TRACE_LUA_API;
    LUA_START("simFindIkPath");
    errorString = "not supported anymore.";
    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simGetPathPlanningHandle(luaWrap_lua_State* L)
{ // DEPRECATED since 3.3.0
    TRACE_LUA_API;
    LUA_START("simGetPathPlanningHandle");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_string, 0))
    {
        std::string name(luaWrap_lua_tostring(L, 1));
        setCurrentScriptInfo_cSide(CScriptObject::getScriptHandleFromInterpreterState_lua(L),
                                   CScriptObject::getScriptNameIndexFromInterpreterState_lua_old(
                                       L)); // for transmitting to the master function additional info (e.g.for autom.
                                            // name adjustment, or for autom. object deletion when script ends)
        retVal = simGetPathPlanningHandle_internal(name.c_str());
        setCurrentScriptInfo_cSide(-1, -1);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSearchPath(luaWrap_lua_State* L)
{ // DEPRECATED since 3.3.0
    TRACE_LUA_API;
    LUA_START("simSearchPath");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int pathPlanningObjectHandle = luaToInt(L, 1);
        double maximumSearchTime = tt::getLimitedFloat(0.001, 36000.0, luaToDouble(L, 2));
        double subDt = 0.05; // 50 ms at a time (default)
        bool foundError = false;
        // Now check the optional argument:
        int res;
        if (!foundError) // sub-dt argument:
        {
            res = checkOneGeneralInputArgument(L, 3, lua_arg_number, 0, true, true, &errorString);
            if (res == 2)
            { // get the data
                subDt = tt::getLimitedFloat(0.001, std::min<double>(1.0, maximumSearchTime), luaToDouble(L, 3));
            }
            foundError = (res == -1);
        }
        if (!foundError)
        {
            CPathPlanningTask* it = App::currentWorld->pathPlanning_old->getObject(pathPlanningObjectHandle);
            if (it == nullptr)
                errorString = SIM_ERROR_PATH_PLANNING_OBJECT_INEXISTANT;
            else
            {
                retVal = 0;
                // if (VThread::isSimThread())
                { // non-threaded
                    if (it->performSearch(false, maximumSearchTime))
                        retVal = 1;
                }
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simInitializePathSearch(luaWrap_lua_State* L)
{ // DEPRECATED since 3.3.0
    TRACE_LUA_API;
    LUA_START("simInitializePathSearch");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0))
    {
        int pathPlanningObjectHandle = luaToInt(L, 1);
        double maximumSearchTime = luaToDouble(L, 2);
        double searchTimeStep = luaToDouble(L, 3);
        retVal = simInitializePathSearch_internal(pathPlanningObjectHandle, maximumSearchTime, searchTimeStep);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simPerformPathSearchStep(luaWrap_lua_State* L)
{ // DEPRECATED since 3.3.0
    TRACE_LUA_API;
    LUA_START("simPerformPathSearchStep");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_bool, 0))
    {
        int temporaryPathSearchObjectHandle = luaToInt(L, 1);
        bool abortSearch = luaToBool(L, 2);
        retVal = simPerformPathSearchStep_internal(temporaryPathSearchObjectHandle, abortSearch);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simEnableWorkThreads(luaWrap_lua_State* L)
{ // DEPRECATED since 3/4/2016
    TRACE_LUA_API;
    LUA_START("simEnableWorkThreads");
    luaWrap_lua_pushinteger(L, 0);
    LUA_END(1);
}

int _simWaitForWorkThreads(luaWrap_lua_State* L)
{ // DEPRECATED since 3/4/2016
    TRACE_LUA_API;
    LUA_START("simWaitForWorkThreads");
    LUA_END(0);
}

int _simGetInvertedMatrix(luaWrap_lua_State* L)
{ // DEPRECATED since 10/5/2016
    TRACE_LUA_API;
    LUA_START("simGetInvertedMatrix");

    if (checkInputArguments(L, &errorString, lua_arg_number, 12))
    {
        double arr[12];
        getDoublesFromTable(L, 1, 12, arr);
        simInvertMatrix_internal(arr);
        pushDoubleTableOntoStack(L, 12, arr);
        LUA_END(1);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simAddSceneCustomData(luaWrap_lua_State* L)
{ // DEPRECATED since 26/12/2016
    TRACE_LUA_API;
    LUA_START("simAddSceneCustomData");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_string, 0))
    {
        int headerNumber = luaToInt(L, 1);
        size_t dataLength;
        char* data = (char*)luaWrap_lua_tobuffer(L, 2, &dataLength);
        retVal = simAddSceneCustomData_internal(headerNumber, data, (int)dataLength);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetSceneCustomData(luaWrap_lua_State* L)
{ // DEPRECATED since 26/12/2016
    TRACE_LUA_API;
    LUA_START("simGetSceneCustomData");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int headerNumber = luaToInt(L, 1);
        int dataLength = simGetSceneCustomDataLength_internal(headerNumber);
        if (dataLength >= 0)
        {
            char* data = new char[dataLength];
            int retVal = simGetSceneCustomData_internal(headerNumber, data);
            if (retVal == -1)
                delete[] data;
            else
            {
                luaWrap_lua_pushbinarystring(L, data, dataLength); // push binary string for backw. comp.
                delete[] data;
                LUA_END(1);
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simAddObjectCustomData(luaWrap_lua_State* L)
{ // DEPRECATED since 26/12/2016
    TRACE_LUA_API;
    LUA_START("simAddObjectCustomData");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_string, 0))
    {
        int objectHandle = luaToInt(L, 1);
        int headerNumber = luaToInt(L, 2);
        size_t dataLength;
        char* data = (char*)luaWrap_lua_tobuffer(L, 3, &dataLength);
        retVal = simAddObjectCustomData_internal(objectHandle, headerNumber, data, (int)dataLength);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetObjectCustomData(luaWrap_lua_State* L)
{ // DEPRECATED since 26/12/2016
    TRACE_LUA_API;
    LUA_START("simGetObjectCustomData");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int objectHandle = luaToInt(L, 1);
        int headerNumber = luaToInt(L, 2);
        int dataLength = simGetObjectCustomDataLength_internal(objectHandle, headerNumber);
        if (dataLength >= 0)
        {
            char* data = new char[dataLength];
            int retVal = simGetObjectCustomData_internal(objectHandle, headerNumber, data);
            if (retVal == -1)
                delete[] data;
            else
            {
                luaWrap_lua_pushbinarystring(L, data, dataLength); // push binary string for backw. comp.
                delete[] data;
                LUA_END(1);
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simGetUIHandle(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simGetUIHandle");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_string, 0))
    {
        std::string name(luaWrap_lua_tostring(L, 1));
        setCurrentScriptInfo_cSide(CScriptObject::getScriptHandleFromInterpreterState_lua(L),
                                   CScriptObject::getScriptNameIndexFromInterpreterState_lua_old(
                                       L)); // for transmitting to the master function additional info (e.g.for autom.
                                            // name adjustment, or for autom. object deletion when script ends)
        retVal = simGetUIHandle_internal(name.c_str());
        setCurrentScriptInfo_cSide(-1, -1);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetUIProperty(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simGetUIProperty");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
        retVal = simGetUIProperty_internal(luaToInt(L, 1));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetUIEventButton(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simGetUIEventButton");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int auxVals[2];
        retVal = simGetUIEventButton_internal(luaToInt(L, 1), auxVals);
        luaWrap_lua_pushinteger(L, retVal);
        if (retVal == -1)
        {
            LUA_END(1);
        }
        pushIntTableOntoStack(L, 2, auxVals);
        LUA_END(2);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetUIProperty(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simSetUIProperty");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
        retVal = simSetUIProperty_internal(luaToInt(L, 1), luaToInt(L, 2));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetUIButtonSize(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simGetUIButtonSize");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int size[2];
        if (simGetUIButtonSize_internal(luaToInt(L, 1), luaToInt(L, 2), size) == 1)
        {
            pushIntTableOntoStack(L, 2, size);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simGetUIButtonProperty(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simGetUIButtonProperty");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
        retVal = simGetUIButtonProperty_internal(luaToInt(L, 1), luaToInt(L, 2));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetUIButtonProperty(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simSetUIButtonProperty");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0))
        retVal = simSetUIButtonProperty_internal(luaToInt(L, 1), luaToInt(L, 2), luaToInt(L, 3));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetUISlider(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simGetUISlider");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
        retVal = simGetUISlider_internal(luaToInt(L, 1), luaToInt(L, 2));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetUISlider(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simSetUISlider");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0))
        retVal = simSetUISlider_internal(luaToInt(L, 1), luaToInt(L, 2), luaToInt(L, 3));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetUIButtonLabel(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simSetUIButtonLabel");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        std::string stra;
        std::string strb;
        char* str1 = nullptr;
        char* str2 = nullptr;
        int res = checkOneGeneralInputArgument(L, 3, lua_arg_string, 0, false, true, &errorString);
        if (res != -1)
        {
            if (res == 2)
            {
                stra = luaWrap_lua_tostring(L, 3);
                str1 = (char*)stra.c_str();
            }
            res = checkOneGeneralInputArgument(L, 4, lua_arg_string, 0, true, true, &errorString);
            if (res != -1)
            {
                if (res == 2)
                {
                    strb = luaWrap_lua_tostring(L, 4);
                    str2 = (char*)strb.c_str();
                }
                retVal = simSetUIButtonLabel_internal(luaToInt(L, 1), luaToInt(L, 2), str1, str2);
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetUIButtonLabel(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simGetUIButtonLabel");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        char* label = simGetUIButtonLabel_internal(luaToInt(L, 1), luaToInt(L, 2));
        if (label != nullptr)
        {
            luaWrap_lua_pushtext(L, label);
            simReleaseBuffer_internal(label);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simCreateUIButtonArray(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simCreateUIButtonArray");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
        retVal = simCreateUIButtonArray_internal(luaToInt(L, 1), luaToInt(L, 2));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetUIButtonArrayColor(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simSetUIButtonArrayColor");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 2, lua_arg_number,
                            3))
    {
        int pos[2];
        float col[3];
        getIntsFromTable(L, 3, 2, pos);
        getFloatsFromTable(L, 4, 3, col);
        retVal = simSetUIButtonArrayColor_internal(luaToInt(L, 1), luaToInt(L, 2), pos, col);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simDeleteUIButtonArray(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simDeleteUIButtonArray");
    int retVal = -1; // error

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
        retVal = simDeleteUIButtonArray_internal(luaToInt(L, 1), luaToInt(L, 2));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simCreateUI(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simCreateUI");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_string, 0, lua_arg_number, 0, lua_arg_number, 2, lua_arg_number,
                            2))
    {
        int clientSize[2];
        int cellSize[2];
        getIntsFromTable(L, 3, 2, clientSize);
        getIntsFromTable(L, 4, 2, cellSize);
        int menuAttributes = luaToInt(L, 2);
        int b = 0;
        for (int i = 0; i < 8; i++)
        {
            if (menuAttributes & (1 << i))
                b++;
        }
        int* buttonHandles = new int[b];
        menuAttributes = (menuAttributes | sim_ui_menu_systemblock) - sim_ui_menu_systemblock;
        retVal = simCreateUI_internal(luaWrap_lua_tostring(L, 1), menuAttributes, clientSize, cellSize, buttonHandles);
        if (retVal != -1)
        {
            luaWrap_lua_pushinteger(L, retVal);
            pushIntTableOntoStack(L, b, buttonHandles);
            delete[] buttonHandles;
            LUA_END(2);
        }
        delete[] buttonHandles;
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simCreateUIButton(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simCreateUIButton");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 2, lua_arg_number, 2, lua_arg_number,
                            0))
    {
        int pos[2];
        int size[2];
        getIntsFromTable(L, 2, 2, pos);
        getIntsFromTable(L, 3, 2, size);
        retVal = simCreateUIButton_internal(luaToInt(L, 1), pos, size, luaToInt(L, 4));
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSaveUI(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simSaveUI");

    int retVal = -1; // error
    int res = checkOneGeneralInputArgument(L, 1, lua_arg_table, 1, false, true, &errorString);
    if (res > 0)
    {
        int res2 = checkOneGeneralInputArgument(L, 2, lua_arg_string, 0, false, false, &errorString);
        if (res2 == 2)
        {
            if (res == 1)
                retVal = simSaveUI_internal(0, nullptr, luaWrap_lua_tostring(L, 2));
            else
            {
                int tl = int(luaWrap_lua_rawlen(L, 1));
                int* tble = new int[tl];
                getIntsFromTable(L, 1, tl, tble);
                retVal = simSaveUI_internal(tl, tble, luaWrap_lua_tostring(L, 2));
                delete[] tble;
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simLoadUI(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simLoadUI");
    LUA_END(0);
}

int _simRemoveUI(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simRemoveUI");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
        retVal = simRemoveUI_internal(luaToInt(L, 1));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetUIPosition(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simGetUIPosition");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int position[2];
        if (simGetUIPosition_internal(luaToInt(L, 1), position) != -1)
        {
            pushIntTableOntoStack(L, 2, position);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetUIPosition(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simSetUIPosition");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 2))
    {
        int position[2];
        getIntsFromTable(L, 2, 2, position);
        retVal = simSetUIPosition_internal(luaToInt(L, 1), position);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetUIButtonColor(luaWrap_lua_State* L)
{ // DEPRECATED since 09/02/2017
    TRACE_LUA_API;
    LUA_START("simSetUIButtonColor");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        float col[9];
        float* acp[3] = {col, col + 3, col + 6};
        //      bool failed=true;
        int res = checkOneGeneralInputArgument(L, 3, lua_arg_number, 3, false, true, &errorString);
        if (res != -1)
        {
            if (res != 2)
                acp[0] = nullptr;
            res = checkOneGeneralInputArgument(L, 4, lua_arg_number, 3, true, true, &errorString);
            if (res != -1)
            {
                if (res != 2)
                    acp[1] = nullptr;
                res = checkOneGeneralInputArgument(L, 5, lua_arg_number, 3, true, true, &errorString);
                if (res != -1)
                {
                    if (res != 2)
                        acp[2] = nullptr;
                    for (int i = 0; i < 3; i++)
                    {
                        if (acp[i] != nullptr)
                            getFloatsFromTable(L, 3 + i, 3, acp[i]);
                    }
                    retVal = simSetUIButtonColor_internal(luaToInt(L, 1), luaToInt(L, 2), acp[0], acp[1], acp[2]);
                }
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simHandleChildScript(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("simHandleChildScript");

    warningString = "function is deprecated. Use simHandleSimulationScripts instead.";
    int currentScriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
    CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(currentScriptID);
    if (!it->checkAndSetWarningAboutSimHandleChildScriptAlreadyIssued_oldCompatibility_7_8_2014())
    {
        std::string title("Compatibility issue with ");
        title += it->getShortDescriptiveName();
        std::string txt("The command simHandleChildScript is not supported anymore and was replaced ");
        txt += "with sim.handleSimulationScripts, which operates in a slightly different manner. Make sure to ";
        txt += "adjust this script manually.";
        App::logMsg(sim_verbosity_errors, txt.c_str());
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simHandleSensingChildScripts(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("simHandleSensingChildScripts");

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simScaleSelectedObjects(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("simScaleSelectedObjects");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_bool, 0))
        retVal = simScaleSelectedObjects_internal(luaToDouble(L, 1), luaToBool(L, 2));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simDeleteSelectedObjects(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("simDeleteSelectedObjects");

    int retVal = simDeleteSelectedObjects_internal();

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simDelegateChildScriptExecution(luaWrap_lua_State* L)
{ // DEPRECATED. can only be called from a script running in a thread!!
    TRACE_LUA_API;
    LUA_START("simDelegateChildScriptExecution");

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simGetShapeVertex(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("simGetShapeVertex");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0))
    {
        double relPos[3];
        retVal = simGetShapeVertex_internal(luaToInt(L, 1), luaToInt(L, 2), luaToInt(L, 3), relPos);
        if (retVal == 1)
        {
            luaWrap_lua_pushinteger(L, retVal);
            pushDoubleTableOntoStack(L, 3, relPos);
            LUA_END(2);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetShapeTriangle(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("simGetShapeTriangle");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0))
    {
        int indices[3];
        double normals[9];
        retVal = simGetShapeTriangle_internal(luaToInt(L, 1), luaToInt(L, 2), luaToInt(L, 3), indices, normals);
        if (retVal == 1)
        {
            luaWrap_lua_pushinteger(L, retVal);
            pushIntTableOntoStack(L, 3, indices);
            pushDoubleTableOntoStack(L, 9, normals);
            LUA_END(3);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetMaterialId(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("simGetMaterialId");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_string, 0))
    {
        std::string matName(luaWrap_lua_tostring(L, 1));
        retVal = simGetMaterialId_internal(matName.c_str());
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetShapeMaterial(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("simGetShapeMaterial");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int shapeHandle = luaToInt(L, 1);
        retVal = simGetShapeMaterial_internal(shapeHandle);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simReleaseScriptRawBuffer(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("simReleaseScriptRawBuffer");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int handle = luaToInt(L, 1);
        if (handle == sim_handle_self)
            handle = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
        if ((handle != sim_handle_tree) && (handle != sim_handle_chain))
            retVal = simReleaseScriptRawBuffer_internal(handle, luaToInt(L, 2));
        else
        {
            std::vector<int> scriptHandles;
            if (handle == sim_handle_tree)
                getScriptTree_old(L, false, scriptHandles);
            else
                getScriptChain_old(L, false, false, scriptHandles);
            for (int i = 0; i < int(scriptHandles.size()); i++)
                retVal = simReleaseScriptRawBuffer_internal(scriptHandles[i], sim_handle_all);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetObjectSelectionSize(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("simGetObjectSelectionSize");

    int retVal = simGetObjectSelectionSize_internal();

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetObjectLastSelection(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("simGetObjectLastSelection");

    int retVal = simGetObjectLastSelection_internal();

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetVisionSensorFilter(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("sim.setVisionSensorFilter");
    int retVal = -1; // error

    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetVisionSensorFilter(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("sim.getVisionSensorFilter");

    luaWrap_lua_pushinteger(L, -1);
    LUA_END(1);
}

int _simGetScriptSimulationParameter(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("sim.getScriptSimulationParameter");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_string, 0))
    {
        bool goOn = true;
        int handle = luaToInt(L, 1);
        int selfScriptHandle = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
        if (selfScriptHandle <= SIM_IDEND_SCENEOBJECT)
        {
            if (handle == sim_handle_self)
            {
                handle = selfScriptHandle;
                CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(handle);
                if (it != nullptr)
                {
                    it = it->getParent();
                    if (it != nullptr)
                        handle = it->getObjectHandle();
                    else
                        goOn = false;
                }
                else
                    goOn = false;
            }
        }
        else
        {
            if (handle == sim_handle_self)
            {
                handle = selfScriptHandle;

                // Since this routine can also be called by customization scripts, check for that here:
                CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(handle);
                if (it->getScriptType() == sim_scripttype_customization)
                {
                    handle = it->getObjectHandleThatScriptIsAttachedTo(sim_scripttype_customization);
                    it = App::currentWorld->sceneObjects->embeddedScriptContainer->getScriptFromObjectAttachedTo(
                        sim_scripttype_simulation, handle);
                    if (it != nullptr)
                        handle = it->getScriptHandle();
                    else
                        goOn = false;
                }
            }
        }
        if (goOn)
        {
            bool returnString = false;
            int ret = checkOneGeneralInputArgument(L, 3, lua_arg_bool, 0, true, false, &errorString);
            if ((ret == 0) || (ret == 2))
            {
                if (ret == 2)
                    returnString = luaToBool(L, 3);
                std::string parameterName(luaWrap_lua_tostring(L, 2));
                if ((handle != sim_handle_tree) && (handle != sim_handle_chain) && (handle != sim_handle_all))
                {
                    int l;
                    char* p = simGetScriptSimulationParameter_internal(handle, parameterName.c_str(), &l);
                    if (p != nullptr)
                    {
                        std::string a;
                        a.assign(p, l);
                        if (returnString)
                            luaWrap_lua_pushbinarystring(L, a.c_str(), a.length()); // push binary string for backw. comp.
                        else
                            pushCorrectTypeOntoLuaStack_old(L, a);
                        simReleaseBuffer_internal(p);
                        LUA_END(1);
                    }
                }
            }
        }
        else
            errorString = SIM_ERROR_NO_ASSOCIATED_CHILD_SCRIPT_FOUND;
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetScriptSimulationParameter(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("sim.setScriptSimulationParameter");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_string, 0, lua_arg_string, 0))
    {
        bool goOn = true;
        int handle = luaToInt(L, 1);
        int selfScriptHandle = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
        if (selfScriptHandle <= SIM_IDEND_SCENEOBJECT)
        {
            if (handle == sim_handle_self)
            {
                handle = selfScriptHandle;
                CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(handle);
                if (it != nullptr)
                {
                    it = it->getParent();
                    if (it != nullptr)
                        handle = it->getObjectHandle();
                    else
                        goOn = false;
                }
                else
                    goOn = false;
            }
        }
        else
        {
            if (handle == sim_handle_self)
            {
                handle = selfScriptHandle;
                // Since this routine can also be called by customization scripts, check for that here:
                CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(handle);
                if (it->getScriptType() == sim_scripttype_customization)
                {
                    handle = it->getObjectHandleThatScriptIsAttachedTo(sim_scripttype_customization);
                    it = App::currentWorld->sceneObjects->embeddedScriptContainer->getScriptFromObjectAttachedTo(
                        sim_scripttype_simulation, handle);
                    if (it != nullptr)
                        handle = it->getScriptHandle();
                    else
                        goOn = false;
                }
            }
        }
        if (goOn)
        {
            std::string parameterName(luaWrap_lua_tostring(L, 2));
            size_t parameterValueLength;
            char* parameterValue = (char*)luaWrap_lua_tobuffer(L, 3, &parameterValueLength);
            if ((handle != sim_handle_tree) && (handle != sim_handle_chain))
            {
                retVal = simSetScriptSimulationParameter_internal(handle, parameterName.c_str(), parameterValue,
                                                                  (int)parameterValueLength);
            }
            else
            {
                std::vector<int> scriptHandles;
                if (handle == sim_handle_tree)
                    getScriptTree_old(L, false, scriptHandles);
                else
                    getScriptChain_old(L, false, false, scriptHandles);
                retVal = 0;
                for (size_t i = 0; i < scriptHandles.size(); i++)
                {
                    if (simSetScriptSimulationParameter_internal(scriptHandles[i], parameterName.c_str(),
                                                                 parameterValue, (int)parameterValueLength) == 1)
                        retVal++;
                }
            }
        }
        else
            errorString = SIM_ERROR_NO_ASSOCIATED_CHILD_SCRIPT_FOUND;
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simHandleMechanism(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("sim.handleMechanism");
    int retVal = -1;                      // means error
    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetPathTargetNominalVelocity(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("sim.setPathTargetNominalVelocity");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
        retVal = simSetPathTargetNominalVelocity_internal(luaToInt(L, 1), luaToDouble(L, 2));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetNameSuffix(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("sim.getNameSuffix");

    if (checkInputArguments(L, nullptr, lua_arg_nil, 0))
    { // we want the suffix of current script
        luaWrap_lua_pushinteger(L, CScriptObject::getScriptNameIndexFromInterpreterState_lua_old(L));
        LUA_END(1);
    }
    if (checkInputArguments(L, &errorString, lua_arg_string, 0))
    { // we want the suffix of the provided name
        std::string nameWithSuffix(luaWrap_lua_tostring(L, 1));
        std::string name(tt::getNameWithoutSuffixNumber(nameWithSuffix.c_str(), true));
        int suffixNumber = tt::getNameSuffixNumber(nameWithSuffix.c_str(), true);
        luaWrap_lua_pushinteger(L, suffixNumber);
        luaWrap_lua_pushtext(L, name.c_str());
        LUA_END(2);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetNameSuffix(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("sim.setNameSuffix");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int nb = luaToInt(L, 1);
        CScriptObject::setScriptNameIndexToInterpreterState_lua_old(L, nb);
        retVal = 1;
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simAddStatusbarMessage(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("sim.addStatusbarMessage");

    int retVal = -1; // means error
    if (luaWrap_lua_gettop(L) == 0)
    {
#ifdef SIM_WITH_GUI
        GuiApp::clearStatusbar();
#endif
        retVal = 1;
    }
    else
    {
        if (checkInputArguments(L, nullptr, lua_arg_nil, 0))
        {
#ifdef SIM_WITH_GUI
            GuiApp::clearStatusbar();
#endif
            retVal = 1;
        }
        else
        {
            if (checkInputArguments(L, &errorString, lua_arg_string, 0))
            {
                // retVal=simAddStatusbarMessage_internal(luaWrap_lua_tostring(L,1));
                CScriptObject* it =
                    App::worldContainer->getScriptObjectFromHandle(CScriptObject::getScriptHandleFromInterpreterState_lua(L));
                if (it != nullptr)
                {
                    App::logScriptMsg(it, sim_verbosity_msgs, luaWrap_lua_tostring(L, 1));
                    retVal = 1;
                }
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetShapeMassAndInertia(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("sim.setShapeMassAndInertia");

    int result = -1;
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 9, lua_arg_number,
                            3))
    {
        int handle = luaToInt(L, 1);
        double mass = luaToDouble(L, 2);
        double inertiaMatrix[9];
        getDoublesFromTable(L, 3, 9, inertiaMatrix);
        double centerOfMass[3];
        getDoublesFromTable(L, 4, 3, centerOfMass);
        double* transf = nullptr;
        double transformation[12];
        int res = checkOneGeneralInputArgument(L, 5, lua_arg_number, 12, true, true, &errorString);
        if (res >= 0)
        {
            if (res == 2)
            {
                getDoublesFromTable(L, 5, 12, transformation);
                transf = transformation;
            }
            result = simSetShapeMassAndInertia_internal(handle, mass, inertiaMatrix, centerOfMass, transf);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, result);
    LUA_END(1);
}

int _simGetShapeMassAndInertia(luaWrap_lua_State* L)
{ // DEPRECATED
    TRACE_LUA_API;
    LUA_START("sim.getShapeMassAndInertia");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int handle = luaToInt(L, 1);
        double* transf = nullptr;
        double transformation[12];
        int res = checkOneGeneralInputArgument(L, 2, lua_arg_number, 12, true, true, &errorString);
        if (res >= 0)
        {
            if (res == 2)
            {
                getDoublesFromTable(L, 2, 12, transformation);
                transf = transformation;
            }
            double mass;
            double inertiaMatrix[9];
            double centerOfMass[3];
            int result = simGetShapeMassAndInertia_internal(handle, &mass, inertiaMatrix, centerOfMass, transf);
            if (result == -1)
                luaWrap_lua_pushnil(L);
            luaWrap_lua_pushnumber(L, mass);
            pushDoubleTableOntoStack(L, 9, inertiaMatrix);
            pushDoubleTableOntoStack(L, 3, centerOfMass);
            LUA_END(3);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

typedef struct
{
    double lastTime;
    double accel;
    int vdl;
    double currentPos;
    double maxVelocity;
    double currentVel;
    int objID;
    CSceneObject* object;
    int targetObjID;
    CSceneObject* targetObject;
    double relativeDistanceOnPath;
    double previousLL;
    C7Vector startTr;
    int positionAndOrOrientation;
} simMoveToObjData_old;

int _sim_moveToObj_1(luaWrap_lua_State* L)
{ // for backward compatibility with simMoveToObject on old threaded scripts
    TRACE_LUA_API;
    LUA_START("sim._moveToObj_1");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    { // Those are the arguments that are always required! (the rest can be ignored or set to nil!
        int objID = luaToInt(L, 1);
        int targetObjID = luaToInt(L, 2);
        double maxVelocity = 0.1;
        double relativeDistanceOnPath = -1.0;
        int positionAndOrOrientation = 3; // position and orientation (default value)
        CSceneObject* object = App::currentWorld->sceneObjects->getObjectFromHandle(objID);
        CSceneObject* targetObject = App::currentWorld->sceneObjects->getObjectFromHandle(targetObjID);
        double accel = 0.0; // means infinite accel!! (default value)
        bool foundError = false;
        if ((!foundError) && ((object == nullptr) || (targetObject == nullptr)))
        {
            errorString = SIM_ERROR_OBJECT_OR_TARGET_OBJECT_DOES_NOT_EXIST;
            foundError = true;
        }
        if ((!foundError) && (targetObject == object))
        {
            errorString = SIM_ERROR_OBJECT_IS_SAME_AS_TARGET_OBJECT;
            foundError = true;
        }
        // Now check the optional arguments:
        int res;
        if (!foundError) // position and/or orientation argument:
        {
            res = checkOneGeneralInputArgument(L, 3, lua_arg_number, 0, true, true, &errorString);
            if (res == 2)
            { // get the data
                positionAndOrOrientation = abs(luaToInt(L, 3));
                if ((positionAndOrOrientation & 3) == 0)
                    positionAndOrOrientation = 1; // position only
            }
            foundError = (res == -1);
        }
        if (!foundError) // positionOnPath argument:
        {
            res = checkOneGeneralInputArgument(L, 4, lua_arg_number, 0, true, true, &errorString);
            if (res == 2)
            { // get the data
                relativeDistanceOnPath = tt::getLimitedFloat(0.0, 1.0, luaToDouble(L, 4));
                if (targetObject->getObjectType() != sim_sceneobject_path)
                {
                    errorString = SIM_ERROR_TARGET_OBJECT_IS_NOT_A_PATH;
                    foundError = true;
                }
            }
            foundError = (res == -1);
        }
        if (!foundError) // Velocity argument:
        {
            res = checkOneGeneralInputArgument(L, 5, lua_arg_number, 0, false, false, &errorString);
            if (res == 2)
            { // get the data
                maxVelocity = luaToDouble(L, 5);
            }
            else
                foundError = true; // this argument is not optional!
        }
        if (!foundError) // Accel argument:
        {
            res = checkOneGeneralInputArgument(L, 6, lua_arg_number, 0, true, true, &errorString);
            if (res == 2)
            { // get the data
                accel = fabs(luaToDouble(L, 6));
            }
            foundError = (res == -1);
        }
        if (!foundError)
        { // do the job here!
            C7Vector startTr(object->getCumulativeTransformation());
            double currentVel = 0.0;
            double lastTime = App::currentWorld->simulation->getSimulationTime();
            double vdl = 1.0;
            // vld is the totalvirtual distance
            double currentPos = 0.0;
            double previousLL = 0.0;

            _memHandles_old.push_back(_nextMemHandle_old);
            simMoveToObjData_old* mem = new simMoveToObjData_old();
            mem->lastTime = lastTime;
            mem->accel = accel;
            mem->vdl = vdl;
            mem->currentPos = currentPos;
            mem->maxVelocity = maxVelocity;
            mem->currentVel = currentVel;
            mem->objID = objID;
            mem->object = object;
            mem->targetObjID = targetObjID;
            mem->targetObject = targetObject;
            mem->relativeDistanceOnPath = relativeDistanceOnPath;
            mem->previousLL = previousLL;
            mem->startTr = startTr;
            mem->positionAndOrOrientation = positionAndOrOrientation;

            _memBuffers_old.push_back(mem);
            luaWrap_lua_pushinteger(L, _nextMemHandle_old);
            _nextMemHandle_old++;
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED();
    LUA_END(0);
}

int _sim_moveToObj_2(luaWrap_lua_State* L)
{ // for backward compatibility with simMoveToObject on old threaded scripts
    TRACE_LUA_API;
    LUA_START("sim._moveToObj_2");
    if (checkInputArguments(L, &errorString, lua_arg_integer, 0))
    {
        int h = luaToInt(L, 1);
        simMoveToObjData_old* mem = nullptr;
        for (size_t i = 0; i < _memHandles_old.size(); i++)
        {
            if (_memHandles_old[i] == h)
            {
                mem = (simMoveToObjData_old*)_memBuffers_old[i];
                break;
            }
        }
        if (mem != nullptr)
        {
            bool movementFinished = false;
            double currentTime =
                App::currentWorld->simulation->getSimulationTime() + App::currentWorld->simulation->getTimeStep();
            double dt = currentTime - mem->lastTime;
            mem->lastTime = currentTime;

            if (mem->accel == 0.0)
            { // Means infinite acceleration
                double timeNeeded = (mem->vdl - mem->currentPos) / mem->maxVelocity;
                mem->currentVel = mem->maxVelocity;
                if (timeNeeded > dt)
                {
                    mem->currentPos += dt * mem->maxVelocity;
                    dt = 0.0; // this is what is left
                }
                else
                {
                    mem->currentPos = mem->vdl;
                    if (timeNeeded >= 0.0)
                        dt -= timeNeeded;
                }
            }
            else
            {
                double p = mem->currentPos;
                double v = mem->currentVel;
                double t = dt;
                CLinMotionRoutines::getNextValues(p, v, mem->maxVelocity, mem->accel, 0.0, mem->vdl, 0.0, 0.0, t);
                mem->currentPos = double(p);
                mem->currentVel = double(v);
                dt = double(t);
            }

            // Now check if we are within tolerances:
            if (fabs(mem->currentPos - mem->vdl) <= 0.00001)
                movementFinished = true;

            // Set the new configuration of the object:
            double ll = mem->currentPos / mem->vdl;
            if (ll > 1.0)
                ll = 1.0;
            if ((App::currentWorld->sceneObjects->getObjectFromHandle(mem->objID) == mem->object) &&
                (App::currentWorld->sceneObjects->getObjectFromHandle(mem->targetObjID) ==
                 mem->targetObject)) // make sure the objects are still valid (running in a thread)
            {
                C7Vector targetTr(mem->targetObject->getCumulativeTransformation());
                bool goOn = true;
                if (mem->relativeDistanceOnPath >= 0.0)
                { // we should have a path here
                    if (mem->targetObject->getObjectType() == sim_sceneobject_path)
                    {
                        C7Vector pathLoc;
                        if (((CPath_old*)mem->targetObject)
                                ->pathContainer->getTransformationOnBezierCurveAtNormalizedVirtualDistance(
                                    mem->relativeDistanceOnPath, pathLoc))
                            targetTr *= pathLoc;
                        else
                            mem->relativeDistanceOnPath = -1.0; // the path is empty!
                    }
                    else
                        goOn = false;
                }
                if (goOn)
                {
                    C7Vector newAbs;
                    newAbs.buildInterpolation(mem->startTr, targetTr, (ll - mem->previousLL) / (1.0 - mem->previousLL));
                    mem->startTr = newAbs;
                    C7Vector parentInv(mem->object->getFullParentCumulativeTransformation().getInverse());
                    C7Vector currentTr(mem->object->getCumulativeTransformation());
                    if ((mem->positionAndOrOrientation & 1) == 0)
                        newAbs.X = currentTr.X;
                    if ((mem->positionAndOrOrientation & 2) == 0)
                        newAbs.Q = currentTr.Q;
                    mem->object->setLocalTransformation(parentInv * newAbs);
                }
                else
                    movementFinished = true; // the target object is not a path anymore!!

                mem->previousLL = ll;
                if (!movementFinished)
                {
                    luaWrap_lua_pushinteger(L, 0); // mov. not yet finished
                    LUA_END(1);
                }
                luaWrap_lua_pushinteger(L, 1); // mov. finished
                luaWrap_lua_pushnumber(L, dt); // success (deltaTime left)
                LUA_END(2);
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED();
    LUA_END(0);
}

int _simCheckIkGroup(luaWrap_lua_State* L)
{ // deprecated on 29.09.2020
    TRACE_LUA_API;
    LUA_START("sim.checkIkGroup");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        if (luaWrap_lua_isnonbuffertable(L, 2))
        {
            int jointCnt = (int)luaWrap_lua_rawlen(L, 2);
            int* handles = new int[jointCnt];
            getIntsFromTable(L, 2, jointCnt, handles);
            double* values = new double[jointCnt];

            int res = checkOneGeneralInputArgument(L, 3, lua_arg_number, jointCnt, true, true, &errorString);
            if (res >= 0)
            {
                int* jointOptionsP = nullptr;
                std::vector<int> jointOptions;
                if (res == 2)
                {
                    jointOptions.resize(jointCnt);
                    getIntsFromTable(L, 3, jointCnt, &jointOptions[0]);
                    jointOptionsP = &jointOptions[0];
                }

                int retVal = simCheckIkGroup_internal(luaToInt(L, 1), jointCnt, handles, values, jointOptionsP);
                luaWrap_lua_pushinteger(L, retVal);
                pushDoubleTableOntoStack(L, jointCnt, values);
                delete[] values;
                delete[] handles;
                LUA_END(2);
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, -1);
    LUA_END(1);
}

int _simCreateIkGroup(luaWrap_lua_State* L)
{ // DEPRECATED ON 29.09.2020
    TRACE_LUA_API;
    LUA_START("sim.createIkGroup");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int options = luaToInt(L, 1);
        int res = checkOneGeneralInputArgument(L, 2, lua_arg_number, 2, true, true, &errorString);
        if (res >= 0)
        {
            int intParams[2];
            int* intP = nullptr;
            if (res == 2)
            {
                getIntsFromTable(L, 2, 2, intParams);
                intP = intParams;
            }
            res = checkOneGeneralInputArgument(L, 3, lua_arg_number, 4, true, true, &errorString);
            if (res >= 0)
            {
                double floatParams[4];
                double* floatP = nullptr;
                if (res == 2)
                {
                    getDoublesFromTable(L, 3, 4, floatParams);
                    floatP = floatParams;
                }
                retVal = simCreateIkGroup_internal(options, intP, floatP, nullptr);
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simRemoveIkGroup(luaWrap_lua_State* L)
{ // DEPRECATED ON 29.09.2020
    TRACE_LUA_API;
    LUA_START("sim.removeIkGroup");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int handle = luaToInt(L, 1);
        retVal = simRemoveIkGroup_internal(handle);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simCreateIkElement(luaWrap_lua_State* L)
{ // DEPRECATED ON 29.09.2020
    TRACE_LUA_API;
    LUA_START("sim.createIkElement");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 4))
    {
        int ikGroup = luaToInt(L, 1);
        int options = luaToInt(L, 2);
        int intParams[4];
        getIntsFromTable(L, 3, 4, intParams);

        int res = checkOneGeneralInputArgument(L, 4, lua_arg_number, 4, true, true, &errorString);
        if (res >= 0)
        {
            double floatParams[4];
            double* floatP = nullptr;
            if (res == 2)
            {
                getDoublesFromTable(L, 4, 4, floatParams);
                floatP = floatParams;
            }
            retVal = simCreateIkElement_internal(ikGroup, options, intParams, floatP, nullptr);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simExportIk(luaWrap_lua_State* L)
{ // deprecated on 29.09.2020
    TRACE_LUA_API;
    LUA_START("sim.exportIk");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_string, 0))
    {
        std::string pathAndFilename(luaWrap_lua_tostring(L, 1));
        retVal = simExportIk_internal(pathAndFilename.c_str(), 0, nullptr);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simComputeJacobian(luaWrap_lua_State* L)
{ // deprecated on 29.09.2020
    TRACE_LUA_API;
    LUA_START("sim.computeJacobian");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
        retVal = simComputeJacobian_internal(luaToInt(L, 1), luaToInt(L, 2), nullptr);

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetConfigForTipPose(luaWrap_lua_State* L)
{ // deprecated on 29.09.2020
    TRACE_LUA_API;
    LUA_START("sim.getConfigForTipPose");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 1, lua_arg_number, 0, lua_arg_number,
                            0))
    {
        int ikGroupHandle = luaToInt(L, 1);
        std::vector<int> jointHandles;
        int jointCnt = int(luaWrap_lua_rawlen(L, 2));
        jointHandles.resize(jointCnt);
        getIntsFromTable(L, 2, jointCnt, &jointHandles[0]);
        double thresholdDist = luaToDouble(L, 3);
        int maxTimeInMs = luaToInt(L, 4);
        double metric[4] = {1.0, 1.0, 1.0, 0.1};
        int res = checkOneGeneralInputArgument(L, 5, lua_arg_number, 4, true, true, &errorString);
        if (res >= 0)
        {
            if (res == 2)
                getDoublesFromTable(L, 5, 4, metric);
            int collisionPairCnt = 0;
            std::vector<int> _collisionPairs;
            int* collisionPairs = nullptr;
            res = checkOneGeneralInputArgument(L, 6, lua_arg_number, -1, true, true, &errorString);
            if (res >= 0)
            {
                if (res == 2)
                {
                    collisionPairCnt = int(luaWrap_lua_rawlen(L, 6)) / 2;
                    if (collisionPairCnt > 0)
                    {
                        _collisionPairs.resize(collisionPairCnt * 2);
                        getIntsFromTable(L, 6, collisionPairCnt * 2, &_collisionPairs[0]);
                        collisionPairs = &_collisionPairs[0];
                    }
                }
                std::vector<int> _jointOptions;
                int* jointOptions = nullptr;
                res = checkOneGeneralInputArgument(L, 7, lua_arg_number, jointCnt, true, true, &errorString);
                if (res >= 0)
                {
                    if (res == 2)
                    {
                        _jointOptions.resize(jointCnt);
                        getIntsFromTable(L, 7, jointCnt, &_jointOptions[0]);
                        jointOptions = &_jointOptions[0];
                    }

                    res = checkOneGeneralInputArgument(L, 8, lua_arg_number, jointCnt, true, true, &errorString);
                    if (res >= 0)
                    {
                        std::vector<double> _lowLimits;
                        _lowLimits.resize(jointCnt);
                        std::vector<double> _ranges;
                        _ranges.resize(jointCnt);
                        double* lowLimits = nullptr;
                        double* ranges = nullptr;
                        if (res == 2)
                        {
                            getDoublesFromTable(L, 8, jointCnt, &_lowLimits[0]);
                            lowLimits = &_lowLimits[0];
                        }
                        res = checkOneGeneralInputArgument(L, 9, lua_arg_number, jointCnt, lowLimits == nullptr,
                                                           lowLimits == nullptr, &errorString);
                        if (res >= 0)
                        {
                            if (res == 2)
                            {
                                getDoublesFromTable(L, 9, jointCnt, &_ranges[0]);
                                ranges = &_ranges[0];
                            }
                            std::vector<double> foundConfig;
                            foundConfig.resize(jointCnt);
                            res = simGetConfigForTipPose_internal(
                                ikGroupHandle, jointCnt, &jointHandles[0], thresholdDist, maxTimeInMs, &foundConfig[0],
                                metric, collisionPairCnt, collisionPairs, jointOptions, lowLimits, ranges, nullptr);
                            if (res > 0)
                            {
                                pushDoubleTableOntoStack(L, jointCnt, &foundConfig[0]);
                                LUA_END(1);
                            }
                        }
                    }
                }
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simGenerateIkPath(luaWrap_lua_State* L)
{ // deprecated on 29.09.2020
    TRACE_LUA_API;
    LUA_START("sim.generateIkPath");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 1, lua_arg_number, 0))
    {
        int ikGroupHandle = luaToInt(L, 1);
        std::vector<int> jointHandles;
        int jointCnt = int(luaWrap_lua_rawlen(L, 2));
        jointHandles.resize(jointCnt);
        getIntsFromTable(L, 2, jointCnt, &jointHandles[0]);
        int ptCnt = luaToInt(L, 3);
        int res = checkOneGeneralInputArgument(L, 4, lua_arg_number, -1, true, true, &errorString);
        if (res >= 0)
        {
            int collisionPairCnt = 0;
            std::vector<int> _collisionPairs;
            int* collisionPairs = nullptr;
            if (res == 2)
            {
                collisionPairCnt = int(luaWrap_lua_rawlen(L, 4)) / 2;
                if (collisionPairCnt > 0)
                {
                    _collisionPairs.resize(collisionPairCnt * 2);
                    getIntsFromTable(L, 4, collisionPairCnt * 2, &_collisionPairs[0]);
                    collisionPairs = &_collisionPairs[0];
                }
            }
            res = checkOneGeneralInputArgument(L, 5, lua_arg_number, jointCnt, true, true, &errorString);
            if (res >= 0)
            {
                std::vector<int> _jointOptions;
                int* jointOptions = nullptr;
                if (res == 2)
                {
                    _jointOptions.resize(jointCnt);
                    getIntsFromTable(L, 5, jointCnt, &_jointOptions[0]);
                    jointOptions = &_jointOptions[0];
                }
                double* path = simGenerateIkPath_internal(ikGroupHandle, jointCnt, &jointHandles[0], ptCnt,
                                                          collisionPairCnt, collisionPairs, jointOptions, nullptr);
                if (path != nullptr)
                {
                    pushDoubleTableOntoStack(L, jointCnt * ptCnt, path);
                    simReleaseBuffer_internal((char*)path);
                    LUA_END(1);
                }
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simGetIkGroupHandle(luaWrap_lua_State* L)
{ // deprecated on 29.09.2020
    TRACE_LUA_API;
    LUA_START("sim.getIkGroupHandle");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_string, 0))
    {
        std::string name(luaWrap_lua_tostring(L, 1));
        setCurrentScriptInfo_cSide(CScriptObject::getScriptHandleFromInterpreterState_lua(L),
                                   CScriptObject::getScriptNameIndexFromInterpreterState_lua_old(
                                       L)); // for transmitting to the master function additional info (e.g.for autom.
                                            // name adjustment, or for autom. object deletion when script ends)
        retVal = simGetIkGroupHandle_internal(name.c_str());
        setCurrentScriptInfo_cSide(-1, -1);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetIkGroupMatrix(luaWrap_lua_State* L)
{ // deprecated on 29.09.2020
    TRACE_LUA_API;
    LUA_START("sim.getIkGroupMatrix");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int ikGroupHandle = luaToInt(L, 1);
        int options = luaToInt(L, 2);
        int matrixSize[2];
        double* data = simGetIkGroupMatrix_internal(ikGroupHandle, options, matrixSize);
        if (data != nullptr)
        {
            pushDoubleTableOntoStack(L, matrixSize[0] * matrixSize[1], data);
            pushIntTableOntoStack(L, 2, matrixSize);
            LUA_END(2);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simHandleIkGroup(luaWrap_lua_State* L)
{ // deprecated on 29.09.2020
    TRACE_LUA_API;
    LUA_START("sim.handleIkGroup");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
        retVal = simHandleIkGroup_internal(luaToInt(L, 1));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetIkGroupProperties(luaWrap_lua_State* L)
{ // deprecated on 29.09.2020
    TRACE_LUA_API;
    LUA_START("sim.setIkGroupProperties");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number,
                            0))
        retVal = simSetIkGroupProperties_internal(luaToInt(L, 1), luaToInt(L, 2), luaToInt(L, 3), luaToDouble(L, 4),
                                                  nullptr);

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetIkElementProperties(luaWrap_lua_State* L)
{ // deprecated on 29.09.2020
    TRACE_LUA_API;
    LUA_START("sim.setIkElementProperties");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0))
    {
        int res = checkOneGeneralInputArgument(L, 4, lua_arg_number, 2, true, true, &errorString);
        if (res >= 0)
        {
            double* precision = nullptr;
            double prec[2];
            if (res == 2)
            {
                getDoublesFromTable(L, 4, 2, prec);
                precision = prec;
            }
            res = checkOneGeneralInputArgument(L, 5, lua_arg_number, 2, true, true, &errorString);
            if (res >= 0)
            {
                double* weight = nullptr;
                double w[2];
                if (res == 2)
                {
                    getDoublesFromTable(L, 5, 2, w);
                    weight = w;
                }
                retVal = simSetIkElementProperties_internal(luaToInt(L, 1), luaToInt(L, 2), luaToInt(L, 3), precision,
                                                            weight, nullptr);
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetThreadIsFree(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.setThreadIsFree");

    int retVal = 0;
    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simTubeRead(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim._tubeRead");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int dataLength;
        char* data = simTubeRead_internal(luaToInt(L, 1), &dataLength);
        if (data)
        {
            luaWrap_lua_pushbinarystring(L, (const char*)data, dataLength); // push binary string for backw. comp.
            delete[] data;
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simTubeOpen(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.tubeOpen");

    int retVal = -1; // Error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_string, 0, lua_arg_number, 0))
    {
        std::string strTmp = luaWrap_lua_tostring(L, 2);
        int currentScriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
        CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(currentScriptID);
        retVal = App::currentWorld->commTubeContainer_old->openTube(luaToInt(L, 1), strTmp.c_str(),
                                                                    (it->getScriptType() == sim_scripttype_main) ||
                                                                        (it->getScriptType() == sim_scripttype_simulation),
                                                                    luaToInt(L, 3));
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simTubeClose(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.tubeClose");

    int retVal = -1; // Error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
        retVal = simTubeClose_internal(luaToInt(L, 1));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simTubeWrite(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.tubeWrite");

    int retVal = -1; // Error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_string, 0))
    {
        size_t dataLength;
        char* data = (char*)luaWrap_lua_tobuffer(L, 2, &dataLength);
        retVal = simTubeWrite_internal(luaToInt(L, 1), data, (int)dataLength);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simTubeStatus(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.tubeStatus");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int readSize;
        int writeSize;
        int status = simTubeStatus_internal(luaToInt(L, 1), &readSize, &writeSize);
        if (status >= 0)
        {
            luaWrap_lua_pushinteger(L, status);
            luaWrap_lua_pushinteger(L, readSize);
            luaWrap_lua_pushinteger(L, writeSize);
            LUA_END(3);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSendData(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.sendData");

    int retVal = -1;
    int currentScriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
    CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(currentScriptID);
    if ((it->getScriptType() == sim_scripttype_main) || (it->getScriptType() == sim_scripttype_simulation))
    {
        if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_string, 0,
                                lua_arg_string, 0))
        {
            int targetID = luaToInt(L, 1);
            if ((targetID <= 0) && (targetID != sim_handle_all) && (targetID != sim_handle_tree) &&
                (targetID != sim_handle_chain))
                errorString = SIM_ERROR_INVALID_TARGET_HANDLE;
            else
            {
                int dataHeader = luaToInt(L, 2);
                if (dataHeader < 0)
                    errorString = SIM_ERROR_INVALID_DATA_HEADER;
                else
                {
                    std::string dataName(luaWrap_lua_tostring(L, 3));
                    if ((dataName.length() == 0) || (dataName.find(char(0)) != std::string::npos))
                        errorString = SIM_ERROR_INVALID_DATA_NAME;
                    else
                    {
                        size_t dataLength;
                        char* data = (char*)luaWrap_lua_tobuffer(L, 4, &dataLength);
                        if (dataLength < 1)
                            errorString = SIM_ERROR_INVALID_DATA;
                        else
                        {
                            // Following are default values:
                            int antennaHandle = sim_handle_self;
                            double actionRadius = 100.0;
                            double emissionAngle1 = piValue;
                            double emissionAngle2 = piValT2;
                            double persistence = 0.0;
                            bool err = false;
                            int res = checkOneGeneralInputArgument(L, 5, lua_arg_number, 0, true, false, &errorString);
                            if (res == 2)
                                antennaHandle = luaToInt(L, 5);
                            err = err || ((res != 0) && (res != 2));
                            if (!err)
                            {
                                if ((antennaHandle < 0) && (antennaHandle != sim_handle_default) &&
                                    ((antennaHandle != sim_handle_self) ||
                                     (it->getScriptType() != sim_scripttype_simulation)))
                                {
                                    errorString = SIM_ERROR_INVALID_ANTENNA_HANDLE;
                                    err = true;
                                }
                                else
                                {
                                    if (antennaHandle == sim_handle_self)
                                        antennaHandle =
                                            it->getObjectHandleThatScriptIsAttachedTo(sim_scripttype_simulation);
                                    if (antennaHandle != sim_handle_default)
                                    {
                                        CSceneObject* ant =
                                            App::currentWorld->sceneObjects->getObjectFromHandle(antennaHandle);
                                        if (ant == nullptr)
                                        {
                                            errorString = SIM_ERROR_INVALID_ANTENNA_HANDLE;
                                            err = true;
                                        }
                                    }
                                }
                            }
                            if (!err)
                            {
                                int res =
                                    checkOneGeneralInputArgument(L, 6, lua_arg_number, 0, true, false, &errorString);
                                if (res == 2)
                                    actionRadius = luaToDouble(L, 6);
                                err = err || ((res != 0) && (res != 2));
                            }
                            if (!err)
                            {
                                int res =
                                    checkOneGeneralInputArgument(L, 7, lua_arg_number, 0, true, false, &errorString);
                                if (res == 2)
                                    emissionAngle1 = luaToDouble(L, 7);
                                err = err || ((res != 0) && (res != 2));
                            }
                            if (!err)
                            {
                                int res =
                                    checkOneGeneralInputArgument(L, 8, lua_arg_number, 0, true, false, &errorString);
                                if (res == 2)
                                    emissionAngle2 = luaToDouble(L, 8);
                                err = err || ((res != 0) && (res != 2));
                            }
                            if (!err)
                            {
                                int res =
                                    checkOneGeneralInputArgument(L, 9, lua_arg_number, 0, true, false, &errorString);
                                if (res == 2)
                                    persistence = luaToDouble(L, 9);
                                err = err || ((res != 0) && (res != 2));
                            }
                            if (!err)
                            {
                                actionRadius = tt::getLimitedFloat(0.0, DBL_MAX, actionRadius);
                                emissionAngle1 = tt::getLimitedFloat(0.0, piValue, emissionAngle1);
                                emissionAngle2 = tt::getLimitedFloat(0.0, piValT2, emissionAngle2);
                                persistence = tt::getLimitedFloat(0.0, 99999999999999.9, persistence);
                                if (persistence == 0.0)
                                    persistence = App::currentWorld->simulation->getTimeStep() * 1.5;

                                App::currentWorld->sceneObjects->embeddedScriptContainer->broadcastDataContainer.broadcastData(
                                    currentScriptID, targetID, dataHeader, dataName,
                                    App::currentWorld->simulation->getSimulationTime() + persistence, actionRadius,
                                    antennaHandle, emissionAngle1, emissionAngle2, data, (int)dataLength);
                                retVal = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    else
        errorString = SIM_ERROR_CAN_ONLY_BE_CALLED_FROM_MAIN_SCRIPT_OR_CHILD_SCRIPT;

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simReceiveData(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.receiveData");

    int currentScriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
    CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(currentScriptID);
    if ((it->getScriptType() == sim_scripttype_main) || (it->getScriptType() == sim_scripttype_simulation))
    {
        int dataHeader = -1;
        std::string dataName;
        int antennaHandle = sim_handle_self;
        int index = -1;
        bool err = false;
        int res = checkOneGeneralInputArgument(L, 1, lua_arg_number, 0, true, false, &errorString);
        if (res == 2)
        {
            dataHeader = luaToInt(L, 1);
            if (dataHeader < 0)
                dataHeader = -1;
        }
        err = err || ((res != 0) && (res != 2));
        if (!err)
        {
            int res = checkOneGeneralInputArgument(L, 2, lua_arg_string, 0, true, true, &errorString);
            if (res == 2)
            {
                dataName = luaWrap_lua_tostring(L, 2);
                if (dataName.length() < 1)
                {
                    errorString = SIM_ERROR_INVALID_DATA_NAME;
                    err = true;
                }
            }
            err = err || (res < 0);
        }
        if (!err)
        {
            int res = checkOneGeneralInputArgument(L, 3, lua_arg_number, 0, true, false, &errorString);
            if (res == 2)
            {
                antennaHandle = luaToInt(L, 3);
                if ((antennaHandle < 0) && (antennaHandle != sim_handle_default) &&
                    ((antennaHandle != sim_handle_self) || (it->getScriptType() != sim_scripttype_simulation)))
                {
                    errorString = SIM_ERROR_INVALID_ANTENNA_HANDLE;
                    err = true;
                }
            }
            err = err || ((res != 0) && (res != 2));
            if (!err)
            {
                if (antennaHandle == sim_handle_self)
                    antennaHandle = it->getObjectHandleThatScriptIsAttachedTo(sim_scripttype_simulation);
                if (antennaHandle != sim_handle_default)
                {
                    CSceneObject* ant = App::currentWorld->sceneObjects->getObjectFromHandle(antennaHandle);
                    if (ant == nullptr)
                    {
                        errorString = SIM_ERROR_INVALID_ANTENNA_HANDLE;
                        err = true;
                    }
                }
            }
        }
        if (!err)
        {
            int res = checkOneGeneralInputArgument(L, 4, lua_arg_number, 0, true, false, &errorString);
            if (res == 2)
            {
                index = luaToInt(L, 4);
                if (index < 0)
                    index = -1;
            }
            err = err || ((res != 0) && (res != 2));
        }
        if (!err)
        {
            int theDataHeader;
            int theDataLength;
            int theSenderID;
            std::string theDataName;
            char* data0 = App::currentWorld->sceneObjects->embeddedScriptContainer->broadcastDataContainer.receiveData(
                currentScriptID, App::currentWorld->simulation->getSimulationTime(), dataHeader, dataName,
                antennaHandle, theDataLength, index, theSenderID, theDataHeader, theDataName);
            if (data0 != nullptr)
            {
                luaWrap_lua_pushbinarystring(L, data0, theDataLength); // push binary string for backw. comp.
                luaWrap_lua_pushinteger(L, theSenderID);
                luaWrap_lua_pushinteger(L, theDataHeader);
                luaWrap_lua_pushtext(L, theDataName.c_str());
                LUA_END(4);
            }
        }
    }
    else
        errorString = SIM_ERROR_CAN_ONLY_BE_CALLED_FROM_MAIN_SCRIPT_OR_CHILD_SCRIPT;

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

typedef struct
{
    int objID;
    CSceneObject* object;
    int pathID;
    CPath_old* path;
    double lastTime;
    double accel;
    double pos;
    double vel;
    double maxVelocity;
    double bezierPathLength;
    int positionAndOrOrientation;
} simFollowPath_old;

int _sim_followPath_1(luaWrap_lua_State* L)
{ // for backward compatibility with simFollowPath on old threaded scripts
    TRACE_LUA_API;
    LUA_START("sim._followPath_1");
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0,
                            lua_arg_number, 0))
    { // Those are the arguments that are always required! (the rest can be ignored or set to nil!
        int objID = luaToInt(L, 1);
        int pathID = luaToInt(L, 2);
        double posOnPath = luaToDouble(L, 4);
        int positionAndOrOrientation = abs(luaToInt(L, 3));
        if (positionAndOrOrientation == 0)
            positionAndOrOrientation = 1;
        double maxVelocity = luaToDouble(L, 5);
        CSceneObject* object = App::currentWorld->sceneObjects->getObjectFromHandle(objID);
        CPath_old* path = App::currentWorld->sceneObjects->getPathFromHandle(pathID);
        double accel = 0.0; // means infinite accel!! (default value)
        bool foundError = false;
        if ((!foundError) && (object == nullptr))
        {
            errorString = SIM_ERROR_OBJECT_INEXISTANT;
            foundError = true;
        }
        if ((!foundError) && (path == nullptr))
        {
            errorString = SIM_ERROR_PATH_INEXISTANT;
            foundError = true;
        }
        if (!foundError)
        {
            if (path->pathContainer->getAttributes() & sim_pathproperty_closed_path)
            {
                if (posOnPath < 0.0)
                    posOnPath = 0.0;
            }
            else
                posOnPath = tt::getLimitedFloat(0.0, 1.0, posOnPath);
        }

        // Now check the optional arguments:
        int res;
        if (!foundError) // Accel argument:
        {
            res = checkOneGeneralInputArgument(L, 6, lua_arg_number, 0, true, true, &errorString);
            if (res == 2)
            { // get the data
                accel = fabs(luaToDouble(L, 6));
            }
            foundError = (res == -1);
        }
        if (!foundError)
        { // do the job here!
            double bezierPathLength = path->pathContainer->getBezierVirtualPathLength();
            double pos = posOnPath * bezierPathLength;
            double vel = 0.0;
            double lastTime = App::currentWorld->simulation->getSimulationTime();
            bool movementFinished = (bezierPathLength == 0.0);
            if (movementFinished)
                luaWrap_lua_pushinteger(L, -1);
            else
            {
                _memHandles_old.push_back(_nextMemHandle_old);
                simFollowPath_old* mem = new simFollowPath_old();
                mem->objID = objID;
                mem->object = object;
                mem->pathID = pathID;
                mem->path = path;
                mem->lastTime = lastTime;
                mem->accel = accel;
                mem->pos = pos;
                mem->vel = vel;
                mem->maxVelocity = maxVelocity;
                mem->bezierPathLength = bezierPathLength;
                mem->positionAndOrOrientation = positionAndOrOrientation;
                _memBuffers_old.push_back(mem);
                luaWrap_lua_pushinteger(L, _nextMemHandle_old);
                _nextMemHandle_old++;
            }
            LUA_END(1);
        }
    }
    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED();
    LUA_END(0);
}

int _sim_followPath_2(luaWrap_lua_State* L)
{ // for backward compatibility with simFollowPath on old threaded scripts
    TRACE_LUA_API;
    LUA_START("sim._followPath_2");
    if (checkInputArguments(L, &errorString, lua_arg_integer, 0))
    {
        int h = luaToInt(L, 1);
        simFollowPath_old* mem = nullptr;
        for (size_t i = 0; i < _memHandles_old.size(); i++)
        {
            if (_memHandles_old[i] == h)
            {
                mem = (simFollowPath_old*)_memBuffers_old[i];
                break;
            }
        }
        if (mem != nullptr)
        {
            if ((App::currentWorld->sceneObjects->getObjectFromHandle(mem->objID) == mem->object) &&
                (App::currentWorld->sceneObjects->getPathFromHandle(mem->pathID) ==
                 mem->path)) // make sure the objects are still valid (running in a thread)
            {
                double dt = App::currentWorld->simulation->getTimeStep(); // this is the time left if we leave here
                bool movementFinished = false;
                double currentTime =
                    App::currentWorld->simulation->getSimulationTime() + App::currentWorld->simulation->getTimeStep();
                dt = currentTime - mem->lastTime;
                mem->lastTime = currentTime;
                if (mem->accel == 0.0)
                { // Means infinite acceleration
                    mem->path->pathContainer->handlePath_keepObjectUnchanged(dt, mem->pos, mem->vel, mem->maxVelocity,
                                                                             1.0, false, true);
                }
                else
                {
                    mem->path->pathContainer->handlePath_keepObjectUnchanged(dt, mem->pos, mem->vel, mem->maxVelocity,
                                                                             mem->accel, false, false);
                }

                // Now check if we are within tolerances:
                if (((fabs(mem->pos - mem->bezierPathLength) <= 0.00001) && (mem->maxVelocity >= 0.0)) ||
                    ((fabs(mem->pos - 0.0) <= 0.00001) && (mem->maxVelocity <= 0.0)))
                    movementFinished = true;

                // Set the new configuration of the object:
                double ll = double(mem->pos / mem->bezierPathLength);
                C7Vector newAbs;
                if (mem->path->pathContainer->getTransformationOnBezierCurveAtNormalizedVirtualDistance(ll, newAbs))
                {
                    newAbs = mem->path->getCumulativeTransformation() * newAbs;
                    C7Vector parentInv(mem->object->getFullParentCumulativeTransformation().getInverse());
                    C7Vector currAbs(mem->object->getCumulativeTransformation());
                    if ((mem->positionAndOrOrientation & 1) == 0)
                        newAbs.X = currAbs.X;
                    if ((mem->positionAndOrOrientation & 2) == 0)
                        newAbs.Q = currAbs.Q;
                    mem->object->setLocalTransformation(parentInv * newAbs);
                }
                else
                    movementFinished = true;

                if (!movementFinished)
                {
                    luaWrap_lua_pushinteger(L, 0); // mov. not yet finished
                    LUA_END(1);
                }
                luaWrap_lua_pushinteger(L, 1); // mov. finished
                luaWrap_lua_pushnumber(L, dt); // success (deltaTime left)
                LUA_END(2);
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED();
    LUA_END(0);
}

int _simGetDataOnPath(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.getDataOnPath");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int auxFlags;
        double auxChannels[4];
        if (simGetDataOnPath_internal(luaToInt(L, 1), luaToDouble(L, 2), 0, &auxFlags, auxChannels) == 1)
        {
            luaWrap_lua_pushinteger(L, auxFlags);
            pushDoubleTableOntoStack(L, 4, auxChannels);
            LUA_END(2);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simGetPositionOnPath(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.getPositionOnPath");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        double coord[3];
        if (simGetPositionOnPath_internal(luaToInt(L, 1), luaToDouble(L, 2), coord) == 1)
        {
            pushDoubleTableOntoStack(L, 3, coord);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simGetOrientationOnPath(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.getOrientationOnPath");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        double coord[3];
        if (simGetOrientationOnPath_internal(luaToInt(L, 1), luaToDouble(L, 2), coord) == 1)
        {
            pushDoubleTableOntoStack(L, 3, coord);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simGetClosestPositionOnPath(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.getClosestPositionOnPath");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 3))
    {
        double coord[3];
        getDoublesFromTable(L, 2, 3, coord);
        double dist = 0.0;
        if (simGetClosestPositionOnPath_internal(luaToInt(L, 1), coord, &dist) != -1)
        {
            luaWrap_lua_pushnumber(L, dist);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simGetPathPosition(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.getPathPosition");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        double pathVal[1];
        if (simGetPathPosition_internal(luaToInt(L, 1), pathVal) != -1)
        {
            luaWrap_lua_pushnumber(L, pathVal[0]);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetPathPosition(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.setPathPosition");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
        retVal = simSetPathPosition_internal(luaToInt(L, 1), luaToDouble(L, 2));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetPathLength(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.getPathLength");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        double pathLen[1];
        if (simGetPathLength_internal(luaToInt(L, 1), pathLen) != -1)
        {
            luaWrap_lua_pushnumber(L, pathLen[0]);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simInsertPathCtrlPoints(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.insertPathCtrlPoints");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number,
                            0))
    {
        int pathHandle = luaToInt(L, 1);
        int options = luaToInt(L, 2);
        int startIndex = luaToInt(L, 3);
        int ptCnt = luaToInt(L, 4);
        int floatOrIntCountPerPoint = 11;
        if (options & 2)
            floatOrIntCountPerPoint = 16;

        int res = checkOneGeneralInputArgument(L, 5, lua_arg_number, ptCnt * floatOrIntCountPerPoint, false, false,
                                               &errorString);
        if (res == 2)
        {
            double* data = new double[ptCnt * floatOrIntCountPerPoint];
            getDoublesFromTable(L, 5, ptCnt * floatOrIntCountPerPoint, data);
            for (int i = 0; i < ptCnt; i++)
                ((int*)(data + floatOrIntCountPerPoint * i + 8))[0] = int(data[floatOrIntCountPerPoint * i + 8] + 0.5);
            if (options & 2)
            {
                for (int i = 0; i < ptCnt; i++)
                    ((int*)(data + floatOrIntCountPerPoint * i + 11))[0] =
                        int(data[floatOrIntCountPerPoint * i + 11] + 0.5);
            }
            retVal = simInsertPathCtrlPoints_internal(pathHandle, options, startIndex, ptCnt, data);
            delete[] data;
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simCutPathCtrlPoints(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.cutPathCtrlPoints");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0))
    {
        int pathHandle = luaToInt(L, 1);
        int startIndex = luaToInt(L, 2);
        int ptCnt = luaToInt(L, 3);
        retVal = simCutPathCtrlPoints_internal(pathHandle, startIndex, ptCnt);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _sim_CreatePath(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim._createPath");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int attribs = luaToInt(L, 1);
        int* intP = nullptr;
        double* floatP = nullptr;
        int intParams[3];
        double floatParams[3];
        float* color = nullptr;
        float c[12];
        int res = checkOneGeneralInputArgument(L, 2, lua_arg_number, 3, true, true, &errorString);
        if (res >= 0)
        {
            if (res == 2)
            {
                getIntsFromTable(L, 2, 3, intParams);
                intP = intParams;
            }
            res = checkOneGeneralInputArgument(L, 3, lua_arg_number, 3, true, true, &errorString);
            if (res >= 0)
            {
                if (res == 2)
                {
                    getDoublesFromTable(L, 3, 3, floatParams);
                    floatP = floatParams;
                }
                res = checkOneGeneralInputArgument(L, 4, lua_arg_number, 12, true, true, &errorString);
                if (res >= 0)
                {
                    if (res == 2)
                    {
                        getFloatsFromTable(L, 4, 12, c);
                        color = c;
                    }
                    retVal = simCreatePath_internal(attribs, intP, floatP, color);
                }
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetScriptExecutionCount(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.getScriptExecutionCount");

    int currentScriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
    CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(currentScriptID);

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, it->getNumberOfPasses());
    LUA_END(1);
}

int _simIsScriptExecutionThreaded(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.isScriptExecutionThreaded");

    int currentScriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
    CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(currentScriptID);
    int retVal = 0;
    if ((it != nullptr) && it->getThreadedExecution_oldThreads())
        retVal = 1;

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simIsScriptRunningInThread(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.isScriptRunningInThread");

    int retVal = 1;
    if (VThread::isSimThread())
        retVal = 0;

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetThreadResumeLocation(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.setThreadResumeLocation");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        if (CThreadPool_old::setThreadResumeLocation(luaToInt(L, 1), luaToInt(L, 2)))
            retVal = 1;
        else
            retVal = 0;
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simResumeThreads(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.resumeThreads");

    int retVal = -1;
    int currentScriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
    CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(currentScriptID);
    if (it->getScriptType() == sim_scripttype_main)
    {
        if (checkInputArguments(L, &errorString, lua_arg_number, 0))
        {
            int loc = luaToInt(L, 1);

            int startT = (int)VDateTime::getTimeInMs();
            retVal = App::currentWorld->sceneObjects->callScripts_noMainScript(sim_scripttype_simulation | sim_scripttype_threaded_old, loc, nullptr, nullptr);
            // Following line important: when erasing a running threaded script object, with above cascaded
            // call, the thread will never resume nor be able to end. Next line basically runs all
            // that were not yet ran:
            retVal += CThreadPool_old::handleAllThreads_withResumeLocation(loc);
        }
    }
    else
        errorString = SIM_ERROR_CAN_ONLY_BE_CALLED_FROM_MAIN_SCRIPT;

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simLaunchThreadedChildScripts(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.launchThreadedChildScripts");

    int retVal = -1; // means error
    int currentScriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
    CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(currentScriptID);
    if (it != nullptr)
    {
        if (it->getScriptType() == sim_scripttype_main)
        {
            int startT = (int)VDateTime::getTimeInMs();
            retVal = App::currentWorld->sceneObjects->callScripts_noMainScript(sim_scripttype_simulation | sim_scripttype_threaded_old, sim_scriptthreadresume_launch, nullptr, nullptr);
        }
        else
            errorString = SIM_ERROR_CAN_ONLY_BE_CALLED_FROM_MAIN_SCRIPT;
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetThreadId(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.getThreadId");

    int retVal = simGetThreadId_internal();

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetUserParameter(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.getUserParameter");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_string, 0))
    {
        int handle = luaToInt(L, 1);
        if (handle == sim_handle_self)
        {
            handle = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
            CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(handle);
            if (handle <= SIM_IDEND_SCENEOBJECT)
            { // is a CScript
                if (it->getParentIsProxy())
                {
                    CSceneObject* obj = App::currentWorld->sceneObjects->getObjectFromHandle(handle);
                    obj = obj->getParent();
                    if (obj != nullptr)
                        handle = obj->getObjectHandle();
                    else
                        handle = -1;
                }
            }
            else
                handle = it->getObjectHandleThatScriptIsAttachedTo(-1);
        }
        bool returnString = false;
        int ret = checkOneGeneralInputArgument(L, 3, lua_arg_bool, 0, true, false, &errorString);
        if ((ret == 0) || (ret == 2))
        {
            if (ret == 2)
                returnString = luaToBool(L, 3);
            std::string parameterName(luaWrap_lua_tostring(L, 2));
            int l;
            char* p = simGetUserParameter_internal(handle, parameterName.c_str(), &l);
            if (p != nullptr)
            {
                std::string a;
                a.assign(p, l);
                if (returnString)
                    luaWrap_lua_pushbinarystring(L, a.c_str(), a.length()); // push binary string for backw. comp.
                else
                    pushCorrectTypeOntoLuaStack_old(L, a);
                simReleaseBuffer_internal(p);
                LUA_END(1);
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetUserParameter(luaWrap_lua_State* L)
{ // deprecated on 01.10.2020
    TRACE_LUA_API;
    LUA_START("sim.setUserParameter");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_string, 0, lua_arg_string, 0))
    {
        int handle = luaToInt(L, 1);
        if (handle == sim_handle_self)
        {
            handle = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
            CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(handle);
            if (handle <= SIM_IDEND_SCENEOBJECT)
            { // is a CScript
                if (it->getParentIsProxy())
                {
                    CSceneObject* obj = App::currentWorld->sceneObjects->getObjectFromHandle(handle);
                    obj = obj->getParent();
                    if (obj != nullptr)
                        handle = obj->getObjectHandle();
                    else
                        handle = -1;
                }
            }
            else
                handle = it->getObjectHandleThatScriptIsAttachedTo(-1);
        }
        std::string parameterName(luaWrap_lua_tostring(L, 2));
        size_t parameterValueLength;
        char* parameterValue = (char*)luaWrap_lua_tobuffer(L, 3, &parameterValueLength);
        retVal = simSetUserParameter_internal(handle, parameterName.c_str(), parameterValue, (int)parameterValueLength);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _genericFunctionHandler_old(luaWrap_lua_State* L, CScriptCustomFunction* func)
{ // deprecated around 2015
    TRACE_LUA_API;
    // We first read all arguments from the stack
    std::vector<char> inBoolVector;
    std::vector<int> inIntVector;
    std::vector<float> inFloatVector;
    std::vector<double> inDoubleVector;
    std::vector<std::string> inStringVector;
    std::vector<std::string> inCharVector;
    std::vector<int> inInfoVector;
    for (int i = 0; i < int(func->inputArgTypes.size()); i++)
    {
        if (!readCustomFunctionDataFromStack_old(L, i + 1, func->inputArgTypes[i], inBoolVector, inIntVector,
                                                 inFloatVector, inDoubleVector, inStringVector, inCharVector,
                                                 inInfoVector))
            break;
    }

    // Now we retrieve the object ID this script might be attached to:
    int currentScriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
    CScriptObject* itObj = App::worldContainer->getScriptObjectFromHandle(currentScriptID);
    int linkedObject = -1;
    if (itObj->getScriptType() == sim_scripttype_simulation)
    {
        CSceneObject* obj = App::currentWorld->sceneObjects->getObjectFromHandle(
            itObj->getObjectHandleThatScriptIsAttachedTo(sim_scripttype_simulation));
        if (obj != nullptr)
            linkedObject = obj->getObjectHandle();
    }
    if (itObj->getScriptType() == sim_scripttype_customization)
    {
        CSceneObject* obj = App::currentWorld->sceneObjects->getObjectFromHandle(
            itObj->getObjectHandleThatScriptIsAttachedTo(sim_scripttype_customization));
        if (obj != nullptr)
            linkedObject = obj->getObjectHandle();
    }
    // We prepare the callback structure:
    SLuaCallBack* p = new SLuaCallBack;
    p->objectID = linkedObject;
    p->scriptID = currentScriptID;
    p->inputBool = nullptr;
    p->inputInt = nullptr;
    p->inputFloat = nullptr;
    p->inputDouble = nullptr;
    p->inputChar = nullptr;
    p->inputCharBuff = nullptr;
    p->inputArgCount = 0;
    p->inputArgTypeAndSize = nullptr;
    p->outputBool = nullptr;
    p->outputInt = nullptr;
    p->outputFloat = nullptr;
    p->outputDouble = nullptr;
    p->outputChar = nullptr;
    p->outputCharBuff = nullptr;
    p->outputArgCount = 0;
    p->outputArgTypeAndSize = nullptr;
    p->waitUntilZero = 0;
    // Now we prepare the input buffers:
    p->inputBool = new bool[inBoolVector.size()];
    p->inputInt = new int[inIntVector.size()];
    p->inputFloat = new float[inFloatVector.size()];
    p->inputDouble = new double[inDoubleVector.size()];
    int charCnt = 0;
    for (size_t k = 0; k < inStringVector.size(); k++)
        charCnt += (int)inStringVector[k].length() + 1; // terminal 0
    p->inputChar = new char[charCnt];

    int charBuffCnt = 0;
    for (size_t k = 0; k < inCharVector.size(); k++)
        charBuffCnt += (int)inCharVector[k].length();
    p->inputCharBuff = new char[charBuffCnt];

    p->inputArgCount = (int)inInfoVector.size() / 2;
    p->inputArgTypeAndSize = new int[inInfoVector.size()];
    // We fill the input buffers:
    for (int k = 0; k < int(inBoolVector.size()); k++)
        p->inputBool[k] = inBoolVector[k];
    for (int k = 0; k < int(inIntVector.size()); k++)
        p->inputInt[k] = inIntVector[k];
    for (int k = 0; k < int(inFloatVector.size()); k++)
        p->inputFloat[k] = inFloatVector[k];
    for (int k = 0; k < int(inDoubleVector.size()); k++)
        p->inputDouble[k] = inDoubleVector[k];
    charCnt = 0;
    for (int k = 0; k < int(inStringVector.size()); k++)
    {
        for (int l = 0; l < int(inStringVector[k].length()); l++)
            p->inputChar[charCnt + l] = inStringVector[k][l];
        charCnt += (int)inStringVector[k].length();
        // terminal 0:
        p->inputChar[charCnt] = 0;
        charCnt++;
    }

    charBuffCnt = 0;
    for (int k = 0; k < int(inCharVector.size()); k++)
    {
        for (int l = 0; l < int(inCharVector[k].length()); l++)
            p->inputCharBuff[charBuffCnt + l] = inCharVector[k][l];
        charBuffCnt += (int)inCharVector[k].length();
    }

    for (int k = 0; k < int(inInfoVector.size()); k++)
        p->inputArgTypeAndSize[k] = inInfoVector[k];

    // Now we can call the callback:
    func->callBackFunction_old(p);

    bool dontDeleteStructureYet = false;
    while (p->waitUntilZero != 0)
    { // backward compatibility (for real threads)
        if (!CThreadPool_old::switchBackToPreviousThread())
            break;
        if (CThreadPool_old::getSimulationStopRequestedAndActivated())
        { // give a chance to the c app to set the waitUntilZero to zero! (above turns true only 1-2 secs after the stop
            // request arrived)
            // Following: the extension module might still write 0 into that position to signal "no more waiting" in
            // case this while loop got interrupted by a stop request.
            dontDeleteStructureYet = true;
            break;
        }
    }

    // We first delete the input buffers:
    delete[] p->inputBool;
    delete[] p->inputInt;
    delete[] p->inputFloat;
    delete[] p->inputDouble;
    delete[] p->inputChar;
    delete[] p->inputCharBuff;
    delete[] p->inputArgTypeAndSize;
    // Now we have to build the returned data onto the stack:
    if (p->outputArgCount != 0)
    {
        int boolPt = 0;
        int intPt = 0;
        int floatPt = 0;
        int doublePt = 0;
        int stringPt = 0;
        int stringBuffPt = 0;
        for (int i = 0; i < p->outputArgCount; i++)
        {
            writeCustomFunctionDataOntoStack_old(L, p->outputArgTypeAndSize[2 * i + 0],
                                                 p->outputArgTypeAndSize[2 * i + 1], p->outputBool, boolPt,
                                                 p->outputInt, intPt, p->outputFloat, floatPt, p->outputDouble,
                                                 doublePt, p->outputChar, stringPt, p->outputCharBuff, stringBuffPt);
        }
    }
    // We now delete the output buffers:
    delete[] p->outputBool;
    delete[] p->outputInt;
    delete[] p->outputFloat;
    delete[] p->outputDouble;
    delete[] p->outputChar;
    delete[] p->outputCharBuff;
    delete[] p->outputArgTypeAndSize;
    // And we return the number of arguments:
    int outputArgCount = p->outputArgCount;
    if (dontDeleteStructureYet)
    { // We cannot yet delete the structure because an extension module might still write '0' into
        // p->waitUntilZero!! We delete the structure at the end of the simulation.
        App::currentWorld->sceneObjects->embeddedScriptContainer->addCallbackStructureObjectToDestroyAtTheEndOfSimulation_old(p);
    }
    else
        delete p;
    if (outputArgCount == 0)
    {
        luaWrap_lua_pushnil(L);
        outputArgCount = 1;
    }
    return (outputArgCount);
}

int _simSetCollectionName(luaWrap_lua_State* L)
{ // deprecated on 17.11.2020
    TRACE_LUA_API;
    LUA_START("sim.setCollectionName");
    int retVal = -1; // error

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_string, 0))
        retVal = simSetCollectionName_internal(luaToInt(L, 1), luaWrap_lua_tostring(L, 2));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _sim_CreateCollection(luaWrap_lua_State* L)
{ // deprecated on 17.11.2020
    TRACE_LUA_API;
    LUA_START("sim._createCollection");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_string, 0, lua_arg_number, 0))
    {
        std::string collName(luaWrap_lua_tostring(L, 1));
        int options = luaToInt(L, 2);
        retVal = simCreateCollection_internal(collName.c_str(), options);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simAddObjectToCollection(luaWrap_lua_State* L)
{ // deprecated on 17.11.2020
    TRACE_LUA_API;
    LUA_START("sim.addObjectToCollection");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number,
                            0))
    {
        int collHandle = luaToInt(L, 1);
        int objHandle = luaToInt(L, 2);
        int what = luaToInt(L, 3);
        int options = luaToInt(L, 4);
        retVal = simAddObjectToCollection_internal(collHandle, objHandle, what, options);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetCollectionHandle(luaWrap_lua_State* L)
{ // deprecated on 17.11.2020
    TRACE_LUA_API;
    LUA_START("sim.getCollectionHandle");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_string, 0))
    {
        std::string name(luaWrap_lua_tostring(L, 1));
        setCurrentScriptInfo_cSide(CScriptObject::getScriptHandleFromInterpreterState_lua(L),
                                   CScriptObject::getScriptNameIndexFromInterpreterState_lua_old(
                                       L)); // for transmitting to the master function additional info (e.g.for autom.
                                            // name adjustment, or for autom. object deletion when script ends)
        retVal = simGetCollectionHandle_internal(name.c_str());
        setCurrentScriptInfo_cSide(-1, -1);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simRemoveCollection(luaWrap_lua_State* L)
{ // deprecated on 17.11.2020
    TRACE_LUA_API;
    LUA_START("sim.removeCollection");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
        retVal = simRemoveCollection_internal(luaToInt(L, 1));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simEmptyCollection(luaWrap_lua_State* L)
{ // deprecated on 17.11.2020
    TRACE_LUA_API;
    LUA_START("sim.emptyCollection");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
        retVal = simEmptyCollection_internal(luaToInt(L, 1));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetCollectionName(luaWrap_lua_State* L)
{ // deprecated on 17.11.2020
    TRACE_LUA_API;
    LUA_START("sim.getCollectionName");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        char* name = simGetCollectionName_internal(luaToInt(L, 1));
        if (name != nullptr)
        {
            luaWrap_lua_pushtext(L, name);
            simReleaseBuffer_internal(name);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simHandleCollision(luaWrap_lua_State* L)
{ // deprecated on 20.11.2020
    TRACE_LUA_API;
    LUA_START("sim.handleCollision");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int objHandle = luaToInt(L, 1);
        retVal = simHandleCollision_internal(objHandle);
        if ((retVal > 0) && (objHandle >= 0))
        {
            int collObjHandles[2];
            CCollisionObject_old* it = App::currentWorld->collisions_old->getObjectFromHandle(objHandle);
            if (it != nullptr)
            {
                it->readCollision(collObjHandles);
                luaWrap_lua_pushinteger(L, retVal);
                pushIntTableOntoStack(L, 2, collObjHandles);
                LUA_END(2);
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simReadCollision(luaWrap_lua_State* L)
{ // deprecated on 20.11.2020
    TRACE_LUA_API;
    LUA_START("sim.readCollision");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int objHandle = luaToInt(L, 1);
        retVal = simReadCollision_internal(objHandle);
        if (retVal > 0)
        {
            int collObjHandles[2];
            CCollisionObject_old* it = App::currentWorld->collisions_old->getObjectFromHandle(objHandle);
            if (it != nullptr)
            {
                it->readCollision(collObjHandles);
                luaWrap_lua_pushinteger(L, retVal);
                pushIntTableOntoStack(L, 2, collObjHandles);
                LUA_END(2);
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simHandleDistance(luaWrap_lua_State* L)
{ // deprecated on 20.11.2020
    TRACE_LUA_API;
    LUA_START("sim.handleDistance");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        double d;
        retVal = simHandleDistance_internal(luaToInt(L, 1), &d);
        if (retVal == 1)
        {
            luaWrap_lua_pushinteger(L, retVal);
            luaWrap_lua_pushnumber(L, d);
            LUA_END(2);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simReadDistance(luaWrap_lua_State* L)
{ // deprecated on 20.11.2020
    TRACE_LUA_API;
    LUA_START("sim.readDistance");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        double d;
        retVal = simReadDistance_internal(luaToInt(L, 1), &d);
        if (retVal == 1)
        {
            luaWrap_lua_pushinteger(L, retVal);
            luaWrap_lua_pushnumber(L, d);
            LUA_END(2);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetCollisionHandle(luaWrap_lua_State* L)
{ // deprecated on 20.11.2020
    TRACE_LUA_API;
    LUA_START("sim.getCollisionHandle");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_string, 0))
    {
        std::string name(luaWrap_lua_tostring(L, 1));
        setCurrentScriptInfo_cSide(CScriptObject::getScriptHandleFromInterpreterState_lua(L),
                                   CScriptObject::getScriptNameIndexFromInterpreterState_lua_old(
                                       L)); // for transmitting to the master function additional info (e.g.for autom.
                                            // name adjustment, or for autom. object deletion when script ends)
        retVal = simGetCollisionHandle_internal(name.c_str());
        setCurrentScriptInfo_cSide(-1, -1);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetDistanceHandle(luaWrap_lua_State* L)
{ // deprecated on 20.11.2020
    TRACE_LUA_API;
    LUA_START("sim.getDistanceHandle");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_string, 0))
    {
        std::string name(luaWrap_lua_tostring(L, 1));
        setCurrentScriptInfo_cSide(CScriptObject::getScriptHandleFromInterpreterState_lua(L),
                                   CScriptObject::getScriptNameIndexFromInterpreterState_lua_old(
                                       L)); // for transmitting to the master function additional info (e.g.for autom.
                                            // name adjustment, or for autom. object deletion when script ends)
        retVal = simGetDistanceHandle_internal(name.c_str());
        setCurrentScriptInfo_cSide(-1, -1);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simResetCollision(luaWrap_lua_State* L)
{ // deprecated on 20.11.2020
    TRACE_LUA_API;
    LUA_START("sim.resetCollision");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
        retVal = simResetCollision_internal(luaToInt(L, 1));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simResetDistance(luaWrap_lua_State* L)
{ // deprecated on 20.11.2020
    TRACE_LUA_API;
    LUA_START("sim.resetDistance");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
        retVal = simResetDistance_internal(luaToInt(L, 1));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simAddBanner(luaWrap_lua_State* L)
{ // deprecated on 23.11.2020
    TRACE_LUA_API;
    LUA_START("sim.addBanner");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_string, 0, lua_arg_number, 0, lua_arg_number, 0))
    {
        std::string label(luaWrap_lua_tostring(L, 1));
        double size = luaToDouble(L, 2);
        int options = luaToInt(L, 3);

        double* positionAndEulerAngles = nullptr;
        int parentObjectHandle = -1;
        float* labelColors = nullptr;
        float* backgroundColors = nullptr;

        int res = checkOneGeneralInputArgument(L, 4, lua_arg_number, 6, true, true, &errorString);
        int okToGo = (res != -1);
        if (okToGo)
        {
            double positionAndEulerAnglesC[6];
            if (res > 0)
            {
                if (res == 2)
                {
                    getDoublesFromTable(L, 4, 6, positionAndEulerAnglesC);
                    positionAndEulerAngles = positionAndEulerAnglesC;
                }
                res = checkOneGeneralInputArgument(L, 5, lua_arg_number, 0, true, true, &errorString);
                okToGo = (res != -1);
                if (okToGo)
                {
                    if (res > 0)
                    {
                        if (res == 2)
                            parentObjectHandle = luaToInt(L, 5);
                        res = checkOneGeneralInputArgument(L, 6, lua_arg_number, 12, true, true, &errorString);
                        okToGo = (res != -1);
                        if (okToGo)
                        {
                            float labelColorsC[12];
                            if (res > 0)
                            {
                                if (res == 2)
                                {
                                    getFloatsFromTable(L, 6, 12, labelColorsC);
                                    labelColors = labelColorsC;
                                }
                                res = checkOneGeneralInputArgument(L, 7, lua_arg_number, 12, true, true, &errorString);
                                okToGo = (res != -1);
                                if (okToGo)
                                {
                                    float backgroundColorsC[12];
                                    if (res > 0)
                                    {
                                        if (res == 2)
                                        {
                                            getFloatsFromTable(L, 7, 12, backgroundColorsC);
                                            backgroundColors = backgroundColorsC;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (okToGo)
            {
                retVal = simAddBanner_internal(label.c_str(), size, options, positionAndEulerAngles, parentObjectHandle,
                                               labelColors, backgroundColors);
                if (retVal != -1)
                { // following condition added on 2011/01/06 so as to not remove objects created from the c/c++
                    // interface or an add-on:
                    int currentScriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
                    CScriptObject* itScrObj = App::worldContainer->getScriptObjectFromHandle(currentScriptID);
                    CBannerObject* anObj = App::currentWorld->bannerCont_old->getObject(retVal);
                    if (anObj != nullptr)
                        anObj->setCreatedFromScript((itScrObj->getScriptType() == sim_scripttype_main) ||
                                                    (itScrObj->getScriptType() == sim_scripttype_simulation));
                }
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simRemoveBanner(luaWrap_lua_State* L)
{ // deprecated on 23.11.2020
    TRACE_LUA_API;
    LUA_START("sim.removeBanner");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int objectHandle = luaToInt(L, 1);
        if (objectHandle == sim_handle_all)
        { // following condition added here on 2011/01/06 so as not to remove objects created from a C/c++ call
            App::currentWorld->bannerCont_old->eraseAllObjects(true);
            retVal = 1;
        }
        else
            retVal = simRemoveBanner_internal(objectHandle);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simAddGhost(luaWrap_lua_State* L)
{ // deprecated on 23.11.2020
    TRACE_LUA_API;
    LUA_START("sim.addGhost");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0,
                            lua_arg_number, 0))
    {
        int ghostGroup = luaToInt(L, 1);
        int objectHandle = luaToInt(L, 2);
        int options = luaToInt(L, 3);
        double startTime = luaToDouble(L, 4);
        double endTime = luaToDouble(L, 5);
        int res = checkOneGeneralInputArgument(L, 6, lua_arg_number, 12, true, true, &errorString);
        if (res >= 0)
        {
            bool defaultColors = true;
            float color[12];
            if (res == 2)
            {
                defaultColors = false;
                getFloatsFromTable(L, 6, 12, color);
            }
            if (defaultColors)
                retVal = simAddGhost_internal(ghostGroup, objectHandle, options, startTime, endTime, nullptr);
            else
                retVal = simAddGhost_internal(ghostGroup, objectHandle, options, startTime, endTime, color);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simModifyGhost(luaWrap_lua_State* L)
{ // deprecated on 23.11.2020
    TRACE_LUA_API;
    LUA_START("sim.modifyGhost");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number,
                            0))
    {
        int ghostGroup = luaToInt(L, 1);
        int ghostId = luaToInt(L, 2);
        int operation = luaToInt(L, 3);
        double floatValue = luaToDouble(L, 4);

        int options = 0;
        int optionsMask = 0;
        int res = 0;
        if (operation == 10)
            res = checkOneGeneralInputArgument(L, 5, lua_arg_number, 0, false, false, &errorString);
        if (res >= 0)
        {
            if ((res == 2) && (operation == 10))
            {
                options = luaToInt(L, 5);
                res = checkOneGeneralInputArgument(L, 6, lua_arg_number, 0, false, false, &errorString);
                if (res == 2)
                    optionsMask = luaToInt(L, 6);
                else
                    res = -1;
            }
            if (res >= 0)
            {
                int floatCnt = 7;
                if (operation == 13)
                    floatCnt = 12;
                res = 0;
                if ((operation >= 11) && (operation <= 13))
                    res = checkOneGeneralInputArgument(L, 7, lua_arg_number, floatCnt, false, false, &errorString);
                if (res >= 0)
                {
                    double colorOrTransfData[12];
                    if ((res == 2) && (operation >= 11) && (operation <= 13))
                        getDoublesFromTable(L, 7, floatCnt, colorOrTransfData);
                    retVal = simModifyGhost_internal(ghostGroup, ghostId, operation, floatValue, options, optionsMask,
                                                     colorOrTransfData);
                }
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetGraphUserData(luaWrap_lua_State* L)
{ // deprecated on 23.11.2020
    TRACE_LUA_API;
    LUA_START("sim.setGraphUserData");

    int retVal = -1; // for error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_string, 0, lua_arg_number, 0))
    {
        int graphHandle = luaToInt(L, 1);
        std::string dataName(luaWrap_lua_tostring(L, 2));
        double data = luaToDouble(L, 3);
        retVal = simSetGraphUserData_internal(graphHandle, dataName.c_str(), data);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simAddPointCloud(luaWrap_lua_State* L)
{ // deprecated on 23.11.2020
    TRACE_LUA_API;
    LUA_START("sim.addPointCloud");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0,
                            lua_arg_number, 0, lua_arg_number, 3))
    {
        int pageMask = luaToInt(L, 1);
        int layerMask = luaToInt(L, 2);
        int objectHandle = luaToInt(L, 3);
        int options = luaToInt(L, 4);
        int currentScriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
        CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(currentScriptID);
        if ((it->getScriptType() == sim_scripttype_main) || (it->getScriptType() == sim_scripttype_simulation))
            options = (options | 1) -
                      1; // cloud is automatically removed at the end of the simulation (i.e. is not persistent)
        double pointSize = luaToDouble(L, 5);
        int pointCnt = (int)luaWrap_lua_rawlen(L, 6) / 3;
        std::vector<double> pointCoordinates(pointCnt * 3, 0.0);
        getDoublesFromTable(L, 6, pointCnt * 3, &pointCoordinates[0]);
        int res;
        res = checkOneGeneralInputArgument(L, 7, lua_arg_number, 12, true, true, &errorString);
        if (res >= 0)
        {
            unsigned char* defaultColors = nullptr;
            std::vector<unsigned char> _defCols(12, 0);
            if (res == 2)
            {
                std::vector<int> _defCols_(12, 0);
                getIntsFromTable(L, 7, 12, &_defCols_[0]);
                for (int i = 0; i < 12; i++)
                    _defCols[i] = (unsigned char)_defCols_[i];
                defaultColors = &_defCols[0];
            }
            res = checkOneGeneralInputArgument(L, 8, lua_arg_number, pointCnt * 3, true, true, &errorString);
            if (res >= 0)
            {
                unsigned char* pointColors = nullptr;
                std::vector<unsigned char> _pointCols;
                if (res == 2)
                {
                    _pointCols.resize(pointCnt * 3, 0);
                    std::vector<int> _pointCols_(pointCnt * 3, 0);
                    getIntsFromTable(L, 8, pointCnt * 3, &_pointCols_[0]);
                    for (int i = 0; i < pointCnt * 3; i++)
                        _pointCols[i] = (unsigned char)_pointCols_[i];
                    pointColors = &_pointCols[0];
                }
                res = checkOneGeneralInputArgument(L, 9, lua_arg_number, pointCnt * 3, true, true, &errorString);
                if (res >= 0)
                {
                    double* pointNormals = nullptr;
                    std::vector<double> _pointNormals;
                    if (res == 2)
                    {
                        _pointNormals.resize(pointCnt * 3, 0);
                        getDoublesFromTable(L, 9, pointCnt * 3, &_pointNormals[0]);
                        pointNormals = &_pointNormals[0];
                    }
                    retVal = simAddPointCloud_internal(pageMask, layerMask, objectHandle, options, pointSize,
                                                       (int)pointCoordinates.size() / 3, &pointCoordinates[0],
                                                       (char*)defaultColors, (char*)pointColors, pointNormals);
                }
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simModifyPointCloud(luaWrap_lua_State* L)
{ // deprecated on 23.11.2020
    TRACE_LUA_API;
    LUA_START("sim.modifyPointCloud");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int pointCloudHandle = luaToInt(L, 1);
        int operation = luaToInt(L, 2);
        retVal = simModifyPointCloud_internal(pointCloudHandle, operation, nullptr, nullptr);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simCopyMatrix(luaWrap_lua_State* L)
{ // deprecated on 23.11.2020
    TRACE_LUA_API;
    LUA_START("sim.copyMatrix");

    if (checkInputArguments(L, &errorString, lua_arg_number, 12))
    {
        double arr[12];
        getDoublesFromTable(L, 1, 12, arr);
        pushDoubleTableOntoStack(L, 12, arr);
        LUA_END(1);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simGetObjectInt32Parameter(luaWrap_lua_State* L)
{ // deprecated on 22.04.2021
    TRACE_LUA_API;
    LUA_START("sim.getObjectInt32Parameter");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int param;
        retVal = simGetObjectInt32Param_internal(luaToInt(L, 1), luaToInt(L, 2), &param);
        if (retVal > 0)
        {
            luaWrap_lua_pushinteger(L, retVal);
            luaWrap_lua_pushinteger(L, param);
            LUA_END(2);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetObjectFloatParameter(luaWrap_lua_State* L)
{ // deprecated on 22.04.2021
    TRACE_LUA_API;
    LUA_START("sim.getObjectFloatParameter");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        double param;
        retVal = simGetObjectFloatParam_internal(luaToInt(L, 1), luaToInt(L, 2), &param);
        if (retVal > 0)
        {
            luaWrap_lua_pushinteger(L, retVal);
            luaWrap_lua_pushnumber(L, param);
            LUA_END(2);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simIsHandleValid(luaWrap_lua_State* L)
{ // deprecated on 23.04.2021
    TRACE_LUA_API;
    LUA_START("sim.isHandleValid");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int objType = -1;
        int res = checkOneGeneralInputArgument(L, 2, lua_arg_number, 0, true, false, &errorString);
        if ((res == 0) || (res == 2))
        {
            if (res == 2)
                objType = luaToInt(L, 2);
            retVal = simIsHandle_internal(luaToInt(L, 1), objType);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetObjectName(luaWrap_lua_State* L)
{ // deprecated on 08.06.2021
    TRACE_LUA_API;
    LUA_START("sim.getObjectName");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        char* name = simGetObjectName_internal(luaToInt(L, 1));
        if (name != nullptr)
        {
            luaWrap_lua_pushtext(L, name);
            simReleaseBuffer_internal(name);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetObjectName(luaWrap_lua_State* L)
{ // deprecated on 08.06.2021
    TRACE_LUA_API;
    LUA_START("sim.setObjectName");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_string, 0))
        retVal = simSetObjectName_internal(luaToInt(L, 1), luaWrap_lua_tostring(L, 2));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetScriptName(luaWrap_lua_State* L)
{ // deprecated on 08.06.2021
    TRACE_LUA_API;
    LUA_START("sim.getScriptName");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int a = luaToInt(L, 1);
        if (a == sim_handle_self)
            a = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
        char* name = simGetScriptName_internal(a);
        if (name != nullptr)
        {
            luaWrap_lua_pushtext(L, name);
            simReleaseBuffer_internal(name);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetScriptVariable(luaWrap_lua_State* L)
{ // deprecated on 16.06.2021
    TRACE_LUA_API;
    LUA_START("sim.setScriptVariable");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_string, 0, lua_arg_number, 0))
    {
        std::string varAndScriptName(luaWrap_lua_tostring(L, 1));
        int scriptHandleOrType = luaToInt(L, 2);
        int numberOfArguments = luaWrap_lua_gettop(L);
        if (numberOfArguments >= 3)
        {
            CInterfaceStack* stack = App::worldContainer->interfaceStackContainer->createStack();
            CScriptObject::buildFromInterpreterStack_lua(L, stack, 3, 1);
            retVal = simSetScriptVariable_internal(scriptHandleOrType, varAndScriptName.c_str(), stack->getId());
            App::worldContainer->interfaceStackContainer->destroyStack(stack);
        }
        else
            errorString = SIM_ERROR_FUNCTION_REQUIRES_MORE_ARGUMENTS;
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetObjectAssociatedWithScript(luaWrap_lua_State* L)
{ // deprecated on 18.06.2021
    TRACE_LUA_API;
    LUA_START("sim.getObjectAssociatedWithScript");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int a = luaToInt(L, 1);
        if (a == sim_handle_self)
            a = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
        retVal = simGetObjectAssociatedWithScript_internal(a);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetScriptAssociatedWithObject(luaWrap_lua_State* L)
{ // deprecated on 18.06.2021
    TRACE_LUA_API;
    LUA_START("sim.getScriptAssociatedWithObject");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
        retVal = simGetScriptAssociatedWithObject_internal(luaToInt(L, 1));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetCustomizationScriptAssociatedWithObject(luaWrap_lua_State* L)
{ // deprecated on 18.06.2021
    TRACE_LUA_API;
    LUA_START("sim.getCustomizationScriptAssociatedWithObject");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
        retVal = simGetCustomizationScriptAssociatedWithObject_internal(luaToInt(L, 1));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetObjectConfiguration(luaWrap_lua_State* L)
{ // deprecated on 18.06.2021
    TRACE_LUA_API;
    LUA_START("sim.getObjectConfiguration");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        char* data = simGetObjectConfiguration_internal(luaToInt(L, 1));
        if (data != nullptr)
        {
            int dataSize = ((int*)data)[0] + 4;
            luaWrap_lua_pushbuffer(L, data, dataSize);
            delete[] data;
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetObjectConfiguration(luaWrap_lua_State* L)
{ // deprecated on 18.06.2021
    TRACE_LUA_API;
    LUA_START("sim.setObjectConfiguration");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_string, 0))
    {
        size_t l;
        const char* data = luaWrap_lua_tobuffer(L, 1, &l);
        retVal = simSetObjectConfiguration_internal(data);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetConfigurationTree(luaWrap_lua_State* L)
{ // deprecated on 18.06.2021
    TRACE_LUA_API;
    LUA_START("sim.getConfigurationTree");

    CScriptObject* it =
        App::worldContainer->getScriptObjectFromHandle(CScriptObject::getScriptHandleFromInterpreterState_lua(L));
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int id = luaToInt(L, 1);
        if (id == sim_handle_self)
        {
            int objID = it->getObjectHandleThatScriptIsAttachedTo(sim_scripttype_simulation);
            id = objID;
            if (id != -1)
            {
                CScript* s = App::currentWorld->sceneObjects->getScriptFromHandle(id);
                if (s != nullptr)
                {
                    if (s->scriptObject->getParentIsProxy())
                    {
                        CSceneObject* o = s->getParent();
                        if (o != nullptr)
                            id = o->getObjectHandle();
                        else
                            id = -1;
                    }
                }
            }
            if (id == -1)
                errorString = SIM_ERROR_ARGUMENT_VALID_ONLY_WITH_CHILD_SCRIPTS;
        }
        if (id != -1)
        {
            char* data = simGetConfigurationTree_internal(id);
            if (data != nullptr)
            {
                int dataSize = ((int*)data)[0] + 4;
                luaWrap_lua_pushbuffer(L, data, dataSize);
                delete[] data;
                LUA_END(1);
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetConfigurationTree(luaWrap_lua_State* L)
{ // deprecated on 18.06.2021
    TRACE_LUA_API;
    LUA_START("sim.setConfigurationTree");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_string, 0))
    {
        size_t l;
        const char* data = luaWrap_lua_tobuffer(L, 1, &l);
        retVal = simSetConfigurationTree_internal(data);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetObjectSizeValues(luaWrap_lua_State* L)
{ // deprecated on 28.06.2021
    TRACE_LUA_API;
    LUA_START("sim.setObjectSizeValues");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 3))
    {
        int handle = luaToInt(L, 1);
        double s[3];
        getDoublesFromTable(L, 2, 3, s);
        retVal = simSetObjectSizeValues_internal(handle, s);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetObjectSizeValues(luaWrap_lua_State* L)
{ // deprecated on 28.06.2021
    TRACE_LUA_API;
    LUA_START("sim.getObjectSizeValues");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int handle = luaToInt(L, 1);
        double s[3];
        if (simGetObjectSizeValues_internal(handle, s) != -1)
        {
            pushDoubleTableOntoStack(L, 3, s);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simOpenModule(luaWrap_lua_State* L)
{ // deprecated in 2019-2020 sometimes
    TRACE_LUA_API;
    LUA_START("sim.openModule");

    moduleCommonPart_old(L, sim_message_eventcallback_moduleopen, &errorString);

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(1);
}
int _simCloseModule(luaWrap_lua_State* L)
{ // deprecated in 2019-2020 sometimes
    TRACE_LUA_API;
    LUA_START("sim.closeModule");

    moduleCommonPart_old(L, sim_message_eventcallback_moduleclose, &errorString);

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(1);
}
int _simHandleModule(luaWrap_lua_State* L)
{ // deprecated in 2019-2020 sometimes
    TRACE_LUA_API;
    LUA_START_NO_CSIDE_ERROR("sim.handleModule");
    bool sensingPart = false;
    int res = checkOneGeneralInputArgument(L, 2, lua_arg_bool, 0, true, false, &errorString);

    if ((res == 0) || (res == 2))
    {
        if (res == 2)
            sensingPart = luaToBool(L, 2);
        if (sensingPart)
            moduleCommonPart_old(L, sim_message_eventcallback_modulehandleinsensingpart, &errorString);
        else
            moduleCommonPart_old(L, sim_message_eventcallback_modulehandle, &errorString);
    }
    else
        luaWrap_lua_pushinteger(L, -1);

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(1);
}
void moduleCommonPart_old(luaWrap_lua_State* L, int action, std::string* errorString)
{ // deprecated in 2019-2020 sometimes
    TRACE_LUA_API;
    std::string functionName;
    if (action == sim_message_eventcallback_moduleopen)
        functionName = "sim.openModule";
    if (action == sim_message_eventcallback_moduleclose)
        functionName = "sim.closeModule";
    if ((action == sim_message_eventcallback_modulehandle) ||
        (action == sim_message_eventcallback_modulehandleinsensingpart))
        functionName = "sim.handleModule";
    int currentScriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
    CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(currentScriptID);
    if (it->getScriptType() != sim_scripttype_main)
    {
        if (errorString != nullptr)
            errorString->assign(SIM_ERROR_CAN_ONLY_BE_CALLED_FROM_MAIN_SCRIPT);
        luaWrap_lua_pushinteger(L, -1);
    }
    else
    {
        bool handleAll = false;
        if (luaWrap_lua_isnumber(L, 1))
        { // We try to check whether we have sim_handle_all as a number:
            if (luaToInt(L, 1) == sim_handle_all)
            {
                handleAll = true;
                App::worldContainer->pluginContainer->sendEventCallbackMessageToAllPlugins(action);
                luaWrap_lua_pushinteger(L, 1);
            }
        }
        if (!handleAll)
            luaWrap_lua_pushinteger(L, 1);
    }
}
int _simGetLastError(luaWrap_lua_State* L)
{ // deprecated on 01.07.2021
    TRACE_LUA_API;
    LUA_START("sim.getLastError");

    int scriptHandle = -1;
    if (luaWrap_lua_gettop(L) != 0)
    {
        if (checkInputArguments(L, &errorString, lua_arg_number, 0))
            scriptHandle = luaToInt(L, 1);
    }
    else
        scriptHandle = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
    CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(scriptHandle);
    if (it != nullptr)
    {
        luaWrap_lua_pushtext(L, it->getAndClearLastError_old().c_str());
        LUA_END(1);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}
int _simSwitchThread(luaWrap_lua_State* L)
{ // now implemented in Lua, except for old threads. Deprecated since V4.2.0
    TRACE_LUA_API;
    LUA_START("sim._switchThread");

    int retVal = -1;
    int currentScriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
    CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(currentScriptID);
    if ((it != nullptr) && (it->canManualYield()))
    {
        it->resetScriptExecutionTime();
        if (CThreadPool_old::switchBackToPreviousThread())
            retVal = 1;
        else
            retVal = 0;
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}
int _simFileDialog(luaWrap_lua_State* L)
{ // deprecated
    TRACE_LUA_API;
    LUA_START("sim.fileDialog");
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_string, 0, lua_arg_string, 0, lua_arg_string, 0,
                            lua_arg_string, 0, lua_arg_string, 0))
    {
        int mode = luaToInt(L, 1);
        std::string title(luaWrap_lua_tostring(L, 2));
        std::string startPath(luaWrap_lua_tostring(L, 3));
        std::string initName(luaWrap_lua_tostring(L, 4));
        std::string extName(luaWrap_lua_tostring(L, 5));
        std::string ext(luaWrap_lua_tostring(L, 6));
        char* pathAndName = simFileDialog_internal(mode, title.c_str(), startPath.c_str(), initName.c_str(),
                                                   extName.c_str(), ext.c_str());
        if (pathAndName != nullptr)
        {
            luaWrap_lua_pushtext(L, pathAndName);
            simReleaseBuffer_internal(pathAndName);
            LUA_END(1);
        }
    }
    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}
int _simMsgBox(luaWrap_lua_State* L)
{ // deprecated
    TRACE_LUA_API;
    LUA_START("sim.msgBox");
    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_string, 0, lua_arg_string,
                            0))
    {
        int dlgType = luaToInt(L, 1);
        int dlgButtons = luaToInt(L, 2);
        std::string title(luaWrap_lua_tostring(L, 3));
        std::string message(luaWrap_lua_tostring(L, 4));
        retVal = simMsgBox_internal(dlgType, dlgButtons, title.c_str(), message.c_str());
    }
    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simIsObjectInSelection(luaWrap_lua_State* L)
{ // deprecated since 24.09.2021
    TRACE_LUA_API;
    LUA_START("sim.isObjectInSelection");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
        retVal = simIsObjectInSelection_internal(luaToInt(L, 1));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simAddObjectToSelection(luaWrap_lua_State* L)
{ // deprecated since 24.09.2021
    TRACE_LUA_API;
    LUA_START("sim.addObjectToSelection");

    int retVal = -1; // error
    // We check if argument 1 is nil (special case):
    if (checkOneGeneralInputArgument(L, 1, lua_arg_nil, 0, false, true, nullptr) ==
        1) // we do not generate an error message!
    {
        retVal = 1; // nothing happens
    }
    else
    {
        // We check if we have a table at position 1:
        if (!luaWrap_lua_isnonbuffertable(L, 1))
        {                                                                              // It is not a table!
            if (checkInputArguments(L, nullptr, lua_arg_number, 0, lua_arg_number, 0)) // we don't generate an error
                retVal = simAddObjectToSelection_internal(luaToInt(L, 1), luaToInt(L, 2));
            else
            { // Maybe we have a special case with one argument only?
                // nil is a valid argument!
                if (checkInputArguments(L, nullptr, lua_arg_nil, 0)) // we don't generate an error
                    retVal = 1;
                else
                {
                    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
                    {
                        if (luaToInt(L, 1) == sim_handle_all)
                            retVal = simAddObjectToSelection_internal(luaToInt(L, 1), -1);
                        else
                            checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number,
                                                0); // we just generate an error
                    }
                }
            }
        }
        else
        { // Ok we have a table. Now what size is it?
            int tableLen = int(luaWrap_lua_rawlen(L, 1));
            int* buffer = new int[tableLen];
            if (getIntsFromTable(L, 1, tableLen, buffer))
            {
                for (int i = 0; i < tableLen; i++)
                {
                    if (App::currentWorld->sceneObjects->getObjectFromHandle(buffer[i]) != nullptr)
                        App::currentWorld->sceneObjects->addObjectToSelection(buffer[i]);
                }
                retVal = 1;
            }
            else
                errorString = SIM_ERROR_TABLE_CONTAINS_INVALID_TYPES;
            delete[] buffer;
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simRemoveObjectFromSelection(luaWrap_lua_State* L)
{ // deprecated since 24.09.2021
    TRACE_LUA_API;
    LUA_START("sim.removeObjectFromSelection");

    int retVal = -1; // error
    // We check if argument 1 is nil (special case):
    if (checkOneGeneralInputArgument(L, 1, lua_arg_nil, 0, false, true, nullptr) ==
        1)          // we do not generate an error message!
        retVal = 1; // nothing happens
    else
    {
        // We check if we have a table at position 1:
        if (!luaWrap_lua_isnonbuffertable(L, 1))
        {                                                                              // It is not a table!
            if (checkInputArguments(L, nullptr, lua_arg_number, 0, lua_arg_number, 0)) // we don't generate an error
                retVal = simRemoveObjectFromSelection_internal(luaToInt(L, 1), luaToInt(L, 2));
            else
            {
                if (checkInputArguments(L, &errorString, lua_arg_number, 0))
                {
                    if (luaToInt(L, 1) == sim_handle_all)
                        retVal = simRemoveObjectFromSelection_internal(luaToInt(L, 1), -1);
                    else
                        checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number,
                                            0); // we just generate an error
                }
            }
        }
        else
        { // Ok we have a table. Now what size is it?
            int tableLen = int(luaWrap_lua_rawlen(L, 1));
            int* buffer = new int[tableLen];
            if (getIntsFromTable(L, 1, tableLen, buffer))
            {
                for (int i = 0; i < tableLen; i++)
                    retVal = simRemoveObjectFromSelection_internal(sim_handle_single, buffer[i]);
            }
            else
                errorString = SIM_ERROR_TABLE_CONTAINS_INVALID_TYPES;
            delete[] buffer;
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetObjectUniqueIdentifier(luaWrap_lua_State* L)
{ // deprecated since 08.10.2021
    TRACE_LUA_API;
    LUA_START("sim.getObjectUniqueIdentifier");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int handle = luaToInt(L, 1);
        if (handle != sim_handle_all)
        {
            int retVal;
            if (simGetObjectUniqueIdentifier_internal(handle, &retVal) != -1)
            {
                luaWrap_lua_pushinteger(L, retVal);
                LUA_END(1);
            }
        }
        else
        { // for backward compatibility
            int cnt = int(App::currentWorld->sceneObjects->getObjectCount());
            int* buffer = new int[cnt];
            if (simGetObjectUniqueIdentifier_internal(handle, buffer) != -1)
            {
                pushIntTableOntoStack(L, cnt, buffer);
                delete[] buffer;
                LUA_END(1);
            }
            delete[] buffer;
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simBreakForceSensor(luaWrap_lua_State* L)
{ // deprecated since 08.11.2021
    TRACE_LUA_API;
    LUA_START("sim.breakForceSensor");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
        retVal = simBreakForceSensor_internal(luaToInt(L, 1));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetSphericalJointMatrix(luaWrap_lua_State* L)
{ // deprecated since 09.11.2021
    TRACE_LUA_API;
    LUA_START("sim.setSphericalJointMatrix");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 12))
    {
        double arr[12];
        getDoublesFromTable(L, 2, 12, arr);
        retVal = simSetSphericalJointMatrix_internal(luaToInt(L, 1), arr);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetJointMatrix(luaWrap_lua_State* L)
{ // deprecated since 09.11.2021
    TRACE_LUA_API;
    LUA_START("sim.getJointMatrix");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        double arr[12];
        if (simGetJointMatrix_internal(luaToInt(L, 1), arr) == 1)
        {
            pushDoubleTableOntoStack(L, 12, arr); // Success
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _sim_getObjectHandle(luaWrap_lua_State* L)
{ // deprecated on 03.12.2021
    TRACE_LUA_API;
    LUA_START("sim._getObjectHandle");

    int retVal = -1; // means error

    bool checkWithString = true;
    if (checkInputArguments(L, nullptr, lua_arg_integer, 0)) // do not output error if not string
    {                                                        // argument sim.handle_self
        if (luaToInt(L, 1) == sim_handle_self)
        {
            checkWithString = false;
            int a = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
            if (a <= SIM_IDEND_SCENEOBJECT)
            { // is a CScript
                CScriptObject* it = App::currentWorld->sceneObjects->getScriptObjectFromHandle(a);
                if (it->getParentIsProxy())
                {
                    CSceneObject* obj = App::currentWorld->sceneObjects->getObjectFromHandle(a);
                    obj = obj->getParent();
                    if (obj != nullptr)
                        retVal = obj->getObjectHandle();
                    else
                        retVal = -1;
                }
                else
                    retVal = a;
            }
            else
                retVal = simGetObjectAssociatedWithScript_internal(a);
        }
    }
    if (checkWithString)
    {
        if (checkInputArguments(L, &errorString, lua_arg_string, 0))
        {
            int index = -1;
            int res = checkOneGeneralInputArgument(L, 2, lua_arg_number, 0, true, false, &errorString);
            if (res >= 0)
            {
                if (res == 2)
                    index = luaToInt(L, 2);
                int proxyForSearch = -1;
                res = checkOneGeneralInputArgument(L, 3, lua_arg_number, 0, true, false, &errorString);
                if (res >= 0)
                {
                    if (res == 2)
                        proxyForSearch = luaToInt(L, 3);

                    int options = 0;
                    res = checkOneGeneralInputArgument(L, 4, lua_arg_number, 0, true, false, &errorString);
                    if (res >= 0)
                    {
                        if (res == 2)
                            options = luaToInt(L, 4);
                        std::string name(luaWrap_lua_tostring(L, 1));
                        setCurrentScriptInfo_cSide(
                            CScriptObject::getScriptHandleFromInterpreterState_lua(L),
                            CScriptObject::getScriptNameIndexFromInterpreterState_lua_old(
                                L)); // for transmitting to the master function additional info (e.g.for autom. name
                                     // adjustment, or for autom. object deletion when script ends)
                        retVal = simGetObjectHandleEx_internal(name.c_str(), index, proxyForSearch, options);
                        setCurrentScriptInfo_cSide(-1, -1);
                    }
                }
            }
        }
    }
    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetScriptAttribute(luaWrap_lua_State* L)
{ // deprecated on 05.01.2022
    TRACE_LUA_API;
    LUA_START("sim.setScriptAttribute");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int scriptID = luaToInt(L, 1);
        if (scriptID == sim_handle_self)
            scriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
        int attribID = luaToInt(L, 2);
        int thirdArgType = lua_arg_number;
        if ((attribID == sim_customizationscriptattribute_activeduringsimulation) ||
            (attribID == sim_childscriptattribute_automaticcascadingcalls) ||
            (attribID == sim_scriptattribute_enabled) ||
            (attribID == sim_customizationscriptattribute_cleanupbeforesave))
            thirdArgType = lua_arg_bool;

        if ((attribID == sim_scriptattribute_executionorder) || (attribID == sim_scriptattribute_executioncount) ||
            (attribID == sim_scriptattribute_debuglevel))
            thirdArgType = lua_arg_number;
        int res = checkOneGeneralInputArgument(L, 3, thirdArgType, 0, false, false, &errorString);
        if (res == 2)
        {
            if ((attribID == sim_customizationscriptattribute_activeduringsimulation) ||
                (attribID == sim_childscriptattribute_automaticcascadingcalls) ||
                (attribID == sim_scriptattribute_enabled) ||
                (attribID == sim_customizationscriptattribute_cleanupbeforesave))
                retVal = simSetScriptAttribute_internal(scriptID, attribID, 0.0, luaToBool(L, 3));
            if ((attribID == sim_scriptattribute_executionorder) || (attribID == sim_scriptattribute_executioncount) ||
                (attribID == sim_scriptattribute_debuglevel))
                retVal = simSetScriptAttribute_internal(scriptID, attribID, 0.0, luaToInt(L, 3));
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetScriptAttribute(luaWrap_lua_State* L)
{ // deprecated on 05.01.2022
    TRACE_LUA_API;
    LUA_START("sim.getScriptAttribute");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int scriptID = luaToInt(L, 1);
        if (scriptID == sim_handle_self)
            scriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
        int attribID = luaToInt(L, 2);
        int intVal;
        double floatVal;
        int result = simGetScriptAttribute_internal(scriptID, attribID, &floatVal, &intVal);
        if (result != -1)
        {
            if ((attribID == sim_customizationscriptattribute_activeduringsimulation) ||
                (attribID == sim_childscriptattribute_automaticcascadingcalls) ||
                (attribID == sim_scriptattribute_enabled) ||
                (attribID == sim_customizationscriptattribute_cleanupbeforesave))
                luaWrap_lua_pushboolean(L, intVal);
            if ((attribID == sim_scriptattribute_executionorder) || (attribID == sim_scriptattribute_executioncount) ||
                (attribID == sim_scriptattribute_scripttype) || (attribID == sim_scriptattribute_scripthandle))
                luaWrap_lua_pushinteger(L, intVal);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetScriptText(luaWrap_lua_State* L)
{ // deprecated on 04.02.2022
    TRACE_LUA_API;
    LUA_START("sim.setScriptText");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_string, 0))
    {
        int scriptHandle = luaToInt(L, 1);
        std::string scriptText(luaWrap_lua_tostring(L, 2));
        retVal = simSetScriptText_internal(scriptHandle, scriptText.c_str());
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetJointMaxForce(luaWrap_lua_State* L)
{ // deprecated on 24.02.2022
    TRACE_LUA_API;
    LUA_START("sim.getJointMaxForce");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        double jointF[1];
        if (simGetJointMaxForce_internal(luaToInt(L, 1), jointF) > 0)
        {
            luaWrap_lua_pushnumber(L, jointF[0]);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetJointMaxForce(luaWrap_lua_State* L)
{ // deprecated on 24.02.2022
    TRACE_LUA_API;
    LUA_START("sim.setJointMaxForce");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
        retVal = simSetJointMaxForce_internal(luaToInt(L, 1), luaToDouble(L, 2));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simRemoveObject(luaWrap_lua_State* L)
{ // deprecated on 07.03.2022
    TRACE_LUA_API;
    LUA_START("sim.removeObject");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int objId = luaToInt(L, 1);
        int currentScriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
        CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(currentScriptID);
        if (!it->getThreadedExecution_oldThreads())
            retVal = simRemoveObject_internal(objId);
        else
        { // this script runs threaded and wants to destroy another object (than itself probably). We need to make sure
            // that it will only destroy objects that do not have any scripts attached with a non-nullptr lua state:
            std::vector<CScriptObject*> scripts;
            App::currentWorld->sceneObjects->embeddedScriptContainer->getScriptsFromObjectAttachedTo(objId, scripts);
            bool ok = true;
            for (size_t i = 0; i < scripts.size(); i++)
            {
                if ((it != scripts[i]) && scripts[i]->hasInterpreterState())
                    ok = false;
            }
            if (ok)
                retVal = simRemoveObject_internal(objId);
            else
                errorString = SIM_ERROR_THREADED_SCRIPT_DESTROYING_OBJECTS_WITH_ACTIVE_SCRIPTS;
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetSystemTimeInMs(luaWrap_lua_State* L)
{ // deprecated on 01.04.2022
    TRACE_LUA_API;
    LUA_START("sim.getSystemTimeInMs");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int lastTime = luaToInt(L, 1);
        luaWrap_lua_pushinteger(L, simGetSystemTimeInMs_internal(lastTime));
        LUA_END(1);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simGetVisionSensorResolution(luaWrap_lua_State* L)
{ // deprecated on 11.04.2022
    TRACE_LUA_API;
    LUA_START("sim.getVisionSensorResolution");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int resolution[2];
        if (simGetVisionSensorRes_internal(luaToInt(L, 1), resolution) == 1)
        {
            pushIntTableOntoStack(L, 2, resolution);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simGetVisionSensorImage(luaWrap_lua_State* L)
{ // deprecated on 11.04.2022
    TRACE_LUA_API;
    LUA_START("sim.getVisionSensorImage");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int arg1 = luaToInt(L, 1);
        int handleFlags = arg1 & 0xff00000;
        int objectHandle = arg1 & 0xfffff;
        int valPerPix = 3;
        int rgbOrGreyOrDepth = 0;
        if ((handleFlags & sim_handleflag_greyscale) != 0)
        {
            valPerPix = 1;
            rgbOrGreyOrDepth = 1;
        }
        int posX = 0;
        int posY = 0;
        int sizeX = 0;
        int sizeY = 0;
        int retType = 0;
        // Now check the optional arguments:
        int res;
        res = checkOneGeneralInputArgument(L, 2, lua_arg_number, 0, true, false, &errorString);
        if ((res == 0) || (res == 2))
        {
            if (res == 2)
                posX = luaToInt(L, 2);
            res = checkOneGeneralInputArgument(L, 3, lua_arg_number, 0, true, false, &errorString);
            if ((res == 0) || (res == 2))
            {
                if (res == 2)
                    posY = luaToInt(L, 3);
                res = checkOneGeneralInputArgument(L, 4, lua_arg_number, 0, true, false, &errorString);
                if ((res == 0) || (res == 2))
                {
                    if (res == 2)
                        sizeX = luaToInt(L, 4);
                    res = checkOneGeneralInputArgument(L, 5, lua_arg_number, 0, true, false, &errorString);
                    if ((res == 0) || (res == 2))
                    {
                        if (res == 2)
                            sizeY = luaToInt(L, 5);
                        res = checkOneGeneralInputArgument(L, 6, lua_arg_number, 0, true, false, &errorString);
                        if ((res == 0) || (res == 2))
                        {
                            if (res == 2)
                                retType = luaToInt(L, 6);
                            CVisionSensor* rs =
                                App::currentWorld->sceneObjects->getVisionSensorFromHandle(objectHandle);
                            if (rs != nullptr)
                            {
                                if ((sizeX == 0) && (sizeY == 0))
                                { // we have default values here (the whole picture)
                                    int reso[2];
                                    rs->getResolution(reso);
                                    sizeX = reso[0];
                                    sizeY = reso[1];
                                }
                                float* buffer = rs->readPortionOfImage(posX, posY, sizeX, sizeY, rgbOrGreyOrDepth);
                                if (buffer != nullptr)
                                {
                                    if (retType == 0)
                                        pushFloatTableOntoStack(L, sizeX * sizeY * valPerPix, buffer);
                                    else
                                    { // here we return RGB data in a string
                                        char* str = new char[sizeX * sizeY * valPerPix];
                                        int vvv = sizeX * sizeY * valPerPix;
                                        for (int i = 0; i < vvv; i++)
                                            str[i] = char(buffer[i] * 255.0001);
                                        luaWrap_lua_pushbuffer(L, (const char*)str, vvv);
                                        delete[]((char*)str);
                                    }
                                    delete[]((char*)buffer);
                                    LUA_END(1);
                                }
                                else
                                    errorString = SIM_ERROR_INVALID_ARGUMENTS;
                            }
                            else
                                errorString = SIM_ERROR_VISION_SENSOR_INEXISTANT;
                        }
                    }
                }
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetVisionSensorImage(luaWrap_lua_State* L)
{ // deprecated on 11.04.2022
    TRACE_LUA_API;
    LUA_START("sim.setVisionSensorImage");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int arg1 = luaToInt(L, 1);
        int handleFlags = arg1 & 0xff00000;
        int sensHandle = arg1 & 0xfffff;
        int valPerPix = 3;
        bool noProcessing = false;
        bool setDepthBufferInstead = false;
        if ((handleFlags & sim_handleflag_greyscale) != 0)
            valPerPix = 1;
        if ((handleFlags & sim_handleflag_rawvalue) != 0)
            noProcessing = true;
        if ((handleFlags & sim_handleflag_depthbuffer) != 0)
            setDepthBufferInstead = true;
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(sensHandle);
        if (it != nullptr)
        { // Ok we have a valid object
            if (it->getObjectType() == sim_sceneobject_visionsensor)
            { // ok we have a valid vision sensor
                int res[2];
                CVisionSensor* rendSens = (CVisionSensor*)it;
                rendSens->getResolution(res);
                // We check if we have a table or string at position 2:
                bool notTableNorString = true;
                if (luaWrap_lua_isnonbuffertable(L, 2))
                { // Ok we have a table. Now what size is it?
                    notTableNorString = false;
                    if (setDepthBufferInstead)
                    {
                        // Now we check if the provided table has correct size:
                        if (int(luaWrap_lua_rawlen(L, 2)) >= res[0] * res[1])
                        {
                            float* img = new float[res[0] * res[1]];
                            getFloatsFromTable(L, 2, res[0] * res[1], img);
                            rendSens->setDepthBuffer(img);
                            retVal = 1;
                            delete[] img;
                        }
                        else
                            errorString = SIM_ERROR_ONE_TABLE_SIZE_IS_WRONG;
                    }
                    else
                    {
                        // Now we check if the provided table has correct size:
                        if (int(luaWrap_lua_rawlen(L, 2)) >= res[0] * res[1] * valPerPix)
                        {
                            float* img = new float[res[0] * res[1] * valPerPix];
                            getFloatsFromTable(L, 2, res[0] * res[1] * valPerPix,
                                               img); // we do the operation directly without going through the c-api
                            if (rendSens->setExternalImage_old(img, valPerPix == 1, noProcessing))
                                retVal = 1;
                            delete[] img;
                        }
                        else
                            errorString = SIM_ERROR_ONE_TABLE_SIZE_IS_WRONG;
                    }
                }
                if (luaWrap_lua_isstring(L, 2))
                { // Ok we have a string. Now what size is it?
                    notTableNorString = false;
                    // Now we check if the provided string has correct size:
                    size_t dataLength;
                    char* data = (char*)luaWrap_lua_tobuffer(L, 2, &dataLength);
                    if (setDepthBufferInstead)
                    {
                        if (int(dataLength) >= res[0] * res[1] * sizeof(float))
                        {
                            rendSens->setDepthBuffer((float*)data);
                            retVal = 1;
                        }
                        else
                            errorString = SIM_ERROR_INCORRECT_BUFFER_SIZE;
                    }
                    else
                    {
                        if (int(dataLength) >= res[0] * res[1] * valPerPix)
                        {
                            float* img = new float[res[0] * res[1] * valPerPix];
                            for (int i = 0; i < res[0] * res[1] * valPerPix; i++)
                                img[i] = float(data[i]) / 255.0;
                            if (rendSens->setExternalImage_old(img, valPerPix == 1, noProcessing))
                                retVal = 1;
                            delete[] img;
                        }
                        else
                            errorString = SIM_ERROR_INCORRECT_BUFFER_SIZE;
                    }
                }
                if (notTableNorString)
                    errorString = SIM_ERROR_ONE_ARGUMENT_TYPE_IS_WRONG;
            }
            else
                errorString = SIM_ERROR_OBJECT_NOT_VISION_SENSOR;
        }
        else
            errorString = SIM_ERROR_OBJECT_INEXISTANT;
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetVisionSensorCharImage(luaWrap_lua_State* L)
{ // deprecated on 11.04.2022
    TRACE_LUA_API;
    LUA_START("sim.getVisionSensorCharImage");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int arg1 = luaToInt(L, 1);
        int handleFlags = arg1 & 0xff00000;
        int objectHandle = arg1 & 0xfffff;
        int valPerPix = 3;
        if ((handleFlags & sim_handleflag_greyscale) != 0)
            valPerPix = 1;
        int posX = 0;
        int posY = 0;
        int sizeX = 0;
        int sizeY = 0;
        double rgbaCutOff = 0.0;
        // Now check the optional arguments:
        int res;
        res = checkOneGeneralInputArgument(L, 2, lua_arg_number, 0, true, false, &errorString);
        if ((res == 0) || (res == 2))
        {
            if (res == 2)
                posX = luaToInt(L, 2);
            res = checkOneGeneralInputArgument(L, 3, lua_arg_number, 0, true, false, &errorString);
            if ((res == 0) || (res == 2))
            {
                if (res == 2)
                    posY = luaToInt(L, 3);
                res = checkOneGeneralInputArgument(L, 4, lua_arg_number, 0, true, false, &errorString);
                if ((res == 0) || (res == 2))
                {
                    if (res == 2)
                        sizeX = luaToInt(L, 4);
                    res = checkOneGeneralInputArgument(L, 5, lua_arg_number, 0, true, false, &errorString);
                    if ((res == 0) || (res == 2))
                    {
                        if (res == 2)
                            sizeY = luaToInt(L, 5);
                        res = checkOneGeneralInputArgument(L, 6, lua_arg_number, 0, true, false, &errorString);
                        if ((res == 0) || (res == 2))
                        {
                            if (res == 2)
                                rgbaCutOff = luaToDouble(L, 6);
                            CVisionSensor* rs =
                                App::currentWorld->sceneObjects->getVisionSensorFromHandle(objectHandle);
                            if (rs != nullptr)
                            {
                                int reso[2];
                                rs->getResolution(reso);
                                if ((sizeX == 0) && (sizeY == 0))
                                { // we have default values here (the whole picture)
                                    sizeX = reso[0];
                                    sizeY = reso[1];
                                }
                                int options = 0;
                                if (valPerPix == 1)
                                    options = options | 1;
                                if (rgbaCutOff > 0.0)
                                    options = options | 2;
                                unsigned char* buffer =
                                    rs->readPortionOfCharImage(posX, posY, sizeX, sizeY, rgbaCutOff, valPerPix == 1);
                                if (buffer != nullptr)
                                {
                                    int vvv = sizeX * sizeY * valPerPix;
                                    if (rgbaCutOff > 0.0)
                                    {
                                        if (valPerPix == 1)
                                            vvv = sizeX * sizeY * 2;
                                        else
                                            vvv = sizeX * sizeY * 4;
                                    }
                                    luaWrap_lua_pushbuffer(L, (const char*)buffer, vvv);
                                    delete[]((char*)buffer);
                                    luaWrap_lua_pushinteger(L, reso[0]);
                                    luaWrap_lua_pushinteger(L, reso[1]);
                                    LUA_END(3);
                                }
                                else
                                    errorString = SIM_ERROR_INVALID_ARGUMENTS;
                            }
                            else
                                errorString = SIM_ERROR_VISION_SENSOR_INEXISTANT;
                        }
                    }
                }
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetVisionSensorCharImage(luaWrap_lua_State* L)
{ // deprecated on 11.04.2022
    TRACE_LUA_API;
    LUA_START("sim.setVisionSensorCharImage");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int arg1 = luaToInt(L, 1);
        int handleFlags = arg1 & 0xff00000;
        int sensHandle = arg1 & 0xfffff;
        int valPerPix = 3;
        if ((handleFlags & sim_handleflag_greyscale) != 0)
            valPerPix = 1;
        bool noProcessing = false;
        if ((handleFlags & sim_handleflag_rawvalue) != 0)
            noProcessing = true;
        CSceneObject* it = App::currentWorld->sceneObjects->getObjectFromHandle(sensHandle);
        if (it != nullptr)
        { // Ok we have a valid object
            if (it->getObjectType() == sim_sceneobject_visionsensor)
            { // ok we have a valid vision sensor
                int res[2];
                CVisionSensor* rendSens = (CVisionSensor*)it;
                rendSens->getResolution(res);
                // We check if we have a string at position 2:
                if (luaWrap_lua_isstring(L, 2))
                { // Ok we have a string. Now what size is it?
                    // Now we check if the provided string has correct size:
                    size_t dataLength;
                    char* data = (char*)luaWrap_lua_tobuffer(L, 2, &dataLength);
                    if (int(dataLength) >= res[0] * res[1] * valPerPix)
                    {
                        if (rendSens->setExternalCharImage_old((unsigned char*)data, valPerPix == 1, noProcessing))
                            retVal = 1;
                    }
                    else
                        errorString = SIM_ERROR_INCORRECT_BUFFER_SIZE;
                }
                else
                    errorString = SIM_ERROR_ONE_ARGUMENT_TYPE_IS_WRONG;
            }
            else
                errorString = SIM_ERROR_OBJECT_NOT_VISION_SENSOR;
        }
        else
            errorString = SIM_ERROR_OBJECT_INEXISTANT;
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetVisionSensorDepthBuffer(luaWrap_lua_State* L)
{ // deprecated on 11.04.2022
    TRACE_LUA_API;
    LUA_START("sim.getVisionSensorDepthBuffer");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int posX = 0;
        int posY = 0;
        int sizeX = 0;
        int sizeY = 0;
        // Now check the optional arguments:
        int res;
        res = checkOneGeneralInputArgument(L, 2, lua_arg_number, 0, true, false, &errorString);
        if ((res == 0) || (res == 2))
        {
            if (res == 2)
                posX = luaToInt(L, 2);
            res = checkOneGeneralInputArgument(L, 3, lua_arg_number, 0, true, false, &errorString);
            if ((res == 0) || (res == 2))
            {
                if (res == 2)
                    posY = luaToInt(L, 3);
                res = checkOneGeneralInputArgument(L, 4, lua_arg_number, 0, true, false, &errorString);
                if ((res == 0) || (res == 2))
                {
                    if (res == 2)
                        sizeX = luaToInt(L, 4);
                    res = checkOneGeneralInputArgument(L, 5, lua_arg_number, 0, true, false, &errorString);
                    if ((res == 0) || (res == 2))
                    {
                        if (res == 2)
                            sizeY = luaToInt(L, 5);
                        int sensHandle = luaToInt(L, 1);
                        bool returnString = (sensHandle & sim_handleflag_codedstring) != 0;
                        bool toMeters = (sensHandle & sim_handleflag_depthbuffermeters) != 0;
                        sensHandle = sensHandle & 0xfffff;
                        CVisionSensor* rs = App::currentWorld->sceneObjects->getVisionSensorFromHandle(sensHandle);
                        if (rs != nullptr)
                        {
                            if ((sizeX == 0) && (sizeY == 0))
                            { // we have default values here (the whole picture)
                                int reso[2];
                                rs->getResolution(reso);
                                sizeX = reso[0];
                                sizeY = reso[1];
                            }
                            float* buffer = rs->readPortionOfImage(posX, posY, sizeX, sizeY, 2);
                            if (buffer != nullptr)
                            {
                                if (toMeters)
                                { // Here we need to convert values to distances in meters:
                                    double np, fp;
                                    rs->getClippingPlanes(np, fp);
                                    float n = (float)np;
                                    float f = (float)fp;
                                    float fmn = f - n;
                                    for (int i = 0; i < sizeX * sizeY; i++)
                                        buffer[i] = n + fmn * buffer[i];
                                }
                                if (returnString)
                                    luaWrap_lua_pushbuffer(L, (char*)buffer, sizeX * sizeY * sizeof(float));
                                else
                                    pushFloatTableOntoStack(L, sizeX * sizeY, buffer);
                                delete[]((char*)buffer);
                                LUA_END(1);
                            }
                            else
                                errorString = SIM_ERROR_INVALID_ARGUMENTS;
                        }
                        else
                            errorString = SIM_ERROR_VISION_SENSOR_INEXISTANT;
                    }
                }
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simCreatePureShape(luaWrap_lua_State* L)
{ // deprecated on 27.04.2022
    TRACE_LUA_API;
    LUA_START("sim.createPureShape");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 3, lua_arg_number,
                            0))
    {
        int primitiveType = luaToInt(L, 1);
        int options = luaToInt(L, 2);
        double sizes[3];
        getDoublesFromTable(L, 3, 3, sizes);
        double mass = luaToDouble(L, 4);
        int* precision = nullptr;
        int prec[2];
        int res = checkOneGeneralInputArgument(L, 5, lua_arg_number, 2, true, true, &errorString);
        if (res >= 0)
        {
            if (res == 2)
            {
                getIntsFromTable(L, 5, 2, prec);
                precision = prec;
            }
            retVal = simCreatePureShape_internal(primitiveType, options, sizes, mass, precision);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetScriptHandle(luaWrap_lua_State* L)
{ // deprecated on 06.05.2022
    TRACE_LUA_API;
    LUA_START("sim.getScriptHandle");

    int retVal = -1; // means error
    if (luaWrap_lua_gettop(L) == 0)
        retVal = CScriptObject::getScriptHandleFromInterpreterState_lua(L); // no arguments, return itself
    else
    {
        if (checkInputArguments(L, nullptr, lua_arg_nil, 0))
            retVal = CScriptObject::getScriptHandleFromInterpreterState_lua(
                L); // nil arg, return itself (back. compatibility)
        else
        {
            if (checkInputArguments(L, nullptr, lua_arg_integer, 0))
            { // script type arg.
                int scriptType = luaToInt(L, 1);
                if (scriptType != sim_handle_self)
                {
                    int objectHandle = -1;
                    std::string scriptName;
                    if (scriptType == sim_scripttype_addon)
                    {
                        if (checkInputArguments(L, &errorString, lua_arg_integer, 0, lua_arg_string, 0))
                            scriptName = luaWrap_lua_tostring(L, 2);
                    }
                    if ((scriptType == sim_scripttype_simulation) ||
                        (scriptType == sim_scripttype_customization))
                    {
                        if (checkInputArguments(L, nullptr, lua_arg_integer, 0, lua_arg_integer, 0))
                            objectHandle = luaToInt(L, 2); // back compatibility actually
                        else
                        {
                            if (checkInputArguments(L, &errorString, lua_arg_integer, 0, lua_arg_string, 0))
                            {
                                scriptName = luaWrap_lua_tostring(L, 2);
                                if (scriptName.size() == 0)
                                {
                                    if (checkInputArguments(L, &errorString, lua_arg_integer, 0, lua_arg_string, 0,
                                                            lua_arg_integer, 0))
                                        objectHandle = luaToInt(L, 3);
                                }
                            }
                        }
                    }
                    if (((scriptName.size() > 0) || (objectHandle >= 0)) ||
                        ((scriptType == sim_scripttype_main) || (scriptType == sim_scripttype_sandbox)))
                    {
                        setCurrentScriptInfo_cSide(
                            CScriptObject::getScriptHandleFromInterpreterState_lua(L),
                            CScriptObject::getScriptNameIndexFromInterpreterState_lua_old(
                                L)); // for transmitting to the master function additional info (e.g.for autom. name
                                     // adjustment, or for autom. object deletion when script ends)
                        retVal = simGetScriptHandleEx_internal(scriptType, objectHandle, scriptName.c_str());
                        setCurrentScriptInfo_cSide(-1, -1);
                    }
                }
                else
                    retVal = CScriptObject::getScriptHandleFromInterpreterState_lua(L); // for backward compatibility
            }
            else
            { // string argument, for backward compatibility:
                if (checkInputArguments(L, nullptr, lua_arg_string, 0))
                {
                    std::string name(luaWrap_lua_tostring(L, 1));
                    setCurrentScriptInfo_cSide(
                        CScriptObject::getScriptHandleFromInterpreterState_lua(L),
                        CScriptObject::getScriptNameIndexFromInterpreterState_lua_old(
                            L));                                        // for transmitting to the master function additional info (e.g.for autom. name
                                                                        // adjustment, or for autom. object deletion when script ends)
                    retVal = simGetScriptHandle_internal(name.c_str()); // deprecated func.
                    setCurrentScriptInfo_cSide(-1, -1);
                }
                else
                    checkInputArguments(L, &errorString, lua_arg_integer, 0); // just generate an error
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simHandleCustomizationScripts(luaWrap_lua_State* L)
{ // deprecated on 19.09.2022
    TRACE_LUA_API;
    LUA_START("sim.handleCustomizationScripts");

    int retVal = -1;
    int currentScriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
    CScriptObject* itScrObj = App::worldContainer->getScriptObjectFromHandle(currentScriptID);
    if (itScrObj->getScriptType() == sim_scripttype_main)
    {
        if (checkInputArguments(L, &errorString, lua_arg_number, 0))
        {
            int callType = luaToInt(L, 1);
            retVal = 0;
            int editMode = NO_EDIT_MODE;
#ifdef SIM_WITH_GUI
            editMode = GuiApp::getEditModeType();
#endif
            if (editMode == NO_EDIT_MODE)
            {
                retVal = App::currentWorld->sceneObjects->callScripts_noMainScript(sim_scripttype_customization, callType, nullptr, nullptr);
                App::currentWorld->sceneObjects->embeddedScriptContainer->removeDestroyedScripts(sim_scripttype_customization);
            }
        }
    }
    else
        errorString = SIM_ERROR_CAN_ONLY_BE_CALLED_FROM_MAIN_SCRIPT;

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetDoubleSignal(luaWrap_lua_State* L)
{ // deprecated on 13.10.2022
    TRACE_LUA_API;
    LUA_START("sim.setDoubleSignal");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_string, 0, lua_arg_number, 0))
    {
        setCurrentScriptInfo_cSide(CScriptObject::getScriptHandleFromInterpreterState_lua(L),
                                   CScriptObject::getScriptNameIndexFromInterpreterState_lua_old(
                                       L)); // for transmitting to the master function additional info (e.g.for autom.
                                            // name adjustment, or for autom. object deletion when script ends)
        retVal = simSetDoubleSignalOld_internal(luaWrap_lua_tostring(L, 1), luaToDouble(L, 2));
        setCurrentScriptInfo_cSide(-1, -1);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetDoubleSignal(luaWrap_lua_State* L)
{ // deprecated on 13.10.2022
    TRACE_LUA_API;
    LUA_START("sim.getDoubleSignal");

    if (checkInputArguments(L, &errorString, lua_arg_string, 0))
    {
        double doubleVal;
        if (simGetDoubleSignalOld_internal(std::string(luaWrap_lua_tostring(L, 1)).c_str(), &doubleVal) == 1)
        {
            luaWrap_lua_pushnumber(L, doubleVal);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simClearDoubleSignal(luaWrap_lua_State* L)
{ // deprecated on 13.10.2022
    TRACE_LUA_API;
    LUA_START("sim.clearDoubleSignal");

    int retVal = -1; // error
    int res = checkOneGeneralInputArgument(L, 1, lua_arg_string, 0, true, true, &errorString);
    if (res >= 0)
    {
        if (res != 2)
            retVal = simClearDoubleSignalOld_internal(nullptr); // actually deprecated. No need for that
        else
            retVal = simClearDoubleSignalOld_internal(luaWrap_lua_tostring(L, 1));
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simReorientShapeBoundingBox(luaWrap_lua_State* L)
{ // deprecated on 15.03.2023
    TRACE_LUA_API;
    LUA_START("sim.reorientShapeBoundingBox");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int shapeHandle = luaToInt(L, 1);
        int relativeToHandle = luaToInt(L, 2);
        retVal = simReorientShapeBoundingBox_internal(shapeHandle, relativeToHandle, 0);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simCreateMeshShape(luaWrap_lua_State* L)
{ // deprecated on 15.03.2023
    TRACE_LUA_API;
    LUA_START("sim.createMeshShape");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int options = luaToInt(L, 1);
        double shadingAngle = luaToDouble(L, 2);

        int vl = 2;
        int il = 2;
        if ((luaWrap_lua_gettop(L) >= 4) && luaWrap_lua_isnonbuffertable(L, 3) && luaWrap_lua_isnonbuffertable(L, 4))
        {
            vl = (int)luaWrap_lua_rawlen(L, 3);
            il = (int)luaWrap_lua_rawlen(L, 4);
        }
        int res = checkOneGeneralInputArgument(L, 3, lua_arg_number, vl, false, false, &errorString);
        if (res == 2)
        {
            res = checkOneGeneralInputArgument(L, 4, lua_arg_number, il, false, false, &errorString);
            if (res == 2)
            {
                double* vertices = new double[vl];
                int* indices = new int[il];
                getDoublesFromTable(L, 3, vl, vertices);
                getIntsFromTable(L, 4, il, indices);
                retVal = simCreateMeshShape_internal(options, shadingAngle, vertices, vl, indices, il, nullptr);
                delete[] indices;
                delete[] vertices;
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simInvertMatrix(luaWrap_lua_State* L)
{ // deprecated on 29.03.2023
    TRACE_LUA_API;
    LUA_START("sim.invertMatrix");
    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_number, 12))
    {
        double arr[12];
        getDoublesFromTable(L, 1, 12, arr);
        retVal = simInvertMatrix_internal(arr);
        for (int i = 0; i < 12; i++)
        {
            luaWrap_lua_pushnumber(L, arr[i]);
            luaWrap_lua_rawseti(L, 1, i + 1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simInvertPose(luaWrap_lua_State* L)
{ // deprecated on 29.03.2023
    TRACE_LUA_API;
    LUA_START("sim.invertPose");
    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_number, 7))
    {
        double arr[7];
        getDoublesFromTable(L, 1, 7, arr);
        retVal = simInvertPose_internal(arr);
        for (int i = 0; i < 7; i++)
        {
            luaWrap_lua_pushnumber(L, arr[i]);
            luaWrap_lua_rawseti(L, 1, i + 1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simRegisterScriptFunction(luaWrap_lua_State* L)
{ // deprecated on 19.05.2023
    TRACE_LUA_API;
    LUA_START("sim.registerScriptFunction");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_string, 0, lua_arg_string, 0))
    {
        std::string funcNameAtPluginName(luaWrap_lua_tostring(L, 1));
        std::string ct(luaWrap_lua_tostring(L, 2));

        std::string funcName;
        std::string pluginName;

        size_t p = funcNameAtPluginName.find('@');
        if (p != std::string::npos)
        {
            pluginName.assign(funcNameAtPluginName.begin() + p + 1, funcNameAtPluginName.end());
            funcName.assign(funcNameAtPluginName.begin(), funcNameAtPluginName.begin() + p);
        }
        if (pluginName.size() > 0)
        {
            retVal = 1;
            if (App::worldContainer->scriptCustomFuncAndVarContainer->removeCustomFunction(
                    funcNameAtPluginName.c_str()))
                retVal = 0; // that function already existed. We remove it and replace it!
            CScriptCustomFunction* newFunction =
                new CScriptCustomFunction(funcNameAtPluginName.c_str(), ct.c_str(), nullptr, false);
            if (!App::worldContainer->scriptCustomFuncAndVarContainer->insertCustomFunction(newFunction))
            {
                delete newFunction;
                CApiErrors::setLastWarningOrError(__func__, SIM_ERROR_CUSTOM_LUA_FUNC_COULD_NOT_BE_REGISTERED);
                retVal = -1;
            }
        }
        else
            errorString = SIM_ERROR_MISSING_PLUGIN_NAME;
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simRegisterScriptVariable(luaWrap_lua_State* L)
{ // deprecated on 19.05.2023
    TRACE_LUA_API;
    LUA_START("sim.registerScriptVariable");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_string, 0))
    {
        std::string varNameAtPluginName(luaWrap_lua_tostring(L, 1));
        std::string varName;
        std::string pluginName;

        size_t p = varNameAtPluginName.find('@');
        if (p != std::string::npos)
        {
            pluginName.assign(varNameAtPluginName.begin() + p + 1, varNameAtPluginName.end());
            varName.assign(varNameAtPluginName.begin(), varNameAtPluginName.begin() + p);
        }
        retVal = 1;
        App::worldContainer->scriptCustomFuncAndVarContainer->insertCustomVariable(varNameAtPluginName.c_str(), nullptr,
                                                                                   0);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simIsDeprecated(luaWrap_lua_State* L)
{ // deprecated on 31.05.2023
    TRACE_LUA_API;
    LUA_START("sim.isDeprecated");

    int retVal = 0;

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simLoadModule(luaWrap_lua_State* L)
{ // deprecated on 07.06.2023
    TRACE_LUA_API;
    LUA_START("sim.loadModule");

    int retVal = -3; // means plugin could not be loaded
    if (checkInputArguments(L, &errorString, lua_arg_string, 0, lua_arg_string, 0))
    {
        std::string fileAndPath(luaWrap_lua_tostring(L, 1));
        std::string pluginName(luaWrap_lua_tostring(L, 2));
        retVal = simLoadModule_internal(fileAndPath.c_str(), pluginName.c_str());
        if (retVal >= 0)
        {
            CScriptObject* it =
                App::worldContainer->getScriptObjectFromHandle(CScriptObject::getScriptHandleFromInterpreterState_lua(L));
            it->registerNewFunctions_lua(); // otherwise we can only use the custom Lua functions that the plugin
                                            // registers after this script has re-initialized!
            it->registerPluginFunctions();
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simUnloadModule(luaWrap_lua_State* L)
{ // deprecated on 07.06.2023
    TRACE_LUA_API;
    LUA_START("sim.unloadModule");

    int retVal = 0; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
        retVal = simUnloadModule_internal(luaToInt(L, 1));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetThreadSwitchTimingOLD(luaWrap_lua_State* L)
{ // deprecated on 21.09.2023
    TRACE_LUA_API;
    LUA_START("sim.setThreadSwitchTiming");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int timeInMs = luaToInt(L, 1);
        int currentScriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
        CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(currentScriptID);
        if (it != nullptr)
            it->setDelayForAutoYielding(timeInMs);

        CThreadPool_old::setThreadSwitchTiming(timeInMs);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simConvexDecompose(luaWrap_lua_State* L)
{ // deprecated in June 2024
    TRACE_LUA_API;
    LUA_START("sim.convexDecompose");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int shapeHandle = luaToInt(L, 1);
        int options = luaToInt(L, 2);
        int intParams[10];
        double floatParams[10];
        bool goOn = true;
        if ((options & 4) == 0)
        {
            goOn = false;
            int ipc = 4;
            int fpc = 3;
            if (options & 128)
            {
                ipc = 10;
                fpc = 10;
            }
            int res = checkOneGeneralInputArgument(L, 3, lua_arg_number, ipc, false, false, &errorString);
            if (res == 2)
            {
                res = checkOneGeneralInputArgument(L, 4, lua_arg_number, fpc, false, false, &errorString);
                if (res == 2)
                {
                    getIntsFromTable(L, 3, ipc, intParams);
                    getDoublesFromTable(L, 4, fpc, floatParams);
                    goOn = true;
                }
            }
        }
        intParams[4] = 0;
        floatParams[3] = 0.0;
        floatParams[4] = 0.0;
        if (goOn)
            retVal = simConvexDecompose_internal(shapeHandle, options, intParams, floatParams);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetDecimatedMesh(luaWrap_lua_State* L)
{ // deprecated in June 2024
    TRACE_LUA_API;
    LUA_START("sim.getDecimatedMesh");

    if (checkInputArguments(L, &errorString, lua_arg_number, 9, lua_arg_number, 6, lua_arg_number, 0))
    {
        int vl = (int)luaWrap_lua_rawlen(L, 1);
        int il = (int)luaWrap_lua_rawlen(L, 2);
        double percentage = luaToDouble(L, 3);
        if (checkInputArguments(L, &errorString, lua_arg_number, vl, lua_arg_number, il, lua_arg_number, 0))
        {
            double* vertices = new double[vl];
            getDoublesFromTable(L, 1, vl, vertices);
            int* indices = new int[il];
            getIntsFromTable(L, 2, il, indices);
            double* vertOut;
            int vertOutL;
            int* indOut;
            int indOutL;
            if (simGetDecimatedMesh_internal(vertices, vl, indices, il, &vertOut, &vertOutL, &indOut, &indOutL,
                                             percentage, 0, nullptr))
            {
                pushDoubleTableOntoStack(L, vertOutL, vertOut);
                pushIntTableOntoStack(L, indOutL, indOut);
                delete[] vertOut;
                delete[] indOut;
                LUA_END(2);
            }
            delete[] vertices;
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simAddScript(luaWrap_lua_State* L)
{ // deprecated in June 2024
    TRACE_LUA_API;
    LUA_START("sim.addScript");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int scriptType = luaToInt(L, 1);
        retVal = simAddScript_internal(scriptType);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simAssociateScriptWithObject(luaWrap_lua_State* L)
{ // deprecated in June 2024
    TRACE_LUA_API;
    LUA_START("sim.associateScriptWithObject");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int scriptHandle = luaToInt(L, 1);
        int objectHandle = luaToInt(L, 2);
        retVal = simAssociateScriptWithObject_internal(scriptHandle, objectHandle);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simRemoveScript(luaWrap_lua_State* L)
{ // deprecated in June 2024
    TRACE_LUA_API;
    LUA_START("sim.removeScript");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int handle = luaToInt(L, 1);
        if (handle == sim_handle_self)
            handle = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
        if (sim_handle_all != handle)
            retVal = simRemoveScript_internal(handle);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetScriptInt32Param(luaWrap_lua_State* L)
{ // deprecated in June 2024
    TRACE_LUA_API;
    LUA_START("sim.getScriptInt32Param");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int param;
        int scriptID = luaToInt(L, 1);
        if (scriptID == sim_handle_self)
            scriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
        int retVal = simGetScriptInt32Param_internal(scriptID, luaToInt(L, 2), &param);
        if (retVal > 0)
        {
            luaWrap_lua_pushinteger(L, param);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetScriptInt32Param(luaWrap_lua_State* L)
{ // deprecated in June 2024
    TRACE_LUA_API;
    LUA_START("sim.setScriptInt32Param");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0))
    {
        int scriptID = luaToInt(L, 1);
        if (scriptID == sim_handle_self)
            scriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
        retVal = simSetScriptInt32Param_internal(scriptID, luaToInt(L, 2), luaToInt(L, 3));
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetScriptStringParam(luaWrap_lua_State* L)
{ // deprecated in June 2024
    TRACE_LUA_API;
    LUA_START("sim.getScriptStringParam");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int paramLength;
        int scriptID = luaToInt(L, 1);
        if (scriptID == sim_handle_self)
            scriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
        char* strBuff = simGetScriptStringParam_internal(scriptID, luaToInt(L, 2), &paramLength);
        if (strBuff != nullptr)
        {
            luaWrap_lua_pushbinarystring(L, strBuff, paramLength);
            delete[] strBuff;
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetScriptStringParam(luaWrap_lua_State* L)
{ // deprecated in June 2024
    TRACE_LUA_API;
    LUA_START("sim.setScriptStringParam");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_string, 0))
    {
        int scriptID = luaToInt(L, 1);
        if (scriptID == sim_handle_self)
            scriptID = CScriptObject::getScriptHandleFromInterpreterState_lua(L);
        size_t dataLength;
        char* data = (char*)luaWrap_lua_tobuffer(L, 3, &dataLength);
        retVal = simSetScriptStringParam_internal(scriptID, luaToInt(L, 2), data, (int)dataLength);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simPersistentDataWrite(luaWrap_lua_State* L)
{ // deprecated on June 19 2024
    TRACE_LUA_API;
    LUA_START("sim.persistentDataWrite");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_string, 0, lua_arg_string, 0))
    {
        int options = 0;
        int res = checkOneGeneralInputArgument(L, 3, lua_arg_number, 0, true, false, &errorString);
        if ((res == 0) || (res == 2))
        {
            if (res == 2)
                options = luaToInt(L, 3);
            size_t dataLength;
            char* data = (char*)luaWrap_lua_tobuffer(L, 2, &dataLength);
            retVal = simPersistentDataWrite_internal(std::string(luaWrap_lua_tostring(L, 1)).c_str(), data, (int)dataLength, options);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simPersistentDataRead(luaWrap_lua_State* L)
{ // deprecated on June 19 2024
    TRACE_LUA_API;
    LUA_START("sim.persistentDataRead");

    if (checkInputArguments(L, &errorString, lua_arg_string, 0))
    {
        int stringLength;
        char* str = simPersistentDataRead_internal(std::string(luaWrap_lua_tostring(L, 1)).c_str(), &stringLength);

        if (str != nullptr)
        {
            luaWrap_lua_pushbuffer(L, str, stringLength);
            simReleaseBuffer_internal(str);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simGetPersistentDataTags(luaWrap_lua_State* L)
{ // deprecated on June 19 2024
    TRACE_LUA_API;
    LUA_START("sim.getPersistentDataTags");

    int tagCount;
    char* data = simGetPersistentDataTags_internal(&tagCount);
    if (data != nullptr)
    {
        std::vector<std::string> stringTable;
        size_t off = 0;
        for (int i = 0; i < tagCount; i++)
        {
            stringTable.push_back(data + off);
            off += strlen(data + off) + 1;
        }
        pushStringTableOntoStack(L, stringTable);
        simReleaseBuffer_internal(data);
        LUA_END(1);
    }
    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetBoolParam(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.setBoolParam");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_bool, 0))
        retVal = simSetBoolParam_internal(luaToInt(L, 1), luaToBool(L, 2));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetBoolParam(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getBoolParam");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int retVal = simGetBoolParam_internal(luaToInt(L, 1));
        if (retVal != -1)
        {
            luaWrap_lua_pushboolean(L, retVal != 0);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetInt32Param(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.setInt32Param");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int paramIndex = luaToInt(L, 1);
        int v = luaToInt(L, 2);
        if (paramIndex == sim_intparam_error_report_mode)
        { // for backward compatibility (2020)
            CScriptObject* it =
                App::worldContainer->getScriptObjectFromHandle(CScriptObject::getScriptHandleFromInterpreterState_lua(L));
            if (it != nullptr)
            {
                bool r = true; // default
                if ((v & sim_api_error_report) == 0)
                    r = false;
                it->setRaiseErrors_backCompatibility(r);
                retVal = 1;
            }
        }
        else
            retVal = simSetInt32Param_internal(paramIndex, v);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetInt32Param(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getInt32Param");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int paramIndex = luaToInt(L, 1);
        if (paramIndex == sim_intparam_error_report_mode)
        { // for backward compatibility (2020)
            CScriptObject* it =
                App::worldContainer->getScriptObjectFromHandle(CScriptObject::getScriptHandleFromInterpreterState_lua(L));
            if (it != nullptr)
            {
                int v = 1; // default
                if (!it->getRaiseErrors_backCompatibility())
                    v = 0;
                luaWrap_lua_pushinteger(L, v);
                LUA_END(1);
            }
        }
        else
        {
            int v;
            int retVal = simGetInt32Param_internal(paramIndex, &v);
            if (retVal != -1)
            {
                luaWrap_lua_pushinteger(L, v);
                LUA_END(1);
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetFloatParam(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.setFloatParam");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
        retVal = simSetFloatParam_internal(luaToInt(L, 1), luaToDouble(L, 2));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetFloatParam(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getFloatParam");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        double v;
        int retVal = simGetFloatParam_internal(luaToInt(L, 1), &v);
        if (retVal != -1)
        {
            luaWrap_lua_pushnumber(L, v);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(1);
}

int _simSetStringParam(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.setStringParam");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_string, 0))
        retVal = simSetStringParam_internal(luaToInt(L, 1), luaWrap_lua_tostring(L, 2));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetStringParam(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getStringParam");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int param = luaToInt(L, 1);
        if (sim_stringparam_addonpath == param)
        {
            std::string s;
            CScriptObject* it = App::worldContainer->getScriptObjectFromHandle(CScriptObject::getScriptHandleFromInterpreterState_lua(L));
            if (it != nullptr)
                s = it->getAddOnPath();
            luaWrap_lua_pushtext(L, s.c_str());
            LUA_END(1);
        }
        else
        {
            char* s = simGetStringParam_internal(param);
            if (s != nullptr)
            {
                luaWrap_lua_pushtext(L, s);
                delete[] s;
                LUA_END(1);
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetArrayParam(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.setArrayParam");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_table, 0))
    {
        int parameter = luaToInt(L, 1);
        if (true)
        { // for now all array parameters are tables of 3 floats
            double theArray[3];
            getDoublesFromTable(L, 2, 3, theArray);
            retVal = simSetArrayParam_internal(parameter, theArray);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetArrayParam(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getArrayParam");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int parameter = luaToInt(L, 1);
        if (true)
        { // for now all parameters are tables of 3 floats
            double theArray[3];
            int retVal = simGetArrayParam_internal(parameter, theArray);
            if (retVal != -1)
            {
                pushDoubleTableOntoStack(L, 3, theArray);
                LUA_END(1);
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetNamedStringParam(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.setNamedStringParam");
    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_string, 0, lua_arg_string, 0))
    {
        std::string paramName(luaWrap_lua_tostring(L, 1));
        size_t l;
        const char* data = ((char*)luaWrap_lua_tobuffer(L, 2, &l));
        retVal = simSetNamedStringParam_internal(paramName.c_str(), data, int(l));
        if (retVal >= 0)
        {
            luaWrap_lua_pushinteger(L, retVal);
            LUA_END(1);
        }
    }
    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simGetNamedStringParam(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getNamedStringParam");
    if (checkInputArguments(L, &errorString, lua_arg_string, 0))
    {
        std::string paramName(luaWrap_lua_tostring(L, 1));
        int l;
        char* stringParam = simGetNamedStringParam_internal(paramName.c_str(), &l);
        if (stringParam != nullptr)
        {
            luaWrap_lua_pushbinarystring(L, stringParam, l);
            delete[] stringParam;
            LUA_END(1);
        }
        LUA_END(0);
    }
    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetInt32Signal(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.setInt32Signal");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_string, 0, lua_arg_number, 0))
    {
        setCurrentScriptInfo_cSide(CScriptObject::getScriptHandleFromInterpreterState_lua(L),
                                   CScriptObject::getScriptNameIndexFromInterpreterState_lua_old(
                                       L)); // for transmitting to the master function additional info (e.g.for autom.
                                            // name adjustment, or for autom. object deletion when script ends)
        retVal = simSetInt32Signal_internal(luaWrap_lua_tostring(L, 1), luaToInt(L, 2));
        setCurrentScriptInfo_cSide(-1, -1);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetInt32Signal(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getInt32Signal");

    if (checkInputArguments(L, &errorString, lua_arg_string, 0))
    {
        int intVal;
        if (simGetInt32Signal_internal(std::string(luaWrap_lua_tostring(L, 1)).c_str(), &intVal) == 1)
        {
            luaWrap_lua_pushinteger(L, intVal);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simClearInt32Signal(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.clearInt32Signal");

    int retVal = -1; // error
    int res = checkOneGeneralInputArgument(L, 1, lua_arg_string, 0, true, true, &errorString);
    if (res >= 0)
    {
        if (res != 2)
            retVal = simClearInt32Signal_internal(nullptr); // actually deprecated. No need for that
        else
            retVal = simClearInt32Signal_internal(luaWrap_lua_tostring(L, 1));
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetFloatSignal(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.setFloatSignal");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_string, 0, lua_arg_number, 0))
    {
        setCurrentScriptInfo_cSide(CScriptObject::getScriptHandleFromInterpreterState_lua(L),
                                   CScriptObject::getScriptNameIndexFromInterpreterState_lua_old(
                                       L)); // for transmitting to the master function additional info (e.g.for autom.
                                            // name adjustment, or for autom. object deletion when script ends)
        retVal = simSetFloatSignal_internal(luaWrap_lua_tostring(L, 1), luaToDouble(L, 2));
        setCurrentScriptInfo_cSide(-1, -1);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetFloatSignal(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getFloatSignal");

    if (checkInputArguments(L, &errorString, lua_arg_string, 0))
    {
        double floatVal;
        if (simGetFloatSignal_internal(std::string(luaWrap_lua_tostring(L, 1)).c_str(), &floatVal) == 1)
        {
            luaWrap_lua_pushnumber(L, floatVal);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simClearFloatSignal(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.clearFloatSignal");

    int retVal = -1; // error
    int res = checkOneGeneralInputArgument(L, 1, lua_arg_string, 0, true, true, &errorString);
    if (res >= 0)
    {
        if (res != 2)
            retVal = simClearFloatSignal_internal(nullptr); // actually deprecated. No need for that
        else
            retVal = simClearFloatSignal_internal(luaWrap_lua_tostring(L, 1));
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetStringSignal(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.setStringSignal");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_string, 0, lua_arg_string, 0))
    {
        size_t dataLength;
        const char* data = luaWrap_lua_tobuffer(L, 2, &dataLength);
        setCurrentScriptInfo_cSide(CScriptObject::getScriptHandleFromInterpreterState_lua(L),
                                   CScriptObject::getScriptNameIndexFromInterpreterState_lua_old(
                                       L)); // for transmitting to the master function additional info (e.g.for autom.
                                            // name adjustment, or for autom. object deletion when script ends)
        retVal = simSetStringSignal_internal(luaWrap_lua_tostring(L, 1), data, int(dataLength));
        setCurrentScriptInfo_cSide(-1, -1);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetStringSignal(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getStringSignal");

    if (checkInputArguments(L, &errorString, lua_arg_string, 0))
    {
        int stringLength;
        char* str = simGetStringSignal_internal(std::string(luaWrap_lua_tostring(L, 1)).c_str(), &stringLength);
        if (str != nullptr)
        {
            luaWrap_lua_pushbinarystring(L, str, stringLength);
            simReleaseBuffer_internal(str);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simClearStringSignal(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.clearStringSignal");

    int retVal = -1; // error
    int res = checkOneGeneralInputArgument(L, 1, lua_arg_string, 0, true, true, &errorString);
    if (res >= 0)
    {
        if (res != 2)
            retVal = simClearStringSignal_internal(nullptr);
        else
            retVal = simClearStringSignal_internal(luaWrap_lua_tostring(L, 1));
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetSignalName(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getSignalName");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        char* str = simGetSignalName_internal(luaToInt(L, 1), luaToInt(L, 2));
        if (str != nullptr)
        {
            luaWrap_lua_pushtext(L, str);
            simReleaseBuffer_internal(str);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simGetLightParameters(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getLightParameters");

    int retVal = -1;
    double ambientOld[3] = {0.0, 0.0, 0.0};
    double diffuse[3] = {0.0, 0.0, 0.0};
    double specular[3] = {0.0, 0.0, 0.0};
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
        retVal = simGetLightParameters_internal(luaToInt(L, 1), nullptr, diffuse, specular);

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    pushDoubleTableOntoStack(L, 3, ambientOld);
    pushDoubleTableOntoStack(L, 3, diffuse);
    pushDoubleTableOntoStack(L, 3, specular);
    LUA_END(4);
}

int _simSetLightParameters(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.setLightParameters");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int objHandle = luaToInt(L, 1);
        int state = luaToInt(L, 2);
        float* diffuseP = nullptr;
        float* specularP = nullptr;
        float diffuse_[3] = {0.0, 0.0, 0.0};
        float specular_[3] = {0.0, 0.0, 0.0};
        int res = checkOneGeneralInputArgument(L, 3, lua_arg_number, 3, true, true, &errorString);
        if (res != -1)
        {
            int res = checkOneGeneralInputArgument(L, 4, lua_arg_number, 3, true, true, &errorString);
            if (res != -1)
            {
                if (res == 2)
                { // get the data
                    getFloatsFromTable(L, 4, 3, diffuse_);
                    diffuseP = diffuse_;
                }
                int res = checkOneGeneralInputArgument(L, 5, lua_arg_number, 3, true, true, &errorString);
                if (res != -1)
                {
                    if (res == 2)
                    { // get the data
                        getFloatsFromTable(L, 5, 3, specular_);
                        specularP = specular_;
                    }
                    retVal = simSetLightParameters_internal(objHandle, state, nullptr, diffuseP, specularP);
                }
            }
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetObjectInt32Param(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getObjectInt32Param");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int param;
        int retVal = simGetObjectInt32Param_internal(luaToInt(L, 1), luaToInt(L, 2), &param);
        if (retVal > 0)
        {
            luaWrap_lua_pushinteger(L, param);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetObjectInt32Param(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.setObjectInt32Param");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0))
        retVal = simSetObjectInt32Param_internal(luaToInt(L, 1), luaToInt(L, 2), luaToInt(L, 3));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetObjectFloatParam(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getObjectFloatParam");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        double param;
        int retVal = simGetObjectFloatParam_internal(luaToInt(L, 1), luaToInt(L, 2), &param);
        if (retVal > 0)
        {
            luaWrap_lua_pushnumber(L, param);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetObjectFloatParam(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.setObjectFloatParam");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0))
        retVal = simSetObjectFloatParam_internal(luaToInt(L, 1), luaToInt(L, 2), luaToDouble(L, 3));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetObjectFloatArrayParam(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getObjectFloatArrayParam");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int s;
        double* params = simGetObjectFloatArrayParam_internal(luaToInt(L, 1), luaToInt(L, 2), &s);
        if (params != nullptr)
        {
            pushDoubleTableOntoStack(L, s, params);
            delete[] params;
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetObjectFloatArrayParam(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.setObjectFloatArrayParam");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 1))
    {
        size_t cnt = luaWrap_lua_rawlen(L, 3);
        std::vector<double> arr;
        arr.resize(cnt);
        getDoublesFromTable(L, 3, cnt, &arr[0]);
        retVal = simSetObjectFloatArrayParam_internal(luaToInt(L, 1), luaToInt(L, 2), &arr[0], int(cnt));
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetObjectStringParam(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getObjectStringParam");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int paramLength;
        char* strBuff = simGetObjectStringParam_internal(luaToInt(L, 1), luaToInt(L, 2), &paramLength);
        if (strBuff != nullptr)
        {
            luaWrap_lua_pushbuffer(L, strBuff, paramLength);
            delete[] strBuff;
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetObjectStringParam(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.setObjectStringParam");

    int retVal = -1; // means error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_string, 0))
    {
        size_t dataLength;
        char* data = (char*)luaWrap_lua_tobuffer(L, 3, &dataLength);
        retVal = simSetObjectStringParam_internal(luaToInt(L, 1), luaToInt(L, 2), data, (int)dataLength);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simWriteCustomStringData(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.writeCustomStringData");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_string, 0))
    {
        int objectHandle = luaToInt(L, 1);
        std::string dataName(luaWrap_lua_tostring(L, 2));
        int res;
        res = checkOneGeneralInputArgument(L, 3, lua_arg_string, 0, false, true, &errorString);
        if (res >= 1)
        {
            size_t dataLength = 0;
            char* data = nullptr;
            if (res == 2)
                data = (char*)luaWrap_lua_tobuffer(L, 3, &dataLength);
            retVal = simWriteCustomDataBlock_internal(objectHandle, dataName.c_str(), data, (int)dataLength);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simReadCustomStringData(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.readCustomStringData");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_string, 0))
    {
        int objectHandle = luaToInt(L, 1);
        std::string dataName(luaWrap_lua_tostring(L, 2));
        int dataLength;
        char* data = simReadCustomDataBlock_internal(objectHandle, dataName.c_str(), &dataLength);
        if (data != nullptr)
        {
            luaWrap_lua_pushbinarystring(L, (const char*)data, dataLength);
            simReleaseBuffer_internal(data);
        }
        else
            luaWrap_lua_pushnil(L);
        LUA_END(1);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simReadCustomDataTags(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.readCustomDataTags");

    std::vector<std::string> stringTable;
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
    {
        int objectHandle = luaToInt(L, 1);
        int tagCount;
        char* data = simReadCustomDataBlockTags_internal(objectHandle, &tagCount);
        if (data != nullptr)
        {
            size_t off = 0;
            for (int i = 0; i < tagCount; i++)
            {
                stringTable.push_back(data + off);
                off += strlen(data + off) + 1;
            }
            simReleaseBuffer_internal(data);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    pushStringTableOntoStack(L, stringTable);
    LUA_END(1);
}

int _simGetEngineFloatParam(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getEngineFloatParam_old");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int paramId = luaToInt(L, 1);
        int objectHandle = luaToInt(L, 2);
        bool ok;
        double paramVal = simGetEngineFloatParam_internal(paramId, objectHandle, nullptr, &ok);
        if (ok)
        {
            luaWrap_lua_pushnumber(L, paramVal);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simGetEngineInt32Param(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getEngineInt32Param");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int paramId = luaToInt(L, 1);
        int objectHandle = luaToInt(L, 2);
        bool ok;
        int paramVal = simGetEngineInt32Param_internal(paramId, objectHandle, nullptr, &ok);
        if (ok)
        {
            luaWrap_lua_pushinteger(L, paramVal);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simGetEngineBoolParam(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getEngineBoolParam_old");

    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
    {
        int paramId = luaToInt(L, 1);
        int objectHandle = luaToInt(L, 2);
        bool ok;
        bool paramVal = simGetEngineBoolParam_internal(paramId, objectHandle, nullptr, &ok);
        if (ok)
        {
            luaWrap_lua_pushboolean(L, paramVal);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

int _simSetEngineFloatParam(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.setEngineFloatParam_old");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0))
    {
        int paramId = luaToInt(L, 1);
        int objectHandle = luaToInt(L, 2);
        double paramVal = luaToDouble(L, 3);
        retVal = simSetEngineFloatParam_internal(paramId, objectHandle, nullptr, paramVal);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetEngineInt32Param(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.setEngineInt32Param");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_number, 0))
    {
        int paramId = luaToInt(L, 1);
        int objectHandle = luaToInt(L, 2);
        int paramVal = luaToInt(L, 3);
        retVal = simSetEngineInt32Param_internal(paramId, objectHandle, nullptr, paramVal);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetEngineBoolParam(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.setEngineBoolParam_old");

    int retVal = -1;
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0, lua_arg_bool, 0))
    {
        int paramId = luaToInt(L, 1);
        int objectHandle = luaToInt(L, 2);
        bool paramVal = luaToBool(L, 3);
        retVal = simSetEngineBoolParam_internal(paramId, objectHandle, nullptr, paramVal);
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetObjectProperty(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getObjectProperty");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
        retVal = simGetObjectProperty_internal(luaToInt(L, 1));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetObjectProperty(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.setObjectProperty");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
        retVal = simSetObjectProperty_internal(luaToInt(L, 1), luaToInt(L, 2));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetObjectSpecialProperty(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getObjectSpecialProperty");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
        retVal = simGetObjectSpecialProperty_internal(luaToInt(L, 1));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetObjectSpecialProperty(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.setObjectSpecialProperty");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
        retVal = simSetObjectSpecialProperty_internal(luaToInt(L, 1), luaToInt(L, 2));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetModelProperty(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getModelProperty");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0))
        retVal = simGetModelProperty_internal(luaToInt(L, 1));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simSetModelProperty(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.setModelProperty");

    int retVal = -1; // error
    if (checkInputArguments(L, &errorString, lua_arg_number, 0, lua_arg_number, 0))
        retVal = simSetModelProperty_internal(luaToInt(L, 1), luaToInt(L, 2));

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushinteger(L, retVal);
    LUA_END(1);
}

int _simGetRealTimeSimulation(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.getRealTimeSimulation");

    int retVal = simGetRealTimeSimulation_internal();

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    luaWrap_lua_pushboolean(L, retVal);
    LUA_END(1);
}

int _simBuildMatrixQ(luaWrap_lua_State* L)
{
    TRACE_LUA_API;
    LUA_START("sim.buildMatrixQ");

    if (checkInputArguments(L, &errorString, lua_arg_number, 3, lua_arg_number, 4))
    {
        double arr[12];
        double pos[3];
        double quaternion[4];
        getDoublesFromTable(L, 1, 3, pos);
        getDoublesFromTable(L, 2, 4, quaternion);
        if (simBuildMatrixQ_internal(pos, quaternion, arr) == 1)
        {
            pushDoubleTableOntoStack(L, 12, arr);
            LUA_END(1);
        }
    }

    LUA_RAISE_ERROR_OR_YIELD_IF_NEEDED(); // we might never return from this!
    LUA_END(0);
}

