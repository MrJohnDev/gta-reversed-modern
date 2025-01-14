#include "TaskSimple.h"

class NOTSA_EXPORT_VTABLE CTaskSimpleTogglePedThreatScanner : public CTaskSimple {
public:
    bool m_bScanAllowedScriptPed;
    bool m_bScanAllowedInVehicle;
    bool m_bScanAllowedScriptedTask;

public:
    static constexpr auto Type = TASK_SIMPLE_TOGGLE_PED_THREAT_SCANNER;

    CTaskSimpleTogglePedThreatScanner(bool bScanAllowedScriptPed, bool bScanAllowedInVehicle, bool bScanAllowedScriptedTask);
    ~CTaskSimpleTogglePedThreatScanner() override = default;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleTogglePedThreatScanner(m_bScanAllowedScriptPed, m_bScanAllowedInVehicle, m_bScanAllowedScriptedTask); } // 0x492D50
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override { return false; }
    bool ProcessPed(CPed* ped) override;
};
VALIDATE_SIZE(CTaskSimpleTogglePedThreatScanner, 0xC);
