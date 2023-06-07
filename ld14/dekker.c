#include <func.h>
#define NUM 10000000

int main(int argc, char* argv[])
{
    //  bool enter[2] = {false,false};
    //  int turn = 0;
    int count = 0;

    // 建立共享内存
    int shmid = shmget(250, 4096, IPC_CREAT | 0600);
    ERROR_CHECK(shmid, -1, "shmget");

    // 建立映射
    int* shm_arr = (int*)shmat(shmid, NULL, 0);
    ERROR_CHECK(shm_arr, NULL, "shmat");

    shm_arr[0] = 0; // 存储结果
    shm_arr[1] = 0; // enter
    shm_arr[2] = 0;
    shm_arr[3] = 0; // turn
    if(fork()) {
        while(1){
            shm_arr[1] = 1;
            while(shm_arr[2]){
                if(shm_arr[3] != 0) {
                    shm_arr[1] = 0;
                    while(shm_arr[3] != 0); //BUSY WAIT
                    shm_arr[1] = 1;
                }
            }
            if(count!=NUM){
                shm_arr[0]++;
                count++;
            }
            else{
                shm_arr[3] = 1;
                shm_arr[1] = 0;
                break;
            }
            shm_arr[3] = 1;
            shm_arr[1] = 0;
        }
        wait(NULL);
        printf("Final result = %d\n", shm_arr[0]);
        shmdt(shm_arr);
    }
    else{
        while(1){    
            shm_arr[2] = 1;
            while(shm_arr[1]){
                if(shm_arr[3] != 1) {
                    shm_arr[2] = 0;
                    while(shm_arr[3] != 1); //BUSY WAIT
                    shm_arr[2] = 1;
                }
            }
            if(count!=NUM){
                shm_arr[0]++;
                count++;
            }
            else{
                shm_arr[3] = 0;
                shm_arr[2] = 0;
                break;
            }
            shm_arr[3] = 0;
            shm_arr[2] = 0;
        }
        shmdt(shm_arr);
    }
    return 0;
}

