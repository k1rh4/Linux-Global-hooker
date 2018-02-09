#define _GNU_SOURCE
#include<stdio.h>
#include<dlfcn.h>
#include<stdlib.h>
#include<string.h>
extern char * __progname;
static int (*hook_open)(const char *path , int flags, mode_t mode)= NULL;
static int (*hook_open64)(const char *path , int flags, mode_t mode)= NULL;
static FILE *(*hook_fopen)(const char *path, const char *mode) = NULL;
static int (*hook_unlinkat)(int dirfd, const char *path, int flags) = NULL;
static int (*hook_unlink)(const char *path) = NULL;
static int (*hook_creat)(const char * pathname, mode_t mode) = NULL;
static int (*hook_creat64)(const char * pathname, mode_t mode) = NULL;
static int (*hook_openat)(int dirfd, const char * pathname, int flags, mode_t mode);
static int (*hook_openat64)(int dirfd, const char * pathname, int flags, mode_t mode);


#define MAX 0x100
#define DEFAULT_FILTER 	"/tmp/"
#define DEFAULT_CONFIG 	"/tmp/hook.ini"
#define DEFAULT_LOG	"/tmp/file_log.txt"

char FILTER[MAX] = DEFAULT_FILTER;
FILE * cf_file = NULL;

void getNamePID(int pid, char *pName)
{
	int fp = 0;
	char buff[MAX]={0,};
	snprintf(buff,MAX,"/proc/%d/cmdline",pid);
	fp = hook_open(buff,0,0);
	read(fp,(char *)pName,MAX);
	close(fp);
}
void CheckConfig()
{
	if ( cf_file == NULL )
	{
		cf_file = hook_fopen(DEFAULT_CONFIG,"r");
		if(cf_file) fscanf(cf_file,"%s",FILTER);
		if(strlen(FILTER)<1) strncpy(FILTER,DEFAULT_FILTER,sizeof(FILTER));
	}

}
void PrintLog(char * real_path)
{
	char pName[MAX] = {0,};
	FILE *fp = NULL;
	if( strstr(real_path,FILTER) > 0 )
	{
		if( fp = hook_fopen(DEFAULT_LOG, "a+") )
		{
			getNamePID(getppid(),pName);
			fprintf(fp,"[+] Caller->ppName:[%s]:[%d],pName:[%s]:[%d]->%s\n" \
				,pName,getppid() ,__progname, getpid(),real_path );
			fclose(fp);
		}
		
	}

}
int unlinkat(int dirfd, const char *path, int flags)
{
	if (hook_unlinkat == NULL)hook_unlinkat = dlsym(RTLD_NEXT, "unlinkat");
	char *real_path = realpath(path,0);
	if ( real_path )
	{
		CheckConfig();
		PrintLog(real_path);
	}
	return hook_unlinkat(dirfd, path, flags);
}

int unlink(const char *path)
{
	if (hook_unlink	== NULL) hook_unlink = dlsym(RTLD_NEXT, "unlink");
	char *real_path = realpath(path,0);
	if ( real_path )
	{
		CheckConfig();
		PrintLog( real_path );

	}
	return hook_unlink(path);
}

int creat(const char * pathname, mode_t mode)
{
	if(hook_creat	==NULL) hook_creat = dlsym(RTLD_NEXT,"creat");
	int hook_ret 		= hook_creat(pathname, mode);
	char * real_path	= realpath(pathname,0);

	if( real_path )
	{
		CheckConfig();
		PrintLog( real_path );
	}
	return hook_ret;


}
int creat64(const char * pathname, mode_t mode)
{
	if(hook_creat64	==NULL) hook_creat64 = dlsym(RTLD_NEXT,"creat64");
	int hook_ret 		= hook_creat64(pathname, mode);
	char * real_path	= realpath(pathname,0);

	if( real_path )
	{
		CheckConfig();
		PrintLog( real_path );
	}
	return hook_ret;
}
int openat(int dirfd, const char * pathname, int flags, mode_t mode )
{
	if(hook_openat == NULL) hook_openat = dlsym(RTLD_NEXT, "openat");
	int hook_ret 	 = hook_openat(dirfd, pathname, flags, mode );
	char * real_path = realpath(pathname,0);
	if( real_path )
	{
		CheckConfig();
		PrintLog( real_path );

	}
	return hook_ret;

}
int openat64(int dirfd, const char * pathname, int flags, mode_t mode )
{
	if(hook_openat64 == NULL) hook_openat64 = dlsym(RTLD_NEXT, "openat64");
	int hook_ret 	 = hook_openat64(dirfd, pathname, flags, mode );
	char * real_path = realpath(pathname,0);
	if( real_path )
	{
		CheckConfig();
		PrintLog( real_path );

	}
	return hook_ret;

}

int open(const char * path, int flags, mode_t mode)
{
	if (hook_open 	== NULL) hook_open = dlsym(RTLD_NEXT, "open");
	int hook_ret 	= hook_open(path,flags,mode);
	char *real_path = realpath(path,0);
	if ( real_path )
	{
		CheckConfig();
		PrintLog( real_path );
	}
	return hook_ret;
}
int open64(const char * path, int flags, mode_t mode)
{
	if (hook_open64 == NULL) hook_open64 = dlsym(RTLD_NEXT, "open64");
	int hook_ret 	= hook_open64(path,flags,mode);
	char *real_path = realpath(path,0);
	if ( real_path )
	{
		CheckConfig();
		PrintLog( real_path );
	}
	return hook_ret; 
}

FILE * fopen(const char *path, const char *mode)
{
	if (hook_fopen 	== NULL) hook_fopen = dlsym(RTLD_NEXT, "fopen");
	FILE *hook_ret 	= hook_fopen(path,mode);
	char *real_path = realpath(path,0);
	if ( real_path )
	{
		CheckConfig();
		PrintLog( real_path );
	}
	return hook_ret; 
}

void __attribute__ ((constructor)) before_load(void)
{
	if (hook_open 	== NULL) hook_open 	= dlsym(RTLD_NEXT, "open");
	if (hook_open64 == NULL) hook_open64 	= dlsym(RTLD_NEXT, "open64");
	if (hook_fopen 	== NULL) hook_fopen 	= dlsym(RTLD_NEXT, "fopen");
	if (hook_unlink	== NULL) hook_unlink 	= dlsym(RTLD_NEXT, "unlink");
	if (hook_unlinkat == NULL)hook_unlinkat = dlsym(RTLD_NEXT, "unlinkat");

}

