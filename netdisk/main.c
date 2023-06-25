#include <func.h>
// 功能：注册
// 步骤：
// 1、数据库查询username，结果为!=NULL则拒绝注册；
// 2、为NULL则随机生成一个salt，并crypt_r(salt,passwd,...),并将用户信息存入数据库
// 返回值：-1失败，0成功
int signup(MYSQL* db, const char* username, const char* passwd);

// 功能：登录，并返回一个token
// 步骤：
// 1、数据库查询username，若查询结果为NULL则返回-1
// 2、若!=NULL，获取salt和cryptpasswd，
// 3、将crypt_r(salt, passwd)和 cryptpasswd 执行 strcmp()
// 返回值：-1失败，0成功
int login(MYSQL* db, const char* username, const char* passwd, char* token);

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
    
    /*
     * decode_result describes whether decoding/parsing the token succeeded or failed;
     * the output l8w8jwt_validation_result variable contains actual information about
     * JWT signature verification status and claims validation (e.g. expiration check).
     * 
     * If you need the claims, pass an (ideally stack pre-allocated) array of struct l8w8jwt_claim
     * instead of NULL,NULL into the corresponding l8w8jwt_decode() function parameters.
     * If that array is heap-allocated, remember to free it yourself!
     */

    return 0;

}

int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 2);
    char token[1024] = {0};
    tkmake(argv[1], token);
    printf("token:%s\n", token);

    sleep(3);

    printf("justify ret = %d\n", tkcheck(argv[1], token));
}

// 根据用户信息加密获取token
int main5(void)
{
    char* jwt;
    size_t jwt_length;

    struct l8w8jwt_encoding_params params;
    l8w8jwt_encoding_params_init(&params);

    params.alg = L8W8JWT_ALG_HS512;

    params.sub = "Username";
    params.iss = "SkipLogin";
    params.aud = "DaskiSnow";

    params.iat = 0;
    params.exp = 0x7fffffff; /* Set to expire after 10 minutes (600 seconds). */

    params.secret_key = (unsigned char*)"Content only known by Daskisnow's server! Prevent leaking this content!";
    params.secret_key_length = strlen((char*)params.secret_key);

    params.out = &jwt;
    params.out_length = &jwt_length;

    int r = l8w8jwt_encode(&params);

    printf("\n l8w8jwt example HS512 token: %s \n", r == L8W8JWT_SUCCESS ? jwt : " (encoding failure) ");

    /* Always free the output jwt string! */
    l8w8jwt_free(jwt);

    return 0;
}


static const char KEY[] = "YoUR sUpEr S3krEt 1337 HMAC kEy HeRE";
static const char JWT[] = "eyJhbGciOiJIUzUxMiIsInR5cCI6IkpXVCJ9.eyJpYXQiOjE2ODc2Njc4NDcsImV4cCI6MTY4NzY2ODQ0Nywic3ViIjoiR29yZG9uIEZyZWVtYW4iLCJpc3MiOiJCbGFjayBNZXNhIiwiYXVkIjoiQWRtaW5pc3RyYXRvciJ9.cK1OiT4ZiXHLYxAhB72_mRFGmj2aakf1H1uegcW4W6OjdnY5mkAF3sJ1rTe8m2hzHFzBFTdhkvNUWJ96s-jtoQ";
int main4(void)
{
    struct l8w8jwt_decoding_params params;
    l8w8jwt_decoding_params_init(&params);

    params.alg = L8W8JWT_ALG_HS512;

    params.jwt = (char*)JWT;
    params.jwt_length = strlen(JWT);

    params.verification_key = (unsigned char*)KEY;
    params.verification_key_length = strlen(KEY);

    /* 
     * Not providing params.validate_iss_length makes it use strlen()
     * Only do this when using properly NUL-terminated C-strings! 
     */
    params.validate_iss = "Black Mesa"; 
    params.validate_sub = "Username";
    params.validate_aud = "AAA";

    /* Expiration validation set to false here only because the above example token is already expired! */
    params.validate_exp = 0; 
    params.exp_tolerance_seconds = 60;

    params.validate_iat = 1;
    params.iat_tolerance_seconds = 60;

    enum l8w8jwt_validation_result validation_result;

    int decode_result = l8w8jwt_decode(&params, &validation_result, NULL, NULL);

    if (decode_result == L8W8JWT_SUCCESS && validation_result == L8W8JWT_VALID) 
    {
        printf("\n Example HS512 token validation successful! \n");
    }
    else
    {
        printf("\n Example HS512 token validation failed! \n");
    }
    
    /*
     * decode_result describes whether decoding/parsing the token succeeded or failed;
     * the output l8w8jwt_validation_result variable contains actual information about
     * JWT signature verification status and claims validation (e.g. expiration check).
     * 
     * If you need the claims, pass an (ideally stack pre-allocated) array of struct l8w8jwt_claim
     * instead of NULL,NULL into the corresponding l8w8jwt_decode() function parameters.
     * If that array is heap-allocated, remember to free it yourself!
     */

    return 0;
}


//static const char KEY[] = "Content only known by Daskisnow's server! Prevent leaking this content!"; // 这里的内容不要给别人知道
//static const char JWT[] = 
//"eyJhbGciOiJIUzUxMiIsInR5cCI6IkpXVCJ9.eyJleHAiOjYwLCJzdWIiOiJIYXp1eXVraSIsImlzcyI6IlNraXAgTG9naW4iLCJhdWQiOiJOZXRkaXNrIFNlcnZlciJ9.Z7BkmcoRC-jPTEGVIPWJmib-IWGWHvaf9qyovm3si77Ahx8LSLgTVyAPXePLqgtiETWlQ4rDYGr8XsJaALP01A";
//int main() {
//    struct l8w8jwt_decoding_params params;
//    l8w8jwt_decoding_params_init(&params);
//
//    params.alg = L8W8JWT_ALG_HS512;
//
//    params.jwt = (char*)JWT;
//    params.jwt_length = strlen(JWT);
//
//    params.verification_key = (unsigned char*)KEY;
//    params.verification_key_length = strlen(KEY);
//
//    /* 
//     * Not providing params.validate_iss_length makes it use strlen()
//     * Only do this when using properly NUL-terminated C-strings! 
//     */
//    params.validate_sub = "Hazuyuki";       // 所需登录的用户
//    params.validate_iss = "Skip Login";     // 应接收的服务系统名
//
//    /* Expiration validation set to false here only because the above example token is already expired! */
//    params.validate_exp = 0; 
//    params.exp_tolerance_seconds = 60;
//
//    params.validate_iat = 1;
//    params.iat_tolerance_seconds = 60;
//
//    enum l8w8jwt_validation_result validation_result;
//
//    int decode_result = l8w8jwt_decode(&params, &validation_result, NULL, NULL);
//
//    if (decode_result == L8W8JWT_SUCCESS && validation_result == L8W8JWT_VALID) 
//    {
//        printf("\n Example HS512 token validation successful! \n");
//    }
//    else
//    {
//        printf("\n Example HS512 token validation failed! \n");
//    }
//    
//    /*
//     * decode_result describes whether decoding/parsing the token succeeded or failed;
//     * the output l8w8jwt_validation_result variable contains actual information about
//     * JWT signature verification status and claims validation (e.g. expiration check).
//     * 
//     * If you need the claims, pass an (ideally stack pre-allocated) array of struct l8w8jwt_claim
//     * instead of NULL,NULL into the corresponding l8w8jwt_decode() function parameters.
//     * If that array is heap-allocated, remember to free it yourself!
//     */
//
//    return 0;
//}

// 生成token，根据不同用户修改sub字段
int main3() {
    char* jwt;
    size_t jwt_length;

    struct l8w8jwt_encoding_params params;
    l8w8jwt_encoding_params_init(&params);

    params.alg = L8W8JWT_ALG_HS512;

    params.sub = "Hazuyuki";            // 用户username
    params.iss = "Skip Login";          // 应接收的服务系统名
    params.aud = "Netdisk Server";      // 受众

    params.iat = 0;
    params.exp = 60; /* Set to expire after 10 minutes (600 seconds). */

    params.secret_key = (unsigned char*)"Content only known by Daskisnow's server! Prevent leaking this content!";
    params.secret_key_length = strlen((char*)params.secret_key);

    params.out = &jwt;
    params.out_length = &jwt_length;

    int r = l8w8jwt_encode(&params);

    printf("\n l8w8jwt example HS512 token: %s \n", r == L8W8JWT_SUCCESS ? jwt : " (encoding failure) ");

    /* Always free the output jwt string! */
    l8w8jwt_free(jwt);

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

