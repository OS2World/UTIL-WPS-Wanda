-- WANDA 1.10 --

 Wanda is a program that allows you to create lots of little "sticky
notes" on your OS/2 desktop, in which you can write down all kinds of
valuable (or not so ...) information.

 Since v1.10, Wanda is free software released under the GPL. See the
file COPYING for details.


-- INSTALLATION --

 If you've unzipped the archiv (which seems to be the case, since you
are reading this file ;-) and copied the files to some appropriate
directory, you're done.

 As a normal user, you probably will just need the files from the
"distr" directory.

 You may run "install.cmd" to create a WPS-object for Wanda.


-- BUILDING --

  Wanda was originally developed under OS/2 using emx/gcc 0.9d and
dmake 4.0. I can't say if it would be hard to adjust it for other
compilers or make utilities (though I guess it will need some work to
port it to another OS due to missing seperation of program logic and
system specific issues like e.g. windowing - aka: bad code). If you
want to recompile the program, take a look at the Makefile and adjust
the settings (probably only the "I" macro that tells where you keep
your include files) and then just run dmake.

Oh yes, and you safely may ignore those "cycle detected by make_type" :-)


-- MORE INFO --

For more information see the file "wanda.inf"!

Have fun!
Thorsten Thielen <thth@gmx.net>
(Member of Team OS/2 Region Trier e.V.)
