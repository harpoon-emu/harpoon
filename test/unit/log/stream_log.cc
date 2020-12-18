#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <harpoon/log/message.hh>
#include <harpoon/log/stream_log.hh>
#include <sstream>

TEST(stream_log, out) {
	std::stringstream ss;
	harpoon::log::stream_log l(ss);
	harpoon::log::message m(harpoon::log::message::Level::ERROR, "!!file!!", 1234, "@@function@@",
	                        "##component##");

	m.get_stream() << "==message==";

	l.out(m);

	EXPECT_THAT(ss.str(), testing::HasSubstr("==message=="));
}

TEST(stream_log, defaults) {
	std::stringstream ss;
	harpoon::log::stream_log l(ss);
	harpoon::log::message m(harpoon::log::message::Level::ERROR, "!!file!!", 31415, "@@function@@",
	                        "##component##");

	m.get_stream() << "==message==";

	l.out(m);

	EXPECT_THAT(ss.str(), testing::HasSubstr("##component##"));
	EXPECT_THAT(ss.str(), testing::Not(testing::HasSubstr("!!file!!")));
	EXPECT_THAT(ss.str(), testing::Not(testing::HasSubstr("@@function@@")));
	EXPECT_THAT(ss.str(), testing::Not(testing::HasSubstr("31415")));
}

TEST(stream_log, component) {
	std::stringstream ss;
	harpoon::log::stream_log l(ss);
	harpoon::log::message m(harpoon::log::message::Level::ERROR, "!!file!!", 31415, "@@function@@",
	                        "##component##");

	l.display_component(true);
	m.get_stream() << "==message==";

	l.out(m);

	EXPECT_THAT(ss.str(), testing::HasSubstr("##component##"));
}

TEST(stream_log, component_neg) {
	std::stringstream ss;
	harpoon::log::stream_log l(ss);
	harpoon::log::message m(harpoon::log::message::Level::ERROR, "!!file!!", 31415, "@@function@@",
	                        "##component##");

	l.display_component(false);
	m.get_stream() << "==message==";

	l.out(m);

	EXPECT_THAT(ss.str(), testing::Not(testing::HasSubstr("##component##")));
}

TEST(stream_log, file) {
	std::stringstream ss;
	harpoon::log::stream_log l(ss);
	harpoon::log::message m(harpoon::log::message::Level::ERROR, "!!file!!", 31415, "@@function@@",
	                        "##component##");

	l.display_file(true);
	m.get_stream() << "==message==";

	l.out(m);

	EXPECT_THAT(ss.str(), testing::HasSubstr("!!file!!"));
}

TEST(stream_log, file_neg) {
	std::stringstream ss;
	harpoon::log::stream_log l(ss);
	harpoon::log::message m(harpoon::log::message::Level::ERROR, "!!file!!", 31415, "@@function@@",
	                        "##component##");

	l.display_component(false);
	m.get_stream() << "==message==";

	l.out(m);

	EXPECT_THAT(ss.str(), testing::Not(testing::HasSubstr("##file##")));
}

TEST(stream_log, line) {
	std::stringstream ss;
	harpoon::log::stream_log l(ss);
	harpoon::log::message m(harpoon::log::message::Level::ERROR, "!!file!!", 31415, "@@function@@",
	                        "##component##");

	l.display_line(true);
	l.display_file(true);
	m.get_stream() << "==message==";

	l.out(m);

	EXPECT_THAT(ss.str(), testing::HasSubstr("31415"));
}

TEST(stream_log, line_neg_1) {
	std::stringstream ss;
	harpoon::log::stream_log l(ss);
	harpoon::log::message m(harpoon::log::message::Level::ERROR, "!!file!!", 31415, "@@function@@",
	                        "##component##");

	l.display_file(false);
	l.display_line(true);
	m.get_stream() << "==message==";

	l.out(m);

	EXPECT_THAT(ss.str(), testing::Not(testing::HasSubstr("31415")));
}

TEST(stream_log, line_neg_2) {
	std::stringstream ss;
	harpoon::log::stream_log l(ss);
	harpoon::log::message m(harpoon::log::message::Level::ERROR, "!!file!!", 31415, "@@function@@",
	                        "##component##");

	l.display_file(true);
	l.display_line(false);
	m.get_stream() << "==message==";

	l.out(m);

	EXPECT_THAT(ss.str(), testing::Not(testing::HasSubstr("31415")));
}

TEST(stream_log, line_neg_3) {
	std::stringstream ss;
	harpoon::log::stream_log l(ss);
	harpoon::log::message m(harpoon::log::message::Level::ERROR, "!!file!!", 31415, "@@function@@",
	                        "##component##");

	l.display_file(false);
	l.display_line(false);
	m.get_stream() << "==message==";

	l.out(m);

	EXPECT_THAT(ss.str(), testing::Not(testing::HasSubstr("31415")));
}

TEST(stream_log, function) {
	std::stringstream ss;
	harpoon::log::stream_log l(ss);
	harpoon::log::message m(harpoon::log::message::Level::ERROR, "!!file!!", 31415, "@@function@@",
	                        "##component##");

	l.display_function(true);
	m.get_stream() << "==message==";

	l.out(m);

	EXPECT_THAT(ss.str(), testing::HasSubstr("@@function@@"));
}

TEST(stream_log, function_neg) {
	std::stringstream ss;
	harpoon::log::stream_log l(ss);
	harpoon::log::message m(harpoon::log::message::Level::ERROR, "!!file!!", 31415, "@@function@@",
	                        "##component##");

	l.display_function(false);
	m.get_stream() << "==message==";

	l.out(m);

	EXPECT_THAT(ss.str(), testing::Not(testing::HasSubstr("@@function@@")));
}
