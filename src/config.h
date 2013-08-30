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

// Define these to enable various #ifdef'd features.

//#define _DEBUGLOG_

// Do a little more than basic error checking.
#define _CAUTIOUS_

#ifdef _CAUTIOUS_
#define CAUTIOUS_ERROR   0xfe
#endif

// Do extensive error checking.
#define _PARANOID_

#ifdef _PARANOID_
#define _CAUTIOUS_
#define PARANOID_ERROR   0xff
#endif

// Rename old nld file to another name to it keep as backup before saving.
#define _NOTELISTBACKUP_

// Allow to hide the notelist window's title.
#define DONLDREMOVETITLE

// Enable the find/replace function.
#define _DOFIND_
