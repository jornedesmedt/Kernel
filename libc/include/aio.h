/**
    POSIX DESCRIPTION

    Name: aio.h -  asynchronous input and output.
    Description:
    
    The <aio.h> header shal define the aiocb structure, which shall inclide the following members

    int             aio_fildes     File descriptor. 
    off_t           aio_offset     File offset. 
    volatile void  *aio_buf        Location of buffer. 
    size_t          aio_nbytes     Length of transfer. 
    int             aio_reqprio    Request priority offset. 
    struct sigevent aio_sigevent   Signal number and value. 
    int             aio_lio_opcode Operation to be performed. 

    The <aio.h> header shall define the off_t, pthread_attr_t, size_t, and ssize_t types as described in <sys/types.h>.

    The <aio.h> header shall define the struct timespec structure as described in <time.h>.

    The <aio.h> header shall define the sigevent structure and sigval union as described in <signal.h>.

    The <aio.h> header shall define the following symbolic constants:

    AIO_ALLDONE
        A return value indicating that none of the requested operations could be canceled since they are already complete.
    AIO_CANCELED
        A return value indicating that all requested operations have been canceled.
    AIO_NOTCANCELED
        A return value indicating that some of the requested operations could not be canceled since they are in progress.
    LIO_NOP
        A lio_listio() element operation option indicating that no transfer is requested.
    LIO_NOWAIT
        A lio_listio() synchronization operation indicating that the calling thread is to continue execution while the lio_listio() operation is being performed, and no notification is given when the operation is complete.
    LIO_READ
        A lio_listio() element operation option requesting a read.
    LIO_WAIT
        A lio_listio() synchronization operation indicating that the calling thread is to suspend until the lio_listio() operation is complete.
    LIO_WRITE
        A lio_listio() element operation option requesting a write.

    The following shall be declared as functions and may also be defined as macros. Function prototypes shall be provided.

    int      aio_cancel(int, struct aiocb *);
    int      aio_error(const struct aiocb *);
    [FSC|SIO][Option Start]
    int      aio_fsync(int, struct aiocb *);
    [Option End]
    int      aio_read(struct aiocb *);
    ssize_t  aio_return(struct aiocb *);
    int      aio_suspend(const struct aiocb *const [], int,
                const struct timespec *);
    int      aio_write(struct aiocb *);
    int      lio_listio(int, struct aiocb *restrict const [restrict], int,
                struct sigevent *restrict);

    Inclusion of the <aio.h> header may make visible symbols defined in the headers <fcntl.h>, <signal.h>, and <time.h>.

*/

#ifndef __POSIX_AIO_H__
#define __POSIX_AIO_H__

#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>

int             aio_fildes;     //File descriptor. 
off_t           aio_offset;     //File offset. 
volatile void   *aio_buf;       //Location of buffer. 
size_t          aio_nbytes;     //Length of transfer. 
int             aio_reqprio;    //Request priority offset. 
struct sigevent aio_sigevent;   //Signal number and value. 
int             aio_lio_opcode; //Operation to be performed.

/*  Return values for aio_cancel */
#define AIO_CANCELED        0x1     //A return value indicating that all requested operations have been canceled.
#define AIO_NOTCANCELED     0x2     //A return value indicating that some of the requested operations could not be canceled since they are in progress.
#define AIO_ALLDONE         0x3     //A return value indicating that none of the requested operations could be canceled since they are already complete.

/* LIO opcodes */
#define LIO_NOP             0x0     //A lio_listio() element operation option indicating that no transfer is requested.
#define LIO_WRITE           0x1     //A lio_listio() element operation option requesting a write.
#define LIO_READ            0x2     //A lio_listio() element operation option requesting a read.

/*  LIO modes */
#define LIO_NOWAIT          0x0      //A lio_listio() synchronization operation indicating that the calling thread is to continue execution while the lio_listio() operation is being performed, and no notification is given when the operation is complete.
#define LIO_WAIT            0x1      //A lio_listio() synchronization operation indicating that the calling thread is to suspend until the lio_listio() operation is complete.


int      aio_cancel(int, struct aiocb *);
int      aio_error(const struct aiocb *);
int      aio_fsync(int, struct aiocb *);
int      aio_read(struct aiocb *);
ssize_t  aio_return(struct aiocb *);
int      aio_suspend(const struct aiocb * const list[], int, const struct timespec *);
int      aio_write(struct aiocb *);
int      lio_listio(int, struct aiocb *restrict const [restrict], int, struct sigevent *restrict);

#endif