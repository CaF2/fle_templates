$<
global camel_str,low_str,up_str
components = $3.split('-')
low_str = '_'.join(components).lower()
up_str = '_'.join(components).upper()
camel_str = ''

for t in components:
  camel_str += t.capitalize()
>

$1 $2GLOBAL_$<[3]: return up_str >;
static pthread_mutex_t GLOBAL_$<[3]: return up_str >_MUTEX = PTHREAD_MUTEX_INITIALIZER;

int global_$3_set($1 $2value)
{
	pthread_mutex_lock(&GLOBAL_$<[3]: return up_str >_MUTEX);
	GLOBAL_$<[3]: return up_str >=value;
	pthread_mutex_unlock(&GLOBAL_$<[3]: return up_str >_MUTEX);
}

$1 $2global_$3_get(void)
{
	pthread_mutex_lock(&GLOBAL_$<[3]: return up_str >_MUTEX);
	$1 $2value=GLOBAL_$<[3]: return up_str >;
	pthread_mutex_unlock(&GLOBAL_$<[3]: return up_str >_MUTEX);
	
	return value;
}
