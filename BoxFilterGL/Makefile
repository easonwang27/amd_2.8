DEPTH = ../../../../..

include $(DEPTH)/make/openclsdkdefs.mk 

####
#
#  Targets
#
####

OPENCL			= 1
SAMPLE_EXE		= 1
EXE_TARGET 		= BoxFilterGL
EXE_TARGET_INSTALL   	= BoxFilterGL

####
#
#  C/CPP files
#
####

FILES 	= BoxFilterGL BoxFilterGLSeparable BoxFilterGLSAT
CLFILES = BoxFilterGL_Kernels.cl
IMAGES	= BoxFilterGL_Input.bmp

LLIBS  += SDKUtil

SUSEOS := $(shell lsb_release -a)
ifeq ($(findstring openSUSE, $(SUSEOS)), openSUSE)
LDFLAGS += -lX11
endif

ifeq ($(OS),lnx)
ifdef MINGW
	LLIBS += glew$(BITS).dll glut$(BITS) opengl32 glu32 gdi32
else
	LLIBS += glut GLEW GL GLU
endif
else
	LLIBS += glut$(BITS) GLEW$(BITS)
	LLIBS  += kernel32 gdi32 user32 advapi32 Shlwapi
endif

include $(DEPTH)/make/openclsdkrules.mk 

