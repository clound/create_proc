#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/utsname.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/rtc.h>
static int __init hello_proc_init(void)
{
	struct timeval tv;	//struct timeval 为设定时间或获取时间时使用的结构体，tv_sec 变量把当前时间换算为秒，tv_usec 值指定或获取 tv_usec 无法表示的 us 单位经过的时间。
	struct rtc_time tm;
	do_gettimeofday(&tv);//此函数获取从1970-1-1 0:0:0到现在的时间值，存在timeval的结构体里边。
	rtc_time_to_tm(tv.tv_sec+8*3600,&tm);//此内核函数将系统实时时钟时间转换为格林尼治标准时间（GMT）。如果要得到北京时间需。需要将此时间处理（年份加上1900，月份加上1，小时加上8）。具体参看内核中rtc.h中rtc_time_to_tm代码实现。
	printk("BeiJing time :%d-%d-%d %d:%d:%d\n",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec);//北京时间
	return 0;
}
static int __exit hello_proc_exit(void)
{
	printk("GoodBye kernel\n");
}
MODULE_LICENSE("GPL");
module_init(hello_proc_init);
module_exit(hello_proc_exit);
