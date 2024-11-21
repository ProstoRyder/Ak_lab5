#include <linux/module.h>
#include <linux/slab.h>
#include <linux/printk.h>
#include "hello1.h"

MODULE_DESCRIPTION("Hello1 module");
MODULE_AUTHOR("Denys Denysiuk");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION("1.0");

static LIST_HEAD(hello_list);

void print_hello(int count)
{
    struct hello_data *data;
    int i;

    for (i = 0; i < count; i++) {
        data = kmalloc(sizeof(*data), GFP_KERNEL);
        if (!data) {
            pr_err("Memory allocation failed for hello_data.\n");
            return;
        }

        data->start = ktime_get();
        pr_info("Hello, world!\n");
        data->end = ktime_get();
        list_add_tail(&data->list, &hello_list);
    }
}

EXPORT_SYMBOL(print_hello);

static void __exit hello1_exit(void)
{
    struct hello_data *data, *tmp;

    list_for_each_entry_safe(data, tmp, &hello_list, list) {
        pr_info("Print duration: %lld ns\n",
                ktime_to_ns(data->end) - ktime_to_ns(data->start));
        list_del(&data->list);
        kfree(data);
    }
}

module_exit(hello1_exit);
