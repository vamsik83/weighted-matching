#
# SAPE: Please add the source files to SRCS
# vamsi.krishnak@gmail.com ,  June 24,2006.
#


CC = gcc
LD = gcc
AR = ar


SRCS = List.c \
	   hash.c \
	   RandQsort.c \
	   InSort.c \
	   Heap.c


LOCAL_LIBS += -lm 

INCLUDES += hash.h \
            List.h \
			RandQsort.h \
			Heap.h
			
DEPEND_INCLUDE += -I/usr/include/linux -I/usr/local/include
		
AR_FLAGS += rc
OBJS = $(SRCS:.c=.o)

ifeq ($(DEBUG),1)
	LOCAL_CFLAGS += -g
    LOCAL_CFLAGS += -DVERBOSE_DEBUG
else
	LOCAL_CFLAGS +=  -O2 
endif

LOCAL_CFLAGS += -DNO_UNIT_TEST

ifeq ($(NO_WARNINGS), 1)
	LOCAL_CFLAGS += -Wall
endif

MYUTIL_STATIC = libmyutil.a
MYUTIL_DYNAMIC = libmyutil.so

myutil_static: $(OBJS)
	@echo "........Building myutil.a........"	
	$(AR) $(AR_FLAGS) $(MYUTIL_STATIC)  $(OBJS)

myutil_dynamic: $(OBJS)
	@echo "........Building myutil.so......."
	$(CC) --shared -o $(MYUTIL_DYNAMIC) $(OBJS)

y.tab.c: sp.y sp.h
	yacc -d sp.y

lex.yy.c: in.l
	lex in.l

#Rules to build c files
.c.o:
	$(CC) $(CFLAGS) $(LOCAL_CFLAGS) $(LAPACK_INCLUDE) $(LOCAL_DEFINES) -c $<

clean:
	find . -name "*.o" -exec rm -rf \{\} \; -print
	find . -name "y.tab.*" -exec rm -rf \{\} \; -print
	find . -name "lex.yy.c" -exec rm -rf \{\} \; -print
	find . -name "sape" -exec rm -rf \{\} \; -print
	find . -name "*.so" -exec rm -rf \{\} \; -print


depend: $(SRCS)
	makedepend $(DEPEND_INCLUDE) $(LAPACK_INCLUDE) $(INCLUDES) $^
# DO NOT DELETE

hash.o: /usr/include/stdlib.h /usr/include/features.h
hash.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
hash.o: /usr/include/linux/stddef.h
RandQsort.o: /usr/include/stdio.h /usr/include/features.h
RandQsort.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
RandQsort.o: /usr/include/linux/stddef.h /usr/include/bits/types.h
RandQsort.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
RandQsort.o: /usr/include/libio.h /usr/include/_G_config.h
RandQsort.o: /usr/include/wchar.h /usr/include/bits/wchar.h
RandQsort.o: /usr/include/gconv.h
RandQsort.o: /usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stdarg.h
RandQsort.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
RandQsort.o: /usr/include/linux/malloc.h /usr/include/linux/slab.h
RandQsort.o: /usr/include/assert.h
List.o: List.h /usr/include/stdlib.h /usr/include/features.h
List.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
List.o: /usr/include/linux/stddef.h /usr/include/linux/malloc.h
List.o: /usr/include/linux/slab.h /usr/include/stdio.h
List.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
List.o: /usr/include/bits/typesizes.h /usr/include/libio.h
List.o: /usr/include/_G_config.h /usr/include/wchar.h
List.o: /usr/include/bits/wchar.h /usr/include/gconv.h
List.o: /usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stdarg.h
List.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
List.o: /usr/include/assert.h
hash.o: /usr/include/strings.h /usr/include/features.h
hash.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
hash.o: /usr/include/linux/stddef.h /usr/include/stdlib.h
hash.o: /usr/include/assert.h /usr/include/linux/string.h
hash.o: /usr/include/stdio.h /usr/include/bits/types.h
hash.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
hash.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
hash.o: /usr/include/bits/wchar.h /usr/include/gconv.h
hash.o: /usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stdarg.h
hash.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h hash.h
RandQsort.o: /usr/include/stdlib.h /usr/include/features.h
RandQsort.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
RandQsort.o: /usr/include/linux/stddef.h /usr/include/stdio.h
RandQsort.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
RandQsort.o: /usr/include/bits/typesizes.h /usr/include/libio.h
RandQsort.o: /usr/include/_G_config.h /usr/include/wchar.h
RandQsort.o: /usr/include/bits/wchar.h /usr/include/gconv.h
RandQsort.o: /usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stdarg.h
RandQsort.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
RandQsort.o: /usr/include/linux/time.h /usr/include/asm/param.h
RandQsort.o: /usr/include/linux/types.h /usr/include/linux/posix_types.h
RandQsort.o: /usr/include/linux/stddef.h /usr/include/asm/posix_types.h
RandQsort.o: /usr/include/asm/types.h /usr/include/assert.h
RandQsort.o: /usr/include/linux/string.h /usr/include/math.h
RandQsort.o: /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
RandQsort.o: /usr/include/bits/mathcalls.h RandQsort.h
RandQsort.o: /usr/include/linux/malloc.h /usr/include/linux/slab.h
InSort.o: /usr/include/stdio.h /usr/include/features.h
InSort.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
InSort.o: /usr/include/linux/stddef.h /usr/include/bits/types.h
InSort.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
InSort.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
InSort.o: /usr/include/bits/wchar.h /usr/include/gconv.h
InSort.o: /usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stdarg.h
InSort.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
InSort.o: /usr/include/stdlib.h /usr/include/assert.h
Heap.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
Heap.o: /usr/include/gnu/stubs.h /usr/include/linux/stddef.h
Heap.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
Heap.o: /usr/include/bits/typesizes.h /usr/include/libio.h
Heap.o: /usr/include/_G_config.h /usr/include/wchar.h
Heap.o: /usr/include/bits/wchar.h /usr/include/gconv.h
Heap.o: /usr/lib/gcc-lib/i386-redhat-linux/3.2.3/include/stdarg.h
Heap.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
Heap.o: /usr/include/stdlib.h /usr/include/assert.h
Heap.o: /usr/include/linux/string.h Heap.h
