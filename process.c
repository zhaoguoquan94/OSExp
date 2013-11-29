#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>

#define HZ	100

void cpuio_bound(int last, int cpu_time, int io_time);

int main(int argc, char * argv[])
{
	pid_t process1,process2,process3,process4;
	if((process1=fork())==0){
		printf("process1 is running...\n");
		cpuio_bound(30,1,0);
	}
	else if((process2=fork())==0){
		printf("process2 is running...\n");
		cpuio_bound(30,0,1);
	}
	else if((process3=fork())==0){
		printf("process3 is running...\n");
		cpuio_bound(30,1,1);
	}
	else if((process4=fork())==0){
		printf("process4 is running...\n");
		cpuio_bound(20,4,1);
	}
	else{
		printf("father process is running...\n");
		printf("father pid=%d\nprocess1's pid=%d\nprocess2's pid=%d\nprocess3's pid=%d\nprocess4's pid=%d\n",getpid(),process1,process2,process3,process4);
		wait(NULL);		/*书上说wait函数等待某个子进程退出，在这之前一直挂起。因此可以设置多个wait函数让父进程等待所有子进程结束之后再结束*/
		wait(NULL);		/*其实还可以使用waitpid（）函数，但是比较复杂不太会用……试了一下老是出错*/
		wait(NULL);
		wait(NULL);
	}
	
	return 0;
}

/*
 * 此函数按照参数占用CPU和I/O时间
 * last: 函数实际占用CPU和I/O的总时间，不含在就绪队列中的时间，>=0是必须的
 * cpu_time: 一次连续占用CPU的时间，>=0是必须的
 * io_time: 一次I/O消耗的时间，>=0是必须的
 * 如果last > cpu_time + io_time，则往复多次占用CPU和I/O
 * 所有时间的单位为秒
 */
void cpuio_bound(int last, int cpu_time, int io_time)
{
	struct tms start_time, current_time;
	clock_t utime, stime;
	int sleep_time;

	while (last > 0)
	{
		/* CPU Burst */
		times(&start_time);
		/* 其实只有t.tms_utime才是真正的CPU时间。但我们是在模拟一个
		 * 只在用户状态运行的CPU大户，就像“for(;;);”。所以把t.tms_stime
		 * 加上很合理。*/
		do
		{
			times(&current_time);
			utime = current_time.tms_utime - start_time.tms_utime;
			stime = current_time.tms_stime - start_time.tms_stime;
		} while ( ( (utime + stime) / HZ )  < cpu_time );
		last -= cpu_time;

		if (last <= 0 )
			break;

		/* IO Burst */
		/* 用sleep(1)模拟1秒钟的I/O操作 */
		sleep_time=0;
		while (sleep_time < io_time)
		{
			sleep(1);
			sleep_time++;
		}
		last -= sleep_time;
	}
}

