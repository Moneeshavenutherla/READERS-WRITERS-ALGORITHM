#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

int rc=0,val,wc=0;
pthread_mutex_t mutex1,mread;
pthread_t tr1,tr2,tr3,tr4,tr5,tw1,tw2,tw3,tw4,tw5;
pthread_attr_t tr1attr,tr2attr,tr3attr,tr4attr,tr5attr,tw1attr,tw2attr,tw3attr,tw4attr,tw5attr;

void *reader();
void *writer();

int main()
{
 pthread_mutex_init(&mutex1,NULL);
 pthread_mutex_init(&mread,NULL);

 pthread_attr_init(&tr1attr);
 pthread_attr_init(&tr2attr);
 pthread_attr_init(&tr3attr);
 pthread_attr_init(&tr4attr);
 pthread_attr_init(&tr5attr);
 pthread_attr_init(&tw1attr);
 pthread_attr_init(&tw2attr);
 pthread_attr_init(&tw3attr);
 pthread_attr_init(&tw4attr);
 pthread_attr_init(&tw5attr);
 
 printf("\n Writer 1 created");
 pthread_create(&tw1,&tw1attr,writer,NULL);
 
 printf("\n Reader 1 created");
 pthread_create(&tr1,&tr1attr,reader,NULL);
 
 printf("\n Writer 2 created");
 pthread_create(&tw2,&tw2attr,writer,NULL);
 
 printf("\n Reader 2 created");
 pthread_create(&tr2,&tr2attr,reader,NULL);
 
 printf("\n Writer 3 created");
 pthread_create(&tw3,&tw3attr,writer,NULL);
 
 printf("\n Reader 3 created");
 pthread_create(&tr3,&tr3attr,reader,NULL);
 
 printf("\n Writer 4 created");
 pthread_create(&tw4,&tw4attr,writer,NULL);
 
 printf("\n Reader 4 created");
 pthread_create(&tr4,&tr4attr,reader,NULL);
 
 printf("\n Writer 5 created");
 pthread_create(&tw5,&tw5attr,writer,NULL);
 
 printf("\n Reader 5 created");
 pthread_create(&tr5,&tr5attr,reader,NULL);
 

 pthread_join(tw1,NULL);
 pthread_join(tr1,NULL);
 pthread_join(tw2,NULL);
 pthread_join(tr2,NULL); 
 pthread_join(tw3,NULL);
 pthread_join(tr3,NULL);
 pthread_join(tw4,NULL);
 pthread_join(tr4,NULL);
 pthread_join(tw5,NULL);
 pthread_join(tr5,NULL);
 

 return 0;
}

void *writer()
{
 pthread_mutex_lock(&mutex1);
 wc++;
 sleep(1);
 printf("\n\n\nwriter %d initiated",wc);
 printf("\n\nreaders present : %d",rc);
 printf("\n\n Enter data:  ");
 
 scanf("%d",&val);
 
 pthread_mutex_unlock(&mutex1);
 
// printf("\n writer %d executed",wc);
 sleep(1);
 printf("\n\n value written by writer is : %d",val);
 pthread_exit(0);
 
}
  
void *reader()
{
 pthread_mutex_lock(&mread);
 rc++;
 
 if(rc==1)
  pthread_mutex_lock(&mutex1);
 pthread_mutex_unlock(&mread);

 printf("\n Value read by reader %d: %d",rc,val);

 pthread_mutex_lock(&mread);
 rc--;
 if(rc==0)
  pthread_mutex_unlock(&mutex1);
 pthread_mutex_unlock(&mread);
 printf("\n Reader %d executing",rc+1);
 //sleep(1);
 pthread_exit(0);
 
}
