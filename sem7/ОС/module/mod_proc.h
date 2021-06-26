#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/uaccess.h> 
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/fdtable.h>
// #include <linux/vmalloc.h>

#define PROCFS_TREE_NAME "mod_proc_tree"
#define PROCFS_MEM_NAME "mod_proc_mem"
#define PROCFS_FILES_NAME "mod_proc_files"
#define MAX_WRITE_BUF_SIZE 10
#define DEPTH 1000

bool is_number(const char *str, int n);
int str_to_number(const char *str, int n);
void mem_info(int id, char* buf);
void files_info(int id, char* buf);
void process_info(struct task_struct* task, int n, char* buf, int* offset);
