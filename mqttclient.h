#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <QObject>
#include <QtMqtt/QMqttClient>
#include <QtMqtt/QMqttSubscription>

typedef QMqttSubscription::SubscriptionState SubscriptionState;

class MQTTClient : public QObject
{
    Q_OBJECT
public:
    explicit MQTTClient(const QString &userName, const QString &passwordMD5, const QString &deviceId, QObject *parent = nullptr);
    ~MQTTClient();

    bool isOpened();
    void open();
    void close();
    void write(const QByteArray &data);

private:
    QString m_userName;
    QString m_passwordMD5;
    QString m_deviceId;
    QMqttClient *m_client;
    QByteArray m_buffer;

private slots:
    void doConnected();
    void doDisconnected();
    void doMessageReceived(const QByteArray &message, const QMqttTopicName &topic);
    void doQMqttSubscriptionStateChanged(SubscriptionState subscriptionState);

signals:
    void log(const QString &text);

public slots:
};

#endif // MQTTCLIENT_H
