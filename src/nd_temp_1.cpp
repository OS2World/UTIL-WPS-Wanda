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

#include "nd_temp_1.h"

// ** Init **************************************************************** /*FOLD00*/

VOID NoteDisplayTemplate_1 :: Init (VOID)
{
    swp.x = swp.y = x = y = 300;
    swp.cx = swp.cy = cx = cy = 100;
    swp.hwnd = HWND_DESKTOP;
    swp.fl = SWP_SHOW|SWP_MOVE|SWP_SIZE;

    color = 0x00ffffdd;
    colorFG = 0x00000000;

    strcpy(ach, "8.Helv");

    fTitlebar = fWordwrap = fTasklist = TRUE;
    fMinimized = fVertSB = fHorizSB = fAutosize = fAutohide = FALSE;
}

// ** NoteDisplayTemplate_1 *********************************************** /*FOLD00*/

NoteDisplayTemplate_1 :: NoteDisplayTemplate_1 (PVOID pv)
{
#ifdef _PARANOID_
    if (!pv) {
        DisplayError("NoteDisplayTemplate_1", "pv == NULL");
        exit(PARANOID_ERROR);
    }
#endif

    NoteDisplayTemplateData_1 *pndtd = (NoteDisplayTemplateData_1 *)pv;

    swp.x  = pndtd->swp.x;
    swp.y  = pndtd->swp.y;
    swp.cx = pndtd->swp.cx;
    swp.cy = pndtd->swp.cy;

    fMinimized = pndtd->fMinimized;

    x  = pndtd->x;
    y  = pndtd->y;
    cx = pndtd->cx;
    cy = pndtd->cy;

    fTitlebar = pndtd->fTitlebar;
    fVertSB   = pndtd->fVertSB;
    fHorizSB  = pndtd->fHorizSB;
    fWordwrap = pndtd->fWordwrap;
    fAutohide = pndtd->fAutohide;
    fAutosize = pndtd->fAutosize;
    fTasklist = pndtd->fTasklist;

    color   = pndtd->color;
    colorFG = pndtd->colorFG;

    strcpy(ach, pndtd->ach);
}

// ** Load **************************************************************** /*FOLD00*/

BOOL NoteDisplayTemplate_1 :: Load (FILE *pf)
{
#ifdef _PARANOID_
    if (!pf) {
        DisplayError("NoteDisplayTemplate_1::Load", "pf == NULL");
        exit(PARANOID_ERROR);
    }
#endif

    // Type will already have been red by calling function!

    fread (&(swp.x), sizeof (swp.x), 1, pf);
    fread (&(swp.y), sizeof (swp.y), 1, pf);
    fread (&(swp.cx), sizeof (swp.cx), 1, pf);
    fread (&(swp.cy), sizeof (swp.cy), 1, pf);

    fread (&fMinimized, sizeof(fMinimized), 1, pf);
    fread (&x, sizeof(x), 1, pf);
    fread (&y, sizeof(y), 1, pf);
    fread (&cx, sizeof(cx), 1, pf);
    fread (&cy, sizeof(cy), 1, pf);

    fread (&fTitlebar, sizeof(fTitlebar), 1, pf);
    fread (&fVertSB, sizeof(fVertSB), 1, pf);
    fread (&fHorizSB, sizeof(fHorizSB), 1, pf);
    fread (&fWordwrap, sizeof(fWordwrap), 1, pf);
    fread (&fAutohide, sizeof(fAutohide), 1, pf);
    fread (&fAutosize, sizeof(fAutosize), 1, pf);
    fread (&fTasklist, sizeof(fTasklist), 1, pf);

    fread (&color, sizeof(color), 1, pf);
    fread (&colorFG, sizeof(colorFG), 1, pf);

    USHORT  us;
    fread (&us, sizeof(us), 1, pf);
    fread (ach, us, 1, pf);
    ach[us] = '\0';

    return TRUE;
}

// ** Save **************************************************************** /*FOLD00*/

BOOL NoteDisplayTemplate_1 :: Save (FILE *pf)
{
#ifdef _PARANOID_
    if (!pf) {
        DisplayError("NoteDisplayTemplate_1::Save", "pf == NULL");
        exit(PARANOID_ERROR);
    }
#endif

    WRITE_NDID(Type(), pf);

    fwrite (&(swp.x), sizeof(swp.x), 1, pf);
    fwrite (&(swp.y), sizeof(swp.y), 1, pf);
    fwrite (&(swp.cx), sizeof(swp.cx), 1, pf);
    fwrite (&(swp.cy), sizeof(swp.cy), 1, pf);

    fwrite (&fMinimized, sizeof(fMinimized), 1, pf);
    fwrite (&x, sizeof(x), 1, pf);
    fwrite (&y, sizeof(y), 1, pf);
    fwrite (&cx, sizeof(cx), 1, pf);
    fwrite (&cy, sizeof(cy), 1, pf);

    fwrite (&fTitlebar, sizeof(fTitlebar), 1, pf);
    fwrite (&fVertSB, sizeof(fVertSB), 1, pf);
    fwrite (&fHorizSB, sizeof(fHorizSB), 1, pf);
    fwrite (&fWordwrap, sizeof(fWordwrap), 1, pf);
    fwrite (&fAutohide, sizeof(fAutohide), 1, pf);
    fwrite (&fAutosize, sizeof(fAutosize), 1, pf);
    fwrite (&fTasklist, sizeof(fTasklist), 1, pf);

    fwrite (&color, sizeof(color), 1, pf);
    fwrite (&colorFG, sizeof(colorFG), 1, pf);

    USHORT  us = strlen (ach);
    fwrite (&us, sizeof(us), 1, pf);
    fwrite (ach, us, 1, pf);

    return TRUE;
}

// ************************************************************************

PVOID NoteDisplayTemplate_1 :: Flatten (size_t &size)
{
    struct NoteDisplayTemplateData_1 *pndtd = new NoteDisplayTemplateData_1;

    pndtd->swp.x  = swp.x;
    pndtd->swp.y  = swp.y;
    pndtd->swp.cx = swp.cx;
    pndtd->swp.cy = swp.cy;

    pndtd->fMinimized = fMinimized;

    pndtd->x  = x;
    pndtd->y  = y;
    pndtd->cx = cx;
    pndtd->cy = cy;

    pndtd->fTitlebar = fTitlebar;
    pndtd->fVertSB   = fVertSB;
    pndtd->fHorizSB  = fHorizSB;
    pndtd->fWordwrap = fWordwrap;
    pndtd->fAutohide = fAutohide;
    pndtd->fAutosize = fAutosize;
    pndtd->fTasklist = fTasklist;

    pndtd->color   = color;
    pndtd->colorFG = colorFG;

    strcpy(pndtd->ach, ach);

    size = sizeof(*pndtd);
    return pndtd;
}

// ************************************************************************
