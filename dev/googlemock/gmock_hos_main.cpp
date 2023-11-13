extern "C" {
	#include "kernel.h"
}
#include <atomic>
#include <thread>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

static std::atomic_bool hos_is_done(false);
static int gtest_result = 0;
static std::atomic_bool gtest_is_done(false);
extern "C" void drive_gtest(VP_INT exinf);

static void drive_hos(void) {
	vsta_knl();
	hos_is_done = true;
}

extern "C" void drive_gtest(VP_INT exinf) {
	(void)exinf;
	gtest_result = RUN_ALL_TESTS();
	gtest_is_done = true;
	vter_knl();
}

int main(int argc, char **argv) {
	testing::InitGoogleMock(&argc, argv);

	std::thread th_hos(drive_hos);
	th_hos.detach();

	while(!gtest_is_done && !hos_is_done) {
		_sleep(1000);
	}

	return gtest_result;  
}

/* end of file */
