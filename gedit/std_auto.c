#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/**
	Used to steal a pointer to avoid auto cleanup
*/
static void *_steal_ptr(void *data)
{
	void **fdata=data;
	if(fdata && *fdata)
	{
		void *tmp=*fdata;
		*fdata=NULL;
		return tmp;
	}
}

//simplification of the steal function
#define steal_ptr(ptr) _steal_ptr(&(ptr))

/**
	Defines a temporary free function of single pointer structs
*/
static void _cleanup_autofree(void *data)
{
	void **fdata=data;
	if(fdata && *fdata)
	{
		free(*fdata);
		*fdata=NULL;
	}
}

//attirbute used with pointers which needs single frees.
#define autofree __attribute__((cleanup(_cleanup_autofree)))

//used for auto pointers
#define auto_ptr_cleanup_function(structf,funct) \
	static void _cleanup_ptr_## structf(structf **fdata) \
	{ \
		if(fdata && *fdata) \
		{ \
			funct(*fdata); \
			*fdata=NULL; \
		} \
	} \
	typedef structf* cleanup_ptr_ ## structf

//used together with auto pointers
#define auto_ptr(struct) __attribute__((cleanup(_cleanup_ptr_ ## struct))) cleanup_ptr_ ## struct

//used for auto pointers
#define auto_release_cleanup_function(structf,funct) \
	static void _cleanup_release_## structf(structf *fdata) \
	{ \
		if(fdata) \
		{ \
			funct(fdata); \
		} \
	} \
	typedef structf cleanup_release_ ## structf

//used together with auto pointers
#define auto_release(struct) __attribute__((cleanup(_cleanup_release_ ## struct))) cleanup_release_ ## struct

//for FILE types.
auto_ptr_cleanup_function(FILE,fclose);
auto_release_cleanup_function(pthread_mutex_t,pthread_mutex_unlock);
/////////////////////////////////////////////////////

