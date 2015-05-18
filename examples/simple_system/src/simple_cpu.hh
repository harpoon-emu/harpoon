#ifndef SIMPLE_CPU_HH
#define SIMPLE_CPU_HH

#include "harpoon/execution/processing_unit.hh"

class simple_cpu : public harpoon::execution::processing_unit {
public:
	using harpoon::execution::processing_unit::processing_unit;

	virtual std::uint_fast64_t fetch();
	virtual std::uint_fast64_t execute();

	virtual ~simple_cpu();
};

#endif
