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

#include "cad_gas_pipeteeconnector.h"

CAD_Gas_PipeTeeConnector::CAD_Gas_PipeTeeConnector() : CADitem(CADitemTypes::Gas_PipeTeeConnector)
{
    wizardParams.insert("Position x", 0.0);
    wizardParams.insert("Position y", 0.0);
    wizardParams.insert("Position z", 0.0);
    wizardParams.insert("Angle x", 0.0);
    wizardParams.insert("Angle y", 0.0);
    wizardParams.insert("Angle z", 0.0);

    wizardParams.insert("l",500.0);
    wizardParams.insert("l2",200.0);
    wizardParams.insert("l3",200.0);
    wizardParams.insert("d",150.0);
    wizardParams.insert("iso",10.0);
    wizardParams.insert("d3",100.0);
    wizardParams.insert("iso3",10.0);
    wizardParams.insert("alpha",50.0);
    wizardParams.insert("s",10.0);

    pipe = new CAD_basic_pipe();
    branch = new CAD_basic_pipe();
    this->subItems.append(pipe);
    this->subItems.append(branch);

    processWizardInput();
    calculate();
}

CAD_Gas_PipeTeeConnector::~CAD_Gas_PipeTeeConnector()
{
//    arrayBufVertices->destroy();
//    indexBufFaces->destroy();
//    indexBufLines->destroy();
//    delete arrayBufVertices;
//    delete indexBufFaces;
//    delete indexBufLines;
}

QList<CADitemTypes::ItemType> CAD_Gas_PipeTeeConnector::flangable_items(int flangeIndex)
{
    Q_UNUSED(flangeIndex);
    QList<CADitemTypes::ItemType> flangable_items;
    
    return flangable_items;
}

QImage CAD_Gas_PipeTeeConnector::wizardImage()
{
    QImage image;
    QFileInfo fileinfo(__FILE__);
    QString imageFileName = fileinfo.baseName();
    imageFileName.prepend(":/itemGraphic/");
    imageFileName.append(".png");
    image.load(imageFileName, "PNG");
                       
    return image;
}

QString CAD_Gas_PipeTeeConnector::iconPath()
{
    return ":/icons/cad_gas/cad_gas_pipeteeconnector.svg";
}

QString CAD_Gas_PipeTeeConnector::domain()
{
    return "Gas";
}

QString CAD_Gas_PipeTeeConnector::description()
{
    return "Gas|Pipe Tee Connector";
}

void CAD_Gas_PipeTeeConnector::calculate()
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

    pipe->wizardParams.insert("Position x", position.x());
    pipe->wizardParams.insert("Position y", position.y());
    pipe->wizardParams.insert("Position z", position.z());
    pipe->wizardParams.insert("Angle x", angle_x);
    pipe->wizardParams.insert("Angle y", angle_y);
    pipe->wizardParams.insert("Angle z", angle_z);
    pipe->wizardParams.insert("l", l);
    pipe->wizardParams.insert("d", d + 2*iso);
    pipe->wizardParams.insert("s",  s+iso);
    pipe->layer = this->layer;
    pipe->processWizardInput();
    pipe->calculate();

    QVector3D position_branch = position + matrix_rotation * QVector3D(l2, 0.0, 0.0);
    QVector3D angles_branch = MAngleCalculations().anglesFromVector(matrix_rotation * QVector3D(cos(alpha / 180 * PI), 0.0, sin(alpha / 180 * PI)));
    branch->wizardParams.insert("Position x", position_branch.x());
    branch->wizardParams.insert("Position y", position_branch.y());
    branch->wizardParams.insert("Position z", position_branch.z());
    branch->wizardParams.insert("Angle x", angles_branch.x());
    branch->wizardParams.insert("Angle y", angles_branch.y());
    branch->wizardParams.insert("Angle z", angles_branch.z());
    branch->wizardParams.insert("l", l3);
    branch->wizardParams.insert("d", d3 + 2*iso3);
    branch->wizardParams.insert("s",  s+iso3);
    branch->layer = this->layer;
    branch->processWizardInput();
    branch->calculate();

    this->boundingBox = pipe->boundingBox;
    this->boundingBox.enterVertices(branch->boundingBox.getVertices());
    this->snap_flanges.append(position);
    this->snap_flanges.append(position + matrix_rotation * QVector3D(l, 0.0, 0.0));
    this->snap_flanges.append(position + matrix_rotation * QVector3D(l2 + cos(alpha / 180 * PI) * l3, 0.0, sin(alpha / 180 * PI) * l3));
}

void CAD_Gas_PipeTeeConnector::processWizardInput()
{
    position.setX(wizardParams.value("Position x").toDouble());
    position.setY(wizardParams.value("Position y").toDouble());
    position.setZ(wizardParams.value("Position z").toDouble());
    angle_x = wizardParams.value("Angle x").toDouble();
    angle_y = wizardParams.value("Angle y").toDouble();
    angle_z = wizardParams.value("Angle z").toDouble();

    l = wizardParams.value("l").toDouble();
    l2 = wizardParams.value("l2").toDouble();
    l3 = wizardParams.value("l3").toDouble();
    d = wizardParams.value("d").toDouble();
    d3 = wizardParams.value("d3").toDouble();
    iso = wizardParams.value("iso").toDouble();
    iso3 = wizardParams.value("iso3").toDouble();
    alpha = wizardParams.value("alpha").toDouble();
    s = wizardParams.value("s").toDouble();
}

QMatrix4x4 CAD_Gas_PipeTeeConnector::rotationOfFlange(quint8 num)
{
    if(num == 1)
    {
        QMatrix4x4 m;
        m.setToIdentity();
        m.rotate(180.0, 0.0, 0.0, 1.0);
        return matrix_rotation * m;
    }
    else if(num == 2)
    {
        return matrix_rotation;
    }
    else if(num == 3)
    {
        QMatrix4x4 m;
        m.setToIdentity();
        m.rotate(-alpha, 0.0, 1.0, 0.0);
        return matrix_rotation * m;
    }
    else
        return matrix_rotation;
}

//void CAD_Gas_PipeTeeConnector::paint(GLWidget *glwidget)
//{
//    QColor color_pen_tmp = getColorPen();
//    QColor color_brush_tmp = getColorBrush();

//    arrayBufVertices->bind();
//    glwidget->shaderProgram->enableAttributeArray(glwidget->shader_vertexLocation);
//    glwidget->shaderProgram->setAttributeBuffer(0, GL_FLOAT, 0, 3, sizeof(QVector3D));

//    if (glwidget->render_solid)
//    {
//        glwidget->setPaintingColor(color_brush_tmp);

//        indexBufFaces->bind();
//        glwidget->glDrawElements(GL_TRIANGLE_STRIP, indexBufFaces->size(), GL_UNSIGNED_SHORT, 0);

//        indexBufFaces->release();
//    }

//    if (glwidget->render_outline)
//    {
//        glwidget->setPaintingColor(color_pen_tmp);
                                      
//        indexBufLines->bind();
//        glwidget->glDrawElements(GL_LINES, indexBufLines->size(), GL_UNSIGNED_SHORT, 0);
//        indexBufLines->release();
//     }                          
                                                                                           
//     arrayBufVertices->release();
//}
