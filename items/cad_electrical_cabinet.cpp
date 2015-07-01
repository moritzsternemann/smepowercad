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

#include "cad_electrical_cabinet.h"
#include "itemdb.h"

CAD_electrical_cabinet::CAD_electrical_cabinet() : CADitem(CADitemTypes::Electrical_Cabinet)
{
    cabinet = new CAD_basic_duct;
    back = new CAD_basic_box;
    door = new CAD_basic_box;
    socket = new CAD_basic_box;
    this->subItems.append(cabinet);
    this->subItems.append(back);
    this->subItems.append(door);
    this->subItems.append(socket);
    wizardParams.insert("Position x", 0.0);
    wizardParams.insert("Position y", 0.0);
    wizardParams.insert("Position z", 0.0);
    wizardParams.insert("Angle x", 0.0);
    wizardParams.insert("Angle y", 0.0);
    wizardParams.insert("Angle z", 0.0);

    wizardParams.insert("a", 1500.0);       //Höhe Schrank
    wizardParams.insert("a1", 300.0);       //Höhe Sockel
    wizardParams.insert("b", 500.0);        //Tiefe Sockel
    wizardParams.insert("l", 500.0);        //Breite
    wizardParams.insert("i", 100.0);        //Überhang Schrank
    wizardParams.insert("s", 10.0);         //Wandstärke
    wizardParams.insert("alpha", -45.0);    //Öffnungswinkel Tür


    processWizardInput();
    calculate();
}

CAD_electrical_cabinet::~CAD_electrical_cabinet()
{

}

QList<CADitemTypes::ItemType> CAD_electrical_cabinet::flangable_items(int flangeIndex)
{
    Q_UNUSED(flangeIndex);
    QList<CADitemTypes::ItemType> flangable_items;
    flangable_items.append(CADitemTypes::Electrical_Cabinet);
    return flangable_items;
}

QImage CAD_electrical_cabinet::wizardImage()
{
    QImage image;
    QFileInfo fileinfo(__FILE__);
    QString imageFileName = fileinfo.baseName();
    imageFileName.prepend(":/itemGraphic/");
    imageFileName.append(".png");
    image.load(imageFileName, "PNG");

    return image;
}

QString CAD_electrical_cabinet::iconPath()
{
    return ":/icons/cad_electrical/cad_electrical_cabinet.svg";
}

QString CAD_electrical_cabinet::domain()
{
    return "Electrical";
}

QString CAD_electrical_cabinet::description()
{
    return "Electrical|Cabinet";
}

void CAD_electrical_cabinet::calculate()
{
    matrix_rotation.setToIdentity();
    matrix_rotation.rotate(angle_x, 1.0, 0.0, 0.0);
    matrix_rotation.rotate(angle_y, 0.0, 1.0, 0.0);
    matrix_rotation.rotate(angle_z, 0.0, 0.0, 1.0);

    boundingBox.reset();

    this->snap_flanges.clear();
    this->snap_center.clear();
    this->snap_vertices.clear();

    this->snap_basepoint = (position);

    QVector3D position_cab = position + matrix_rotation * QVector3D(l/2, b/2, a1 + a/2);
    cabinet->wizardParams.insert("Position x", position_cab.x());
    cabinet->wizardParams.insert("Position y", position_cab.y());
    cabinet->wizardParams.insert("Position z", position_cab.z());
    cabinet->wizardParams.insert("Angle x", angle_x);
    cabinet->wizardParams.insert("Angle y", angle_y);
    cabinet->wizardParams.insert("Angle z", angle_z-90.0);

    cabinet->wizardParams.insert("l", (b+i));
    cabinet->wizardParams.insert("b", (l));
    cabinet->wizardParams.insert("a", (a));
    cabinet->wizardParams.insert("s", (s));
    cabinet->layer = this->layer;
    cabinet->processWizardInput();
    cabinet->calculate();

    QVector3D position_sock = position + matrix_rotation * QVector3D(l/2, 0.0, a1/2);
    socket->wizardParams.insert("Position x", position_sock.x());
    socket->wizardParams.insert("Position y", position_sock.y());
    socket->wizardParams.insert("Position z", position_sock.z());
    socket->wizardParams.insert("Angle x", angle_x);
    socket->wizardParams.insert("Angle y", angle_y);
    socket->wizardParams.insert("Angle z", angle_z);

    socket->wizardParams.insert("l", l);
    socket->wizardParams.insert("b", b);
    socket->wizardParams.insert("a", a1);
    socket->layer = this->layer;
    socket->processWizardInput();
    socket->calculate();

    QVector3D position_back = position + matrix_rotation * QVector3D(l/2, b/2 - s/2, a1 + a/2);
    back->wizardParams.insert("Position x", position_back.x());
    back->wizardParams.insert("Position y", position_back.y());
    back->wizardParams.insert("Position z", position_back.z());
    back->wizardParams.insert("Angle x", angle_x);
    back->wizardParams.insert("Angle y", angle_y);
    back->wizardParams.insert("Angle z", angle_z);

    back->wizardParams.insert("l", l - 2*s);
    back->wizardParams.insert("b", s);
    back->wizardParams.insert("a", a - 2*s);
    back->layer = this->layer;
    back->processWizardInput();
    back->calculate();


    QVector3D position_door;
    if(alpha < 0)
    {
        QMatrix4x4 matrix_door;
        matrix_door.setToIdentity();
        matrix_door.rotate(alpha, 0.0, 0.0, 1.0);
        position_door = position + matrix_rotation * (QVector3D(0.0, -b/2 - i, 0.0) + matrix_door * QVector3D(l/2, s/2, a1 + a/2));
    }
    else
    {
        QMatrix4x4 matrix_door;
        matrix_door.setToIdentity();
        matrix_door.rotate(alpha, 0.0, 0.0, 1.0);
        position_door = position + matrix_rotation * (QVector3D(l, -b/2 - i, 0.0) + matrix_door * QVector3D(-l/2, s/2, a1 + a/2));
    }
    door->wizardParams.insert("Position x", position_door.x());
    door->wizardParams.insert("Position y", position_door.y());
    door->wizardParams.insert("Position z", position_door.z());
    door->wizardParams.insert("Angle x", angle_x);
    door->wizardParams.insert("Angle y", angle_y);
    door->wizardParams.insert("Angle z", angle_z + alpha);

    door->wizardParams.insert("l", l - 2*s);
    door->wizardParams.insert("b", s);
    door->wizardParams.insert("a", a - 2*s);
    door->layer = this->layer;
    door->processWizardInput();
    door->calculate();

    this->boundingBox.enterVertices(cabinet->boundingBox.getVertices());
    this->boundingBox.enterVertices(door->boundingBox.getVertices());
    this->boundingBox.enterVertices(socket->boundingBox.getVertices());
    this->boundingBox.enterVertices(back->boundingBox.getVertices());
}

void CAD_electrical_cabinet::processWizardInput()
{
    position.setX(wizardParams.value("Position x").toDouble());
    position.setY(wizardParams.value("Position y").toDouble());
    position.setZ(wizardParams.value("Position z").toDouble());
    angle_x = wizardParams.value("Angle x").toDouble();
    angle_y = wizardParams.value("Angle y").toDouble();
    angle_z = wizardParams.value("Angle z").toDouble();

    a = wizardParams.value("a").toDouble();
    a1 = wizardParams.value("a1").toDouble();
    b = wizardParams.value("b").toDouble();
    l = wizardParams.value("l").toDouble();
    i = wizardParams.value("i").toDouble();
    s = wizardParams.value("s").toDouble();
    alpha = wizardParams.value("alpha").toDouble();

}

QMatrix4x4 CAD_electrical_cabinet::rotationOfFlange(quint8 num)
{
    return matrix_rotation;
}
