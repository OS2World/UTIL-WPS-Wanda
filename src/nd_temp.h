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

#ifndef _ND_TEMP_H_
#define _ND_TEMP_H_

#include "wanda.h"

class NoteDisplayTemplate
{
public:
    virtual BOOL   Load (FILE *pf) = 0;
    virtual BOOL   Save (FILE *pf) = 0;

    virtual USHORT Type (VOID) = 0;
    virtual PVOID  Flatten (size_t &size) = 0;
};

#endif
