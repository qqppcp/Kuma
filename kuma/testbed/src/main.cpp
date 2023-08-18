#include "core/logger.h"
#include "core/asserts.h"
#include "platform/platform.h"

int main()
{
	KFATAL("Output: %f", 3.14f);
	KERROR("Output: %f", 3.14f);
	KWARN("Output: %f", 3.14f);
	KINFO("Output: %f", 3.14f);
	KDEBUG("Output: %f", 3.14f);
	KTRACE("Output: %f", 3.14f);

	platform_state state;
	if (platform_startup(&state, "Kohi Engine Testbed", 100, 100, 1280, 720)) {
		while (TRUE) {
			platform_pump_messages(&state);
		}
	}
	platform_shutdown(&state);

	KASSERT(FALSE);
}