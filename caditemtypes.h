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

#ifndef CADITEMTYPES_H
#define CADITEMTYPES_H

#include <QObject>
#include <QMetaEnum>

class CADitemTypes : public QObject
{
    Q_OBJECT
    Q_ENUMS(ItemType)

public:
    explicit CADitemTypes(QObject *parent = 0);

    enum ItemType
    {
        None,
        Basic_Point,                            // Basisgeometrie: Punkt
        Basic_Line,                             // Basisgeometrie: Linie
        Basic_Polyline,                         // Basisgeometrie: Polylinie
        Basic_Circle,                           // Basisgeometrie: Kreis
        Basic_Arc,                              // Basisgeometrie: Bogen
        Basic_Face,                             // Basisgeometrie: Fläche
        Basic_Plane,                            // Basisgeometrie: Ebene
        Basic_Box,                              // Basisgeometrie: Box
        Basic_Cylinder,                         // Basisgeometrie: Zylinder
        Basic_Pipe,                             // Basisgeometrie: Rohr
        Basic_Turn,                             // Basisgeometrie: Rohrbogen
        Basic_Sphere,                           // Basisgeometrie: Kugel
        Basic_Duct,                             // Basisgeometrie: Kanal
        Arch_Foundation,                        // Fundament
        Arch_BoredPile,                         // Bohrpfahl
        Arch_LevelSlab,                         // Decke
        Arch_Wall_loadBearing,                  // Tragende Wand
        Arch_Wall_nonLoadBearing,               // Nicht tragende Wand
        Arch_Grating,                           // Gitterrost
        Arch_BlockOut,
        Arch_Support,                           // Stütze
        Arch_Beam,                              // Unterzug
        Arch_Door,
        Arch_Window,
        Air_Duct,                               // Kanal (eckig)
        Air_Pipe,                               // Rohr (rund)
        Air_DuctFireResistant,                  // Kanal (feuerbeständig)
        Air_DuctTurn,                           // Kanalbogen
        Air_PipeTurn,                           // Rohrbogen
        Air_PipeReducer,                        // Rohrreduzierung
        Air_PipeTeeConnector,                   // Rohr-T-Stück, auch mit mehr als 3 Anschlüssen
        Air_DuctTeeConnector,                   // Kanal-T-Stück
        Air_DuctTransition,                     // Kanalübergang (eckig)
        Air_DuctTransitionRectRound,            // Kanalübergang eckig/rund
        Air_DuctYpiece,                         // Kanal-Hosenstück
        Air_DuctEndPlate,                       // Kanalenddeckel (Boden)
        Air_PipeEndCap,                         // Rohr-Enddeckel
        Air_ThrottleValve,                      // Drossel-/ Absperrklappe (rund)
        Air_MultiLeafDamper,                    // Jalousieklappe (eckig)
        Air_PressureReliefDamper,               // Druckentlastungsklappe
        Air_PipeFireDamper,                     // Brandschutzklappe (rund)
        Air_DuctFireDamper,                     // Brandschutzklappe (eckig)
        Air_DuctVolumetricFlowController,       // Kanal-Volumenstromregler
        Air_PipeVolumetricFlowController,       // Rohr-Volumenstromregler
        Air_HeatExchangerWaterAir,              // Wärmetauscher Wasser/Luft
        Air_HeatExchangerAirAir,                // Wärmetauscher Luft/Luft
        Air_CanvasFlange,                       // Segeltuchstutzen
        Air_Filter,                             // Luftfilter
        Air_PipeSilencer,                       // Rohr-Schalldämpfer
        Air_PipeBranch,                         // Rohr-Abzweig
        Air_DuctBaffleSilencer,                 // Kanal-Kulissenschalldämpfer
        Air_Fan,                                // Ventilator
        Air_Humidifier,                         // Befeuchter
        Air_EmptyCabinet,                       // Leergerät
        Air_EquipmentFrame,                     // Geräterahmen
        Air_LinearDiffuser,                     // Linearauslass
        Cleanroom_CeilingCornerPiece,
        Cleanroom_CeilingFilterFanUnit,
        Cleanroom_CeilingFrameFeedThrough,
        Cleanroom_CeilingFrame,
        Cleanroom_CeilingGrating,
        Cleanroom_CeilingJoiningKnot,
        Cleanroom_CeilingMaintenanceFlap,
        Cleanroom_CeilingMountingRails,
        Cleanroom_CeilingPanel,
        Cleanroom_CeilingSmokeExtractFlap,
        Cleanroom_CeilingSuspension,
        Cleanroom_CeilingTeeJoiningPiece,
        Cleanroom_CeilingVerticalLadder,
        Cleanroom_ControlEmergencySwitch,
        Cleanroom_ControlLedTouchKey,
        Cleanroom_ControlRadarSensor,
        Cleanroom_ControlSwitch,
        Cleanroom_DoorFrame,
        Cleanroom_DoorSlidingDouble,
        Cleanroom_DoorSlidingSingle,
        Cleanroom_DoorSwingingDouble,
        Cleanroom_DoorSwingingSingle,
        Cleanroom_FloorStiffenerDiagonal,
        Cleanroom_FloorStiffenerHorizontal,
        Cleanroom_FloorGrating,
        Cleanroom_FloorPanel,
        Cleanroom_FloorPanelWithBushing,
        Cleanroom_FloorPanelWithTank,
        Cleanroom_FloorPanelPerforated,
        Cleanroom_FloorSupport,
        Cleanroom_TagLeakageDetector,
        Cleanroom_TagSmokeDetector,
        Cleanroom_VacuumCleanerSocket,
        Cleanroom_WallStiffenerDiagonal,
        Cleanroom_WallMountingProfile,
        Cleanroom_WallOverflowGrate,
        Cleanroom_WallPanel,
        Cleanroom_WallPost,
        Cleanroom_WallSmokeExtractFlap,
        HeatCool_Pipe,                          // Rohr
        HeatCool_PipeTurn,                      // Rohrbogen
        HeatCool_PipeReducer,                   // Reduzierung
        HeatCool_PipeTeeConnector,              // T-Stück
        HeatCool_PipeEndCap,                    // Endkappe / Klöpperboden
        HeatCool_Flange,                        // Flansch
        HeatCool_Chiller,                       // Kältemaschine
        HeatCool_CoolingTower,                  // Kühlturm
        HeatCool_ExpansionChamber,              // Ausdehnungsgefäß
        HeatCool_Boiler,                        // Heizkessel
        HeatCool_WaterHeater,                   // Warmwasserboiler
        HeatCool_StorageBoiler,                 // Speicherkessel / Schichtspeicher
        HeatCool_HeatExchanger,                 // Wärmetauscher
        HeatCool_Radiator,                      // Heizkörper
        HeatCool_Pump,                          // Pumpe
        HeatCool_Filter,                        // Filter
        HeatCool_Controlvalve,                  // Regelventil
        HeatCool_Adjustvalve,                   // Regulierventil
        HeatCool_BallValve,                     // Kugelhahn
        HeatCool_ButterflyValve,                // Absperrklappe
        HeatCool_SafetyValve,                   // Sicherheitsventil
        HeatCool_Flowmeter,                     // Durchflussmesser
        HeatCool_Sensor,                        // Sensor
        Sprinkler_Pipe,                         // Sprinklerrohr
        Sprinkler_PipeTurn,                     // Rohrbogen
        Sprinkler_PipeReducer,                  // Reduzierung
        Sprinkler_PipeEndCap,                   // Rohr-Endkappe
        Sprinkler_Head,                         // Sprinklerkopf
        Sprinkler_Pump,                         // Sprinklerpumpe
        Sprinkler_Valve,                        // Ventil
        Sprinkler_Distribution,                 // Verteiler
        Sprinkler_TeeConnector,                 // T-Stück
        Sprinkler_ZoneCheck,                    // Zone-Check
        Sprinkler_WetAlarmValve,                // Nassalarmventil
        Sprinkler_CompressedAirWaterContainer,  // Druckluftwasserbehälter
        Sanitary_Pipe,                          // Rohr (allgemein)
        Sanitary_PipeTurn,                      // Rohrbogen
        Sanitary_PipeReducer,                   // Reduzierung
        Sanitary_PipeTeeConnector,              // T-Stück
        Sanitary_PipeEndCap,                    // Endkappe
        Sanitary_Flange,                        // Flansch
        Sanitary_ElectricWaterHeater,           // Elektrischer Wasserboiler
        Sanitary_WashBasin,                     // Waschbecken
        Sanitary_Sink,                          // Ausgussbecken
        Sanitary_Shower,                        // Dusche
        Sanitary_EmergencyShower,               // Notdusche
        Sanitary_EmergencyEyeShower,            // Augendusche
        Sanitary_LiftingUnit,                   // Hebeanlage
        Electrical_BusbarWithoutTapoffPoints,   // Stromschiene
        Electrical_BusbarWithTapoffPoints1Row,  //
        Electrical_BusbarWithTapoffPoints2Row,  //
        Electrical_Cabletray,                   // Kabeltrasse
        Electrical_CabletrayReducer,            // Kabeltrasse Übergang
        Electrical_CabletrayTeeConnector,       // Kabeltrasse T-Stück
        Electrical_CabletrayTransition,         // Kabeltrasse Übergang (in z-Richtung)
        Electrical_Cabinet,                     // Schaltschrank
        LastItem
    };


    QString getEnumNameOfItemType(CADitemTypes::ItemType type);
    int countOfItemTypes();

signals:

public slots:

};

#endif // CADITEMTYPES_H
