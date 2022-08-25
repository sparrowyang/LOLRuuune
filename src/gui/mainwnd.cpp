#include "mainwnd.h"
Mainwnd::Mainwnd(/* args */) {
    qDebug() << "Windows Init...";
    m_icon.addFile(":/img/ouc.png");
	i_del.addFile(":/img/delete.png");
	i_hide.addFile(":/img/hide.png");
	i_exit.addFile(":/img/power.png");
	i_move.addFile(":/img/move.png");
	i_done.addFile(":/img/done.png");
	i_add.addFile(":/img/add.png");
    setWindowIcon(m_icon);
    setStyleSheet(LoadQss());
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool | Qt::FramelessWindowHint);
    m_label.setText("LolRuuuner");
    QFont font;
    font.setFamily("Consolas");
    font.setPixelSize(48);
    m_label.setFont(font);
    //m_newBtn.setText("+");
	m_newBtn.setIcon(i_add);
    //m_delBtn.setText("-");
	m_delBtn.setIcon(i_del);
    //m_exitBtn.setText("Exit");
	m_exitBtn.setIcon(i_exit);
    m_hidBtn.setIcon(i_hide);
    //m_setBtn.setText("Done");
	m_setBtn.setIcon(i_done);
    m_setBtn.setText("Save");
    m_setBtn.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //m_drapBtn.setText("@");
	m_drapBtn.setIcon(i_move);
    m_drapBtn.SetMain(this);
    m_vLayoutTitle.addWidget(&m_comboBox,3);
    m_vLayoutTitle.addWidget(&m_newBtn);
    m_vLayoutTitle.addWidget(&m_delBtn);
    // m_vLayoutTitle.setStretchFactor();
    // m_btnGruop1.setExclusive(true);
    m_headerLayout.addWidget(&m_drapBtn,5);
    m_headerLayout.addWidget(&m_hidBtn);
    m_headerLayout.addWidget(&m_exitBtn,1);
    m_hLayout.addLayout(&m_headerLayout);
    m_hLayout.addWidget(&m_label);
    m_hLayout.addLayout(&m_vLayoutTitle);
    // m_hLayout.addWidget(&m_comboBox);
    // m_hLayout.addWidget(&m_radio11);
    // m_hLayout.addWidget(&m_radio12);
    // m_hLayout.addWidget(&m_radio13);
    m_hLayout.addWidget(&m_setBtn, 3);
    // m_hLayout.addWidget(&m_saveBtn, 1);
    // m_hLayout.addWidget(&m_exitBtn, 1);
    // m_hLayout.addWidget(&m_drapBtn, 1);
    m_hLayout.addWidget(&m_statusBar);
    // m_hLayout.addWidget();
    m_mainWidget.setLayout(&m_hLayout);
    setCentralWidget(&m_mainWidget);
    // resize(300, 600);
    m_trayIcon.setIcon(m_icon);
    m_trayIcon.setToolTip(tr("Known image viewer"));
    QMenu* menu = new QMenu(this);
    m_quit.setText("exit");
    menu->addAction(&m_quit);
    m_trayIcon.setContextMenu(menu);
    m_trayIcon.show();
    m_lcu.LoadFile();
    auto pages = m_lcu.GetSavePages();
    m_comboBox.clear();
    for (auto& i : pages) {
        m_comboBox.addItem(QString::fromStdString(i.GetName()));
    }
    ConnectSignals();
}

Mainwnd::~Mainwnd() {}

void Mainwnd::ConnectSignals() {
    connect(&m_comboBox,
            static_cast<void (QComboBox::*)(const QString&)>(
            &QComboBox::currentTextChanged),
            this, [](const QString & text)
    { qDebug() << text; });
    connect(&m_delBtn, &QPushButton::clicked, this,
    [&] {
        int id = m_comboBox.currentIndex();
        m_lcu.DelSavePage(id);
        auto pages = m_lcu.GetSavePages();
        m_comboBox.clear();
        for (auto& i : pages) {
            m_comboBox.addItem(QString::fromStdString(i.GetName()));
        }
        m_lcu.SaveToFile();
    });
    connect(&m_setBtn, &QPushButton::clicked, this,
    [&] {
        int id = m_comboBox.currentIndex();
        m_lcu.setRune(id);
    });
    connect(&m_newBtn, &QPushButton::clicked, this,
    [ = ] {
        m_lcu.saveRunnePage();
        auto pages = m_lcu.GetSavePages();
        m_comboBox.clear();
        for (auto& i : pages) {
            m_comboBox.addItem(QString::fromStdString(i.GetName()));
        }
        m_lcu.SaveToFile();
    });
    connect(&m_exitBtn, &QPushButton::clicked, this, [ = ]() {
        QApplication* app;
        app->exit(0);
    });
    connect(&m_trayIcon, &QSystemTrayIcon::activated, this, [ = ]() {
        if (isHidden()) {
            resize(m_size);
            show();
        } else {
            m_size = size();
            close();
        }
    });
    connect(&m_hidBtn,&QPushButton::clicked, this, [ = ]() {
        if (isHidden()) {
            resize(m_size);
            show();
        } else {
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
    QFile qss(":/qss/ubuntu.qss");
    if (qss.open(QFile::ReadOnly)) {
        qDebug("Qss open success");
        QString style = QLatin1String(qss.readAll());
        qss.close();
        return style;
    } else {
        qDebug("Qt StyleSheet Open failed");
    }
    return QString();
}

void Mainwnd::OnClick() {}
