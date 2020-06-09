#include <linux/module.h>
#include <linux/mm.h>
#include <linux/init.h>
#include <linux/sched.h>

static int pid;

module_param(pid,int,0644);

static void printit(struct task_struct *tsk)
{
	struct mm_struct *mm;
	struct vm_area_struct *vma;
	int j = 0;
	unsigned long start,end,length,vflags;

	mm = tsk->mm;
	pr_info("mm_struct addr = 0x%p",mm);
	vma = mm->mmap;

	down_read(&mm->mmap_sem);
	pr_info("vmas:\tvma\tstart\tend\tlength\tvm_flags\n");

	while(vma){
		j++;
		start = vma->vm_start;
		end = vma->vm_end;
		length = end - start;
		vflags = vma->vm_flags;
		pr_info("%6d: %16p %12lx %12lx %8ld %8ld\n",j,vma,start,end,length,vflags);
		vma = vma -> vm_next;
	}
	up_read(&mm->mmap_sem);
}

static int __init vma_test_init(void)
{
	struct task_struct *tsk;
	if (pid ==0){
		tsk = current;
		pid = current->pid;
		pr_info("using current process\n");
	}
	else {
		tsk = pid_task(find_vpid(pid),PIDTYPE_PID);
	}
	if(!tsk){
		return -1;
	}
	pr_info("Examining vma's for pid=%d, command=%s\n",pid,tsk->comm);
	printit(tsk);
	return 0;
}

static void __exit vma_test_exit(void)
{
	pr_info("Module exit.\n");
}

module_init(vma_test_init);
module_exit(vma_test_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kingtous");
MODULE_DESCRIPTION("vma test");