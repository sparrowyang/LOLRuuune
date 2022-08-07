#include "mainwnd.h"
Mainwnd::Mainwnd(/* args */)
{
    setStyleSheet(LoadQss());

    m_btn.setText("00");
    m_label.setText("00");
    m_label.setText("00");
    m_hLayout.addWidget(&m_btn);
    m_hLayout.addWidget(&m_label);
    m_hLayout.addWidget(&m_lindEdit);
    m_hLayout.addWidget(&m_radio);
    m_mainWidget.setLayout(&m_hLayout);
    setCentralWidget(&m_mainWidget);
    resize(200, 200);
    ConnectSignals();
}

Mainwnd::~Mainwnd()
{
}

void Mainwnd::ConnectSignals()
{
    connect(&m_btn, &QPushButton::clicked, this,&Mainwnd::OnClick);
    // auto ptr = std::shared_ptr<Mainwnd>(this);
    connect(&m_lindEdit,&QLineEdit::textChanged,this,[=]{
        m_lcu.addRunePage();
    });
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

void Mainwnd::OnClick(){
    m_lcu.setRune();
}