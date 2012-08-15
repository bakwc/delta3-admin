#include "network.h"
#include "netextract.h"

using namespace delta3;

Network::Network(QHostAddress adr, QObject *parent) :
    QObject(parent), adr_(adr)
{
    socket_ = new QTcpSocket(this);
    QObject::connect(socket_, SIGNAL(readyRead()),
                     this, SLOT(onDataReceived()));

    QObject::connect(socket_, SIGNAL(connected()),
                     this,SLOT(onConnected()));
}


void Network::connectToServer()
{
    if (socket_->state()!=QTcpSocket::UnconnectedState)
        return;

    socket_->connectToHost(adr_, 1235);
}


void Network::onDataReceived()
{
    buf_ += socket_->readAll();
    //buf_ = socket_->readAll();

    if (buf_.size() < 3) return; // if we don't read header

    if (getProtoId(buf_) != CSPYP1_PROTOCOL_ID ||
            getProtoVersion(buf_) != CSPYP1_PROTOCOL_VERSION)
    {
        // wrong packet - disconnecting client
        qDebug() << Q_FUNC_INFO << " PROTOCOL ERROR";
        qDebug() << getProtoId(buf_) << getProtoVersion(buf_);
        //this->disconnectFromHost();
        return;
    }

    switch (getCommand(buf_))
    {
    case CMD1_RLIST:
        parseList();
        break;
    case CMD1_TRANSMIT:
        parseResponse();
        break;
    case CMD1_PING:
        parsePing();
        break;
    default:
        // for warning disable
        break;
    }
}


void Network::parseList()
{
    if (buf_.size()<5) // TODO: remove magic number
        return;     // not all data avaliable

    if (buf_.size()<5+getClientNumber(buf_)*CMD1_CLIENT_INFO_SIZE) // TODO: remove magic number
        return;     // not all data avaliable

    clients_.clear();

    for (qint16 i=0;i<getClientNumber(buf_);i++)
    {
        Client *client = new Client(this);
        client->setId(getClientId(i,buf_));
        client->setHash(getClientHash(i,buf_));
        client->setOs(getClientOs(i,buf_));
        client->setDevice(getClientDevice(i,buf_));
        client->setCaption(getClientCaption(i,buf_));
        client->setIp(getClientIp(i,buf_));
        clients_.insert(getClientId(i,buf_), client);
    }
    emit listUpdated();

    buf_ = buf_.right(buf_.size()-(5+getClientNumber(buf_)*CMD1_CLIENT_INFO_SIZE));
    if (buf_.size()>0)
        onDataReceived();   // If something in buffer - parse again
}


void Network::parsePing()
{
    if (buf_.size()<3) // TODO: remove magic number
        return;     // not all data avaliable

    QByteArray cmd;
    cmd.append(CSPYP1_PROTOCOL_ID);
    cmd.append(CSPYP1_PROTOCOL_VERSION);
    cmd.append(CMD1_PING);
    socket_->write(cmd);

    buf_=buf_.right(buf_.size()-3);
    if (buf_.size()>0)
        onDataReceived();   // If something in buffer - parse again
}


void Network::parseResponse()
{
    if (buf_.size()<9) // TODO: remove magic number
        return;     // not all data avaliable

    if (buf_.size() < getPacketLength(buf_) + 9) // TODO: remove magic number
        return; // not all data avaliable

    qint16 from = getClientId(buf_);

    QByteArray cmd = getPacketData(buf_);

    parseProtoTwo(from, cmd);
    return;
}


void Network::parseProtoTwo(qint32 from, const QByteArray &data)
{
    if (getProtoId(data) != CSPYP2_PROTOCOL_ID ||
            getProtoVersion(data) != CSPYP2_PROTOCOL_VERSION)
    {
        // wrong packet - disconnecting client
        qDebug() << Q_FUNC_INFO << " PROTOCOL ERROR!";
        qDebug() << data;
        //this->disconnectFromHost();
        return;
    }


    switch (getCommand2(data))
    {
    case CMD2_TRANSMIT:
        parseMessage(from, data);
        break;
    case CMD2_MODES:
        //TODO: parse avaliable modes
        break;
    default:
        // for warning disable
        break;
    }
}


void Network::parseMessage(qint32 from, const QByteArray &data)
{

    income_.mode = getMode2(data);
    income_.from = from;
    income_.data = getPacketData2(data);

    emit dataIncome();
    buf_.clear();
}


void Network::onConnected()
{
    QByteArray cmd;
    cmd.append(CSPYP1_PROTOCOL_ID);
    cmd.append(CSPYP1_PROTOCOL_VERSION);
    cmd.append(CMD1_ADM);
    QByteArray login="admin";
    QByteArray password="admin";
    login.leftJustified(22,0);
    password.leftJustified(22,0);
    cmd.append(login,22);
    cmd.append(password,22);
    socket_->write(cmd);

    cmd.clear();

    cmd.append(CSPYP1_PROTOCOL_ID);
    cmd.append(CSPYP1_PROTOCOL_VERSION);
    cmd.append(CMD1_LIST);

    socket_->write(cmd);
}


const Clients& Network::getClients() const
{
    return clients_;
}


QString Network::getClientName(qint16 id) const
{
    auto client=clients_.find(id);
    if (client==clients_.end())
        return "";
    return client.value()->getHash();
}

QString	Network::getClientCapt(qint16 id) const
{
    auto client=clients_.find(id);
    if (client==clients_.end())
        return "";
    return client.value()->getCaption();
}


void Network::sendLevelOne(qint16 dest, const QByteArray& data)
{
    QByteArray cmd;
    cmd.append(CSPYP1_PROTOCOL_ID);
    cmd.append(CSPYP1_PROTOCOL_VERSION);
    cmd.append(CMD1_TRANSMIT);
    cmd.append(toBytes(dest));
    cmd.append(toBytes(data.size()));
    cmd.append(data);

    socket_->write(cmd);
}


void Network::sendLevelTwo(qint16 dest, ProtocolMode mode, const QByteArray& data)
{
    QByteArray cmd;
    cmd.append(CSPYP2_PROTOCOL_ID);
    cmd.append(CSPYP2_PROTOCOL_VERSION);
    cmd.append(CMD2_TRANSMIT);
    cmd.append(mode);
    cmd.append(toBytes(data.size()));
    cmd.append(data);
    sendLevelOne(dest, cmd);
}


void Network::activateMode(qint16 client, ProtocolMode mode)
{
    QByteArray cmd;
    cmd.append(CSPYP2_PROTOCOL_ID);
    cmd.append(CSPYP2_PROTOCOL_VERSION);
    cmd.append(CMD2_ACTIVATE);
    cmd.append(mode);

    sendLevelOne(client, cmd);
}


void Network::deactivateMode(qint16 client, ProtocolMode mode)
{
    QByteArray cmd;
    cmd.append(CSPYP2_PROTOCOL_ID);
    cmd.append(CSPYP2_PROTOCOL_VERSION);
    cmd.append(CMD2_DEACTIVATE);
    cmd.append(mode);

    sendLevelOne(client, cmd);
}


const Network::Income& Network::receivedData() const
{
    return income_;
}


Client *Network::getClient(qint16 clientId) const
{
    auto i=clients_.find(clientId);
    if (i!=clients_.end())
        return i.value();
    return NULL;
}


void Network::setClientCaption(qint16 client, const QString& info)
{
    if (getClient(client)!=NULL)
        getClient(client)->setCaption(info);

    QByteArray cmd;
    cmd.append(CSPYP1_PROTOCOL_ID);
    cmd.append(CSPYP1_PROTOCOL_VERSION);
    cmd.append(CMD1_SETINFO);
    cmd.append(toBytes(client));
    cmd.append(toBytes(info,30),30);

    socket_->write(cmd);
}
