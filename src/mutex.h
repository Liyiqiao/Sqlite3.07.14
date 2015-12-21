/*
** 2007 August 28
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
**
** This file contains the common header for all mutex implementations.
** The sqliteInt.h header #includes this file so that it is available
** to all source files.  We break it out in an effort to keep the code
** better organized.
**
** NOTE:  source files should *not* #include this header file directly.
** Source files should #include the sqliteInt.h file and let that file
** include this one indirectly.
*/


/*
** Figure out what version of the code to use.  The choices are
**
**   SQLITE_MUTEX_OMIT         No mutex logic.  Not even stubs.  The
**                             mutexes implemention cannot be overridden
**                             at start-time.
**
**   SQLITE_MUTEX_NOOP         For single-threaded applications.  No
**                             mutual exclusion is provided.  But this
**                             implementation can be overridden at
**                             start-time.
**
**   SQLITE_MUTEX_PTHREADS     For multi-threaded applications on Unix.
**
**   SQLITE_MUTEX_W32          For multi-threaded applications on Win32.
*/
/*弄清楚要使用的是哪个版本的code，有以下选择：
** SQLITE_MUTEX_OMIT          不实现互斥锁逻辑，当声明了这个宏，在启动阶段互斥锁实现代码不能被覆盖
**
** SQLITE_MUTEX_NOOP           适用于单线程应用，不提供互斥功能，但是当声明了这个宏，在启动阶段互斥锁实现代码能被覆盖
**
**SQLITE_MUTEX_PTHREADS        适用于Unix系统中的多线程应用
**
** SQLITE_MUTEX_W32            适用于Win32系统的多线程应用

/*
下面是对上述规则的规定
*/

#if !SQLITE_THREADSAFE    /*如果是非线程安全状态，则互斥锁只声明，不实现具体的逻辑*/
# define SQLITE_MUTEX_OMIT
#endif
#if SQLITE_THREADSAFE && !defined(SQLITE_MUTEX_NOOP)       /*如果是线程安全状态，并且没有定义单线程应用的宏**/
#  if SQLITE_OS_UNIX
#    define SQLITE_MUTEX_PTHREADS
#  elif SQLITE_OS_WIN
#    define SQLITE_MUTEX_W32
#  else
#    define SQLITE_MUTEX_NOOP
#  endif
#endif

#ifdef SQLITE_MUTEX_OMIT
/*
** If this is a no-op implementation, implement everything as macros.
**如果以下的方法没有给出具体的实现，则用宏代替它实现它的功能，其实这里实际上就是给函数一个默认的返回值了
*/
#define sqlite3_mutex_alloc(X)    ((sqlite3_mutex*)8)
#define sqlite3_mutex_free(X)
#define sqlite3_mutex_enter(X)    
#define sqlite3_mutex_try(X)      SQLITE_OK
#define sqlite3_mutex_leave(X)    
#define sqlite3_mutex_held(X)     ((void)(X),1)
#define sqlite3_mutex_notheld(X)  ((void)(X),1)
#define sqlite3MutexAlloc(X)      ((sqlite3_mutex*)8)
#define sqlite3MutexInit()        SQLITE_OK
#define sqlite3MutexEnd()
#define MUTEX_LOGIC(X)
#else
#define MUTEX_LOGIC(X)            X
#endif /* defined(SQLITE_MUTEX_OMIT) */
