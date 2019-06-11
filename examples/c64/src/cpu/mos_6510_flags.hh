#ifndef CPU_MOS_6510_FLAGS_HH
#define CPU_MOS_6510_FLAGS_HH

#include "harpoon/execution/basic_register.hh"

#include <bitset>

namespace commodore {
namespace cpu {

class mos_6510_flags : public harpoon::execution::basic_register<std::bitset<8>> {
public:
	mos_6510_flags() {
		get()[5] = true;
		get()[4] = true;
	}

	std::uint8_t get_flags() const {
		std::uint8_t flags = 0;

		flags |= (N() ? 0x80 : 0x00);
		flags |= (V() ? 0x40 : 0x00);
		flags |= 0x20;
		flags |= (B() ? 0x10 : 0x00);
		flags |= (D() ? 0x08 : 0x00);
		flags |= (I() ? 0x04 : 0x00);
		flags |= (Z() ? 0x02 : 0x00);
		flags |= (C() ? 0x01 : 0x00);

		return flags;
	}

	void set_flags(std::uint8_t flags) {
		N() = ((flags & 0x80) != 0);
		V() = ((flags & 0x40) != 0);
		B() = true;
		D() = ((flags & 0x08) != 0);
		I() = ((flags & 0x04) != 0);
		Z() = ((flags & 0x02) != 0);
		C() = ((flags & 0x01) != 0);
	}

	bool N() const {
		return get()[7];
	}

	std::bitset<8>::reference N() {
		return get()[7];
	}

	bool V() const {
		return get()[6];
	}

	std::bitset<8>::reference V() {
		return get()[6];
	}

	bool B() const {
		return get()[4];
	}

	std::bitset<8>::reference B() {
		return get()[4];
	}

	bool D() const {
		return get()[3];
	}

	std::bitset<8>::reference D() {
		return get()[3];
	}

	bool I() const {
		return get()[2];
	}

	std::bitset<8>::reference I() {
		return get()[2];
	}

	bool Z() const {
		return get()[1];
	}

	std::bitset<8>::reference Z() {
		return get()[1];
	}

	bool C() const {
		return get()[0];
	}

	std::bitset<8>::reference C() {
		return get()[0];
	}
};

} // namespace cpu
} // namespace commodore

#endif
