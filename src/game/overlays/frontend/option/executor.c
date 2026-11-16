#include "common.h"

void option_RoomObjectSetup(void);
void option_RoomFromLObjectSetup(void);
void option_RoomFromRObjectSetup(void);
void option_RoomFromRecordObjectSetup(void);
void option_SoundRoomLObjectSetup(void);
void option_SoundRoomRObjectSetup(void);
void option_RecordRoomObjectSetup(void);

OvlEntrypoint option_ovlEntryTbl[] = {
    { 0, option_RoomObjectSetup },
    { 1, option_RoomFromLObjectSetup },
    { 2, option_RoomFromRObjectSetup },
    { 3, option_RoomFromRecordObjectSetup },
    { 4, option_SoundRoomLObjectSetup },
    { 5, option_SoundRoomRObjectSetup },
    { 6, option_RecordRoomObjectSetup },
    { -1, NULL },
};

void option_Executor(void) {
    ovlEventCall(option_ovlEntryTbl, omovlevtno);
}
