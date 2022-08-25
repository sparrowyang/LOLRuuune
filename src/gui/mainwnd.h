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
class DrapBtn : public QPushButton {
public:
    DrapBtn() {};
    ~DrapBtn() {};
    QPoint m_CurrentPos;
    QMainWindow* m;
    void mousePressEvent(QMouseEvent* event) {
        //按住左键可以托动窗口
        if (event->button() == Qt::LeftButton) {
            m_CurrentPos = event->globalPos() - m->frameGeometry().topLeft();
            event->accept();
        }
    }

    void mouseMoveEvent(QMouseEvent* event) {
        if (event->buttons() && Qt::LeftButton) {
            m->move(event->globalPos() - m_CurrentPos);
            event->accept();
        }
    }
    void SetMain(QMainWindow* _m) { m = _m; }
};

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
    QIcon i_add;
    QIcon i_del;
    QIcon i_hide;
    QIcon i_exit;
    QIcon i_move;
    QIcon i_done;
    QSize m_size;
    QSystemTrayIcon m_trayIcon;
    QWidget m_mainWidget;
    QVBoxLayout m_hLayout;
    QHBoxLayout m_headerLayout;
    QHBoxLayout m_vLayoutTitle;
    QComboBox m_comboBox;

    QPushButton m_hidBtn;
    QPushButton m_newBtn;
    QPushButton m_delBtn;
    QPushButton m_setBtn;
    // QPushButton m_saveBtn;
    QPushButton m_exitBtn;
    QStatusBar m_statusBar;
    DrapBtn m_drapBtn;
    QAction m_quit;

    QButtonGroup m_btnGruop1;
    QLabel m_label;
    Lcu m_lcu;
    QPoint m_CurrentPos;
};
