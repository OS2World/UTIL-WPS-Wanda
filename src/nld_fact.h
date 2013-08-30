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

#ifndef _NLD_FACT_H_
#define _NLD_FACT_H_

#include "nldisp.h"
#include "nldisp_1.h"

class NotelistDisplayFactory
{
public:
    static NotelistDisplayFactory *Instance (VOID) {
        if (! pnldf) { pnldf = new NotelistDisplayFactory; }
        return pnldf;
    }

    NotelistDisplay *New (Notelist &nl);

private:
    NotelistDisplayFactory (VOID);

    USHORT nldid;
    PVOID  pv;

    static NotelistDisplayFactory *pnldf;
};

#endif
