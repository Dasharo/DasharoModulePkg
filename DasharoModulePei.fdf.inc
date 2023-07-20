## @file
# Dasharo FDF include file for [FV.PEIFV] section.
#
# This file can be included to the [FV.PEIFV] section of a platform FDF file
# by using "!include DasharoModulePkg/DasharoModulePei.fdf.inc" to specify the INFs.
#
# Copyright (c) 2023, 3mdeb Sp. z o.o. All rights reserved.<BR>
# SPDX-License-Identifier: BSD-2-Clause
#
##

!if $(TPM_ENABLE) == TRUE
INF DasharoModulePkg/Tcg2Config/Tcg2ConfigPei.inf
INF SecurityPkg/Tcg/TcgPei/TcgPei.inf
INF SecurityPkg/Tcg/Tcg2Pei/Tcg2Pei.inf
!if $(OPAL_PASSWORD_ENABLE) == TRUE
INF SecurityPkg/Tcg/Opal/OpalPassword/OpalPasswordPei.inf
!endif
!endif

!if $(SATA_PASSWORD_ENABLE) == TRUE
INF SecurityPkg/HddPassword/HddPasswordPei.inf
!endif
