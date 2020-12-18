#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <harpoon/log/log.hh>
#include <harpoon/log/message.hh>

namespace mocks {
class log : public harpoon::log::log {
public:
	using harpoon::log::log::out;
	MOCK_METHOD(void, out, (const harpoon::log::message &message), (override));
};

} // namespace mocks

namespace harpoon {
namespace log {

static bool operator==(const harpoon::log::message &a, const harpoon::log::message &b) {
	return a.get_component() == b.get_component() && a.get_file() == b.get_file()
	       && a.get_function() == b.get_function() && a.get_level() == b.get_level()
	       && a.get_line() == b.get_line() && a.get_text() == b.get_text();
}

} // namespace log
} // namespace harpoon

TEST(log, out) {
	std::shared_ptr<mocks::log> l(new mocks::log);
	harpoon::log::message m(harpoon::log::message::Level::ERROR, "file", 1234, "function",
	                        "component");

	EXPECT_CALL(*l, out(m)).Times(1);

	l->out(m.get_stream());
}
