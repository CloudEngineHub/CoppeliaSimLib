// single precision, non-deprecated:
SIM_DLLEXPORT int simGetShapeViz(int shapeHandle, int index, struct SShapeVizInfof* info);
SIM_DLLEXPORT int simSetFloatParam(int parameter, float floatState);
SIM_DLLEXPORT int simGetFloatParam(int parameter, float* floatState);
SIM_DLLEXPORT int simSetArrayParam(int parameter, const float* arrayOfValues);
SIM_DLLEXPORT int simGetArrayParam(int parameter, float* arrayOfValues);
SIM_DLLEXPORT int simGetObjectMatrix(int objectHandle, int relativeToObjectHandle, float* matrix);
SIM_DLLEXPORT int simSetObjectMatrix(int objectHandle, int relativeToObjectHandle, const float* matrix);
SIM_DLLEXPORT int simGetObjectPose(int objectHandle, int relativeToObjectHandle, float* pose);
SIM_DLLEXPORT int simSetObjectPose(int objectHandle, int relativeToObjectHandle, const float* pose);
SIM_DLLEXPORT int simGetObjectPosition(int objectHandle, int relativeToObjectHandle, float* position);
SIM_DLLEXPORT int simSetObjectPosition(int objectHandle, int relativeToObjectHandle, const float* position);
SIM_DLLEXPORT int simGetObjectOrientation(int objectHandle, int relativeToObjectHandle, float* eulerAngles);
SIM_DLLEXPORT int simGetObjectQuaternion(int objectHandle, int relativeToObjectHandle, float* quaternion);
SIM_DLLEXPORT int simSetObjectQuaternion(int objectHandle, int relativeToObjectHandle, const float* quaternion);
SIM_DLLEXPORT int simSetObjectOrientation(int objectHandle, int relativeToObjectHandle, const float* eulerAngles);
SIM_DLLEXPORT int simGetJointPosition(int objectHandle, float* position);
SIM_DLLEXPORT int simSetJointPosition(int objectHandle, float position);
SIM_DLLEXPORT int simSetJointTargetPosition(int objectHandle, float targetPosition);
SIM_DLLEXPORT int simGetJointTargetPosition(int objectHandle, float* targetPosition);
SIM_DLLEXPORT int simGetObjectChildPose(int objectHandle, float* pose);
SIM_DLLEXPORT int simSetObjectChildPose(int objectHandle, const float* pose);
SIM_DLLEXPORT int simGetJointInterval(int objectHandle, bool* cyclic, float* interval);
SIM_DLLEXPORT int simSetJointInterval(int objectHandle, bool cyclic, const float* interval);
SIM_DLLEXPORT int simBuildIdentityMatrix(float* matrix);
SIM_DLLEXPORT int simBuildMatrix(const float* position, const float* eulerAngles, float* matrix);
SIM_DLLEXPORT int simBuildPose(const float* position, const float* eulerAngles, float* pose);
SIM_DLLEXPORT int simGetEulerAnglesFromMatrix(const float* matrix, float* eulerAngles);
SIM_DLLEXPORT int simInvertMatrix(float* matrix);
SIM_DLLEXPORT int simMultiplyMatrices(const float* matrixIn1, const float* matrixIn2, float* matrixOut);
SIM_DLLEXPORT int simMultiplyPoses(const float* poseIn1, const float* poseIn2, float* poseOut);
SIM_DLLEXPORT int simInvertPose(float* pose);
SIM_DLLEXPORT int simInterpolatePoses(const float* poseIn1, const float* poseIn2, float interpolFactor, float* poseOut);
SIM_DLLEXPORT int simPoseToMatrix(const float* poseIn, float* matrixOut);
SIM_DLLEXPORT int simMatrixToPose(const float* matrixIn, float* poseOut);
SIM_DLLEXPORT int simInterpolateMatrices(const float* matrixIn1, const float* matrixIn2, float interpolFactor,
                                         float* matrixOut);
SIM_DLLEXPORT int simTransformVector(const float* matrix, float* vect);
SIM_DLLEXPORT float simGetSimulationTime();
SIM_DLLEXPORT float simGetSystemTime();
SIM_DLLEXPORT int simHandleProximitySensor(int sensorHandle, float* detectedPoint, int* detectedObjectHandle,
                                           float* normalVector);
SIM_DLLEXPORT int simReadProximitySensor(int sensorHandle, float* detectedPoint, int* detectedObjectHandle,
                                         float* normalVector);
SIM_DLLEXPORT int simHandleDynamics(float deltaTime);
SIM_DLLEXPORT int simCheckProximitySensor(int sensorHandle, int entityHandle, float* detectedPoint);
SIM_DLLEXPORT int simCheckProximitySensorEx(int sensorHandle, int entityHandle, int detectionMode,
                                            float detectionThreshold, float maxAngle, float* detectedPoint,
                                            int* detectedObjectHandle, float* normalVector);
SIM_DLLEXPORT int simCheckProximitySensorEx2(int sensorHandle, float* vertexPointer, int itemType, int itemCount,
                                             int detectionMode, float detectionThreshold, float maxAngle,
                                             float* detectedPoint, float* normalVector);
SIM_DLLEXPORT int simCheckCollisionEx(int entity1Handle, int entity2Handle, float** intersectionSegments);
SIM_DLLEXPORT int simCheckDistance(int entity1Handle, int entity2Handle, float threshold, float* distanceData);
SIM_DLLEXPORT int simSetSimulationTimeStep(float timeStep);
SIM_DLLEXPORT float simGetSimulationTimeStep();
SIM_DLLEXPORT int simAdjustRealTimeTimer(int instanceIndex, float deltaTime);
SIM_DLLEXPORT int simFloatingViewAdd(float posX, float posY, float sizeX, float sizeY, int options);
SIM_DLLEXPORT int simHandleGraph(int graphHandle, float simulationTime);
SIM_DLLEXPORT int simSetGraphStreamTransformation(int graphHandle, int streamId, int trType, float mult, float off,
                                                  int movingAvgPeriod);
SIM_DLLEXPORT int simAddGraphStream(int graphHandle, const char* streamName, const char* unitStr, int options,
                                    const float* color, float cyclicRange);
SIM_DLLEXPORT int simAddGraphCurve(int graphHandle, const char* curveName, int dim, const int* streamIds,
                                   const float* defaultValues, const char* unitStr, int options, const float* color,
                                   int curveWidth);
SIM_DLLEXPORT int simSetGraphStreamValue(int graphHandle, int streamId, float value);
SIM_DLLEXPORT int simSetJointTargetVelocity(int objectHandle, float targetVelocity);
SIM_DLLEXPORT int simGetJointTargetVelocity(int objectHandle, float* targetVelocity);
SIM_DLLEXPORT int simScaleObjects(const int* objectHandles, int objectCount, float scalingFactor,
                                  bool scalePositionsToo);
SIM_DLLEXPORT int simAddDrawingObject(int objectType, float size, float duplicateTolerance, int parentObjectHandle,
                                      int maxItemCount, const float* color, const float* setToNULL,
                                      const float* setToNULL2, const float* setToNULL3);
SIM_DLLEXPORT int simAddDrawingObjectItem(int objectHandle, const float* itemData);
SIM_DLLEXPORT float simGetObjectSizeFactor(int objectHandle);
SIM_DLLEXPORT int simSetFloatSignal(const char* signalName, float signalValue);
SIM_DLLEXPORT int simGetFloatSignal(const char* signalName, float* signalValue);
SIM_DLLEXPORT int simReadForceSensor(int objectHandle, float* forceVector, float* torqueVector);
SIM_DLLEXPORT int simGetLightParameters(int objectHandle, float* setToNULL, float* diffusePart, float* specularPart);
SIM_DLLEXPORT int simGetVelocity(int shapeHandle, float* linearVelocity, float* angularVelocity);
SIM_DLLEXPORT int simGetObjectVelocity(int objectHandle, float* linearVelocity, float* angularVelocity);
SIM_DLLEXPORT int simGetJointVelocity(int jointHandle, float* velocity);
SIM_DLLEXPORT int simAddForceAndTorque(int shapeHandle, const float* force, const float* torque);
SIM_DLLEXPORT int simAddForce(int shapeHandle, const float* position, const float* force);
SIM_DLLEXPORT int simGetContactInfo(int dynamicPass, int objectHandle, int index, int* objectHandles,
                                    float* contactInfo);
SIM_DLLEXPORT int simImportShape(int fileformat, const char* pathAndFilename, int options,
                                 float identicalVerticeTolerance, float scalingFactor);
SIM_DLLEXPORT int simImportMesh(int fileformat, const char* pathAndFilename, int options,
                                float identicalVerticeTolerance, float scalingFactor, float*** vertices,
                                int** verticesSizes, int*** indices, int** indicesSizes, float*** reserved,
                                char*** names);
SIM_DLLEXPORT int simExportMesh(int fileformat, const char* pathAndFilename, int options, float scalingFactor,
                                int elementCount, const float** vertices, const int* verticesSizes, const int** indices,
                                const int* indicesSizes, float** reserved, const char** names);
SIM_DLLEXPORT int simCreateMeshShape(int options, float shadingAngle, const float* vertices, int verticesSize,
                                     const int* indices, int indicesSize, float* reserved);
SIM_DLLEXPORT int simCreatePrimitiveShape(int primitiveType, const float* sizes, int options);
SIM_DLLEXPORT int simCreateHeightfieldShape(int options, float shadingAngle, int xPointCount, int yPointCount,
                                            float xSize, const float* heights);
SIM_DLLEXPORT int simGetShapeMesh(int shapeHandle, float** vertices, int* verticesSize, int** indices, int* indicesSize,
                                  float** normals);
SIM_DLLEXPORT int simCreateJoint(int jointType, int jointMode, int options, const float* sizes, const float* reservedA,
                                 const float* reservedB);
SIM_DLLEXPORT int simGetObjectFloatParam(int objectHandle, int ParamID, float* Param);
SIM_DLLEXPORT int simSetObjectFloatParam(int objectHandle, int ParamID, float Param);
SIM_DLLEXPORT float* simGetObjectFloatArrayParam(int objectHandle, int parameterID, int* size);
SIM_DLLEXPORT int simSetObjectFloatArrayParam(int objectHandle, int parameterID, const float* params, int size);
SIM_DLLEXPORT int simGetRotationAxis(const float* matrixStart, const float* matrixGoal, float* axis, float* angle);
SIM_DLLEXPORT int simRotateAroundAxis(const float* matrixIn, const float* axis, const float* axisPos, float angle,
                                      float* matrixOut);
SIM_DLLEXPORT int simGetJointForce(int jointHandle, float* forceOrTorque);
SIM_DLLEXPORT int simGetJointTargetForce(int jointHandle, float* forceOrTorque);
SIM_DLLEXPORT int simSetJointTargetForce(int objectHandle, float forceOrTorque, bool signedValue);
SIM_DLLEXPORT int simCameraFitToView(int viewHandleOrIndex, int objectCount, const int* objectHandles, int options,
                                     float scaling);
SIM_DLLEXPORT int simHandleVisionSensor(int visionSensorHandle, float** auxValues, int** auxValuesCount);
SIM_DLLEXPORT int simReadVisionSensor(int visionSensorHandle, float** auxValues, int** auxValuesCount);
SIM_DLLEXPORT int simCheckVisionSensor(int visionSensorHandle, int entityHandle, float** auxValues,
                                       int** auxValuesCount);
SIM_DLLEXPORT unsigned char* simGetVisionSensorImg(int sensorHandle, int options, float rgbaCutOff, const int* pos,
                                                   const int* size, int* resolution);
SIM_DLLEXPORT int simCreateDummy(float size, const float* reserved);
SIM_DLLEXPORT int simCreateProximitySensor(int sensorType, int subType, int options, const int* intParams,
                                           const float* floatParams, const float* reserved);
SIM_DLLEXPORT int simCreateForceSensor(int options, const int* intParams, const float* floatParams,
                                       const float* reserved);
SIM_DLLEXPORT int simCreateVisionSensor(int options, const int* intParams, const float* floatParams,
                                        const float* reserved);
SIM_DLLEXPORT int simConvexDecompose(int shapeHandle, int options, const int* intParams, const float* floatParams);
SIM_DLLEXPORT int simWriteTexture(int textureId, int options, const char* data, int posX, int posY, int sizeX,
                                  int sizeY, float interpol);
SIM_DLLEXPORT int simCreateTexture(const char* fileName, int options, const float* planeSizes, const float* scalingUV,
                                   const float* xy_g, int fixedResolution, int* textureId, int* resolution,
                                   const void* reserved);
SIM_DLLEXPORT int simGetShapeGeomInfo(int shapeHandle, int* intData, float* floatData, void* reserved);
SIM_DLLEXPORT int simScaleObject(int objectHandle, float xScale, float yScale, float zScale, int options);
SIM_DLLEXPORT int simSetShapeTexture(int shapeHandle, int textureId, int mappingMode, int options,
                                     const float* uvScaling, const float* position, const float* orientation);
SIM_DLLEXPORT int simTransformImage(unsigned char* image, const int* resolution, int options, const float* floatParams,
                                    const int* intParams, void* reserved);
SIM_DLLEXPORT int simGetQHull(const float* inVertices, int inVerticesL, float** verticesOut, int* verticesOutL,
                              int** indicesOut, int* indicesOutL, int reserved1, const float* reserved2);
SIM_DLLEXPORT int simGetDecimatedMesh(const float* inVertices, int inVerticesL, const int* inIndices, int inIndicesL,
                                      float** verticesOut, int* verticesOutL, int** indicesOut, int* indicesOutL,
                                      float decimationPercent, int reserved1, const float* reserved2);
SIM_DLLEXPORT int simComputeMassAndInertia(int shapeHandle, float density);
SIM_DLLEXPORT float simGetEngineFloatParam(int paramId, int objectHandle, const void* object, bool* ok);
SIM_DLLEXPORT int simSetEngineFloatParam(int paramId, int objectHandle, const void* object, float val);
SIM_DLLEXPORT int simCreateOctree(float voxelSize, int options, float pointSize, void* reserved);
SIM_DLLEXPORT int simCreatePointCloud(float maxVoxelSize, int maxPtCntPerVoxel, int options, float pointSize,
                                      void* reserved);
SIM_DLLEXPORT int simSetPointCloudOptions(int pointCloudHandle, float maxVoxelSize, int maxPtCntPerVoxel, int options,
                                          float pointSize, void* reserved);
SIM_DLLEXPORT int simGetPointCloudOptions(int pointCloudHandle, float* maxVoxelSize, int* maxPtCntPerVoxel,
                                          int* options, float* pointSize, void* reserved);
SIM_DLLEXPORT int simInsertVoxelsIntoOctree(int octreeHandle, int options, const float* pts, int ptCnt,
                                            const unsigned char* color, const unsigned int* tag, void* reserved);
SIM_DLLEXPORT int simRemoveVoxelsFromOctree(int octreeHandle, int options, const float* pts, int ptCnt, void* reserved);
SIM_DLLEXPORT int simInsertPointsIntoPointCloud(int pointCloudHandle, int options, const float* pts, int ptCnt,
                                                const unsigned char* color, void* optionalValues);
SIM_DLLEXPORT int simRemovePointsFromPointCloud(int pointCloudHandle, int options, const float* pts, int ptCnt,
                                                float tolerance, void* reserved);
SIM_DLLEXPORT int simIntersectPointsWithPointCloud(int pointCloudHandle, int options, const float* pts, int ptCnt,
                                                   float tolerance, void* reserved);
SIM_DLLEXPORT const float* simGetOctreeVoxels(int octreeHandle, int* ptCnt, void* reserved);
SIM_DLLEXPORT const float* simGetPointCloudPoints(int pointCloudHandle, int* ptCnt, void* reserved);
SIM_DLLEXPORT int simInsertObjectIntoPointCloud(int pointCloudHandle, int objectHandle, int options, float gridSize,
                                                const unsigned char* color, void* optionalValues);
SIM_DLLEXPORT int simSubtractObjectFromPointCloud(int pointCloudHandle, int objectHandle, int options, float tolerance,
                                                  void* reserved);
SIM_DLLEXPORT int simCheckOctreePointOccupancy(int octreeHandle, int options, const float* points, int ptCnt,
                                               unsigned int* tag, unsigned long long int* location, void* reserved);
SIM_DLLEXPORT int simApplyTexture(int shapeHandle, const float* textureCoordinates, int textCoordSize,
                                  const unsigned char* texture, const int* textureResolution, int options);
SIM_DLLEXPORT int simSetJointDependency(int jointHandle, int masterJointHandle, float offset, float multCoeff);
SIM_DLLEXPORT int simGetJointDependency(int jointHandle, int* masterJointHandle, float* offset, float* multCoeff);
SIM_DLLEXPORT int simGetShapeMass(int shapeHandle, float* mass);
SIM_DLLEXPORT int simSetShapeMass(int shapeHandle, float mass);
SIM_DLLEXPORT int simGetShapeInertia(int shapeHandle, float* inertiaMatrix, float* transformationMatrix);
SIM_DLLEXPORT int simSetShapeInertia(int shapeHandle, const float* inertiaMatrix, const float* transformationMatrix);
SIM_DLLEXPORT int simGenerateShapeFromPath(const float* path, int pathSize, const float* section, int sectionSize,
                                           int options, const float* upVector, float reserved);
SIM_DLLEXPORT float simGetClosestPosOnPath(const float* path, int pathSize, const float* pathLengths,
                                           const float* absPt);
SIM_DLLEXPORT int simExtCallScriptFunction(int scriptHandleOrType, const char* functionNameAtScriptName,
                                           const int* inIntData, int inIntCnt, const float* inFloatData, int inFloatCnt,
                                           const char** inStringData, int inStringCnt, const char* inBufferData,
                                           int inBufferCnt, int** outIntData, int* outIntCnt, float** outFloatData,
                                           int* outFloatCnt, char*** outStringData, int* outStringCnt,
                                           char** outBufferData, int* outBufferSize);
SIM_DLLEXPORT void _simGetObjectLocalTransformation(const void* object, float* pos, float* quat,
                                                    bool excludeFirstJointTransformation);
SIM_DLLEXPORT void _simSetObjectLocalTransformation(void* object, const float* pos, const float* quat, float simTime);
SIM_DLLEXPORT void _simDynReportObjectCumulativeTransformation(void* object, const float* pos, const float* quat,
                                                               float simTime);
SIM_DLLEXPORT void _simSetObjectCumulativeTransformation(void* object, const float* pos, const float* quat,
                                                         bool keepChildrenInPlace);
SIM_DLLEXPORT void _simGetObjectCumulativeTransformation(const void* object, float* pos, float* quat,
                                                         bool excludeFirstJointTransformation);
SIM_DLLEXPORT void _simSetJointVelocity(const void* joint, float vel);
SIM_DLLEXPORT void _simSetJointPosition(const void* joint, float pos);
SIM_DLLEXPORT float _simGetJointPosition(const void* joint);
SIM_DLLEXPORT void _simSetDynamicMotorPositionControlTargetPosition(const void* joint, float pos);
SIM_DLLEXPORT void _simGetInitialDynamicVelocity(const void* shape, float* vel);
SIM_DLLEXPORT void _simSetInitialDynamicVelocity(void* shape, const float* vel);
SIM_DLLEXPORT void _simGetInitialDynamicAngVelocity(const void* shape, float* angularVel);
SIM_DLLEXPORT void _simSetInitialDynamicAngVelocity(void* shape, const float* angularVel);
SIM_DLLEXPORT void _simSetShapeDynamicVelocity(void* shape, const float* linear, const float* angular, float simTime);
SIM_DLLEXPORT void _simGetAdditionalForceAndTorque(const void* shape, float* force, float* torque);
SIM_DLLEXPORT bool _simGetJointPositionInterval(const void* joint, float* minValue, float* rangeValue);
SIM_DLLEXPORT float _simGetDynamicMotorTargetPosition(const void* joint);
SIM_DLLEXPORT float _simGetDynamicMotorTargetVelocity(const void* joint);
SIM_DLLEXPORT float _simGetDynamicMotorMaxForce(const void* joint);
SIM_DLLEXPORT float _simGetDynamicMotorUpperLimitVelocity(const void* joint);
SIM_DLLEXPORT void _simSetDynamicMotorReflectedPositionFromDynamicEngine(void* joint, float pos, float simTime);
SIM_DLLEXPORT void _simSetJointSphericalTransformation(void* joint, const float* quat, float simTime);
SIM_DLLEXPORT void _simAddForceSensorCumulativeForcesAndTorques(void* forceSensor, const float* force,
                                                                const float* torque, int totalPassesCount,
                                                                float simTime);
SIM_DLLEXPORT void _simAddJointCumulativeForcesOrTorques(void* joint, float forceOrTorque, int totalPassesCount,
                                                         float simTime);
SIM_DLLEXPORT float _simGetMass(const void* geomInfo);
SIM_DLLEXPORT float _simGetLocalInertiaInfo(const void* object, float* pos, float* quat, float* diagI);
SIM_DLLEXPORT void _simGetPurePrimitiveSizes(const void* geometric, float* sizes);
SIM_DLLEXPORT void _simGetVerticesLocalFrame(const void* shape, const void* geometric, float* pos, float* quat);
SIM_DLLEXPORT const float* _simGetHeightfieldData(const void* geometric, int* xCount, int* yCount, float* minHeight,
                                                  float* maxHeight);
SIM_DLLEXPORT void _simGetGravity(float* gravity);
SIM_DLLEXPORT float _simGetPureHollowScaling(const void* geometric);
SIM_DLLEXPORT void _simDynCallback(const int* intData, const float* floatData);
SIM_DLLEXPORT int _simHandleJointControl(const void* joint, int auxV, const int* inputValuesInt,
                                         const float* inputValuesFloat, float* outputValues);
SIM_DLLEXPORT int _simHandleCustomContact(int objHandle1, int objHandle2, int engine, int* dataInt, float* dataFloat);
SIM_DLLEXPORT void _simGetCumulativeMeshes(const void* shape, const void* geomInfo, float** vertices, int* verticesSize,
                                           int** indices, int* indicesSize);

SIM_DLLEXPORT bool _simGetDistanceBetweenEntitiesIfSmaller(int entity1ID, int entity2ID, float* distance, float* ray,
                                                           int* cacheBuffer,
                                                           bool overrideMeasurableFlagIfNonCollection1,
                                                           bool overrideMeasurableFlagIfNonCollection2,
                                                           bool pathPlanningRoutineCalling);

// Deprecated begin
SIM_DLLEXPORT int simRunSimulator(const char* applicationName, int options, void (*setToNull1)(), void (*setToNull2)(),
                                  void (*setToNull3)());
SIM_DLLEXPORT int simRunSimulatorEx(const char* applicationName, int options, void (*setToNull1)(),
                                    void (*setToNull2)(), void (*setToNull3)(), int stopDelay,
                                    const char* sceneOrModelToLoad);
SIM_DLLEXPORT int simGetMaterialId(const char* materialName);
SIM_DLLEXPORT int simGetShapeMaterial(int shapeHandle);
SIM_DLLEXPORT int simHandleVarious();
SIM_DLLEXPORT int simSerialPortOpen(int portNumber, int baudRate, void* reserved1, void* reserved2);
SIM_DLLEXPORT int simSerialPortClose(int portNumber);
SIM_DLLEXPORT int simSerialPortSend(int portNumber, const char* data, int dataLength);
SIM_DLLEXPORT int simSerialPortRead(int portNumber, char* buffer, int dataLengthToRead);
SIM_DLLEXPORT int simGetPathPlanningHandle(const char* pathPlanningObjectName);
SIM_DLLEXPORT int simGetMotionPlanningHandle(const char* motionPlanningObjectName);
SIM_DLLEXPORT int simRemoveMotionPlanning(int motionPlanningHandle);
SIM_DLLEXPORT int simPerformPathSearchStep(int temporaryPathSearchObject, bool abortSearch);
SIM_DLLEXPORT int simLockInterface(bool locked);
SIM_DLLEXPORT int simCopyPasteSelectedObjects();
SIM_DLLEXPORT int simResetPath(int pathHandle);
SIM_DLLEXPORT int simResetJoint(int jointHandle);
SIM_DLLEXPORT int simAppendScriptArrayEntry(const char* reservedSetToNull, int scriptHandleOrType,
                                            const char* arrayNameAtScriptName, const char* keyName, const char* data,
                                            const int* what);
SIM_DLLEXPORT int simClearScriptVariable(const char* reservedSetToNull, int scriptHandleOrType,
                                         const char* variableNameAtScriptName);
SIM_DLLEXPORT int simAddSceneCustomData(int header, const char* data, int dataLength);
SIM_DLLEXPORT int simGetSceneCustomDataLength(int header);
SIM_DLLEXPORT int simGetSceneCustomData(int header, char* data);
SIM_DLLEXPORT int simAddObjectCustomData(int objectHandle, int header, const char* data, int dataLength);
SIM_DLLEXPORT int simGetObjectCustomDataLength(int objectHandle, int header);
SIM_DLLEXPORT int simGetObjectCustomData(int objectHandle, int header, char* data);
SIM_DLLEXPORT int simCreateUI(const char* uiName, int menuAttributes, const int* clientSize, const int* cellSize,
                              int* buttonHandles);
SIM_DLLEXPORT int simCreateUIButton(int uiHandle, const int* position, const int* size, int buttonProperty);
SIM_DLLEXPORT int simGetUIHandle(const char* uiName);
SIM_DLLEXPORT int simGetUIProperty(int uiHandle);
SIM_DLLEXPORT int simGetUIEventButton(int uiHandle, int* auxiliaryValues);
SIM_DLLEXPORT int simSetUIProperty(int uiHandle, int elementProperty);
SIM_DLLEXPORT int simGetUIButtonProperty(int uiHandle, int buttonHandle);
SIM_DLLEXPORT int simSetUIButtonProperty(int uiHandle, int buttonHandle, int buttonProperty);
SIM_DLLEXPORT int simGetUIButtonSize(int uiHandle, int buttonHandle, int* size);
SIM_DLLEXPORT int simSetUIButtonLabel(int uiHandle, int buttonHandle, const char* upStateLabel,
                                      const char* downStateLabel);
SIM_DLLEXPORT char* simGetUIButtonLabel(int uiHandle, int buttonHandle);
SIM_DLLEXPORT int simSetUISlider(int uiHandle, int buttonHandle, int position);
SIM_DLLEXPORT int simGetUISlider(int uiHandle, int buttonHandle);
SIM_DLLEXPORT int simSetUIButtonTexture(int uiHandle, int buttonHandle, const int* size, const char* textureData);
SIM_DLLEXPORT int simCreateUIButtonArray(int uiHandle, int buttonHandle);
SIM_DLLEXPORT int simDeleteUIButtonArray(int uiHandle, int buttonHandle);
SIM_DLLEXPORT int simRemoveUI(int uiHandle);
SIM_DLLEXPORT int simSetUIPosition(int uiHandle, const int* position);
SIM_DLLEXPORT int simGetUIPosition(int uiHandle, int* position);
SIM_DLLEXPORT int simLoadUI(const char* filename, int maxCount, int* uiHandles);
SIM_DLLEXPORT int simSaveUI(int count, const int* uiHandles, const char* filename);
SIM_DLLEXPORT int simHandleGeneralCallbackScript(int callbackId, int callbackTag, void* additionalData);
SIM_DLLEXPORT int simRegisterCustomLuaFunction(const char* funcName, const char* callTips,
                                               const int* inputArgumentTypes, void (*callBack)(struct SLuaCallBack* p));
SIM_DLLEXPORT int simRegisterCustomLuaVariable(const char* varName, const char* varValue);
SIM_DLLEXPORT int simGetMechanismHandle(const char* mechanismName);
SIM_DLLEXPORT int simHandleMechanism(int mechanismHandle);
SIM_DLLEXPORT int simHandleCustomizationScripts(int callType);
SIM_DLLEXPORT int simCallScriptFunction(int scriptHandleOrType, const char* functionNameAtScriptName,
                                        SLuaCallBack* data, const char* reservedSetToNull);
SIM_DLLEXPORT char* simGetScriptSimulationParameter(int scriptHandle, const char* parameterName, int* parameterLength);
SIM_DLLEXPORT int simSetScriptSimulationParameter(int scriptHandle, const char* parameterName,
                                                  const char* parameterValue, int parameterLength);
SIM_DLLEXPORT int simResetMill(int millHandle);
SIM_DLLEXPORT int simResetMilling(int objectHandle);
SIM_DLLEXPORT int simApplyMilling(int objectHandle);
SIM_DLLEXPORT int simGetNameSuffix(const char* name);
SIM_DLLEXPORT int simSetNameSuffix(int nameSuffixNumber);
SIM_DLLEXPORT int simAddStatusbarMessage(const char* message);
SIM_DLLEXPORT char* simGetScriptRawBuffer(int scriptHandle, int bufferHandle);
SIM_DLLEXPORT int simSetScriptRawBuffer(int scriptHandle, const char* buffer, int bufferSize);
SIM_DLLEXPORT int simReleaseScriptRawBuffer(int scriptHandle, int bufferHandle);
SIM_DLLEXPORT int simRemoveIkGroup(int ikGroupHandle);
SIM_DLLEXPORT int simExportIk(const char* pathAndFilename, int reserved1, void* reserved2);
SIM_DLLEXPORT int simComputeJacobian(int ikGroupHandle, int options, void* reserved);
SIM_DLLEXPORT int simGetIkGroupHandle(const char* ikGroupName);
SIM_DLLEXPORT int simHandleIkGroup(int ikGroupHandle);
SIM_DLLEXPORT int simSetThreadIsFree(bool freeMode);
SIM_DLLEXPORT int simTubeOpen(int dataHeader, const char* dataName, int readBufferSize, bool notUsedButKeepZero);
SIM_DLLEXPORT int simTubeClose(int tubeHandle);
SIM_DLLEXPORT int simTubeWrite(int tubeHandle, const char* data, int dataLength);
SIM_DLLEXPORT char* simTubeRead(int tubeHandle, int* dataLength);
SIM_DLLEXPORT int simTubeStatus(int tubeHandle, int* readPacketsCount, int* writePacketsCount);
SIM_DLLEXPORT char* simReceiveData(int dataHeader, const char* dataName, int antennaHandle, int index, int* dataLength,
                                   int* senderID, int* dataHeaderR, char** dataNameR);
SIM_DLLEXPORT int simInsertPathCtrlPoints(int pathHandle, int options, int startIndex, int ptCnt, const void* ptData);
SIM_DLLEXPORT int simCutPathCtrlPoints(int pathHandle, int startIndex, int ptCnt);
SIM_DLLEXPORT int simGetThreadId();
SIM_DLLEXPORT int simSwitchThread();
SIM_DLLEXPORT int simLockResources(int lockType, int reserved);
SIM_DLLEXPORT int simUnlockResources(int lockHandle);
SIM_DLLEXPORT char* simGetUserParameter(int objectHandle, const char* parameterName, int* parameterLength);
SIM_DLLEXPORT int simSetUserParameter(int objectHandle, const char* parameterName, const char* parameterValue,
                                      int parameterLength);
SIM_DLLEXPORT int simGetCollectionHandle(const char* collectionName);
SIM_DLLEXPORT int simRemoveCollection(int collectionHandle);
SIM_DLLEXPORT int simEmptyCollection(int collectionHandle);
SIM_DLLEXPORT char* simGetCollectionName(int collectionHandle);
SIM_DLLEXPORT int simSetCollectionName(int collectionHandle, const char* collectionName);
SIM_DLLEXPORT int simCreateCollection(const char* collectionName, int options);
SIM_DLLEXPORT int simAddObjectToCollection(int collectionHandle, int objectHandle, int what, int options);
SIM_DLLEXPORT int simGetCollisionHandle(const char* collisionObjectName);
SIM_DLLEXPORT int simGetDistanceHandle(const char* distanceObjectName);
SIM_DLLEXPORT int simResetCollision(int collisionObjectHandle);
SIM_DLLEXPORT int simResetDistance(int distanceObjectHandle);
SIM_DLLEXPORT int simHandleCollision(int collisionObjectHandle);
SIM_DLLEXPORT int simReadCollision(int collisionObjectHandle);
SIM_DLLEXPORT int simRemoveBanner(int bannerID);
SIM_DLLEXPORT int simGetObjectIntParameter(int objectHandle, int ParamID, int* Param);
SIM_DLLEXPORT int simSetObjectIntParameter(int objectHandle, int ParamID, int Param);
SIM_DLLEXPORT int simGetObjectInt32Parameter(int objectHandle, int ParamID, int* Param);
SIM_DLLEXPORT int simSetObjectInt32Parameter(int objectHandle, int ParamID, int Param);
SIM_DLLEXPORT char* simGetObjectStringParameter(int objectHandle, int ParamID, int* ParamLength);
SIM_DLLEXPORT int simSetObjectStringParameter(int objectHandle, int ParamID, const char* Param, int ParamLength);
SIM_DLLEXPORT int simSetBooleanParameter(int parameter, bool boolState);
SIM_DLLEXPORT int simGetBooleanParameter(int parameter);
SIM_DLLEXPORT int simSetBoolParameter(int parameter, bool boolState);
SIM_DLLEXPORT int simGetBoolParameter(int parameter);
SIM_DLLEXPORT int simSetIntegerParameter(int parameter, int intState);
SIM_DLLEXPORT int simGetIntegerParameter(int parameter, int* intState);
SIM_DLLEXPORT int simSetInt32Parameter(int parameter, int intState);
SIM_DLLEXPORT int simGetInt32Parameter(int parameter, int* intState);
SIM_DLLEXPORT int simGetUInt64Parameter(int parameter, unsigned long long int* intState);
SIM_DLLEXPORT int simSetStringParameter(int parameter, const char* str);
SIM_DLLEXPORT char* simGetStringParameter(int parameter);
SIM_DLLEXPORT int simGetEngineInt32Parameter(int paramId, int objectHandle, const void* object, bool* ok);
SIM_DLLEXPORT bool simGetEngineBoolParameter(int paramId, int objectHandle, const void* object, bool* ok);
SIM_DLLEXPORT int simSetEngineInt32Parameter(int paramId, int objectHandle, const void* object, int val);
SIM_DLLEXPORT int simSetEngineBoolParameter(int paramId, int objectHandle, const void* object, bool val);
SIM_DLLEXPORT int simIsHandleValid(int generalObjectHandle, int generalObjectType);
SIM_DLLEXPORT int simAddModuleMenuEntry(const char* entryLabel, int itemCount, int* itemHandles);
SIM_DLLEXPORT int simSetModuleMenuItemState(int itemHandle, int state, const char* label);
SIM_DLLEXPORT int simSetIntegerSignal(const char* signalName, int signalValue);
SIM_DLLEXPORT int simGetIntegerSignal(const char* signalName, int* signalValue);
SIM_DLLEXPORT int simClearIntegerSignal(const char* signalName);
SIM_DLLEXPORT char* simGetObjectName(int objectHandle);
SIM_DLLEXPORT int simSetObjectName(int objectHandle, const char* objectName);
SIM_DLLEXPORT char* simGetScriptName(int scriptHandle);
SIM_DLLEXPORT int simGetScriptHandle(const char* scriptName);
SIM_DLLEXPORT int simSetScriptVariable(int scriptHandleOrType, const char* variableNameAtScriptName, int stackHandle);
SIM_DLLEXPORT int simGetObjectHandle(const char* objectAlias);
SIM_DLLEXPORT int simGetObjectHandleEx(const char* objectAlias, int index, int proxy, int options);
SIM_DLLEXPORT int simGetScript(int index);
SIM_DLLEXPORT int simGetScriptAssociatedWithObject(int objectHandle);
SIM_DLLEXPORT int simGetCustomizationScriptAssociatedWithObject(int objectHandle);
SIM_DLLEXPORT int simGetObjectAssociatedWithScript(int scriptHandle);
SIM_DLLEXPORT char* simGetObjectConfiguration(int objectHandle);
SIM_DLLEXPORT int simSetObjectConfiguration(const char* data);
SIM_DLLEXPORT char* simGetConfigurationTree(int objectHandle);
SIM_DLLEXPORT int simSetConfigurationTree(const char* data);
SIM_DLLEXPORT int simEnableEventCallback(int eventCallbackType, const char* plugin, int reserved);
SIM_DLLEXPORT int simRMLPosition(int dofs, double timeStep, int flags, const double* currentPosVelAccel,
                                 const double* maxVelAccelJerk, const bool* selection, const double* targetPosVel,
                                 double* newPosVelAccel, void* auxData);
SIM_DLLEXPORT int simRMLVelocity(int dofs, double timeStep, int flags, const double* currentPosVelAccel,
                                 const double* maxAccelJerk, const bool* selection, const double* targetVel,
                                 double* newPosVelAccel, void* auxData);
SIM_DLLEXPORT int simRMLPos(int dofs, double smallestTimeStep, int flags, const double* currentPosVelAccel,
                            const double* maxVelAccelJerk, const bool* selection, const double* targetPosVel,
                            void* auxData);
SIM_DLLEXPORT int simRMLVel(int dofs, double smallestTimeStep, int flags, const double* currentPosVelAccel,
                            const double* maxAccelJerk, const bool* selection, const double* targetVel, void* auxData);
SIM_DLLEXPORT int simRMLStep(int handle, double timeStep, double* newPosVelAccel, void* auxData, void* reserved);
SIM_DLLEXPORT int simRMLRemove(int handle);
SIM_DLLEXPORT int simGetSystemTimeInMilliseconds();
SIM_DLLEXPORT unsigned int simGetSystemTimeInMs(int previousTime);
SIM_DLLEXPORT char* simFileDialog(int mode, const char* title, const char* startPath, const char* initName,
                                  const char* extName, const char* ext);
SIM_DLLEXPORT int simMsgBox(int dlgType, int buttons, const char* title, const char* message);
SIM_DLLEXPORT int simGetDialogResult(int genericDialogHandle);
SIM_DLLEXPORT char* simGetDialogInput(int genericDialogHandle);
SIM_DLLEXPORT int simEndDialog(int genericDialogHandle);
SIM_DLLEXPORT int simIsObjectInSelection(int objectHandle);
SIM_DLLEXPORT int simAddObjectToSelection(int what, int objectHandle);
SIM_DLLEXPORT int simRemoveObjectFromSelection(int what, int objectHandle);
SIM_DLLEXPORT int simGetObjectSelectionSize();
SIM_DLLEXPORT int simGetObjectLastSelection();
SIM_DLLEXPORT int simGetObjectSelection(int* objectHandles);
SIM_DLLEXPORT int simDeleteSelectedObjects();
SIM_DLLEXPORT int simSetStringNamedParam(const char* paramName, const char* stringParam, int paramLength);
SIM_DLLEXPORT char* simGetStringNamedParam(const char* paramName, int* paramLength);
SIM_DLLEXPORT int simGetObjectUniqueIdentifier(int objectHandle, int* uniqueIdentifier);
SIM_DLLEXPORT int simBreakForceSensor(int objectHandle);
SIM_DLLEXPORT int simSetScriptText(int scriptHandle, const char* scriptText);
SIM_DLLEXPORT const char* simGetScriptText(int scriptHandle);
SIM_DLLEXPORT int simGetScriptProperty(int scriptHandle, int* scriptProperty, int* associatedObjectHandle);
SIM_DLLEXPORT int simRemoveObject(int objectHandle);
SIM_DLLEXPORT int simGetVisionSensorResolution(int visionSensorHandle, int* resolution);
SIM_DLLEXPORT unsigned char* simGetVisionSensorCharImage(int visionSensorHandle, int* resolutionX, int* resolutionY);
SIM_DLLEXPORT int simSetVisionSensorCharImage(int visionSensorHandle, const unsigned char* image);
SIM_DLLEXPORT void* simBroadcastMessage(int* auxiliaryData, void* customData, int* replyData);
SIM_DLLEXPORT void* simSendModuleMessage(int message, int* auxiliaryData, void* customData, int* replyData);
SIM_DLLEXPORT int simSetDoubleSignal(const char* signalName, double signalValue);
SIM_DLLEXPORT int simGetDoubleSignal(const char* signalName, double* signalValue);
SIM_DLLEXPORT int simClearDoubleSignal(const char* signalName);
SIM_DLLEXPORT int simRemoveParticleObject(int objectHandle);
SIM_DLLEXPORT bool _simGetBulletStickyContact(const void* geomInfo);
SIM_DLLEXPORT bool _simGetParentFollowsDynamic(const void* shape);
SIM_DLLEXPORT void _simSetDynamicJointLocalTransformationPart2IsValid(void* joint, bool valid);
SIM_DLLEXPORT void _simSetDynamicForceSensorLocalTransformationPart2IsValid(void* forceSensor, bool valid);
SIM_DLLEXPORT bool _simIsForceSensorBroken(const void* forceSensor);
SIM_DLLEXPORT void _simSetGeomProxyDynamicsFullRefreshFlag(void* geomData, bool flag);
SIM_DLLEXPORT bool _simGetGeomProxyDynamicsFullRefreshFlag(const void* geomData);
SIM_DLLEXPORT void _simSetShapeIsStaticAndNotRespondableButDynamicTag(const void* shape, bool tag);
SIM_DLLEXPORT bool _simGetShapeIsStaticAndNotRespondableButDynamicTag(const void* shape);
SIM_DLLEXPORT bool _simIsDynamicMotorEnabled(const void* joint);
SIM_DLLEXPORT bool _simIsDynamicMotorPositionCtrlEnabled(const void* joint);
SIM_DLLEXPORT bool _simIsDynamicMotorTorqueModulationEnabled(const void* joint);
SIM_DLLEXPORT int _simGetContactCallbackCount();
SIM_DLLEXPORT const void* _simGetContactCallback(int index);
SIM_DLLEXPORT int _simGetJointCallbackCallOrder(const void* joint);
SIM_DLLEXPORT int simReorientShapeBoundingBox(int shapeHandle, int relativeToHandle, int reservedSetToZero);
SIM_DLLEXPORT int simIsRealTimeSimulationStepNeeded();
SIM_DLLEXPORT int simSetSimulationPassesPerRenderingPass(int p);
SIM_DLLEXPORT int simGetSimulationPassesPerRenderingPass();
SIM_DLLEXPORT int simAdvanceSimulationByOneStep();
SIM_DLLEXPORT int simHandleMainScript();
SIM_DLLEXPORT int simAdjustRealTimeTimer_D(int instanceIndex, double deltaTime);

/* deprecated, double and single precision functions (compatibility): */
SIM_DLLEXPORT int simCreateMotionPlanning_D(int jointCnt, const int* jointHandles, const int* jointRangeSubdivisions,
                                            const double* jointMetricWeights, int options, const int* intParams,
                                            const double* floatParams, const void* reserved);
SIM_DLLEXPORT int simAddParticleObject_D(int objectType, double size, double density, const void* params,
                                         double lifeTime, int maxItemCount, const float* color, const float* setToNULL,
                                         const float* setToNULL2, const float* setToNULL3);
SIM_DLLEXPORT int simAddParticleObjectItem_D(int objectHandle, const double* itemData);
SIM_DLLEXPORT int simJointGetForce_D(int jointHandle, double* forceOrTorque);
SIM_DLLEXPORT int simGetMpConfigForTipPose_D(int motionPlanningObjectHandle, int options, double closeNodesDistance,
                                             int trialCount, const double* tipPose, int maxTimeInMs,
                                             double* outputJointPositions, const double* referenceConfigs,
                                             int referenceConfigCount, const double* jointWeights,
                                             const int* jointBehaviour, int correctionPasses);
SIM_DLLEXPORT double* simFindMpPath_D(int motionPlanningObjectHandle, const double* startConfig,
                                      const double* goalConfig, int options, double stepSize, int* outputConfigsCnt,
                                      int maxTimeInMs, double* reserved, const int* auxIntParams,
                                      const double* auxFloatParams);
SIM_DLLEXPORT double* simSimplifyMpPath_D(int motionPlanningObjectHandle, const double* pathBuffer, int configCnt,
                                          int options, double stepSize, int increment, int* outputConfigsCnt,
                                          int maxTimeInMs, double* reserved, const int* auxIntParams,
                                          const double* auxFloatParams);
SIM_DLLEXPORT double* simFindIkPath_D(int motionPlanningObjectHandle, const double* startConfig, const double* goalPose,
                                      int options, double stepSize, int* outputConfigsCnt, double* reserved,
                                      const int* auxIntParams, const double* auxFloatParams);
SIM_DLLEXPORT double* simGetMpConfigTransition_D(int motionPlanningObjectHandle, const double* startConfig,
                                                 const double* goalConfig, int options, const int* select,
                                                 double calcStepSize, double maxOutStepSize, int wayPointCnt,
                                                 const double* wayPoints, int* outputConfigsCnt,
                                                 const int* auxIntParams, const double* auxFloatParams);
SIM_DLLEXPORT int simSearchPath_D(int pathPlanningObjectHandle, double maximumSearchTime);
SIM_DLLEXPORT int simInitializePathSearch_D(int pathPlanningObjectHandle, double maximumSearchTime,
                                            double searchTimeStep);
SIM_DLLEXPORT int simHandlePath_D(int pathHandle, double deltaTime);
SIM_DLLEXPORT int simHandleJoint_D(int jointHandle, double deltaTime);
SIM_DLLEXPORT int simRegisterContactCallback_D(int (*callBack)(int, int, int, int*, double*));
SIM_DLLEXPORT int simRegisterJointCtrlCallback_D(int (*callBack)(int, int, int, const int*, const double*, double*));
SIM_DLLEXPORT int simSetJointForce_D(int objectHandle, double forceOrTorque);
SIM_DLLEXPORT int simHandleMill_D(int millHandle, double* removedSurfaceAndVolume);
SIM_DLLEXPORT int simSetShapeMassAndInertia_D(int shapeHandle, double mass, const double* inertiaMatrix,
                                              const double* centerOfMass, const double* transformation);
SIM_DLLEXPORT int simGetShapeMassAndInertia_D(int shapeHandle, double* mass, double* inertiaMatrix,
                                              double* centerOfMass, const double* transformation);
SIM_DLLEXPORT int simCheckIkGroup_D(int ikGroupHandle, int jointCnt, const int* jointHandles, double* jointValues,
                                    const int* jointOptions);
SIM_DLLEXPORT int simCreateIkGroup_D(int options, const int* intParams, const double* floatParams,
                                     const void* reserved);
SIM_DLLEXPORT int simCreateIkElement_D(int ikGroupHandle, int options, const int* intParams, const double* floatParams,
                                       const void* reserved);
SIM_DLLEXPORT int simGetConfigForTipPose_D(int ikGroupHandle, int jointCnt, const int* jointHandles,
                                           double thresholdDist, int maxTimeInMs, double* retConfig,
                                           const double* metric, int collisionPairCnt, const int* collisionPairs,
                                           const int* jointOptions, const double* lowLimits, const double* ranges,
                                           void* reserved);
SIM_DLLEXPORT double* simGenerateIkPath_D(int ikGroupHandle, int jointCnt, const int* jointHandles, int ptCnt,
                                          int collisionPairCnt, const int* collisionPairs, const int* jointOptions,
                                          void* reserved);
SIM_DLLEXPORT double* simGetIkGroupMatrix_D(int ikGroupHandle, int options, int* matrixSize);
SIM_DLLEXPORT int simSetIkGroupProperties_D(int ikGroupHandle, int resolutionMethod, int maxIterations, double damping,
                                            void* reserved);
SIM_DLLEXPORT int simSetIkElementProperties_D(int ikGroupHandle, int tipDummyHandle, int constraints,
                                              const double* precision, const double* weight, void* reserved);
SIM_DLLEXPORT int simSetVisionSensorFilter_D(int visionSensorHandle, int filterIndex, int options, const int* pSizes,
                                             const unsigned char* bytes, const int* ints, const double* floats,
                                             const unsigned char* custom);
SIM_DLLEXPORT int simGetVisionSensorFilter_D(int visionSensorHandle, int filterIndex, int* options, int* pSizes,
                                             unsigned char** bytes, int** ints, double** floats,
                                             unsigned char** custom);
SIM_DLLEXPORT int simGetPositionOnPath_D(int pathHandle, double relativeDistance, double* position);
SIM_DLLEXPORT int simGetDataOnPath_D(int pathHandle, double relativeDistance, int dataType, int* intData,
                                     double* floatData);
SIM_DLLEXPORT int simGetOrientationOnPath_D(int pathHandle, double relativeDistance, double* eulerAngles);
SIM_DLLEXPORT int simGetClosestPositionOnPath_D(int pathHandle, double* absolutePosition, double* pathPosition);
SIM_DLLEXPORT int simGetPathPosition_D(int objectHandle, double* position);
SIM_DLLEXPORT int simSetPathPosition_D(int objectHandle, double position);
SIM_DLLEXPORT int simGetPathLength_D(int objectHandle, double* length);
SIM_DLLEXPORT int simCreatePath_D(int attributes, const int* intParams, const double* floatParams, const float* color);
SIM_DLLEXPORT int simSetPathTargetNominalVelocity_D(int objectHandle, double targetNominalVelocity);
SIM_DLLEXPORT int simSendData_D(int targetID, int dataHeader, const char* dataName, const char* data, int dataLength,
                                int antennaHandle, double actionRadius, double emissionAngle1, double emissionAngle2,
                                double persistence);
SIM_DLLEXPORT int simHandleDistance_D(int distanceObjectHandle, double* smallestDistance);
SIM_DLLEXPORT int simReadDistance_D(int distanceObjectHandle, double* smallestDistance);
SIM_DLLEXPORT int simAddBanner_D(const char* label, double size, int options, const double* positionAndEulerAngles,
                                 int parentObjectHandle, const float* labelColors, const float* backgroundColors);
SIM_DLLEXPORT int simAddGhost_D(int ghostGroup, int objectHandle, int options, double startTime, double endTime,
                                const float* color);
SIM_DLLEXPORT int simModifyGhost_D(int ghostGroup, int ghostId, int operation, double floatValue, int options,
                                   int optionsMask, const double* colorOrTransformation);
SIM_DLLEXPORT int simSetGraphUserData_D(int graphHandle, const char* streamName, double data);
SIM_DLLEXPORT int simAddPointCloud_D(int pageMask, int layerMask, int objectHandle, int options, double pointSize,
                                     int ptCnt, const double* pointCoordinates, const char* defaultColors,
                                     const char* pointColors, const double* pointNormals);
SIM_DLLEXPORT int simModifyPointCloud_D(int pointCloudHandle, int operation, const int* intParam,
                                        const double* floatParam);
SIM_DLLEXPORT int simCopyMatrix_D(const double* matrixIn, double* matrixOut);
SIM_DLLEXPORT int simGetObjectFloatParameter_D(int objectHandle, int ParamID, double* Param);
SIM_DLLEXPORT int simSetObjectFloatParameter_D(int objectHandle, int ParamID, double Param);
SIM_DLLEXPORT int simSetFloatingParameter_D(int parameter, double floatState);
SIM_DLLEXPORT int simGetFloatingParameter_D(int parameter, double* floatState);
SIM_DLLEXPORT int simSetFloatParameter_D(int parameter, double floatState);
SIM_DLLEXPORT int simGetFloatParameter_D(int parameter, double* floatState);
SIM_DLLEXPORT int simSetArrayParameter_D(int parameter, const double* arrayOfValues);
SIM_DLLEXPORT int simGetArrayParameter_D(int parameter, double* arrayOfValues);
SIM_DLLEXPORT double simGetEngineFloatParameter_D(int paramId, int objectHandle, const void* object, bool* ok);
SIM_DLLEXPORT int simSetEngineFloatParameter_D(int paramId, int objectHandle, const void* object, double val);
SIM_DLLEXPORT int simSetObjectSizeValues_D(int objectHandle, const double* sizeValues);
SIM_DLLEXPORT int simGetObjectSizeValues_D(int objectHandle, double* sizeValues);
SIM_DLLEXPORT int simScaleSelectedObjects_D(double scalingFactor, bool scalePositionsToo);
SIM_DLLEXPORT int simGetJointMatrix_D(int objectHandle, double* matrix);
SIM_DLLEXPORT int simSetSphericalJointMatrix_D(int objectHandle, const double* matrix);
SIM_DLLEXPORT int simSetScriptAttribute_D(int scriptHandle, int attributeID, double floatVal, int intOrBoolVal);
SIM_DLLEXPORT int simGetScriptAttribute_D(int scriptHandle, int attributeID, double* floatVal, int* intOrBoolVal);
SIM_DLLEXPORT int simGetJointMaxForce_D(int jointHandle, double* forceOrTorque);
SIM_DLLEXPORT int simSetJointMaxForce_D(int objectHandle, double forceOrTorque);
SIM_DLLEXPORT int simCreatePureShape_D(int primitiveType, int options, const double* sizes, double mass,
                                       const int* precision);
SIM_DLLEXPORT int simBuildMatrixQ_D(const double* position, const double* quaternion, double* matrix);
SIM_DLLEXPORT int simGetQuaternionFromMatrix_D(const double* matrix, double* quaternion);
SIM_DLLEXPORT int simGetShapeVertex_D(int shapeHandle, int groupElementIndex, int vertexIndex,
                                      double* relativePosition);
SIM_DLLEXPORT int simGetShapeTriangle_D(int shapeHandle, int groupElementIndex, int triangleIndex, int* vertexIndices,
                                        double* triangleNormals);
SIM_DLLEXPORT void _simGetJointOdeParameters_D(const void* joint, double* stopERP, double* stopCFM, double* bounce,
                                               double* fudge, double* normalCFM);
SIM_DLLEXPORT void _simGetJointBulletParameters_D(const void* joint, double* stopERP, double* stopCFM,
                                                  double* normalCFM);
SIM_DLLEXPORT void _simGetOdeMaxContactFrictionCFMandERP_D(const void* geomInfo, int* maxContacts, double* friction,
                                                           double* cfm, double* erp);
SIM_DLLEXPORT bool _simGetBulletCollisionMargin_D(const void* geomInfo, double* margin, int* otherProp);
SIM_DLLEXPORT double _simGetBulletRestitution_D(const void* geomInfo);
SIM_DLLEXPORT void _simGetVortexParameters_D(const void* object, int version, double* floatParams, int* intParams);
SIM_DLLEXPORT void _simGetNewtonParameters_D(const void* object, int* version, double* floatParams, int* intParams);
SIM_DLLEXPORT void _simGetDamping_D(const void* geomInfo, double* linDamping, double* angDamping);
SIM_DLLEXPORT double _simGetFriction_D(const void* geomInfo);
SIM_DLLEXPORT void _simSetDynamicJointLocalTransformationPart2_D(void* joint, const double* pos, const double* quat);
SIM_DLLEXPORT void _simSetDynamicForceSensorLocalTransformationPart2_D(void* forceSensor, const double* pos,
                                                                       const double* quat);
SIM_DLLEXPORT void _simGetDynamicForceSensorLocalTransformationPart2_D(const void* forceSensor, double* pos,
                                                                       double* quat);
SIM_DLLEXPORT void _simGetMotorPid_D(const void* joint, double* pParam, double* iParam, double* dParam);
SIM_DLLEXPORT void _simGetPrincipalMomentOfInertia_D(const void* geomInfo, double* inertia);
SIM_DLLEXPORT void _simGetLocalInertiaFrame_D(const void* geomInfo, double* pos, double* quat);
SIM_DLLEXPORT int simExtLaunchUIThread(const char* applicationName, int options, const char* sceneOrModelOrUiToLoad,
                                       const char* applicationDir_);
SIM_DLLEXPORT int simExtCanInitSimThread();
SIM_DLLEXPORT int simExtSimThreadInit();
SIM_DLLEXPORT int simExtSimThreadDestroy();
SIM_DLLEXPORT int simExtPostExitRequest();
SIM_DLLEXPORT int simExtGetExitRequest();
SIM_DLLEXPORT int simExtStep(bool stepIfRunning);
SIM_DLLEXPORT int simExtCallScriptFunction_D(int scriptHandleOrType, const char* functionNameAtScriptName,
                                             const int* inIntData, int inIntCnt, const double* inFloatData,
                                             int inFloatCnt, const char** inStringData, int inStringCnt,
                                             const char* inBufferData, int inBufferCnt, int** outIntData,
                                             int* outIntCnt, double** outFloatData, int* outFloatCnt,
                                             char*** outStringData, int* outStringCnt, char** outBufferData,
                                             int* outBufferSize);
SIM_DLLEXPORT int simCreateMotionPlanning(int jointCnt, const int* jointHandles, const int* jointRangeSubdivisions,
                                          const float* jointMetricWeights, int options, const int* intParams,
                                          const float* floatParams, const void* reserved);
SIM_DLLEXPORT int simAddParticleObject(int objectType, float size, float density, const void* params, float lifeTime,
                                       int maxItemCount, const float* color, const float* setToNULL,
                                       const float* setToNULL2, const float* setToNULL3);
SIM_DLLEXPORT int simAddParticleObjectItem(int objectHandle, const float* itemData);
SIM_DLLEXPORT int simJointGetForce(int jointHandle, float* forceOrTorque);
SIM_DLLEXPORT int simGetMpConfigForTipPose(int motionPlanningObjectHandle, int options, float closeNodesDistance,
                                           int trialCount, const float* tipPose, int maxTimeInMs,
                                           float* outputJointPositions, const float* referenceConfigs,
                                           int referenceConfigCount, const float* jointWeights,
                                           const int* jointBehaviour, int correctionPasses);
SIM_DLLEXPORT float* simFindMpPath(int motionPlanningObjectHandle, const float* startConfig, const float* goalConfig,
                                   int options, float stepSize, int* outputConfigsCnt, int maxTimeInMs, float* reserved,
                                   const int* auxIntParams, const float* auxFloatParams);
SIM_DLLEXPORT float* simSimplifyMpPath(int motionPlanningObjectHandle, const float* pathBuffer, int configCnt,
                                       int options, float stepSize, int increment, int* outputConfigsCnt,
                                       int maxTimeInMs, float* reserved, const int* auxIntParams,
                                       const float* auxFloatParams);
SIM_DLLEXPORT float* simFindIkPath(int motionPlanningObjectHandle, const float* startConfig, const float* goalPose,
                                   int options, float stepSize, int* outputConfigsCnt, float* reserved,
                                   const int* auxIntParams, const float* auxFloatParams);
SIM_DLLEXPORT float* simGetMpConfigTransition(int motionPlanningObjectHandle, const float* startConfig,
                                              const float* goalConfig, int options, const int* select,
                                              float calcStepSize, float maxOutStepSize, int wayPointCnt,
                                              const float* wayPoints, int* outputConfigsCnt, const int* auxIntParams,
                                              const float* auxFloatParams);
SIM_DLLEXPORT int simSearchPath(int pathPlanningObjectHandle, float maximumSearchTime);
SIM_DLLEXPORT int simInitializePathSearch(int pathPlanningObjectHandle, float maximumSearchTime, float searchTimeStep);
SIM_DLLEXPORT int simHandlePath(int pathHandle, float deltaTime);
SIM_DLLEXPORT int simHandleJoint(int jointHandle, float deltaTime);
SIM_DLLEXPORT int simSetUIButtonColor(int uiHandle, int buttonHandle, const float* upStateColor,
                                      const float* downStateColor, const float* labelColor);
SIM_DLLEXPORT int simSetUIButtonArrayColor(int uiHandle, int buttonHandle, const int* position, const float* color);
SIM_DLLEXPORT int simRegisterContactCallback(int (*callBack)(int, int, int, int*, float*));
SIM_DLLEXPORT int simRegisterJointCtrlCallback(int (*callBack)(int, int, int, const int*, const float*, float*));
SIM_DLLEXPORT int simSetJointForce(int objectHandle, float forceOrTorque);
SIM_DLLEXPORT int simHandleMill(int millHandle, float* removedSurfaceAndVolume);
SIM_DLLEXPORT int simSetShapeMassAndInertia(int shapeHandle, float mass, const float* inertiaMatrix,
                                            const float* centerOfMass, const float* transformation);
SIM_DLLEXPORT int simGetShapeMassAndInertia(int shapeHandle, float* mass, float* inertiaMatrix, float* centerOfMass,
                                            const float* transformation);
SIM_DLLEXPORT int simCheckIkGroup(int ikGroupHandle, int jointCnt, const int* jointHandles, float* jointValues,
                                  const int* jointOptions);
SIM_DLLEXPORT int simCreateIkGroup(int options, const int* intParams, const float* floatParams, const void* reserved);
SIM_DLLEXPORT int simCreateIkElement(int ikGroupHandle, int options, const int* intParams, const float* floatParams,
                                     const void* reserved);
SIM_DLLEXPORT int simGetConfigForTipPose(int ikGroupHandle, int jointCnt, const int* jointHandles, float thresholdDist,
                                         int maxTimeInMs, float* retConfig, const float* metric, int collisionPairCnt,
                                         const int* collisionPairs, const int* jointOptions, const float* lowLimits,
                                         const float* ranges, void* reserved);
SIM_DLLEXPORT float* simGenerateIkPath(int ikGroupHandle, int jointCnt, const int* jointHandles, int ptCnt,
                                       int collisionPairCnt, const int* collisionPairs, const int* jointOptions,
                                       void* reserved);
SIM_DLLEXPORT float* simGetIkGroupMatrix(int ikGroupHandle, int options, int* matrixSize);
SIM_DLLEXPORT int simSetIkGroupProperties(int ikGroupHandle, int resolutionMethod, int maxIterations, float damping,
                                          void* reserved);
SIM_DLLEXPORT int simSetIkElementProperties(int ikGroupHandle, int tipDummyHandle, int constraints,
                                            const float* precision, const float* weight, void* reserved);
SIM_DLLEXPORT int simSetVisionSensorFilter(int visionSensorHandle, int filterIndex, int options, const int* pSizes,
                                           const unsigned char* bytes, const int* ints, const float* floats,
                                           const unsigned char* custom);
SIM_DLLEXPORT int simGetVisionSensorFilter(int visionSensorHandle, int filterIndex, int* options, int* pSizes,
                                           unsigned char** bytes, int** ints, float** floats, unsigned char** custom);
SIM_DLLEXPORT int simGetPositionOnPath(int pathHandle, float relativeDistance, float* position);
SIM_DLLEXPORT int simGetDataOnPath(int pathHandle, float relativeDistance, int dataType, int* intData,
                                   float* floatData);
SIM_DLLEXPORT int simGetOrientationOnPath(int pathHandle, float relativeDistance, float* eulerAngles);
SIM_DLLEXPORT int simGetClosestPositionOnPath(int pathHandle, float* absolutePosition, float* pathPosition);
SIM_DLLEXPORT int simGetPathPosition(int objectHandle, float* position);
SIM_DLLEXPORT int simSetPathPosition(int objectHandle, float position);
SIM_DLLEXPORT int simGetPathLength(int objectHandle, float* length);
SIM_DLLEXPORT int simCreatePath(int attributes, const int* intParams, const float* floatParams, const float* color);
SIM_DLLEXPORT int simSetPathTargetNominalVelocity(int objectHandle, float targetNominalVelocity);
SIM_DLLEXPORT int simSendData(int targetID, int dataHeader, const char* dataName, const char* data, int dataLength,
                              int antennaHandle, float actionRadius, float emissionAngle1, float emissionAngle2,
                              float persistence);
SIM_DLLEXPORT int simHandleDistance(int distanceObjectHandle, float* smallestDistance);
SIM_DLLEXPORT int simReadDistance(int distanceObjectHandle, float* smallestDistance);
SIM_DLLEXPORT int simAddBanner(const char* label, float size, int options, const float* positionAndEulerAngles,
                               int parentObjectHandle, const float* labelColors, const float* backgroundColors);
SIM_DLLEXPORT int simAddGhost(int ghostGroup, int objectHandle, int options, float startTime, float endTime,
                              const float* color);
SIM_DLLEXPORT int simModifyGhost(int ghostGroup, int ghostId, int operation, float floatValue, int options,
                                 int optionsMask, const float* colorOrTransformation);
SIM_DLLEXPORT int simSetGraphUserData(int graphHandle, const char* streamName, float data);
SIM_DLLEXPORT int simAddPointCloud(int pageMask, int layerMask, int objectHandle, int options, float pointSize,
                                   int ptCnt, const float* pointCoordinates, const char* defaultColors,
                                   const char* pointColors, const float* pointNormals);
SIM_DLLEXPORT int simModifyPointCloud(int pointCloudHandle, int operation, const int* intParam,
                                      const float* floatParam);
SIM_DLLEXPORT int simCopyMatrix(const float* matrixIn, float* matrixOut);
SIM_DLLEXPORT int simGetObjectFloatParameter(int objectHandle, int ParamID, float* Param);
SIM_DLLEXPORT int simSetObjectFloatParameter(int objectHandle, int ParamID, float Param);
SIM_DLLEXPORT int simSetFloatingParameter(int parameter, float floatState);
SIM_DLLEXPORT int simGetFloatingParameter(int parameter, float* floatState);
SIM_DLLEXPORT int simSetFloatParameter(int parameter, float floatState);
SIM_DLLEXPORT int simGetFloatParameter(int parameter, float* floatState);
SIM_DLLEXPORT int simSetArrayParameter(int parameter, const float* arrayOfValues);
SIM_DLLEXPORT int simGetArrayParameter(int parameter, float* arrayOfValues);
SIM_DLLEXPORT float simGetEngineFloatParameter(int paramId, int objectHandle, const void* object, bool* ok);
SIM_DLLEXPORT int simSetEngineFloatParameter(int paramId, int objectHandle, const void* object, float val);
SIM_DLLEXPORT int simSetObjectSizeValues(int objectHandle, const float* sizeValues);
SIM_DLLEXPORT int simGetObjectSizeValues(int objectHandle, float* sizeValues);
SIM_DLLEXPORT int simDisplayDialog(const char* titleText, const char* mainText, int dialogType, const char* initialText,
                                   const float* titleColors, const float* dialogColors, int* elementHandle);
SIM_DLLEXPORT int simScaleSelectedObjects(float scalingFactor, bool scalePositionsToo);
SIM_DLLEXPORT int simGetJointMatrix(int objectHandle, float* matrix);
SIM_DLLEXPORT int simSetSphericalJointMatrix(int objectHandle, const float* matrix);
SIM_DLLEXPORT int simSetScriptAttribute(int scriptHandle, int attributeID, float floatVal, int intOrBoolVal);
SIM_DLLEXPORT int simGetScriptAttribute(int scriptHandle, int attributeID, float* floatVal, int* intOrBoolVal);
SIM_DLLEXPORT int simGetJointMaxForce(int jointHandle, float* forceOrTorque);
SIM_DLLEXPORT int simSetJointMaxForce(int objectHandle, float forceOrTorque);
SIM_DLLEXPORT float* simGetVisionSensorImage(int visionSensorHandle);
SIM_DLLEXPORT int simSetVisionSensorImage(int visionSensorHandle, const float* image);
SIM_DLLEXPORT int simSetVisionSensorDepthBuffer(int visionSensorHandle, const float* depthBuffer);
SIM_DLLEXPORT int simCreatePureShape(int primitiveType, int options, const float* sizes, float mass,
                                     const int* precision);
SIM_DLLEXPORT int simBuildMatrixQ(const float* position, const float* quaternion, float* matrix);
SIM_DLLEXPORT int simGetQuaternionFromMatrix(const float* matrix, float* quaternion);
SIM_DLLEXPORT int simGetShapeVertex(int shapeHandle, int groupElementIndex, int vertexIndex, float* relativePosition);
SIM_DLLEXPORT int simGetShapeTriangle(int shapeHandle, int groupElementIndex, int triangleIndex, int* vertexIndices,
                                      float* triangleNormals);
SIM_DLLEXPORT void _simGetJointOdeParameters(const void* joint, float* stopERP, float* stopCFM, float* bounce,
                                             float* fudge, float* normalCFM);
SIM_DLLEXPORT void _simGetJointBulletParameters(const void* joint, float* stopERP, float* stopCFM, float* normalCFM);
SIM_DLLEXPORT void _simGetOdeMaxContactFrictionCFMandERP(const void* geomInfo, int* maxContacts, float* friction,
                                                         float* cfm, float* erp);
SIM_DLLEXPORT bool _simGetBulletCollisionMargin(const void* geomInfo, float* margin, int* otherProp);
SIM_DLLEXPORT float _simGetBulletRestitution(const void* geomInfo);
SIM_DLLEXPORT void _simGetVortexParameters(const void* object, int version, float* floatParams, int* intParams);
SIM_DLLEXPORT void _simGetNewtonParameters(const void* object, int* version, float* floatParams, int* intParams);
SIM_DLLEXPORT void _simGetDamping(const void* geomInfo, float* linDamping, float* angDamping);
SIM_DLLEXPORT float _simGetFriction(const void* geomInfo);
SIM_DLLEXPORT void _simSetDynamicJointLocalTransformationPart2(void* joint, const float* pos, const float* quat);
SIM_DLLEXPORT void _simSetDynamicForceSensorLocalTransformationPart2(void* forceSensor, const float* pos,
                                                                     const float* quat);
SIM_DLLEXPORT void _simGetDynamicForceSensorLocalTransformationPart2(const void* forceSensor, float* pos, float* quat);
SIM_DLLEXPORT void _simGetMotorPid(const void* joint, float* pParam, float* iParam, float* dParam);
SIM_DLLEXPORT void _simGetPrincipalMomentOfInertia(const void* geomInfo, float* inertia);
SIM_DLLEXPORT void _simGetLocalInertiaFrame(const void* geomInfo, float* pos, float* quat);
SIM_DLLEXPORT const void* _simGetGeomProxyFromShape(const void* shape);
SIM_DLLEXPORT int simIsDeprecated(const char* funcOrConst);
SIM_DLLEXPORT int simLoadModule(const char* filenameAndPath, const char* pluginName);
SIM_DLLEXPORT int simUnloadModule(int pluginhandle);
SIM_DLLEXPORT char* simGetModuleName(int index, unsigned char* setToNull);
SIM_DLLEXPORT int simSetModuleInfo(const char* moduleName, int infoType, const char* stringInfo, int intInfo);
SIM_DLLEXPORT int simGetModuleInfo(const char* moduleName, int infoType, char** stringInfo, int* intInfo);
SIM_DLLEXPORT int simIsStackValueNull(int stackHandle);
SIM_DLLEXPORT int simPersistentDataWrite(const char* dataName, const char* dataValue, int dataLength, int options);
SIM_DLLEXPORT char* simPersistentDataRead(const char* dataName, int* dataLength);
SIM_DLLEXPORT char* simGetPersistentDataTags(int* tagCount);

SIM_DLLEXPORT int simSetBoolParam(int parameter, bool boolState);
SIM_DLLEXPORT int simGetBoolParam(int parameter);
SIM_DLLEXPORT int simSetInt32Param(int parameter, int intState);
SIM_DLLEXPORT int simGetInt32Param(int parameter, int* intState);
SIM_DLLEXPORT int simGetUInt64Param(int parameter, unsigned long long int* intState);
SIM_DLLEXPORT int simSetStringParam(int parameter, const char* str);
SIM_DLLEXPORT char* simGetStringParam(int parameter);
SIM_DLLEXPORT int simSetNamedStringParam(const char* paramName, const char* stringParam, int paramLength);
SIM_DLLEXPORT char* simGetNamedStringParam(const char* paramName, int* paramLength);
SIM_DLLEXPORT int simSetInt32Signal(const char* signalName, int signalValue);
SIM_DLLEXPORT int simGetInt32Signal(const char* signalName, int* signalValue);
SIM_DLLEXPORT int simClearInt32Signal(const char* signalName);
SIM_DLLEXPORT int simClearFloatSignal(const char* signalName);
SIM_DLLEXPORT int simSetStringSignal(const char* signalName, const char* signalValue, int stringLength);
SIM_DLLEXPORT char* simGetStringSignal(const char* signalName, int* stringLength);
SIM_DLLEXPORT int simClearStringSignal(const char* signalName);
SIM_DLLEXPORT char* simGetSignalName(int signalIndex, int signalType);
SIM_DLLEXPORT int simGetObjectInt32Param(int objectHandle, int ParamID, int* Param);
SIM_DLLEXPORT int simSetObjectInt32Param(int objectHandle, int ParamID, int Param);
SIM_DLLEXPORT char* simGetObjectStringParam(int objectHandle, int ParamID, int* ParamLength);
SIM_DLLEXPORT int simSetObjectStringParam(int objectHandle, int ParamID, const char* Param, int ParamLength);
SIM_DLLEXPORT int simGetScriptInt32Param(int ScriptHandle, int ParamID, int* Param);
SIM_DLLEXPORT int simSetScriptInt32Param(int ScriptHandle, int ParamID, int Param);
SIM_DLLEXPORT char* simGetScriptStringParam(int ScriptHandle, int ParamID, int* ParamLength);
SIM_DLLEXPORT int simSetScriptStringParam(int ScriptHandle, int ParamID, const char* Param, int ParamLength);
SIM_DLLEXPORT int simWriteCustomDataBlock(int objectHandle, const char* tagName, const char* data, int dataSize);
SIM_DLLEXPORT char* simReadCustomDataBlock(int objectHandle, const char* tagName, int* dataSize);
SIM_DLLEXPORT char* simReadCustomDataBlockTags(int objectHandle, int* tagCount);
SIM_DLLEXPORT int simGetEngineInt32Param(int paramId, int objectHandle, const void* object, bool* ok);
SIM_DLLEXPORT bool simGetEngineBoolParam(int paramId, int objectHandle, const void* object, bool* ok);
SIM_DLLEXPORT int simSetEngineInt32Param(int paramId, int objectHandle, const void* object, int val);
SIM_DLLEXPORT int simSetEngineBoolParam(int paramId, int objectHandle, const void* object, bool val);
SIM_DLLEXPORT int simSetArrayParam_D(int parameter, const double* arrayOfValues);
SIM_DLLEXPORT int simGetArrayParam_D(int parameter, double* arrayOfValues);
SIM_DLLEXPORT int simSetFloatParam_D(int parameter, double floatState);
SIM_DLLEXPORT int simGetFloatParam_D(int parameter, double* floatState);
SIM_DLLEXPORT int simSetFloatSignal_D(const char* signalName, double signalValue);
SIM_DLLEXPORT int simGetFloatSignal_D(const char* signalName, double* signalValue);
SIM_DLLEXPORT int simSetLightParameters(int objectHandle, int state, const float* setToNULL, const float* diffusePart,
                                        const float* specularPart);
SIM_DLLEXPORT int simGetLightParameters_D(int objectHandle, double* setToNULL, double* diffusePart,
                                          double* specularPart);
SIM_DLLEXPORT int simGetObjectFloatParam_D(int objectHandle, int ParamID, double* Param);
SIM_DLLEXPORT int simSetObjectFloatParam_D(int objectHandle, int ParamID, double Param);
SIM_DLLEXPORT double* simGetObjectFloatArrayParam_D(int objectHandle, int parameterID, int* size);
SIM_DLLEXPORT int simSetObjectFloatArrayParam_D(int objectHandle, int parameterID, const double* params, int size);
SIM_DLLEXPORT double simGetEngineFloatParam_D(int paramId, int objectHandle, const void* object, bool* ok);
SIM_DLLEXPORT int simSetEngineFloatParam_D(int paramId, int objectHandle, const void* object, double val);
SIM_DLLEXPORT int simSetModelProperty(int objectHandle, int modelProperty);
SIM_DLLEXPORT int simGetModelProperty(int objectHandle);
SIM_DLLEXPORT int simSetObjectProperty(int objectHandle, int prop);
SIM_DLLEXPORT int simGetObjectProperty(int objectHandle);
SIM_DLLEXPORT int simSetObjectSpecialProperty(int objectHandle, int prop);
SIM_DLLEXPORT int simGetObjectSpecialProperty(int objectHandle);
SIM_DLLEXPORT char* simGetStringProperty(long long int target, const char* pName);
SIM_DLLEXPORT char* simGetTableProperty(long long int target, const char* pName, int* bufferL);
SIM_DLLEXPORT char* simGetBufferProperty(long long int target, const char* pName, int* bufferL);
SIM_DLLEXPORT double* simGetFloatArrayProperty(long long int target, const char* pName, int* vL);
SIM_DLLEXPORT int* simGetIntArrayProperty(long long int target, const char* pName, int* vL);
