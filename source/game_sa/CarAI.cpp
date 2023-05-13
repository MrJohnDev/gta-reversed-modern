/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "CarAI.h"
#include "CarCtrl.h"

void CCarAI::InjectHooks() {
    RH_ScopedClass(CCarAI);
    RH_ScopedCategory("AI");

    RH_ScopedInstall(AddAmbulanceOccupants, 0x41C4A0, { .reversed = false });
    RH_ScopedInstall(AddFiretruckOccupants, 0x41C600, { .reversed = false });
    RH_ScopedInstall(AddPoliceCarOccupants, 0x41C070, { .reversed = false });
    RH_ScopedInstall(BackToCruisingIfNoWantedLevel, 0x41BFA0, { .reversed = false });
    RH_ScopedInstall(CarHasReasonToStop, 0x41C050, { .reversed = false });
    RH_ScopedInstall(EntitiesGoHeadOn, 0x41CD00, { .reversed = false });
    RH_ScopedInstall(FindPoliceBikeMissionForWantedLevel, 0x41CA40);
    RH_ScopedInstall(FindPoliceBoatMissionForWantedLevel, 0x41CA50);
    RH_ScopedInstall(FindPoliceCarMissionForWantedLevel, 0x41C9D0, { .reversed = false });
    RH_ScopedInstall(FindPoliceCarSpeedForWantedLevel, 0x41CAA0);
    RH_ScopedInstall(FindSwitchDistanceClose, 0x41BF50, { .reversed = false });
    RH_ScopedInstall(FindSwitchDistanceFar, 0x41BF70, { .reversed = false });
    RH_ScopedInstall(GetCarToGoToCoors, 0x41CE30, { .reversed = false });
    RH_ScopedInstall(GetCarToGoToCoorsAccurate, 0x41D0E0, { .reversed = false });
    RH_ScopedInstall(GetCarToGoToCoorsRacing, 0x41D210, { .reversed = false });
    RH_ScopedInstall(GetCarToGoToCoorsStraightLine, 0x41CFB0, { .reversed = false });
    RH_ScopedInstall(GetCarToParkAtCoors, 0x41D350, { .reversed = false });
    RH_ScopedInstall(MakeWayForCarWithSiren, 0x41D660, { .reversed = false });
    RH_ScopedInstall(MellowOutChaseSpeed, 0x41D3D0, { .reversed = false });
    RH_ScopedInstall(MellowOutChaseSpeedBoat, 0x41CB70);
    RH_ScopedInstall(TellCarToBlockOtherCar, 0x41C900, { .reversed = false });
    RH_ScopedInstall(TellCarToFollowOtherCar, 0x41C960, { .reversed = false });
    RH_ScopedInstall(TellCarToRamOtherCar, 0x41C8A0, { .reversed = false });
    RH_ScopedInstall(TellOccupantsToLeaveCar, 0x41C760, { .reversed = false });
    RH_ScopedInstall(UpdateCarAI, 0x41DA30, { .reversed = false });
}

// 0x41C4A0
void CCarAI::AddAmbulanceOccupants(CVehicle* vehicle) {
    plugin::Call<0x41C4A0, CVehicle*>(vehicle);
}

// 0x41C600
void CCarAI::AddFiretruckOccupants(CVehicle* vehicle) {
    plugin::Call<0x41C600, CVehicle*>(vehicle);
}

// 0x41C070
void CCarAI::AddPoliceCarOccupants(CVehicle* vehicle, bool arg2) {
    plugin::Call<0x41C070, CVehicle*, bool>(vehicle, arg2);
}

// 0x41BFA0
void CCarAI::BackToCruisingIfNoWantedLevel(CVehicle* vehicle) {
    plugin::Call<0x41BFA0, CVehicle*>(vehicle);
}

// 0x41C050
void CCarAI::CarHasReasonToStop(CVehicle* vehicle) {
    vehicle->m_autoPilot.m_nTimeToStartMission = CTimer::m_snTimeInMilliseconds;
}

// 0x41CD00
void CCarAI::EntitiesGoHeadOn(CEntity* entity1, CEntity* entity2) {
    plugin::Call<0x41CD00, CEntity*, CEntity*>(entity1, entity2);
}

// 0x41CA40
eCarMission CCarAI::FindPoliceBikeMissionForWantedLevel() {
    return MISSION_POLICE_BIKE;
}

// 0x41CA50
eCarMission CCarAI::FindPoliceBoatMissionForWantedLevel() {
    const auto& wantedLevel = FindPlayerWanted()->m_nWantedLevel;
    if (wantedLevel < 2 || wantedLevel > 6)
        return FindPlayerVehicle() ? MISSION_BLOCKPLAYER_FARAWAY : MISSION_BOAT_CIRCLING_PLAYER;
    else
        return FindPlayerVehicle() ? MISSION_ATTACKPLAYER : MISSION_BOAT_CIRCLING_PLAYER;
}

// rtype eCarMission ?
// 0x41C9D0
int8 CCarAI::FindPoliceCarMissionForWantedLevel() {
    return plugin::CallAndReturn<int8, 0x41C9D0>();
}

// 0x41CAA0
int32 CCarAI::FindPoliceCarSpeedForWantedLevel(CVehicle* vehicle) {
    const auto& maxVelocity = vehicle->m_pHandlingData->m_transmissionData.m_fMaxVelocity;
    switch (FindPlayerWanted()->m_nWantedLevel) {
    case 0:
        return (int32)CGeneral::GetRandomNumberInRange(12.0f, 16.0f);
    case 1:
        return 25;
    case 2:
        return 34;
    case 3:
        return int32(maxVelocity * GAME_SPEED_TO_CAR_AI_SPEED * 0.90f);
    case 4:
        return int32(maxVelocity * GAME_SPEED_TO_CAR_AI_SPEED * 1.20f);
    case 5:
        return int32(maxVelocity * GAME_SPEED_TO_CAR_AI_SPEED * 1.25f);
    case 6:
        return int32(maxVelocity * GAME_SPEED_TO_CAR_AI_SPEED * 1.30f);
    default:
        return 0;
    }
}

// 0x41BF50
float CCarAI::FindSwitchDistanceClose(CVehicle* vehicle) {
    return (float)vehicle->m_autoPilot.m_nStraightLineDistance;
}

// 0x41BF70
float CCarAI::FindSwitchDistanceFar(CVehicle* vehicle) {
    if (vehicle->vehicleFlags.bIsLawEnforcer)
        return 50.0f;
    else
        return FindSwitchDistanceClose(vehicle) + 5.0f;
}

// 0x41CE30
float CCarAI::GetCarToGoToCoors(CVehicle* vehicle, CVector* vec, int32 drivingStyle, bool bSpeedLimit20) {
    return plugin::CallAndReturn<float, 0x41CE30, CVehicle*, CVector*, int32, bool>(vehicle, vec, drivingStyle, bSpeedLimit20);
}

// 0x41D0E0
float CCarAI::GetCarToGoToCoorsAccurate(CVehicle* vehicle, CVector* vec, int32 drivingStyle, bool bSpeedLimit20) {
    return plugin::CallAndReturn<float, 0x41D0E0, CVehicle*, CVector*, int32, bool>(vehicle, vec, drivingStyle, bSpeedLimit20);
}

// 0x41D210
float CCarAI::GetCarToGoToCoorsRacing(CVehicle* vehicle, CVector* vec, int32 drivingStyle, bool bSpeedLimit20) {
    return plugin::CallAndReturn<float, 0x41D210, CVehicle*, CVector*, int32, bool>(vehicle, vec, drivingStyle, bSpeedLimit20);
}

// 0x41CFB0
float CCarAI::GetCarToGoToCoorsStraightLine(CVehicle* vehicle, CVector* vec, int32 drivingStyle, bool bSpeedLimit20) {
    return plugin::CallAndReturn<float, 0x41CFB0, CVehicle*, CVector*, int32, bool>(vehicle, vec, drivingStyle, bSpeedLimit20);
}

// 0x41D350
float CCarAI::GetCarToParkAtCoors(CVehicle* vehicle, CVector* vec) {
    return plugin::CallAndReturn<float, 0x41D350, CVehicle*, CVector*>(vehicle, vec);
}

// 0x41D660
void CCarAI::MakeWayForCarWithSiren(CVehicle* vehicle) {
    plugin::Call<0x41D660, CVehicle*>(vehicle);
}

// The closer the car is to the player, the slower its speed.
// Used for police cars when the player has wanted stars.
//
// 0x41D3D0
void CCarAI::MellowOutChaseSpeed(CVehicle* vehicle) {
    if (FindPlayerWanted()->GetWantedLevel() == 1) {
        const float distanceToPlayer = (vehicle->GetPosition() - FindPlayerCoors()).Magnitude();
        if (FindPlayerVehicle()) {
            if (distanceToPlayer < 10.0) {
                vehicle->m_autoPilot.m_nCruiseSpeed = 15;
            } else if (distanceToPlayer < 20.0) {
                vehicle->m_autoPilot.m_nCruiseSpeed = 22;
            } else {
                vehicle->m_autoPilot.m_nCruiseSpeed = 25;
            }
        } else {
            if (distanceToPlayer < 20.0) {
                vehicle->m_autoPilot.m_nCruiseSpeed = 5;
            } else if (distanceToPlayer < 40.0) {
                vehicle->m_autoPilot.m_nCruiseSpeed = 13;
            } else {
                vehicle->m_autoPilot.m_nCruiseSpeed = 25;
            }
        }
    } else {
        if (FindPlayerWanted()->GetWantedLevel() == 2) {
            const float distanceToPlayer = (vehicle->GetPosition() - FindPlayerCoors()).Magnitude();
            if (FindPlayerVehicle(-1, 0)) {
                if (distanceToPlayer < 10.0) {
                    vehicle->m_autoPilot.m_nCruiseSpeed = 27;
                } else if (distanceToPlayer < 20.0) {
                    vehicle->m_autoPilot.m_nCruiseSpeed = 30;
                } else {
                    vehicle->m_autoPilot.m_nCruiseSpeed = 34;
                }
            } else {
                if (distanceToPlayer < 20.0) {
                    vehicle->m_autoPilot.m_nCruiseSpeed = 5;
                } else if (distanceToPlayer < 40.0) {
                    vehicle->m_autoPilot.m_nCruiseSpeed = 18;
                } else {
                    vehicle->m_autoPilot.m_nCruiseSpeed = 34;
                }
            }
        }
    }
    if (!FindPlayerVehicle() && FindPlayerPed()->GetMoveSpeed().Magnitude() < 0.07) {
        if ((FindPlayerCoors() - vehicle->GetPosition()).Magnitude() < 30.0f)
            vehicle->m_autoPilot.m_nCruiseSpeed = std::min(10, (int)vehicle->m_autoPilot.m_nCruiseSpeed);
    }
}

// 0x41CB70
void CCarAI::MellowOutChaseSpeedBoat(CVehicle* vehicle) {
    switch (FindPlayerWanted()->m_nWantedLevel) {
    case 0:
        vehicle->m_autoPilot.m_nCruiseSpeed = 8;
        break;
    case 1:
        vehicle->m_autoPilot.m_nCruiseSpeed = 10;
        break;
    case 2:
        vehicle->m_autoPilot.m_nCruiseSpeed = 15;
        break;
    case 3:
        vehicle->m_autoPilot.m_nCruiseSpeed = 20;
        break;
    case 4:
        vehicle->m_autoPilot.m_nCruiseSpeed = 25;
        break;
    case 5:
        vehicle->m_autoPilot.m_nCruiseSpeed = 30;
        break;
    case 6:
        vehicle->m_autoPilot.m_nCruiseSpeed = 40;
        break;
    default:
        return;
    }
}

// 0x41C900
void CCarAI::TellCarToBlockOtherCar(CVehicle* vehicle1, CVehicle* vehicle2) {
    plugin::Call<0x41C900, CVehicle*, CVehicle*>(vehicle1, vehicle2);
}

// 0x41C960
void CCarAI::TellCarToFollowOtherCar(CVehicle* vehicle1, CVehicle* vehicle2, float radius) {
    plugin::Call<0x41C960, CVehicle*, CVehicle*, float>(vehicle1, vehicle2, radius);
}

// 0x41C8A0
void CCarAI::TellCarToRamOtherCar(CVehicle* vehicle1, CVehicle* vehicle2) {
    plugin::Call<0x41C8A0, CVehicle*, CVehicle*>(vehicle1, vehicle2);
}

// 0x41C760
void CCarAI::TellOccupantsToLeaveCar(CVehicle* vehicle) {
    plugin::Call<0x41C760, CVehicle*>(vehicle);
}

// 0x41DA30
void CCarAI::UpdateCarAI(CVehicle* vehicle) {
    plugin::Call<0x41DA30, CVehicle*>(vehicle);
}
