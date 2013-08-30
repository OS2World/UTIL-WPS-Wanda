#
# Wanda makefile for DMAKE 4.0 / emx 0.9d
#

# set this to something if debug version should be created
DEBUG  = 

# adjust this as desired/required
CFLAGS = -g -Wall -fno-exceptions -fno-rtti
CC     = gcc $(CFLAGS)
I      = e:/prog/emx/include/

# where the various files are (to be) kept; no trailing slashes please!
SRC    = src
TMP    = tmp
OUT    = out
DATA   = $(SRC)/data

# -------------------------------------------------------------------------

.IF $(DEBUG)
    o=o
    $(TMP)/%.$(o) : $(SRC)/%.cpp $(SRC)/%.h ; $(CC) -o $@ -c $<
.ELSE
    o=obj
    $(TMP)/%.$(o) : $(SRC)/%.cpp $(SRC)/%.h ; $(CC) -o $@ -Zomf -Zsys -O2 -c $<
.END

# -- 'big' targes ---------------------------------------------------------

default:      all
all:          wanda $(OUT)/wanda.inf

distr .IGNORE:        all
	copy "$(OUT)\*.inf" "distr"
	copy "$(OUT)\*.dll" "distr"
	copy "$(OUT)\*.hlp" "distr"
	copy "$(OUT)\*.exe" "distr"
	del "distr\*~"

wanda:        $(OUT)/wanda.exe

# -- 'small' targets ------------------------------------------------------

$(OUT)/wanda.exe:       $(TMP)/wanda.$(o) \
                        $(TMP)/wanda.res \
                        $(SRC)/wanda.def \
                        $(TMP)/about.$(o) \
                        $(TMP)/finder.$(o) \
                        $(TMP)/nd_fact.$(o) \
                        $(TMP)/nd_temp_1.$(o) \
                        $(TMP)/nld_fact.$(o) \
                        $(TMP)/nldisp_1.$(o) \
                        $(TMP)/note.$(o) \
                        $(TMP)/notedisp_1.$(o) \
                        $(TMP)/notelist.$(o) \
                        $(TMP)/printer.$(o) \
                        $(TMP)/tasklist.$(o) \
                        $(TMP)/log.$(o)
.IF $(DEBUG)
	$(CC) -o $(OUT)/wanda -Zmt -lstdcpp $(TMP)/*.$(o) $(TMP)/*.res \
                 $(SRC)/wanda.def
	emxbind -bpq e:/prog/emx/bin/emxl $(OUT)/wanda
# FIXME the above is probably totally wrong now ...
.ELSE
	$(CC) -o $(OUT)/wanda.exe -Zomf -Zsys -Zmt -s -lstdcpp $<
.END

$(TMP)/wanda.res:       $(SRC)/wanda.rc \
			$(SRC)/id.h \
			$(SRC)/version.h \
			$(DATA)/wanda.ico
	rc -i $I -i $(SRC) -cc 1 -cp 850 -r $(SRC)/wanda.rc $@

# -- language ressources --------------------------------------------------

$(OUT)/wanda.inf:       $(SRC)/wanda.ipf $(DATA)/teamlogo.bmp \
                        $(DATA)/ace.bmp $(DATA)/wanda.bmp
	ipfc -i /D:001 /C:850 $(SRC)/wanda.ipf $@

# -------------------------------------------------------------------------
