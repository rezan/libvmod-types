#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "cache/cache.h"
#include "vcl.h"

#include "vcc_types_if.h"


struct vmod_types_integer {
	unsigned			magic;
#define VMOD_TYPES_INTEGER_MAGIC	0x6714BA6E

	pthread_rwlock_t		rwlock;

	long				value;
};

VCL_VOID
vmod_integer__init(VRT_CTX, struct vmod_types_integer **object_p,
	const char *vcl_name, VCL_INT value)
{
	struct vmod_types_integer *object;

	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);
	AN(object_p);
	AZ(*object_p);
	AN(vcl_name);

	ALLOC_OBJ(object, VMOD_TYPES_INTEGER_MAGIC);
	AN(object);

	AZ(pthread_rwlock_init(&object->rwlock, NULL));

	object->value = value;

	*object_p = object;
}

VCL_VOID
vmod_integer__fini(struct vmod_types_integer **object_p)
{
	AN(object_p);
	CHECK_OBJ_NOTNULL(*object_p, VMOD_TYPES_INTEGER_MAGIC);

	AZ(pthread_rwlock_destroy(&(*object_p)->rwlock));

	FREE_OBJ(*object_p);
}

VCL_INT
vmod_integer_value(VRT_CTX, struct vmod_types_integer *object)
{
	long ret;

	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);
	CHECK_OBJ_NOTNULL(object, VMOD_TYPES_INTEGER_MAGIC);

	AZ(pthread_rwlock_rdlock(&object->rwlock));

	ret = object->value;

	AZ(pthread_rwlock_unlock(&object->rwlock));

	return (ret);
}

VCL_VOID
vmod_integer_set(VRT_CTX, struct vmod_types_integer *object, VCL_INT value)
{
	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);
	CHECK_OBJ_NOTNULL(object, VMOD_TYPES_INTEGER_MAGIC);

	AZ(pthread_rwlock_wrlock(&object->rwlock));

	object->value = value;

	AZ(pthread_rwlock_unlock(&object->rwlock));
}

VCL_VOID
vmod_integer_increment(VRT_CTX, struct vmod_types_integer *object, VCL_INT value)
{
	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);
	CHECK_OBJ_NOTNULL(object, VMOD_TYPES_INTEGER_MAGIC);

	AZ(pthread_rwlock_wrlock(&object->rwlock));

	object->value += value;

	AZ(pthread_rwlock_unlock(&object->rwlock));
}

VCL_INT
vmod_integer_increment_get(VRT_CTX, struct vmod_types_integer *object, VCL_INT value)
{
	long ret;

	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);
	CHECK_OBJ_NOTNULL(object, VMOD_TYPES_INTEGER_MAGIC);

	AZ(pthread_rwlock_wrlock(&object->rwlock));

	object->value += value;

	ret = object->value;

	AZ(pthread_rwlock_unlock(&object->rwlock));

	return (ret);
}
