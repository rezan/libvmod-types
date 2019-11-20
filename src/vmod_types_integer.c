#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache/cache.h"
#include "vcl.h"

#include "vcc_types_if.h"


struct vmod_types_integer {
	unsigned			magic;
#define VMOD_TYPES_INTEGER_MAGIC	0x6714BA6E

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

	object = WS_Alloc(ctx->ws, sizeof(struct vmod_types_integer));

	if (!object) {
		VRT_fail(ctx, "Out of workspace");
                return;
	}

	INIT_OBJ(object, VMOD_TYPES_INTEGER_MAGIC);
	object->value = value;

	*object_p = object;
}

VCL_VOID
vmod_integer__fini(struct vmod_types_integer **object_p)
{
	AN(object_p);
	CHECK_OBJ_NOTNULL(*object_p, VMOD_TYPES_INTEGER_MAGIC);

	INIT_OBJ(*object_p, 0);
}

VCL_INT
vmod_integer_value(VRT_CTX, struct vmod_types_integer *object)
{
	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);
	CHECK_OBJ_NOTNULL(object, VMOD_TYPES_INTEGER_MAGIC);

	return (object->value);
}

VCL_VOID
vmod_integer_set(VRT_CTX, struct vmod_types_integer *object, VCL_INT value)
{
	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);
	CHECK_OBJ_NOTNULL(object, VMOD_TYPES_INTEGER_MAGIC);

	object->value = value;
}

VCL_INT
vmod_integer_increment(VRT_CTX, struct vmod_types_integer *object, VCL_INT value)
{
	CHECK_OBJ_NOTNULL(ctx, VRT_CTX_MAGIC);
	CHECK_OBJ_NOTNULL(object, VMOD_TYPES_INTEGER_MAGIC);

	object->value += value;

	return (object->value);
}
