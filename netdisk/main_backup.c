#include <func.h>
int tkmake(const char* username, char* retToken);
int tkcheck(const char* username, const char* token);
int getSaltCryptpasswd(const char* passwd, char* salt, char* cryptpasswd);
// 功能：注册(已测试)
// 步骤：
// 1、数据库查询username，结果为!=NULL则拒绝注册；
// 2、为NULL则随机生成一个salt，并crypt_r(salt,passwd,...),并将用户信息存入数据库
// 返回值：-1失败，0成功
int signup(MYSQL* db, const char* username, const char* passwd) {
    char sql[1024] = {0};
    char salt[12] = {0};    
    char cryptpasswd[99] = {0};

    // 获取salt和cryptpasswd
    getSaltCryptpasswd(passwd, salt, cryptpasswd);

    // 尝试插入
    sprintf(sql, "insert into user_table (username, salt, cryptpasswd) values ('%s','%s','%s')", username, salt, cryptpasswd);
    int qret = mysql_query(db, sql);
    if(qret != 0) {
        // printf("Error: %s\n", mysql_error(db));
        return -1;
    }
    return 0;
}

// 功能：登录，并返回一个token
// 步骤：
// 1、数据库查询username，若查询结果为NULL则返回-1
// 2、若!=NULL，获取salt和cryptpasswd，
// 3、将crypt_r(salt, passwd)和 cryptpasswd 执行 strcmp()
// 返回值：-1失败，0成功
int login(MYSQL* db, const char* username, const char* passwd, char* token) {
    char sql[1024] = {0};
    char salt[12] = {0};    
    char cryptpasswd[99] = {0};
    
    // 数据库查询匹配username的记录
    sprintf(sql, "select * from user_table where username='%s'", username);
    int qret = mysql_query(db, sql);
    if(qret != 0) {
        printf("Error: %s\n", mysql_error(db));
        return -1;
    }

    // 从数据库取salt和cryptpasswd
    MYSQL_RES* res = mysql_store_result(db);
    MYSQL_ROW row = mysql_fetch_row(res);
    memcpy(salt, row[2], strlen(row[2]));
    memcpy(cryptpasswd, row[3], strlen(row[3]));

    // 比较cryptpasswd
    struct crypt_data cryptData2;
    char* hash = crypt_r(passwd, salt, &cryptData2);
    int ret_cmp = strncmp(cryptpasswd, hash, strlen(cryptpasswd));
    if(ret_cmp != 0) { // 密码错误
        return -1;
    }

    // 密码正确，生成token
    char retToken[1024] = {0};
    tkmake(username, retToken);
    memcpy(token, retToken, strlen(retToken));

    return 0;

}

// 测试用代码：测试login()
int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 3);
    MYSQL* db = mysql_init(NULL);
    char* host = "localhost";
    char* user = "root";
    char* passwd = "1688";
    char* database = "netdisk";
    MYSQL* ret = mysql_real_connect(db, host, user, passwd, database, 0, NULL, 0); 
    if(ret == NULL) {
        printf("Error: %s\n", mysql_error(db));
        return -1;
    }
    char retToken[1024] = {0};
    int ret_login = login(db, argv[1], argv[2], retToken);
    if(ret_login == 0) {
        printf("login successful!\n");
        printf("retToken=%s\n", retToken);
    }
    else {
        printf("login falid!\n");
    }
    return 0;
}

// 功能：服务器生成token
// 返回值：0成功，-1失败
int tkmake(const char* username, char* retToken) {
    char* jwt;
    size_t jwt_length;

    struct l8w8jwt_encoding_params params;
    l8w8jwt_encoding_params_init(&params);

    params.alg = L8W8JWT_ALG_HS512;

    char name_buf[1024] = {0};
    memcpy(name_buf, username, strlen(username));

    params.sub = name_buf;
    params.iss = "SkipLogin";
    params.aud = "DaskiSnow";

    params.iat = 0;
    params.exp = 0x7fffffff;

    params.secret_key = (unsigned char*)"Content only known by Daskisnow's server! Prevent leaking this content!";
    params.secret_key_length = strlen((char*)params.secret_key);

    params.out = &jwt;
    params.out_length = &jwt_length;

    int r = l8w8jwt_encode(&params);

    memcpy(retToken, jwt, strlen(jwt)); // 注意传入的buf的大小至少为256

    // printf("\n l8w8jwt example HS512 token: %s \n", r == L8W8JWT_SUCCESS ? jwt : " (encoding failure) ");

    l8w8jwt_free(jwt);

    if(r != L8W8JWT_SUCCESS) { // encoding failure
        return -1;
    }
    return 0; // encoding successful
}

// 验证token
// 返回值：0成功 -1失败
int tkcheck(const char* username, const char* token) {
    char* KEY = "Content only known by Daskisnow's server! Prevent leaking this content!";
    const char* JWT = token;
    struct l8w8jwt_decoding_params params;
    l8w8jwt_decoding_params_init(&params);

    params.alg = L8W8JWT_ALG_HS512;

    params.jwt = (char*)JWT;
    params.jwt_length = strlen(JWT);

    params.verification_key = (unsigned char*)KEY;
    params.verification_key_length = strlen(KEY);

    char name_buf[1024] = {0};
    memcpy(name_buf, username, strlen(username));

    params.validate_iss = "SkipLogin"; 
    params.validate_sub = name_buf;
    params.validate_aud = "DaskiSnow";

    params.validate_exp = 0; 
    params.exp_tolerance_seconds = 60;

    params.validate_iat = 0;
    params.iat_tolerance_seconds = 0x7fffffff;

    enum l8w8jwt_validation_result validation_result;

    int decode_result = l8w8jwt_decode(&params, &validation_result, NULL, NULL);

    if (decode_result == L8W8JWT_SUCCESS && validation_result == L8W8JWT_VALID) 
    {
        // token验证成功
        printf("\n Example HS512 token validation successful! \n");
        return 0;
    }
    else
    {
        // token验证失败
        printf("\n Example HS512 token validation failed! \n");
        return -1;
    }

    return 0;

}

int main_signup(int argc, char* argv[]) {
    ARGS_CHECK(argc, 3);
    MYSQL* db = mysql_init(NULL);
    char* host = "localhost";
    char* user = "root";
    char* passwd = "1688";
    char* database = "netdisk";
    MYSQL* ret = mysql_real_connect(db, host, user, passwd, database, 0, NULL, 0); 
    if(ret == NULL) {
        printf("Error: %s\n", mysql_error(db));
        return -1;
    }
    int signup_ret = signup(db, argv[1], argv[2]);
    if(signup_ret == -1) {
        printf("注册失败,重复用户\n");
    }
    else{
        printf("注册成功\n");
    }
    return 0;
}

// 功能：随机生成生成salt，并结合passwd生成cryptpasswd
// 注意点：salt的长度至少为12, 即salt[12];cryptpasswd长度至少为99, 即cryptpasswd[99]
int getSaltCryptpasswd(const char* passwd, char* salt, char* cryptpasswd) {
    // 随机生成类型为$6$的salt
    const char *const seedchars =
        "./0123456789ABCDEFGHIJKLMNOPQRST"
        "UVWXYZabcdefghijklmnopqrstuvwxyz";
    srand(time(NULL) + getpid());

    for (int i = 0; i < 11; i++) {
        salt[i] = seedchars[rand() % 64];
    }
    salt[11] = '\0';
    salt[0] = '$';
    salt[1] = '6';
    salt[2] = '$';

    // 生成cryptpasswd
    struct crypt_data cryptData2;
    char* hash = crypt_r(passwd, salt, &cryptData2);
    memcpy(cryptpasswd, hash, strlen(hash));

    return 0;
}

// 生成salt，以及通过salt和passwd验证cryptpasswd
int main2() {
    char salt[12];
    const char *const seedchars =
        "./0123456789ABCDEFGHIJKLMNOPQRST"
        "UVWXYZabcdefghijklmnopqrstuvwxyz";
    srand(time(NULL) + getpid());

    for (int i = 0; i < 11; i++) {
        salt[i] = seedchars[rand() % 64];
    }
    salt[11] = '\0';
    salt[0] = '$';
    salt[1] = '6';
    salt[2] = '$';
    printf("Generated salt: %s\n", salt);


    char* passwd = "1688";
    struct crypt_data cryptData2;
    char* hash = crypt_r(passwd, salt, &cryptData2);
    printf("hash:%s\n", hash);
    printf("crypt_3_buf:%s\n", cryptData2.crypt_3_buf);
    printf("current_salt:%s\n", cryptData2.current_salt);
    printf("direction:%d\n", cryptData2.direction);
    printf("initialized:%d\n", cryptData2.initialized);
    printf("keysched:%s\n", cryptData2.keysched);
    return 0;
}

// MySQL 连接测试
int main1(int argc, char* argv[])
{
    MYSQL* db = mysql_init(NULL);
    char* host = "localhost";
    char* user = "root";
    char* passwd = "1688";
    char* database = "netdisk";
    MYSQL* ret = mysql_real_connect(db, host, user, passwd, database, 0, NULL, 0); 
    if(ret == NULL) {
        printf("Error: %s\n", mysql_error(db));
        return -1;
    }
    char* sql = "select * from user_table";
    int qret = mysql_query(db, sql);
    if(qret != 0) {
        printf("Error: %s\n", mysql_error(db));
        return -1;
    }
    MYSQL_RES* res = mysql_store_result(db);
    printf("total row: %llu\n", mysql_num_rows(res));
    printf("total column: %u\n", mysql_num_fields(res));
    MYSQL_ROW row;
    while((row = mysql_fetch_row(res)) != NULL) {
        for(unsigned int i = 0; i < mysql_num_fields(res); i++) {
            printf("%s\t", row[i]);
        }
        printf("\n");
    }
    mysql_free_result(res);
    mysql_close(db);

    return 0;
}

