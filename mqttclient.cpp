#include "mqttclient.h"
#include <QDebug>

#define MQTT_HOSTNAME   "clouddata.usr.cn"
#define MQTT_PORT       1883

#define MQTT_CLIENT_SUBSCRIBE_PREFIX    "$USR/DevTx"
#define MQTT_CLIENT_PUBLISH_PREFIX      "$USR/DevRx"

MQTTClient::MQTTClient(const QString &userName, const QString &passwordMD5, const QString &deviceId, QObject *parent) : QObject(parent)
{
    m_client=NULL;
    this->m_userName=userName;
    this->m_passwordMD5=passwordMD5;
    this->m_deviceId=deviceId;
}

MQTTClient::~MQTTClient()
{
    if(m_client!=NULL)
    {
        if(m_client->state()==QMqttClient::Connected)
        {
            m_client->disconnectFromHost();
        }
        delete m_client;
        m_client=NULL;
    }
}

bool MQTTClient::isOpened()
{
    if(m_client==NULL)
    {
        return false;
    }
    else if(m_client->state()==QMqttClient::Connected)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void MQTTClient::open()
{
    if(m_client!=NULL)
    {
        return;
    }
    m_client = new QMqttClient(this);
    m_client->setHostname(MQTT_HOSTNAME);
    m_client->setPort(MQTT_PORT);
    m_client->setUsername(m_userName);
    m_client->setClientId(QString("APP:%1").arg(m_userName));
    m_client->setPassword(m_passwordMD5);
    m_client->setProtocolVersion(QMqttClient::MQTT_3_1_1);

    connect(m_client, SIGNAL(connected()), this, SLOT(doConnected()));
    connect(m_client, SIGNAL(disconnected()), this, SLOT(doDisconnected()));
    connect(m_client, SIGNAL(messageReceived(QByteArray,QMqttTopicName)), this, SLOT(doMessageReceived(QByteArray,QMqttTopicName)));

    m_client->connectToHost();
    emit log("MQTTClient 正在连接...");
}

void MQTTClient::close()
{
    if(m_client!=NULL)
    {
        if(m_client->state()==QMqttClient::Connected)
        {
            m_client->disconnectFromHost();
        }
        delete m_client;
        m_client=NULL;
    }
}

void MQTTClient::write(const QByteArray &data)
{
    if(m_client!=NULL)
    {
        m_client->publish(QString("%1/%2").arg(MQTT_CLIENT_PUBLISH_PREFIX).arg(this->m_deviceId), data);
        emit log(QString("MQTTClient 正发布设备消息，设备ID: %1, 消息:%2").arg(this->m_deviceId).arg(QString::fromLatin1(data)));
    }
}

void MQTTClient::doConnected()
{
    emit log("MQTTClient 已建立连接！");
    emit log(QString("MQTTClient 正订阅设备消息，设备ID: %1").arg(this->m_deviceId));
    QMqttSubscription *subscription=m_client->subscribe(QString("%1/%2").arg(MQTT_CLIENT_SUBSCRIBE_PREFIX).arg(this->m_deviceId));
    connect(subscription, SIGNAL(stateChanged(SubscriptionState)),
            this, SLOT(doQMqttSubscriptionStateChanged(SubscriptionState)));
}

void MQTTClient::doDisconnected()
{
    emit log("MQTTClient 已断开连接！");
    this->close();
}

void MQTTClient::doMessageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    emit log(QString("MQTTClient 接收到数据: %1").arg(QString::fromLatin1(message)));
}

void MQTTClient::doQMqttSubscriptionStateChanged(SubscriptionState subscriptionState)
{
    if(subscriptionState==QMqttSubscription::Subscribed)
    {
        emit log("订阅设备消息成功！");
    }
}
