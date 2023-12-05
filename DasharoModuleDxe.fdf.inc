## @file
# Dasharo FDF include file for [FV.DXEFV] section.
#
# This file can be included to the [FV.DXEFV] section of a platform FDF file
# by using "!include DasharoModulePkg/DasharoModuleDxe.fdf.inc" to specify the INFs.
#
# Copyright (c) 2023, 3mdeb Sp. z o.o. All rights reserved.<BR>
# SPDX-License-Identifier: BSD-2-Clause
#
##

INF MdeModulePkg/Universal/SecurityStubDxe/SecurityStubDxe.inf

INF MdeModulePkg/Universal/DriverHealthManagerDxe/DriverHealthManagerDxe.inf

!if $(BOOTLOADER) == "COREBOOT"
  # Initialize VariableStore and update PCDs before VariableRuntimeDxe
  INF DasharoModulePkg/SmmStoreFvb/SmmStoreFvbRuntimeDxe.inf
!endif
INF MdeModulePkg/Universal/FaultTolerantWriteDxe/FaultTolerantWriteDxe.inf
INF MdeModulePkg/Universal/Variable/RuntimeDxe/VariableRuntimeDxe.inf

INF DasharoModulePkg/Logo/LogoDxe.inf

INF MdeModulePkg/Universal/SmbiosMeasurementDxe/SmbiosMeasurementDxe.inf

FILE FREEFORM = PCD(gEfiMdeModulePkgTokenSpaceGuid.PcdLogoFile) {
  SECTION RAW = MdeModulePkg/Logo/Logo.bmp
}

INF DasharoModulePkg/AcpiPlatformDxe/AcpiPlatformDxe.inf
INF DasharoModulePkg/PciPlatformDxe/PciPlatformDxe.inf

#
# Filesystem drivers
#
!if $(ARCH) == IA32
INF  RuleOverride=BINARY USE = IA32 FSDrivers/exfat.inf
INF  RuleOverride=BINARY USE = IA32 FSDrivers/ext2.inf
INF  RuleOverride=BINARY USE = IA32 FSDrivers/ntfs.inf
INF  RuleOverride=BINARY USE = IA32 FSDrivers/ext4.inf
!else
INF  RuleOverride=BINARY USE = X64 FSDrivers/exfat.inf
INF  RuleOverride=BINARY USE = X64 FSDrivers/ext2.inf
INF  RuleOverride=BINARY USE = X64 FSDrivers/ntfs.inf
INF  RuleOverride=BINARY USE = X64 FSDrivers/ext4.inf
!endif

#
# Network Support
#
!include NetworkPkg/Network.fdf.inc

#
# Network modules (only available on X64)
#
!if $(NETWORK_LAN_ROM) == TRUE
#
# Build system must place the LanRom.efi before building the UEFI Payload.
# Typically will be done per platform needs by coreboot.
#
  FILE DRIVER = DEB917C0-C56A-4860-A05B-BF2F22EBB717 {
    SECTION DXE_DEPEX_EXP = {gDasharoNetworkBootPolicyGuid}
    SECTION PE32 = UefiPayloadPkg/NetworkDrivers/LanRom.efi
  }
!endif

#
# iPXE support
#
!if $(NETWORK_IPXE) == TRUE
  #
  # coreboot build system should put the ipxe.efi file here before EDK2 build
  #
  FILE FREEFORM = B68653C7-EEA1-4435-A199-A44F59E4476C {
   SECTION PE32 = UefiPayloadPkg/NetworkDrivers/ipxe.efi
  }
!endif

INF DasharoModulePkg/DasharoBootPolicies/DasharoBootPolicies.inf

!if $(RAM_DISK_ENABLE) == TRUE
INF  MdeModulePkg/Universal/Disk/RamDiskDxe/RamDiskDxe.inf
!endif

!if $(PERFORMANCE_MEASUREMENT_ENABLE)
  INF MdeModulePkg/Universal/Acpi/FirmwarePerformanceDataTableDxe/FirmwarePerformanceDxe.inf
!endif


# ACPI Support
#
INF MdeModulePkg/Universal/Acpi/AcpiTableDxe/AcpiTableDxe.inf
INF MdeModulePkg/Universal/Acpi/BootGraphicsResourceTableDxe/BootGraphicsResourceTableDxe.inf


!if $(USE_PLATFORM_GOP) == TRUE
!if "X64" in $(ARCH)
INF DasharoModulePkg/PlatformGopPolicy/PlatformGopPolicy.inf
!endif
FILE DRIVER = FF0C8745-3270-4439-B74F-3E45F8C77064 {
  SECTION DXE_DEPEX_EXP = {gPlatformGOPPolicyGuid}
  SECTION PE32 = UefiPayloadPkg/IntelGopDriver.efi
  SECTION UI = "IntelGopDriver"
}

FILE FREEFORM = 878AC2CC-5343-46F2-B563-51F89DAF56BA {
  SECTION RAW = UefiPayloadPkg/vbt.bin
  SECTION UI = "IntelGopVbt"
}
!else
INF UefiPayloadPkg/GraphicsOutputDxe/GraphicsOutputDxe.inf
!endif

#
# Security
#
!if $(SECURE_BOOT_ENABLE) == TRUE
  INF  SecurityPkg/VariableAuthenticated/SecureBootConfigDxe/SecureBootConfigDxe.inf
  INF  SecurityPkg/VariableAuthenticated/SecureBootDefaultKeysDxe/SecureBootDefaultKeysDxe.inf

  # gDefaultKEKFileGuid
  FILE FREEFORM = 6F64916E-9F7A-4C35-B952-CD041EFB05A3 {
    SECTION RAW = DasharoModulePkg/SecureBootDefaultKeys/MicCorKEKCA2011_2011-06-24.crt
    SECTION RAW = DasharoModulePkg/SecureBootDefaultKeys/microsoft_corporation_kek_2k_ca_2023.crt
    SECTION UI = "DefaultKekCert"
  }

  # gDefaultPKFileGuid
  FILE FREEFORM = 85254EA7-4759-4FC4-82D4-5EED5FB0A4A0 {
    SECTION RAW = DasharoModulePkg/SecureBootDefaultKeys/pk.crt
    SECTION UI = "DefaultPkCert"
  }

  # gDefaultdbFileGuid
  FILE FREEFORM = C491D352-7623-4843-ACCC-2791A7574421 {
    SECTION RAW = DasharoModulePkg/SecureBootDefaultKeys/MicWinProPCA2011_2011-10-19.crt
    SECTION RAW = DasharoModulePkg/SecureBootDefaultKeys/MicCorUEFCA2011_2011-06-27.crt
    SECTION RAW = DasharoModulePkg/SecureBootDefaultKeys/windows_uefi_ca_2023.crt
    SECTION RAW = DasharoModulePkg/SecureBootDefaultKeys/microsoft_uefi_ca_2023.crt
    SECTION UI = "DefaultDbCert"
  }

  # gDefaultdbxFileGuid
  FILE FREEFORM = 5740766A-718E-4DC0-9935-C36F7D3F884F {
    SECTION RAW = DasharoModulePkg/SecureBootDefaultKeys/DBXUpdate.bin
    SECTION UI = "DefaultDbxCert"
  }
!endif



!if $(TPM_ENABLE) == TRUE
INF  SecurityPkg/Tcg/TcgDxe/TcgDxe.inf
INF  SecurityPkg/Tcg/Tcg2Dxe/Tcg2Dxe.inf
INF  SecurityPkg/Tcg/TcgConfigDxe/TcgConfigDxe.inf
INF  SecurityPkg/Tcg/Tcg2Config/Tcg2ConfigDxe.inf
!if $(OPAL_PASSWORD_ENABLE) == TRUE
INF SecurityPkg/Tcg/Opal/OpalPassword/OpalPasswordDxe.inf
!endif
!endif

!if $(SATA_PASSWORD_ENABLE) == TRUE
INF SecurityPkg/HddPassword/HddPasswordDxe.inf
!endif

!if $(SETUP_PASSWORD_ENABLE) == TRUE
INF DasharoModulePkg/UserAuthenticationDxe/UserAuthenticationDxe.inf
!endif

!if $(IOMMU_ENABLE) == TRUE
INF IntelSiliconPkg/Feature/VTd/IntelVTdDxe/IntelVTdDxe.inf
!endif

#
# Random Number Generator
#
INF SecurityPkg/RandomNumberGenerator/RngDxe/RngDxe.inf

#
# Hash2
#
INF SecurityPkg/Hash2DxeCrypto/Hash2DxeCrypto.inf

#
# PKCS7 Verification
#
INF SecurityPkg/Pkcs7Verify/Pkcs7VerifyDxe/Pkcs7VerifyDxe.inf

INF CrScreenshotDxe/CrScreenshotDxe.inf

INF MdeModulePkg/Application/BootManagerMenuApp/BootManagerMenuApp.inf

#
# ISA Support
#
INF MdeModulePkg/Universal/SerialDxe/SerialDxe.inf
!if $(PS2_KEYBOARD_ENABLE) == TRUE
INF OvmfPkg/SioBusDxe/SioBusDxe.inf
INF MdeModulePkg/Bus/Isa/Ps2KeyboardDxe/Ps2KeyboardDxe.inf
!endif

# Rules have to be at the end, always.
[RULE.COMMON.USER_DEFINED]
  FILE FREEFORM = $(NAMED_GUID) {
    RAW BIN                |.crt
    RAW BIN                |.bin
  }

[RULE.COMMON.USER_DEFINED.BINARY]
  FILE FREEFORM = $(NAMED_GUID) {
    RAW BIN                |.crt
    RAW BIN                |.bin
    UI       STRING="$(MODULE_NAME)" Optional
  }
