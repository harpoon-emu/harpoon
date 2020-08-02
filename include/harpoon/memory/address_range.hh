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
	constexpr address_range() {
		set_start_and_length(0, 0);
	}

	constexpr address_range(const address &start, const address &end) {
		set_range(start, end);
	}

	address_range(const address_range &) = default;
	address_range &operator=(const address_range &) = default;

	constexpr bool operator==(const address_range &second) const {
		return get_start() == second.get_start() && get_end() == second.get_end();
	}

	constexpr bool operator!=(const address_range &second) const {
		return get_start() != second.get_start() || get_end() != second.get_end();
	}

	constexpr operator bool() const {
		return !is_empty();
	}

	constexpr bool is_empty() const {
		return _start == _end;
	}

	constexpr address get_start() const {
		return _start;
	}

	constexpr void set_start(address start) {
		_start = start;
		_normalize();
	}

	constexpr address get_end() const {
		return _end - 1;
	}

	constexpr void set_end(address end) {
		_end = end + 1;
		_normalize();
	}

	constexpr std::uint_fast64_t get_length() const {
		return _end - _start;
	}

	constexpr void set_length(std::uint_fast64_t length) {
		_end = _start + length;
	}

	constexpr void set_range(address start, address end) {
		_start = start;
		_end = end + 1;
		_normalize();
	}

	constexpr void set_start_and_length(address start, std::uint_fast64_t length) {
		_start = start;
		set_length(length);
	}

	constexpr bool has_address(address address) const {
		return address >= get_start() && address <= get_end();
	}

	constexpr address get_offset(address address) const {
		return address - get_start();
	}

	constexpr bool overlaps(const address_range &second) const {
		return get_start() <= second.get_end() && get_end() >= second.get_start();
	}

	constexpr address_range get_intersection(const address_range &r) const {
		address_range n = r;
		n.intersect(*this);
		return n;
	}

	constexpr void intersect(const address_range &r) {
		address s = std::max(_start, r._start);
		address e = std::min(_end, r._end);
		if (e < s) {
			e = s = 0;
		}
		_start = s;
		_end = e;
	}

	static constexpr address max() {
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
	constexpr void _normalize() {
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
