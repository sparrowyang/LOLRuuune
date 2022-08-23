#include "mainwnd.h"
Mainwnd::Mainwnd(/* args */) {
    qDebug() << "Windows Init...";
    m_icon.addFile(":/img/ouc.png");
    setWindowIcon(m_icon);
    setStyleSheet(LoadQss());
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool | Qt::FramelessWindowHint);
    m_label.setText("LolRuuune");
    m_newBtn.setText("+");
    m_delBtn.setText("-");
    m_exitBtn.setText("Exit");
    m_setBtn.setText("Done");
    m_saveBtn.setText("Save");
    m_drapBtn.setText("@");
    m_drapBtn.SetMain(this);
    m_vLayoutTitle.addWidget(&m_comboBox, 3);
    m_vLayoutTitle.addWidget(&m_newBtn);
    m_vLayoutTitle.addWidget(&m_delBtn);
    // m_vLayoutTitle.setStretchFactor();
    // m_btnGruop1.setExclusive(true);
    // m_hLayout.addWidget(&m_label);
    m_hLayout.addWidget(&m_label, 1);
    m_hLayout.addLayout(&m_vLayoutTitle, 2);
    // m_hLayout.addWidget(&m_comboBox);
    // m_hLayout.addWidget(&m_radio11);
    // m_hLayout.addWidget(&m_radio12);
    // m_hLayout.addWidget(&m_radio13);
    m_hLayout.addWidget(&m_setBtn, 1);
    // m_hLayout.addWidget(&m_saveBtn, 1);
    m_hLayout.addWidget(&m_exitBtn, 1);
    m_hLayout.addWidget(&m_drapBtn, 1);
    m_hLayout.addWidget(&m_statusBar, 1);
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
    //带参数要这样写
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
            show();
        } else {
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
