#pragma once

#include "Base.h"
#include <rwplcore.h>

#include "TaskSimpleIKChain.h"

class CEntity;
class CPed;

class CTaskSimpleIKLookAt : public CTaskSimpleIKChain {
public:
    bool m_bUseTorso;
    int8 m_nPriority;

public:
    static constexpr auto Type = TASK_SIMPLE_IK_LOOK_AT;

    CTaskSimpleIKLookAt(Const char* name, CEntity* lookAtEntity, int32 time, ePedBones pedBoneID, CVector lookAtOffset, bool useTorso, float speed, int32 blendTime, int8 priority);
    ~CTaskSimpleIKLookAt() override = default; // 0x633EF0

    eTaskType GetTaskType() override { return Type; }
    CTaskSimpleIKLookAt* Clone() override;
    bool CreateIKChain(CPed* ped) override;

    void UpdateLookAtInfo(const char* strPurpose, CPed* ped, CEntity* targetPed, int32 time, ePedBones pedBoneID, RwV3d lookAtOffset, bool useTorso, float fSpeed, int32 blendTime, int32 unused);
    CEntity* GetLookAtEntity();
    CVector GetLookAtOffset();

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleIKLookAt* Constructor(char* name, CEntity* lookAtEntity, int32 time, ePedBones pedBoneID, RwV3d lookAtOffset, uint8 useTorso, float fSpeed, int32 blendTime, int32 priority) { this->CTaskSimpleIKLookAt::CTaskSimpleIKLookAt(name, lookAtEntity, time, pedBoneID, lookAtOffset, useTorso, fSpeed, blendTime, priority); return this; }
    CTaskSimpleIKLookAt* Destructor() { this->CTaskSimpleIKLookAt::~CTaskSimpleIKLookAt(); return this; }
    CTask* Clone_Reversed() { return CTaskSimpleIKLookAt::Clone(); }
    eTaskType GetTaskType_Reversed() { return CTaskSimpleIKLookAt::GetTaskType(); }
    bool CreateIKChain_Reversed(CPed* ped) { return CTaskSimpleIKLookAt::CreateIKChain(ped); }
};
VALIDATE_SIZE(CTaskSimpleIKLookAt, 0x5C);
