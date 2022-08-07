#pragma once
#include "../lcu/lcu.h"

#include <QtWidgets>
#include <QString>
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
class Mainwnd : public QMainWindow, public std::enable_shared_from_this<Mainwnd>
{
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
    QSystemTrayIcon m_trayIcon;
    QWidget m_mainWidget;
    QLineEdit m_lindEdit;
    QVBoxLayout m_hLayout;
    QPushButton m_btn;
    QRadioButton m_radio;
    QLabel m_label;
    Lcu m_lcu;
};
