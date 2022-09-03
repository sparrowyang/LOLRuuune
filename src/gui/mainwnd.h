#pragma once
#include <qprocess.h>
#include <QString>
#include <QStringList>
#include <QtWidgets>
#include <list>
#include "../lcu/lcu.h"
class DrapBtn: public QPushButton {
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
    void SetMain(QMainWindow* _m) {
        m = _m;
    }
};
class Mainwnd: public QMainWindow,
               public std::enable_shared_from_this<Mainwnd> {
public:
    Mainwnd(/* args */);
    ~Mainwnd();
    QString LoadQss();
    std::string GetToken();

protected:
    void ConnectSignals();
private slots:
    void OnClick();

private:
    void UpdatePreview(std::vector<std::string> perks);

private:
    QIcon m_icon, i_add, i_del, i_hide, i_exit, i_move, i_done;
    QLabel m1, m2, m3, m4, s1, s2, s3, a1, a2, a3;
    QSize m_size;
    QSystemTrayIcon m_trayIcon;
    QWidget m_mainWidget;
    QVBoxLayout m_hLayout;
    QHBoxLayout m_headerLayout, m_vLayoutTitle;
    QComboBox m_comboBox;
    QPushButton m_hidBtn, m_newBtn, m_delBtn, m_setBtn, m_conBtn, m_exitBtn;
    QStatusBar m_statusBar;
    DrapBtn m_drapBtn;
    QAction m_quit;
    QButtonGroup m_btnGruop1;
    QLabel m_label;
    Lcu m_lcu;
    QPoint m_CurrentPos;
    QGroupBox m_preview;
    QGridLayout pre_layout;
};
