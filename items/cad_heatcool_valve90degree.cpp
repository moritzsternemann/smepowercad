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

#include "cad_heatcool_valve90degree.h"
#include "glwidget.h"

CAD_HeatCool_Valve90Degree::CAD_HeatCool_Valve90Degree() : CADitem(CADitemTypes::HeatCool_Valve90Degree)
{
    pipe_lower = new CAD_basic_pipe;
    flange_lower = new CAD_basic_pipe;
    pipe_right = new CAD_basic_pipe;
    flange_right = new CAD_basic_pipe;
    endcap = new CAD_basic_pipe;
    this->subItems.append(pipe_lower);
    this->subItems.append(flange_lower);
    this->subItems.append(pipe_right);
    this->subItems.append(flange_right);
    this->subItems.append(endcap);
    wizardParams.insert("Position x", 0.0);
    wizardParams.insert("Position y", 0.0);
    wizardParams.insert("Position z", 0.0);
    wizardParams.insert("Angle x", 0.0);
    wizardParams.insert("Angle y", 0.0);
    wizardParams.insert("Angle z", 0.0);

    wizardParams.insert("d", 150.0);
    wizardParams.insert("a1", 250.0);
    wizardParams.insert("a2", 100.0);
    wizardParams.insert("fe", 10.0);
    wizardParams.insert("ff", 10.0);
    wizardParams.insert("l", 100.0);
    wizardParams.insert("s", 10.0);

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

CAD_HeatCool_Valve90Degree::~CAD_HeatCool_Valve90Degree()
{
//    arrayBufVertices->destroy();
//    indexBufFaces->destroy();
//    indexBufLines->destroy();
//    delete arrayBufVertices;
//    delete indexBufFaces;
//    delete indexBufLines;
}

QList<CADitemTypes::ItemType> CAD_HeatCool_Valve90Degree::flangable_items(int flangeIndex)
{
    Q_UNUSED(flangeIndex);
    if(flangeIndex == 3)
    {
        QList<CADitemTypes::ItemType> flangable_items;
        flangable_items.append(CADitemTypes::HeatCool_ValveHandwheel);
        flangable_items.append(CADitemTypes::HeatCool_ValveHandwheelGear);
        flangable_items.append(CADitemTypes::HeatCool_ValveLever);
        flangable_items.append(CADitemTypes::HeatCool_ValveMotorRect);
        flangable_items.append(CADitemTypes::HeatCool_ValveMotorRound);
        return flangable_items;
    }
    else
    {
        QList<CADitemTypes::ItemType> flangable_items;
        flangable_items.append(CADitemTypes::HeatCool_Adjustvalve);
        flangable_items.append(CADitemTypes::HeatCool_BallValve);
        flangable_items.append(CADitemTypes::HeatCool_Boiler);
        flangable_items.append(CADitemTypes::HeatCool_ButterflyValveBolted);
        flangable_items.append(CADitemTypes::HeatCool_ButterflyValveClamped);
        flangable_items.append(CADitemTypes::HeatCool_Chiller);
        flangable_items.append(CADitemTypes::HeatCool_Controlvalve);
        flangable_items.append(CADitemTypes::HeatCool_CoolingTower);
        flangable_items.append(CADitemTypes::HeatCool_DirtArrester);
        flangable_items.append(CADitemTypes::HeatCool_ExpansionChamber);
        flangable_items.append(CADitemTypes::HeatCool_Filter);
        flangable_items.append(CADitemTypes::HeatCool_Flange);
        flangable_items.append(CADitemTypes::HeatCool_Flowmeter);
        flangable_items.append(CADitemTypes::HeatCool_Gauge);
        flangable_items.append(CADitemTypes::HeatCool_Gauge90Degree);
        flangable_items.append(CADitemTypes::HeatCool_HeatexchangerSoldered);
        flangable_items.append(CADitemTypes::HeatCool_HeatexchangerBolted);
        flangable_items.append(CADitemTypes::HeatCool_NonReturnFlap);
        flangable_items.append(CADitemTypes::HeatCool_NonReturnValve);
        flangable_items.append(CADitemTypes::HeatCool_Pipe);
        flangable_items.append(CADitemTypes::HeatCool_PipeEndCap);
        flangable_items.append(CADitemTypes::HeatCool_PipeReducer);
        flangable_items.append(CADitemTypes::HeatCool_PipeTeeConnector);
        flangable_items.append(CADitemTypes::HeatCool_PipeTurn);
        flangable_items.append(CADitemTypes::HeatCool_PumpInline);
        flangable_items.append(CADitemTypes::HeatCool_PumpNorm);
        flangable_items.append(CADitemTypes::HeatCool_Radiator);
        flangable_items.append(CADitemTypes::HeatCool_RadiatorCompact);
        flangable_items.append(CADitemTypes::HeatCool_RadiatorFlange);
        flangable_items.append(CADitemTypes::HeatCool_RadiatorFlangeBent);
        flangable_items.append(CADitemTypes::HeatCool_RadiatorValve);
        flangable_items.append(CADitemTypes::HeatCool_SafetyValve);
        flangable_items.append(CADitemTypes::HeatCool_Sensor);
        flangable_items.append(CADitemTypes::HeatCool_StorageBoiler);
        flangable_items.append(CADitemTypes::HeatCool_Valve);
        flangable_items.append(CADitemTypes::HeatCool_Valve90Degree);
        flangable_items.append(CADitemTypes::HeatCool_WaterHeater);
        return flangable_items;
    }
}

QImage CAD_HeatCool_Valve90Degree::wizardImage()
{
    QImage image;
    QFileInfo fileinfo(__FILE__);
    QString imageFileName = fileinfo.baseName();
    imageFileName.prepend(":/itemGraphic/");
    imageFileName.append(".png");
    image.load(imageFileName, "PNG");

    return image;
}

QString CAD_HeatCool_Valve90Degree::iconPath()
{
    return ":/icons/cad_heatcool/cad_heatcool_valve90degree.svg";
}

QString CAD_HeatCool_Valve90Degree::domain()
{
    return "HeatCool";
}

QString CAD_HeatCool_Valve90Degree::description()
{
    return "HeatCool|Valve 90 Degree";
}

void CAD_HeatCool_Valve90Degree::calculate()
{                
    boundingBox.reset();

    this->snap_flanges.clear();
    this->snap_center.clear();
    this->snap_vertices.clear();

    this->snap_basepoint = (position);

    QVector3D position_lower = position + matrix_rotation * QVector3D(l, 0.0, -a2);
    pipe_lower->wizardParams.insert("Position x", position_lower.x());
    pipe_lower->wizardParams.insert("Position y", position_lower.y());
    pipe_lower->wizardParams.insert("Position z", position_lower.z());
    pipe_lower->wizardParams.insert("Angle x", angle_x);
    pipe_lower->wizardParams.insert("Angle y", angle_y);
    pipe_lower->wizardParams.insert("Angle z", angle_z);
    pipe_lower->wizardParams.insert("l", a2);
    pipe_lower->wizardParams.insert("d", d);
    pipe_lower->wizardParams.insert("s",  s);
    pipe_lower->layer = this->layer;
    pipe_lower->processWizardInput();
    pipe_lower->rotateAroundAxis(-90.0, QVector3D(0.0, 1.0, 0.0), angle_x, angle_y, angle_z);
    pipe_lower->calculate();

    flange_lower->wizardParams.insert("Position x", position_lower.x());
    flange_lower->wizardParams.insert("Position y", position_lower.y());
    flange_lower->wizardParams.insert("Position z", position_lower.z());
    flange_lower->wizardParams.insert("Angle x", angle_x);
    flange_lower->wizardParams.insert("Angle y", angle_y);
    flange_lower->wizardParams.insert("Angle z", angle_z);
    flange_lower->wizardParams.insert("l", fe);
    flange_lower->wizardParams.insert("d", d + 2*ff);
    flange_lower->wizardParams.insert("s",  ff);
    flange_lower->layer = this->layer;
    flange_lower->processWizardInput();
    flange_lower->rotateAroundAxis(-90.0, QVector3D(0.0, 1.0, 0.0), angle_x, angle_y, angle_z);
    flange_lower->calculate();

    pipe_right->wizardParams.insert("Position x", position.x());
    pipe_right->wizardParams.insert("Position y", position.y());
    pipe_right->wizardParams.insert("Position z", position.z());
    pipe_right->wizardParams.insert("Angle x", angle_x);
    pipe_right->wizardParams.insert("Angle y", angle_y);
    pipe_right->wizardParams.insert("Angle z", angle_z);
    pipe_right->wizardParams.insert("l", l);
    pipe_right->wizardParams.insert("d", d);
    pipe_right->wizardParams.insert("s",  s);
    pipe_right->layer = this->layer;
    pipe_right->processWizardInput();
    pipe_right->calculate();

    flange_right->wizardParams.insert("Position x", position.x());
    flange_right->wizardParams.insert("Position y", position.y());
    flange_right->wizardParams.insert("Position z", position.z());
    flange_right->wizardParams.insert("Angle x", angle_x);
    flange_right->wizardParams.insert("Angle y", angle_y);
    flange_right->wizardParams.insert("Angle z", angle_z);
    flange_right->wizardParams.insert("l", fe);
    flange_right->wizardParams.insert("d", d + 2*ff);
    flange_right->wizardParams.insert("s",  ff);
    flange_right->layer = this->layer;
    flange_right->processWizardInput();
    flange_right->calculate();

    QVector3D position_upper = position + matrix_rotation * QVector3D(l, 0.0, a1);
    endcap->wizardParams.insert("Position x", position_upper.x());
    endcap->wizardParams.insert("Position y", position_upper.y());
    endcap->wizardParams.insert("Position z", position_upper.z());
    endcap->wizardParams.insert("Angle x", angle_x);
    endcap->wizardParams.insert("Angle y", angle_y);
    endcap->wizardParams.insert("Angle z", angle_z);
    endcap->wizardParams.insert("l", a1);
    endcap->wizardParams.insert("d", d);
    endcap->wizardParams.insert("s",  d/2);
    endcap->layer = this->layer;
    endcap->processWizardInput();
    endcap->rotateAroundAxis(90.0, QVector3D(0.0, 1.0, 0.0), angle_x, angle_y, angle_z);
    endcap->calculate();

    foreach(CADitem *item, subItems)
    {
        this->boundingBox.enterVertices(item->boundingBox.getVertices());
    }
    this->snap_flanges.append(position);
    this->snap_flanges.append(position_lower);
    this->snap_flanges.append(position_upper);


}

void CAD_HeatCool_Valve90Degree::processWizardInput()
{
    position.setX(wizardParams.value("Position x").toDouble());
    position.setY(wizardParams.value("Position y").toDouble());
    position.setZ(wizardParams.value("Position z").toDouble());
    angle_x = wizardParams.value("Angle x").toDouble();
    angle_y = wizardParams.value("Angle y").toDouble();
    angle_z = wizardParams.value("Angle z").toDouble();

    a1 = wizardParams.value("a1").toDouble();
    a2 = wizardParams.value("a2").toDouble();
    d = wizardParams.value("d").toDouble();
    fe = wizardParams.value("fe").toDouble();
    ff = wizardParams.value("ff").toDouble();
    l = wizardParams.value("l").toDouble();
    s = wizardParams.value("s").toDouble();

    matrix_rotation.setToIdentity();
    matrix_rotation.rotate(angle_x, 1.0, 0.0, 0.0);
    matrix_rotation.rotate(angle_y, 0.0, 1.0, 0.0);
    matrix_rotation.rotate(angle_z, 0.0, 0.0, 1.0);
}

//void CAD_HeatCool_Valve90Degree::paint(GLWidget *glwidget)
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
//        glwidget->glLineWidth(1.0);

//        indexBufLines->bind();
//        glwidget->glDrawElements(GL_LINES, indexBufLines->size(), GL_UNSIGNED_SHORT, 0);
//        indexBufLines->release();
//     }                          

//     arrayBufVertices->release();
//}

QMatrix4x4 CAD_HeatCool_Valve90Degree::rotationOfFlange(quint8 num)
{
    if(num == 1)
    {
        QMatrix4x4 m;
        m.setToIdentity();
        m.rotate(-180.0, 0.0, 1.0, 0.0);
        return matrix_rotation * m;
    }
    else if(num == 2)
    {
        QMatrix4x4 m;
        m.setToIdentity();
        m.rotate(90.0, 0.0, 1.0, 0.0);
        return matrix_rotation * m;
    }
    else if(num == 3)
    {
        return matrix_rotation;
    }
    else
        return matrix_rotation;
}
