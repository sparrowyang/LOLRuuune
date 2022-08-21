#pragma once
#include "../lcu/lcu.h"

#include <QString>
#include <QtWidgets>
/*
[______________v] [O][_/][+][X]
[_____v]  ||   [_____v]             //主系副系不重复
-------------------
[x x x]        [x x x]              //不一定是三个，可变长度
[x x x]        [x x x]
[x x x]        [x x x]
[x x x]
--------------------
[x x x]
[x x x]
[x x x]
[Apply]
*/
class Mainwnd : public QMainWindow,
	public std::enable_shared_from_this<Mainwnd> {
private:
	/* data */
public:
	Mainwnd(/* args */);
	~Mainwnd();
	QString LoadQss();

protected:
	void ConnectSignals();

private slots:
	void OnClick();

private:
	QIcon m_icon;
	QSystemTrayIcon m_trayIcon;
	QWidget m_mainWidget;
	QLineEdit m_lindEdit;
	QVBoxLayout m_hLayout;
	QHBoxLayout m_vLayoutTitle;
	QComboBox m_comboBox;

	QPushButton m_newBtn;
	QPushButton m_delBtn;
	QPushButton m_setBtn;
	QPushButton m_saveBtn;
	QPushButton m_exitBtn;

	QAction m_quit;

	QRadioButton m_radio11;
	QRadioButton m_radio12;
	QRadioButton m_radio13;
	QRadioButton m_radio21;
	QButtonGroup m_btnGruop1;
	QLabel m_label;
	Lcu m_lcu;
};
