## @file
# Dasharo DSC include file for [Pcds*] section.
#
# This file can be included to the [Pcds*] section(s) of a platform DSC file
# by using "!include DasharoModulePkg/DasharoModulePcds.dsc.inc" to specify the PCDs.
#
# Copyright (c) 2023, 3mdeb Sp. z o.o. All rights reserved.<BR>
# SPDX-License-Identifier: BSD-2-Clause
#
##

[PcdsFeatureFlag]

  gEfiMdeModulePkgTokenSpaceGuid.PcdFirmwarePerformanceDataTableS3Support|FALSE
  gEfiMdeModulePkgTokenSpaceGuid.PcdInstallAcpiSdtProtocol|TRUE
  gEfiMdeModulePkgTokenSpaceGuid.PcdPs2KbdExtendedVerification|TRUE

!if ($(TARGET) == DEBUG || $(USE_CBMEM_FOR_CONSOLE) == TRUE)
  gEfiMdeModulePkgTokenSpaceGuid.PcdStatusCodeUseSerial|TRUE
!else
  gEfiMdeModulePkgTokenSpaceGuid.PcdStatusCodeUseSerial|FALSE
!endif
  gEfiMdeModulePkgTokenSpaceGuid.PcdStatusCodeUseMemory|FALSE

[PcdsFixedAtBuild]
  # UEFI spec: Minimal value is 0x8000!
  gEfiMdeModulePkgTokenSpaceGuid.PcdMaxVariableSize|0x8000
  gEfiMdeModulePkgTokenSpaceGuid.PcdMaxAuthVariableSize|0x8800
  gUefiPayloadPkgTokenSpaceGuid.PcdBootMenuKey|$(BOOT_MENU_KEY)
  gUefiPayloadPkgTokenSpaceGuid.PcdSetupMenuKey|$(SETUP_MENU_KEY)
  gUefiPayloadPkgTokenSpaceGuid.PcdLoadOptionRoms|$(LOAD_OPTION_ROMS)
  gEfiMdeModulePkgTokenSpaceGuid.PcdSdMmcGenericTimeoutValue|$(SD_MMC_TIMEOUT)
  gDasharoSystemFeaturesTokenSpaceGuid.PcdShowMenu|$(DASHARO_SYSTEM_FEATURES_ENABLE)
  gDasharoSystemFeaturesTokenSpaceGuid.PcdShowIommuOptions|$(IOMMU_ENABLE)

!if $(SECURE_BOOT_DEFAULT_ENABLE) == TRUE
  gEfiSecurityPkgTokenSpaceGuid.PcdSecureBootDefaultEnable|1
!else
  gEfiSecurityPkgTokenSpaceGuid.PcdSecureBootDefaultEnable|0
!endif

!if $(PERFORMANCE_MEASUREMENT_ENABLE)
  gEfiMdePkgTokenSpaceGuid.PcdPerformanceLibraryPropertyMask|0x1
!endif

  # Disable MTRR programming
  gUefiCpuPkgTokenSpaceGuid.PcdCpuDisableMtrrProgramming|$(DISABLE_MTRR_PROGRAMMING)

  # 4K displays may need bigger buffers for the option strings in forms
  gEfiMdePkgTokenSpaceGuid.PcdMaximumUnicodeStringLength|2000000
  gUefiPayloadPkgTokenSpaceGuid.PcdBootMenuKey|$(BOOT_MENU_KEY)
  gUefiPayloadPkgTokenSpaceGuid.PcdSetupMenuKey|$(SETUP_MENU_KEY)
  gUefiPayloadPkgTokenSpaceGuid.PcdLoadOptionRoms|$(LOAD_OPTION_ROMS)
  gEfiMdeModulePkgTokenSpaceGuid.PcdSdMmcGenericTimeoutValue|$(SD_MMC_TIMEOUT)

  gEfiMdeModulePkgTokenSpaceGuid.PcdBootManagerMenuFile|{ 0x21, 0xaa, 0x2c, 0x46, 0x14, 0x76, 0x03, 0x45, 0x83, 0x6e, 0x8a, 0xb6, 0xf4, 0x66, 0x23, 0x31 }

[PcdsPatchableInModule.common]

  gEfiMdeModulePkgTokenSpaceGuid.PcdPciDisableBusEnumeration|TRUE
  gEfiMdePkgTokenSpaceGuid.PcdUartDefaultBaudRate|$(UART_DEFAULT_BAUD_RATE)
  gEfiMdePkgTokenSpaceGuid.PcdUartDefaultDataBits|$(UART_DEFAULT_DATA_BITS)
  gEfiMdePkgTokenSpaceGuid.PcdUartDefaultParity|$(UART_DEFAULT_PARITY)
  gEfiMdePkgTokenSpaceGuid.PcdUartDefaultStopBits|$(UART_DEFAULT_STOP_BITS)
  gEfiMdePkgTokenSpaceGuid.PcdDefaultTerminalType|$(DEFAULT_TERMINAL_TYPE)

  gEfiMdeModulePkgTokenSpaceGuid.PcdFastPS2Detection|FALSE

!if $(PS2_KEYBOARD_ENABLE) == FALSE
  gUefiPayloadPkgTokenSpaceGuid.PcdSkipPs2Detect|TRUE
!else
  gUefiPayloadPkgTokenSpaceGuid.PcdSkipPs2Detect|FALSE
!endif

!if ($(USE_CBMEM_FOR_CONSOLE) == FALSE)
  !if $(SOURCE_DEBUG_ENABLE)
    gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x17
  !else
    gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x2F
  !endif
!else
  !if $(TARGET) == DEBUG
    gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x07
  !else
    gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x03
  !endif
!endif

[PcdsPatchableInModule.X64]
  #
  # Network Pcds
  #
!include NetworkPkg/NetworkPcds.dsc.inc

[PcdsDynamicDefault]

  gEfiMdeModulePkgTokenSpaceGuid.PcdEmuVariableNvModeEnable|FALSE

  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|0
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|0

  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn|0
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow|0

  gEfiSecurityPkgTokenSpaceGuid.PcdTpmInstanceGuid|{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # No need to initialize TPM again, coreboot already did that
  gEfiSecurityPkgTokenSpaceGuid.PcdTpm2InitializationPolicy|0
  gEfiSecurityPkgTokenSpaceGuid.PcdTpm2SelfTestPolicy|0
  gEfiSecurityPkgTokenSpaceGuid.PcdTpmInitializationPolicy|0

  gEfiMdePkgTokenSpaceGuid.PcdPlatformBootTimeOut|$(PLATFORM_BOOT_TIMEOUT)

  gEfiMdeModulePkgTokenSpaceGuid.PcdEmuVariableNvModeEnable|FALSE
  gEfiMdeModulePkgTokenSpaceGuid.PcdEmuVariableNvStoreReserved|0
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageVariableBase|0
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwWorkingBase|0
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwSpareBase|0
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageVariableSize|0
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwWorkingSize|0
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwSpareSize|0
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageVariableBase|0
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageVariableBase64|0
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwWorkingBase64|0
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwSpareBase64|0

[PcdsDynamicDefault.X64]
  gIntelSiliconPkgTokenSpaceGuid.PcdVTdPolicyPropertyMask|1

[PcdsDynamicHii]

!if $(TPM_ENABLE) == TRUE
  gEfiSecurityPkgTokenSpaceGuid.PcdTcgPhysicalPresenceInterfaceVer|L"TCG2_VERSION"|gTcg2ConfigFormSetGuid|0x0|"1.3"|NV,BS
  gEfiSecurityPkgTokenSpaceGuid.PcdTpm2AcpiTableRev|L"TCG2_VERSION"|gTcg2ConfigFormSetGuid|0x8|4|NV,BS
!endif

