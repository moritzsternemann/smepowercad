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

#include "cad_sprinkler_wetalarmvalve.h"

CAD_sprinkler_wetAlarmValve::CAD_sprinkler_wetAlarmValve() : CADitem(CADitemTypes::Sprinkler_WetAlarmValve)
{
    wizardParams.insert("Position x", 0.0);
    wizardParams.insert("Position y", 0.0);
    wizardParams.insert("Position z", 0.0);
    wizardParams.insert("Angle x", 0.0);
    wizardParams.insert("Angle y", 0.0);
    wizardParams.insert("Angle z", 0.0);

    processWizardInput();
    calculate();
}

CAD_sprinkler_wetAlarmValve::~CAD_sprinkler_wetAlarmValve()
{

}

QList<CADitemTypes::ItemType> CAD_sprinkler_wetAlarmValve::flangable_items(int flangeIndex)
{
    Q_UNUSED(flangeIndex);
    QList<CADitemTypes::ItemType> flangable_items;
    flangable_items.append(CADitemTypes::Sprinkler_CompressedAirWaterContainer);
    flangable_items.append(CADitemTypes::Sprinkler_Distribution);
    flangable_items.append(CADitemTypes::Sprinkler_Flange);
    flangable_items.append(CADitemTypes::Sprinkler_Head);
    flangable_items.append(CADitemTypes::Sprinkler_Pipe);
    flangable_items.append(CADitemTypes::Sprinkler_PipeEndCap);
    flangable_items.append(CADitemTypes::Sprinkler_PipeReducer);
    flangable_items.append(CADitemTypes::Sprinkler_PipeTurn);
    flangable_items.append(CADitemTypes::Sprinkler_Pump);
    flangable_items.append(CADitemTypes::Sprinkler_PipeTeeConnector);
    flangable_items.append(CADitemTypes::Sprinkler_Valve);
    flangable_items.append(CADitemTypes::Sprinkler_WetAlarmValve);
    flangable_items.append(CADitemTypes::Sprinkler_ZoneCheck);

    return flangable_items;
}

QImage CAD_sprinkler_wetAlarmValve::wizardImage()
{
    QImage image;
    QFileInfo fileinfo(__FILE__);
    QString imageFileName = fileinfo.baseName();
    imageFileName.prepend(":/itemGraphic/");
    imageFileName.append(".png");
    image.load(imageFileName, "PNG");

    return image;
}

QString CAD_sprinkler_wetAlarmValve::iconPath()
{
    return ":/icons/cad_sprinkler/cad_sprinkler_wetalarmvalve.svg";
}

QString CAD_sprinkler_wetAlarmValve::domain()
{
    return "Sprinkler";
}

QString CAD_sprinkler_wetAlarmValve::description()
{
    return "Sprinkler|Wet alarm valve";
}

void CAD_sprinkler_wetAlarmValve::calculate()
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
}

void CAD_sprinkler_wetAlarmValve::processWizardInput()
{

}

QMatrix4x4 CAD_sprinkler_wetAlarmValve::rotationOfFlange(quint8 num)
{
    return matrix_rotation;
}
