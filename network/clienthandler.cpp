/**********************************************************************
** smepowercad
** Copyright (C) 2015 Smart Micro Engineering GmbH
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/

#include "clienthandler.h"

ClientHandler::ClientHandler(QObject *parent, QTcpSocket* socket, ItemDB* itemDB) :
    QObject(parent)
{
    this->socket = socket;
    this->itemDB = itemDB;

    QString debugStr;

    debugStr += "New connection ";

    if (socket->socketType() == QAbstractSocket::TcpSocket)
        debugStr += "tcp from ";
    else if (socket->socketType() == QAbstractSocket::UdpSocket)
        debugStr += "udp from ";
    else if (socket->socketType() == QAbstractSocket::UnknownSocketType)
        debugStr += " - unknown socket type - ";

    debugStr += socket->peerAddress().toString() + ":" + QString().setNum(socket->peerPort()) + " \r\n";

    // TBD: do something with the debugstring...

    socket->write("Hello\r\n");

    connect(socket, SIGNAL(readyRead()), this, SLOT(slot_read_ready()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(slot_disconnected()));
}


void ClientHandler::slot_read_ready()
{
    while (socket->canReadLine())
    {
        // Data format:
        // COMMAND id [$parentId] [key]>[value];[key]>[value];...
        QString line = QString::fromUtf8(this->socket->readLine());
        line.remove(QRegExp("[\\r\\n]"));      // Strip newlines at the beginning and at the end
        int commandLength = line.indexOf(' ');
        if (commandLength == -1) commandLength = line.length();
        QString command = line.left(commandLength);
        line.remove(0, commandLength + 1);  // Remove command and optional space
        //line = line.trimmed();      // Strip paces and newlines at the beginning and at the end
        int idLength = line.indexOf(' ');
        if (idLength == -1)
            idLength = line.length();

        printf("Received data: \r\n");

        quint64 id = 0;
        bool idValid = true;

        //if (idLength > 0)
        id = line.left(idLength).toULongLong(&idValid);

        line.remove(0, idLength + 1);       // Remove id and optional space

        // Parse key/value pairs now
        QStringList commandChunks = line.split(';', QString::SkipEmptyParts);
        QMap<QString, QString> data;

        foreach(QString commandChunk, commandChunks)
        {
            printf("Decoding chunk: %s\r\n", commandChunk.toLatin1().data());
            QStringList key_value_pair = commandChunk.split('>');
            if (key_value_pair.length() != 2)
            {
                socket->write("ERROR: key_value_pair length invalid\r\n");
                continue;
            }
            // key and value are base64 encoded.
//            QString key = QString::fromUtf8(QByteArray::fromBase64(key_value_pair.at(0).toUtf8()));
//            QString value = QString::fromUtf8(QByteArray::fromBase64(key_value_pair.at(1).toUtf8()));
// DEBUG: disable base64 coding to use it manually in a terminal
            QString key = key_value_pair.at(0);
            QString value = key_value_pair.at(1);
            data.insert(key, value);
        }

        if (command == "A")     // Get All
        {
            socket->write(itemDB->network_getAll());
            continue;
        }

        if (command == "M")     // Modify item
        {
            socket->write(itemDB->network_modifyItem(id, data));
            continue;
        }

        if (command == "D")     // Delete item
        {
            socket->write(itemDB->network_deleteItem(id));
            continue;
        }

        if (command == "G")     // Get item
        {
            socket->write(itemDB->network_getItem(id));
            continue;
        }

        if (command == "N")     // New item; id field is used as requested item type!
        {
            QByteArray response = itemDB->network_newItem(id, data);
            socket->write(response);
            if (!response.startsWith("Error"))
                emit signal_broadcast(this->socket, response);
            continue;
        }

        if (command == "C")     // Change Layer of item
        {
            QByteArray response = itemDB->network_changeLayerOfItem(id, data);
            socket->write(response);
            if (!response.startsWith("Error"))
                emit signal_broadcast(this->socket, response);
            continue;
        }

        if (command == "n")     // New layer
        {
            QByteArray response = itemDB->network_newLayer(data);
            socket->write(response);
            if (!response.startsWith("Error"))
                emit signal_broadcast(this->socket, response);
            continue;
        }

        if (command == "m")     // Modify layer
        {
            QByteArray response = itemDB->network_modifyLayer(data);
            socket->write(response);
            if (!response.startsWith("Error"))
                emit signal_broadcast(this->socket, response);
            continue;
        }

        if (command == "d")     // Delete layer
        {
            QByteArray response = itemDB->network_deleteLayer(data);
            socket->write(response);
            if (!response.startsWith("Error"))
                emit signal_broadcast(this->socket, response);
            continue;
        }

        if (command == "c")     // Change Position of Layer (move layer)
        {
            QByteArray response = itemDB->network_moveLayer(data);
            socket->write(response);
            if (!response.startsWith("Error"))
                emit signal_broadcast(this->socket, response);
            continue;
        }

//        if (command == "N") // Creates a new set of data in the parent identified by id
//        {
//            QByteArray response = itemDB->create(data).toUtf8();
//            socket->write(response);
//            if (!response.startsWith("ERROR"))
//                emit signal_broadcast(this->socket, response);
//            continue;
//        }

//        if (command == "S") // Set a set of data, overwrites all keys
//        {
//            if (!idValid)
//            {
//                socket->write("ERROR: unable to decode id\r\n");
//                continue;
//            }
//            socket->write(itemDB->set(id, data).toUtf8());
//            continue;
//        }

//        if (command == "C") // Change a set of data, overwrites the given keys
//        {
//            if (!idValid)
//            {
//                socket->write("ERROR: unable to decode id\r\n");
//                continue;
//            }
//            QByteArray response = itemDB->change(id, data).toUtf8();
//            socket->write(response);
//            if (!response.startsWith("ERROR"))
//                emit signal_broadcast(this->socket, response);
//            continue;
//        }

//        // Move id to the parent "toId"
//        if (command == "M") // Move a set of data from a node point to another
//        {
//            if (!idValid)
//            {
//                socket->write("ERROR: unable to decode id\r\n");
//                continue;
//            }

//            quint64 parentIdSource = data.value("parentIdSource").toULongLong();
//            quint64 parentIdDest = data.value("parentIdDest").toULongLong();
//            quint64 index_dest = data.value("index_dest").toULongLong();
//            QByteArray response = itemDB->move(id, parentIdSource, parentIdDest, index_dest).toUtf8();
//            socket->write(response);
//            if (!response.startsWith("ERROR"))
//                emit signal_broadcast(this->socket, response);
//            continue;
//        }

//        // Copy id to the parent "toId"
//        if (command == "C") // Move a set of data from a node point to another
//        {
//            if (!idValid)
//            {
//                socket->write("ERROR: unable to decode id\r\n");
//                continue;
//            }

//            quint64 parentIdSource = data.value("parentIdSource").toULongLong();
//            quint64 parentIdDest = data.value("parentIdDest").toULongLong();
//            quint64 index_dest = data.value("index_dest").toULongLong();
//            QByteArray response = itemDB->copy(id, parentIdSource, parentIdDest, index_dest).toUtf8();
//            socket->write(response);
//            if (!response.startsWith("ERROR"))
//                emit signal_broadcast(this->socket, response);
//            continue;
//        }

//        if (command == "R") // Remove a set of data
//        {
//            socket->write(itemDB->remove(id).toUtf8());
//            continue;
//        }

//        if (command == "L") // Lock: Disable changing, moving, deletion
//        {
//            if (!idValid)
//            {
//                socket->write("ERROR: unable to decode id\r\n");
//                continue;
//            }
//            socket->write(itemDB->lock(id).toUtf8());
//            continue;
//        }

//        if (command == "U") // Unlock: Enable changing, moving, deletion
//        {
//            if (!idValid)
//            {
//                socket->write("ERROR: unable to decode id\r\n");
//                continue;
//            }
//            socket->write(itemDB->unlock(id).toUtf8());
//            continue;
//        }

        // If control reaches this point, we have an unsupported command
        socket->write("ERROR: Command not supported: " + command.toUtf8() + "\r\n");
    }
}

void ClientHandler::slot_disconnected()
{
    QString debugStr;

    debugStr += "Closed connection ";

    if (socket->socketType() == QAbstractSocket::TcpSocket)
        debugStr += "tcp from ";
    else if (socket->socketType() == QAbstractSocket::UdpSocket)
        debugStr += "udp from ";
    else if (socket->socketType() == QAbstractSocket::UnknownSocketType)
        debugStr += " - unknown socket type - ";

    debugStr += socket->peerAddress().toString() + ":" + QString().setNum(socket->peerPort()) + " \r\n";

    // TBD: do something with the debugstring...

    emit signal_connectionClosed(this->socket, this);
}
