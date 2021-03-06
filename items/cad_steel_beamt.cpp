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

#include "cad_steel_beamt.h"
#include "glwidget.h"

CAD_Steel_BeamT::CAD_Steel_BeamT() : CADitem(CADitemTypes::Steel_BeamT)
{
    wizardParams.insert("Position x", 0.0);
    wizardParams.insert("Position y", 0.0);
    wizardParams.insert("Position z", 0.0);
    wizardParams.insert("Angle x", 0.0);
    wizardParams.insert("Angle y", 0.0);
    wizardParams.insert("Angle z", 0.0);

    wizardParams.insert("a",  96.0);
    wizardParams.insert("b", 100.0);
    wizardParams.insert("l", 500.0);
    wizardParams.insert("g",   8.0);
    wizardParams.insert("s",   5.0);

    box_flangeUpper = new CAD_basic_box();
    box_web = new CAD_basic_box();
    this->subItems.append(box_flangeUpper);
    this->subItems.append(box_web);

//    arrayBufVertices = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
//    arrayBufVertices->create();
//    arrayBufVertices->setUsagePattern(QOpenGLBuffer::StaticDraw);

//    indexBufFaces = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
//    indexBufFaces->create();
//    indexBufFaces->setUsagePattern(QOpenGLBuffer::StaticDraw);

//    indexBufLines = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
//    indexBufLines->create();
//    indexBufLines->setUsagePattern(QOpenGLBuffer::StaticDraw);
   
    processWizardInput();
    calculate();
}

CAD_Steel_BeamT::~CAD_Steel_BeamT()
{
//    arrayBufVertices->destroy();
//    indexBufFaces->destroy();
//    indexBufLines->destroy();
//    delete arrayBufVertices;
//    delete indexBufFaces;
//    delete indexBufLines;
}

QList<CADitemTypes::ItemType> CAD_Steel_BeamT::flangable_items(int flangeIndex)
{
    Q_UNUSED(flangeIndex);
    QList<CADitemTypes::ItemType> flangable_items;
    flangable_items.append(CADitemTypes::Steel_BeamI);
    flangable_items.append(CADitemTypes::Steel_BeamL);
    flangable_items.append(CADitemTypes::Steel_BeamT);
    flangable_items.append(CADitemTypes::Steel_BeamU);
    flangable_items.append(CADitemTypes::Steel_BeamZ);

    return flangable_items;
}

QImage CAD_Steel_BeamT::wizardImage()
{
    QImage image;
    QFileInfo fileinfo(__FILE__);
    QString imageFileName = fileinfo.baseName();
    imageFileName.prepend(":/itemGraphic/");
    imageFileName.append(".png");
    image.load(imageFileName, "PNG");
                       
    return image;
}

QString CAD_Steel_BeamT::iconPath()
{
    return ":/icons/cad_steel/cad_steel_beamt.svg";
}

QString CAD_Steel_BeamT::domain()
{
    return "Steel";
}

QString CAD_Steel_BeamT::description()
{
    return "Steel|Beam T";
}

void CAD_Steel_BeamT::calculate()
{                
    boundingBox.reset();
                    
    this->snap_flanges.clear();
    this->snap_center.clear();
    this->snap_vertices.clear();
                                
    this->snap_basepoint = (position);

    QVector3D position_box_flangeUpper = (matrix_rotation * QVector3D(l/2.0, 0.0, a - g/2.0)) + position;
    box_flangeUpper->wizardParams.insert("Position x", position_box_flangeUpper.x());
    box_flangeUpper->wizardParams.insert("Position y", position_box_flangeUpper.y());
    box_flangeUpper->wizardParams.insert("Position z", position_box_flangeUpper.z());
    box_flangeUpper->wizardParams.insert("Angle x", angle_x);
    box_flangeUpper->wizardParams.insert("Angle y", angle_y);
    box_flangeUpper->wizardParams.insert("Angle z", angle_z);
    box_flangeUpper->wizardParams.insert("l", l);
    box_flangeUpper->wizardParams.insert("b", b);
    box_flangeUpper->wizardParams.insert("a", g);
    box_flangeUpper->layer = this->layer;
    box_flangeUpper->processWizardInput();
    box_flangeUpper->calculate();

    QVector3D position_box_web = (matrix_rotation * QVector3D(l/2.0, 0.0, (a - g)/2.0)) + position;
    box_web->wizardParams.insert("Position x", position_box_web.x());
    box_web->wizardParams.insert("Position y", position_box_web.y());
    box_web->wizardParams.insert("Position z", position_box_web.z());
    box_web->wizardParams.insert("Angle x", angle_x);
    box_web->wizardParams.insert("Angle y", angle_y);
    box_web->wizardParams.insert("Angle z", angle_z);
    box_web->wizardParams.insert("l", l);
    box_web->wizardParams.insert("b", s);
    box_web->wizardParams.insert("a", a - g);
    box_web->layer = this->layer;
    box_web->processWizardInput();
    box_web->calculate();

    this->boundingBox.enterVertices(box_flangeUpper->boundingBox.getVertices());
    this->boundingBox.enterVertices(box_web->boundingBox.getVertices());
    this->snap_vertices.append(box_flangeUpper->snap_vertices);
    this->snap_vertices.append(box_web->snap_vertices);
//    this->snap_center.append();
    this->snap_flanges.append(position);
    this->snap_flanges.append((matrix_rotation * QVector3D(0.0, 0.0, a))   + position);
    this->snap_flanges.append((matrix_rotation * QVector3D(l,   0.0, 0.0)) + position);
    this->snap_flanges.append((matrix_rotation * QVector3D(l,   0.0, a))   + position);
}

void CAD_Steel_BeamT::processWizardInput()
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
    g = wizardParams.value("g").toDouble();
    s = wizardParams.value("s").toDouble();

    matrix_rotation.setToIdentity();
    matrix_rotation.rotate(angle_x, 1.0, 0.0, 0.0);
    matrix_rotation.rotate(angle_y, 0.0, 1.0, 0.0);
    matrix_rotation.rotate(angle_z, 0.0, 0.0, 1.0);
}

QMatrix4x4 CAD_Steel_BeamT::rotationOfFlange(quint8 num)
{
    if(num <= 2)
    {
        QMatrix4x4 m;
        m.setToIdentity();
        m.rotate(180.0, 0.0, 0.0, 1.0);
        return matrix_rotation * m;
    }
    else
        return matrix_rotation;
}

//void CAD_Steel_BeamT::paint(GLWidget *glwidget)
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
