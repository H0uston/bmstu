#include "mod_proc.h"

typedef struct PList
{
    struct task_struct* task;
    struct PList* next;
}PList;

bool is_number(const char *str, int n)
{
	int i;	
	for(i = 0; i < n; i++)
		if (str[i] < '0' || str[i] > '9')
			return false;
	return true;
}

int str_to_number(const char *str, int n)
{
	int res = 0;
	int i;
	for(i = 0; i < n; i++)
		res = res * 10 + ( str[i] - '0' );
	return res;
}

void mem_info(int id, char* buf)
{
	char *str = vmalloc(10000 * sizeof(char));
	int offset = 0;
	int cnt;

	bool found = false;
	struct task_struct *task;
	struct task_struct *t = current;
	struct mm_struct *m;
	struct vm_area_struct *v;
	//struct files_struct *open_files;
	//struct fdtable *files_table; 
	struct kstat *ks;
	//struct path files_path;
	unsigned long t_size = 0;
	rcu_read_lock();
	for_each_process(task)
	{
		task_lock(task);
		int iid = task -> pid;
		if(iid == id)
		{	
			t = task;
			found = true;
		}
		task_unlock(task);
				
	}
	rcu_read_unlock();

	if(found && t ->  mm != NULL)
	{
		printk("//////VIRTUAL MEMORY INFORMATION//////\n\n");
		v = t -> mm -> mmap;
		if(v != NULL)
		{
			printk("Process: %s[%d]\n",t -> comm, t -> pid);
			cnt = sprintf(str, "Process: %s[%d]\n",t -> comm, t -> pid);
			str[cnt] = '\0';
			memcpy(buf + offset, str, strlen(str));
			offset += strlen(str);
			int is_full = 0;
			while(v -> vm_next != NULL)
			{
				unsigned long size = v -> vm_end - v -> vm_start;
				if (size > 100000) {
					printk("Full house\n");
					is_full = 1;
					break;
				}
				t_size = t_size + size;
				printk("Start: 0x%lx, End: 0x%lx, Block Size: 0x%lx\n", v -> vm_start, v -> vm_end, size);
				cnt = sprintf(str, "Start: 0x%lx, End: 0x%lx, Block Size: 0x%lx\n", v -> vm_start, v -> vm_end, size);
				str[cnt] = '\0';
				memcpy(buf + offset, str, strlen(str));
				offset += strlen(str);
				v = v -> vm_next;
			}

			if (is_full) {

			} else {
				printk("Total size of virtual space is: 0x%lx\n",t_size);
				cnt = sprintf(str, "Total size of virtual space is: 0x%lx\n",t_size);
				str[cnt] = '\0';
				memcpy(buf + offset, str, strlen(str));
				offset += strlen(str);
			}
		}
	}
	else if (t -> mm == NULL) {
		printk("ID %d not found\n", id);
		cnt = sprintf(str, "ID %d have no memory structure.\n", id);
		str[cnt] = '\0';
		memcpy(buf + offset, str, strlen(str));
		offset += strlen(str);

	}
	else
	{
		printk("ID %d not found\n", id);
		cnt = sprintf(str, "ID %d not found\n", id);
		str[cnt] = '\0';
		memcpy(buf + offset, str, strlen(str));
		offset += strlen(str);
	}
	
	buf[offset] = '\0';
	vfree(str);

}

void files_info(int id, char* buf)
{
	char *str = vmalloc(1000 * sizeof(char));
	int offset = 0;
	int cnt;

	bool found = false;
	struct task_struct *task;
	struct task_struct *t = current;
	//struct mm_struct *m;
	//struct vm_area_struct *v;
	struct files_struct *open_files;
	struct fdtable *files_table; 
	//struct kstat *ks;
	struct path files_path;
	//unsigned long t_size = 0;
	rcu_read_lock();
	for_each_process(task)
	{
		task_lock(task);
		int iid = task -> pid;
		if(iid == id)
		{	
			t = task;
			found = true;
		}
		task_unlock(task);
				
	}
	rcu_read_unlock();
	if(found)
	{

		printk("//////OPEN FILES INFORMATION//////\n\n");
		printk("Process: %s[%d]\n",t -> comm, t -> pid);
		cnt = sprintf(str, "Process: %s[%d]\n",t -> comm, t -> pid);
		str[cnt] = '\0';
		memcpy(buf + offset, str, strlen(str));
		offset += strlen(str);

		int i = 0;
		open_files = t -> files;
		files_table = files_fdtable(open_files);
		char *path;
		char *buf_tmp = (char*)kmalloc(10000 * sizeof(char), GFP_KERNEL);
		while(files_table -> fd[i] != NULL)
		{
			files_path = files_table -> fd[i] -> f_path;
			char* name = files_table-> fd[i] -> f_path.dentry -> d_iname;
			long long size = i_size_read(files_table-> fd[i] -> f_path.dentry -> d_inode);
			path = d_path(&files_path, buf_tmp, 10000 * sizeof(char));
			printk("Name: %s, FD: %d, Size: 0x%llx bytes, Path: %s\n", name, i, size , path);
			cnt = sprintf(str, "Name: %s, FD: %d, Size: 0x%llx bytes, Path: %s\n", name, i, size , path);
			str[cnt] = '\0';
			memcpy(buf + offset, str, strlen(str));
			offset += strlen(str);
			i++;
		}

		if (i == 0) {
			cnt = sprintf(str, "Process hasn't opened files.");
			str[cnt] = '\0';
			memcpy(buf + offset, str, strlen(str));
			offset += strlen(str);
		}

		kfree(buf_tmp);
	}
	else
	{
		printk("ID %d not found\n", id);
		cnt = sprintf(str, "ID %d not found\n", id);
		str[cnt] = '\0';
		memcpy(buf + offset, str, strlen(str));
		offset += strlen(str);
	}
	
	buf[offset] = '\0';
	vfree(str);

}

void process_info(struct task_struct* task, int n, char* buf, int* offset)
{
	char *str = vmalloc(1000 * sizeof(char));
	int cnt;
    
	int count = 0;
    struct PList* head = kmalloc(sizeof(PList), GFP_KERNEL);
    head -> task = NULL;
    head -> next = NULL;
    struct PList* cur = head;
    struct list_head* pos;
    list_for_each(pos, &task->children)
    {
        if (head -> task == NULL)
            head -> task = list_entry(pos, struct task_struct, sibling);
        else
        {
            cur -> next = kmalloc(sizeof(PList),GFP_KERNEL);
            cur -> next -> task = list_entry(pos, struct task_struct, sibling);
            cur -> next -> next = NULL;
            cur = cur -> next;
        }
        count++;
    }
    printk("Process: %s[%d], Parent: %s[%d]\n", task -> comm, task -> pid , task -> parent -> comm, task -> parent -> pid);
	cnt = sprintf(str, "Process: %s[%d], Parent: %s[%d]\n",
				 task -> comm, task -> pid , task -> parent -> comm, task -> parent -> pid);
	str[cnt] = '\0';
	memcpy(buf + (*offset), str, strlen(str));
	(*offset) += strlen(str);
    if(count > 0)
    {
        struct PList* pr;
        n = n - 1;
        int i = 1;
        if(n > 0)
		for(pr = head; pr != NULL;)
        {
        	int m = DEPTH;
            for(; m > n; m--)
            {
            	printk("\t");
				memcpy(buf + (*offset), "\t", strlen("\t"));
				(*offset) += strlen("\t");
            }
            printk("--->Child: %d, ", i);
			cnt = sprintf(str, "--->Child: %d, ", i);
			str[cnt] = '\0';
			memcpy(buf + (*offset), str, strlen(str));
			(*offset) += strlen(str);
            process_info(pr -> task, n, buf, offset);
            i = i+1;
            struct PList* temp = pr;
            pr = pr -> next;
            kfree(temp);
            temp = NULL;
            }
    }
	
	buf[*offset] = '\0';
	vfree(str);	  
	return 0;
}

