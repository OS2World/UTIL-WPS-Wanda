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

#ifndef _ND_FACT_H_
#define _ND_FACT_H_

#include "notedisp.h"
#include "nd_temp.h"

#include "nld_fact.h"

#include "notedisp_1.h"

class NoteDisplayFactory
{
    friend class Notelist;

public:
    static NoteDisplayFactory *Instance (VOID) {
        if (! pndf) { pndf = new NoteDisplayFactory; }
        return pndf;
    }

    VOID Template (NoteDisplayTemplate *pndt);

protected:
    NoteDisplay *New (Note &n, NoteDisplayTemplate *pndt2 = NULL);
    NoteDisplay *New (Note &n, FILE *pf);

    NoteDisplayFactory (VOID);

private:
    static NoteDisplayFactory *pndf;

    NoteDisplayTemplate *pndt;
};

#endif
