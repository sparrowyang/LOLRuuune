#include "mainwnd.h"
Mainwnd::Mainwnd(/* args */)
{
    qDebug() << "Windows Init...";
    setStyleSheet(LoadQss());
    //隐藏窗口边框，这样会无法移动和调整大小
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);
    m_newBtn.setText("+");
    m_delBtn.setText("-");
    m_exitBtn.setText("Exit");
    m_setBtn.setText("Done");
    m_label.setText("00");
    m_label.setText("00");
    
    m_comboBox.addItems(QStringList({
        "[压缩]100%胜率符文", "[压缩]100%胜率符文", "[压缩]100%胜率符文",
        "[压缩]100%胜率符文", "[压缩]100%胜率符文", "[压缩]100%胜率符文",
        "[压缩]100%胜率符文", "[压缩]100%胜率符文", "[压缩]100%胜率符文"
        }));

    m_radio11.setText("radio");
    m_radio12.setText("radio");
    m_radio13.setText("radio");
    m_btnGruop1.addButton(&m_radio11);
    m_btnGruop1.addButton(&m_radio12);
    m_btnGruop1.addButton(&m_radio13);

    m_vLayoutTitle.addWidget(&m_comboBox, 3);
    m_vLayoutTitle.addWidget(&m_newBtn);
    m_vLayoutTitle.addWidget(&m_delBtn);
    // m_vLayoutTitle.setStretchFactor();
    m_btnGruop1.setExclusive(true);

    // m_hLayout.addWidget(&m_label);
    m_hLayout.addLayout(&m_vLayoutTitle);
    // m_hLayout.addWidget(&m_comboBox);
    // m_hLayout.addWidget(&m_radio11);
    // m_hLayout.addWidget(&m_radio12);
    // m_hLayout.addWidget(&m_radio13);
    m_hLayout.addWidget(&m_setBtn);
    m_hLayout.addWidget(&m_exitBtn);
    // m_hLayout.addWidget();
    m_mainWidget.setLayout(&m_hLayout);
    setCentralWidget(&m_mainWidget);
    resize(300, 600);
    m_trayIcon.setIcon(QIcon("ouc.png"));
    m_trayIcon.setToolTip(tr("Known image viewer"));
    QMenu *menu = new QMenu(this);
    m_quit.setText("exit");
    menu->addAction(&m_quit);
    m_trayIcon.setContextMenu(menu);

    m_trayIcon.show();
    ConnectSignals();
}

Mainwnd::~Mainwnd()
{
}

void Mainwnd::ConnectSignals()
{
    //带参数要这样写
    connect(&m_comboBox, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentTextChanged), this, [](const QString &text)
            { qDebug() << text; });
    connect(&m_newBtn, &QPushButton::clicked, this, []
            { qDebug() << "Clicked"; });
    // auto ptr = std::shared_ptr<Mainwnd>(this);
    connect(&m_lindEdit, &QLineEdit::textChanged, this, [=]
            {
        // m_lcu.addRunePage();
            qDebug()<<"text Change"; });
    connect(&m_exitBtn, &QPushButton::clicked, this, [=]()
            {
        QApplication *app;
        app->exit(0); });
    connect(&m_trayIcon, &QSystemTrayIcon::activated, this, [=]()
            {
                if (isHidden())
                {
                    show();
                }
                else
                {
                    close();
                } });
    connect(&m_quit, &QAction::triggered, this, []()
            {
            QApplication* app;
            app->exit(0); });
}
QString Mainwnd::LoadQss()
{
    QFile qss("ubuntu.qss");
    if (qss.open(QFile::ReadOnly))
    {
        qDebug("Qss open success");
        QString style = QLatin1String(qss.readAll());
        qss.close();
        return style;
    }
    else
    {
        qDebug("Qt StyleSheet Open failed");
    }
    return QString();
}

void Mainwnd::OnClick()
{
    // m_lcu.setRune();
}