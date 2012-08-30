PROJNAME = luagl
LIBNAME = luagl

OPT=Yes

INCLUDES = ../include .
SRC = luagl.c
DEF_FILE := $(LIBNAME).def

ifdef USE_LUA52
  LUASFX = 52
  DEFINES += LUA_COMPAT_MODULE
else
  LUASFX = 51
  USE_LUA51 = Yes
endif

NO_LUALINK = Yes

ifdef USE_NO_SFX
  LUAMOD_DIR = Yes
  DLIBPRE :=
else
  LIBNAME := $(LIBNAME)$(LUASFX)
endif

LIBS = luagl_base$(LUASFX)
LDIR = ../lib/$(TEC_UNAME)

USE_OPENGL = Yes
USE_MACOS_OPENGL = Yes

ifneq ($(findstring MacOS, $(TEC_UNAME)), )
  ifdef USE_MACOS_OPENGL
    LFLAGS = -framework OpenGL
    USE_OPENGL :=
  endif
endif
