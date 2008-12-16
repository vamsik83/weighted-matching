# 1 "MeasureTime.c"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "MeasureTime.c"



# 1 "/usr/include/sys/times.h" 1 3 4
# 11 "/usr/include/sys/times.h" 3 4
#pragma ident "@(#)times.h	1.10	97/08/12 SMI" 

# 1 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 1 3 4
# 25 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 3 4
#pragma ident "@(#)types.h	1.66	00/02/14 SMI"

# 1 "/usr/include/sys/isa_defs.h" 1 3 4
# 9 "/usr/include/sys/isa_defs.h" 3 4
#pragma ident "@(#)isa_defs.h	1.20	99/05/04 SMI"
# 28 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 2 3 4
# 1 "/usr/include/sys/feature_tests.h" 1 3 4
# 13 "/usr/include/sys/feature_tests.h" 3 4
#pragma ident "@(#)feature_tests.h	1.18	99/07/26 SMI"
# 29 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 2 3 4




# 1 "/usr/include/sys/machtypes.h" 1 3 4
# 16 "/usr/include/sys/machtypes.h" 3 4
#pragma ident "@(#)machtypes.h	1.13	99/05/04 SMI"
# 33 "/usr/include/sys/machtypes.h" 3 4
typedef struct _label_t { long val[2]; } label_t;



typedef unsigned char lock_t;
# 34 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 2 3 4
# 45 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 3 4
# 1 "/usr/include/sys/int_types.h" 1 3 4
# 9 "/usr/include/sys/int_types.h" 3 4
#pragma ident "@(#)int_types.h	1.6	97/08/20 SMI"
# 62 "/usr/include/sys/int_types.h" 3 4
typedef char int8_t;





typedef short int16_t;
typedef int int32_t;




typedef long long int64_t;



typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;




typedef unsigned long long uint64_t;
# 94 "/usr/include/sys/int_types.h" 3 4
typedef int64_t intmax_t;
typedef uint64_t uintmax_t;
# 110 "/usr/include/sys/int_types.h" 3 4
typedef int intptr_t;
typedef unsigned int uintptr_t;







typedef char int_least8_t;





typedef short int_least16_t;
typedef int int_least32_t;




typedef long long int_least64_t;



typedef unsigned char uint_least8_t;
typedef unsigned short uint_least16_t;
typedef unsigned int uint_least32_t;




typedef unsigned long long uint_least64_t;
# 46 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 2 3 4
# 62 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 3 4
typedef long long longlong_t;
typedef unsigned long long u_longlong_t;
# 85 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 3 4
typedef long t_scalar_t;
typedef unsigned long t_uscalar_t;





typedef unsigned char uchar_t;
typedef unsigned short ushort_t;
typedef unsigned int uint_t;
typedef unsigned long ulong_t;

typedef char *caddr_t;
typedef long daddr_t;
typedef short cnt_t;


typedef ulong_t paddr_t;
# 118 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 3 4
typedef int ptrdiff_t;
# 127 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 3 4
typedef ulong_t pfn_t;
typedef ulong_t pgcnt_t;
typedef long spgcnt_t;

typedef uchar_t use_t;
typedef short sysid_t;
typedef short index_t;
typedef void *timeout_id_t;
typedef void *bufcall_id_t;
# 149 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 3 4
typedef long off_t;
# 158 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 3 4
typedef longlong_t off64_t;






typedef ulong_t ino_t;
typedef long blkcnt_t;
typedef ulong_t fsblkcnt_t;
typedef ulong_t fsfilcnt_t;
# 183 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 3 4
typedef u_longlong_t ino64_t;
typedef longlong_t blkcnt64_t;
typedef u_longlong_t fsblkcnt64_t;
typedef u_longlong_t fsfilcnt64_t;






typedef long blksize_t;





typedef enum { B_FALSE, B_TRUE } boolean_t;
# 210 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 3 4
typedef int64_t pad64_t;
typedef uint64_t upad64_t;
# 223 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 3 4
typedef longlong_t offset_t;
typedef u_longlong_t u_offset_t;
typedef u_longlong_t len_t;
typedef longlong_t diskaddr_t;
# 244 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 3 4
typedef union {
        offset_t _f;
        struct {
                int32_t _u;
                int32_t _l;
        } _p;
} lloff_t;
# 264 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 3 4
typedef union {
        diskaddr_t _f;
        struct {
                int32_t _u;
                int32_t _l;
        } _p;
} lldaddr_t;


typedef uint_t k_fltset_t;
# 287 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 3 4
typedef long id_t;






typedef uint_t useconds_t;



typedef long suseconds_t;
# 308 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 3 4
typedef ulong_t major_t;
typedef ulong_t minor_t;





typedef short pri_t;
# 328 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 3 4
typedef ushort_t o_mode_t;
typedef short o_dev_t;
typedef ushort_t o_uid_t;
typedef o_uid_t o_gid_t;
typedef short o_nlink_t;
typedef short o_pid_t;
typedef ushort_t o_ino_t;





typedef int key_t;



typedef ulong_t mode_t;







typedef long uid_t;



typedef uid_t gid_t;

typedef id_t taskid_t;
typedef id_t projid_t;






typedef unsigned int pthread_t;
typedef unsigned int pthread_key_t;

typedef struct _pthread_mutex {
        struct {
                uint16_t __pthread_mutex_flag1;
                uint8_t __pthread_mutex_flag2;
                uint8_t __pthread_mutex_ceiling;
                uint32_t __pthread_mutex_type;
        } __pthread_mutex_flags;
        union {
                struct {
                        uint8_t __pthread_mutex_pad[8];
                } __pthread_mutex_lock64;
                upad64_t __pthread_mutex_owner64;
        } __pthread_mutex_lock;
        upad64_t __pthread_mutex_data;
} pthread_mutex_t;

typedef struct _pthread_cond {
        struct {
                uint8_t __pthread_cond_flag[4];
                uint32_t __pthread_cond_type;
        } __pthread_cond_flags;
        upad64_t __pthread_cond_data;
} pthread_cond_t;




typedef struct _pthread_rwlock {
        int32_t __pthread_rwlock_readers;
        uint16_t __pthread_rwlock_type;
        uint16_t __pthread_rwlock_magic;
        upad64_t __pthread_rwlock_pad1[3];
        upad64_t __pthread_rwlock_pad2[2];
        upad64_t __pthread_rwlock_pad3[2];
} pthread_rwlock_t;




typedef struct _pthread_attr {
        void *__pthread_attrp;
} pthread_attr_t;





typedef struct _pthread_mutexattr {
        void *__pthread_mutexattrp;
} pthread_mutexattr_t;





typedef struct _pthread_condattr {
        void *__pthread_condattrp;
} pthread_condattr_t;




typedef struct _once {
        upad64_t __pthread_once_pad[4];
} pthread_once_t;





typedef struct _pthread_rwlockattr {
        void *__pthread_rwlockattrp;
} pthread_rwlockattr_t;

typedef ulong_t dev_t;





typedef ulong_t nlink_t;
typedef long pid_t;
# 464 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 3 4
typedef unsigned int size_t;
# 475 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 3 4
typedef int ssize_t;





typedef long time_t;




typedef long clock_t;




typedef int clockid_t;




typedef int timer_t;






typedef unsigned char unchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
# 557 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 3 4
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;
typedef struct _quad { int val[2]; } quad_t;
typedef quad_t quad;






# 1 "/usr/include/sys/select.h" 1 3 4
# 12 "/usr/include/sys/select.h" 3 4
#pragma ident "@(#)select.h	1.16	98/04/27 SMI" 




# 1 "/usr/include/sys/time.h" 1 3 4
# 23 "/usr/include/sys/time.h" 3 4
#pragma ident "@(#)time.h	2.67	03/08/07 SMI" 
# 50 "/usr/include/sys/time.h" 3 4
struct timeval {
        time_t tv_sec;
        suseconds_t tv_usec;
};
# 83 "/usr/include/sys/time.h" 3 4
struct timezone {
        int tz_minuteswest;
        int tz_dsttime;
};
# 101 "/usr/include/sys/time.h" 3 4
# 1 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 1 3 4
# 102 "/usr/include/sys/time.h" 2 3 4
# 156 "/usr/include/sys/time.h" 3 4
struct itimerval {
        struct timeval it_interval;
        struct timeval it_value;
};
# 204 "/usr/include/sys/time.h" 3 4
typedef longlong_t hrtime_t;
# 321 "/usr/include/sys/time.h" 3 4
int adjtime(struct timeval *, struct timeval *);
# 332 "/usr/include/sys/time.h" 3 4
int getitimer(int, struct itimerval *);
int utimes(const char *, const struct timeval *);



int setitimer(int, struct itimerval *, struct itimerval *);
# 370 "/usr/include/sys/time.h" 3 4
int settimeofday(struct timeval *, void *);

hrtime_t gethrtime(void);
hrtime_t gethrvtime(void);
# 390 "/usr/include/sys/time.h" 3 4
int gettimeofday(struct timeval *, void *);
# 411 "/usr/include/sys/time.h" 3 4
# 1 "/usr/include/time.h" 1 3 4
# 16 "/usr/include/time.h" 3 4
#pragma ident "@(#)time.h	1.39	99/08/10 SMI" 



# 1 "/usr/include/iso/time_iso.h" 1 3 4
# 28 "/usr/include/iso/time_iso.h" 3 4
#pragma ident "@(#)time_iso.h	1.1	99/08/09 SMI" 
# 69 "/usr/include/iso/time_iso.h" 3 4
struct tm {
        int tm_sec;
        int tm_min;
        int tm_hour;
        int tm_mday;
        int tm_mon;
        int tm_year;
        int tm_wday;
        int tm_yday;
        int tm_isdst;
};




extern char *asctime(const struct tm *);
extern clock_t clock(void);
extern char *ctime(const time_t *);
extern double difftime(time_t, time_t);
extern struct tm *gmtime(const time_t *);
extern struct tm *localtime(const time_t *);
extern time_t mktime(struct tm *);
extern time_t time(time_t *);
extern size_t strftime(char *, size_t, const char *, const struct tm *);
# 21 "/usr/include/time.h" 2 3 4
# 67 "/usr/include/time.h" 3 4
extern char *strptime(const char *, const char *, struct tm *);
# 83 "/usr/include/time.h" 3 4
# 1 "/usr/include/sys/time_impl.h" 1 3 4
# 15 "/usr/include/sys/time_impl.h" 3 4
#pragma ident "@(#)time_impl.h	1.5	99/10/05 SMI"
# 36 "/usr/include/sys/time_impl.h" 3 4
typedef struct timespec {
        time_t tv_sec;
        long tv_nsec;
} timespec_t;
# 60 "/usr/include/sys/time_impl.h" 3 4
typedef struct timespec timestruc_t;
# 79 "/usr/include/sys/time_impl.h" 3 4
typedef struct itimerspec {
        struct timespec it_interval;
        struct timespec it_value;
} itimerspec_t;
# 84 "/usr/include/time.h" 2 3 4
# 98 "/usr/include/time.h" 3 4
union sigval {
        int sival_int;
        void *sival_ptr;
};




struct sigevent {
        int sigev_notify;
        int sigev_signo;
        union sigval sigev_value;
        void (*sigev_notify_function)(union sigval);
        pthread_attr_t *sigev_notify_attributes;
        int __sigev_pad2;
};


extern int clock_getres(clockid_t, struct timespec *);
extern int clock_gettime(clockid_t, struct timespec *);
extern int clock_settime(clockid_t, const struct timespec *);
extern int timer_create(clockid_t, struct sigevent *, timer_t *);
extern int timer_delete(timer_t);
extern int timer_getoverrun(timer_t);
extern int timer_gettime(timer_t, struct itimerspec *);
extern int timer_settime(timer_t, int, const struct itimerspec *,
                struct itimerspec *);
extern int nanosleep(const struct timespec *, struct timespec *);




extern void tzset(void);

extern char *tzname[2];


extern long _sysconf(int);






extern long timezone;
extern int daylight;





extern int cftime(char *, char *, const time_t *);
extern int ascftime(char *, const char *, const struct tm *);
extern long altzone;




extern struct tm *getdate(const char *);






extern int getdate_err;
# 412 "/usr/include/sys/time.h" 2 3 4
# 424 "/usr/include/sys/time.h" 3 4
# 1 "/usr/include/sys/select.h" 1 3 4
# 425 "/usr/include/sys/time.h" 2 3 4
# 18 "/usr/include/sys/select.h" 2 3 4
# 45 "/usr/include/sys/select.h" 3 4
typedef long fd_mask;

typedef long fds_mask;
# 73 "/usr/include/sys/select.h" 3 4
typedef struct fd_set {



        long fds_bits[(((1024)+(((sizeof (fds_mask) * 8))-1))/((sizeof (fds_mask) * 8)))];
} fd_set;
# 97 "/usr/include/sys/select.h" 3 4
extern int select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
# 570 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/sys/types.h" 2 3 4
# 14 "/usr/include/sys/times.h" 2 3 4
# 22 "/usr/include/sys/times.h" 3 4
struct tms {
        clock_t tms_utime;
        clock_t tms_stime;
        clock_t tms_cutime;
        clock_t tms_cstime;
};
# 44 "/usr/include/sys/times.h" 3 4
clock_t times(struct tms *);
# 5 "MeasureTime.c" 2

# 1 "/usr/include/assert.h" 1 3 4
# 11 "/usr/include/assert.h" 3 4
#pragma ident "@(#)assert.h	1.9	92/07/14 SMI" 






extern void __assert(const char *, const char *, int);
# 7 "MeasureTime.c" 2

# 1 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/stdio.h" 1 3 4
# 14 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/stdio.h" 3 4
# 1 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/stdarg.h" 1 3 4
# 43 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 15 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/stdio.h" 2 3 4
# 34 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/stdio.h" 3 4
#pragma ident "@(#)stdio.h	1.78	99/12/08 SMI" 

# 1 "/usr/include/iso/stdio_iso.h" 1 3 4
# 32 "/usr/include/iso/stdio_iso.h" 3 4
#pragma ident "@(#)stdio_iso.h	1.2	99/10/25 SMI"



# 1 "/usr/include/sys/va_list.h" 1 3 4
# 9 "/usr/include/sys/va_list.h" 3 4
#pragma ident "@(#)va_list.h	1.12	99/05/04 SMI"
# 26 "/usr/include/sys/va_list.h" 3 4
typedef void *__va_list;
# 37 "/usr/include/iso/stdio_iso.h" 2 3 4
# 1 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/stdio_tag.h" 1 3 4
# 18 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/stdio_tag.h" 3 4
#pragma ident "@(#)stdio_tag.h	1.3	98/04/20 SMI"
# 30 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/stdio_tag.h" 3 4
typedef struct __FILE __FILE;
# 38 "/usr/include/iso/stdio_iso.h" 2 3 4
# 1 "/usr/include/stdio_impl.h" 1 3 4
# 9 "/usr/include/stdio_impl.h" 3 4
#pragma ident "@(#)stdio_impl.h	1.8	99/06/10 SMI"
# 38 "/usr/include/stdio_impl.h" 3 4
struct __FILE
{




        ssize_t _cnt;
        unsigned char *_ptr;

        unsigned char *_base;
        unsigned char _flag;
        unsigned char _file;
        unsigned __orientation:2;
        unsigned __ionolock:1;
        unsigned __filler:5;
};
# 39 "/usr/include/iso/stdio_iso.h" 2 3 4
# 59 "/usr/include/iso/stdio_iso.h" 3 4
typedef long long __longlong_t;
# 75 "/usr/include/iso/stdio_iso.h" 3 4
typedef __FILE FILE;
# 88 "/usr/include/iso/stdio_iso.h" 3 4
typedef long fpos_t;
# 147 "/usr/include/iso/stdio_iso.h" 3 4
extern __FILE __iob[20];
# 164 "/usr/include/iso/stdio_iso.h" 3 4
extern int remove(const char *);
extern int rename(const char *, const char *);
extern FILE *tmpfile(void);
extern char *tmpnam(char *);
extern int fclose(FILE *);
extern int fflush(FILE *);
extern FILE *fopen(const char *, const char *);
extern FILE *freopen(const char *, const char *, FILE *);
extern void setbuf(FILE *, char *);
extern int setvbuf(FILE *, char *, int, size_t);

extern int fprintf(FILE *, const char *, ...);

extern int fscanf(FILE *, const char *, ...);

extern int printf(const char *, ...);

extern int scanf(const char *, ...);

extern int sprintf(char *, const char *, ...);

extern int sscanf(const char *, const char *, ...);
extern int vfprintf(FILE *, const char *, __va_list);
extern int vprintf(const char *, __va_list);
extern int vsprintf(char *, const char *, __va_list);
extern int fgetc(FILE *);
extern char *fgets(char *, int, FILE *);
extern int fputc(int, FILE *);
extern int fputs(const char *, FILE *);


extern int getc(FILE *);
extern int putc(int, FILE *);



extern int getchar(void);
extern int putchar(int);

extern char *gets(char *);
extern int puts(const char *);
extern int ungetc(int, FILE *);
extern size_t fread(void *, size_t, size_t, FILE *);
extern size_t fwrite(const void *, size_t, size_t, FILE *);
extern int fgetpos(FILE *, fpos_t *);
extern int fseek(FILE *, long, int);
extern int fsetpos(FILE *, const fpos_t *);
extern long ftell(FILE *);
extern void rewind(FILE *);


extern void clearerr(FILE *);
extern int feof(FILE *);
extern int ferror(FILE *);

extern void perror(const char *);


extern int __filbuf(FILE *);
extern int __flsbuf(int, FILE *);
# 37 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/stdio.h" 2 3 4
# 123 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/stdio.h" 3 4
typedef __longlong_t fpos64_t;
# 151 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/stdio.h" 3 4
extern unsigned char _sibuf[], _sobuf[];
# 193 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/stdio.h" 3 4
extern unsigned char *_bufendtab[];
extern FILE *_lastbuf;
# 229 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/stdio.h" 3 4
extern void setbuffer(FILE *, char *, size_t);
extern int setlinebuf(FILE *);





extern int snprintf(char *, size_t, const char *, ...);




extern int vsnprintf(char *, size_t, const char *, __gnuc_va_list);
# 250 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/stdio.h" 3 4
extern FILE *fdopen(int, const char *);
extern char *ctermid(char *);
extern int fileno(FILE *);
# 276 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/stdio.h" 3 4
extern FILE *popen(const char *, const char *);
extern char *cuserid(char *);
extern char *tempnam(const char *, const char *);
extern int getopt(int, char *const *, const char *);

extern int getsubopt(char **, char *const *, char **);

extern char *optarg;
extern int optind, opterr, optopt;
extern int getw(FILE *);
extern int putw(int, FILE *);
extern int pclose(FILE *);







extern int fseeko(FILE *, off_t, int);
extern off_t ftello(FILE *);
# 305 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/stdio.h" 3 4
extern FILE *fopen64(const char *, const char *);
extern FILE *freopen64(const char *, const char *, FILE *);
extern FILE *tmpfile64(void);
extern int fgetpos64(FILE *, fpos64_t *);
extern int fsetpos64(FILE *, const fpos64_t *);
extern int fseeko64(FILE *, off64_t, int);
extern off64_t ftello64(FILE *);
# 9 "MeasureTime.c" 2
# 1 "/usr/include/stdlib.h" 1 3 4
# 16 "/usr/include/stdlib.h" 3 4
#pragma ident "@(#)stdlib.h	1.47	99/11/03 SMI" 

# 1 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/iso/stdlib_iso.h" 1 3 4
# 37 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/iso/stdlib_iso.h" 3 4
#pragma ident "@(#)stdlib_iso.h	1.2	99/12/21 SMI" 
# 46 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/iso/stdlib_iso.h" 3 4
extern unsigned char __ctype[];
# 57 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/iso/stdlib_iso.h" 3 4
typedef struct {
        int quot;
        int rem;
} div_t;

typedef struct {
        long quot;
        long rem;
} ldiv_t;
# 96 "/usr/local/lib/gcc-lib/sparc-sun-solaris2.8/3.3.2/include/iso/stdlib_iso.h" 3 4
typedef long wchar_t;






extern void abort(void);
extern int abs(int);
extern int atexit(void (*)(void));
extern double atof(const char *);
extern int atoi(const char *);
extern long int atol(const char *);
extern void *bsearch(const void *, const void *, size_t, size_t,
        int (*)(const void *, const void *));
extern void *calloc(size_t, size_t);
extern div_t div(int, int);
extern void exit(int);
extern void free(void *);
extern char *getenv(const char *);
extern long int labs(long);
extern ldiv_t ldiv(long, long);
extern void *malloc(size_t);
extern int mblen(const char *, size_t);
extern size_t mbstowcs(wchar_t *, const char *, size_t);
extern int mbtowc(wchar_t *, const char *, size_t);
extern void qsort(void *, size_t, size_t,
        int (*)(const void *, const void *));
extern int rand(void);
extern void *realloc(void *, size_t);
extern void srand(unsigned int);
extern double strtod(const char *, char **);
extern long int strtol(const char *, char **, int);
extern unsigned long int strtoul(const char *, char **, int);
extern int system(const char *);
extern int wctomb(char *, wchar_t);
extern size_t wcstombs(char *, const wchar_t *, size_t);
# 19 "/usr/include/stdlib.h" 2 3 4
# 68 "/usr/include/stdlib.h" 3 4
typedef struct {
        long long quot;
        long long rem;
} lldiv_t;
# 112 "/usr/include/stdlib.h" 3 4
extern void _exithandle(void);




extern double drand48(void);
extern double erand48(unsigned short *);
extern long jrand48(unsigned short *);
extern void lcong48(unsigned short *);
extern long lrand48(void);
extern long mrand48(void);
extern long nrand48(unsigned short *);
extern unsigned short *seed48(unsigned short *);
extern void srand48(long);
extern int putenv(char *);
extern void setkey(const char *);
# 144 "/usr/include/stdlib.h" 3 4
extern void swab(const char *, char *, ssize_t);





extern int mkstemp(char *);




extern int mkstemp64(char *);





extern long a64l(const char *);
extern char *ecvt(double, int, int *, int *);
extern char *fcvt(double, int, int *, int *);
extern char *gcvt(double, int, char *);
extern int getsubopt(char **, char *const *, char **);
extern int grantpt(int);
extern char *initstate(unsigned, char *, size_t);
extern char *l64a(long);
extern char *mktemp(char *);
extern char *ptsname(int);
extern long random(void);
extern char *realpath(const char *, char *);
extern char *setstate(const char *);
extern void srandom(unsigned);
extern int ttyslot(void);
extern int unlockpt(int);
extern void *valloc(size_t);




extern int dup2(int, int);
extern char *qecvt(long double, int, int *, int *);
extern char *qfcvt(long double, int, int *, int *);
extern char *qgcvt(long double, int, char *);
extern char *getcwd(char *, size_t);
extern const char *getexecname(void);
extern char *getlogin(void);
extern int getopt(int, char *const *, const char *);
extern char *optarg;
extern int optind, opterr, optopt;
extern char *getpass(const char *);
extern char *getpassphrase(const char *);
extern int getpw(uid_t, char *);
extern int isatty(int);
extern void *memalign(size_t, size_t);
extern char *ttyname(int);


extern long long atoll(const char *);
extern long long llabs(long long);
extern lldiv_t lldiv(long long, long long);
extern char *lltostr(long long, char *);
extern long long strtoll(const char *, char **, int);
extern unsigned long long strtoull(const char *, char **, int);
extern char *ulltostr(unsigned long long, char *);
# 10 "MeasureTime.c" 2
# 1 "MeasureTime.h" 1
# 12 "MeasureTime.h"
typedef struct anst_clock{
        struct tms measureTimeS1;
        struct tms measureTimeS2;
}Clock;







void StopClock(Clock *);
void StartClock(Clock *);
unsigned long long GetClockTicks(Clock *);
Clock* CreateClock(void);
# 11 "MeasureTime.c" 2
# 20 "MeasureTime.c"
void StartClock(Clock *clk){
        if(times(&(clk->measureTimeS1)) == (clock_t)-1){
                fprintf((&__iob[2]),"WARNING:Unable to Start the Clock %p \n",clk);
        }
}
void StopClock(Clock *clk){
        if(times(&(clk->measureTimeS2)) == (clock_t)-1){
                fprintf((&__iob[2]),"WARNING:Unable to Stop the Clock %p \n",clk);
        }
}
unsigned long long GetClockTicks(Clock *clk){
        return ((clk->measureTimeS2).tms_utime - (clk->measureTimeS1).tms_utime);
}
Clock * CreateClock(){
        return (Clock *)malloc(sizeof(Clock)*1);
}
void DeleteClock(Clock *clk){
        free(clk);
}

int main(int argc,char **argv){
        struct tms s1;
        struct tms s2;
        volatile int count,count1;
        volatile int i;
        volatile double X=1024;
        Clock *test_clk = CreateClock();

        StartClock(test_clk);
        for(i=0;i<10000000;i++){
                count1+=(i+1);
                count1 = (count1*i)/count1;
                X += ((X*X) + X/0.331)*(X*X*X);
        }
        StopClock(test_clk);
        printf("PROBE1: Clock Ticks Elapsed is %Lu \n",(clock_t)GetClockTicks(test_clk));

        StartClock(test_clk);
        for(i=0;i<10000000;i++){
                count1+=(i+1);
                count1 = (count1*i)/count1;
                X += ((X*X) + X/0.331)*(X*X*X);
        }
        StopClock(test_clk);
        printf("PROBE2: Clock Ticks Elapsed is %Lu \n",(clock_t)GetClockTicks(test_clk));


}
