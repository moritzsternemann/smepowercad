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

#ifndef CAD_AIR_DUCTFIRERESISTANT_H
#define CAD_AIR_DUCTFIRERESISTANT_H

#include "caditem.h"
#include "cad_air_duct.h"

class CAD_air_ductFireResistant : public CADitem
{
public:
    CAD_air_ductFireResistant();
    virtual ~CAD_air_ductFireResistant();
    virtual QList<CADitemTypes::ItemType> flangable_items();
    virtual QImage wizardImage();
    virtual QString iconPath();
    virtual QString domain();
    virtual QString description();
    virtual void calculate();
    virtual void processWizardInput();

    qreal a,b,l, fe, ff, s, iso;
    CAD_air_duct* duct;


};

#endif // CAD_AIR_DUCTFIRERESISTANT_H
