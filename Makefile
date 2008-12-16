#
# Makefile template:
# vamsi.krishnak@gmail.com ,  June 24,2006.
#
# Note: To build on windows invoke this make file from
# cygwin. Also you need to set the following before you
# build on windows.
# 1. Open the cygwin shell
# 2. Open the file /Cygwin.bat
# 3. Add the following line 
# <--------->
# call "C:\Program Files\Microsoft Visual Studio 9.0\VC\bin\vcvars32.bat"
# <--------->
#
# This sets up the MSVC cl.exe compiler
# 4.set environment variable as "export PF=win32"
# 5.make
#
# Note: To build on solaris, add this directory to the path
# "/opt/sfw/bin"
# 1. If you want to make a 64-bit build , setenv MODE 64
# else a 32-bit build is made by default.
#
#
#
# If you want to build the fast dual update scheme
# build with -DFAST_PRE_ORDER
#
CC = g++ 
LD = g++ 
AR = ar


CPPSRCS = ReadSparse.cpp \
 		Heap.cpp 
#		DoubleHeap.c
#		BipartiteC.c

ifeq ($(USE_ZERO_INDEX),1)
CPPSRCS += Bipartite2.cpp
else
CPPSRCS += Bipartite.cpp
endif

CPPSRCS += MeasureTime.cpp

#
# Solaris specific settings.
#
ifeq ($(PF),sparc)
	CC = CC
	LD = CC
	PROJECT_NAME=bipartite1-sparc32 
	LOCAL_CFLAGS += -library=stlport4 -DSOLARIS=1
	LD_FLAGS += -library=stlport4
ifeq ($(MODE),64)
	LOCAL_CFLAGS += -xarch=v9
	PROJECT_NAME=bipartite1-sparc64 
	LD_FLAGS += -xarch=v9
endif
endif

#
# 64-bit Linux settings
#
ifeq ($(PF),x86_64)
	 LOCAL_CFLAGS += -DSOLARIS=1
	 LD += -DSOLARIS
	 PROJECT_NAME = bipartite1-linux64
endif

#
# Win32 settings
#
ifeq ($(PF),win32)
	LOCAL_CFLAGS += /DSOLARIS=1 /DWIN32=1
	LD += /DSOLARIS=1 /DWIN32=1
	PROJECT_NAME = bipartite1-win32
	CC = cl
	LD = cl
	OBJS = $(CSRCS:.c=.obj)
	OBJS += $(CPPSRCS:.cpp=.obj) 
	else
	OBJS = $(CSRCS:.c=.o)
	OBJS += $(CPPSRCS:.cpp=.o) 
endif


ifeq ($(PF),i686)
	CSRCS += MC64Driver.c
	MC64_LIBPATH= -L/home/kundeti/work/ReorderMatrix/lib/
	DEPEND_INCLUDE += -I/usr/include/linux -I/usr/local/include
	LOCAL_CFLAGS +=  #-ffloat-store #-mfpmath=sse
endif

# Link mathlibrary for non-windows platforms
ifneq ($(PF),win32)
LOCAL_LIBS += -lm 
AR_FLAGS += rc
endif


#Debug and non-debug settingS
ifeq ($(DEBUG),1)
	LOCAL_CFLAGS += -g
    LOCAL_CFLAGS += -DVERBOSE_DEBUG
else

ifeq ($(PF),win32)
	LOCAL_CFLAGS += /O2
else
	LOCAL_CFLAGS +=  -O3
endif

endif

ifeq ($(PROFILE),1)
	LOCAL_CFLAGS += -pg
	LD += -pg
endif



ifeq ($(PF),i686)
LOCAL_LIBS += -lordering
PROJECT_NAME = bipartite1-linux32
endif


ifeq ($(RELEASE),1) 
ifeq ($(PF),win32)
LOCAL_CFLAGS += /DNO_UNIT_TEST=1
else
LOCAL_CFLAGS += -DNO_UNIT_TEST
endif
endif

ifeq ($(STANDALONE),1)

ifeq ($(PF),win32)
LOCAL_CFLAGS += /DSTANDALONE_MODE=1
else
LOCAL_CFLAGS += -DSTANDALONE_MODE
endif

endif

ifeq ($(NO_WARNINGS), 1)
	ifneq ($(PF),win32)
		LOCAL_CFLAGS += -Wall
	endif
endif

#
#
#
ifeq ($(USE_MC21),1)
ifeq ($(PF),win32)
	LOCAL_CFLAGS += /DUSE_MC32=1
	PROJECT_NAME = bipartite1-mc21-win32
else
	LOCAL_CFLAGS += -DUSE_MC21
endif
ifeq ($(PF),i686)
	PROJECT_NAME = bipartite1-mc21-linux32
endif
ifeq ($(PF),sparc)
	PROJECT_NAME = bipartite1-mc21-sparc32
	ifeq ($(MODE),64)
		PROJECT_NAME = bipartite1-mc21-sparc64
	endif
endif
ifeq ($(PF),x86_64)
	PROJECT_NAME = bipartite1-mc21-linux64
endif
ifeq ($(PF),win32)
	PROJECT_NAME = bipartite1-mc21-win32
endif
endif

ifeq ($(PF),win32)
LINK_OUT = /Fe$(PROJECT_NAME)
else
LINK_OUT = -o $(PROJECT_NAME)
endif

ifeq ($(FAST_PRE_ORDER),1)
LOCAL_CFLAGS += -DFAST_PRE_ORDER
LINK_OUT = -o $(PROJECT_NAME)-fast-dual-update
endif

ifeq ($(VERIFY_INTEL_MKL),1)
LOCAL_CFLAGS += -DVERIFY_INTEL_MKL
endif

unit_test_bipartite: $(OBJS)
	@echo "........Linking..$(PROJECT_NAME) ......."	
	$(LD) $(OBJS) $(LINK_OUT) $(MC64_LIBPATH) $(LD_FLAGS) $(LOCAL_LIBS)

unit_test_mc21: $(OBJS)
	@echo ".......Building MC21........"
	$(LD) $(OBJS) -o $(PROJECT_NAME)$(FAST_SUFFIX) -L$(MC64_LIBPATH) $(LOCAL_LIBS) $(LD_FLAGS)

mc64_performance: CreateMC64PermFile.c
	@echo ".........building MC64 Perm generator......."
	$(CC) -o  mc64_program -O3 -DPERFORMANCE_TEST CreateMC64PermFile.c MeasureTime.c -L$(MC64_LIBPATH) $(LOCAL_LIBS)

validate_perm: ValidatePermutation.o ReadSparse.o
	@echo "...........Linking .....validate_perm......"
	$(LD) ValidatePermutation.o ReadSparse.o -o validate_perm -lm

create_m64_perm : CreateMC64PermFile.c 
	@echo ".........building MC64 Perm generator......."
	$(CC) -o  create_perm -O3 CreateMC64PermFile.c MeasureTime.c -L$(MC64_LIBPATH) $(LOCAL_LIBS)


y.tab.c: sp.y sp.h
	yacc -d sp.y

lex.yy.c: in.l
	lex in.l


%.obj : %.cpp
	$(CC) /I. /c $(CFLAGS) $(LOCAL_CFLAGS) $(LAPACK_INCLUDE) $(LOCAL_DEFINES) $<

#Rules to build c files


.c.o:
	$(CC) $(CFLAGS) $(LOCAL_CFLAGS) $(LAPACK_INCLUDE) $(LOCAL_DEFINES) -c $<

.c.obj:
	$(CC) /I. /c $(CFLAGS) $(LOCAL_CFLAGS) $(LAPACK_INCLUDE) $(LOCAL_DEFINES) $<

 
.cpp.o:
	$(CC) $(CFLAGS) $(LOCAL_CFLAGS) $(LAPACK_INCLUDE) $(LOCAL_DEFINES) -c $<

clean:
	find . -name "*.o" -exec rm -rf \{\} \; -print
	find . -name "y.tab.*" -exec rm -rf \{\} \; -print
	find . -name "lex.yy.c" -exec rm -rf \{\} \; -print
	find . -name "sape" -exec rm -rf \{\} \; -print
	find . -name "*.so" -exec rm -rf \{\} \; -print
	find . -name "*.exe" -exec rm -rf \{\} \; -print
	find . -name "*.obj" -exec rm -rf \{\} \; -print




depend: $(SRCS)
	makedepend $(DEPEND_INCLUDE) $(LAPACK_INCLUDE) $(INCLUDES) $^
# DO NOT DELETE
