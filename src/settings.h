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

#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include "wanda.h"
#include "thth/thth_settings.h"

class Settings : public ththSettings
{
public:
    Settings (PTHTH_SE apse[]) : ththSettings (apse, "wanda.ini", 2L)
    {}

    BOOL   Dialog (VOID);

protected:
    USHORT VersionError (VOID) {
        DisplayError ("INI-FILE VERSION ERROR",
                      "The INI-file's (\"%s\") version does not match the current "
                      "version of Wanda. Defaults will be used.",
                      QueryProfileName ());
        return 0;
    }

    USHORT FileNotOpenError (VOID)
    {
        DisplayError ("INI-FILE OPENING ERROR",
                      "The INI-file (\"%s\") could not be opened! "
                      "Defaults will be used.",
                      QueryProfileName ());
        return 0;
    }
};

#endif
