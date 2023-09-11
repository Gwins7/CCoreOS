#include <string.h>
#include <os.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdint.h>
#include "test.h"
#define COMMAND_NUM 1
#define True 1
#define False 0
#define SHELL_BEGIN 25
typedef void (*function)(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5);
typedef void * parameter;

static pid_t shell_exec(final_test_t* command);

static struct{
    char *name;
    function func;
    int arg_num;
} command_table [] = {
        {"exec"   , &shell_exec   ,   1},
    };

static pid_t shell_exec(final_test_t* command){   
    // printf("exec process: %s\n", file_name);
    // sys_reflush();
    pid_t pid = sys_exec(command->argv[0], command->argc, command->argv, AUTO_CLEANUP_ON_EXIT);
    if(pid == -1){
        //  printf("> [Error] failed to create the process: %s\n",file_name);
        //  sys_reflush();
    }else{
        //  printf("succeed to create the process: %s, the pid: %d\n",file_name, pid);
        //  sys_reflush();
        return pid;
    }
}


pid_t do_command(char *buffer, int length){
    /*考虑最多只有六个参数*/
    char cmd_two_dim[15][40] = {0};
    int i;
    /*得到以上所有的参数*/
    /*上一个命令的截止地址*/
    int index = 0;
    /*判断是第几个参数*/
    int judge = 0;
    // judge for str
    int judge_str = 0;
    for (i = 0; i < length; i++){
        char ch = buffer[i];
        if (ch == '\"' && !judge_str)
        {
            judge_str = 1;
            continue;
        } else if (ch == '\"' && judge_str)
        {
            judge_str = 0;
            continue;
        }
        if (ch == ' ' && !judge_str){
            cmd_two_dim[judge++][index++] = 0;
            index = 0;
        } 
        else      
            cmd_two_dim[judge][index++] = ch;    
    }
    cmd_two_dim[judge][index] = 0;
    pid_t pid;
    /* only exec */
    uint32_t exec = 0;
    if(!strcmp(cmd_two_dim[0], "exec")) exec = 1;
    else {
        printf("Unknown command\n");
        return 0;
    }
    if (!strcmp(cmd_two_dim[1], "echo"))
    {
        printf("%s\n", &buffer[10]);
        return 0;
    }
        
    if (!strcmp(cmd_two_dim[2], "hwclock"))
        return 0;
    final_test_t final_test = {0};
    final_test.argc = judge;
    for (int i = 0; i < MAX_ARGV_NUM; i++)
    {
        final_test.argv[i] = cmd_two_dim[i + 1];
    }
    
    if(exec){
        pid = shell_exec(&final_test);
    }
    return pid;
}


int main()
{
    // TODO:
    printf("> info: the beginning of the OScomp!\n");
    /**
     * @brief 如果想要在QEMU里面运行就得以一下的格式，并且要将相应的elf编译到内核当中
     */
    int r = 1;
    sys_pre_load("busybox",LOAD);
    sys_pre_load("7za",LOAD);
    sys_pre_load("readelf",LOAD);
    sys_pre_load("libc.so",LOAD);
    for (int i = 0; test[i] != NULL; i++)
    {
        printf("%d: %s\n", r++, test[i]);
        pid_t pid = do_command(test[i], strlen(test[i]));
        sys_sleep(1);
    }  
    sys_pre_load("readelf",FREE);
    sys_pre_load("7za",FREE);
    sys_pre_load("busybox",FREE);
    printf("next:wzq\n");
    sys_sleep(3);
    sys_pre_load("wzq",LOAD);
    pid_t pid = do_command("exec wzq", strlen("exec wzq"));
    if (pid)
        waitpid(pid);
    sys_pre_load("wzq",FREE);
    sys_pre_load("libc.so",FREE);
    printf("test finished!\n");
    for(int i = 0; ; i++){
        sys_sleep(1);
    }
        
    return 0;
}