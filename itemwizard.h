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

#ifndef ITEMWIZARD_H
#define ITEMWIZARD_H

#include <QComboBox>
#include <QDockWidget>
#include <QDoubleSpinBox>
#include <QEvent>
#include <QKeyEvent>
#include <QLineEdit>
#include <QMap>
#include <QSpinBox>
#include <QWidget>

#include "caditem.h"
#include "itemdb.h"
#include "itemparameterswidget.h"
#include "calculatinglineedit.h"
#include "stylesheetprovider.h"

namespace Ui {
class ItemWizard;
}

class ItemWizard : public QDockWidget
{
    Q_OBJECT

public:
    explicit ItemWizard(QWidget *parent = 0);
    ~ItemWizard();

    void showWizard(CADitem *item, ItemDB *itemDB);
    static QImage wizardImage(CADitem *item);

private slots:
    void slot_rejected();
    void slot_accepted();

    void on_pushButton_ok_clicked();

    void on_pushButton_apply_clicked();

    void on_pushButton_cancel_clicked();

public slots:
    void slot_itemDeleted(CADitem* item);

private:
    Ui::ItemWizard *ui;
    ItemParametersWidget *m_itemParametersWidget;

    CADitem *m_currentItem;
    ItemDB* itemDB;
    QWidget* widgetLastFocus;   // The widget that had the focus before ItemWizard got focus
    void save();
    void clear();
    void giveFocusBack();

protected:
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

signals:
    void signal_sceneRepaintNeeded();
};

#endif // ITEMWIZARD_H
