#ifndef CPU_INSTRUCTIONS_DISASSEMBLER_HH
#define CPU_INSTRUCTIONS_DISASSEMBLER_HH

#include "harpoon/execution/instruction.hh"

#include <array>

namespace c64 {
namespace hw {
namespace cpu {
namespace instructions {
namespace disassembler {

class base {
public:
	base(const std::string &mnemonic, std::uint32_t len) {
		_mnemonic = mnemonic;
		_length = len;
	}
	base(const base &) = default;
	base &operator=(const base &) = default;

	void operator()(const harpoon::execution::instruction &instruction, std::ostream &stream);

	std::uint8_t get_byte(std::size_t idx) const {
		return _bytes[idx + 1];
	}

	virtual ~base();

protected:
	virtual void disassemble(const harpoon::execution::instruction &instruction,
	                         std::ostream &stream)
	    = 0;

	void out_byte_raw(std::ostream &stream, std::uint8_t v);
	void out_byte_hex(std::ostream &stream, std::uint8_t v);
	void out_operand_byte(std::ostream &stream) {
		out_byte_hex(stream, get_byte(0));
	}

	void out_word_raw(std::ostream &stream, std::uint8_t lo, std::uint8_t hi);
	void out_word_hex(std::ostream &stream, std::uint8_t lo, std::uint8_t hi);
	void out_operand_word(std::ostream &stream) {
		out_word_hex(stream, get_byte(0), get_byte(1));
	}

private:
	std::string _mnemonic{};
	std::uint32_t _length{};
	std::array<std::uint8_t, 3> _bytes;
};

class implied : public base {
public:
	implied(const std::string &mnemonic) : base(mnemonic, 1) {}

protected:
	virtual void disassemble(const harpoon::execution::instruction &instruction,
	                         std::ostream &stream);
};

class accumulator : public base {
public:
	accumulator(const std::string &mnemonic) : base(mnemonic, 1) {}

protected:
	virtual void disassemble(const harpoon::execution::instruction &instruction,
	                         std::ostream &stream);
};

class immediate : public base {
public:
	immediate(const std::string &mnemonic) : base(mnemonic, 2) {}

protected:
	virtual void disassemble(const harpoon::execution::instruction &instruction,
	                         std::ostream &stream);
};

class zero_page : public base {
public:
	zero_page(const std::string &mnemonic) : base(mnemonic, 2) {}

protected:
	virtual void disassemble(const harpoon::execution::instruction &instruction,
	                         std::ostream &stream);
};

class zero_page_x : public base {
public:
	zero_page_x(const std::string &mnemonic) : base(mnemonic, 2) {}

protected:
	virtual void disassemble(const harpoon::execution::instruction &instruction,
	                         std::ostream &stream);
};

class zero_page_y : public base {
public:
	zero_page_y(const std::string &mnemonic) : base(mnemonic, 2) {}

protected:
	virtual void disassemble(const harpoon::execution::instruction &instruction,
	                         std::ostream &stream);
};

class absolute : public base {
public:
	absolute(const std::string &mnemonic) : base(mnemonic, 3) {}

protected:
	virtual void disassemble(const harpoon::execution::instruction &instruction,
	                         std::ostream &stream);
};

class absolute_x : public base {
public:
	absolute_x(const std::string &mnemonic) : base(mnemonic, 3) {}

protected:
	virtual void disassemble(const harpoon::execution::instruction &instruction,
	                         std::ostream &stream);
};

class absolute_y : public base {
public:
	absolute_y(const std::string &mnemonic) : base(mnemonic, 3) {}

protected:
	virtual void disassemble(const harpoon::execution::instruction &instruction,
	                         std::ostream &stream);
};

class indirect : public base {
public:
	indirect(const std::string &mnemonic) : base(mnemonic, 3) {}

protected:
	virtual void disassemble(const harpoon::execution::instruction &instruction,
	                         std::ostream &stream);
};

class indirect_x : public base {
public:
	indirect_x(const std::string &mnemonic) : base(mnemonic, 2) {}

protected:
	virtual void disassemble(const harpoon::execution::instruction &instruction,
	                         std::ostream &stream);
};

class indirect_y : public base {
public:
	indirect_y(const std::string &mnemonic) : base(mnemonic, 2) {}

protected:
	virtual void disassemble(const harpoon::execution::instruction &instruction,
	                         std::ostream &stream);
};

class relative : public base {
public:
	relative(const std::string &mnemonic) : base(mnemonic, 2) {}

protected:
	virtual void disassemble(const harpoon::execution::instruction &instruction,
	                         std::ostream &stream);
};


} // namespace disassembler
} // namespace instructions
} // namespace cpu
} // namespace hw
} // namespace c64

#endif
