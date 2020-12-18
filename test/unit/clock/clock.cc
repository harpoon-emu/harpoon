#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <harpoon/clock/clock.hh>
#include <harpoon/clock/exception/dead_clock.hh>
#include <harpoon/log/queue_log.hh>

namespace {

namespace mocks {

class step {
public:
	MOCK_METHOD(void, do_call, (harpoon::clock::clock * c, const harpoon::clock::cycle &cycle));
};

} // namespace mocks

class clock : public ::testing::Test {
protected:
	harpoon::clock::clock_ptr _clock;

	virtual void SetUp() {
		_clock = harpoon::clock::make_clock(1000000);
		_clock->set_name("clock_TEST");
		_clock->prepare();
		_clock->boot();
	}

	virtual void TearDown() {
		_clock->shutdown();
		_clock->cleanup();
	}
};

TEST_F(clock, log_state) {
	harpoon::log::queue_log_ptr l = harpoon::log::make_queue_log();

	_clock->set_log(l);

	_clock->log_state(harpoon::log::message::Level::NOTICE);

	EXPECT_FALSE(l->empty());
	auto m = l->pop();
	EXPECT_EQ(m.get_component(), _clock->get_name());
	EXPECT_EQ(m.get_level(), harpoon::log::message::Level::NOTICE);
}

TEST_F(clock, dead_clock) {
	EXPECT_THROW({ _clock->step(_clock.get()); }, harpoon::clock::exception::dead_clock);
}

TEST_F(clock, schedule_1) {
	mocks::step h1;

	_clock->schedule(10, 0, [&h1](harpoon::clock::clock *c) { h1.do_call(c, c->get_cycle()); });

	EXPECT_CALL(h1, do_call(_clock.get(), harpoon::clock::cycle{10, 0}));

	EXPECT_THROW(
	    {
		    _clock->step(_clock.get());
		    _clock->step(_clock.get());
	    },
	    harpoon::clock::exception::dead_clock);
}

TEST_F(clock, schedule_2) {
	mocks::step h1, h2;

	_clock->schedule(20, 0, [&h2](harpoon::clock::clock *c) { h2.do_call(c, c->get_cycle()); });
	_clock->schedule(10, 0, [&h1](harpoon::clock::clock *c) { h1.do_call(c, c->get_cycle()); });

	{
		testing::InSequence s;

		EXPECT_CALL(h1, do_call(_clock.get(), harpoon::clock::cycle{10, 0}));
		EXPECT_CALL(h2, do_call(_clock.get(), harpoon::clock::cycle{20, 0}));
	}

	EXPECT_THROW(
	    {
		    _clock->step(_clock.get());
		    _clock->step(_clock.get());
		    _clock->step(_clock.get());
	    },
	    harpoon::clock::exception::dead_clock);
}

TEST_F(clock, schedule_2_same) {
	mocks::step h1, h2;

	_clock->schedule(10, 0, [&h2](harpoon::clock::clock *c) { h2.do_call(c, c->get_cycle()); });
	_clock->schedule(10, 0, [&h1](harpoon::clock::clock *c) { h1.do_call(c, c->get_cycle()); });

	EXPECT_CALL(h1, do_call(_clock.get(), harpoon::clock::cycle{10, 0}));
	EXPECT_CALL(h2, do_call(_clock.get(), harpoon::clock::cycle{10, 0}));

	EXPECT_THROW(
	    {
		    _clock->step(_clock.get());
		    _clock->step(_clock.get());
		    _clock->step(_clock.get());
	    },
	    harpoon::clock::exception::dead_clock);
}

TEST_F(clock, schedule_2_same_diff_phases) {
	mocks::step h1, h2;

	_clock->schedule(10, 0, [&h1](harpoon::clock::clock *c) { h1.do_call(c, c->get_cycle()); });
	_clock->schedule(10, 1, [&h2](harpoon::clock::clock *c) { h2.do_call(c, c->get_cycle()); });

	{
		testing::InSequence s;

		EXPECT_CALL(h1, do_call(_clock.get(), harpoon::clock::cycle{10, 0}));
		EXPECT_CALL(h2, do_call(_clock.get(), harpoon::clock::cycle{10, 1}));
	}

	EXPECT_THROW(
	    {
		    _clock->step(_clock.get());
		    _clock->step(_clock.get());
		    _clock->step(_clock.get());
	    },
	    harpoon::clock::exception::dead_clock);
}

TEST_F(clock, schedule_chain) {
	mocks::step h1, h2;

	_clock->schedule(10, 0, [&h1, &h2](harpoon::clock::clock *c) {
		h1.do_call(c, c->get_cycle());
		c->schedule(20, 0, [&h2](harpoon::clock::clock *c) { h2.do_call(c, c->get_cycle()); });
	});


	{
		testing::InSequence s;

		EXPECT_CALL(h1, do_call(_clock.get(), harpoon::clock::cycle{10, 0}));
		EXPECT_CALL(h2, do_call(_clock.get(), harpoon::clock::cycle{30, 0}));
	}

	EXPECT_THROW(
	    {
		    _clock->step(_clock.get());
		    _clock->step(_clock.get());
		    _clock->step(_clock.get());
	    },
	    harpoon::clock::exception::dead_clock);
}

TEST_F(clock, schedule_chain_phase) {
	mocks::step h1, h2;

	_clock->schedule(10, 0, [&h1, &h2](harpoon::clock::clock *c) {
		h1.do_call(c, c->get_cycle());
		c->schedule(0, 1, [&h2](harpoon::clock::clock *c) { h2.do_call(c, c->get_cycle()); });
	});


	{
		testing::InSequence s;

		EXPECT_CALL(h1, do_call(_clock.get(), harpoon::clock::cycle{10, 0}));
		EXPECT_CALL(h2, do_call(_clock.get(), harpoon::clock::cycle{10, 1}));
	}

	EXPECT_THROW(
	    {
		    _clock->step(_clock.get());
		    _clock->step(_clock.get());
		    _clock->step(_clock.get());
	    },
	    harpoon::clock::exception::dead_clock);
}

} // namespace
