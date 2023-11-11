extern "C" {
	#include "kernel.h"
}
#include <atomic>
#include <thread>
#include "gtest/gtest.h"

static std::atomic_bool hos_is_done(false);
static int gtest_result = 0;
static std::atomic_bool gtest_is_done(false);

static void drive_hos(void) {
	vsta_knl();
	hos_is_done = true;
}

void wait_for_hos(void) {
	while(!hos_is_done) {
		_sleep(1000);
	}
}

static void drive_gtest(void) {
	gtest_result = RUN_ALL_TESTS();
	gtest_is_done = true;
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);

	std::thread th_hos(drive_hos);
	th_hos.detach();
	std::thread th_gtest(drive_gtest);
	th_gtest.detach();

	while(!gtest_is_done && !hos_is_done) {
		_sleep(1000);
	}

	return gtest_result;  
}

/* end of file */
