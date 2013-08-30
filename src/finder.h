/***
 This file belongs to the Wanda distribution.
 Copyright (C) 1998-2001 Thorsten Thielen <thth@gmx.net>

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ***/

#ifndef _FINDER_H_
#define _FINDER_H_

#include "wanda.h"
#include "settings.h"

const USHORT  CMAX_FINDTEXT = 64;
const USHORT  CMAX_FINDREPLACETEXT = 64;

typedef class Finder FINDER;
typedef FINDER *PFINDER;

// ** classdef ************************************************************

class Finder
{
public:
    Finder (class Notelist *pnl) { this->pnl = pnl; }

    BOOL   Dialog (VOID);

    VOID   EnableDoNext (VOID) {
        WinEnableWindow (WinWindowFromID (hwndDlg, WID_PB_DONEXT), TRUE); }
    VOID   DisableDoNext (VOID) {
        WinEnableWindow (WinWindowFromID (hwndDlg, WID_PB_DONEXT), FALSE); }

private:
    static MRESULT EXPENTRY dp (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

    class Notelist *pnl;
    HWND  hwndDlg;
};

#include "notelist.h"

// ************************************************************************
#endif
