#include <gtest/gtest.h>
#include <harpoon/log/message.hh>

TEST(message, constructor) {
	harpoon::log::message m(harpoon::log::message::Level::ERROR, "file", 1234, "function",
	                        "component");

	ASSERT_EQ(m.get_level(), harpoon::log::message::Level::ERROR);
	ASSERT_EQ(m.get_file(), "file");
	ASSERT_EQ(m.get_line(), 1234);
	ASSERT_EQ(m.get_function(), "function");
	ASSERT_EQ(m.get_component(), "component");
}
