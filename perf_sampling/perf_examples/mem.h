#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/types.h>
#include <errno.h>
#include <limits.h>
#include <linux/sched.h>
#include <openssl/md5.h>

struct pid_totals {
    uint32_t    size;
    uint32_t    rss;
    uint32_t    pss;
    uint32_t    shared_clean;
    uint32_t    shared_dirty;
    uint32_t    private_clean;
    uint32_t    private_dirty;
    uint32_t    referenced;
    uint32_t    swap;

    uint32_t    uss;    // private_clean + private_dirty
    uint32_t    maps;   //# of mappings
    char        **addrs;    //addrs[maps] = "startaddr-endaddr"
};

//one entry for each process
struct process_totals {
    pid_t                   pid;
    char                    name[16];
    char                    path[PATH_MAX];
    uint8_t                 hash[MD5_DIGEST_LENGTH];
    struct pid_totals       totals;
    struct process_totals   *next;
};

struct mem_table {
    struct process_totals   *root;
    struct process_totals   *last;
    uint32_t                size;
};

