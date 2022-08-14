#pragma once

#include "FxInfo.h"
#include "FxInterpInfoFloat.h"

class FxInfoEmAngle_c : public FxInfo_c {
protected:
    FxInterpInfoFloat_c m_InterpInfo;

public:
    FxInfoEmAngle_c();
    ~FxInfoEmAngle_c() override = default; // 0x4A6C50

    void Load(FILESTREAM file, int32 version) override;
    void GetValue(float currentTime, float mult, float totalTime, float length, bool bConstTimeSet, void* info) override;
};