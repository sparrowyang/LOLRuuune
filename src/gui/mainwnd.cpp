#include "mainwnd.h"
Mainwnd::Mainwnd(/* args */) {
    qDebug() << "Windows Init...";
    m_icon.addFile(":/img/static/ouc.png");
    i_del.addFile(":/img/static/delete.png");
    i_hide.addFile(":/img/static/hide.png");
    i_exit.addFile(":/img/static/power.png");
    i_move.addFile(":/img/static/move.png");
    i_done.addFile(":/img/static/done.png");
    i_add.addFile(":/img/static/add.png");
    setWindowIcon(m_icon);
    setStyleSheet(LoadQss());
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool | Qt::FramelessWindowHint);
    m_label.setText("LolRuuuner");
    QFont font;
    font.setFamily("Consolas");
    font.setPixelSize(48);
    m_label.setFont(font);
    m_newBtn.setIcon(i_add);
    m_delBtn.setIcon(i_del);
    m_exitBtn.setIcon(i_exit);
    m_hidBtn.setIcon(i_hide);
    m_conBtn.setText("C");
    m_setBtn.setIcon(i_done);
    m_setBtn.setText("Save");
    m_setBtn.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_drapBtn.setIcon(i_move);
    m_drapBtn.SetMain(this);
    pre_layout.addWidget(&m1, 0, 0);
    pre_layout.addWidget(&m2, 1, 0);
    pre_layout.addWidget(&m3, 2, 0);
    pre_layout.addWidget(&m4, 3, 0);
    pre_layout.addWidget(&s1, 0, 1);
    pre_layout.addWidget(&s2, 1, 1);
    // pre_layout.addWidget(&s3, 2, 1);
    pre_layout.addWidget(&a1, 2, 1);
    pre_layout.addWidget(&a2, 3, 1);
    pre_layout.addWidget(&a3, 4, 1);
    m_preview.setLayout(&pre_layout);
    m_vLayoutTitle.addWidget(&m_comboBox, 3);
    m_vLayoutTitle.addWidget(&m_newBtn);
    m_vLayoutTitle.addWidget(&m_delBtn);
    m_headerLayout.addWidget(&m_drapBtn, 5);
    m_headerLayout.addWidget(&m_conBtn);
    m_headerLayout.addWidget(&m_hidBtn);
    m_headerLayout.addWidget(&m_exitBtn, 1);
    m_hLayout.addLayout(&m_headerLayout);
    m_hLayout.addWidget(&m_label);
    m_hLayout.addLayout(&m_vLayoutTitle);
    m_hLayout.addWidget(&m_preview);
    m_hLayout.addWidget(&m_setBtn, 3);
    m_hLayout.addWidget(&m_statusBar);
    m_mainWidget.setLayout(&m_hLayout);
    setCentralWidget(&m_mainWidget);
    m_trayIcon.setIcon(m_icon);
    m_trayIcon.setToolTip(tr("Ruunner"));
    QMenu* menu = new QMenu(this);
    m_quit.setText("exit");
    menu->addAction(&m_quit);
    m_trayIcon.setContextMenu(menu);
    m_trayIcon.show();
    m_lcu.LoadFile();
    auto pages = m_lcu.GetSavePages();
    m_comboBox.clear();
    for (auto& i: pages) {
        m_comboBox.addItem(QString::fromUtf8(i.GetName().c_str()));
    }
    ConnectSignals();
    m_lcu.SetToken(GetToken());
}
Mainwnd::~Mainwnd() {
}
void Mainwnd::ConnectSignals() {
    connect(&m_comboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [&](int index) {
        UpdatePreview(m_lcu.GetPageMsg(index));
    });
    connect(&m_delBtn, &QPushButton::clicked, this, [&] {
        int id = m_comboBox.currentIndex();
        m_lcu.DelSavePage(id);
        auto pages = m_lcu.GetSavePages();
        m_comboBox.clear();
        for (auto& i: pages) {
            m_comboBox.addItem(QString::fromStdString(i.GetName()));
        }
        m_lcu.SaveToFile();
    });
    connect(&m_setBtn, &QPushButton::clicked, this, [&] {
        int id = m_comboBox.currentIndex();
        m_lcu.setRune(id);
    });
    connect(&m_newBtn, &QPushButton::clicked, this, [=] {
        m_lcu.saveRunnePage();
        auto pages = m_lcu.GetSavePages();
        m_comboBox.clear();
        for (auto& i: pages) {
            m_comboBox.addItem(QString::fromStdString(i.GetName()));
        }
        m_lcu.SaveToFile();
    });
    connect(&m_exitBtn, &QPushButton::clicked, this, [=]() {
        QApplication* app;
        app->exit(0);
    });
    connect(&m_trayIcon, &QSystemTrayIcon::activated, this, [=]() {
        if (isHidden()) {
            resize(m_size);
            show();
        }
        else {
            m_size = size();
            close();
        }
    });
    connect(&m_hidBtn, &QPushButton::clicked, this, [=]() {
        if (isHidden()) {
            resize(m_size);
            show();
        }
        else {
            m_size = size();
            close();
        }
    });
    connect(&m_quit, &QAction::triggered, this, []() {
        QApplication* app;
        app->exit(0);
    });
}
QString Mainwnd::LoadQss() {
    QFile qss(":/qss/static/ubuntu.qss");
    if (qss.open(QFile::ReadOnly)) {
        qDebug("Qss open success");
        QString style = QLatin1String(qss.readAll());
        qss.close();
        return style;
    }
    else {
        qDebug("Qt StyleSheet Open failed");
    }
    return QString();
}
std::string Mainwnd::GetToken() {
    //"wmic process where \"name='LeagueClientUx.exe'\" get commandline"
    QProcess p;
    // p.setProgram("wmic");
    QStringList args;
    args << "process"
         << "where"
         << "name='LeagueClientUx.exe'"
         << "get"
         << "commandline";
    // p.setArguments(args);
    p.start("WMIC.exe", args);
    p.waitForStarted();
    p.waitForReadyRead();
    p.waitForFinished();
    std::string s = std::string(p.readAllStandardOutput().data());
    return s;
}
void Mainwnd::UpdatePreview(std::vector<std::string> perks) {
    if (perks.size() != 9) {
        return;
    }
    m1.setText(QString::fromUtf8(perks[0].c_str()));
    m2.setText(QString::fromUtf8(perks[1].c_str()));
    m3.setText(QString::fromUtf8(perks[2].c_str()));
    m4.setText(QString::fromUtf8(perks[3].c_str()));
    s1.setText(QString::fromUtf8(perks[4].c_str()));
    s2.setText(QString::fromUtf8(perks[5].c_str()));
    a1.setText(QString::fromUtf8(perks[6].c_str()));
    a2.setText(QString::fromUtf8(perks[7].c_str()));
    a3.setText(QString::fromUtf8(perks[8].c_str()));
}
void Mainwnd::OnClick() {
}
