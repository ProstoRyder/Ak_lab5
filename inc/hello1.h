#ifndef HELLO1_H
#define HELLO1_H

#include <linux/ktime.h>
#include <linux/list.h>

struct hello_data {
    ktime_t start;
    ktime_t end;
    struct list_head list;
};

void print_hello(int count);

#endif
