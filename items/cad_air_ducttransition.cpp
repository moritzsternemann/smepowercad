#include "cad_air_ducttransition.h"

CAD_air_ductTransition::CAD_air_ductTransition() : CADitem(CADitem::Air_DuctTransition)
{
    this->description = "Air|Duct transition rect/rect";
    wizardParams.insert(QObject::tr("Position x"), QVariant::fromValue(0.0));
    wizardParams.insert(QObject::tr("Position y"), QVariant::fromValue(0.0));
    wizardParams.insert(QObject::tr("Position z"), QVariant::fromValue(0.0));

    wizardParams.insert(QObject::tr("Length (l)"), QVariant::fromValue(20.0));
    wizardParams.insert(QObject::tr("Width 1 (b)"), QVariant::fromValue(10.0));
    wizardParams.insert(QObject::tr("Height 1 (a)"), QVariant::fromValue(10.0));
    wizardParams.insert(QObject::tr("Width 2 (d)"), QVariant::fromValue(5.0));
    wizardParams.insert(QObject::tr("Height 2 (c)"), QVariant::fromValue(5.0));

    wizardParams.insert(QObject::tr("Offset y (e)"), QVariant::fromValue(0.0));
    wizardParams.insert(QObject::tr("Offset z (f)"), QVariant::fromValue(0.0));

    wizardParams.insert(QObject::tr("Length endcap (u)"), QVariant::fromValue(5.0));

    wizardParams.insert(QObject::tr("Wall thickness"), QVariant::fromValue(1.0));
    wizardParams.insert(QObject::tr("Flange size"), QVariant::fromValue(1.0));


    wizardParams.insert(QObject::tr("Angle x"), QVariant::fromValue(0.0));
    wizardParams.insert(QObject::tr("Angle y"), QVariant::fromValue(0.0));
    wizardParams.insert(QObject::tr("Angle z"), QVariant::fromValue(0.0));

    transition_duct = new CAD_basic_duct();
    endcap_left_duct = new CAD_basic_duct();
    endcap_right_duct = new CAD_basic_duct();
    flange_left_duct = new CAD_basic_duct();
    flange_right_duct = new CAD_basic_duct();
    subItems.append(transition_duct);
    subItems.append(endcap_left_duct);
    subItems.append(endcap_right_duct);
    subItems.append(flange_left_duct);
    subItems.append(flange_right_duct);


}

CAD_air_ductTransition::~CAD_air_ductTransition()
{
}

QList<CADitem::ItemType> CAD_air_ductTransition::flangable_items()
{
    QList<CADitem::ItemType> flangable_items;
    flangable_items.append(CADitem::Air_Duct);
    flangable_items.append(CADitem::Air_DuctEndPlate);
    flangable_items.append(CADitem::Air_DuctFireDamper);
    flangable_items.append(CADitem::Air_DuctTeeConnector);
    flangable_items.append(CADitem::Air_DuctTransitionRectRound);
    flangable_items.append(CADitem::Air_DuctTurn);
    flangable_items.append(CADitem::Air_DuctVolumetricFlowController);
    flangable_items.append(CADitem::Air_DuctYpiece);
    flangable_items.append(CADitem::Air_Filter);
    flangable_items.append(CADitem::Air_HeatExchangerAirAir);
    flangable_items.append(CADitem::Air_HeatExchangerWaterAir);
    flangable_items.append(CADitem::Air_MultiLeafDamper);
    return flangable_items;
}

QImage CAD_air_ductTransition::wizardImage()
{
    QImage image;
    QFileInfo fileinfo(__FILE__);
    QString imageFileName = fileinfo.baseName();
    imageFileName.prepend(":/itemGraphic/");
    imageFileName.append(".png");

    qDebug() << imageFileName;

    image.load(imageFileName, "PNG");

    return image;
}

void CAD_air_ductTransition::calculate()
{
    boundingBox.reset();

    matrix_rotation.setToIdentity();
    matrix_rotation.rotate(angle_x, 1.0, 0.0, 0.0);
    matrix_rotation.rotate(angle_y, 0.0, 1.0, 0.0);
    matrix_rotation.rotate(angle_z, 0.0, 0.0, 1.0);

//    pos_bot_1 = QVector3D(-1.0, 0.0, 0.0) * l + QVector3D(0.0, -1.0, 0.0) * b + QVector3D(0.0, 0.0, -1.0) * a + position;
//    pos_bot_2 = QVector3D( 0.0, 0.0, 0.0) * l + QVector3D(0.0, -1.0, 0.0) * d + QVector3D(0.0, 0.5,  0.0) * e + QVector3D(0.0, 0.0, -1.0) * c + QVector3D(0.0, 0.0, 0.5) * f + position;
//    pos_bot_3 = QVector3D( 0.0, 0.0, 0.0) * l + QVector3D(0.0, -0.0, 0.0) * d + QVector3D(0.0, 0.5,  0.0) * e + QVector3D(0.0, 0.0, -1.0) * c  + QVector3D(0.0, 0.0, 0.5) * f + position;
//    pos_bot_4 = QVector3D(-1.0, 0.0, 0.0) * l + QVector3D(0.0, -0.0, 0.0) * b + QVector3D(0.0, 0.0, -1.0) * a + position;

//    pos_top_1 = QVector3D(-1.0, 0.0, 0.0) * l + QVector3D(0.0, -1.0, 0.0) * b + QVector3D(0.0, 0.0, -0.0) * a + position;
//    pos_top_2 = QVector3D( 0.0, 0.0, 0.0) * l + QVector3D(0.0, -1.0, 0.0) * d + QVector3D(0.0, 0.5,  0.0) * e + QVector3D(0.0, 0.0,  0.0) * c + QVector3D(0.0, 0.0, 0.5) * f + position;
//    pos_top_3 = QVector3D( 0.0, 0.0, 0.0) * l + QVector3D(0.0,  0.0, 0.0) * d + QVector3D(0.0, 0.5,  0.0) * e + QVector3D(0.0, 0.0,  0.0) * c + QVector3D(0.0, 0.0, 0.5) * f + position;
//    pos_top_4 = QVector3D(-1.0, 0.0, 0.0) * l + QVector3D(0.0,  0.0, 0.0) * b + QVector3D(0.0, 0.0,  0.0) * a + position;

    QVector3D position_led = position + matrix_rotation * QVector3D(0.0, 0.0, 0.0);
    QVector3D position_red = position + matrix_rotation * QVector3D(-l,(b - d) / 2 + e, (a - c) / 2 + f);
    QVector3D position_lfd = position + matrix_rotation * QVector3D(0, 0.0, 0.0);
    QVector3D position_rfd = position + matrix_rotation * QVector3D(flange_size - l - endcap, (b - d) / 2 + e, (a-c) / 2 + f);




    endcap_left_duct->wizardParams.insert(QObject::tr("Position x"), QVariant::fromValue(position_led.x()));
    endcap_left_duct->wizardParams.insert(QObject::tr("Position y"), QVariant::fromValue(position_led.y()));
    endcap_left_duct->wizardParams.insert(QObject::tr("Position z"), QVariant::fromValue(position_led.z()));
    endcap_left_duct->wizardParams.insert(QObject::tr("Angle x"), QVariant::fromValue(angle_x));
    endcap_left_duct->wizardParams.insert(QObject::tr("Angle y"), QVariant::fromValue(angle_y));
    endcap_left_duct->wizardParams.insert(QObject::tr("Angle z"), QVariant::fromValue(angle_z));
    endcap_left_duct->wizardParams.insert(QObject::tr("Length (l)"), QVariant::fromValue(endcap));
    endcap_left_duct->wizardParams.insert(QObject::tr("Width (b)"), QVariant::fromValue(b));
    endcap_left_duct->wizardParams.insert(QObject::tr("Height (a)"), QVariant::fromValue(a));
    endcap_left_duct->wizardParams.insert(QObject::tr("Wall thickness"), QVariant::fromValue(wall_thickness));
    endcap_left_duct->processWizardInput();
    endcap_left_duct->calculate();


    endcap_right_duct->wizardParams.insert(QObject::tr("Position x"), QVariant::fromValue(position_red.x()));//position.x()+l));
    endcap_right_duct->wizardParams.insert(QObject::tr("Position y"), QVariant::fromValue(position_red.y()));//position.y()+(b-d)/2+e));
    endcap_right_duct->wizardParams.insert(QObject::tr("Position z"), QVariant::fromValue(position_red.z()));//position.z()+(a-c)/2+f));
    endcap_right_duct->wizardParams.insert(QObject::tr("Angle x"), QVariant::fromValue(angle_x));
    endcap_right_duct->wizardParams.insert(QObject::tr("Angle y"), QVariant::fromValue(angle_y));
    endcap_right_duct->wizardParams.insert(QObject::tr("Angle z"), QVariant::fromValue(angle_z));
    endcap_right_duct->wizardParams.insert(QObject::tr("Length (l)"), QVariant::fromValue(endcap));
    endcap_right_duct->wizardParams.insert(QObject::tr("Width (b)"), QVariant::fromValue(d));
    endcap_right_duct->wizardParams.insert(QObject::tr("Height (a)"), QVariant::fromValue(c));
    endcap_right_duct->wizardParams.insert(QObject::tr("Wall thickness"), QVariant::fromValue(wall_thickness));
    endcap_right_duct->processWizardInput();
    endcap_right_duct->calculate();

    flange_left_duct->wizardParams.insert(QObject::tr("Position x"), QVariant::fromValue(position_lfd.x()));
    flange_left_duct->wizardParams.insert(QObject::tr("Position y"), QVariant::fromValue(position_lfd.y()));
    flange_left_duct->wizardParams.insert(QObject::tr("Position z"), QVariant::fromValue(position_lfd.z()));
    flange_left_duct->wizardParams.insert(QObject::tr("Angle x"), QVariant::fromValue(angle_x));
    flange_left_duct->wizardParams.insert(QObject::tr("Angle y"), QVariant::fromValue(angle_y));
    flange_left_duct->wizardParams.insert(QObject::tr("Angle z"), QVariant::fromValue(angle_z));
    flange_left_duct->wizardParams.insert(QObject::tr("Length (l)"), QVariant::fromValue(flange_size));
    flange_left_duct->wizardParams.insert(QObject::tr("Width (b)"), QVariant::fromValue(b+2*flange_size));
    flange_left_duct->wizardParams.insert(QObject::tr("Height (a)"), QVariant::fromValue(a+2*flange_size));
    flange_left_duct->wizardParams.insert(QObject::tr("Wall thickness"), QVariant::fromValue(flange_size));
    flange_left_duct->processWizardInput();
    flange_left_duct->calculate();

    flange_right_duct->wizardParams.insert(QObject::tr("Position x"), QVariant::fromValue(position_rfd.x()));//position.x()+l));
    flange_right_duct->wizardParams.insert(QObject::tr("Position y"), QVariant::fromValue(position_rfd.y()));//position.y()+(b-d)/2+e));
    flange_right_duct->wizardParams.insert(QObject::tr("Position z"), QVariant::fromValue(position_rfd.z()));//position.z()+(a-c)/2+f));
    flange_right_duct->wizardParams.insert(QObject::tr("Angle x"), QVariant::fromValue(angle_x));
    flange_right_duct->wizardParams.insert(QObject::tr("Angle y"), QVariant::fromValue(angle_y));
    flange_right_duct->wizardParams.insert(QObject::tr("Angle z"), QVariant::fromValue(angle_z));
    flange_right_duct->wizardParams.insert(QObject::tr("Length (l)"), QVariant::fromValue(flange_size));
    flange_right_duct->wizardParams.insert(QObject::tr("Width (b)"), QVariant::fromValue(d+2*flange_size));
    flange_right_duct->wizardParams.insert(QObject::tr("Height (a)"), QVariant::fromValue(c+2*flange_size));
    flange_right_duct->wizardParams.insert(QObject::tr("Wall thickness"), QVariant::fromValue(flange_size));
    flange_right_duct->processWizardInput();
    flange_right_duct->calculate();

    transition_duct->wizardParams.insert(QObject::tr("Position x"), QVariant::fromValue(position.x()+endcap));
    transition_duct->wizardParams.insert(QObject::tr("Position y"), QVariant::fromValue(position.y()));
    transition_duct->wizardParams.insert(QObject::tr("Position z"), QVariant::fromValue(position.z()));
    transition_duct->wizardParams.insert(QObject::tr("Angle x"), QVariant::fromValue(angle_x));
    transition_duct->wizardParams.insert(QObject::tr("Angle y"), QVariant::fromValue(angle_y));
    transition_duct->wizardParams.insert(QObject::tr("Angle z"), QVariant::fromValue(angle_z));
    transition_duct->wizardParams.insert(QObject::tr("Length (l)"), QVariant::fromValue(l -2*endcap));
    transition_duct->wizardParams.insert(QObject::tr("Width (b)"), QVariant::fromValue(b));
    transition_duct->wizardParams.insert(QObject::tr("Height (a)"), QVariant::fromValue(a));
    transition_duct->wizardParams.insert(QObject::tr("Wall thickness"), QVariant::fromValue(wall_thickness));
    transition_duct->processWizardInput();
    transition_duct->calculate();

    //set Outer Points
    transition_duct->pos_bot_1 = endcap_left_duct->pos_bot_1;
    transition_duct->pos_bot_2 = endcap_right_duct->pos_bot_2;
    transition_duct->pos_bot_3 = endcap_right_duct->pos_bot_3;
    transition_duct->pos_bot_4 = endcap_left_duct->pos_bot_4;

    transition_duct->pos_top_1 = endcap_left_duct->pos_top_1;
    transition_duct->pos_top_2 = endcap_right_duct->pos_top_2;
    transition_duct->pos_top_3 = endcap_right_duct->pos_top_3;
    transition_duct->pos_top_4 = endcap_left_duct->pos_top_4;

    //set inner Points
    transition_duct->inner_pos_bot_1 = endcap_left_duct->inner_pos_bot_1;
    transition_duct->inner_pos_bot_2 = endcap_right_duct->inner_pos_bot_2;
    transition_duct->inner_pos_bot_3 = endcap_right_duct->inner_pos_bot_3;
    transition_duct->inner_pos_bot_4 = endcap_left_duct->inner_pos_bot_4;

    transition_duct->inner_pos_top_1 = endcap_left_duct->inner_pos_top_1;
    transition_duct->inner_pos_top_2 = endcap_right_duct->inner_pos_top_2;
    transition_duct->inner_pos_top_3 = endcap_right_duct->inner_pos_top_3;
    transition_duct->inner_pos_top_4 = endcap_left_duct->inner_pos_top_4;

    boundingBox.enterVertex(endcap_left_duct->pos_bot_1);
    boundingBox.enterVertex(endcap_left_duct->pos_top_1);
    boundingBox.enterVertex(endcap_left_duct->pos_bot_2);
    boundingBox.enterVertex(endcap_left_duct->pos_top_2);
    boundingBox.enterVertex(endcap_left_duct->pos_bot_3);
    boundingBox.enterVertex(endcap_left_duct->pos_top_3);
    boundingBox.enterVertex(endcap_left_duct->pos_bot_4);
    boundingBox.enterVertex(endcap_left_duct->pos_top_4);


    boundingBox.enterVertex(endcap_right_duct->pos_bot_1);
    boundingBox.enterVertex(endcap_right_duct->pos_top_1);
    boundingBox.enterVertex(endcap_right_duct->pos_bot_2);
    boundingBox.enterVertex(endcap_right_duct->pos_top_2);
    boundingBox.enterVertex(endcap_right_duct->pos_bot_3);
    boundingBox.enterVertex(endcap_right_duct->pos_top_3);
    boundingBox.enterVertex(endcap_right_duct->pos_bot_4);
    boundingBox.enterVertex(endcap_right_duct->pos_top_4);





    this->snap_basepoint = position;

    this->snap_vertices.append(pos_bot_1);
    this->snap_vertices.append(pos_bot_2);
    this->snap_vertices.append(pos_bot_3);
    this->snap_vertices.append(pos_bot_4);
    this->snap_vertices.append(pos_top_1);
    this->snap_vertices.append(pos_top_2);
    this->snap_vertices.append(pos_top_3);
    this->snap_vertices.append(pos_top_4);

    this->snap_flanges.append((pos_top_3 + pos_bot_2) / 2.0);
    this->snap_flanges.append((pos_top_4 + pos_bot_1) / 2.0);

}

void CAD_air_ductTransition::processWizardInput()
{

    position.setX(wizardParams.value(QObject::tr("Position x")).toDouble());
    position.setY(wizardParams.value(QObject::tr("Position y")).toDouble());
    position.setZ(wizardParams.value(QObject::tr("Position z")).toDouble());

    l = wizardParams.value(QObject::tr("Length (l)")).toDouble();
    b = wizardParams.value(QObject::tr("Width 1 (b)")).toDouble();
    a = wizardParams.value(QObject::tr("Height 1 (a)")).toDouble();
    d = wizardParams.value(QObject::tr("Width 2 (d)")).toDouble();
    c = wizardParams.value(QObject::tr("Height 2 (c)")).toDouble();

    angle_x = wizardParams.value(QObject::tr("Angle x")).toDouble();
    angle_y = wizardParams.value(QObject::tr("Angle y")).toDouble();
    angle_z = wizardParams.value(QObject::tr("Angle z")).toDouble();

    wall_thickness = wizardParams.value(QObject::tr("Wall thickness")).toDouble();
    flange_size = wizardParams.value(QObject::tr("Flange size")).toDouble();
    qDebug() << flange_size;
    endcap = wizardParams.value(QObject::tr("Length endcap (u)")).toDouble();
    e = wizardParams.value(QObject::tr("Offset y (e)")).toDouble();
    f = wizardParams.value(QObject::tr("Offset z (f)")).toDouble();

    matrix_rotation.setToIdentity();
    matrix_rotation.rotate(angle_x, 1.0, 0.0, 0.0);
    matrix_rotation.rotate(angle_y, 0.0, 1.0, 0.0);
    matrix_rotation.rotate(angle_z, 0.0, 0.0, 1.0);
}
