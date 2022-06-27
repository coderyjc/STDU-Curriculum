#include <stdio.h>
#include "thread.h"

// 缓冲池的最大容量
#define BUFFER_MAX 20

// 初始产品的数量
int count = 0;

void producer(){
  while(1){
    if(count >= BUFFER_MAX){
      printf("缓冲池已满, 等待\n");
      sleep(0.7);
    } else {
      count++;
      printf("生产了一个产品...当前产品的数量是 %d\n", count);
      sleep(0.4);
    }
  }
}

void consumer(){

  while(1){
    if(count == 0){
      printf("缓冲池空了,等待\n");
      sleep(0.7);
    } else {
      count--;
      printf("取出了一个产品...当前的产品数量是 %d\n", count);
      sleep(0.4);
    }
  }
}

int main (){
  create(producer);
  create(consumer);
  join();
  return 0;
}