/*************************************************************************/
/*  Wanda installation file - Creates a WPS-object for Wanda             */
/*  To run this file, just type "install" on the OS/2 command line.      */
/*************************************************************************/

PARSE SOURCE operSystem . sourceFile

IF \(operSystem = "OS/2") THEN DO
    SAY "Please use only with IBM-OS/2 Operating system!"
    EXIT
    END

/*************************************************************************/

'@ECHO OFF'

CALL rxfuncadd 'sysloadfuncs', 'rexxutil', 'sysloadfuncs'
CALL sysloadfuncs

/*************************************************************************/

Ver = "1.10"
WandaDir = FILESPEC("drive", sourceFile)FILESPEC("path", sourceFile)

SAY ""

/*************************************************************************/

CALL SysFileTree WandaDir"WANDA.EXE",'file','F'
IF file.0 = 0 THEN DO
    SAY "WANDA.EXE was not found in the same directory as ",
    FILESPEC("name",sourceFile)

    DO UNTIL \(file.0 = 0)
        SAY ""
        SAY "Please give the full path to the file WANDA.EXE."
        SAY "(Press ENTER/RETURN alone to exit)"
        PULL WandaDir
        IF WandaDir = "" THEN
            EXIT
        IF (FILESPEC("drive",WandaDir) = "") | (FILESPEC("path",WandaDir) = "") THEN
            SAY 'You must give a full path in format "d:\path\"'
        ELSE DO
            IF \(SUBSTR(WandaDir,length(WandaDir),1) = "\" ) THEN
                WandaDir = WandaDir"\"
            CALL SysFileTree WandaDir"WANDA.EXE",'file','F'
            IF file.0 = 0 THEN
                SAY "Can not find "WandaDir"WANDA.EXE. Please try again."
            END
        END
    SAY ""
    END

/*************************************************************************/

setup = 'PROGTYPE=PM;EXENAME='WandaDir'Wanda.EXE;STARTUPDIR='WandaDir';'
setup = setup'OBJECTID=<THTH_WANDA>;'

SAY ""
SAY "* Creating Wanda WPS-object ..."
check = SysCreateObject('WPProgram', 'Wanda 'Ver, '<WP_DESKTOP>', setup)

IF check = 0 THEN DO
    SAY "* Could not create WPS-object!"
    SAY "  (Does perhaps an object for Wanda already exist?)"
    CALL CHAROUT , "* Do you want to replace the existing object [Y/N] ? "
    key = SysGetKey('ECHO')
    PARSE upper var key key
    SAY ""
    IF key <> 'Y' THEN
        EXIT

    SAY "* Replacing old Wanda WPS-object ..."
    check = SysCreateObject('WPProgram','Wanda 'Ver,'<WP_DESKTOP>',setup,"r")

    IF check = 0 THEN DO
        SAY ""
        SAY "* Sorry, object-creation failed again. Aborting ..."
        EXIT
        END
    ELSE DO
        SAY ""
        SAY "* Old Wanda WPS-object replaced successfully!"
        END
    END
ELSE DO
    SAY ""
    SAY "* Wanda WPS-object created successfully!"
    END

/*************************************************************************/

SAY ""
SAY "* See WANDA.INF for more information about Wanda!"
SAY ""

/*************************************************************************/

EXIT
