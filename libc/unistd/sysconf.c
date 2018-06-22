#include <unistd.h>
#include <limits.h>

long sysconf(int name)
{
    switch(name)
    {
        case _SC_AIO_LISTIO_MAX:
            return AIO_LISTIO_MAX;
        case _SC_AIO_MAX:
            return AIO_MAX;
        case _SC_AIO_PRIO_DELTA_MAX:
            return AIO_PRIO_DELTA_MAX;
        case _SC_ARG_MAX:
            return ARG_MAX;
        case _SC_ATEXIT_MAX:
            return ATEXIT_MAX;
        case _SC_BC_BASE_MAX:
            return BC_BASE_MAX;
        case _SC_BC_DIM_MAX:
            return BC_DIM_MAX;
        case _SC_BC_SCALE_MAX:
            return BC_SCALE_MAX;
        case _SC_BC_STRING_MAX:
            return BC_STRING_MAX;
        case _SC_CHILD_MAX:
            return CHILD_MAX;
        case _SC_CLK_TCK:
            return 1000; //TODO: Clock Ticks / second
        case _SC_COLL_WEIGHTS_MAX:
            return COLL_WEIGHTS_MAX;
        case _SC_DELAYTIMER_MAX:
            return DELAYTIMER_MAX;
        case _SC_EXPR_NEST_MAX:
            return EXPR_NEST_MAX;
        case _SC_HOST_NAME_MAX:
            return HOST_NAME_MAX;
        case _SC_IOV_MAX:
            return IOV_MAX;
        case _SC_LINE_MAX:
            return LINE_MAX;
        case _SC_LOGIN_NAME_MAX:
            return LOGIN_NAME_MAX;
        case _SC_NGROUPS_MAX:
            return NGROUPS_MAX;
        case _SC_GETGR_R_SIZE_MAX:
            return 0; //TODO
        case _SC_GETPW_R_SIZE_MAX:
            return 0; //TODO
        case _SC_MQ_OPEN_MAX:
            return MQ_OPEN_MAX;
        case _SC_MQ_PRIO_MAX:
            return MQ_PRIO_MAX;
        case _SC_OPEN_MAX:
            return OPEN_MAX;
        case _SC_PAGE_SIZE:
            return PAGE_SIZE;
        case _SC_PAGESIZE:
            return PAGESIZE;
        case _SC_THREAD_DESTRUCTOR_ITERATIONS:
            return PTHREAD_DESTRUCTOR_ITERATIONS;
        case _SC_THREAD_KEYS_MAX:
            return PTHREAD_KEYS_MAX;
        case _SC_THREAD_STACK_MIN:
            return PTHREAD_STACK_MIN;
        case _SC_THREAD_THREADS_MAX:
            return PTHREAD_THREADS_MAX;
        case _SC_RE_DUP_MAX:
            return RE_DUP_MAX;
        case _SC_RTSIG_MAX:
            return RTSIG_MAX;
        case _SC_SEM_NSEMS_MAX:
            return SEM_NSEMS_MAX;
        case _SC_SEM_VALUE_MAX:
            return SEM_VALUE_MAX;
        case _SC_SIGQUEUE_MAX:
            return SIGQUEUE_MAX;
        case _SC_STREAM_MAX:
            return STREAM_MAX;
        case _SC_SYMLOOP_MAX:
            return SYMLOOP_MAX;
        case _SC_TIMER_MAX:
            return TIMER_MAX;
        case _SC_TTY_NAME_MAX:
            return TTY_NAME_MAX;
        case _SC_TZNAME_MAX:
            return TZNAME_MAX;
        case _SC_ADVISORY_INFO:
            return _POSIX_ADVISORY_INFO;
        case _SC_BARRIERS:
            return _POSIX_BARRIERS;
        case _SC_ASYNCHRONOUS_IO:
            return _POSIX_ASYNCHRONOUS_IO;
        case _SC_CLOCK_SELECTION:
            return _POSIX_CLOCK_SELECTION;
        case _SC_CPUTIME:
            return _POSIX_CPUTIME;
        case _SC_FSYNC:
            return _POSIX_FSYNC;
        case _SC_IPV6:
            return _POSIX_IPV6;
        case _SC_JOB_CONTROL:
            return _POSIX_JOB_CONTROL;
        case _SC_MAPPED_FILES:
            return _POSIX_MAPPED_FILES,
        case _SC_MEMLOCK:
            return _POSIX_MEMLOCK;
        case _SC_MEMLOCK_RANGE:
            return _POSIX_MEMLOCK_RANGE;
        case _SC_MEMORY_PROTECTION:
            return _POSIX_MEMORY_PROTECTION;
        case _SC_MESSAGE_PASSING:
            return _POSIX_MESSAGE_PASSING;
        case _SC_MONOTONIC_CLOCK:
            return _POSIX_MONOTONIC_CLOCK;
        case _SC_PRIORITIZED_IO:
            return _POSIX_PRIORITIZED_IO;
        case _SC_PRIORITY_SCHEDULING:
            return _POSIX_PRIORITY_SCHEDULING;
        case _SC_RAW_SOCKETS:
            return _POSIX_RAW_SOCKETS;
        case _SC_READER_WRITER_LOCKS:
            return _POSIX_READER_WRITER_LOCKS;
        case _SC_REALTIME_SIGNALS:
            return _POSIX_REALTIME_SIGNALS;
        case _SC_REGEXP:
            return _POSIX_REGEXP;
        case _SC_SAVED_IDS:
            return _POSIX_SAVED_IDS;
        case _SC_SEMAPHORES:
            return _POSIX_SEMAPHORES;
        case _SC_SHARED_MEMORY_OBJECTS:
            return _POSIX_SHARED_MEMORY_OBJECTS;
        case _SC_SHELL:
            return _POSIX_SHELL;
        case _SC_SPAWN:
            return _POSIX_SPAWN;
        case _SC_SPIN_LOCKS:
            return _POSIX_SPIN_LOCKS;
        case _SC_SPORADIC_SERVER:
            return _POSIX_SPORADIC_SERVER;
        case _SC_SS_REPL_MAX:
            return _POSIX_SS_REPL_MAX;
        case _SC_SYNCHRONIZED_IO:
            return _POSIX_SYNCHRONIZED_IO;
        case _SC_THREAD_ATTR_STACKADDR:
            return _POSIX_THREAD_ATTR_STACKADDR;
        case _SC_THREAD_ATTR_STACKSIZE:
            return _POSIX_THREAD_ATTR_STACKSIZE;
        case _SC_THREAD_CPUTIME:
            return _POSIX_THREAD_CPUTIME;
        case _SC_THREAD_PRIO_INHERIT:
            return _POSIX_THREAD_PRIO_INHERIT;
        case _SC_THREAD_PRIO_PROTECT:
            return _POSIX_THREAD_PRIO_PROTECT;
        case _SC_PRIORITY_SCHEDULING:
            return _POSIX_PRIORITY_SCHEDULING;
        case _SC_THREAD_PROCESS_SHARED:
            return _POSIX_THREAD_PROCESS_SHARED;
        case _SC_THREAD_ROBUST_PRIO_INHERIT:
            return _POSIX_THREAD_ROBUST_PRIO_INHERIT;
        case _SC_THREAD_ROBUST_PRIO_PROTECT:
            return _POSIX_THREAD_ROBUST_PRIO_PROTECT;
        case _SC_THREAD_SAFE_FUNCTIONS:
            return _POSIX_THREAD_SAFE_FUNCTIONS;
        case _SC_THREAD_SPORADIC_SERVER:
            return _POSIX_THREAD_SPORADIC_SERVER;
        case _SC_THREADS:
            return _POSIX_THREADS;
        case _SC_TIMEOUTS:
            return _POSIX_TIMEOUTS;
        case _SC_TIMERS:
            return _POSIX_TIMERS;
        case _SC_TRACE:
            return _POSIX_TRACE;
        case _SC_TRACE_EVENT_FILTER:
            return _POSIX_TRACE_EVENT_FILTERS;
        case _SC_TRACE_EVENT_NAME_MAX:
            _POSIX_TRACE_EVENT_NAME_MAX;
        case _SC_TRACE_INHERIT:
            _POSIX_TRACE_INHERIT;
        case _SC_TRACE_LOG:
            return _POSIX_TRACE_LOG;
        case _SC_TRACE_NAME_MAX:
            return _POSIX_TRACE_NAME_MAX;
        case _SC_TRACE_SYS_MAX:
            return _POSIX_TRACE_SYS_MAX;
        case _SC_TRACE_USER_EVENT_MAX:
            return _POSIX_TRACE_USER_EVENT_MAX;
        case _SC_TYPED_MEMORY_OBJECTS:
            return _POSIX_TYPED_MEMORY_OBJECTS;
        case _SC_VERSION:
            return _POSIX_VERSION;
        case _SC_V7_ILP32_OFF32:
            return _POSIX_V7_ILP32_OFF32;
        case _SC_V7_ILP32_OFFBIG:
            return _POSIX_V7_ILP32_OFFBIG;
        case _SC_V7_LP64_OFF64:
            return _POSIX_V7_LP64_OFF64;
        case _SC_V7_LPBIG_OFFBIG:
            return _POSIX_V7_LPBIG_OFFBIG;
        case _SC_V6_ILP32_OFF32:
            return _POSIX_V7_ILP32_OFF32;
        case _SC_V6_ILP32_OFFBIG:
            return _POSIX_V7_ILP32_OFFBIG;
        case _SC_V6_LP64_OFF64:
            return _POSIX_V7_LP64_OFF64;
        case _SC_V6_LPBIG_OFFBIG:
            return _POSIX_V7_LPBIG_OFFBIG;
        case _SC_2_C_BIND:
            return _POSIX2_C_BIND;
        case _SC_2_C_DEV:
            return _POSIX2_C_DEV;
        case _SC_2_CHAR_TERM:
            return _POSIX2_CHAR_TERM;
        case _SC_2_FORT_DEV:
            return _POSIX2_FORT_DEV;
        case _SC_2_FORT_RUN:
            return _SC_2_FORT_RUN;
        case _SC_2_LOCALEDEF:
            return _POSIX2_LOCALEDEF;
        case _SC_2_PBS:
            return _POSIX2_PBS;
        case _SC_2_PBS_ACCOUNTING:
            return _POSIX2_PBS_ACCOUNTING;
        case _SC_2_PBS_CHECKPOINT:
            return _POSIX2_PBS_CHECKPOINT;
        case _SC_2_PBS_LOCATE:
            return _POSIX2_PBS_LOCATE;
        case _SC_2_PBS_MESSAGE:
            return _POSIX2_PBS_MESSAGE;
        case _SC_2_PBS_TRACK:
            return _POSIX2_PBS_TRACK;
        case _SC_2_SW_DEV:
            return _POSIX2_SW_DEV;
        case _SC_2_UPE:
            return _POSIX2_UPE;
        case _SC_2_VERSION:
            return _POSIX2_VERSION;
        case _SC_XOPEN_CRYPT:
            return _XOPEN_CRYPT;
        case _SC_XOPEN_ENH_I18N:
            return _XOPEN_ENH_I18N;
        case _SC_XOPEN_REALTIME:
            return _XOPEN_REALTIME:
        case _SC_XOPEN_REALTIME_THREADS:
            return _XOPEN_REALTIME_THREADS;
        case _SC_XOPEN_SHM:
            return _XOPEN_SHM;
        case _SC_XOPEN_STREAMS:
            return _XOPEN_STREAMS;
        case _SC_XOPEN_UNIX:
            return _XOPEN_UNIX;
        case _SC_XOPEN_UUCP:
            return _XOPEN_UUCP
        case _SC_XOPEN_VERSION:
            return _XOPEN_VERSION;
        default:
            //TODO: set errno
            return -1;
    }
}