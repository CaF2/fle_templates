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
	Header file for $<[1]: return camel_str >
*/
#pragma once

#ifndef $<[1]: return up_str >
#define $<[1]: return up_str >

typedef struct $<[1]: return camel_str >
{
}$<[1]: return camel_str >;

/////////////////////////////

$<[1]: return camel_str > *$1_init($<[1]: return camel_str > *self);
$<[1]: return camel_str > *$1_new(void);
void $1_finalize($<[1]: return camel_str > *self);
void $1_free($<[1]: return camel_str > *self);

#endif
