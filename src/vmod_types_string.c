#include <stdio.h>
#include <stdlib.h>

#include "vcl.h"
#include "vrt.h"
#include "cache/cache.h"

#include "vcc_if.h"


struct vmod_types_string {
	unsigned			magic;
#define VMOD_TYPES_STRING_MAGIC		0xB2045F8E

	char				*value;
	char				*vcl_name;

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

	REPLACE(object->value, value);
	REPLACE(object->vcl_name, vcl_name);

	object->length = strlen(object->value);

	*object_p = object;
}

VCL_VOID
vmod_string__fini(struct vmod_types_string **object_p)
{
	AN(object_p);
	CHECK_OBJ_NOTNULL(*object_p, VMOD_TYPES_STRING_MAGIC);

	free((*object_p)->value);
	free((*object_p)->vcl_name);

	FREE_OBJ(*object_p);
}

VCL_STRING
vmod_string_value(VRT_CTX, struct vmod_types_string *object)
{
	char *value;
	unsigned available;

	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);
	CHECK_OBJ_NOTNULL(object, VMOD_TYPES_STRING_MAGIC);

	available = WS_Reserve(ctx->ws, 0);
	value = ctx->ws->f;

	if (available < object->length + 1) {
		WS_Release(ctx->ws, 0);
		return NULL;
	}

	strcpy(value, object->value);

	WS_Release(ctx->ws, object->length + 1);

	return(value);
}

VCL_INT
vmod_string_length(VRT_CTX, struct vmod_types_string *object)
{
	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);
	CHECK_OBJ_NOTNULL(object, VMOD_TYPES_STRING_MAGIC);

	return((long)object->length);
}