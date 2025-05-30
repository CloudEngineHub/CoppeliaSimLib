#include <simQApp.h>
#ifdef SIM_WITH_GUI
#include <guiApp.h>
#endif

CSimQApp::CSimQApp(int& argc, char** argv)
    : QAPP(argc, argv)
{
#ifdef Q_OS_MAC
    QuitKeyInterceptor::install();
#endif
}

CSimQApp::~CSimQApp()
{
}

bool CSimQApp::notify(QObject* object, QEvent* event)
{
#ifdef SIM_WITH_GUI
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        int key = keyEvent->key();
        if (key == Qt::Key_Escape)
            GuiApp::setFullScreen(false);
    }
#endif
    return (QAPP::notify(object, event));
};
