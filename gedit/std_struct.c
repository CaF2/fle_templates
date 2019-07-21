$<
global camel_str,low_str,up_str
components = $1.split('-')
low_str = '_'.join(components).lower()
up_str = '_'.join(components).upper()
camel_str = ''

for t in components:
  camel_str += t.capitalize()
>
/**
	Code for handling the $<[1]: return camel_str > struct.
*/
#include "$1.h"

/**
	Constructor for $<[1]: return camel_str >
	
	@param self
		reset or initialize the $<[1]: return camel_str > struct.
	@returns
		initialized $<[1]: return camel_str > struct.
*/
$<[1]: return camel_str > *$1_init($<[1]: return camel_str > *self)
{
	memset(self,'\0',sizeof($<[1]: return camel_str >));

	return self;
}

/**
	Constructor and allocator for the $<[1]: return camel_str > struct
	
	@returns
		newly allocated $<[1]: return camel_str > struct.
*/
$<[1]: return camel_str > *$1_new(void)
{
	$<[1]: return camel_str > *self=malloc(sizeof($<[1]: return camel_str >));
	if(!self)
	{
		return NULL;
	}
	
	$<[1]: return camel_str > *result=$1_init(self);
	
	if(!result)
	{
		free(self);
		return NULL;
	}
	
	return result;
}

/**
	De-initialize the struct but does not free the input.
	
	@param self
		Struct to handle
*/
void $1_finalize($<[1]: return camel_str > *self)
{
	
}

/**
	Destructor of the struct, will call $1_finalize and free. 
	
	@param self
		Struct to handle. Note that self will be freed inside this function
*/
void $1_free($<[1]: return camel_str > *self)
{
	$1_finalize(self);

	free(self);
}

/////////////////////////////
