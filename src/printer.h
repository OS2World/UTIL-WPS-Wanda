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

#ifndef _PRINTER_H_
#define _PRINTER_H_

#include "wanda.h"
#include "settings.h"

// ** classdef ************************************************************

class Printer
{
public:
    Printer (class Notelist *pnl) { this->pnl = pnl; }

    BOOL   Dialog (VOID);

    BOOL PrintToDevice (VOID) {
        return BOOL (pset->QueryLong (SEI_PRINTSTYLE) == PS_TODEVICE); }
    PSZ QueryFilename (VOID) {
        return pset->QueryString (SEI_PRINTFILENAME); }

    PSZ QueryDevicename (VOID)
    {
        switch (pset->QueryLong (SEI_PRINTDEVICE))
        {
        case PDEV_PRN:   return "PRN";
        case PDEV_LPT1:  return "LPT1";
        case PDEV_LPT2:  return "LPT2";
        case PDEV_LPT3:  return "LPT3";
        case PDEV_NUL:   return "NUL";
        }
        return "";
    }

    BOOL  SelectFile (VOID);

    FILE *OpenOutput (VOID);
    BOOL  OutputNote (FILE *pf, class Note *pn);
    VOID  CloseOutput (FILE *pf) { if (pf) fclose (pf); }

private:
    static MRESULT EXPENTRY dp (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

    Notelist  *pnl;
    HWND  hwndDlg;
};

#include "note.h"

// ************************************************************************
#endif
