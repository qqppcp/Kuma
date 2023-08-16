#include "core/logger.h"
#include "core/asserts.h"

int main()
{
	KFATAL("Output: %f", 3.14f);
	KERROR("Output: %f", 3.14f);
	KWARN("Output: %f", 3.14f);
	KINFO("Output: %f", 3.14f);
	KDEBUG("Output: %f", 3.14f);
	KTRACE("Output: %f", 3.14f);

	KASSERT(FALSE);
}