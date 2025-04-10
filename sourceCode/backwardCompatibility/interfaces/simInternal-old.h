int simExtCallScriptFunction_internal(int scriptHandleOrType, const char* functionNameAtScriptName,
                                      const int* inIntData, int inIntCnt, const double* inFloatData, int inFloatCnt,
                                      const char** inStringData, int inStringCnt, const char* inBufferData,
                                      int inBufferCnt, int** outIntData, int* outIntCnt, double** outFloatData,
                                      int* outFloatCnt, char*** outStringData, int* outStringCnt, char** outBufferData,
                                      int* outBufferSize);
int simGetMaterialId_internal(const char* materialName);
int simGetShapeMaterial_internal(int shapeHandle);
int simHandleVarious_internal();
int simSerialPortOpen_internal(int portNumber, int baudRate, void* reserved1, void* reserved2);
int simSerialPortClose_internal(int portNumber);
int simSerialPortSend_internal(int portNumber, const char* data, int dataLength);
int simSerialPortRead_internal(int portNumber, char* buffer, int dataLengthToRead);
int simGetPathPlanningHandle_internal(const char* pathPlanningObjectName);
int simGetMotionPlanningHandle_internal(const char* motionPlanningObjectName);
int simGetMpConfigForTipPose_internal(int motionPlanningObjectHandle, int options, double closeNodesDistance,
                                      int trialCount, const double* tipPose, int maxTimeInMs,
                                      double* outputJointPositions, const double* referenceConfigs,
                                      int referenceConfigCount, const double* jointWeights, const int* jointBehaviour,
                                      int correctionPasses);
double* simFindMpPath_internal(int motionPlanningObjectHandle, const double* startConfig, const double* goalConfig,
                               int options, double stepSize, int* outputConfigsCnt, int maxTimeInMs, double* reserved,
                               const int* auxIntParams, const double* auxFloatParams);
double* simSimplifyMpPath_internal(int motionPlanningObjectHandle, const double* pathBuffer, int configCnt, int options,
                                   double stepSize, int increment, int* outputConfigsCnt, int maxTimeInMs,
                                   double* reserved, const int* auxIntParams, const double* auxFloatParams);
double* simFindIkPath_internal(int motionPlanningObjectHandle, const double* startConfig, const double* goalPose,
                               int options, double stepSize, int* outputConfigsCnt, double* reserved,
                               const int* auxIntParams, const double* auxFloatParams);
double* simGetMpConfigTransition_internal(int motionPlanningObjectHandle, const double* startConfig,
                                          const double* goalConfig, int options, const int* select, double calcStepSize,
                                          double maxOutStepSize, int wayPointCnt, const double* wayPoints,
                                          int* outputConfigsCnt, const int* auxIntParams, const double* auxFloatParams);
int simCreateMotionPlanning_internal(int jointCnt, const int* jointHandles, const int* jointRangeSubdivisions,
                                     const double* jointMetricWeights, int options, const int* intParams,
                                     const double* floatParams, const void* reserved);
int simRemoveMotionPlanning_internal(int motionPlanningHandle);
int simSearchPath_internal(int pathPlanningObjectHandle, double maximumSearchTime);
int simInitializePathSearch_internal(int pathPlanningObjectHandle, double maximumSearchTime, double searchTimeStep);
int simPerformPathSearchStep_internal(int temporaryPathSearchObject, bool abortSearch);
int simLockInterface_internal(bool locked);
int simCopyPasteSelectedObjects_internal();
int simResetPath_internal(int pathHandle);
int simHandlePath_internal(int pathHandle, double deltaTime);
int simResetJoint_internal(int jointHandle);
int simHandleJoint_internal(int jointHandle, double deltaTime);
int simAppendScriptArrayEntry_internal(const char* reservedSetToNull, int scriptHandleOrType,
                                       const char* arrayNameAtScriptName, const char* keyName, const char* data,
                                       const int* what);
int simClearScriptVariable_internal(const char* reservedSetToNull, int scriptHandleOrType,
                                    const char* variableNameAtScriptName);
void _simGetJointOdeParameters_internal(const void* joint, double* stopERP, double* stopCFM, double* bounce,
                                        double* fudge, double* normalCFM);
void _simGetJointBulletParameters_internal(const void* joint, double* stopERP, double* stopCFM, double* normalCFM);
void _simGetOdeMaxContactFrictionCFMandERP_internal(const void* geomInfo, int* maxContacts, double* friction,
                                                    double* cfm, double* erp);
bool _simGetBulletCollisionMargin_internal(const void* geomInfo, double* margin, int* otherProp);
bool _simGetBulletStickyContact_internal(const void* geomInfo);
double _simGetBulletRestitution_internal(const void* geomInfo);
void _simGetVortexParameters_internal(const void* object, int version, double* floatParams, int* intParams);
void _simGetNewtonParameters_internal(const void* object, int* version, double* floatParams, int* intParams);
void _simGetDamping_internal(const void* geomInfo, double* linDamping, double* angDamping);
double _simGetFriction_internal(const void* geomInfo);
int simAddSceneCustomData_internal(int header, const char* data, int dataLength);
int simGetSceneCustomDataLength_internal(int header);
int simGetSceneCustomData_internal(int header, char* data);
int simAddObjectCustomData_internal(int objectHandle, int header, const char* data, int dataLength);
int simGetObjectCustomDataLength_internal(int objectHandle, int header);
int simGetObjectCustomData_internal(int objectHandle, int header, char* data);
int simCreateUI_internal(const char* uiName, int menuAttributes, const int* clientSize, const int* cellSize,
                         int* buttonHandles);
int simCreateUIButton_internal(int uiHandle, const int* position, const int* size, int buttonProperty);
int simGetUIHandle_internal(const char* uiName);
int simGetUIProperty_internal(int uiHandle);
int simGetUIEventButton_internal(int uiHandle, int* auxiliaryValues);
int simSetUIProperty_internal(int uiHandle, int elementProperty);
int simGetUIButtonProperty_internal(int uiHandle, int buttonHandle);
int simSetUIButtonProperty_internal(int uiHandle, int buttonHandle, int buttonProperty);
int simGetUIButtonSize_internal(int uiHandle, int buttonHandle, int* size);
int simSetUIButtonLabel_internal(int uiHandle, int buttonHandle, const char* upStateLabel, const char* downStateLabel);
char* simGetUIButtonLabel_internal(int uiHandle, int buttonHandle);
int simSetUISlider_internal(int uiHandle, int buttonHandle, int position);
int simGetUISlider_internal(int uiHandle, int buttonHandle);
int simSetUIButtonColor_internal(int uiHandle, int buttonHandle, const float* upStateColor, const float* downStateColor,
                                 const float* labelColor);
int simSetUIButtonTexture_internal(int uiHandle, int buttonHandle, const int* size, const char* textureData);
int simCreateUIButtonArray_internal(int uiHandle, int buttonHandle);
int simSetUIButtonArrayColor_internal(int uiHandle, int buttonHandle, const int* position, const float* color);
int simDeleteUIButtonArray_internal(int uiHandle, int buttonHandle);
int simRemoveUI_internal(int uiHandle);
int simSetUIPosition_internal(int uiHandle, const int* position);
int simGetUIPosition_internal(int uiHandle, int* position);
int simLoadUI_internal(const char* filename, int maxCount, int* uiHandles);
int simSaveUI_internal(int count, const int* uiHandles, const char* filename);
int simHandleGeneralCallbackScript_internal(int callbackId, int callbackTag, void* additionalData);
int simRegisterCustomLuaFunction_internal(const char* funcName, const char* callTips, const int* inputArgumentTypes,
                                          void (*callBack)(struct SLuaCallBack* p));
int simRegisterContactCallback_internal(int (*callBack)(int, int, int, int*, double*));
int simRegisterJointCtrlCallback_internal(int (*callBack)(int, int, int, const int*, const double*, double*));
int simGetMechanismHandle_internal(const char* mechanismName);
int simHandleMechanism_internal(int mechanismHandle);
int simHandleCustomizationScripts_internal(int callType);
int simCallScriptFunction_internal(int scriptHandleOrType, const char* functionNameAtScriptName, SLuaCallBack* data,
                                   const char* reservedSetToNull);
int simSetVisionSensorFilter_internal(int visionSensorHandle, int filterIndex, int options, const int* pSizes,
                                      const unsigned char* bytes, const int* ints, const double* floats,
                                      const unsigned char* custom);
int simGetVisionSensorFilter_internal(int visionSensorHandle, int filterIndex, int* options, int* pSizes,
                                      unsigned char** bytes, int** ints, double** floats, unsigned char** custom);
char* simGetScriptSimulationParameter_internal(int scriptHandle, const char* parameterName, int* parameterLength);
int simSetScriptSimulationParameter_internal(int scriptHandle, const char* parameterName, const char* parameterValue,
                                             int parameterLength);
int simGetNameSuffix_internal(const char* name);
int simSetNameSuffix_internal(int nameSuffixNumber);
int simAddStatusbarMessage_internal(const char* message);
char* simGetScriptRawBuffer_internal(int scriptHandle, int bufferHandle);
int simSetScriptRawBuffer_internal(int scriptHandle, const char* buffer, int bufferSize);
int simReleaseScriptRawBuffer_internal(int scriptHandle, int bufferHandle);
int simSetShapeMassAndInertia_internal(int shapeHandle, double mass, const double* inertiaMatrix,
                                       const double* centerOfMass, const double* transformation);
int simGetShapeMassAndInertia_internal(int shapeHandle, double* mass, double* inertiaMatrix, double* centerOfMass,
                                       const double* transformation);
int simCheckIkGroup_internal(int ikGroupHandle, int jointCnt, const int* jointHandles, double* jointValues,
                             const int* jointOptions);
int simCreateIkGroup_internal(int options, const int* intParams, const double* floatParams, const void* reserved);
int simRemoveIkGroup_internal(int ikGroupHandle);
int simCreateIkElement_internal(int ikGroupHandle, int options, const int* intParams, const double* floatParams,
                                const void* reserved);
int simExportIk_internal(const char* pathAndFilename, int reserved1, void* reserved2);
int simComputeJacobian_internal(int ikGroupHandle, int options, void* reserved);
int simGetConfigForTipPose_internal(int ikGroupHandle, int jointCnt, const int* jointHandles, double thresholdDist,
                                    int maxTimeInMs, double* retConfig, const double* metric, int collisionPairCnt,
                                    const int* collisionPairs, const int* jointOptions, const double* lowLimits,
                                    const double* ranges, void* reserved);
double* simGenerateIkPath_internal(int ikGroupHandle, int jointCnt, const int* jointHandles, int ptCnt,
                                   int collisionPairCnt, const int* collisionPairs, const int* jointOptions,
                                   void* reserved);
int simGetIkGroupHandle_internal(const char* ikGroupName);
double* simGetIkGroupMatrix_internal(int ikGroupHandle, int options, int* matrixSize);
int simHandleIkGroup_internal(int ikGroupHandle);
int simSetIkGroupProperties_internal(int ikGroupHandle, int resolutionMethod, int maxIterations, double damping,
                                     void* reserved);
int simSetIkElementProperties_internal(int ikGroupHandle, int tipDummyHandle, int constraints, const double* precision,
                                       const double* weight, void* reserved);
int simSetThreadIsFree_internal(bool freeMode);
int simTubeOpen_internal(int dataHeader, const char* dataName, int readBufferSize, bool notUsedButKeepZero);
int simTubeClose_internal(int tubeHandle);
int simTubeWrite_internal(int tubeHandle, const char* data, int dataLength);
char* simTubeRead_internal(int tubeHandle, int* dataLength);
int simTubeStatus_internal(int tubeHandle, int* readPacketsCount, int* writePacketsCount);
int simSendData_internal(int targetID, int dataHeader, const char* dataName, const char* data, int dataLength,
                         int antennaHandle, double actionRadius, double emissionAngle1, double emissionAngle2,
                         double persistence);
char* simReceiveData_internal(int dataHeader, const char* dataName, int antennaHandle, int index, int* dataLength,
                              int* senderID, int* dataHeaderR, char** dataNameR);
int simGetPositionOnPath_internal(int pathHandle, double relativeDistance, double* position);
int simGetOrientationOnPath_internal(int pathHandle, double relativeDistance, double* eulerAngles);
int simGetDataOnPath_internal(int pathHandle, double relativeDistance, int dataType, int* intData, double* floatData);
int simGetClosestPositionOnPath_internal(int pathHandle, double* absolutePosition, double* pathPosition);
int simGetPathPosition_internal(int objectHandle, double* position);
int simSetPathPosition_internal(int objectHandle, double position);
int simGetPathLength_internal(int objectHandle, double* length);
int simCreatePath_internal(int attributes, const int* intParams, const double* floatParams, const float* color);
int simInsertPathCtrlPoints_internal(int pathHandle, int options, int startIndex, int ptCnt, const void* ptData);
int simCutPathCtrlPoints_internal(int pathHandle, int startIndex, int ptCnt);
int simGetThreadId_internal();
int simSwitchThread_internal();
int simLockResources_internal(int lockType, int reserved);
int simUnlockResources_internal(int lockHandle);
char* simGetUserParameter_internal(int objectHandle, const char* parameterName, int* parameterLength);
int simSetUserParameter_internal(int objectHandle, const char* parameterName, const char* parameterValue,
                                 int parameterLength);
int simSetPathTargetNominalVelocity_internal(int objectHandle, double targetNominalVelocity);
int simGetCollectionHandle_internal(const char* collectionName);
int simRemoveCollection_internal(int collectionHandle);
int simEmptyCollection_internal(int collectionHandle);
char* simGetCollectionName_internal(int collectionHandle);
int simSetCollectionName_internal(int collectionHandle, const char* collectionName);
int simCreateCollection_internal(const char* collectionName, int options);
int simAddObjectToCollection_internal(int collectionHandle, int objectHandle, int what, int options);
int simGetCollisionHandle_internal(const char* collisionObjectName);
int simGetDistanceHandle_internal(const char* distanceObjectName);
int simResetCollision_internal(int collisionObjectHandle);
int simResetDistance_internal(int distanceObjectHandle);
int simHandleCollision_internal(int collisionObjectHandle);
int simReadCollision_internal(int collisionObjectHandle);
int simHandleDistance_internal(int distanceObjectHandle, double* smallestDistance);
int simReadDistance_internal(int distanceObjectHandle, double* smallestDistance);
int simAddBanner_internal(const char* label, double size, int options, const double* positionAndEulerAngles,
                          int parentObjectHandle, const float* labelColors, const float* backgroundColors);
int simRemoveBanner_internal(int bannerID);
int simAddGhost_internal(int ghostGroup, int objectHandle, int options, double startTime, double endTime,
                         const float* color);
int simModifyGhost_internal(int ghostGroup, int ghostId, int operation, double floatValue, int options, int optionsMask,
                            const double* colorOrTransformation);
int simSetGraphUserData_internal(int graphHandle, const char* streamName, double data);
int simAddPointCloud_internal(int pageMask, int layerMask, int objectHandle, int options, double pointSize, int ptCnt,
                              const double* pointCoordinates, const char* defaultColors, const char* pointColors,
                              const double* pointNormals);
int simModifyPointCloud_internal(int pointCloudHandle, int operation, const int* intParam, const double* floatParam);
int simCopyMatrix_internal(const double* matrixIn, double* matrixOut);
int simAddModuleMenuEntry_internal(const char* entryLabel, int itemCount, int* itemHandles);
int simSetModuleMenuItemState_internal(int itemHandle, int state, const char* label);
char* simGetObjectName_internal(int objectHandle);
int simSetObjectName_internal(int objectHandle, const char* objectName);
char* simGetScriptName_internal(int scriptHandle);
int simGetScriptHandle_internal(const char* scriptName);
int simSetScriptVariable_internal(int scriptHandleOrType, const char* variableNameAtScriptName, int stackHandle);
int simGetScript_internal(int index);
int simGetScriptAssociatedWithObject_internal(int objectHandle);
int simGetCustomizationScriptAssociatedWithObject_internal(int objectHandle);
int simGetObjectAssociatedWithScript_internal(int scriptHandle);
char* simGetObjectConfiguration_internal(int objectHandle);
int simSetObjectConfiguration_internal(const char* data);
char* simGetConfigurationTree_internal(int objectHandle);
int simSetConfigurationTree_internal(const char* data);
int simEnableEventCallback_internal(int eventCallbackType, const char* plugin, int reserved);
char* simFileDialog_internal(int mode, const char* title, const char* startPath, const char* initName,
                             const char* extName, const char* ext);
int simMsgBox_internal(int dlgType, int buttons, const char* title, const char* message);
int simDisplayDialog_internal(const char* titleText, const char* mainText, int dialogType, const char* initialText,
                              const float* titleColors, const float* dialogColors, int* elementHandle);
int simGetDialogResult_internal(int genericDialogHandle);
char* simGetDialogInput_internal(int genericDialogHandle);
int simEndDialog_internal(int genericDialogHandle);
int simIsObjectInSelection_internal(int objectHandle);
int simAddObjectToSelection_internal(int what, int objectHandle);
int simRemoveObjectFromSelection_internal(int what, int objectHandle);
int simGetObjectSelectionSize_internal();
int simGetObjectLastSelection_internal();
int simGetObjectSelection_internal(int* objectHandles);
int simScaleSelectedObjects_internal(double scalingFactor, bool scalePositionsToo);
int simDeleteSelectedObjects_internal();
int simGetObjectUniqueIdentifier_internal(int objectHandle, int* uniqueIdentifier);
void _simSetDynamicJointLocalTransformationPart2_internal(void* joint, const double* pos, const double* quat);
void _simSetDynamicForceSensorLocalTransformationPart2_internal(void* forceSensor, const double* pos,
                                                                const double* quat);
void _simSetDynamicJointLocalTransformationPart2IsValid_internal(void* joint, bool valid);
void _simSetDynamicForceSensorLocalTransformationPart2IsValid_internal(void* forceSensor, bool valid);
int simBreakForceSensor_internal(int objectHandle);
bool _simIsForceSensorBroken_internal(const void* forceSensor);
void _simGetDynamicForceSensorLocalTransformationPart2_internal(const void* forceSensor, double* pos, double* quat);
int simGetJointMatrix_internal(int objectHandle, double* matrix);
int simSetSphericalJointMatrix_internal(int objectHandle, const double* matrix);
int simGetObjectHandleEx_internal(const char* objectAlias, int index, int proxy, int options);
int simSetScriptAttribute_internal(int scriptHandle, int attributeID, double floatVal, int intOrBoolVal);
int simGetScriptAttribute_internal(int scriptHandle, int attributeID, double* floatVal, int* intOrBoolVal);
int simSetScriptText_internal(int scriptHandle, const char* scriptText);
const char* simGetScriptText_internal(int scriptHandle);
int simGetScriptProperty_internal(int scriptHandle, int* scriptProperty, int* associatedObjectHandle);
int simGetJointMaxForce_internal(int jointHandle, double* forceOrTorque);
int simSetJointMaxForce_internal(int objectHandle, double forceOrTorque);
void _simSetGeomProxyDynamicsFullRefreshFlag_internal(void* geomData, bool flag);
bool _simGetGeomProxyDynamicsFullRefreshFlag_internal(const void* geomData);
int simRemoveObject_internal(int objectHandle);
unsigned int simGetSystemTimeInMs_internal(int previousTime);
float* simGetVisionSensorImage_internal(int visionSensorHandle);
unsigned char* simGetVisionSensorCharImage_internal(int visionSensorHandle, int* resolutionX, int* resolutionY);
int simSetVisionSensorImage_internal(int visionSensorHandle, const float* image);
int simSetVisionSensorCharImage_internal(int visionSensorHandle, const unsigned char* image);
float* simGetVisionSensorDepthBuffer_internal(int visionSensorHandle);
int simCreatePureShape_internal(int primitiveType, int options, const double* sizes, double mass, const int* precision);
void* simBroadcastMessage_internal(int* auxiliaryData, void* customData, int* replyData);
void* simSendModuleMessage_internal(int message, int* auxiliaryData, void* customData, int* replyData);
int simBuildMatrixQ_internal(const double* position, const double* quaternion, double* matrix);
int simGetQuaternionFromMatrix_internal(const double* matrix, double* quaternion);
void _simGetPrincipalMomentOfInertia_internal(const void* geomInfo, double* inertia);
void _simGetLocalInertiaFrame_internal(const void* geomInfo, double* pos, double* quat);
int simSetDoubleSignalOld_internal(const char* signalName, double signalValue);
int simGetDoubleSignalOld_internal(const char* signalName, double* signalValue);
int simClearDoubleSignalOld_internal(const char* signalName);
int simGetShapeVertex_internal(int shapeHandle, int groupElementIndex, int vertexIndex, double* relativePosition);
int simGetShapeTriangle_internal(int shapeHandle, int groupElementIndex, int triangleIndex, int* vertexIndices,
                                 double* triangleNormals);
const void* _simGetGeomProxyFromShape_internal(const void* shape);
int simReorientShapeBoundingBox_internal(int shapeHandle, int relativeToHandle, int reservedSetToZero);
int simLoadModule_internal(const char* filenameAndPath, const char* pluginName);
int simUnloadModule_internal(int pluginhandle);
int simIsStackValueNull_internal(int stackHandle);
int simIsRealTimeSimulationStepNeeded_internal();
int simAdjustRealTimeTimer_internal(int instanceIndex, double deltaTime);
int simSetSimulationPassesPerRenderingPass_internal(int p);
int simGetSimulationPassesPerRenderingPass_internal();
int simAdvanceSimulationByOneStep_internal();
int simHandleMainScript_internal();
int simAssociateScriptWithObject_internal(int scriptHandle, int associatedObjectHandle);
int simAddScript_internal(int scriptProperty);
int simRemoveScript_internal(int scriptHandle);
int simGetScriptInt32Param_internal(int scriptHandle, int parameterID, int* parameter);
int simSetScriptInt32Param_internal(int scriptHandle, int parameterID, int parameter);
char* simGetScriptStringParam_internal(int scriptHandle, int parameterID, int* parameterLength);
int simSetScriptStringParam_internal(int scriptHandle, int parameterID, const char* parameter, int parameterLength);
int simPersistentDataWrite_internal(const char* dataTag, const char* dataValue, int dataLength, int options);
char* simPersistentDataRead_internal(const char* dataTag, int* dataLength);
char* simGetPersistentDataTags_internal(int* tagCount);

int simSetBoolParam_internal(int parameter, bool boolState);
int simGetBoolParam_internal(int parameter);
int simSetInt32Param_internal(int parameter, int intState);
int simGetInt32Param_internal(int parameter, int* intState);
int simGetUInt64Param_internal(int parameter, unsigned long long int* intState);
int simSetFloatParam_internal(int parameter, double floatState);
int simGetFloatParam_internal(int parameter, double* floatState);
int simSetStringParam_internal(int parameter, const char* str);
char* simGetStringParam_internal(int parameter);
int simSetArrayParam_internal(int parameter, const double* arrayOfValues);
int simGetArrayParam_internal(int parameter, double* arrayOfValues);
int simSetNamedStringParam_internal(const char* paramName, const char* stringParam, int paramLength);
char* simGetNamedStringParam_internal(const char* paramName, int* paramLength);
int simSetInt32Signal_internal(const char* signalName, int signalValue);
int simGetInt32Signal_internal(const char* signalName, int* signalValue);
int simClearInt32Signal_internal(const char* signalName);
int simSetFloatSignal_internal(const char* signalName, double signalValue);
int simGetFloatSignal_internal(const char* signalName, double* signalValue);
int simClearFloatSignal_internal(const char* signalName);
int simSetStringSignal_internal(const char* signalName, const char* signalValue, int stringLength);
char* simGetStringSignal_internal(const char* signalName, int* stringLength);
int simClearStringSignal_internal(const char* signalName);
char* simGetSignalName_internal(int signalIndex, int signalType);
int simSetLightParameters_internal(int objectHandle, int state, const float* setToNULL, const float* diffusePart,
                                   const float* specularPart);
int simGetLightParameters_internal(int objectHandle, double* setToNULL, double* diffusePart, double* specularPart);
int simGetObjectInt32Param_internal(int objectHandle, int parameterID, int* parameter);
int simSetObjectInt32Param_internal(int objectHandle, int parameterID, int parameter);
int simGetObjectFloatParam_internal(int objectHandle, int parameterID, double* parameter);
int simSetObjectFloatParam_internal(int objectHandle, int parameterID, double parameter);
double* simGetObjectFloatArrayParam_internal(int objectHandle, int parameterID, int* size);
int simSetObjectFloatArrayParam_internal(int objectHandle, int parameterID, const double* params, int size);
char* simGetObjectStringParam_internal(int objectHandle, int parameterID, int* parameterLength);
int simSetObjectStringParam_internal(int objectHandle, int parameterID, const char* parameter, int parameterLength);
int simWriteCustomDataBlock_internal(int objectHandle, const char* tagName, const char* data, int dataSize);
char* simReadCustomDataBlock_internal(int objectHandle, const char* tagName, int* dataSize);
char* simReadCustomDataBlockTags_internal(int objectHandle, int* tagCount);
double simGetEngineFloatParam_internal(int paramId, int objectHandle, const void* object, bool* ok);
int simGetEngineInt32Param_internal(int paramId, int objectHandle, const void* object, bool* ok);
bool simGetEngineBoolParam_internal(int paramId, int objectHandle, const void* object, bool* ok);
int simSetEngineFloatParam_internal(int paramId, int objectHandle, const void* object, double val);
int simSetEngineInt32Param_internal(int paramId, int objectHandle, const void* object, int val);
int simSetEngineBoolParam_internal(int paramId, int objectHandle, const void* object, bool val);
int simSetObjectProperty_internal(int objectHandle, int prop);
int simGetObjectProperty_internal(int objectHandle);
int simSetObjectSpecialProperty_internal(int objectHandle, int prop);
int simGetObjectSpecialProperty_internal(int objectHandle);
int simSetModelProperty_internal(int objectHandle, int modelProperty);
int simGetModelProperty_internal(int objectHandle);
