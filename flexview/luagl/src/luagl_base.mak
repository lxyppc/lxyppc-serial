PROJNAME = luagl
LIBNAME = luagl_base

OPT=Yes

SRC = luagl_util.c luagl_const.c
DEF_FILE := $(LIBNAME).def

ifdef USE_LUA52
  LUASFX = 52
  DEFINES += LUA_COMPAT_MODULE
else
  LUASFX = 51
  USE_LUA51 = Yes
endif

LIBNAME := $(LIBNAME)$(LUASFX)
NO_LUALINK = Yes

ifneq ($(findstring MacOS, $(TEC_UNAME)), )
  ifneq ($(TEC_SYSMINOR), 4)
    BUILD_DYLIB=Yes
  endif
endif
