#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include<linux/timer.h>
#include<linux/timex.h>
#include<linux/rtc.h>
MODULE_LICENSE("GPL");
	struct timex txc;
	struct rtc_time tm;
static int __init hello_init(void)
{
	printk(KERN_ALERT "hello entered.\n");

	do_gettimeofday(&(txc.time));
	rtc_time_to_tm(txc.time.tv_sec,&tm);
	tm.tm_hour=tm.tm_hour+8;
	if(tm.tm_hour>=24){
		tm.tm_hour=tm.tm_hour-24;
		if((tm.tm_mon+1)==1||(tm.tm_mon+1)==3||(tm.tm_mon+1)==5||(tm.tm_mon+1)==7||(tm.tm_mon+1)==8||(tm.tm_mon+1)==10||(tm.tm_mon+1)==12)
		{
				tm.tm_mday=tm.tm_mday+1;
				if((tm.tm_mday)>31)
					tm.tm_mon=tm.tm_mon+2;
		}
		if((tm.tm_mon+1)==4||(tm.tm_mon+1)==6||(tm.tm_mon+1)==9||(tm.tm_mon+1)==11)
		{
			tm.tm_mday=tm.tm_mday+1;
				if((tm.tm_mday)>30)
					tm.tm_mon=tm.tm_mon+2;
		}
		if((tm.tm_mon+1)==2)
		{
			tm.tm_mday=tm.tm_mday+1;
			if((tm.tm_year+1900)%100==0||(tm.tm_year+1900)%400==0)		//如果是闰年
				if((tm.tm_mday)>29)
					tm.tm_mon=tm.tm_mon+2;
			else
				if((tm.tm_mday)>28)
					tm.tm_mon=tm.tm_mon+2;
		}	
		if((tm.tm_mon+1)>12){
			tm.tm_mon=tm.tm_mon-12;
			tm.tm_year=tm.tm_year+1;
		}
		
			
	}
	else
	printk("utc time:%d-%d-%d %d:%d:%d \n",tm.tm_year+1900,tm.tm_mon+1, tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec);
	
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_ALERT "hello exiting.\n");
}

module_init(hello_init);
module_exit(hello_exit);
