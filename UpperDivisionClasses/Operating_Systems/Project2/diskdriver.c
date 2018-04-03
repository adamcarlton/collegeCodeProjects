/* Adam Carlton
 * acarlton
 * CIS 415 PROJECT 2
 * This is my own work. I pseudocoded this out in OH and
 * implemented it on my own. Howard Lin and Edward Szczepanski
 * pointed out a couple bugs I was having but they did not give
 * me code in any way shape or form.
 */

#include "diskdriver.h"
#include "freesectordescriptorstore_full.h"
#include "stdio.h"
#include "pthread.h"
#include "sectordescriptorcreator.h"
#include "BoundedBuffer.h"
/* Contains A sector descriptor, status if it passes or fails
 * a type if it's a read or write
 * checks to see if the thread has run on it and the basis
 * for the while loop in redeem and then a condition and mutex
 */
typedef struct voucher{
    SectorDescriptor *sd;
    int status;
    int type;
    int isDone;
    pthread_cond_t vouchCond;
    pthread_mutex_t vouchMutex;
}Voucher;

/*initial setup of variables and bounded buffers*/
static DiskDevice *globalDd;
BoundedBuffer *writeBB;
BoundedBuffer *readBB;
BoundedBuffer *freeVouchersBB;
FreeSectorDescriptorStore *globalFsds;
static Voucher voucherArr[30];
pthread_t read;
pthread_t write;
/* the function that loops forever for our read thread to run
 * gets a voucher from the read buffer, locks it, sets the
 * status of it from read, sets isDone to 1, signal for redeem
 * then unlock
 */
void* threadRead(){
    while(1){
        Voucher *readVouch = blockingReadBB(readBB);
        pthread_mutex_lock(&readVouch->vouchMutex);
        readVouch->status = read_sector(globalDd, readVouch->sd);
        readVouch->isDone = 1;
        pthread_cond_signal(&readVouch->vouchCond);
        pthread_mutex_unlock(&readVouch->vouchMutex);
    }
}
/* loops forever for our write thread to run
 * gets a voucher from the write buffer, locks it, sets status
 * to that of write_sector, sets isDone to 1, signal for redeem
 * unlock
 */
void* threadWrite(){
    while(1){
        Voucher *writeVouch = blockingReadBB(writeBB);
        pthread_mutex_lock(&writeVouch->vouchMutex);
        writeVouch->status = write_sector(globalDd, writeVouch->sd);
        writeVouch->isDone = 1;
        pthread_cond_signal(&writeVouch->vouchCond);
        pthread_mutex_unlock(&writeVouch->vouchMutex);
    }
}
/* creates a global FSDS, fills it with SD's, sets our BB to
 * size 20, creates our pthreads and gives them the functions
 * to run, loops through an array of vouchers and sets initial
 * variables that need to be set and initializes their mutex/conds
 * puts them in a bounded buffer of free vouchers
 * sets the global disk device to the one that is passed in
 * for use later. Returns fsds to the code that calls us
 */
void init_disk_driver(DiskDevice *dd, void *mem_start, unsigned long mem_length, FreeSectorDescriptorStore **fsds){
    globalFsds = create_fsds();
    create_free_sector_descriptors(globalFsds, mem_start, mem_length);
    writeBB = createBB(20);
    readBB = createBB(20);
    freeVouchersBB = createBB(30);
    pthread_create(&read, NULL, &threadRead, NULL);
    pthread_create(&write, NULL, &threadWrite, NULL);
    int i;
    for(i = 0; i < 30; i++){
        voucherArr[i].status = 0;
        voucherArr[i].isDone = 0;
        pthread_mutex_init(&voucherArr[i].vouchMutex, NULL);
        pthread_cond_init(&voucherArr[i].vouchCond, NULL);
        blockingWriteBB(freeVouchersBB, &voucherArr[i]);
    }
    globalDd = dd;
    *fsds = globalFsds;
}
/* gets a free voucher, sets its SD and type, writes it into
 * the write buffer and then returns the voucher through *v
 */
void blocking_write_sector(SectorDescriptor *sd, Voucher **v){
    Voucher *blockWriteVouch = blockingReadBB(freeVouchersBB);
    blockWriteVouch->sd = sd;
    blockWriteVouch->type = 0;
    blockingWriteBB(writeBB, blockWriteVouch);
    *v = blockWriteVouch;
}
/* gets a free voucher, sets its SD and type, checks to see
 * if the nonblocking call returns 1, if so then set *v and
 * return 1, else returns 0
 */
int nonblocking_write_sector(SectorDescriptor *sd, Voucher **v){
    Voucher *nonBlockWriteVouch = blockingReadBB(freeVouchersBB);
    nonBlockWriteVouch->type = 0;
    nonBlockWriteVouch->sd = sd;
    if(nonblockingWriteBB(writeBB, nonBlockWriteVouch) == 1){
        *v = nonBlockWriteVouch;
        return 1;
    }
    return 0;
}
/* gets a free voucher, sets the SD and type, reads it into the
 * read buffer, and returns the voucher through *v
 */
void blocking_read_sector(SectorDescriptor *sd, Voucher **v){
    Voucher *blockReadVouch = blockingReadBB(freeVouchersBB);
    blockReadVouch->sd = sd;
    blockReadVouch->type = 1;
    blockingWriteBB(readBB, blockReadVouch);
    *v = blockReadVouch;
}
/* gets a free voucher, sets the SD and type, reads it into the
 * checks if the nonblockingWrite into the buffer returns 1,
 * if so then it returns the voucher through *v and returns 1,
 * else it returns 0
 */
int nonblocking_read_sector(SectorDescriptor *sd, Voucher **v){
    Voucher *nonBlockReadVouch = blockingReadBB(freeVouchersBB);
    nonBlockReadVouch->type = 1;
    nonBlockReadVouch->sd = sd;
    if(nonblockingWriteBB(readBB, nonBlockReadVouch) == 1){
        *v = nonBlockReadVouch;
        return 1;
    }
    return 0;
}

/* locks and waits until isDone = 1, then it checks if
 * the status is 1 which means it was a successful read/write
 * then checks the type, if it was a read (type=1) then it
 * returns the sd through *sd, resets the status and isDone,
 * puts it back into the freeVoucher buffer and then unlocks
 * and returns 1. If it was a write then it resets status and
 * isDone as well as put the SD back into the FSDS then unlocks
 * and returns 1. If the status is 0 it puts the SD back into
 * the FSDS, unlocks, then returns 0
 */
int redeem_voucher(Voucher *v, SectorDescriptor **sd){
    pthread_mutex_lock(&v->vouchMutex);
    while(v->isDone != 1){
        pthread_cond_wait(&v->vouchCond, &v->vouchMutex);
    }
    if (v->status == 1 && v->type == 1){
        *sd = v->sd;
        v->status = 0;
        v->isDone = 0;
        blockingWriteBB(freeVouchersBB, v);
        pthread_mutex_unlock(&v->vouchMutex);
        return 1;
    }
    else if(v->status == 1 && v->type == 0){
        v->status = 0;
        v->isDone = 0;
        blockingWriteBB(freeVouchersBB, v);
        blocking_put_sd(globalFsds, v->sd);
        pthread_mutex_unlock(&v->vouchMutex);
        return 1;
    }
    blocking_put_sd(globalFsds, v->sd);
    pthread_mutex_unlock(&v->vouchMutex);
    return 0;
}
