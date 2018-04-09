#ifndef __ERRNO_H__
#define __ERRNO_H__
#ifdef __cplusplus
extern "C"{
#endif

extern int errno = 0;

#define E2BIG 1 //Argument list too long
#define EACCESS 2 //Permission denied
#define EADDRINUSE 3 //Address in use
#define EADDRNOTAVAIL 4 //Address not available
#define EAFNOSUPPORT 5 //Address family not supported
#define EAGAIN 6 //Resource unavailable, try again (may be the same value as EWOULDBLOCK)
#define EALREADY 7 //Connection already in progress
#define EBADF 8 //Bad file descriptor
#define EBUSY 9 //Device or resource busy
#define ECANCELED 10 //Operation canceled
#define ECHILD 11 //No child processes
#define ECONNABORTED 12 //Connection aborted
#define ECONNREFUSED 13 //Connection refused
#define ECONNRESET 14 //Connection reset
#define EDEADLK 15 //Resource deadlock would occur
#define EDESTADDREQ 16 //Destination address required
#define EDOM 17 //Mathematics argement out of domain of function
#define EDQUOT 18 //Reserved
#define EEXIST 19 //File exists
#define EFAULT 20 //Bad address
#define EFBIG 21 //File too large
#define EHOSTUNREACH 22 //Host unreachable
#define EIDRM 23 //Identifier removed
#define EILSEQ 24 //Illegal byte sequence
#define EINPROGRESS 25 //Operation in progress
#define EINTP 26 //Interrupted function
#define EINVAL 27 //Invalid argument
#define EIO 28 //I/O error
#define EISCONN 29 //Socket is connected
#define EISDIR 30 //Is a directory
#define ELOOP 31 //Too many levels of symbolic links
#define EMFILE 32 //File descriptor too large
#define EMLINK 33 //Too many links
#define EMSGSIZE 34 //Message too large
#define EMULTIHOP 35 //Reserved
#define ENAMETOOLONG 36 //Filename too long
#define ENETDOWN 37 //Network down
#define ENETRESET 38 //Connection aborted by network
#define ENETUNREACH 39 //Network unreachable
#define ENFILE 40 //Too many files open in system
#define ENOBUFS 41 //No buffer space available
#define ENODATA 42 //No message available on the STREAM head read queue
#define ENODEV 43 //No such device
#define ENOENT 44 //No such file or directory
#define ENOEXEC 45 //Executable file format error
#define ENOLCK 46 //No locks available
#define ENOLINK 47 //Reserved
#define ENOMEM 48 //Not enough space
#define ENOMSG 49 //No message of the desired type
#define ENOPROTOOPT 50 //Protocol not available
#define ENOSPC 51 //No space left on device
#define ENOSR 52 //No STREAM resources
#define ENOSTR 53 //Not a stream
#define ENOSYS 54 //Functionality not supported
#define ENOTCONN 55 //The socket is not connected
#define ENOTDIR 56 //Not a directory or a symbolic link to a directory
#define ENOTEMPTY 57 //Directory not empty
#define ENOTRECOVERABLE 58 //State not recoverable
#define ENOTSOCK 59 //Not a socket
#define ENOTSUP 60 //Not supported (may be the same value as EOPNOTSUPP)
#define ENOTTY 61 //Inappropriate I/O control operation
#define ENXIO 62 //No such device or address
#define EOPNOTSUPP 63 //Operation not supported on socket (may be the same value as ENOTSUP)
#define EOVERFLOW 64 //Value too large to be stored in data type
#define EOWNERDEAD 65 //Previous owner died
#define EPERM 66 //Operation not permitted
#define EPIPE 67 //Broken pipe
#define EPROTO 68 //Protocol error
#define EPROTONOSUPPORT 69 //Protocol not supported
#define EPROTOTYPE 70 //Protocol wrong type for socket
#define ERANGE 71 //Result too large
#define EROFS 72 //Read only file system
#define ESPIPE 73 //Invalid seek
#define ESRCH 74 //No such process
#define ESTALE 75 //Reserved
#define ETIME 76 //Stream ioctl() timeout
#define ETIMEDOUT 77 //Connection timed out
#define ETXTBSY 78 //Text file busy
#define EWOULDBLOCK 79 //Operation would block (may be the same value as EAGAIN)
#define EXDEV 80 //Cross-device link

#ifdef __cplusplus
}
#endif
#endif