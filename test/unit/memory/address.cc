#include <gtest/gtest.h>
#include <harpoon/memory/address.hh>

TEST(address, hold) {
	harpoon::memory::address a = 0x1013;

	ASSERT_EQ(a, 0x1013);
}

TEST(address, add) {
	harpoon::memory::address a = 0x1234;
	a += 0x1000;
	ASSERT_EQ(a, 0x2234);
}

TEST(address, sub) {
	harpoon::memory::address a = 0x1234;
	a -= 0x1000;
	ASSERT_EQ(a, 0x0234);
}
