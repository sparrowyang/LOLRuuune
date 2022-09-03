#include "gui/mainwnd.h"
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Mainwnd windows;
    windows.show();
    return app.exec();
}
