#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <harpoon/exception/component_loop.hh>
#include <harpoon/exception/not_subcomponent.hh>
#include <harpoon/exception/subcomponent_owned.hh>
#include <harpoon/exception/wrong_state.hh>
#include <harpoon/hardware_component.hh>


namespace mocks {
class hardware_component : public harpoon::hardware_component {
public:
	hardware_component(const std::string &name) : harpoon::hardware_component(name) {
		ON_CALL(*this, prepare).WillByDefault([this]() { harpoon::hardware_component::prepare(); });
		ON_CALL(*this, cleanup).WillByDefault([this]() { harpoon::hardware_component::cleanup(); });
		ON_CALL(*this, boot).WillByDefault([this]() { harpoon::hardware_component::boot(); });
		ON_CALL(*this, shutdown).WillByDefault([this]() {
			harpoon::hardware_component::shutdown();
		});
	}

	MOCK_METHOD(void, prepare, (), (override));
	MOCK_METHOD(void, cleanup, (), (override));
	MOCK_METHOD(void, boot, (), (override));
	MOCK_METHOD(void, shutdown, (), (override));
};

using hardware_component_ptr = std::shared_ptr<hardware_component>;
using hc = hardware_component;
using hcp = hardware_component_ptr;

} // namespace mocks

using hc = harpoon::hardware_component;
using hcp = harpoon::hardware_component_ptr;

TEST(hardware_component_state, constructor_default) {
	hc::state s;

	EXPECT_FALSE(s.is_prepared());
	EXPECT_FALSE(s.is_running());
}

TEST(hardware_component_state, constructor) {
	hc::state s(true, true);

	EXPECT_TRUE(s.is_prepared());
	EXPECT_TRUE(s.is_running());
}

TEST(hardware_component_state, setters) {
	hc::state s;

	EXPECT_FALSE(s.is_prepared());
	EXPECT_FALSE(s.is_running());

	s.set_prepared();
	EXPECT_TRUE(s.is_prepared());
	EXPECT_FALSE(s.is_running());

	s.set_running();
	EXPECT_TRUE(s.is_prepared());
	EXPECT_TRUE(s.is_running());

	s.clear_running();
	EXPECT_TRUE(s.is_prepared());
	EXPECT_FALSE(s.is_running());

	s.clear_prepared();
	EXPECT_FALSE(s.is_prepared());
	EXPECT_FALSE(s.is_running());
}

TEST(hardware_component, constructor) {
	hc c("hw-component");

	EXPECT_EQ(c.get_name(), "hw-component");
	EXPECT_EQ(c.get_parent_component(), nullptr);
	EXPECT_FALSE(c.is_running());
	EXPECT_FALSE(c.is_prepared());
}

TEST(hardware_component, setters) {
	hcp p1(new hc("hw-component1"));

	EXPECT_EQ(p1->get_name(), "hw-component1");

	p1->set_name("hw-component2");
	EXPECT_EQ(p1->get_name(), "hw-component2");
}

TEST(hardware_component, add_component) {
	hcp p1(new hc("hw-component-parent"));
	hcp c1(new hc("hw-component-child"));

	p1->add_component(c1);
	EXPECT_TRUE(c1->has_parent_component());
	EXPECT_EQ(c1->get_parent_component(), p1);
}

TEST(hardware_component, add_component_owned) {
	hcp p1(new hc("hw-component-parent1"));
	hcp p2(new hc("hw-component-parent2"));
	hcp c1(new hc("hw-component-child1"));

	p2->add_component(c1);

	EXPECT_THROW({ p1->add_component(c1); }, harpoon::exception::subcomponent_owned);
	EXPECT_TRUE(c1->has_parent_component());
	EXPECT_EQ(c1->get_parent_component(), p2);
}

TEST(hardware_component, add_component_circular_0) {
	hcp c1(new hc("hw-component1"));

	EXPECT_THROW({ c1->add_component(c1); }, harpoon::exception::component_loop);
	EXPECT_FALSE(c1->has_parent_component());
	EXPECT_FALSE(c1->has_subcomponent(c1));
}

TEST(hardware_component, add_component_circular_1) {
	hcp c1(new hc("hw-component1"));
	hcp c2(new hc("hw-component2"));

	c1->add_component(c2);
	EXPECT_THROW({ c2->add_component(c1); }, harpoon::exception::component_loop);
	EXPECT_FALSE(c1->has_parent_component());
	EXPECT_FALSE(c2->has_subcomponent(c1));
	EXPECT_TRUE(c1->has_subcomponent(c2));
}

TEST(hardware_component, add_component_circular_deep) {
	hcp c1(new hc("hw-component1"));
	hcp c2(new hc("hw-component2"));
	hcp c3(new hc("hw-component3"));
	hcp c4(new hc("hw-component4"));

	c1->add_component(c2);
	c2->add_component(c3);
	c3->add_component(c4);

	EXPECT_THROW({ c4->add_component(c1); }, harpoon::exception::component_loop);
	EXPECT_FALSE(c1->has_parent_component());
	EXPECT_FALSE(c4->has_subcomponent(c1));

	EXPECT_THROW({ c3->add_component(c1); }, harpoon::exception::component_loop);
	EXPECT_FALSE(c1->has_parent_component());
	EXPECT_FALSE(c3->has_subcomponent(c1));

	EXPECT_THROW({ c2->add_component(c1); }, harpoon::exception::component_loop);
	EXPECT_FALSE(c1->has_parent_component());
	EXPECT_FALSE(c2->has_subcomponent(c1));
}

TEST(hardware_component, has_subcomponent) {
	hcp p1(new hc("hw-component-parent1"));
	hcp c1(new hc("hw-component-child"));

	p1->add_component(c1);
	EXPECT_TRUE(p1->has_subcomponent(c1));
}

TEST(hardware_component, has_subcomponent_neg) {
	hcp p1(new hc("hw-component-parent1"));
	hcp p2(new hc("hw-component-parent2"));
	hcp c1(new hc("hw-component-child"));

	EXPECT_FALSE(p1->has_subcomponent(c1));

	p1->add_component(c1);
	EXPECT_FALSE(p2->has_subcomponent(c1));
}

TEST(hardware_component, has_subcomponent_deep) {
	hcp c1(new hc("hw-component1"));
	hcp c2(new hc("hw-component1"));
	hcp c3(new hc("hw-component1"));
	hcp c4(new hc("hw-component1"));

	c1->add_component(c2);
	c2->add_component(c3);
	c3->add_component(c4);

	EXPECT_TRUE(c1->has_subcomponent(c2, true));
	EXPECT_TRUE(c1->has_subcomponent(c3, true));
	EXPECT_TRUE(c1->has_subcomponent(c4, true));
	EXPECT_TRUE(c2->has_subcomponent(c3, true));
	EXPECT_TRUE(c2->has_subcomponent(c4, true));
	EXPECT_TRUE(c3->has_subcomponent(c4, true));
}

TEST(hardware_component, has_subcomponent_deep_neg) {
	hcp c1(new hc("hw-component1"));
	hcp c2(new hc("hw-component1"));
	hcp c3(new hc("hw-component1"));
	hcp c4(new hc("hw-component1"));

	c1->add_component(c2);
	c2->add_component(c3);

	EXPECT_FALSE(c1->has_subcomponent(c4, true));
	EXPECT_FALSE(c2->has_subcomponent(c4, true));
	EXPECT_FALSE(c3->has_subcomponent(c4, true));
}

TEST(hardware_component, is_subcomponent_of) {
	hcp p1(new hc("hw-component-parent1"));
	hcp c1(new hc("hw-component-child"));

	p1->add_component(c1);
	EXPECT_TRUE(c1->is_subcomponent_of(p1));
}

TEST(hardware_component, is_subcomponent_of_neg) {
	hcp p1(new hc("hw-component-parent1"));
	hcp p2(new hc("hw-component-parent2"));
	hcp c1(new hc("hw-component-child"));

	EXPECT_FALSE(c1->is_subcomponent_of(p1));

	p1->add_component(c1);
	EXPECT_FALSE(c1->is_subcomponent_of(p2));
}

TEST(hardware_component, is_subcomponent_of_deep) {
	hcp c1(new hc("hw-component1"));
	hcp c2(new hc("hw-component1"));
	hcp c3(new hc("hw-component1"));
	hcp c4(new hc("hw-component1"));

	c1->add_component(c2);
	c2->add_component(c3);
	c3->add_component(c4);

	EXPECT_TRUE(c2->is_subcomponent_of(c1, true));
	EXPECT_TRUE(c3->is_subcomponent_of(c1, true));
	EXPECT_TRUE(c3->is_subcomponent_of(c2, true));
	EXPECT_TRUE(c4->is_subcomponent_of(c1, true));
	EXPECT_TRUE(c4->is_subcomponent_of(c2, true));
	EXPECT_TRUE(c4->is_subcomponent_of(c3, true));
}

TEST(hardware_component, remove_component) {
	hcp p1(new hc("hw-component-parent"));
	hcp c1(new hc("hw-component-child"));

	p1->add_component(c1);
	EXPECT_TRUE(c1->has_parent_component());
	EXPECT_EQ(c1->get_parent_component(), p1);

	p1->remove_component(c1);
	EXPECT_FALSE(c1->has_parent_component());
	EXPECT_EQ(c1->get_parent_component(), nullptr);
}

TEST(hardware_component, remove_component_neg) {
	hcp p1(new hc("hw-component-parent1"));
	hcp p2(new hc("hw-component-parent2"));
	hcp c1(new hc("hw-component-child"));

	p1->add_component(c1);
	EXPECT_TRUE(c1->has_parent_component());
	EXPECT_EQ(c1->get_parent_component(), p1);

	EXPECT_THROW({ p2->remove_component(c1); }, harpoon::exception::not_subcomponent);
	EXPECT_TRUE(c1->has_parent_component());
	EXPECT_EQ(c1->get_parent_component(), p1);
}

TEST(hardware_component, replace_component) {
	hcp p1(new hc("hw-component-parent"));
	hcp c1(new hc("hw-component-child1"));
	hcp c2(new hc("hw-component-child2"));

	p1->add_component(c1);
	EXPECT_TRUE(c1->has_parent_component());
	EXPECT_EQ(c1->get_parent_component(), p1);

	p1->replace_component(c1, c2);
	EXPECT_FALSE(c1->has_parent_component());
	EXPECT_EQ(c1->get_parent_component(), nullptr);
	EXPECT_TRUE(c2->has_parent_component());
	EXPECT_EQ(c2->get_parent_component(), p1);
}

TEST(hardware_component, replace_component_neg) {
	hcp p1(new hc("hw-component-parent1"));
	hcp p2(new hc("hw-component-parent2"));
	hcp c1(new hc("hw-component-child1"));
	hcp c2(new hc("hw-component-child2"));

	p1->add_component(c1);
	EXPECT_TRUE(c1->has_parent_component());
	EXPECT_EQ(c1->get_parent_component(), p1);

	EXPECT_THROW({ p2->replace_component(c1, c2); }, harpoon::exception::not_subcomponent);
	EXPECT_TRUE(c1->has_parent_component());
	EXPECT_EQ(c1->get_parent_component(), p1);
	EXPECT_FALSE(c2->has_parent_component());
	EXPECT_EQ(c2->get_parent_component(), nullptr);
}

TEST(hardware_component, replace_component_owned) {
	hcp p1(new hc("hw-component-parent1"));
	hcp p2(new hc("hw-component-parent2"));
	hcp c1(new hc("hw-component-child1"));
	hcp c2(new hc("hw-component-child2"));

	p1->add_component(c1);
	p2->add_component(c2);
	EXPECT_TRUE(c1->has_parent_component());
	EXPECT_EQ(c1->get_parent_component(), p1);
	EXPECT_TRUE(c2->has_parent_component());
	EXPECT_EQ(c2->get_parent_component(), p2);

	EXPECT_THROW({ p1->replace_component(c1, c2); }, harpoon::exception::subcomponent_owned);
	EXPECT_TRUE(c1->has_parent_component());
	EXPECT_EQ(c1->get_parent_component(), p1);
	EXPECT_TRUE(c2->has_parent_component());
	EXPECT_EQ(c2->get_parent_component(), p2);
}

TEST(hardware_component, replace_component_circular_0) {
	hcp c1(new hc("hw-component1"));
	hcp c2(new hc("hw-component2"));

	c1->add_component(c2);
	EXPECT_THROW({ c1->replace_component(c2, c1); }, harpoon::exception::component_loop);
	EXPECT_FALSE(c1->has_parent_component());
	EXPECT_TRUE(c1->has_subcomponent(c2));
	EXPECT_FALSE(c1->has_subcomponent(c1));
}

TEST(hardware_component, replace_component_circular_1) {
	hcp c1(new hc("hw-component1"));
	hcp c2(new hc("hw-component2"));
	hcp c3(new hc("hw-component3"));

	c1->add_component(c2);
	c2->add_component(c3);
	EXPECT_THROW({ c2->replace_component(c3, c1); }, harpoon::exception::component_loop);
	EXPECT_FALSE(c1->has_parent_component());
	EXPECT_FALSE(c2->has_subcomponent(c1));
	EXPECT_TRUE(c1->has_subcomponent(c2));
	EXPECT_TRUE(c2->has_subcomponent(c3));
	EXPECT_TRUE(c3->has_parent_component());
	EXPECT_EQ(c3->get_parent_component(), c2);
}

TEST(hardware_component, replace_component_circular_deep) {
	hcp c1(new hc("hw-component1"));
	hcp c2(new hc("hw-component2"));
	hcp c3(new hc("hw-component3"));
	hcp c4(new hc("hw-component4"));

	c1->add_component(c2);
	c2->add_component(c3);
	c3->add_component(c4);
	EXPECT_THROW({ c3->replace_component(c4, c1); }, harpoon::exception::component_loop);
	EXPECT_FALSE(c1->has_parent_component());
	EXPECT_FALSE(c3->has_subcomponent(c1));
	EXPECT_TRUE(c3->has_subcomponent(c4));
	EXPECT_TRUE(c4->has_parent_component());
	EXPECT_EQ(c4->get_parent_component(), c3);
}

TEST(hardware_component, prepare) {
	hcp c1(new hc("hw-component1"));

	c1->prepare();
	EXPECT_TRUE(c1->is_prepared());
	EXPECT_FALSE(c1->is_running());
}

TEST(hardware_component, prepare_double) {
	hcp c1(new hc("hw-component1"));

	c1->prepare();
	EXPECT_THROW({ c1->prepare(); }, harpoon::exception::wrong_state);
	EXPECT_TRUE(c1->is_prepared());
	EXPECT_FALSE(c1->is_running());
}

TEST(hardware_component, prepare_chain) {
	hcp c1(new hc("hw-component1"));
	mocks::hcp c2(new mocks::hc("hw-component2"));
	mocks::hcp c3(new mocks::hc("hw-component3"));
	mocks::hcp c4(new mocks::hc("hw-component4"));

	c1->add_component(c2);
	c2->add_component(c3);
	c3->add_component(c4);

	EXPECT_CALL(*c2, prepare()).Times(1);
	EXPECT_CALL(*c3, prepare()).Times(1);
	EXPECT_CALL(*c4, prepare()).Times(1);
	c1->prepare();

	EXPECT_TRUE(c1->is_prepared());
	EXPECT_TRUE(c2->is_prepared());
	EXPECT_TRUE(c3->is_prepared());
	EXPECT_TRUE(c4->is_prepared());
	EXPECT_FALSE(c1->is_running());
	EXPECT_FALSE(c2->is_running());
	EXPECT_FALSE(c3->is_running());
	EXPECT_FALSE(c4->is_running());
}

TEST(hardware_component, boot) {
	hcp c1(new hc("hw-component1"));

	c1->prepare();

	c1->boot();
	EXPECT_TRUE(c1->is_prepared());
	EXPECT_TRUE(c1->is_running());
}

TEST(hardware_component, boot_double) {
	hcp c1(new hc("hw-component1"));

	c1->prepare();

	c1->boot();
	EXPECT_THROW({ c1->boot(); }, harpoon::exception::wrong_state);
	EXPECT_TRUE(c1->is_running());
	EXPECT_TRUE(c1->is_prepared());
}

TEST(hardware_component, boot_chain) {
	hcp c1(new hc("hw-component1"));
	mocks::hcp c2(new ::testing::NiceMock<mocks::hc>("hw-component2"));
	mocks::hcp c3(new ::testing::NiceMock<mocks::hc>("hw-component3"));
	mocks::hcp c4(new ::testing::NiceMock<mocks::hc>("hw-component4"));

	c1->add_component(c2);
	c2->add_component(c3);
	c3->add_component(c4);

	c1->prepare();

	EXPECT_CALL(*c2, boot()).Times(1);
	EXPECT_CALL(*c3, boot()).Times(1);
	EXPECT_CALL(*c4, boot()).Times(1);
	c1->boot();

	EXPECT_TRUE(c1->is_prepared());
	EXPECT_TRUE(c2->is_prepared());
	EXPECT_TRUE(c3->is_prepared());
	EXPECT_TRUE(c4->is_prepared());
	EXPECT_TRUE(c1->is_running());
	EXPECT_TRUE(c2->is_running());
	EXPECT_TRUE(c3->is_running());
	EXPECT_TRUE(c4->is_running());
}

TEST(hardware_component, shutdown) {
	hcp c1(new hc("hw-component1"));

	c1->prepare();
	c1->boot();
	c1->shutdown();
	EXPECT_TRUE(c1->is_prepared());
	EXPECT_FALSE(c1->is_running());
}

TEST(hardware_component, shutdown_not_running) {
	hcp c1(new hc("hw-component1"));

	EXPECT_THROW({ c1->shutdown(); }, harpoon::exception::wrong_state);
	EXPECT_FALSE(c1->is_prepared());
	EXPECT_FALSE(c1->is_running());

	c1->prepare();
	EXPECT_THROW({ c1->shutdown(); }, harpoon::exception::wrong_state);
	EXPECT_TRUE(c1->is_prepared());
	EXPECT_FALSE(c1->is_running());
}

TEST(hardware_component, shutdown_chain) {
	hcp c1(new hc("hw-component1"));
	mocks::hcp c2(new ::testing::NiceMock<mocks::hc>("hw-component2"));
	mocks::hcp c3(new ::testing::NiceMock<mocks::hc>("hw-component3"));
	mocks::hcp c4(new ::testing::NiceMock<mocks::hc>("hw-component4"));

	c1->add_component(c2);
	c2->add_component(c3);
	c3->add_component(c4);

	c1->prepare();
	c1->boot();

	EXPECT_CALL(*c2, shutdown()).Times(1);
	EXPECT_CALL(*c3, shutdown()).Times(1);
	EXPECT_CALL(*c4, shutdown()).Times(1);
	c1->shutdown();

	EXPECT_TRUE(c1->is_prepared());
	EXPECT_TRUE(c2->is_prepared());
	EXPECT_TRUE(c3->is_prepared());
	EXPECT_TRUE(c4->is_prepared());
	EXPECT_FALSE(c1->is_running());
	EXPECT_FALSE(c2->is_running());
	EXPECT_FALSE(c3->is_running());
	EXPECT_FALSE(c4->is_running());
}

TEST(hardware_component, cleanup) {
	hcp c1(new hc("hw-component1"));

	c1->prepare();
	c1->boot();
	c1->shutdown();
	c1->cleanup();
	EXPECT_FALSE(c1->is_prepared());
	EXPECT_FALSE(c1->is_running());
}

TEST(hardware_component, cleanup_after_prep) {
	hcp c1(new hc("hw-component1"));

	c1->prepare();
	c1->cleanup();
	EXPECT_FALSE(c1->is_prepared());
	EXPECT_FALSE(c1->is_running());
}

TEST(hardware_component, cleanup_not_prepared) {
	hcp c1(new hc("hw-component1"));

	EXPECT_THROW({ c1->cleanup(); }, harpoon::exception::wrong_state);
	EXPECT_FALSE(c1->is_prepared());
	EXPECT_FALSE(c1->is_running());
}

TEST(hardware_component, cleanup_running) {
	hcp c1(new hc("hw-component1"));

	c1->prepare();
	c1->boot();
	EXPECT_THROW({ c1->cleanup(); }, harpoon::exception::wrong_state);
	EXPECT_TRUE(c1->is_prepared());
	EXPECT_TRUE(c1->is_running());
}

TEST(hardware_component, cleanup_chain) {
	hcp c1(new hc("hw-component1"));
	mocks::hcp c2(new ::testing::NiceMock<mocks::hc>("hw-component2"));
	mocks::hcp c3(new ::testing::NiceMock<mocks::hc>("hw-component3"));
	mocks::hcp c4(new ::testing::NiceMock<mocks::hc>("hw-component4"));

	c1->add_component(c2);
	c2->add_component(c3);
	c3->add_component(c4);

	c1->prepare();
	c1->boot();
	c1->shutdown();

	EXPECT_CALL(*c2, cleanup()).Times(1);
	EXPECT_CALL(*c3, cleanup()).Times(1);
	EXPECT_CALL(*c4, cleanup()).Times(1);
	c1->cleanup();

	EXPECT_FALSE(c1->is_prepared());
	EXPECT_FALSE(c2->is_prepared());
	EXPECT_FALSE(c3->is_prepared());
	EXPECT_FALSE(c4->is_prepared());
	EXPECT_FALSE(c1->is_running());
	EXPECT_FALSE(c2->is_running());
	EXPECT_FALSE(c3->is_running());
	EXPECT_FALSE(c4->is_running());

	EXPECT_TRUE(c1->has_subcomponent(c2));
	EXPECT_TRUE(c2->has_subcomponent(c3));
	EXPECT_TRUE(c3->has_subcomponent(c4));
}
