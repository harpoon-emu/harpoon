#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <harpoon/computer_system.hh>
#include <harpoon/execution/execution_unit.hh>
#include <harpoon/memory/main_memory.hh>

using cs = harpoon::computer_system;
using csp = harpoon::computer_system_ptr;

namespace mocks {
class execution_unit : public harpoon::execution::execution_unit {
public:
	using harpoon::execution::execution_unit::execution_unit;

	MOCK_METHOD(void, enable_disassemble, (), (override));
	MOCK_METHOD(void, disable_disassemble, (), (override));

	MOCK_METHOD(void, step, (harpoon::hardware_component * trigger), (override));
};

using execution_unit_ptr = std::shared_ptr<execution_unit>;

class main_memory : public harpoon::memory::main_memory {
public:
	using harpoon::memory::main_memory::main_memory;
};

using main_memory_ptr = std::shared_ptr<main_memory>;

} // namespace mocks

TEST(computer_system, constructor) {
	cs c("computer-system");

	EXPECT_FALSE(c.is_prepared());
	EXPECT_FALSE(c.is_running());
	EXPECT_EQ(c.get_name(), "computer-system");
}

TEST(computer_system, main_execution_unit) {
	csp p(new cs("computer-system"));
	mocks::execution_unit_ptr eu(new mocks::execution_unit("execution-unit"));

	p->set_main_execution_unit(eu);
	EXPECT_EQ(p->get_main_execution_unit(), eu);
	EXPECT_TRUE(p->has_subcomponent(eu));
}

TEST(computer_system, main_execution_unit_replace) {
	csp p(new cs("computer-system"));
	mocks::execution_unit_ptr eu1(new mocks::execution_unit("execution-unit1"));
	mocks::execution_unit_ptr eu2(new mocks::execution_unit("execution-unit2"));

	p->set_main_execution_unit(eu1);
	p->set_main_execution_unit(eu2);
	EXPECT_EQ(p->get_main_execution_unit(), eu2);
	EXPECT_TRUE(p->has_subcomponent(eu2));
	EXPECT_FALSE(p->has_subcomponent(eu1));
}

TEST(computer_system, main_memory) {
	csp p(new cs("computer-system"));
	mocks::main_memory_ptr mm(new mocks::main_memory("main-memory"));

	p->set_main_memory(mm);
	EXPECT_EQ(p->get_main_memory(), mm);
	EXPECT_TRUE(p->has_subcomponent(mm));
}

TEST(computer_system, main_memory_replace) {
	csp p(new cs("computer-system"));
	mocks::main_memory_ptr mm1(new mocks::main_memory("main-memory1"));
	mocks::main_memory_ptr mm2(new mocks::main_memory("main-memory2"));

	p->set_main_memory(mm1);
	p->set_main_memory(mm2);
	EXPECT_EQ(p->get_main_memory(), mm2);
	EXPECT_TRUE(p->has_subcomponent(mm2));
	EXPECT_FALSE(p->has_subcomponent(mm1));
}

TEST(computer_system, step) {
	csp p(new cs("computer-system"));
	mocks::execution_unit_ptr eu(new mocks::execution_unit("execution-unit"));

	p->set_main_execution_unit(eu);

	EXPECT_CALL(*eu, step(p.get())).Times(1);

	p->step(NULL);
}

TEST(computer_system, run) {
	csp p(new cs("computer-system"));
	mocks::execution_unit_ptr eu(new mocks::execution_unit("execution-unit"));

	p->set_main_execution_unit(eu);

	EXPECT_CALL(*eu, step(p.get()))
	    .Times(3)
	    .WillOnce([](harpoon::hardware_component *p) {})
	    .WillOnce([](harpoon::hardware_component *p) {})
	    .WillOnce([this](harpoon::hardware_component *p) { p->shutdown(); });

	p->prepare();
	p->boot();
	p->run();
	EXPECT_FALSE(p->is_running());
}
