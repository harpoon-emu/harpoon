#ifndef HARPOON_MEMORY_ADDRESS_RANGE_HH
#define HARPOON_MEMORY_ADDRESS_RANGE_HH

#include "harpoon/harpoon.hh"

#include "harpoon/memory/address.hh"

#include <iomanip>
#include <limits>

namespace harpoon {
namespace memory {

class address_range {
public:
	address_range() {}
	address_range(const address &start, const address &end) : _start(start), _end(end) {}
	address_range(const address_range &) = default;
	address_range &operator=(const address_range &) = default;

	bool operator==(const address_range &second) const {
		return get_start() == second.get_start() && get_end() == second.get_end();
	}

	address get_start() const {
		return _start;
	}

	void set_start(address start) {
		_start = start;
	}

	address get_end() const {
		return _end;
	}

	void set_end(address end) {
		_end = end;
	}

	std::uint_fast64_t get_length() const {
		return _end - _start + 1;
	}

	void set_length(std::uint_fast64_t length) {
		_end = _start + length - 1;
	}

	void set_range(address start, address end) {
		set_start(start);
		set_end(end);
	}

	void set_start_and_length(address start, std::uint_fast64_t length) {
		set_start(start);
		set_length(length);
	}

	bool has_address(address address) const {
		return address >= get_start() && address <= get_end();
	}

	address get_offset(address address) const {
		return address - get_start();
	}

	bool overlaps(const address_range &second) const {
		return has_address(second.get_start()) || has_address(second.get_end());
	}

	static inline address max() {
		return std::numeric_limits<address>::max();
	}

	friend std::ostream &operator<<(std::ostream &stream, const address_range &range) {
		std::ostream out(stream.rdbuf());
		out << "[";
		out << std::hex << std::setw(sizeof(address) * 2) << std::uppercase << std::setfill('0')
		    << range._start;
		out << ", ";
		out << std::hex << std::setw(sizeof(address) * 2) << std::uppercase << std::setfill('0')
		    << range._end;
		out << "]";
		return stream;
	}

private:
	address _start{};
	address _end{};
};

} // namespace memory
} // namespace harpoon

#endif
