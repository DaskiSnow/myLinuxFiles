#include "func.h"

int main(void) {
    // 传入NULL和0，让系统调用malloc，但要记得释放空间
    char* cwd = getcwd(NULL, 0);
    ERROR_CHECK(cwd, NULL, "getcwd");

    puts(cwd);

    free(cwd);

    return 0;
     
}
