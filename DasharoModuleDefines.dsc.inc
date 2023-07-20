## @file
# Dasharo DSC include file for [Defines] section.
#
# This file can be included to the [Defines] section(s) of a platform DSC file
# by using "!include DasharoModulePkg/DasharoModuleDefines.dsc.inc" to specify the DEFINEs.
#
# Copyright (c) 2023, 3mdeb Sp. z o.o. All rights reserved.<BR>
# SPDX-License-Identifier: BSD-2-Clause
#
##

  #
  # Security options:
  #
  DEFINE SECURE_BOOT_ENABLE             = FALSE
  DEFINE TPM_ENABLE                     = TRUE
  DEFINE BOOT_MENU_KEY                  = 0x0016
  DEFINE SETUP_MENU_KEY                 = 0x0017
  DEFINE SATA_PASSWORD_ENABLE           = FALSE
  DEFINE OPAL_PASSWORD_ENABLE           = FALSE
  DEFINE LOAD_OPTION_ROMS               = TRUE
  DEFINE DASHARO_SYSTEM_FEATURES_ENABLE = FALSE
  DEFINE USE_CBMEM_FOR_CONSOLE          = FALSE
  DEFINE SYSTEM76_EC_LOGGING            = FALSE
  DEFINE ABOVE_4G_MEMORY                = TRUE
  DEFINE DISABLE_MTRR_PROGRAMMING       = TRUE
  DEFINE IOMMU_ENABLE                   = FALSE
  DEFINE SETUP_PASSWORD_ENABLE          = FALSE
  DEFINE SD_MMC_TIMEOUT                 = 1000000
  DEFINE BATTERY_CHECK                  = FALSE
  DEFINE PERFORMANCE_MEASUREMENT_ENABLE = FALSE
  DEFINE RAM_DISK_ENABLE                = FALSE
  #
  # Serial port set up
  #
  DEFINE UART_DEFAULT_BAUD_RATE         = $(BAUD_RATE)
  DEFINE UART_DEFAULT_DATA_BITS         = 8
  DEFINE UART_DEFAULT_PARITY            = 1
  DEFINE UART_DEFAULT_STOP_BITS         = 1
  DEFINE DEFAULT_TERMINAL_TYPE          = 4

  # Enabling the serial terminal will slow down the boot menu redering!
  DEFINE SERIAL_TERMINAL              = FALSE

  DEFINE PLATFORM_BOOT_TIMEOUT        = 5

  #
  # Network definition
  #
  DEFINE NETWORK_PXE_BOOT               = FALSE
  DEFINE NETWORK_ENABLE                 = FALSE
  DEFINE NETWORK_TLS_ENABLE             = FALSE
  DEFINE NETWORK_IP6_ENABLE             = FALSE
  DEFINE NETWORK_IP4_ENABLE             = TRUE
  DEFINE NETWORK_LAN_ROM                = FALSE

!if $(NETWORK_PXE_BOOT) == TRUE
  DEFINE NETWORK_SNP_ENABLE             = TRUE
  DEFINE NETWORK_HTTP_BOOT_ENABLE       = FALSE
  DEFINE NETWORK_ISCSI_ENABLE           = FALSE
!else
  DEFINE NETWORK_SNP_ENABLE             = FALSE
  DEFINE NETWORK_HTTP_BOOT_ENABLE       = TRUE
  DEFINE NETWORK_ALLOW_HTTP_CONNECTIONS = TRUE
  DEFINE NETWORK_ISCSI_ENABLE           = TRUE
!endif

!include NetworkPkg/NetworkDefines.dsc.inc
  #
  # IPXE support
  #
  DEFINE NETWORK_IPXE                   = FALSE

  # For recent X86 CPU, 0x15 CPUID instruction will return Time Stamp Counter Frequence.
  # This is how BaseCpuTimerLib works, and a recommended way to get Frequence, so set the default value as TRUE.
  # Note: for emulation platform such as QEMU, this may not work and should set it as FALSE
  DEFINE CPU_TIMER_LIB_ENABLE  = TRUE

  DEFINE VARIABLE_SUPPORT               = SMMSTORE
