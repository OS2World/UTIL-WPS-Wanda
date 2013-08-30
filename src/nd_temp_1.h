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

#ifndef _ND_TEMP_1_H_
#define _ND_TEMP_1_H_

#include "nd_temp.h"

struct NoteDisplayTemplateData_1
{
    SWP    swp;
    USHORT x, y, cx, cy;

    COLOR  color, colorFG;
    CHAR   ach[CB_FONTNAMESIZE];

    BOOL   fTitlebar, fVertSB, fHorizSB, fWordwrap;
    BOOL   fMinimized, fAutohide, fAutosize, fTasklist;
};

class NoteDisplayTemplate_1 : public NoteDisplayTemplate
{
    friend class NoteDisplay_1;

private:
    SWP    swp;
    USHORT x, y, cx, cy;

    COLOR  color, colorFG;
    CHAR   ach[CB_FONTNAMESIZE];

    BOOL   fTitlebar, fVertSB, fHorizSB, fWordwrap;
    BOOL   fMinimized, fAutohide, fAutosize, fTasklist;

public:
    NoteDisplayTemplate_1 (VOID) { Init(); }
    NoteDisplayTemplate_1 (FILE *pf) { Init(); Load(pf); }
    NoteDisplayTemplate_1 (PVOID pv);

    BOOL   Load (FILE *pf);
    BOOL   Save (FILE *pf);

    USHORT Type (VOID) { return 1; }
    PVOID  Flatten (size_t &size);

protected:
    VOID   Init (VOID);
};

#endif
