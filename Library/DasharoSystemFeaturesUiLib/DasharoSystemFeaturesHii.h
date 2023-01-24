/** @file
The Dasharo system features implementation

Copyright (c) 2022, Intel Corporation. All rights reserved.<BR>
SPDX-License-Identifier: BSD-2-Clause

**/

#ifndef _DASHARO_SYSTEM_FEATURES_HII_H_
#define _DASHARO_SYSTEM_FEATURES_HII_H_

#define DASHARO_SYSTEM_FEATURES_GUID  \
  { 0xd15b327e, 0xff2d, 0x4fc1, {0xab, 0xf6, 0xc1, 0x2b, 0xd0, 0x8c, 0x13, 0x59} }

#define DASHARO_SYSTEM_FEATURES_FORM_ID        0x1000
#define DASHARO_SECURITY_OPTIONS_FORM_ID       0x1001
#define DASHARO_NETWORK_OPTIONS_FORM_ID        0x1002
#define DASHARO_USB_CONFIGURATION_FORM_ID      0x1003
#define DASHARO_INTEL_ME_OPTIONS_FORM_ID       0x1004
#define DASHARO_CHIPSET_CONFIGURATION_FORM_ID  0x1005
#define DASHARO_POWER_CONFIGURATION_FORM_ID    0x1006

#define DASHARO_FEATURES_DATA_VARSTORE_ID      0x0001

#pragma pack(push,1)
typedef struct {
  BOOLEAN WatchdogEnable;
  UINT16  WatchdogTimeout;
} WATCHDOG_CONFIG;

typedef struct {
  UINT8 Temp;
  UINT8 Duty;
} FAN_POINT;

typedef struct {
  FAN_POINT Point1;
  FAN_POINT Point2;
  FAN_POINT Point3;
  FAN_POINT Point4;
} FAN_CURVE;

#define FAN_CURVE_OPTION_SILENT 0
#define FAN_CURVE_OPTION_PERFORMANCE 1

#define FAN_CURVE_SILENT {      \
  { .Temp = 0,   .Duty = 25  }, \
  { .Temp = 65,  .Duty = 30  }, \
  { .Temp = 75,  .Duty = 35  }, \
  { .Temp = 100, .Duty = 100 }  \
}

#define FAN_CURVE_PERFORMANCE { \
  { .Temp = 0,   .Duty = 25 },  \
  { .Temp = 55,  .Duty = 35 },  \
  { .Temp = 75,  .Duty = 60 },  \
  { .Temp = 100, .Duty = 100 }  \
}
#pragma pack(pop)

typedef struct {
  // Feature visibility
  BOOLEAN            ShowSecurityMenu;
  BOOLEAN            ShowIntelMeMenu;
  BOOLEAN            ShowUsbMenu;
  BOOLEAN            ShowNetworkMenu;
  BOOLEAN            ShowChipsetMenu;
  BOOLEAN            ShowPowerMenu;
  // Feature data
  BOOLEAN            LockBios;
  BOOLEAN            SmmBwp;
  BOOLEAN            NetworkBoot;
  BOOLEAN            UsbStack;
  BOOLEAN            UsbMassStorage;
  UINT8              MeMode;
  BOOLEAN            Ps2Controller;
  WATCHDOG_CONFIG    WatchdogConfig;
  BOOLEAN            WatchdogState; // holds the state of watchdog before VAR population
  FAN_CURVE          FanCurve;
  UINT8              FanCurveOption;
} DASHARO_FEATURES_DATA;

#define ME_MODE_ENABLE        0
#define ME_MODE_DISABLE_HECI  1
#define ME_MODE_DISABLE_HAP   2

#define LOCK_BIOS_QUESTION_ID              0x8000
#define NETWORK_BOOT_QUESTION_ID           0x8001
#define USB_STACK_QUESTION_ID              0x8002
#define USB_MASS_STORAGE_QUESTION_ID       0x8003



extern EFI_GUID gDasharoSystemFeaturesGuid;

#endif
