#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> //包含线程相关头文件
#include <errno.h>
#include <sys/ipc.h>
#include <semaphore.h> //包含信号量相关头文件
int lock_var;
time_t end_time;
sem_t sem1,sem2,sem3; //声明两个信号量
int file[501];
int start=0;
int end=-1;
FILE *f;

void pthreadProducer(void *arg); //声明两个线程函数
void pthreadConsumer1(void *arg);
void pthreadConsumer2(void *arg);
void pthreadConsumer3(void *arg);
void pthreadConsumer4(void *arg);
void pthreadConsumer5(void *arg);
 
int main(int argc, char *argv[])
{
    int i=0;
    for (i = 0; i < 500; ++i)
    {
        file[i]=0;
    }

    pthread_t Producer,Consumer1,Consumer2,Consumer3,Consumer4,Consumer5; 
    sem_init(&sem1,0,10);
    sem_init(&sem2,0,0);
    sem_init(&sem3,0,1);

    pthread_create(&Producer,NULL,(void *)pthreadProducer, NULL); //创建producer线程
    pthread_create(&Consumer1,NULL,(void *)pthreadConsumer1, NULL);
    pthread_create(&Consumer2,NULL,(void *)pthreadConsumer2, NULL);
    pthread_create(&Consumer3,NULL,(void *)pthreadConsumer3, NULL);
    pthread_create(&Consumer4,NULL,(void *)pthreadConsumer4, NULL);
    pthread_create(&Consumer5,NULL,(void *)pthreadConsumer5, NULL);
    
    pthread_join(Producer,NULL); 
    pthread_join(Consumer1,NULL); 
    pthread_join(Consumer2,NULL); 
    pthread_join(Consumer3,NULL); 
    pthread_join(Consumer4,NULL); 
    pthread_join(Consumer5,NULL); 
    exit(0);
}
 
void pthreadProducer(void *arg) //线程1的执行内容
{
    
    int i=0;
while (1)
    while(1){
	if(-1==sem_trywait(&sem3)){
//printf("sem3 in use , while produce\n");
		usleep(1);
		break;
	}
        if(-1==sem_trywait(&sem1)){
//printf("full , while produce\n");
sem_post(&sem3);
		usleep(1);

		break;
	}
        end++;
        file[end]=i;
        f=fopen("file.txt","wb");
        fwrite(file,sizeof(int),sizeof(file),f);
        fclose(f);
        if(i>500){
            break;
        }
        i++;
        sem_post(&sem2); 
	sem_post(&sem3);
    }

    
}
 
void pthreadConsumer1(void *arg)
{
    while(1)
    while(1){
	if(-1==sem_trywait(&sem3)){
//p/rintf("sem3 in use , while consume\n");
		usleep(1);
		break;
	}
        if(-1==sem_trywait(&sem2)){
//printf("null buffer , while consume\n");
sem_post(&sem3);
            usleep(1);

            break;
        }
        printf("1: %d\n",file[start] );
        fflush(stdout);
        start++;
        sem_post(&sem1);
        sem_post(&sem3);
        usleep(1);
    }
}
void pthreadConsumer2(void *arg)
{
   while(1)
    while(1){
	if(-1==sem_trywait(&sem3)){
//printf("sem3 in use , while consume\n");
		usleep(1);
		break;
	}
        if(-1==sem_trywait(&sem2)){
//printf("null buffer , while consume\n");
sem_post(&sem3);
            usleep(1);
            break;
        }
        printf("2: %d\n",file[start] );
        fflush(stdout);
        start++;
        sem_post(&sem1);
        sem_post(&sem3);
        usleep(1);
    }
}
void pthreadConsumer3(void *arg)
{
   while(1)
    while(1){
	if(-1==sem_trywait(&sem3)){
//printf("sem3 in use , while consume\n");
		usleep(1);
		break;
	}
        if(-1==sem_trywait(&sem2)){
//printf("null buffer , while consume\n");
sem_post(&sem3);
            usleep(1);
            break;
        }
        printf("3: %d\n",file[start] );
        fflush(stdout);
        start++;
        sem_post(&sem1);
        sem_post(&sem3);
        usleep(1);
    }
}
void pthreadConsumer4(void *arg)
{
    while(1)
    while(1){
	if(-1==sem_trywait(&sem3)){
//printf("sem3 in use , while consume\n");
		usleep(1);
		break;
	}
        if(-1==sem_trywait(&sem2)){
//printf("null buffer , while consume\n");
sem_post(&sem3);
            usleep(1);
            break;
        }
        printf("4: %d\n",file[start] );
        fflush(stdout);
        start++;
        sem_post(&sem1);
        sem_post(&sem3);
        usleep(1);
    }
}
void pthreadConsumer5(void *arg)
{
    while(1)
    while(1){
	if(-1==sem_trywait(&sem3)){
//printf("sem3 in use , while consume\n");
		usleep(1);
		break;
	}
        if(-1==sem_trywait(&sem2)){
//printf("null buffer , while consume\n");
sem_post(&sem3);
            usleep(1);
            break;
        }
        printf("5: %d\n",file[start] );
        fflush(stdout);
        start++;
        sem_post(&sem1);
        sem_post(&sem3);
        usleep(1);
    }
}
