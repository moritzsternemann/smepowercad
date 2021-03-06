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

#include "mtriangle.h"


MTriangle::MTriangle()
{
    this->v0 = QVector3D();
    this->v1 = QVector3D();
    this->v2 = QVector3D();
}

MTriangle::MTriangle(const MTriangle &triangle)
{
    this->v0 = triangle.v0;
    this->v1 = triangle.v1;
    this->v2 = triangle.v2;
}

MTriangle::MTriangle(QVector3D v0, QVector3D v1, QVector3D v2)
{
    this->v0 = v0;
    this->v1 = v1;
    this->v2 = v2;
}

MTriangle::~MTriangle()
{

}

QVector3D MTriangle::getV0()
{
    return this->v0;
}

QVector3D MTriangle::getV1()
{
    return this->v1;
}

QVector3D MTriangle::getV2()
{
    return this->v2;
}

bool MTriangle::operator ==(const MTriangle &t)
{
    return ((v0 == t.v0)
            && (v1 == t.v1)
            && (v2 == t.v2));
}
