## @file
# Dasharo DSC include file for [LibraryClasses*] section.
#
# This file can be included to the [LibraryClasses*] section(s) of a platform DSC file
# by using "!include DasharoModulePkg/DasharoModuleLibs.dsc.inc" to specify the libraries.
#
# Copyright (c) 2023, 3mdeb Sp. z o.o. All rights reserved.<BR>
# SPDX-License-Identifier: BSD-2-Clause
#
##


[LibraryClasses]

!if (($(USE_CBMEM_FOR_CONSOLE) == TRUE) && ($(TARGET) == RELEASE))
  SerialPortLib|DasharoModulePkg/Library/CbSerialPortLib/CbSerialPortLib.inf
  PlatformHookLib|MdeModulePkg/Library/BasePlatformHookLibNull/BasePlatformHookLibNull.inf
!elseif $(SYSTEM76_EC_LOGGING) == TRUE
  SerialPortLib|DasharoModulePkg/Library/System76EcLib/System76EcLib.inf
  PlatformHookLib|DasharoModulePkg/Library/System76EcLib/System76EcLib.inf
!else
  SerialPortLib|MdeModulePkg/Library/BaseSerialPortLib16550/BaseSerialPortLib16550.inf
  PlatformHookLib|UefiPayloadPkg/Library/PlatformHookLib/PlatformHookLib.inf
!endif

  PlatformBootManagerLib|DasharoModulePkg/Library/PlatformBootManagerLib/PlatformBootManagerLib.inf

!if $(OPAL_PASSWORD_ENABLE) == TRUE
  TcgStorageCoreLib|SecurityPkg/Library/TcgStorageCoreLib/TcgStorageCoreLib.inf
  TcgStorageOpalLib|SecurityPkg/Library/TcgStorageOpalLib/TcgStorageOpalLib.inf
!endif

  PciHostBridgeLib|DasharoModulePkg/Library/PciHostBridgeLib/PciHostBridgeLib.inf

#
# Network
#
!include NetworkPkg/NetworkLibs.dsc.inc

!if $(NETWORK_TLS_ENABLE) == TRUE
  OpensslLib|CryptoPkg/Library/OpensslLib/OpensslLib.inf
  TlsLib|CryptoPkg/Library/TlsLib/TlsLib.inf
!else
  OpensslLib|CryptoPkg/Library/OpensslLib/OpensslLibCrypto.inf
!endif

!if $(SECURE_BOOT_ENABLE) == TRUE
  PlatformSecureLib|OvmfPkg/Library/PlatformSecureLib/PlatformSecureLib.inf
  AuthVariableLib|SecurityPkg/Library/AuthVariableLib/AuthVariableLib.inf
  SecureBootVariableLib|SecurityPkg/Library/SecureBootVariableLib/SecureBootVariableLib.inf
  SecureBootVariableProvisionLib|SecurityPkg/Library/SecureBootVariableProvisionLib/SecureBootVariableProvisionLib.inf
!else
  AuthVariableLib|MdeModulePkg/Library/AuthVariableLibNull/AuthVariableLibNull.inf
!endif

!if $(TPM_ENABLE) == TRUE
  Tpm12CommandLib|SecurityPkg/Library/Tpm12CommandLib/Tpm12CommandLib.inf
  Tpm2CommandLib|SecurityPkg/Library/Tpm2CommandLib/Tpm2CommandLib.inf
  Tcg2PhysicalPresenceLib|OvmfPkg/Library/Tcg2PhysicalPresenceLibQemu/DxeTcg2PhysicalPresenceLib.inf
  Tcg2PhysicalPresencePlatformLib|DasharoModulePkg/Library/Tcg2PhysicalPresencePlatformLibUefipayload/DxeTcg2PhysicalPresencePlatformLib.inf
  Tcg2PpVendorLib|SecurityPkg/Library/Tcg2PpVendorLibNull/Tcg2PpVendorLibNull.inf
  TpmMeasurementLib|SecurityPkg/Library/DxeTpmMeasurementLib/DxeTpmMeasurementLib.inf
!else
  TpmMeasurementLib|MdeModulePkg/Library/TpmMeasurementLibNull/TpmMeasurementLibNull.inf
  Tcg2PhysicalPresenceLib|OvmfPkg/Library/Tcg2PhysicalPresenceLibNull/DxeTcg2PhysicalPresenceLib.inf
!endif

!if $(BOOTLOADER) == "COREBOOT"
  SmmStoreLib|DasharoModulePkg/Library/SmmStoreLib/SmmStoreLib.inf
  BlParseLib|DasharoModulePkg/Library/CbParseLib/CbParseLib.inf
!endif

[LibraryClasses.common.PEIM]
  PerformanceLib|MdeModulePkg/Library/PeiPerformanceLib/PeiPerformanceLib.inf

!if $(TPM_ENABLE) == TRUE
  BaseCryptLib|CryptoPkg/Library/BaseCryptLib/PeiCryptLib.inf
  Tpm12DeviceLib|SecurityPkg/Library/Tpm12DeviceLibDTpm/Tpm12DeviceLibDTpm.inf
  Tpm2DeviceLib|SecurityPkg/Library/Tpm2DeviceLibDTpm/Tpm2DeviceLibDTpm.inf
  Tcg2PhysicalPresenceLib|SecurityPkg/Library/PeiTcg2PhysicalPresenceLib/PeiTcg2PhysicalPresenceLib.inf
!endif

	
[LibraryClasses.common.DXE_DRIVER]
  PerformanceLib|MdeModulePkg/Library/DxePerformanceLib/DxePerformanceLib.inf
!if $(TPM_ENABLE) == TRUE
  Tpm12DeviceLib|SecurityPkg/Library/Tpm12DeviceLibTcg/Tpm12DeviceLibTcg.inf
  Tpm2DeviceLib|SecurityPkg/Library/Tpm2DeviceLibTcg2/Tpm2DeviceLibTcg2.inf
!endif


!if $(BATTERY_CHECK)
  LaptopBatteryLib|DasharoModulePkg/Library/LaptopBatteryLib/LaptopBatteryLib.inf
!else
  LaptopBatteryLib|DasharoModulePkg/Library/LaptopBatteryLib/LaptopBatteryLibNull.inf
!endif

[LibraryClasses.common.DXE_RUNTIME_DRIVER]
  PerformanceLib|MdeModulePkg/Library/DxePerformanceLib/DxePerformanceLib.inf
  DebugLib|MdePkg/Library/DxeRuntimeDebugLibSerialPort/DxeRuntimeDebugLibSerialPort.inf