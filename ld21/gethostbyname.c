#include <func.h>

void printIPInfo(struct hostent *phost) {
   printf("-----------------\n");
   printf("h_name = %s\n", phost->h_name); 
   printf("addType = %d\n", phost->h_addrtype);
   printf("length = %d\n", phost->h_length);
   printf("h_aliases :\n");
   for(int i = 0; phost->h_aliases[i]; i++) {
       printf("    %s\n", phost->h_aliases[i]);
   }
   printf("h_addr_list :\n");
   char buf[1024] = {0};
   for(int i = 0; phost->h_addr_list[i]; i++) {
       memset(buf, 0, sizeof(buf));
       inet_ntop(phost->h_addrtype, phost->h_addr_list[i], buf, sizeof(buf));
       printf("    %s\n", buf);
   }
   return;
}

int main(int argc, char* argv[])
{
    char ali[128] = "www.alibabagroup.com";
    char jd[128] = "www.jd.com";
    char tencent[128] = "www.tencent.com";
    char baidu[128] = "www.baidu.com";
    struct hostent *phost;
    phost = gethostbyname(ali);
    printIPInfo(phost);
    phost = gethostbyname(jd);
    printIPInfo(phost);
    phost = gethostbyname(tencent);
    printIPInfo(phost);
    phost = gethostbyname(baidu);
    printIPInfo(phost);
    return 0;
}

