#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "mqttclient.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void on_buttonConnect_clicked();

    void on_buttonWrite_clicked();

    void on_buttonClear_clicked();

    void doLog(const QString &text);

private:
    Ui::MainWidget *ui;

    MQTTClient *m_mqttClient;
};

#endif // MAINWIDGET_H
