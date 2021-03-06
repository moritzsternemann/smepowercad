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

#include "cad_arch_levelslab.h"

CAD_arch_levelSlab::CAD_arch_levelSlab() : CADitem(CADitemTypes::Arch_LevelSlab)
{
    wizardParams.insert("Position x", 0.0);
    wizardParams.insert("Position y", 0.0);
    wizardParams.insert("Position z", 0.0);
    wizardParams.insert("Angle x", 0.0);
    wizardParams.insert("Angle y", 0.0);
    wizardParams.insert("Angle z", 0.0);

    wizardParams.insert("a",  500.0);
    wizardParams.insert("b", 4000.0);
    wizardParams.insert("l", 4000.0);

    slab = new CAD_basic_box();
    subItems.append(slab);

    processWizardInput();
    calculate();
}

CAD_arch_levelSlab::~CAD_arch_levelSlab()
{

}

QList<CADitemTypes::ItemType> CAD_arch_levelSlab::flangable_items(int flangeIndex)
{
    Q_UNUSED(flangeIndex);
    QList<CADitemTypes::ItemType> flangable_items;
    flangable_items.append(CADitemTypes::Arch_Support);
    flangable_items.append(CADitemTypes::Arch_Wall_loadBearing);
    flangable_items.append(CADitemTypes::Arch_Wall_nonLoadBearing);
    return flangable_items;
}

QImage CAD_arch_levelSlab::wizardImage()
{
    QImage image;
    QFileInfo fileinfo(__FILE__);
    QString imageFileName = fileinfo.baseName();
    imageFileName.prepend(":/itemGraphic/");
    imageFileName.append(".png");
    image.load(imageFileName, "PNG");

    return image;
}

QString CAD_arch_levelSlab::iconPath()
{
    return ":/icons/cad_arch/cad_arch_levelslab.svg";
}

QString CAD_arch_levelSlab::domain()
{
    return "Architecture";
}

QString CAD_arch_levelSlab::description()
{
    return "Architecture|Level slab";
}

void CAD_arch_levelSlab::calculate()
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
    QVector3D position_sl = position + matrix_rotation * (QVector3D(l/2, b/2, a/2));
    slab->wizardParams.insert("Position x", (position_sl.x()));
    slab->wizardParams.insert("Position y", (position_sl.y()));
    slab->wizardParams.insert("Position z", (position_sl.z()));
    slab->wizardParams.insert("Angle x", (angle_x));
    slab->wizardParams.insert("Angle y", (angle_y));
    slab->wizardParams.insert("Angle z", (angle_z));
    slab->wizardParams.insert("l", (l));
    slab->wizardParams.insert("b", (b));
    slab->wizardParams.insert("a", (a));
    slab->processWizardInput();
    slab->calculate();

    this->snap_flanges.append(slab->snap_vertices[4]);
    this->snap_flanges.append(slab->snap_vertices[5]);
    this->snap_flanges.append(slab->snap_vertices[6]);
    this->snap_flanges.append(slab->snap_vertices[7]);
    this->snap_vertices = slab->snap_vertices;
    this->snap_center = slab->snap_center;

    this->boundingBox = slab->boundingBox;
    //    this->boundingBox.enterVertex(position + matrix_rotation * (QVector3D(0.0, 0.0, 0.0)));
    //    this->boundingBox.enterVertex(position + matrix_rotation * (QVector3D(0.0, a,   0.0)));
    //    this->boundingBox.enterVertex(position + matrix_rotation * (QVector3D(0.0, a,   b)));
    //    this->boundingBox.enterVertex(position + matrix_rotation * (QVector3D(0.0, 0.0, b)));
    //    this->boundingBox.enterVertex(position + matrix_rotation * (QVector3D(l  , 0.0, 0.0)));
    //    this->boundingBox.enterVertex(position + matrix_rotation * (QVector3D(l  , a  , 0.0)));
    //    this->boundingBox.enterVertex(position + matrix_rotation * (QVector3D(l  , a  , b)));
    //    this->boundingBox.enterVertex(position + matrix_rotation * (QVector3D(l  , 0.0, b)));
}

void CAD_arch_levelSlab::processWizardInput()
{
    position.setX(wizardParams.value("Position x").toDouble());
    position.setY(wizardParams.value("Position y").toDouble());
    position.setZ(wizardParams.value("Position z").toDouble());
    angle_x = wizardParams.value("Angle x").toDouble();
    angle_y = wizardParams.value("Angle y").toDouble();
    angle_z = wizardParams.value("Angle z").toDouble();

    a = wizardParams.value("a").toDouble();
    b = wizardParams.value("b").toDouble();
    l = wizardParams.value("l").toDouble();

}

QMatrix4x4 CAD_arch_levelSlab::rotationOfFlange(quint8 num)
{
    if (num == 1)
        return matrix_rotation;
    else if(num == 2)
    {
        QMatrix4x4 m;
        m.setToIdentity();
        m.rotate(90.0, 0.0, 0.0, 1.0);
        return matrix_rotation * m;
    }
    else if(num == 3)
    {
        QMatrix4x4 m;
        m.setToIdentity();
        m.rotate(180.0, 0.0, 0.0, 1.0);
        return matrix_rotation * m;
    }
    else
    {
        QMatrix4x4 m;
        m.setToIdentity();
        m.rotate(270.0, 0.0, 0.0, 1.0);
        return matrix_rotation * m;
    }
}
