#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <harpoon/log/message.hh>
#include <harpoon/log/queue_log.hh>

namespace harpoon {
namespace log {

static bool operator==(const harpoon::log::message &a, const harpoon::log::message &b) {
	return a.get_component() == b.get_component() && a.get_file() == b.get_file()
	       && a.get_function() == b.get_function() && a.get_level() == b.get_level()
	       && a.get_line() == b.get_line() && a.get_text() == b.get_text();
}

} // namespace log
} // namespace harpoon

TEST(queue_log, constructor) {
	harpoon::log::queue_log_ptr l = harpoon::log::make_queue_log();

	EXPECT_TRUE(l->empty());
}

TEST(queue_log, out_1) {
	harpoon::log::queue_log_ptr l = harpoon::log::make_queue_log();
	harpoon::log::message m(harpoon::log::message::Level::ERROR, "!!file!!", 31415, "@@function@@",
	                        "##component##");

	l->out(m);
	EXPECT_FALSE(l->empty());

	auto o = l->pop();
	EXPECT_EQ(m, o);
}

TEST(queue_log, out_n) {
	harpoon::log::queue_log_ptr l = harpoon::log::make_queue_log();
	harpoon::log::message m1(harpoon::log::message::Level::ERROR, "!!file1!!", 31415,
	                         "@@function@@", "##component##");
	harpoon::log::message m2(harpoon::log::message::Level::ERROR, "!!file2!!", 31415,
	                         "@@function@@", "##component##");
	harpoon::log::message m3(harpoon::log::message::Level::ERROR, "!!file3!!", 31415,
	                         "@@function@@", "##component##");

	l->out(m1);
	l->out(m2);
	l->out(m3);
	EXPECT_FALSE(l->empty());

	auto o = l->pop();
	EXPECT_EQ(m1, o);
	o = l->pop();
	EXPECT_EQ(m2, o);
	o = l->pop();
	EXPECT_EQ(m3, o);
}

TEST(queue_log, pop) {
	harpoon::log::queue_log_ptr l = harpoon::log::make_queue_log();
	harpoon::log::message m1(harpoon::log::message::Level::ERROR, "!!file!!", 31415, "@@function@@",
	                         "##component##");
	harpoon::log::message m2(harpoon::log::message::Level::ERROR, "!!file!!", 31415, "@@function@@",
	                         "##component##");
	harpoon::log::message m3(harpoon::log::message::Level::ERROR, "!!file!!", 31415, "@@function@@",
	                         "##component##");

	l->out(m1);
	l->out(m2);
	l->out(m3);
	l->pop();
	l->pop();
	l->pop();
	EXPECT_TRUE(l->empty());
}

TEST(queue_log, clear) {
	harpoon::log::queue_log_ptr l = harpoon::log::make_queue_log();
	harpoon::log::message m1(harpoon::log::message::Level::ERROR, "!!file!!", 31415, "@@function@@",
	                         "##component##");
	harpoon::log::message m2(harpoon::log::message::Level::ERROR, "!!file!!", 31415, "@@function@@",
	                         "##component##");
	harpoon::log::message m3(harpoon::log::message::Level::ERROR, "!!file!!", 31415, "@@function@@",
	                         "##component##");

	l->out(m1);
	l->out(m2);
	l->out(m3);
	l->clear();
	EXPECT_TRUE(l->empty());
}
