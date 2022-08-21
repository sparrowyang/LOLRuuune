#include <QString>
#include <QtWidgets>
#include "gui/mainwnd.h"

#define CPPHTTPLIB_OPENSSL_SUPPORT

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	Mainwnd windows;
	windows.show();
	/* 设置全局字体以及尺寸 */
	QFont font;
	font.setFamily("Consolas");
	font.setPixelSize(16);
	app.setFont(font);
	/* 设置对话框尺寸 */
	// QDialog dialog;
	// dialog.resize(400, 300);
	/* 设置标签文本与位置 */
	return app.exec();
}
