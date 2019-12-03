#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache/cache.h"
#include "vcl.h"

#include "vcc_types_if.h"


struct vmod_types_string {
	unsigned			magic;
#define VMOD_TYPES_STRING_MAGIC		0xB2045F8E

	const char			*value;
	size_t				length;
};

VCL_VOID
vmod_string__init(VRT_CTX, struct vmod_types_string **object_p,
	const char *vcl_name, VCL_STRING value)
{
	struct vmod_types_string *object;

	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);
	AN(object_p);
	AN(vcl_name);

	if (!value) {
		value = "";
	}

	object = WS_Alloc(ctx->ws, sizeof(struct vmod_types_string));
	if (!object) {
		VRT_fail(ctx, "Out of workspace");
                return;
	}

	INIT_OBJ(object, VMOD_TYPES_STRING_MAGIC);
	object->value = value;
	object->length = strlen(object->value);

	*object_p = object;
}

VCL_VOID
vmod_string__fini(struct vmod_types_string **object_p)
{
	AN(object_p);
	CHECK_OBJ_NOTNULL(*object_p, VMOD_TYPES_STRING_MAGIC);

	INIT_OBJ(*object_p, 0);
}

VCL_STRING
vmod_string_value(VRT_CTX, struct vmod_types_string *object)
{
	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);
	CHECK_OBJ_NOTNULL(object, VMOD_TYPES_STRING_MAGIC);

	return (object->value);
}

VCL_INT
vmod_string_length(VRT_CTX, struct vmod_types_string *object)
{
	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);
	CHECK_OBJ_NOTNULL(object, VMOD_TYPES_STRING_MAGIC);

	return ((VCL_INT)object->length);
}

VCL_VOID
vmod_string_set(VRT_CTX, struct vmod_types_string *object, VCL_STRING value)
{
	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);
	CHECK_OBJ_NOTNULL(object, VMOD_TYPES_STRING_MAGIC);

	if (!value) {
		value = "";
	}

	object->value = value;
	object->length = strlen(object->value);
}
