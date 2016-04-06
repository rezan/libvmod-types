#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "vcl.h"
#include "vrt.h"
#include "cache/cache.h"

#include "vcc_if.h"


struct vmod_types_string {
	unsigned			magic;
#define VMOD_TYPES_STRING_MAGIC		0xB2045F8E

	pthread_rwlock_t		rwlock;

	char				*value;

	size_t				length;
};

VCL_VOID
vmod_string__init(VRT_CTX, struct vmod_types_string **object_p,
	const char *vcl_name, VCL_STRING value)
{
	struct vmod_types_string *object;

	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);
	AN(object_p);
	AZ(*object_p);
	AN(vcl_name);

	if (!value) {
		value = "";
	}

	ALLOC_OBJ(object, VMOD_TYPES_STRING_MAGIC);
	AN(object);

	AZ(pthread_rwlock_init(&object->rwlock, NULL));

	REPLACE(object->value, value);

	object->length = strlen(object->value);

	*object_p = object;
}

VCL_VOID
vmod_string__fini(struct vmod_types_string **object_p)
{
	AN(object_p);
	CHECK_OBJ_NOTNULL(*object_p, VMOD_TYPES_STRING_MAGIC);

	AZ(pthread_rwlock_destroy(&(*object_p)->rwlock));

	free((*object_p)->value);

	FREE_OBJ(*object_p);
}

VCL_STRING
vmod_string_value(VRT_CTX, struct vmod_types_string *object)
{
	char *value;
	unsigned available;

	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);
	CHECK_OBJ_NOTNULL(object, VMOD_TYPES_STRING_MAGIC);

	AZ(pthread_rwlock_rdlock(&object->rwlock));

	available = WS_Reserve(ctx->ws, 0);
	value = ctx->ws->f;

	if (available < object->length + 1) {
		WS_Release(ctx->ws, 0);
		return NULL;
	}

	strcpy(value, object->value);

	WS_Release(ctx->ws, object->length + 1);

	AZ(pthread_rwlock_unlock(&object->rwlock));

	return (value);
}

VCL_INT
vmod_string_length(VRT_CTX, struct vmod_types_string *object)
{
	long ret;
	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);
	CHECK_OBJ_NOTNULL(object, VMOD_TYPES_STRING_MAGIC);

	AZ(pthread_rwlock_rdlock(&object->rwlock));

	ret = (long)object->length;

	AZ(pthread_rwlock_unlock(&object->rwlock));

	return (ret);
}

VCL_VOID
vmod_string_set(VRT_CTX, struct vmod_types_string *object, VCL_STRING value)
{
	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);
	CHECK_OBJ_NOTNULL(object, VMOD_TYPES_STRING_MAGIC);

	AZ(pthread_rwlock_wrlock(&object->rwlock));

	REPLACE(object->value, value);

	object->length = strlen(object->value);

	AZ(pthread_rwlock_unlock(&object->rwlock));
}