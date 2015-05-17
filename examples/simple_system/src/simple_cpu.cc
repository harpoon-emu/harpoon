#include "simple_cpu.hh"

simple_cpu::~simple_cpu() {}

std::uint_fast64_t simple_cpu::fetch() {
	return 1;
}

std::uint_fast64_t simple_cpu::execute() {
	return 4;
}