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

#include "nld_fact.h"

// ** NotelistDisplayFactory ********************************************** /*FOLD00*/

NotelistDisplayFactory :: NotelistDisplayFactory (VOID)
{
    // get nld-data either from settings or use hardcoded defaults
    if ((nldid = pset->QueryLong(SEI_NLDTYPE))) {
        pv = pset->QueryBinary(SEI_NLDD);
    } else {
        nldid = 1;
        pv = new NotelistDisplayData_1;
    }
}

// ** New ***************************************************************** /*FOLD00*/

NotelistDisplay *NotelistDisplayFactory :: New (Notelist &nl)
{
    NotelistDisplay *pnld;

    switch (nldid)
    {
    case 1:
        pnld = new NotelistDisplay_1(nl, (NotelistDisplayData_1 *)pv);
        break;

    default:
        pnld = new NotelistDisplay_1(nl, (NotelistDisplayData_1 *)pv);
        break;
    }

    return pnld;
}

// ************************************************************************
