#include "simple_computer_system.hh"
#include "harpoon/execution/up_execution_unit.hh"
#include "harpoon/execution/cpu.hh"
#include "harpoon/clock/clock.hh"
#include "harpoon/clock/generator/dummy_generator.hh"
#include "harpoon/log/console_log.hh"

#include <memory>
#include <condition_variable>
#include <mutex>
#include <csignal>

using dummy_generator = harpoon::clock::generator::dummy_generator;

static std::condition_variable signal_condition_variable{};
static std::mutex signal_mutex{};

static void signal_handler(int signal) {
	std::unique_lock<std::mutex> lk(signal_mutex);

	signal_condition_variable.notify_all();
}

int main(int argc, char* argv[]) {

	auto console_log = harpoon::log::make_console_log();
	auto computer_system = std::make_shared<simple_computer_system>();
	computer_system->set_log(console_log);

	auto execution_unit = harpoon::execution::make_up_execution_unit("Execution unit");
	computer_system->set_main_execution_unit(execution_unit);

	auto clock = harpoon::clock::make_clock<10, dummy_generator>("Clock#1");
	computer_system->add_component(clock);

	computer_system->prepare();
	computer_system->boot();

	std::unique_lock<std::mutex> lk(signal_mutex);

	signal(SIGINT, signal_handler);

	signal_condition_variable.wait(lk);
	signal(SIGINT, SIG_IGN);

	computer_system->shutdown();
	computer_system->cleanup();
}