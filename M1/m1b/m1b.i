# 1 "m1b.c"
# 1 "/home/kshelton/Documents/GitHub/ECE-4140/M1/m1b//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "m1b.c"
# 22 "m1b.c"
# 1 "user_app.h" 1
# 48 "user_app.h"
void Error_Handler(void);
# 23 "m1b.c" 2
# 1 "/usr/include/newlib/errno.h" 1 3





# 5 "/usr/include/newlib/errno.h" 3
typedef int error_t;



# 1 "/usr/include/newlib/sys/errno.h" 1 3
# 11 "/usr/include/newlib/sys/errno.h" 3
# 1 "/usr/include/newlib/sys/reent.h" 1 3
# 13 "/usr/include/newlib/sys/reent.h" 3
# 1 "/usr/include/newlib/_ansi.h" 1 3
# 10 "/usr/include/newlib/_ansi.h" 3
# 1 "/usr/include/newlib/newlib.h" 1 3
# 14 "/usr/include/newlib/newlib.h" 3
# 1 "/usr/include/newlib/_newlib_version.h" 1 3
# 15 "/usr/include/newlib/newlib.h" 2 3
# 11 "/usr/include/newlib/_ansi.h" 2 3
# 1 "/usr/include/newlib/sys/config.h" 1 3



# 1 "/usr/include/newlib/machine/ieeefp.h" 1 3
# 5 "/usr/include/newlib/sys/config.h" 2 3
# 1 "/usr/include/newlib/sys/features.h" 1 3
# 6 "/usr/include/newlib/sys/config.h" 2 3
# 12 "/usr/include/newlib/_ansi.h" 2 3
# 14 "/usr/include/newlib/sys/reent.h" 2 3
# 1 "/usr/lib/gcc/arm-none-eabi/10.3.1/include/stddef.h" 1 3 4
# 143 "/usr/lib/gcc/arm-none-eabi/10.3.1/include/stddef.h" 3 4
typedef int ptrdiff_t;
# 209 "/usr/lib/gcc/arm-none-eabi/10.3.1/include/stddef.h" 3 4
typedef unsigned int size_t;
# 321 "/usr/lib/gcc/arm-none-eabi/10.3.1/include/stddef.h" 3 4
typedef unsigned int wchar_t;
# 415 "/usr/lib/gcc/arm-none-eabi/10.3.1/include/stddef.h" 3 4
typedef struct {
  long long __max_align_ll __attribute__((__aligned__(__alignof__(long long))));
  long double __max_align_ld __attribute__((__aligned__(__alignof__(long double))));
# 426 "/usr/lib/gcc/arm-none-eabi/10.3.1/include/stddef.h" 3 4
} max_align_t;
# 15 "/usr/include/newlib/sys/reent.h" 2 3
# 1 "/usr/include/newlib/sys/_types.h" 1 3
# 24 "/usr/include/newlib/sys/_types.h" 3
# 1 "/usr/lib/gcc/arm-none-eabi/10.3.1/include/stddef.h" 1 3 4
# 350 "/usr/lib/gcc/arm-none-eabi/10.3.1/include/stddef.h" 3 4
typedef unsigned int wint_t;
# 25 "/usr/include/newlib/sys/_types.h" 2 3


# 1 "/usr/include/newlib/machine/_types.h" 1 3






# 1 "/usr/include/newlib/machine/_default_types.h" 1 3
# 41 "/usr/include/newlib/machine/_default_types.h" 3
typedef signed char __int8_t;

typedef unsigned char __uint8_t;
# 55 "/usr/include/newlib/machine/_default_types.h" 3
typedef short int __int16_t;

typedef short unsigned int __uint16_t;
# 77 "/usr/include/newlib/machine/_default_types.h" 3
typedef long int __int32_t;

typedef long unsigned int __uint32_t;
# 103 "/usr/include/newlib/machine/_default_types.h" 3
typedef long long int __int64_t;

typedef long long unsigned int __uint64_t;
# 134 "/usr/include/newlib/machine/_default_types.h" 3
typedef signed char __int_least8_t;

typedef unsigned char __uint_least8_t;
# 160 "/usr/include/newlib/machine/_default_types.h" 3
typedef short int __int_least16_t;

typedef short unsigned int __uint_least16_t;
# 182 "/usr/include/newlib/machine/_default_types.h" 3
typedef long int __int_least32_t;

typedef long unsigned int __uint_least32_t;
# 200 "/usr/include/newlib/machine/_default_types.h" 3
typedef long long int __int_least64_t;

typedef long long unsigned int __uint_least64_t;
# 214 "/usr/include/newlib/machine/_default_types.h" 3
typedef long long int __intmax_t;







typedef long long unsigned int __uintmax_t;







typedef int __intptr_t;

typedef unsigned int __uintptr_t;
# 8 "/usr/include/newlib/machine/_types.h" 2 3
# 28 "/usr/include/newlib/sys/_types.h" 2 3


typedef long __blkcnt_t;



typedef long __blksize_t;



typedef __uint64_t __fsblkcnt_t;



typedef __uint32_t __fsfilcnt_t;



typedef long _off_t;





typedef int __pid_t;



typedef short __dev_t;



typedef unsigned short __uid_t;


typedef unsigned short __gid_t;



typedef __uint32_t __id_t;







typedef unsigned short __ino_t;
# 90 "/usr/include/newlib/sys/_types.h" 3
typedef __uint32_t __mode_t;





__extension__ typedef long long _off64_t;





typedef _off_t __off_t;


typedef _off64_t __loff_t;


typedef long __key_t;







typedef long _fpos_t;
# 131 "/usr/include/newlib/sys/_types.h" 3
typedef unsigned int __size_t;
# 147 "/usr/include/newlib/sys/_types.h" 3
typedef signed int _ssize_t;
# 158 "/usr/include/newlib/sys/_types.h" 3
typedef _ssize_t __ssize_t;



typedef struct
{
  int __count;
  union
  {
    wint_t __wch;
    unsigned char __wchb[4];
  } __value;
} _mbstate_t;




typedef void *_iconv_t;






typedef unsigned long __clock_t;






typedef __int_least64_t __time_t;





typedef unsigned long __clockid_t;


typedef unsigned long __timer_t;


typedef __uint8_t __sa_family_t;



typedef __uint32_t __socklen_t;


typedef int __nl_item;
typedef unsigned short __nlink_t;
typedef long __suseconds_t;
typedef unsigned long __useconds_t;







typedef __builtin_va_list __va_list;
# 16 "/usr/include/newlib/sys/reent.h" 2 3






typedef unsigned long __ULong;
# 34 "/usr/include/newlib/sys/reent.h" 3
# 1 "/usr/include/newlib/sys/lock.h" 1 3
# 11 "/usr/include/newlib/sys/lock.h" 3
typedef int _LOCK_T;
typedef int _LOCK_RECURSIVE_T;
# 35 "/usr/include/newlib/sys/reent.h" 2 3
typedef _LOCK_RECURSIVE_T _flock_t;







struct _reent;

struct __locale_t;






struct _Bigint
{
  struct _Bigint *_next;
  int _k, _maxwds, _sign, _wds;
  __ULong _x[1];
};


struct __tm
{
  int __tm_sec;
  int __tm_min;
  int __tm_hour;
  int __tm_mday;
  int __tm_mon;
  int __tm_year;
  int __tm_wday;
  int __tm_yday;
  int __tm_isdst;
};







struct _on_exit_args {
 void * _fnargs[32];
 void * _dso_handle[32];

 __ULong _fntypes;


 __ULong _is_cxa;
};
# 98 "/usr/include/newlib/sys/reent.h" 3
struct _atexit {
 struct _atexit *_next;
 int _ind;

 void (*_fns[32])(void);
        struct _on_exit_args _on_exit_args;
};
# 122 "/usr/include/newlib/sys/reent.h" 3
struct __sbuf {
 unsigned char *_base;
 int _size;
};
# 186 "/usr/include/newlib/sys/reent.h" 3
struct __sFILE {
  unsigned char *_p;
  int _r;
  int _w;
  short _flags;
  short _file;
  struct __sbuf _bf;
  int _lbfsize;






  void * _cookie;

  int (*_read) (struct _reent *, void *,
        char *, int);
  int (*_write) (struct _reent *, void *,
         const char *,
         int);
  _fpos_t (*_seek) (struct _reent *, void *, _fpos_t, int);
  int (*_close) (struct _reent *, void *);


  struct __sbuf _ub;
  unsigned char *_up;
  int _ur;


  unsigned char _ubuf[3];
  unsigned char _nbuf[1];


  struct __sbuf _lb;


  int _blksize;
  _off_t _offset;


  struct _reent *_data;



  _flock_t _lock;

  _mbstate_t _mbstate;
  int _flags2;
};
# 292 "/usr/include/newlib/sys/reent.h" 3
typedef struct __sFILE __FILE;



struct _glue
{
  struct _glue *_next;
  int _niobs;
  __FILE *_iobs;
};
# 324 "/usr/include/newlib/sys/reent.h" 3
struct _rand48 {
  unsigned short _seed[3];
  unsigned short _mult[3];
  unsigned short _add;




};
# 613 "/usr/include/newlib/sys/reent.h" 3
struct _reent
{
  int _errno;




  __FILE *_stdin, *_stdout, *_stderr;

  int _inc;
  char _emergency[25];


  int _unspecified_locale_info;
  struct __locale_t *_locale;

  int __sdidinit;

  void (*__cleanup) (struct _reent *);


  struct _Bigint *_result;
  int _result_k;
  struct _Bigint *_p5s;
  struct _Bigint **_freelist;


  int _cvtlen;
  char *_cvtbuf;

  union
    {
      struct
        {
          unsigned int _unused_rand;
          char * _strtok_last;
          char _asctime_buf[26];
          struct __tm _localtime_buf;
          int _gamma_signgam;
          __extension__ unsigned long long _rand_next;
          struct _rand48 _r48;
          _mbstate_t _mblen_state;
          _mbstate_t _mbtowc_state;
          _mbstate_t _wctomb_state;
          char _l64a_buf[8];
          char _signal_buf[24];
          int _getdate_err;
          _mbstate_t _mbrlen_state;
          _mbstate_t _mbrtowc_state;
          _mbstate_t _mbsrtowcs_state;
          _mbstate_t _wcrtomb_state;
          _mbstate_t _wcsrtombs_state;
   int _h_errno;
        } _reent;



      struct
        {

          unsigned char * _nextf[30];
          unsigned int _nmalloc[30];
        } _unused;
    } _new;



  struct _atexit *_atexit;
  struct _atexit _atexit0;



  void (**(_sig_func))(int);




  struct _glue __sglue;

  __FILE __sf[3];

};
# 819 "/usr/include/newlib/sys/reent.h" 3
extern struct _reent *_impure_ptr ;
extern struct _reent *const _global_impure_ptr ;

void _reclaim_reent (struct _reent *);
# 12 "/usr/include/newlib/sys/errno.h" 2 3



extern int *__errno (void);




extern const char * const _sys_errlist[];
extern int _sys_nerr;
# 10 "/usr/include/newlib/errno.h" 2 3
# 24 "m1b.c" 2
# 1 "/usr/include/newlib/stdio.h" 1 3
# 29 "/usr/include/newlib/stdio.h" 3
# 1 "/usr/include/newlib/_ansi.h" 1 3
# 30 "/usr/include/newlib/stdio.h" 2 3





# 1 "/usr/include/newlib/sys/cdefs.h" 1 3
# 47 "/usr/include/newlib/sys/cdefs.h" 3
# 1 "/usr/lib/gcc/arm-none-eabi/10.3.1/include/stddef.h" 1 3 4
# 48 "/usr/include/newlib/sys/cdefs.h" 2 3
# 36 "/usr/include/newlib/stdio.h" 2 3
# 1 "/usr/lib/gcc/arm-none-eabi/10.3.1/include/stddef.h" 1 3 4
# 37 "/usr/include/newlib/stdio.h" 2 3



# 1 "/usr/lib/gcc/arm-none-eabi/10.3.1/include/stdarg.h" 1 3 4
# 40 "/usr/lib/gcc/arm-none-eabi/10.3.1/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 41 "/usr/include/newlib/stdio.h" 2 3





typedef __gnuc_va_list va_list;
# 61 "/usr/include/newlib/stdio.h" 3
# 1 "/usr/include/newlib/sys/types.h" 1 3
# 28 "/usr/include/newlib/sys/types.h" 3
typedef __uint8_t u_int8_t;


typedef __uint16_t u_int16_t;


typedef __uint32_t u_int32_t;


typedef __uint64_t u_int64_t;

typedef __intptr_t register_t;






# 1 "/usr/include/newlib/sys/_stdint.h" 1 3
# 20 "/usr/include/newlib/sys/_stdint.h" 3
typedef __int8_t int8_t ;



typedef __uint8_t uint8_t ;







typedef __int16_t int16_t ;



typedef __uint16_t uint16_t ;







typedef __int32_t int32_t ;



typedef __uint32_t uint32_t ;







typedef __int64_t int64_t ;



typedef __uint64_t uint64_t ;






typedef __intmax_t intmax_t;




typedef __uintmax_t uintmax_t;




typedef __intptr_t intptr_t;




typedef __uintptr_t uintptr_t;
# 47 "/usr/include/newlib/sys/types.h" 2 3


# 1 "/usr/include/newlib/machine/endian.h" 1 3





# 1 "/usr/include/newlib/machine/_endian.h" 1 3
# 7 "/usr/include/newlib/machine/endian.h" 2 3
# 50 "/usr/include/newlib/sys/types.h" 2 3
# 1 "/usr/include/newlib/sys/select.h" 1 3
# 14 "/usr/include/newlib/sys/select.h" 3
# 1 "/usr/include/newlib/sys/_sigset.h" 1 3
# 41 "/usr/include/newlib/sys/_sigset.h" 3
typedef unsigned long __sigset_t;
# 15 "/usr/include/newlib/sys/select.h" 2 3
# 1 "/usr/include/newlib/sys/_timeval.h" 1 3
# 37 "/usr/include/newlib/sys/_timeval.h" 3
typedef __suseconds_t suseconds_t;




typedef __int_least64_t time_t;
# 54 "/usr/include/newlib/sys/_timeval.h" 3
struct timeval {
 time_t tv_sec;
 suseconds_t tv_usec;
};
# 16 "/usr/include/newlib/sys/select.h" 2 3
# 1 "/usr/include/newlib/sys/timespec.h" 1 3
# 38 "/usr/include/newlib/sys/timespec.h" 3
# 1 "/usr/include/newlib/sys/_timespec.h" 1 3
# 47 "/usr/include/newlib/sys/_timespec.h" 3
struct timespec {
 time_t tv_sec;
 long tv_nsec;
};
# 39 "/usr/include/newlib/sys/timespec.h" 2 3
# 58 "/usr/include/newlib/sys/timespec.h" 3
struct itimerspec {
 struct timespec it_interval;
 struct timespec it_value;
};
# 17 "/usr/include/newlib/sys/select.h" 2 3



typedef __sigset_t sigset_t;
# 34 "/usr/include/newlib/sys/select.h" 3
typedef unsigned long fd_mask;







typedef struct _types_fd_set {
 fd_mask fds_bits[(((64)+(((sizeof (fd_mask) * 8))-1))/((sizeof (fd_mask) * 8)))];
} _types_fd_set;
# 60 "/usr/include/newlib/sys/select.h" 3


int select (int __n, _types_fd_set *__readfds, _types_fd_set *__writefds, _types_fd_set *__exceptfds, struct timeval *__timeout)
                                                   ;

int pselect (int __n, _types_fd_set *__readfds, _types_fd_set *__writefds, _types_fd_set *__exceptfds, const struct timespec *__timeout, const sigset_t *__set)

                           ;



# 51 "/usr/include/newlib/sys/types.h" 2 3




typedef __uint32_t in_addr_t;




typedef __uint16_t in_port_t;



typedef __uintptr_t u_register_t;






typedef unsigned char u_char;



typedef unsigned short u_short;



typedef unsigned int u_int;



typedef unsigned long u_long;







typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;



typedef __blkcnt_t blkcnt_t;




typedef __blksize_t blksize_t;




typedef unsigned long clock_t;
# 119 "/usr/include/newlib/sys/types.h" 3
typedef long daddr_t;



typedef char * caddr_t;




typedef __fsblkcnt_t fsblkcnt_t;
typedef __fsfilcnt_t fsfilcnt_t;




typedef __id_t id_t;




typedef __ino_t ino_t;
# 157 "/usr/include/newlib/sys/types.h" 3
typedef __off_t off_t;



typedef __dev_t dev_t;



typedef __uid_t uid_t;



typedef __gid_t gid_t;




typedef __pid_t pid_t;




typedef __key_t key_t;




typedef _ssize_t ssize_t;




typedef __mode_t mode_t;




typedef __nlink_t nlink_t;




typedef __clockid_t clockid_t;





typedef __timer_t timer_t;





typedef __useconds_t useconds_t;
# 220 "/usr/include/newlib/sys/types.h" 3
typedef __int64_t sbintime_t;


# 1 "/usr/include/newlib/sys/_pthreadtypes.h" 1 3
# 23 "/usr/include/newlib/sys/_pthreadtypes.h" 3
# 1 "/usr/include/newlib/sys/sched.h" 1 3
# 48 "/usr/include/newlib/sys/sched.h" 3
struct sched_param {
  int sched_priority;
# 61 "/usr/include/newlib/sys/sched.h" 3
};
# 24 "/usr/include/newlib/sys/_pthreadtypes.h" 2 3
# 32 "/usr/include/newlib/sys/_pthreadtypes.h" 3
typedef __uint32_t pthread_t;
# 61 "/usr/include/newlib/sys/_pthreadtypes.h" 3
typedef struct {
  int is_initialized;
  void *stackaddr;
  int stacksize;
  int contentionscope;
  int inheritsched;
  int schedpolicy;
  struct sched_param schedparam;





  int detachstate;
} pthread_attr_t;
# 154 "/usr/include/newlib/sys/_pthreadtypes.h" 3
typedef __uint32_t pthread_mutex_t;

typedef struct {
  int is_initialized;
# 168 "/usr/include/newlib/sys/_pthreadtypes.h" 3
  int recursive;
} pthread_mutexattr_t;






typedef __uint32_t pthread_cond_t;



typedef struct {
  int is_initialized;
  clock_t clock;



} pthread_condattr_t;



typedef __uint32_t pthread_key_t;

typedef struct {
  int is_initialized;
  int init_executed;
} pthread_once_t;
# 224 "/usr/include/newlib/sys/types.h" 2 3
# 1 "/usr/include/newlib/machine/types.h" 1 3
# 225 "/usr/include/newlib/sys/types.h" 2 3
# 62 "/usr/include/newlib/stdio.h" 2 3




typedef __FILE FILE;






typedef _fpos_t fpos_t;





# 1 "/usr/include/newlib/sys/stdio.h" 1 3
# 80 "/usr/include/newlib/stdio.h" 2 3
# 181 "/usr/include/newlib/stdio.h" 3
char * ctermid (char *);




FILE * tmpfile (void);
char * tmpnam (char *);

char * tempnam (const char *, const char *) __attribute__((__malloc__)) __attribute__((__warn_unused_result__));

int fclose (FILE *);
int fflush (FILE *);
FILE * freopen (const char *restrict, const char *restrict, FILE *restrict);
void setbuf (FILE *restrict, char *restrict);
int setvbuf (FILE *restrict, char *restrict, int, size_t);
int fprintf (FILE *restrict, const char *restrict, ...)
               __attribute__ ((__format__ (__printf__, 2, 3)));
int fscanf (FILE *restrict, const char *restrict, ...)
               __attribute__ ((__format__ (__scanf__, 2, 3)));
int printf (const char *restrict, ...)
               __attribute__ ((__format__ (__printf__, 1, 2)));
int scanf (const char *restrict, ...)
               __attribute__ ((__format__ (__scanf__, 1, 2)));
int sscanf (const char *restrict, const char *restrict, ...)
               __attribute__ ((__format__ (__scanf__, 2, 3)));
int vfprintf (FILE *restrict, const char *restrict, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 2, 0)));
int vprintf (const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 1, 0)));
int vsprintf (char *restrict, const char *restrict, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 2, 0)));
int fgetc (FILE *);
char * fgets (char *restrict, int, FILE *restrict);
int fputc (int, FILE *);
int fputs (const char *restrict, FILE *restrict);
int getc (FILE *);
int getchar (void);
char * gets (char *);
int putc (int, FILE *);
int putchar (int);
int puts (const char *);
int ungetc (int, FILE *);
size_t fread (void *restrict, size_t _size, size_t _n, FILE *restrict);
size_t fwrite (const void *restrict , size_t _size, size_t _n, FILE *);



int fgetpos (FILE *restrict, fpos_t *restrict);

int fseek (FILE *, long, int);



int fsetpos (FILE *, const fpos_t *);

long ftell ( FILE *);
void rewind (FILE *);
void clearerr (FILE *);
int feof (FILE *);
int ferror (FILE *);
void perror (const char *);

FILE * fopen (const char *restrict _name, const char *restrict _type);
int sprintf (char *restrict, const char *restrict, ...)
               __attribute__ ((__format__ (__printf__, 2, 3)));
int remove (const char *);
int rename (const char *, const char *);
# 257 "/usr/include/newlib/stdio.h" 3
int fseeko (FILE *, off_t, int);
off_t ftello (FILE *);







int snprintf (char *restrict, size_t, const char *restrict, ...)
               __attribute__ ((__format__ (__printf__, 3, 4)));
int vsnprintf (char *restrict, size_t, const char *restrict, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 3, 0)));
int vfscanf (FILE *restrict, const char *restrict, __gnuc_va_list)
               __attribute__ ((__format__ (__scanf__, 2, 0)));
int vscanf (const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__scanf__, 1, 0)));
int vsscanf (const char *restrict, const char *restrict, __gnuc_va_list)
               __attribute__ ((__format__ (__scanf__, 2, 0)));
# 284 "/usr/include/newlib/stdio.h" 3
int asiprintf (char **, const char *, ...)
               __attribute__ ((__format__ (__printf__, 2, 3)));
char * asniprintf (char *, size_t *, const char *, ...)
               __attribute__ ((__format__ (__printf__, 3, 4)));
char * asnprintf (char *restrict, size_t *restrict, const char *restrict, ...)
               __attribute__ ((__format__ (__printf__, 3, 4)));

int diprintf (int, const char *, ...)
               __attribute__ ((__format__ (__printf__, 2, 3)));

int fiprintf (FILE *, const char *, ...)
               __attribute__ ((__format__ (__printf__, 2, 3)));
int fiscanf (FILE *, const char *, ...)
               __attribute__ ((__format__ (__scanf__, 2, 3)));
int iprintf (const char *, ...)
               __attribute__ ((__format__ (__printf__, 1, 2)));
int iscanf (const char *, ...)
               __attribute__ ((__format__ (__scanf__, 1, 2)));
int siprintf (char *, const char *, ...)
               __attribute__ ((__format__ (__printf__, 2, 3)));
int siscanf (const char *, const char *, ...)
               __attribute__ ((__format__ (__scanf__, 2, 3)));
int sniprintf (char *, size_t, const char *, ...)
               __attribute__ ((__format__ (__printf__, 3, 4)));
int vasiprintf (char **, const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 2, 0)));
char * vasniprintf (char *, size_t *, const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 3, 0)));
char * vasnprintf (char *, size_t *, const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 3, 0)));
int vdiprintf (int, const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 2, 0)));
int vfiprintf (FILE *, const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 2, 0)));
int vfiscanf (FILE *, const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__scanf__, 2, 0)));
int viprintf (const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 1, 0)));
int viscanf (const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__scanf__, 1, 0)));
int vsiprintf (char *, const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 2, 0)));
int vsiscanf (const char *, const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__scanf__, 2, 0)));
int vsniprintf (char *, size_t, const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 3, 0)));
# 339 "/usr/include/newlib/stdio.h" 3
FILE * fdopen (int, const char *);

int fileno (FILE *);


int pclose (FILE *);
FILE * popen (const char *, const char *);



void setbuffer (FILE *, char *, int);
int setlinebuf (FILE *);



int getw (FILE *);
int putw (int, FILE *);


int getc_unlocked (FILE *);
int getchar_unlocked (void);
void flockfile (FILE *);
int ftrylockfile (FILE *);
void funlockfile (FILE *);
int putc_unlocked (int, FILE *);
int putchar_unlocked (int);
# 374 "/usr/include/newlib/stdio.h" 3
int dprintf (int, const char *restrict, ...)
               __attribute__ ((__format__ (__printf__, 2, 3)));

FILE * fmemopen (void *restrict, size_t, const char *restrict);


FILE * open_memstream (char **, size_t *);
int vdprintf (int, const char *restrict, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 2, 0)));



int renameat (int, const char *, int, const char *);
# 396 "/usr/include/newlib/stdio.h" 3
int _asiprintf_r (struct _reent *, char **, const char *, ...)
               __attribute__ ((__format__ (__printf__, 3, 4)));
char * _asniprintf_r (struct _reent *, char *, size_t *, const char *, ...)
               __attribute__ ((__format__ (__printf__, 4, 5)));
char * _asnprintf_r (struct _reent *, char *restrict, size_t *restrict, const char *restrict, ...)
               __attribute__ ((__format__ (__printf__, 4, 5)));
int _asprintf_r (struct _reent *, char **restrict, const char *restrict, ...)
               __attribute__ ((__format__ (__printf__, 3, 4)));
int _diprintf_r (struct _reent *, int, const char *, ...)
               __attribute__ ((__format__ (__printf__, 3, 4)));
int _dprintf_r (struct _reent *, int, const char *restrict, ...)
               __attribute__ ((__format__ (__printf__, 3, 4)));
int _fclose_r (struct _reent *, FILE *);
int _fcloseall_r (struct _reent *);
FILE * _fdopen_r (struct _reent *, int, const char *);
int _fflush_r (struct _reent *, FILE *);
int _fgetc_r (struct _reent *, FILE *);
int _fgetc_unlocked_r (struct _reent *, FILE *);
char * _fgets_r (struct _reent *, char *restrict, int, FILE *restrict);
char * _fgets_unlocked_r (struct _reent *, char *restrict, int, FILE *restrict);




int _fgetpos_r (struct _reent *, FILE *, fpos_t *);
int _fsetpos_r (struct _reent *, FILE *, const fpos_t *);

int _fiprintf_r (struct _reent *, FILE *, const char *, ...)
               __attribute__ ((__format__ (__printf__, 3, 4)));
int _fiscanf_r (struct _reent *, FILE *, const char *, ...)
               __attribute__ ((__format__ (__scanf__, 3, 4)));
FILE * _fmemopen_r (struct _reent *, void *restrict, size_t, const char *restrict);
FILE * _fopen_r (struct _reent *, const char *restrict, const char *restrict);
FILE * _freopen_r (struct _reent *, const char *restrict, const char *restrict, FILE *restrict);
int _fprintf_r (struct _reent *, FILE *restrict, const char *restrict, ...)
               __attribute__ ((__format__ (__printf__, 3, 4)));
int _fpurge_r (struct _reent *, FILE *);
int _fputc_r (struct _reent *, int, FILE *);
int _fputc_unlocked_r (struct _reent *, int, FILE *);
int _fputs_r (struct _reent *, const char *restrict, FILE *restrict);
int _fputs_unlocked_r (struct _reent *, const char *restrict, FILE *restrict);
size_t _fread_r (struct _reent *, void *restrict, size_t _size, size_t _n, FILE *restrict);
size_t _fread_unlocked_r (struct _reent *, void *restrict, size_t _size, size_t _n, FILE *restrict);
int _fscanf_r (struct _reent *, FILE *restrict, const char *restrict, ...)
               __attribute__ ((__format__ (__scanf__, 3, 4)));
int _fseek_r (struct _reent *, FILE *, long, int);
int _fseeko_r (struct _reent *, FILE *, _off_t, int);
long _ftell_r (struct _reent *, FILE *);
_off_t _ftello_r (struct _reent *, FILE *);
void _rewind_r (struct _reent *, FILE *);
size_t _fwrite_r (struct _reent *, const void *restrict, size_t _size, size_t _n, FILE *restrict);
size_t _fwrite_unlocked_r (struct _reent *, const void *restrict, size_t _size, size_t _n, FILE *restrict);
int _getc_r (struct _reent *, FILE *);
int _getc_unlocked_r (struct _reent *, FILE *);
int _getchar_r (struct _reent *);
int _getchar_unlocked_r (struct _reent *);
char * _gets_r (struct _reent *, char *);
int _iprintf_r (struct _reent *, const char *, ...)
               __attribute__ ((__format__ (__printf__, 2, 3)));
int _iscanf_r (struct _reent *, const char *, ...)
               __attribute__ ((__format__ (__scanf__, 2, 3)));
FILE * _open_memstream_r (struct _reent *, char **, size_t *);
void _perror_r (struct _reent *, const char *);
int _printf_r (struct _reent *, const char *restrict, ...)
               __attribute__ ((__format__ (__printf__, 2, 3)));
int _putc_r (struct _reent *, int, FILE *);
int _putc_unlocked_r (struct _reent *, int, FILE *);
int _putchar_unlocked_r (struct _reent *, int);
int _putchar_r (struct _reent *, int);
int _puts_r (struct _reent *, const char *);
int _remove_r (struct _reent *, const char *);
int _rename_r (struct _reent *,
      const char *_old, const char *_new);
int _scanf_r (struct _reent *, const char *restrict, ...)
               __attribute__ ((__format__ (__scanf__, 2, 3)));
int _siprintf_r (struct _reent *, char *, const char *, ...)
               __attribute__ ((__format__ (__printf__, 3, 4)));
int _siscanf_r (struct _reent *, const char *, const char *, ...)
               __attribute__ ((__format__ (__scanf__, 3, 4)));
int _sniprintf_r (struct _reent *, char *, size_t, const char *, ...)
               __attribute__ ((__format__ (__printf__, 4, 5)));
int _snprintf_r (struct _reent *, char *restrict, size_t, const char *restrict, ...)
               __attribute__ ((__format__ (__printf__, 4, 5)));
int _sprintf_r (struct _reent *, char *restrict, const char *restrict, ...)
               __attribute__ ((__format__ (__printf__, 3, 4)));
int _sscanf_r (struct _reent *, const char *restrict, const char *restrict, ...)
               __attribute__ ((__format__ (__scanf__, 3, 4)));
char * _tempnam_r (struct _reent *, const char *, const char *);
FILE * _tmpfile_r (struct _reent *);
char * _tmpnam_r (struct _reent *, char *);
int _ungetc_r (struct _reent *, int, FILE *);
int _vasiprintf_r (struct _reent *, char **, const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 3, 0)));
char * _vasniprintf_r (struct _reent*, char *, size_t *, const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 4, 0)));
char * _vasnprintf_r (struct _reent*, char *, size_t *, const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 4, 0)));
int _vasprintf_r (struct _reent *, char **, const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 3, 0)));
int _vdiprintf_r (struct _reent *, int, const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 3, 0)));
int _vdprintf_r (struct _reent *, int, const char *restrict, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 3, 0)));
int _vfiprintf_r (struct _reent *, FILE *, const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 3, 0)));
int _vfiscanf_r (struct _reent *, FILE *, const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__scanf__, 3, 0)));
int _vfprintf_r (struct _reent *, FILE *restrict, const char *restrict, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 3, 0)));
int _vfscanf_r (struct _reent *, FILE *restrict, const char *restrict, __gnuc_va_list)
               __attribute__ ((__format__ (__scanf__, 3, 0)));
int _viprintf_r (struct _reent *, const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 2, 0)));
int _viscanf_r (struct _reent *, const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__scanf__, 2, 0)));
int _vprintf_r (struct _reent *, const char *restrict, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 2, 0)));
int _vscanf_r (struct _reent *, const char *restrict, __gnuc_va_list)
               __attribute__ ((__format__ (__scanf__, 2, 0)));
int _vsiprintf_r (struct _reent *, char *, const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 3, 0)));
int _vsiscanf_r (struct _reent *, const char *, const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__scanf__, 3, 0)));
int _vsniprintf_r (struct _reent *, char *, size_t, const char *, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 4, 0)));
int _vsnprintf_r (struct _reent *, char *restrict, size_t, const char *restrict, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 4, 0)));
int _vsprintf_r (struct _reent *, char *restrict, const char *restrict, __gnuc_va_list)
               __attribute__ ((__format__ (__printf__, 3, 0)));
int _vsscanf_r (struct _reent *, const char *restrict, const char *restrict, __gnuc_va_list)
               __attribute__ ((__format__ (__scanf__, 3, 0)));



int fpurge (FILE *);
ssize_t __getdelim (char **, size_t *, int, FILE *);
ssize_t __getline (char **, size_t *, FILE *);


void clearerr_unlocked (FILE *);
int feof_unlocked (FILE *);
int ferror_unlocked (FILE *);
int fileno_unlocked (FILE *);
int fflush_unlocked (FILE *);
int fgetc_unlocked (FILE *);
int fputc_unlocked (int, FILE *);
size_t fread_unlocked (void *restrict, size_t _size, size_t _n, FILE *restrict);
size_t fwrite_unlocked (const void *restrict , size_t _size, size_t _n, FILE *);
# 577 "/usr/include/newlib/stdio.h" 3
int __srget_r (struct _reent *, FILE *);
int __swbuf_r (struct _reent *, int, FILE *);
# 601 "/usr/include/newlib/stdio.h" 3
FILE *funopen (const void *__cookie,
  int (*__readfn)(void *__cookie, char *__buf,
    int __n),
  int (*__writefn)(void *__cookie, const char *__buf,
     int __n),
  fpos_t (*__seekfn)(void *__cookie, fpos_t __off, int __whence),
  int (*__closefn)(void *__cookie));
FILE *_funopen_r (struct _reent *, const void *__cookie,
  int (*__readfn)(void *__cookie, char *__buf,
    int __n),
  int (*__writefn)(void *__cookie, const char *__buf,
     int __n),
  fpos_t (*__seekfn)(void *__cookie, fpos_t __off, int __whence),
  int (*__closefn)(void *__cookie));
# 687 "/usr/include/newlib/stdio.h" 3
static __inline__ int __sputc_r(struct _reent *_ptr, int _c, FILE *_p) {




 if (--_p->_w >= 0 || (_p->_w >= _p->_lbfsize && (char)_c != '\n'))
  return (*_p->_p++ = _c);
 else
  return (__swbuf_r(_ptr, _c, _p));
}
# 741 "/usr/include/newlib/stdio.h" 3
static __inline int
_getchar_unlocked(void)
{
 struct _reent *_ptr;

 _ptr = _impure_ptr;
 return ((--(((_ptr)->_stdin))->_r < 0 ? __srget_r(_ptr, ((_ptr)->_stdin)) : (int)(*(((_ptr)->_stdin))->_p++)));
}

static __inline int
_putchar_unlocked(int _c)
{
 struct _reent *_ptr;

 _ptr = _impure_ptr;
 return (__sputc_r(_ptr, _c, ((_ptr)->_stdout)));
}
# 797 "/usr/include/newlib/stdio.h" 3

# 25 "m1b.c" 2
# 1 "/usr/include/newlib/unistd.h" 1 3



# 1 "/usr/include/newlib/sys/unistd.h" 1 3
# 14 "/usr/include/newlib/sys/unistd.h" 3
# 1 "/usr/lib/gcc/arm-none-eabi/10.3.1/include/stddef.h" 1 3 4
# 15 "/usr/include/newlib/sys/unistd.h" 2 3

extern char **environ;

void _exit (int __status) __attribute__ ((__noreturn__));

int access (const char *__path, int __amode);
unsigned alarm (unsigned __secs);
int chdir (const char *__path);
int chmod (const char *__path, mode_t __mode);

int chown (const char *__path, uid_t __owner, gid_t __group);


int chroot (const char *__path);

int close (int __fildes);

size_t confstr (int __name, char *__buf, size_t __len);
# 44 "/usr/include/newlib/sys/unistd.h" 3
int daemon (int nochdir, int noclose);

int dup (int __fildes);
int dup2 (int __fildes, int __fildes2);
# 56 "/usr/include/newlib/sys/unistd.h" 3
void endusershell (void);




int execl (const char *__path, const char *, ...);
int execle (const char *__path, const char *, ...);
int execlp (const char *__file, const char *, ...);

int execlpe (const char *__file, const char *, ...);

int execv (const char *__path, char * const __argv[]);
int execve (const char *__path, char * const __argv[], char * const __envp[]);
int execvp (const char *__file, char * const __argv[]);




int faccessat (int __dirfd, const char *__path, int __mode, int __flags);


int fchdir (int __fildes);


int fchmod (int __fildes, mode_t __mode);



int fchown (int __fildes, uid_t __owner, gid_t __group);



int fchownat (int __dirfd, const char *__path, uid_t __owner, gid_t __group, int __flags);


int fexecve (int __fd, char * const __argv[], char * const __envp[]);

pid_t fork (void);
long fpathconf (int __fd, int __name);
int fsync (int __fd);

int fdatasync (int __fd);




char * getcwd (char *__buf, size_t __size);

int getdomainname (char *__name, size_t __len);


int getentropy (void *, size_t);


gid_t getegid (void);
uid_t geteuid (void);
gid_t getgid (void);

int getgroups (int __gidsetsize, gid_t __grouplist[]);

long gethostid (void);

char * getlogin (void);




char * getpass (const char *__prompt);
int getpagesize (void);


int getpeereid (int, uid_t *, gid_t *);


pid_t getpgid (pid_t);

pid_t getpgrp (void);
pid_t getpid (void);
pid_t getppid (void);

pid_t getsid (pid_t);


uid_t getuid (void);


char * getusershell (void);


char * getwd (char *__buf);


int iruserok (unsigned long raddr, int superuser, const char *ruser, const char *luser);

int isatty (int __fildes);

int issetugid (void);



int lchown (const char *__path, uid_t __owner, gid_t __group);


int link (const char *__path1, const char *__path2);

int linkat (int __dirfd1, const char *__path1, int __dirfd2, const char *__path2, int __flags);


int nice (int __nice_value);


off_t lseek (int __fildes, off_t __offset, int __whence);






int lockf (int __fd, int __cmd, off_t __len);

long pathconf (const char *__path, int __name);
int pause (void);

int pthread_atfork (void (*)(void), void (*)(void), void (*)(void));

int pipe (int __fildes[2]);




ssize_t pread (int __fd, void *__buf, size_t __nbytes, off_t __offset);
ssize_t pwrite (int __fd, const void *__buf, size_t __nbytes, off_t __offset);

int read (int __fd, void *__buf, size_t __nbyte);

int rresvport (int *__alport);
int revoke (char *__path);

int rmdir (const char *__path);

int ruserok (const char *rhost, int superuser, const char *ruser, const char *luser);


void * sbrk (ptrdiff_t __incr);



int setegid (gid_t __gid);
int seteuid (uid_t __uid);

int setgid (gid_t __gid);


int setgroups (int ngroups, const gid_t *grouplist);


int sethostname (const char *, size_t);

int setpgid (pid_t __pid, pid_t __pgid);

int setpgrp (void);


int setregid (gid_t __rgid, gid_t __egid);
int setreuid (uid_t __ruid, uid_t __euid);

pid_t setsid (void);

int setuid (uid_t __uid);


void setusershell (void);

unsigned sleep (unsigned int __seconds);



long sysconf (int __name);
pid_t tcgetpgrp (int __fildes);
int tcsetpgrp (int __fildes, pid_t __pgrp_id);
char * ttyname (int __fildes);
int ttyname_r (int, char *, size_t);
int unlink (const char *__path);

int usleep (useconds_t __useconds);


int vhangup (void);

int write (int __fd, const void *__buf, size_t __nbyte);






extern char *optarg;
extern int optind, opterr, optopt;
int getopt(int, char * const [], const char *);
extern int optreset;



pid_t vfork (void);
# 283 "/usr/include/newlib/sys/unistd.h" 3
int ftruncate (int __fd, off_t __length);


int truncate (const char *, off_t __length);




int getdtablesize (void);


useconds_t ualarm (useconds_t __useconds, useconds_t __interval);





 int gethostname (char *__name, size_t __len);




int setdtablesize (int);



void sync (void);



ssize_t readlink (const char *restrict __path,
                          char *restrict __buf, size_t __buflen);
int symlink (const char *__name1, const char *__name2);


ssize_t readlinkat (int __dirfd1, const char *restrict __path,
                            char *restrict __buf, size_t __buflen);
int symlinkat (const char *, int, const char *);
int unlinkat (int, const char *, int);
# 5 "/usr/include/newlib/unistd.h" 2 3
# 26 "m1b.c" 2
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/rcc.h" 1
# 20 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/rcc.h"
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/cm3/common.h" 1
# 63 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/cm3/common.h"
# 1 "/usr/lib/gcc/arm-none-eabi/10.3.1/include/stdint.h" 1 3 4
# 34 "/usr/lib/gcc/arm-none-eabi/10.3.1/include/stdint.h" 3 4
typedef signed char int8_t;


typedef short int int16_t;


typedef long int int32_t;


typedef long long int int64_t;


typedef unsigned char uint8_t;


typedef short unsigned int uint16_t;


typedef long unsigned int uint32_t;


typedef long long unsigned int uint64_t;




typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef long int int_least32_t;
typedef long long int int_least64_t;
typedef unsigned char uint_least8_t;
typedef short unsigned int uint_least16_t;
typedef long unsigned int uint_least32_t;
typedef long long unsigned int uint_least64_t;



typedef int int_fast8_t;
typedef int int_fast16_t;
typedef int int_fast32_t;
typedef long long int int_fast64_t;
typedef unsigned int uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef long long unsigned int uint_fast64_t;




typedef int intptr_t;


typedef unsigned int uintptr_t;




typedef long long int intmax_t;
typedef long long unsigned int uintmax_t;
# 64 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/cm3/common.h" 2
# 1 "/usr/lib/gcc/arm-none-eabi/10.3.1/include/stdbool.h" 1 3 4
# 65 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/cm3/common.h" 2
# 21 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/rcc.h" 2
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/memorymap.h" 1
# 40 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/memorymap.h"
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/memorymap.h" 1
# 21 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/memorymap.h"
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/cm3/memorymap.h" 1
# 22 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/memorymap.h" 2
# 41 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/memorymap.h" 2
# 22 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/rcc.h" 2
# 40 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/rcc.h"
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/rcc.h" 1
# 42 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/rcc.h"
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/pwr.h" 1
# 40 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/pwr.h"
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/pwr.h" 1
# 165 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/pwr.h"

# 165 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/pwr.h"
enum pwr_vos_scale {
 PWR_SCALE1,
 PWR_SCALE2,
};



void pwr_set_vos_scale(enum pwr_vos_scale scale);
void pwr_disable_backup_domain_write_protect(void);
void pwr_enable_backup_domain_write_protect(void);


# 41 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/pwr.h" 2
# 43 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/rcc.h" 2
# 743 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/rcc.h"
struct rcc_clock_scale {
 uint8_t pllm;
 uint16_t plln;
 uint8_t pllp;
 uint8_t pllq;
 uint8_t pllr;
 uint8_t pll_source;
 uint32_t flash_config;
 uint8_t hpre;
 uint8_t ppre1;
 uint8_t ppre2;
 enum pwr_vos_scale voltage_scale;
 uint32_t ahb_frequency;
 uint32_t apb1_frequency;
 uint32_t apb2_frequency;
};

enum rcc_clock_config_entry {
 RCC_CLOCK_VRANGE1_80MHZ,
 RCC_CLOCK_CONFIG_END
};

extern const struct rcc_clock_scale rcc_hsi16_configs[RCC_CLOCK_CONFIG_END];



extern uint32_t rcc_ahb_frequency;
extern uint32_t rcc_apb1_frequency;
extern uint32_t rcc_apb2_frequency;





enum rcc_osc {
 RCC_PLL, RCC_HSE, RCC_HSI16, RCC_MSI, RCC_LSE, RCC_LSI, RCC_HSI48
};




enum rcc_periph_clken {


 RCC_TSC = (((0x48) << 5) + (16)),
 RCC_CRC = (((0x48) << 5) + (12)),
 RCC_FLASH = (((0x48) << 5) + (8)),
 RCC_DMA2 = (((0x48) << 5) + (1)),
 RCC_DMA1 = (((0x48) << 5) + (0)),


 RCC_RNG = (((0x4c) << 5) + (18)),
 RCC_AES = (((0x4c) << 5) + (16)),
 RCC_ADC = (((0x4c) << 5) + (13)),
 RCC_ADC1 = (((0x4c) << 5) + (13)),
 RCC_OTGFS = (((0x4c) << 5) + (12)),
 RCC_GPIOH = (((0x4c) << 5) + (7)),
 RCC_GPIOG = (((0x4c) << 5) + (6)),
 RCC_GPIOF = (((0x4c) << 5) + (5)),
 RCC_GPIOE = (((0x4c) << 5) + (4)),
 RCC_GPIOD = (((0x4c) << 5) + (3)),
 RCC_GPIOC = (((0x4c) << 5) + (2)),
 RCC_GPIOB = (((0x4c) << 5) + (1)),
 RCC_GPIOA = (((0x4c) << 5) + (0)),


 RCC_QSPI = (((0x50) << 5) + (8)),
 RCC_FMC = (((0x50) << 5) + (0)),


 RCC_LPTIM1 = (((0x58) << 5) + (31)),
 RCC_OPAMP = (((0x58) << 5) + (30)),
 RCC_DAC1 = (((0x58) << 5) + (29)),
 RCC_PWR = (((0x58) << 5) + (28)),
 RCC_USB = (((0x58) << 5) + (26)),
 RCC_CAN2 = (((0x58) << 5) + (26)),
 RCC_CAN1 = (((0x58) << 5) + (25)),
 RCC_CRS = (((0x58) << 5) + (24)),
 RCC_I2C3 = (((0x58) << 5) + (23)),
 RCC_I2C2 = (((0x58) << 5) + (22)),
 RCC_I2C1 = (((0x58) << 5) + (21)),
 RCC_UART5 = (((0x58) << 5) + (20)),
 RCC_UART4 = (((0x58) << 5) + (19)),
 RCC_USART3 = (((0x58) << 5) + (18)),
 RCC_USART2 = (((0x58) << 5) + (17)),
 RCC_SPI3 = (((0x58) << 5) + (15)),
 RCC_SPI2 = (((0x58) << 5) + (14)),
 RCC_LCD = (((0x58) << 5) + (9)),
 RCC_TIM7 = (((0x58) << 5) + (5)),
 RCC_TIM6 = (((0x58) << 5) + (4)),
 RCC_TIM5 = (((0x58) << 5) + (3)),
 RCC_TIM4 = (((0x58) << 5) + (2)),
 RCC_TIM3 = (((0x58) << 5) + (1)),
 RCC_TIM2 = (((0x58) << 5) + (0)),

 RCC_LPTIM2 = (((0x5c) << 5) + (5)),
 RCC_SWPMI1 = (((0x5c) << 5) + (2)),
 RCC_LPUART1 = (((0x5c) << 5) + (0)),


 RCC_DFSDM = (((0x60) << 5) + (24)),
 RCC_SAI2 = (((0x60) << 5) + (22)),
 RCC_SAI1 = (((0x60) << 5) + (21)),
 RCC_TIM17 = (((0x60) << 5) + (18)),
 RCC_TIM16 = (((0x60) << 5) + (17)),
 RCC_TIM15 = (((0x60) << 5) + (16)),
 RCC_USART1 = (((0x60) << 5) + (14)),
 RCC_TIM8 = (((0x60) << 5) + (13)),
 RCC_SPI1 = (((0x60) << 5) + (12)),
 RCC_TIM1 = (((0x60) << 5) + (11)),
 RCC_SDMMC1 = (((0x60) << 5) + (10)),
 RCC_FW = (((0x60) << 5) + (7)),
 RCC_SYSCFG = (((0x60) << 5) + (0)),


 SCC_TSC = (((0x68) << 5) + (16)),
 SCC_CRC = (((0x68) << 5) + (12)),
 SCC_SRAM1 = (((0x68) << 5) + (9)),
 SCC_FLASH = (((0x68) << 5) + (8)),
 SCC_DMA2 = (((0x68) << 5) + (1)),
 SCC_DMA1 = (((0x68) << 5) + (0)),


 SCC_RNG = (((0x6c) << 5) + (18)),
 SCC_AES = (((0x6c) << 5) + (16)),
 SCC_ADC = (((0x6c) << 5) + (13)),
 SCC_ADC1 = (((0x6c) << 5) + (13)),
 SCC_OTGFS = (((0x6c) << 5) + (12)),
 SCC_SRAM2 = (((0x6c) << 5) + (9)),
 SCC_GPIOH = (((0x6c) << 5) + (7)),
 SCC_GPIOG = (((0x6c) << 5) + (6)),
 SCC_GPIOF = (((0x6c) << 5) + (5)),
 SCC_GPIOE = (((0x6c) << 5) + (4)),
 SCC_GPIOD = (((0x6c) << 5) + (3)),
 SCC_GPIOC = (((0x6c) << 5) + (2)),
 SCC_GPIOB = (((0x6c) << 5) + (1)),
 SCC_GPIOA = (((0x6c) << 5) + (0)),


 SCC_QSPI = (((0x70) << 5) + (8)),
 SCC_FMC = (((0x70) << 5) + (0)),


 SCC_LPTIM1 = (((0x58) << 5) + (31)),
 SCC_OPAMP = (((0x58) << 5) + (30)),
 SCC_DAC1 = (((0x58) << 5) + (29)),
 SCC_PWR = (((0x58) << 5) + (28)),
 SCC_CAN2 = (((0x58) << 5) + (26)),
 SCC_CAN1 = (((0x58) << 5) + (25)),
 SCC_I2C3 = (((0x58) << 5) + (23)),
 SCC_I2C2 = (((0x58) << 5) + (22)),
 SCC_I2C1 = (((0x58) << 5) + (21)),
 SCC_UART5 = (((0x58) << 5) + (20)),
 SCC_UART4 = (((0x58) << 5) + (19)),
 SCC_USART3 = (((0x58) << 5) + (18)),
 SCC_USART2 = (((0x58) << 5) + (17)),
 SCC_SPI3 = (((0x58) << 5) + (15)),
 SCC_SPI2 = (((0x58) << 5) + (14)),
 SCC_WWDG = (((0x58) << 5) + (11)),
 SCC_LCD = (((0x58) << 5) + (9)),
 SCC_TIM7 = (((0x58) << 5) + (5)),
 SCC_TIM6 = (((0x58) << 5) + (4)),
 SCC_TIM5 = (((0x58) << 5) + (3)),
 SCC_TIM4 = (((0x58) << 5) + (2)),
 SCC_TIM3 = (((0x58) << 5) + (1)),
 SCC_TIM2 = (((0x58) << 5) + (0)),

 SCC_LPTIM2 = (((0x5c) << 5) + (5)),
 SCC_SWPMI1 = (((0x5c) << 5) + (2)),
 SCC_LPUART1 = (((0x5c) << 5) + (0)),


 SCC_DFSDM = (((0x60) << 5) + (24)),
 SCC_SAI2 = (((0x60) << 5) + (22)),
 SCC_SAI1 = (((0x60) << 5) + (21)),
 SCC_TIM17 = (((0x60) << 5) + (18)),
 SCC_TIM16 = (((0x60) << 5) + (17)),
 SCC_TIM15 = (((0x60) << 5) + (16)),
 SCC_USART1 = (((0x60) << 5) + (14)),
 SCC_TIM8 = (((0x60) << 5) + (13)),
 SCC_SPI1 = (((0x60) << 5) + (12)),
 SCC_TIM1 = (((0x60) << 5) + (11)),
 SCC_SDMMC1 = (((0x60) << 5) + (10)),
 SCC_SYSCFG = (((0x60) << 5) + (0)),
};

enum rcc_periph_rst {

 RST_TSC = (((0x28) << 5) + (16)),
 RST_CRC = (((0x28) << 5) + (12)),
 RST_FLASH = (((0x28) << 5) + (8)),
 RST_DMA2 = (((0x28) << 5) + (1)),
 RST_DMA1 = (((0x28) << 5) + (0)),


 RST_RNG = (((0x2c) << 5) + (18)),
 RST_AES = (((0x2c) << 5) + (16)),
 RST_ADC = (((0x2c) << 5) + (13)),
 RST_ADC1 = (((0x2c) << 5) + (13)),
 RST_OTGFS = (((0x2c) << 5) + (12)),
 RST_GPIOH = (((0x2c) << 5) + (7)),
 RST_GPIOG = (((0x2c) << 5) + (6)),
 RST_GPIOF = (((0x2c) << 5) + (5)),
 RST_GPIOE = (((0x2c) << 5) + (4)),
 RST_GPIOD = (((0x2c) << 5) + (3)),
 RST_GPIOC = (((0x2c) << 5) + (2)),
 RST_GPIOB = (((0x2c) << 5) + (1)),
 RST_GPIOA = (((0x2c) << 5) + (0)),


 RST_QSPI = (((0x30) << 5) + (8)),
 RST_FMC = (((0x30) << 5) + (0)),


 RST_LPTIM1 = (((0x38) << 5) + (31)),
 RST_OPAMP = (((0x38) << 5) + (30)),
 RST_DAC1 = (((0x38) << 5) + (29)),
 RST_PWR = (((0x38) << 5) + (28)),
 RST_USB = (((0x38) << 5) + (26)),
 RST_CAN2 = (((0x38) << 5) + (26)),
 RST_CAN1 = (((0x38) << 5) + (25)),
 RST_CRS = (((0x38) << 5) + (24)),
 RST_I2C3 = (((0x38) << 5) + (23)),
 RST_I2C2 = (((0x38) << 5) + (22)),
 RST_I2C1 = (((0x38) << 5) + (21)),
 RST_UART5 = (((0x38) << 5) + (20)),
 RST_UART4 = (((0x38) << 5) + (19)),
 RST_USART3 = (((0x38) << 5) + (18)),
 RST_USART2 = (((0x38) << 5) + (17)),
 RST_SPI3 = (((0x38) << 5) + (15)),
 RST_SPI2 = (((0x38) << 5) + (14)),
 RST_LCD = (((0x38) << 5) + (9)),
 RST_TIM7 = (((0x38) << 5) + (5)),
 RST_TIM6 = (((0x38) << 5) + (4)),
 RST_TIM5 = (((0x38) << 5) + (3)),
 RST_TIM4 = (((0x38) << 5) + (2)),
 RST_TIM3 = (((0x38) << 5) + (1)),
 RST_TIM2 = (((0x38) << 5) + (0)),

 RST_LPTIM2 = (((0x3c) << 5) + (5)),
 RST_SWPMI1 = (((0x3c) << 5) + (2)),
 RST_LPUART1 = (((0x3c) << 5) + (0)),


 RST_DFSDM = (((0x40) << 5) + (24)),
 RST_SAI2 = (((0x40) << 5) + (22)),
 RST_SAI1 = (((0x40) << 5) + (21)),
 RST_TIM17 = (((0x40) << 5) + (18)),
 RST_TIM16 = (((0x40) << 5) + (17)),
 RST_TIM15 = (((0x40) << 5) + (16)),
 RST_USART1 = (((0x40) << 5) + (14)),
 RST_TIM8 = (((0x40) << 5) + (13)),
 RST_SPI1 = (((0x40) << 5) + (12)),
 RST_TIM1 = (((0x40) << 5) + (11)),
 RST_SDMMC1 = (((0x40) << 5) + (10)),
 RST_SYSCFG = (((0x40) << 5) + (0)),

};
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/rcc_common_all.h" 1
# 39 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/rcc_common_all.h"


void rcc_peripheral_enable_clock(volatile uint32_t *reg, uint32_t en);
void rcc_peripheral_disable_clock(volatile uint32_t *reg, uint32_t en);
void rcc_peripheral_reset(volatile uint32_t *reg, uint32_t reset);
void rcc_peripheral_clear_reset(volatile uint32_t *reg, uint32_t clear_reset);

void rcc_periph_clock_enable(enum rcc_periph_clken clken);
void rcc_periph_clock_disable(enum rcc_periph_clken clken);
void rcc_periph_reset_pulse(enum rcc_periph_rst rst);
void rcc_periph_reset_hold(enum rcc_periph_rst rst);
void rcc_periph_reset_release(enum rcc_periph_rst rst);

void rcc_set_mco(uint32_t mcosrc);
void rcc_osc_bypass_enable(enum rcc_osc osc);
void rcc_osc_bypass_disable(enum rcc_osc osc);







# 61 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/rcc_common_all.h" 3 4
_Bool 
# 61 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/rcc_common_all.h"
    rcc_is_osc_ready(enum rcc_osc osc);






void rcc_wait_for_osc_ready(enum rcc_osc osc);






uint16_t rcc_get_div_from_hpre(uint8_t div_val);


# 1002 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/rcc.h" 2



void rcc_osc_ready_int_clear(enum rcc_osc osc);
void rcc_osc_ready_int_enable(enum rcc_osc osc);
void rcc_osc_ready_int_disable(enum rcc_osc osc);
int rcc_osc_ready_int_flag(enum rcc_osc osc);
void rcc_css_int_clear(void);
int rcc_css_int_flag(void);
void rcc_wait_for_sysclk_status(enum rcc_osc osc);
void rcc_osc_on(enum rcc_osc osc);
void rcc_osc_off(enum rcc_osc osc);
void rcc_css_enable(void);
void rcc_css_disable(void);
void rcc_set_sysclk_source(uint32_t clk);
void rcc_set_pll_source(uint32_t pllsrc);
void rcc_set_ppre2(uint32_t ppre2);
void rcc_set_ppre1(uint32_t ppre1);
void rcc_set_hpre(uint32_t hpre);
void rcc_set_main_pll(uint32_t source, uint32_t pllm, uint32_t plln, uint32_t pllp, uint32_t pllq, uint32_t pllr);
uint32_t rcc_system_clock_source(void);
void rcc_clock_setup_pll(const struct rcc_clock_scale *clock);
void rcc_set_msi_range(uint32_t msi_range);
void rcc_set_msi_range_standby(uint32_t msi_range);
void rcc_pll_output_enable(uint32_t pllout);
void rcc_set_clock48_source(uint32_t clksel);
void rcc_enable_rtc_clock(void);
void rcc_disable_rtc_clock(void);
void rcc_set_rtc_clock_source(enum rcc_osc clk);
uint32_t rcc_get_usart_clk_freq(uint32_t usart);
uint32_t rcc_get_timer_clk_freq(uint32_t timer);
uint32_t rcc_get_i2c_clk_freq(uint32_t i2c);
uint32_t rcc_get_spi_clk_freq(uint32_t spi);


# 41 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/rcc.h" 2
# 27 "m1b.c" 2
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/gpio.h" 1
# 40 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/gpio.h"
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/gpio.h" 1
# 35 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/gpio.h"
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/gpio_common_f24.h" 1
# 41 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/gpio_common_f24.h"
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/gpio_common_f234.h" 1
# 41 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/gpio_common_f234.h"
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/gpio_common_all.h" 1
# 72 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/gpio_common_all.h"


void gpio_set(uint32_t gpioport, uint16_t gpios);
void gpio_clear(uint32_t gpioport, uint16_t gpios);
uint16_t gpio_get(uint32_t gpioport, uint16_t gpios);
void gpio_toggle(uint32_t gpioport, uint16_t gpios);
uint16_t gpio_port_read(uint32_t gpioport);
void gpio_port_write(uint32_t gpioport, uint16_t data);
void gpio_port_config_lock(uint32_t gpioport, uint16_t gpios);


# 42 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/gpio_common_f234.h" 2
# 270 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/gpio_common_f234.h"

# 280 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/gpio_common_f234.h"
void gpio_mode_setup(uint32_t gpioport, uint8_t mode, uint8_t pull_up_down,
       uint16_t gpios);
void gpio_set_output_options(uint32_t gpioport, uint8_t otype, uint8_t speed,
        uint16_t gpios);
void gpio_set_af(uint32_t gpioport, uint8_t alt_func_num, uint16_t gpios);


# 42 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/gpio_common_f24.h" 2
# 36 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/gpio.h" 2
# 87 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/gpio.h"



# 41 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/gpio.h" 2
# 28 "m1b.c" 2
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/cm3/nvic.h" 1
# 147 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/cm3/nvic.h"
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/dispatch/nvic.h" 1
# 22 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/dispatch/nvic.h"
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/nvic.h" 1
# 9 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/nvic.h"
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/cm3/nvic.h" 1
# 10 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/nvic.h" 2
# 117 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/nvic.h"


void wwdg_isr(void);
void pvd_pvm_isr(void);
void tamp_stamp_isr(void);
void rtc_wkup_isr(void);
void flash_isr(void);
void rcc_isr(void);
void exti0_isr(void);
void exti1_isr(void);
void exti2_isr(void);
void exti3_isr(void);
void exti4_isr(void);
void dma1_channel1_isr(void);
void dma1_channel2_isr(void);
void dma1_channel3_isr(void);
void dma1_channel4_isr(void);
void dma1_channel5_isr(void);
void dma1_channel6_isr(void);
void dma1_channel7_isr(void);
void adc1_2_isr(void);
void can1_tx_isr(void);
void can1_rx0_isr(void);
void can1_rx1_isr(void);
void can1_sce_isr(void);
void exti9_5_isr(void);
void tim1_brk_tim15_isr(void);
void tim1_up_tim16_isr(void);
void tim1_trg_com_tim17_isr(void);
void tim1_cc_isr(void);
void tim2_isr(void);
void tim3_isr(void);
void tim4_isr(void);
void i2c1_ev_isr(void);
void i2c1_er_isr(void);
void i2c2_ev_isr(void);
void i2c2_er_isr(void);
void spi1_isr(void);
void spi2_isr(void);
void usart1_isr(void);
void usart2_isr(void);
void usart3_isr(void);
void exti15_10_isr(void);
void rtc_alarm_isr(void);
void dfsdm3_isr(void);
void tim8_brk_isr(void);
void tim8_up_isr(void);
void tim8_trg_com_isr(void);
void tim8_cc_isr(void);
void adc3_isr(void);
void fmc_isr(void);
void sdmmc1_isr(void);
void tim5_isr(void);
void spi3_isr(void);
void uart4_isr(void);
void uart5_isr(void);
void tim6_dacunder_isr(void);
void tim7_isr(void);
void dma2_channel1_isr(void);
void dma2_channel2_isr(void);
void dma2_channel3_isr(void);
void dma2_channel4_isr(void);
void dma2_channel5_isr(void);
void dfsdm0_isr(void);
void dfsdm1_isr(void);
void dfsdm2_isr(void);
void comp_isr(void);
void lptim1_isr(void);
void lptim2_isr(void);
void otg_fs_isr(void);
void dma2_channel6_isr(void);
void dma2_channel7_isr(void);
void lpuart1_isr(void);
void quadspi_isr(void);
void i2c3_ev_isr(void);
void i2c3_er_isr(void);
void sai1_isr(void);
void sai2_isr(void);
void swpmi1_isr(void);
void tsc_isr(void);
void lcd_isr(void);
void aes_isr(void);
void rng_isr(void);
void fpu_isr(void);
void hash_crs_isr(void);
void i2c4_ev_isr(void);
void i2c4_er_isr(void);
void dcmi_isr(void);
void can2_tx_isr(void);
void can2_rx0_isr(void);
void can2_rx1_isr(void);
void can2_sce_isr(void);
void dma2d_isr(void);


# 23 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/dispatch/nvic.h" 2
# 148 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/cm3/nvic.h" 2





void nvic_enable_irq(uint8_t irqn);
void nvic_disable_irq(uint8_t irqn);
uint8_t nvic_get_pending_irq(uint8_t irqn);
void nvic_set_pending_irq(uint8_t irqn);
void nvic_clear_pending_irq(uint8_t irqn);
uint8_t nvic_get_irq_enabled(uint8_t irqn);
void nvic_set_priority(uint8_t irqn, uint8_t priority);



uint8_t nvic_get_active_irq(uint8_t irqn);
void nvic_generate_software_interrupt(uint16_t irqn);


void reset_handler(void);
void nmi_handler(void);
void hard_fault_handler(void);
void sv_call_handler(void);
void pend_sv_handler(void);
void sys_tick_handler(void);



void mem_manage_handler(void);
void bus_fault_handler(void);
void usage_fault_handler(void);
void debug_monitor_handler(void);



# 29 "m1b.c" 2
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/exti.h" 1
# 42 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/exti.h"
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/exti.h" 1
# 31 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/exti.h"
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/exti_common_all.h" 1
# 74 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/exti_common_all.h"
enum exti_trigger_type {
 EXTI_TRIGGER_RISING,
 EXTI_TRIGGER_FALLING,
 EXTI_TRIGGER_BOTH,
};



void exti_set_trigger(uint32_t extis, enum exti_trigger_type trig);
void exti_enable_request(uint32_t extis);
void exti_disable_request(uint32_t extis);
void exti_reset_request(uint32_t extis);
void exti_select_source(uint32_t exti, uint32_t gpioport);
uint32_t exti_get_flag_status(uint32_t exti);


# 32 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/exti.h" 2
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/exti_common_v1.h" 1

       
# 45 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/exti_common_v1.h"



# 33 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/exti.h" 2
# 43 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/exti.h" 2
# 30 "m1b.c" 2
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/flash.h" 1
# 40 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/flash.h"
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/flash.h" 1
# 44 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/flash.h"
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/flash_common_all.h" 1
# 21 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/flash_common_all.h"
       




# 41 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/flash_common_all.h"
void flash_prefetch_enable(void);





void flash_prefetch_disable(void);
# 59 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/flash_common_all.h"
void flash_set_ws(uint32_t ws);




void flash_lock(void);





void flash_unlock(void);





void flash_unlock_option_bytes(void);


# 45 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/flash.h" 2
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/flash_common_f.h" 1
# 21 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/flash_common_f.h"
       








void flash_clear_eop_flag(void);





void flash_clear_status_flags(void);





void flash_wait_for_last_operation(void);


# 46 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/flash.h" 2
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/flash_common_idcache.h" 1
# 20 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/flash_common_idcache.h"
       

# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/flash.h" 1
# 40 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/flash.h"
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/flash.h" 1
# 41 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/flash.h" 2
# 23 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/flash_common_idcache.h" 2
# 36 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/flash_common_idcache.h"



void flash_dcache_enable(void);


void flash_dcache_disable(void);


void flash_icache_enable(void);


void flash_icache_disable(void);




void flash_dcache_reset(void);




void flash_icache_reset(void);


# 47 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/flash.h" 2
# 223 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/flash.h"


void flash_clear_progerr_flag(void);
void flash_clear_pgserr_flag(void);
void flash_clear_size_flag(void);
void flash_clear_pgaerr_flag(void);
void flash_clear_wrperr_flag(void);
void flash_lock_option_bytes(void);
void flash_program_double_word(uint32_t address, uint64_t data);
void flash_program(uint32_t address, uint8_t *data, uint32_t len);
void flash_erase_page(uint32_t page);
void flash_erase_all_pages(void);
void flash_program_option_bytes(uint32_t data);


# 41 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/flash.h" 2
# 31 "m1b.c" 2

# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/timer.h" 1
# 42 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/timer.h"
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/timer.h" 1
# 35 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/timer.h"
       
# 1 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/timer_common_all.h" 1
# 31 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/timer_common_all.h"
       
# 1061 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/timer_common_all.h"
enum tim_oc_id {
 TIM_OC1 = 0,
 TIM_OC1N,
 TIM_OC2,
 TIM_OC2N,
 TIM_OC3,
 TIM_OC3N,
 TIM_OC4,
};


enum tim_oc_mode {
 TIM_OCM_FROZEN,
 TIM_OCM_ACTIVE,
 TIM_OCM_INACTIVE,
 TIM_OCM_TOGGLE,
 TIM_OCM_FORCE_LOW,
 TIM_OCM_FORCE_HIGH,
 TIM_OCM_PWM1,
 TIM_OCM_PWM2,
};


enum tim_ic_id {
 TIM_IC1,
 TIM_IC2,
 TIM_IC3,
 TIM_IC4,
};
# 1098 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/timer_common_all.h"
enum tim_ic_filter {
 TIM_IC_OFF,
 TIM_IC_CK_INT_N_2,
 TIM_IC_CK_INT_N_4,
 TIM_IC_CK_INT_N_8,
 TIM_IC_DTF_DIV_2_N_6,
 TIM_IC_DTF_DIV_2_N_8,
 TIM_IC_DTF_DIV_4_N_6,
 TIM_IC_DTF_DIV_4_N_8,
 TIM_IC_DTF_DIV_8_N_6,
 TIM_IC_DTF_DIV_8_N_8,
 TIM_IC_DTF_DIV_16_N_5,
 TIM_IC_DTF_DIV_16_N_6,
 TIM_IC_DTF_DIV_16_N_8,
 TIM_IC_DTF_DIV_32_N_5,
 TIM_IC_DTF_DIV_32_N_6,
 TIM_IC_DTF_DIV_32_N_8,
};




enum tim_ic_psc {
 TIM_IC_PSC_OFF,
 TIM_IC_PSC_2,
 TIM_IC_PSC_4,
 TIM_IC_PSC_8,
};





enum tim_ic_input {
 TIM_IC_OUT = 0,
 TIM_IC_IN_TI1 = 1,
 TIM_IC_IN_TI2 = 2,
 TIM_IC_IN_TRC = 3,
 TIM_IC_IN_TI3 = 5,
 TIM_IC_IN_TI4 = 6,
};


enum tim_et_pol {
 TIM_ET_RISING,
 TIM_ET_FALLING,
};


enum tim_ecm2_state {
    TIM_ECM2_DISABLED,
    TIM_ECM2_ENABLED,
};





void timer_enable_irq(uint32_t timer_peripheral, uint32_t irq);
void timer_disable_irq(uint32_t timer_peripheral, uint32_t irq);

# 1158 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/timer_common_all.h" 3 4
_Bool 
# 1158 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/timer_common_all.h"
    timer_interrupt_source(uint32_t timer_peripheral, uint32_t flag);

# 1159 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/timer_common_all.h" 3 4
_Bool 
# 1159 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/timer_common_all.h"
    timer_get_flag(uint32_t timer_peripheral, uint32_t flag);
void timer_clear_flag(uint32_t timer_peripheral, uint32_t flag);
void timer_set_mode(uint32_t timer_peripheral, uint32_t clock_div,
      uint32_t alignment, uint32_t direction);
void timer_set_clock_division(uint32_t timer_peripheral, uint32_t clock_div);
void timer_enable_preload(uint32_t timer_peripheral);
void timer_disable_preload(uint32_t timer_peripheral);
void timer_set_alignment(uint32_t timer_peripheral, uint32_t alignment);
void timer_direction_up(uint32_t timer_peripheral);
void timer_direction_down(uint32_t timer_peripheral);
void timer_one_shot_mode(uint32_t timer_peripheral);
void timer_continuous_mode(uint32_t timer_peripheral);
void timer_update_on_any(uint32_t timer_peripheral);
void timer_update_on_overflow(uint32_t timer_peripheral);
void timer_enable_update_event(uint32_t timer_peripheral);
void timer_disable_update_event(uint32_t timer_peripheral);
void timer_enable_counter(uint32_t timer_peripheral);
void timer_disable_counter(uint32_t timer_peripheral);
void timer_set_output_idle_state(uint32_t timer_peripheral, uint32_t outputs);
void timer_reset_output_idle_state(uint32_t timer_peripheral, uint32_t outputs);
void timer_set_ti1_ch123_xor(uint32_t timer_peripheral);
void timer_set_ti1_ch1(uint32_t timer_peripheral);
void timer_set_master_mode(uint32_t timer_peripheral, uint32_t mode);
void timer_set_dma_on_compare_event(uint32_t timer_peripheral);
void timer_set_dma_on_update_event(uint32_t timer_peripheral);
void timer_enable_compare_control_update_on_trigger(uint32_t timer_peripheral);
void timer_disable_compare_control_update_on_trigger(uint32_t timer_peripheral);
void timer_enable_preload_complementry_enable_bits(uint32_t timer_peripheral);
void timer_disable_preload_complementry_enable_bits(uint32_t timer_peripheral);
void timer_set_prescaler(uint32_t timer_peripheral, uint32_t value);
void timer_set_repetition_counter(uint32_t timer_peripheral, uint32_t value);
void timer_set_period(uint32_t timer_peripheral, uint32_t period);
void timer_enable_oc_clear(uint32_t timer_peripheral, enum tim_oc_id oc_id);
void timer_disable_oc_clear(uint32_t timer_peripheral, enum tim_oc_id oc_id);
void timer_set_oc_fast_mode(uint32_t timer_peripheral, enum tim_oc_id oc_id);
void timer_set_oc_slow_mode(uint32_t timer_peripheral, enum tim_oc_id oc_id);
void timer_set_oc_mode(uint32_t timer_peripheral, enum tim_oc_id oc_id,
         enum tim_oc_mode oc_mode);
void timer_enable_oc_preload(uint32_t timer_peripheral, enum tim_oc_id oc_id);
void timer_disable_oc_preload(uint32_t timer_peripheral, enum tim_oc_id oc_id);
void timer_set_oc_polarity_high(uint32_t timer_peripheral,
    enum tim_oc_id oc_id);
void timer_set_oc_polarity_low(uint32_t timer_peripheral, enum tim_oc_id oc_id);
void timer_enable_oc_output(uint32_t timer_peripheral, enum tim_oc_id oc_id);
void timer_disable_oc_output(uint32_t timer_peripheral, enum tim_oc_id oc_id);
void timer_set_oc_idle_state_set(uint32_t timer_peripheral,
     enum tim_oc_id oc_id);
void timer_set_oc_idle_state_unset(uint32_t timer_peripheral,
       enum tim_oc_id oc_id);
void timer_set_oc_value(uint32_t timer_peripheral, enum tim_oc_id oc_id,
   uint32_t value);
void timer_enable_break_main_output(uint32_t timer_peripheral);
void timer_disable_break_main_output(uint32_t timer_peripheral);
void timer_enable_break_automatic_output(uint32_t timer_peripheral);
void timer_disable_break_automatic_output(uint32_t timer_peripheral);
void timer_set_break_polarity_high(uint32_t timer_peripheral);
void timer_set_break_polarity_low(uint32_t timer_peripheral);
void timer_enable_break(uint32_t timer_peripheral);
void timer_disable_break(uint32_t timer_peripheral);
void timer_set_enabled_off_state_in_run_mode(uint32_t timer_peripheral);
void timer_set_disabled_off_state_in_run_mode(uint32_t timer_peripheral);
void timer_set_enabled_off_state_in_idle_mode(uint32_t timer_peripheral);
void timer_set_disabled_off_state_in_idle_mode(uint32_t timer_peripheral);
void timer_set_break_lock(uint32_t timer_peripheral, uint32_t lock);
void timer_set_deadtime(uint32_t timer_peripheral, uint32_t deadtime);
void timer_generate_event(uint32_t timer_peripheral, uint32_t event);
uint32_t timer_get_counter(uint32_t timer_peripheral);
void timer_set_counter(uint32_t timer_peripheral, uint32_t count);

void timer_ic_set_filter(uint32_t timer, enum tim_ic_id ic,
    enum tim_ic_filter flt);
void timer_ic_set_prescaler(uint32_t timer, enum tim_ic_id ic,
       enum tim_ic_psc psc);
void timer_ic_set_input(uint32_t timer, enum tim_ic_id ic,
   enum tim_ic_input in);
void timer_ic_enable(uint32_t timer, enum tim_ic_id ic);
void timer_ic_disable(uint32_t timer, enum tim_ic_id ic);

void timer_slave_set_filter(uint32_t timer, enum tim_ic_filter flt);
void timer_slave_set_prescaler(uint32_t timer, enum tim_ic_psc psc);
void timer_slave_set_polarity(uint32_t timer, enum tim_et_pol pol);
void timer_slave_set_mode(uint32_t timer, uint8_t mode);
void timer_slave_set_trigger(uint32_t timer, uint8_t trigger);
void timer_slave_set_extclockmode2(uint32_t timer_peripheral,
            enum tim_ecm2_state state);


# 37 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/timer.h" 2
# 43 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/timer.h" 2
# 33 "m1b.c" 2
static void clock_setup(void)
{

 rcc_osc_on(RCC_HSI16);


 flash_prefetch_enable();
 flash_set_ws(4);
 flash_dcache_enable();
 flash_icache_enable();


 rcc_set_main_pll(2, 4, 40, 0, 0, 0);
 rcc_osc_on(RCC_PLL);

 rcc_wait_for_osc_ready(RCC_PLL);

 rcc_periph_clock_enable(RCC_GPIOA);

 rcc_set_sysclk_source(0x3);
 rcc_wait_for_sysclk_status(RCC_PLL);
# 63 "m1b.c"
 rcc_ahb_frequency = 80e6;
 rcc_apb1_frequency = 80e6;
 rcc_apb2_frequency = 80e6;
}

static void delay_loop(int32_t loops)
{
    while(loops > 0)
    {
       asm("nop");
       loops--;
    }
}

int main(void)
{


 clock_setup();

 gpio_mode_setup(((0x48000000U) + 0x0000), 0x1, 0x1, (1 << 5));

 while(1)
 {

  gpio_toggle(((0x48000000U) + 0x0000), (1 << 5));

  delay_loop(400000);
 }


}
