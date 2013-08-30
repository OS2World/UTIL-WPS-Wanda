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

#include "nd_fact.h"

NoteDisplayFactory :: NoteDisplayFactory (VOID)
{
    pndt = NULL;

    // get nd-data either from settings or use hardcoded defaults
    switch ((pset->QueryLong(SEI_NDTYPE)))
    {
    case 1:
        Template(new NoteDisplayTemplate_1(pset->QueryBinary(SEI_NDD)));
        break;

    default:
        Template(new NoteDisplayTemplate_1);
        break;
    }
}

// create a notedisplay of the selected type with the current settings /*FOLD00*/
NoteDisplay *NoteDisplayFactory :: New (Note &n, NoteDisplayTemplate *pndt2)
{
    NoteDisplay *pnd = NULL;

    if (! pndt2) {
#ifdef _PARANOID_
        if (!pndt) {
            DisplayError("NoteDisplayFactory::New", "pndt == NULL");
            exit(PARANOID_ERROR);
        }
#endif
        pndt2 = pndt;
    }

    switch (pndt2->Type())
    {
    case 1:  pnd = new NoteDisplay_1(n,(NoteDisplayTemplate_1 *)pndt2); break;
    default: pnd = new NoteDisplay_1(n,(NoteDisplayTemplate_1 *)pndt2); break;
    }

    return pnd;
}

// get type and settings from file and create appropriate notedisplay /*FOLD00*/
NoteDisplay *NoteDisplayFactory :: New (Note &n, FILE *pf)
{
#ifdef _PARANOID_
    if (!pf) {
        DisplayError("NoteDisplayFactory::New", "pf == NULL");
        exit(PARANOID_ERROR);
    }
#endif

    // get type of display
    USHORT ndid = getc(pf);
    NoteDisplayTemplate *pndt2;

    switch (ndid)
    {
    case 1:   pndt2 = new NoteDisplayTemplate_1(pf);  break;
    default:  pndt2 = new NoteDisplayTemplate_1(pf);  break;
    }

    return New(n, pndt2);
}

VOID NoteDisplayFactory :: Template (NoteDisplayTemplate *pndt)
{
#ifdef _PARANOID_
    if (!pndt) {
        DisplayError("NoteDisplayFactory::Template", "pndt == NULL");
        exit(PARANOID_ERROR);
    }
#endif
    if (this->pndt) delete this->pndt;
    this->pndt = pndt;
    pset->SetLong(SEI_NDTYPE, pndt->Type());
    size_t  size;
    PVOID  pv = pndt->Flatten(size);
    pset->SetBinary(SEI_NDD, pv, size);
}
