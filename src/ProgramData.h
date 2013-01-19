#ifndef PROGRAMDATA_H_
#define PROGRAMDATA_H_

#include <inttypes.h>
#include "AnalogInputs.h"
#include "Hardware.h"


#define MAX_PROGRAMS 32
#define PROGRAM_DATA_MAX_NAME 14

struct ProgramData {
    enum BatteryType {Unknown, NiCd, NiMH, Pb, Life, Lilo, Lipo,                 LAST_BATTERY_TYPE};
    enum VoltageType {VIdle,VCharge,VDischarge,VStorage, VUpperLimit,            LAST_VOLTAGE_TYPE};

    struct BatteryData {
        uint8_t type;
        uint16_t C,Ic,Id,cells;
    };

    BatteryData battery;
    char name[PROGRAM_DATA_MAX_NAME];

    uint16_t getVoltagePerCell(VoltageType type = VIdle) const;
    uint16_t getVoltage(VoltageType type = VIdle) const;
    uint16_t getCapacityLimit() const;
    int16_t getDeltaVLimit() const;
    int16_t getDeltaTLimit() const;

    bool edit(int index);
    void createName(int index);

    uint8_t printBatteryString(int n) const;
    uint8_t printBatteryString() const;

    uint8_t printVoltageString() const;
    uint8_t printIcString() const;
    uint8_t printIdString() const;
    uint8_t printChargeString() const;

    void changeBattery(int direction);
    void changeVoltage(int direction);
    void changeCharge(int direction);
    void changeIc(int direction);
    void changeId(int direction);

    uint16_t getMaxCells() const;
    uint16_t getMaxIc() const;
    uint16_t getMaxId() const;

    void check();
    void loadDefault();

    bool isLiXX() const { return battery.type == Life || battery.type == Lilo || battery.type == Lipo;};
    bool isNiXX() const { return battery.type == NiCd || battery.type == NiMH; };

    static void loadProgramData(int index);
    static void saveProgramData(int index);
    static char * getName_E(int index);
    static void restoreDefault();

    static ProgramData currentProgramData;

private:
    static void printIndex(char * &buf, uint8_t &maxSize, uint8_t index);
};

#endif /* PROGRAMDATA_H_ */
