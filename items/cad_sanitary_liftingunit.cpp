#include "cad_sanitary_liftingunit.h"

CAD_sanitary_liftingUnit::CAD_sanitary_liftingUnit() : CADitem(CADitem::Sanitary_LiftingUnit)
{
    this->description = "Sanitary|Lifting Unit";

}

QList<CADitem::ItemType> CAD_sanitary_liftingUnit::flangable_items()
{
    QList<CADitem::ItemType> flangable_items;
    flangable_items.append(CADitem::Sanitary_ElectricWaterHeater);
    flangable_items.append(CADitem::Sanitary_EmergencyEyeShower);
    flangable_items.append(CADitem::Sanitary_EmergencyShower);
    flangable_items.append(CADitem::Sanitary_Flange);
    flangable_items.append(CADitem::Sanitary_LiftingUnit);
    flangable_items.append(CADitem::Sanitary_Pipe);
    flangable_items.append(CADitem::Sanitary_PipeEndCap);
    flangable_items.append(CADitem::Sanitary_PipeReducer);
    flangable_items.append(CADitem::Sanitary_PipeTeeConnector);
    flangable_items.append(CADitem::Sanitary_PipeTurn);
    flangable_items.append(CADitem::Sanitary_Shower);
    flangable_items.append(CADitem::Sanitary_Sink);
    flangable_items.append(CADitem::Sanitary_WashBasin);

    return flangable_items;
}

QImage CAD_sanitary_liftingUnit::wizardImage()
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

void CAD_sanitary_liftingUnit::calculate()
{

}

void CAD_sanitary_liftingUnit::processWizardInput()
{

}
