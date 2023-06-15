#include <func.h>

int main(int argc, char* argv[])
{
    char str_ip[128] = "192.168.1.1";
    char str_ip_get[128] = {0};
    in_addr_t addr = inet_addr(str_ip);
    inet_ntop(AF_INET, &addr, str_ip_get, sizeof(str_ip_get));
    puts(str_ip_get);
    return 0;
}

