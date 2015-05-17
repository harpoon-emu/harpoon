#ifndef SIMPLE_CPU_HH
#define SIMPLE_CPU_HH

#include "harpoon/execution/cpu.hh"

class simple_cpu : public harpoon::execution::cpu {
public:
	using harpoon::execution::cpu::cpu;

	virtual std::uint_fast64_t fetch();
	virtual std::uint_fast64_t execute();

	virtual ~simple_cpu();
};

#endif