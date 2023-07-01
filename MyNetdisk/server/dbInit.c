#include "headServer.h"

// 功能：初始化并连接数据库，返回MYSQL句柄 
// 返回值：NULL失败，非NULL成功
MYSQL* dbInit(char* host, char* user, char* passwd, char* database) {
    MYSQL* db = mysql_init(NULL);
    MYSQL* ret = mysql_real_connect(db, host, user, passwd, database, 0, NULL, 0); 
    if(ret == NULL) {
        printf("Error: %s\n", mysql_error(db));
        return NULL;
    }
    return db;
}

