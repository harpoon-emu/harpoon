#include "simple_computer_system.hh"
#include "simple_cpu.hh"

#include "harpoon/log/console_log.hh"
#include "harpoon/clock/clock.hh"
#include "harpoon/clock/generator/threaded_generator.hh"
#include "harpoon/execution/up_execution_unit.hh"

#include <memory>
#include <condition_variable>
#include <mutex>
#include <csignal>

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

	auto clock = harpoon::clock::make_clock(
		std::static_pointer_cast<harpoon::clock::generator::generator>(
			harpoon::clock::generator::make_threaded_generator(1000)), "Clock#1");
	execution_unit->set_clock(clock);

	auto cpu = std::make_shared<simple_cpu>("CPU#0");
	execution_unit->set_cpu(cpu);

	computer_system->prepare();
	computer_system->boot();

	std::unique_lock<std::mutex> lk(signal_mutex);

	signal(SIGINT, signal_handler);

	signal_condition_variable.wait(lk);
	signal(SIGINT, SIG_IGN);

	computer_system->shutdown();
	computer_system->cleanup();
}