#include <func.h>

// 功能：通过username在文件表中找到用户根目录的fid
// 返回值：0成功 -1失败且fid=-1
int findFidByUsername(MYSQL* db, const char* username, int* pfid) {
    char sql[1024] = {0};
    sprintf(sql, "select * from tbl_file where u_name='%s' and pre_id=-1", username);
    int qret = mysql_query(db, sql);
    if(qret != 0) {
        printf("Error: %s\n", mysql_error(db));
        return -1;
    }
    MYSQL_RES* result = mysql_store_result(db);
    MYSQL_ROW row = mysql_fetch_row(result);
    if(row == NULL) { // 查询结果为空
        *pfid = -1; 
        return -1;
    }
    *pfid = atoi(row[0]);

    return 0;
}

// TestMain
//int main(int argc, char* argv[])
//{
//    ARGS_CHECK(argc, 2);
//    MYSQL* db = mysql_init(NULL);
//    char* host = "localhost";
//    char* user = "root";
//    char* passwd = "1688";
//    char* database = "netdisk";
//    MYSQL* ret = mysql_real_connect(db, host, user, passwd, database, 0, NULL, 0); 
//    if(ret == NULL) {
//        printf("Error: %s\n", mysql_error(db));
//        return -1;
//    }
//
//    int fid;
//    findFidByUsername(db, argv[1], &fid);
//    if(fid == -1) {
//        printf("查找失败！\n");
//    }
//    else {
//        printf("fid = %d\n", fid);
//    }
//    mysql_close(db);
//    return 0;
//}
