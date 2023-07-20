## @file
# Dasharo DSC include file for [Components*] section.
#
# This file can be included to the [Components*] section(s) of a platform DSC file
# by using "!include DasharoModulePkg/DasharoModuleComponents.dsc.inc" to specify the INF files.
#
# Copyright (c) 2023, 3mdeb Sp. z o.o. All rights reserved.<BR>
# SPDX-License-Identifier: BSD-2-Clause
#
##

[Components.IA32]

!if $(TPM_ENABLE) == TRUE
  DasharoModulePkg/Tcg2Config/Tcg2ConfigPei.inf
  SecurityPkg/Tcg/TcgPei/TcgPei.inf
  SecurityPkg/Tcg/Tcg2Pei/Tcg2Pei.inf {
    <LibraryClasses>
      HashLib|SecurityPkg/Library/HashLibBaseCryptoRouter/HashLibBaseCryptoRouterPei.inf
      NULL|SecurityPkg/Library/HashInstanceLibSha1/HashInstanceLibSha1.inf
      NULL|SecurityPkg/Library/HashInstanceLibSha256/HashInstanceLibSha256.inf
      NULL|SecurityPkg/Library/HashInstanceLibSha384/HashInstanceLibSha384.inf
      NULL|SecurityPkg/Library/HashInstanceLibSha512/HashInstanceLibSha512.inf
      NULL|SecurityPkg/Library/HashInstanceLibSm3/HashInstanceLibSm3.inf
  }
!if $(OPAL_PASSWORD_ENABLE) == TRUE
  SecurityPkg/Tcg/Opal/OpalPassword/OpalPasswordPei.inf
!endif
!endif

!if $(SATA_PASSWORD_ENABLE) == TRUE
  SecurityPkg/HddPassword/HddPasswordPei.inf
!endif

[Components.X64]

  #
  # Components that produce the architectural protocols
  #
  MdeModulePkg/Universal/SecurityStubDxe/SecurityStubDxe.inf {
    <LibraryClasses>
!if $(SECURE_BOOT_ENABLE) == TRUE
      NULL|SecurityPkg/Library/DxeImageVerificationLib/DxeImageVerificationLib.inf
!endif
!if $(TPM_ENABLE) == TRUE
      NULL|SecurityPkg/Library/DxeTpmMeasureBootLib/DxeTpmMeasureBootLib.inf
      NULL|SecurityPkg/Library/DxeTpm2MeasureBootLib/DxeTpm2MeasureBootLib.inf
!endif
  }

!if $(SECURE_BOOT_ENABLE) == TRUE
  SecurityPkg/VariableAuthenticated/SecureBootConfigDxe/SecureBootConfigDxe.inf
  SecurityPkg/VariableAuthenticated/SecureBootDefaultKeysDxe/SecureBootDefaultKeysDxe.inf
!endif

!if $(SETUP_PASSWORD_ENABLE) == TRUE
  DasharoModulePkg/UserAuthenticationDxe/UserAuthenticationDxe.inf {
    <LibraryClasses>
      PlatformPasswordLib|DasharoModulePkg/Library/PlatformPasswordLibNull/PlatformPasswordLibNull.inf
  }
!endif

  DasharoModulePkg/Logo/Logo.inf
  DasharoModulePkg/Logo/LogoDxe.inf

!if $(BOOTLOADER) == "COREBOOT"
  DasharoModulePkg/SmmStoreFvb/SmmStoreFvbRuntimeDxe.inf
!endif
  MdeModulePkg/Universal/FaultTolerantWriteDxe/FaultTolerantWriteDxe.inf
  MdeModulePkg/Universal/Variable/RuntimeDxe/VariableRuntimeDxe.inf {
    <LibraryClasses>
      NULL|MdeModulePkg/Library/VarCheckUefiLib/VarCheckUefiLib.inf
      NULL|EmbeddedPkg/Library/NvVarStoreFormattedLib/NvVarStoreFormattedLib.inf
  }

  MdeModulePkg/Universal/SmbiosMeasurementDxe/SmbiosMeasurementDxe.inf
  MdeModulePkg/Universal/DriverHealthManagerDxe/DriverHealthManagerDxe.inf

  DasharoModulePkg/DasharoBootPolicies/DasharoBootPolicies.inf

  MdeModulePkg/Application/UiApp/UiApp.inf {
    <LibraryClasses>
      NULL|MdeModulePkg/Library/DeviceManagerUiLib/DeviceManagerUiLib.inf
      NULL|DasharoModulePkg/Library/DasharoSystemFeaturesUiLib/DasharoSystemFeaturesUiLib.inf
      NULL|MdeModulePkg/Library/BootManagerUiLib/BootManagerUiLib.inf
      NULL|MdeModulePkg/Library/BootMaintenanceManagerUiLib/BootMaintenanceManagerUiLib.inf
    <PcdsFixedAtBuild>
      gDasharoSystemFeaturesTokenSpaceGuid.PcdShowMenu|$(DASHARO_SYSTEM_FEATURES_ENABLE)
      gDasharoSystemFeaturesTokenSpaceGuid.PcdShowIommuOptions|$(IOMMU_ENABLE)
      gDasharoSystemFeaturesTokenSpaceGuid.PcdShowSerialPortMenu|$(SERIAL_TERMINAL)
  }
  MdeModulePkg/Application/BootManagerMenuApp/BootManagerMenuApp.inf

  #
  # Random Number Generator
  #
  SecurityPkg/RandomNumberGenerator/RngDxe/RngDxe.inf {
      <LibraryClasses>
      RngLib|UefiPayloadPkg/Library/BaseRngLib/BaseRngLib.inf
  }

  #
  # Hash2
  #
  SecurityPkg/Hash2DxeCrypto/Hash2DxeCrypto.inf {
    <LibraryClasses>
    BaseCryptLib|CryptoPkg/Library/BaseCryptLib/BaseCryptLib.inf
  }

  #
  # PKCS7 Verification
  #
  SecurityPkg/Pkcs7Verify/Pkcs7VerifyDxe/Pkcs7VerifyDxe.inf

!if $(TPM_ENABLE) == TRUE
  SecurityPkg/Tcg/Tcg2Dxe/Tcg2Dxe.inf {
    <LibraryClasses>
      Tpm2DeviceLib|SecurityPkg/Library/Tpm2DeviceLibRouter/Tpm2DeviceLibRouterDxe.inf
      NULL|SecurityPkg/Library/Tpm2DeviceLibDTpm/Tpm2InstanceLibDTpm.inf
      HashLib|SecurityPkg/Library/HashLibBaseCryptoRouter/HashLibBaseCryptoRouterDxe.inf
      NULL|SecurityPkg/Library/HashInstanceLibSha1/HashInstanceLibSha1.inf
      NULL|SecurityPkg/Library/HashInstanceLibSha256/HashInstanceLibSha256.inf
      NULL|SecurityPkg/Library/HashInstanceLibSha384/HashInstanceLibSha384.inf
      NULL|SecurityPkg/Library/HashInstanceLibSha512/HashInstanceLibSha512.inf
      NULL|SecurityPkg/Library/HashInstanceLibSm3/HashInstanceLibSm3.inf
  }
  SecurityPkg/Tcg/Tcg2Config/Tcg2ConfigDxe.inf
  SecurityPkg/Tcg/TcgDxe/TcgDxe.inf {
    <LibraryClasses>
      Tpm12DeviceLib|SecurityPkg/Library/Tpm12DeviceLibDTpm/Tpm12DeviceLibDTpm.inf
  }
  SecurityPkg/Tcg/TcgConfigDxe/TcgConfigDxe.inf {
    <LibraryClasses>
      Tpm12DeviceLib|SecurityPkg/Library/Tpm12DeviceLibDTpm/Tpm12DeviceLibDTpm.inf
  }
!if $(OPAL_PASSWORD_ENABLE) == TRUE
  SecurityPkg/Tcg/Opal/OpalPassword/OpalPasswordDxe.inf {
    <LibraryClasses>
    Tpm2DeviceLib|SecurityPkg/Library/Tpm2DeviceLibRouter/Tpm2DeviceLibRouterDxe.inf
  }
!endif
!endif

!if $(SATA_PASSWORD_ENABLE) == TRUE
  SecurityPkg/HddPassword/HddPasswordDxe.inf {
    <LibraryClasses>
      S3BootScriptLib|MdePkg/Library/BaseS3BootScriptLibNull/BaseS3BootScriptLibNull.inf
  }
!endif

!if $(IOMMU_ENABLE) == TRUE
  IntelSiliconPkg/Feature/VTd/IntelVTdDxe/IntelVTdDxe.inf
!endif

  #
  # Network Support
  #
!include NetworkPkg/NetworkComponents.dsc.inc

!if $(NETWORK_TLS_ENABLE) == TRUE
  NetworkPkg/TlsAuthConfigDxe/TlsAuthConfigDxe.inf {
    <LibraryClasses>
      NULL|OvmfPkg/Library/TlsAuthConfigLib/TlsAuthConfigLib.inf
  }
!endif

  DasharoModulePkg/PciPlatformDxe/PciPlatformDxe.inf

  # Upstream already fixed it and there will be no need for this module
  DasharoModulePkg/AcpiPlatformDxe/AcpiPlatformDxe.inf

!if $(RAM_DISK_ENABLE) == TRUE
  MdeModulePkg/Universal/Disk/RamDiskDxe/RamDiskDxe.inf
!endif

  CrScreenshotDxe/CrScreenshotDxe.inf

  MdeModulePkg/Universal/Acpi/AcpiTableDxe/AcpiTableDxe.inf
  MdeModulePkg/Universal/Acpi/BootGraphicsResourceTableDxe/BootGraphicsResourceTableDxe.inf

  #
  # ISA Support
  #
  MdeModulePkg/Universal/SerialDxe/SerialDxe.inf {
    <LibraryClasses>
    !if $(SYSTEM76_EC_LOGGING) == TRUE
      SerialPortLib|DasharoModulePkg/Library/System76EcLib/System76EcLib.inf
      PlatformHookLib|DasharoModulePkg/Library/System76EcLib/System76EcLib.inf
    !else
      SerialPortLib|MdeModulePkg/Library/BaseSerialPortLib16550/BaseSerialPortLib16550.inf
      PlatformHookLib|UefiPayloadPkg/Library/PlatformHookLib/PlatformHookLib.inf
    !endif
  }

!if $(PS2_KEYBOARD_ENABLE) == TRUE
  OvmfPkg/SioBusDxe/SioBusDxe.inf
  MdeModulePkg/Bus/Isa/Ps2KeyboardDxe/Ps2KeyboardDxe.inf
!endif

!if $(USE_PLATFORM_GOP) == TRUE
  DasharoModulePkg/PlatformGopPolicy/PlatformGopPolicy.inf
!else
  UefiPayloadPkg/GraphicsOutputDxe/GraphicsOutputDxe.inf
!endif

!if $(PERFORMANCE_MEASUREMENT_ENABLE)
  MdeModulePkg/Universal/Acpi/FirmwarePerformanceDataTableDxe/FirmwarePerformanceDxe.inf
!endif
