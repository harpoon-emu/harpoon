#ifndef HARPOON_MEMORY_ADDRESS_RANGE_HH
#define HARPOON_MEMORY_ADDRESS_RANGE_HH

#include "harpoon/harpoon.hh"

#include "harpoon/memory/address.hh"

#include <iomanip>
#include <iostream>
#include <limits>

namespace harpoon {
namespace memory {

/*
 * Internally _end is the address of next byte after memory range
 * Valid addresses in range are [_start, _end-1]
 */
class address_range {
public:
	address_range() {
		set_range(0, 0);
	}

	address_range(const address &start, const address &end) {
		set_range(start, end);
	}

	address_range(const address_range &) = default;
	address_range &operator=(const address_range &) = default;

	bool operator==(const address_range &second) const {
		return get_start() == second.get_start() && get_end() == second.get_end();
	}

	bool operator!=(const address_range &second) const {
		return get_start() != second.get_start() || get_end() != second.get_end();
	}

	operator bool() const {
		return !is_empty();
	}

	bool is_empty() const {
		return _start == _end;
	}

	address get_start() const {
		return _start;
	}

	void set_start(address start) {
		_start = start;
		_normalize();
	}

	address get_end() const {
		return _end - 1;
	}

	void set_end(address end) {
		_end = end + 1;
		_normalize();
	}

	std::uint_fast64_t get_length() const {
		return _end - _start;
	}

	void set_length(std::uint_fast64_t length) {
		_end = _start + length;
	}

	void set_range(address start, address end) {
		_start = start;
		_end = end + 1;
		_normalize();
	}

	void set_start_and_length(address start, std::uint_fast64_t length) {
		_start = start;
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

	address_range get_intersection(const address_range &r) const {
		address_range n = r;
		n.intersect(*this);
		return n;
	}

	void intersect(const address_range &r) {
		address s = std::max(_start, r._start);
		address e = std::min(_end, r._end);
		if (e < s) {
			e = s = 0;
		}
		_start = s;
		_end = e;
	}

	static inline address max() {
		return std::numeric_limits<address>::max();
	}

	friend std::ostream &operator<<(std::ostream &stream, const address_range &range) {
		std::ostream out(stream.rdbuf());
		out << "[";
		if (range.is_empty()) {
			out << "empty";
		} else {
			out << std::hex << std::setw(sizeof(address) * 2) << std::uppercase << std::setfill('0')
			    << range._start;
			out << ", ";
			out << std::hex << std::setw(sizeof(address) * 2) << std::uppercase << std::setfill('0')
			    << range._end - 1;
		}
		out << "]";
		return stream;
	}

private:
	void _normalize() {
		if (_start > _end - 1) {
			address t = _start;
			_start = _end - 1;
			_end = t + 1;
		}
	}
	address _start{};
	address _end{};
};

} // namespace memory
} // namespace harpoon

#endif
