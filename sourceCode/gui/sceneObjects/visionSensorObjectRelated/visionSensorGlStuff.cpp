#include <app.h>
#include <visionSensorGlStuff.h>

#ifdef USES_QGLWIDGET
CVisionSensorGlStuff::CVisionSensorGlStuff(int resX, int resY, int offscreenType, bool qtFbo,
                                           QGLWidget* otherWidgetToShareResourcesWith, bool useStencilBuffer,
                                           bool destroyOffscreenContext)
    : QObject()
#else
CVisionSensorGlStuff::CVisionSensorGlStuff(int resX, int resY, int offscreenType, bool qtFbo,
                                           QOpenGLWidget* otherWidgetToShareResourcesWith, bool useStencilBuffer,
                                           bool destroyOffscreenContext)
    : QObject()
#endif
{
    _destroyOffscreenContext = destroyOffscreenContext;

    // 1. We need an offscreen context:
    offscreenContext = new COffscreenGlContext(offscreenType, resX, resY, otherWidgetToShareResourcesWith);

    // 2. We need an FBO:
    frameBufferObject = new CFrameBufferObject(!qtFbo, resX, resY, useStencilBuffer);

    // 3. We need a texture object:
    textureObject = new CTextureObject(resX, resY);

    offscreenContext->doneCurrent();
}

CVisionSensorGlStuff::~CVisionSensorGlStuff()
{
    TRACE_INTERNAL;
    offscreenContext->makeCurrent();
    delete textureObject;
    delete frameBufferObject;
    offscreenContext->doneCurrent();

    // On some buggy GPU drivers, destroying the context here might hinder further renderings in other contexts:
    if (_destroyOffscreenContext)
        delete offscreenContext;
}
