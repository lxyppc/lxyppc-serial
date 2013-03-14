
# To compile on SunOS: add "-lsocket -lnsl" to LDFLAGS
# To compile on MinGW: add "-lws2_32" to LDFLAGS or define WINDOWS in your env
# To compile with PKCS11: add "-lpkcs11-helper" to LDFLAGS

CFLAGS	+= -I../include -D_FILE_OFFSET_BITS=64 -Wall -W -Wdeclaration-after-statement \
			-Wno-unused-function -Wno-unused-value

OFLAGS	= -O2
LDFLAGS	+= -L../library -lpolarssl $(SYS_LDFLAGS)

ifdef DEBUG
CFLAGS += -g3
endif

ifdef WINDOWS
LDFLAGS += -lws2_32
endif

# Zlib shared library extensions:
ifdef ZLIB
LDFLAGS += -lz
endif

APPS =	test

.SILENT:

all: $(APPS)

test: test.c ../library/libpolarssl.a
	echo   "  CC    	$@.c"
	$(CC) $(CFLAGS) $(OFLAGS) $@.c	$(LDFLAGS) -o $@

clean:
ifndef WINDOWS
	rm -f $(APPS) *.o
endif
ifdef WINDOWS
	del /Q /F *.o *.exe
endif

check: $(APPS)
ifndef WINDOWS
	echo "Running checks (Success if all tests PASSED)"	
	RETURN=0;																\
	for i in $(APPS);														\
	do																		\
		echo " - $${i}";													\
		RESULT=`./$${i} | grep -v 'PASS$$' | grep -v -- '-----' | grep -v '^$$'`;	\
		FAILED=`echo $$RESULT |grep FAILED`; 								\
		echo "   $$RESULT";													\
		if [ "$$FAILED" != "" ];											\
		then																\
			echo "**** Failed ***************";								\
			RETURN=1;														\
		fi; 																\
		echo "";															\
	done;																	\
	if [ "$$RETURN" -eq 1 ]; then exit 1; fi
endif
