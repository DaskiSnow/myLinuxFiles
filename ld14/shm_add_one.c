#include <func.h>
#define NUM 10000000
// fork创建一个子进程，两个进程访问同一段共享内存，共享内存里保存一个整形数，父子进程用for循环的方式。
// 每次对这个整形数字加1，父子进程各循环1000万次。加完后打印一下共享内存里的数字，看看是多少？
int main(int argc, char* argv[])
{
    // 建立共享内存（第一次创建时初始化为0）
    int shmid = shmget(250, 4096, IPC_CREAT | 0600);
    ERROR_CHECK(shmid, -1, "shmget");
    printf("shmid = %d\n",shmid);

    // 建立映射
    int* shm_arr = (int*)shmat(shmid, NULL, 0);
    ERROR_CHECK(shm_arr, NULL, "shmat");

    shm_arr[0] = 0;
    // 创建父子进程
    if(fork()) {
        for(int i = 0; i < NUM; i++) {
            shm_arr[0]++;
        }
        wait(NULL);
        printf("Final result = %d\n", shm_arr[0]);
        shmdt(shm_arr);
        
        return 0;
    }
    else{
        for(int i = 0; i < NUM; i++) {
            shm_arr[0]++;
        }
        shmdt(shm_arr);
        
        return 0;
    }
}

