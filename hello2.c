#include <linux/module.h>
#include <linux/printk.h>
#include "hello1.h"

MODULE_AUTHOR("Denys Denysiuk");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION("1.0");

static int count = 1;
module_param(count, int, 0444);
MODULE_PARM_DESC(count, "Number of hello messages to print");

static int __init hello2_init(void) {

    if (count <= 0) {
        pr_err("Invalid count parameter: %d. Must be greater than 0.\n", count);
        return -EINVAL;
    } else if (count >= 5 && count <= 10) {
        pr_warn("Count is between 5 and 10. This might take some time.\n");
    } else if (count > 10) {
        pr_err("Count is greater than 10.\n");
        return -EINVAL;
    }
    pr_info("Hello2 module loaded with count = %d\n", count);
    print_hello(count);

    return 0;
}


static void __exit hello2_exit(void) {
    pr_info("Hello2 module unloaded.\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
