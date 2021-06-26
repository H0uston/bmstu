#include "mod_proc.h"

MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "" );

static char *msg_tree;
static char *msg_mem;
static char *msg_files;

static ssize_t read_proc_tree(struct file *filp,char *buf,size_t count,loff_t *offp );
static ssize_t write_proc_tree(struct file *filp,const char *buf,size_t count,loff_t *offp);

static ssize_t read_proc_mem(struct file *filp,char *buf,size_t count,loff_t *offp );
static ssize_t write_proc_mem(struct file *filp,const char *buf,size_t count,loff_t *offp);

static ssize_t read_proc_files(struct file *filp,char *buf,size_t count,loff_t *offp );
static ssize_t write_proc_files(struct file *filp,const char *buf,size_t count,loff_t *offp);

static ssize_t read_proc_tree(struct file *filp,char *buf,size_t count,loff_t *offp ) 
{
	char msg2[] = "Pass 'tree' to process-tree";
	char *buf_msg = vmalloc(1000000 * sizeof(char));
	if (strcmp(msg_tree, "tree") == 0)
	{
		struct task_struct *task;
		task = &init_task;
		int offset = 0;
		process_info(task, DEPTH, buf_msg, &offset);
	}
	else
	{
		memcpy(buf_msg, msg2, strlen(msg2));
		buf_msg[strlen(msg2)] = '\0';
	}
	
	
	int res;
	if( *offp >= strlen( buf_msg ) )
	{    
		*offp = 0;
		return 0;
	}
    if( count > strlen( buf_msg ) - *offp ) 
       count = strlen( buf_msg ) - *offp;
    res = copy_to_user( (void*)buf, buf_msg + *offp, count );
    *offp += count;
    return count;
	
}

static ssize_t write_proc_tree(struct file *filp,const char *buf,size_t count,loff_t *offp)
{	
	ssize_t procfs_buf_size = count;
	if (procfs_buf_size > MAX_WRITE_BUF_SIZE)
	{
		procfs_buf_size = MAX_WRITE_BUF_SIZE;
	}
	copy_from_user(msg_tree, buf, procfs_buf_size);

	msg_tree[procfs_buf_size] = '\0'; 
	printk("Message to /proc/%s from user-space: %s\n", PROCFS_TREE_NAME, msg_tree);

	return count;
}

static ssize_t read_proc_mem(struct file *filp,char *buf,size_t count,loff_t *offp ) 
{
	char msg2[] = "Pass id of process";
	char *buf_msg = vmalloc(1000000 * sizeof(char));
	if (is_number(msg_mem, strlen(msg_mem)))
	{
		int id = str_to_number(msg_mem, strlen(msg_mem));
		mem_info(id, buf_msg);
	}
	else
	{
		memcpy(buf_msg, msg2, strlen(msg2));
		buf_msg[strlen(msg2)] = '\0';
	}
	
	int res;
	if( *offp >= strlen( buf_msg ) )
	{    
		*offp = 0;
		return 0;
	}
    if( count > strlen( buf_msg ) - *offp ) 
       count = strlen( buf_msg ) - *offp;

    res = copy_to_user( (void*)buf, buf_msg + *offp, count );
    *offp += count;
    return count;
}

static ssize_t write_proc_mem(struct file *filp,const char *buf,size_t count,loff_t *offp)
{
	ssize_t procfs_buf_size = count;
	if (procfs_buf_size > MAX_WRITE_BUF_SIZE)
	{
		procfs_buf_size = MAX_WRITE_BUF_SIZE;
	}
	
	copy_from_user(msg_mem, buf, procfs_buf_size);

	msg_mem[procfs_buf_size] = '\0'; 
	printk("Message to /proc/%s from user-space: %s\n", PROCFS_MEM_NAME, msg_mem);

	return count;
}

static ssize_t read_proc_files(struct file *filp,char *buf,size_t count,loff_t *offp ) 
{
	char msg2[] = "Pass id of process";
	char *buf_msg = vmalloc(1000000 * sizeof(char));	
	if (is_number(msg_files, strlen(msg_files)))
	{
		int id = str_to_number(msg_files, strlen(msg_files));
		files_info(id, buf_msg);
	}
	else
	{
		memcpy(buf_msg, msg2, strlen(msg2));
		buf_msg[strlen(msg2)] = '\0';
	}
	
	int res;
	if( *offp >= strlen( buf_msg ) )
	{    
		*offp = 0;
		return 0;
	}
    if( count > strlen( buf_msg ) - *offp ) 
       count = strlen( buf_msg ) - *offp;
    res = copy_to_user( (void*)buf, buf_msg + *offp, count );
    *offp += count;
    return count;
}

static ssize_t write_proc_files(struct file *filp,const char *buf,size_t count,loff_t *offp)
{
	ssize_t procfs_buf_size = count;
	if (procfs_buf_size > MAX_WRITE_BUF_SIZE)
	{
		procfs_buf_size = MAX_WRITE_BUF_SIZE;
	}	
	
	copy_from_user(msg_files, buf, procfs_buf_size);

	msg_files[procfs_buf_size] = '\0'; 
	printk("Message to /proc/%s from user-space: %s\n", PROCFS_MEM_NAME, msg_mem);

	return count;
}

static int  __init proc_init( void )
{

	printk("Start module\n");
	static struct proc_dir_entry *procfs_tree;
	static struct proc_dir_entry *procfs_mem;
	static struct proc_dir_entry *procfs_files;
	
	static struct file_operations proc_file_fops_tree = {
		.owner = THIS_MODULE,
		.read = read_proc_tree,
	 	.write = write_proc_tree
	};

	static struct file_operations proc_file_fops_mem = {
		.owner = THIS_MODULE,
		.read = read_proc_mem,
	 	.write = write_proc_mem
	};

	static struct file_operations proc_file_fops_files = {
		.owner = THIS_MODULE,
		.read = read_proc_files,
	 	.write = write_proc_files
	};


	procfs_tree = proc_create(PROCFS_TREE_NAME, S_IFREG | S_IRUGO | S_IWUGO, NULL, &proc_file_fops_tree);
	procfs_mem = proc_create(PROCFS_MEM_NAME, S_IFREG | S_IRUGO | S_IWUGO, NULL, &proc_file_fops_mem);
	procfs_files = proc_create(PROCFS_FILES_NAME, S_IFREG | S_IRUGO | S_IWUGO, NULL, &proc_file_fops_files);

	msg_tree = kmalloc(MAX_WRITE_BUF_SIZE * sizeof(char), GFP_KERNEL);
	msg_mem = kmalloc(MAX_WRITE_BUF_SIZE * sizeof(char), GFP_KERNEL);
	msg_files = kmalloc(MAX_WRITE_BUF_SIZE * sizeof(char), GFP_KERNEL);	
	if (procfs_tree == NULL || procfs_mem == NULL || procfs_files == NULL) 
	{
		remove_proc_entry(PROCFS_TREE_NAME, NULL);
		remove_proc_entry(PROCFS_MEM_NAME, NULL);
		remove_proc_entry(PROCFS_FILES_NAME, NULL);
		printk("Error: Could not initialize files in /proc\n");
		return -ENOMEM;
	}
	return 0;
}

	
static void __exit proc_exit( void )
{
	printk("Procfs cleanup\n");
	kfree(msg_tree);
	kfree(msg_mem);
	kfree(msg_files);	
	remove_proc_entry(PROCFS_TREE_NAME, NULL);
	remove_proc_entry(PROCFS_MEM_NAME, NULL);
	remove_proc_entry(PROCFS_FILES_NAME, NULL);
	printk("Success cleanup module\n");
}

module_init(proc_init)
module_exit(proc_exit)
