#ifndef HARPOON_MEMORY_IO_MEMORY_HH
#define HARPOON_MEMORY_IO_MEMORY_HH

#include "harpoon/harpoon.hh"
#include "harpoon/memory/address_range.hh"
#include "harpoon/memory/exception/write_access_violation.hh"

#include <functional>
#include <map>

namespace harpoon {
namespace memory {

template<typename MemoryImplementation>
class io_memory : public MemoryImplementation {
public:

	class port {
	public:
		using in_handler = std::function<void(const address& address, std::uint8_t& value)>;
		using out_handler = std::function<void(const address& address, std::uint8_t value)>;

		const in_handler pt_in_handler = [](const address&, std::uint8_t&) {};
		const out_handler pt_out_handler = [](const address&, std::uint8_t) {};

		port(const in_handler& in_handler, const out_handler& out_handler) {
			_in_handler = in_handler;
			_out_handler = out_handler;
		}

		port(const port& source) = default;
		port& operator=(const port& source) = default;

		void in(const address& address, std::uint8_t& value) const {
			_in_handler(address, value);
		}

		void out(const address& address, std::uint8_t value) const {
			_out_handler(address, value);
		}

	protected:
		in_handler _in_handler{};
		out_handler _out_handler{};
	};

	class in_port : public port {
	public:
		in_port(const typename port::in_handler& in_handler) 
		: port(in_handler, [](const address& address, std::uint8_t value) { (void)address; (void)value; }) {}
	};

	class out_port : public port {
	public:
		out_port(const typename port::out_handler& out_handler) 
		: port([](const address& address, std::uint8_t value) { (void)address; (void)value; }, out_handler) {}
	};

	using MemoryImplementation::MemoryImplementation;

	void add_port(const address& address, const typename port::in_handler& in_handler, const typename port::out_handler& out_handler) {
		_ports.insert({address, port(in_handler, out_handler)});
	}
	void add_in_port(const address& address, const typename port::in_handler& in_handler) {
		_ports.insert({address, in_port(in_handler)});
	}
	void add_out_port(const address& address, const typename port::out_handler& out_handler) {
		_ports.insert({address, out_port(out_handler)});
	}

	virtual ~io_memory() override {}

protected:

	virtual void get_cell(address address, std::uint8_t& value) override {
		MemoryImplementation::get_cell(address, value);
		if (_ports.find(address) != _ports.end()) {
			_ports.at(address).in(address, value);
		}
	}

	virtual void set_cell(address address, std::uint8_t value) override {
		MemoryImplementation::set_cell(address, value);
		if (_ports.find(address) != _ports.end()) {
			_ports.at(address).out(address, value);
		}
	}


private:
	std::map<address, port> _ports{};
};

template<typename MemoryImplementation>
using io_memory_ptr = std::shared_ptr<io_memory<MemoryImplementation>>;

template<typename MemoryImplementation>
using io_memory_weak_ptr = std::weak_ptr<io_memory<MemoryImplementation>>;

template<typename MemoryImplementation, typename... Args>
io_memory_ptr<MemoryImplementation> make_io_memory(Args&&... args) {
	return std::make_shared<io_memory<MemoryImplementation>>(std::forward<Args>(args)...);
}

}
}

#endif

