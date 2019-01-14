#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    m_mqttClient=NULL;
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_buttonConnect_clicked()
{
    if(m_mqttClient!=NULL)
    {
        m_mqttClient->close();
        m_mqttClient=NULL;
    }
    m_mqttClient=new MQTTClient(ui->lineUsername->text(), ui->linePasswordMD5->text(), ui->lineDeviceId->text());
    connect(m_mqttClient, SIGNAL(log(QString)), this, SLOT(doLog(QString)));
    m_mqttClient->open();
}

void MainWidget::on_buttonWrite_clicked()
{
    if((m_mqttClient==NULL) || (!m_mqttClient->isOpened()))
    {
        ui->textLog->append("MQTT客户端未打开!");
        return;
    }
    m_mqttClient->write(ui->lineWrite->text().toLatin1());
}

void MainWidget::on_buttonClear_clicked()
{
    ui->textLog->clear();
}

void MainWidget::doLog(const QString &text)
{
    ui->textLog->append(text);
}
