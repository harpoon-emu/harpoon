#include <gtest/gtest.h>
#include <harpoon/memory/address_range.hh>

#define START_ADDRESS 0x1000
#define END_ADDRESS 0x3550
#define LENGTH 0x5481

using ar = harpoon::memory::address_range;

std::vector<std::pair<ar, ar>> intersect_tests
    = {{ar(START_ADDRESS, END_ADDRESS), ar(START_ADDRESS, END_ADDRESS)},

       {ar(START_ADDRESS, END_ADDRESS), ar(START_ADDRESS, END_ADDRESS)},
       {ar(START_ADDRESS, END_ADDRESS + 1), ar(START_ADDRESS, END_ADDRESS)},
       {ar(START_ADDRESS, END_ADDRESS - 1), ar(START_ADDRESS, END_ADDRESS - 1)},
       {ar(START_ADDRESS + 1, END_ADDRESS), ar(START_ADDRESS + 1, END_ADDRESS)},
       {ar(START_ADDRESS + 1, END_ADDRESS + 1), ar(START_ADDRESS + 1, END_ADDRESS)},
       {ar(START_ADDRESS + 1, END_ADDRESS - 1), ar(START_ADDRESS + 1, END_ADDRESS - 1)},

       {ar(START_ADDRESS - 1, END_ADDRESS), ar(START_ADDRESS, END_ADDRESS)},
       {ar(START_ADDRESS - 1, END_ADDRESS + 1), ar(START_ADDRESS, END_ADDRESS)},
       {ar(START_ADDRESS - 1, END_ADDRESS - 1), ar(START_ADDRESS, END_ADDRESS - 1)},

       {ar(START_ADDRESS, START_ADDRESS), ar(START_ADDRESS, START_ADDRESS)},
       {ar(START_ADDRESS, START_ADDRESS + 1), ar(START_ADDRESS, START_ADDRESS + 1)},

       {ar(START_ADDRESS - 1, START_ADDRESS), ar(START_ADDRESS, START_ADDRESS)},
       {ar(START_ADDRESS - 1, START_ADDRESS + 1), ar(START_ADDRESS, START_ADDRESS + 1)},

       {ar(END_ADDRESS, END_ADDRESS), ar(END_ADDRESS, END_ADDRESS)},
       {ar(END_ADDRESS, END_ADDRESS + 1), ar(END_ADDRESS, END_ADDRESS)},

       {ar(END_ADDRESS - 1, END_ADDRESS), ar(END_ADDRESS - 1, END_ADDRESS)},
       {ar(END_ADDRESS - 1, END_ADDRESS + 1), ar(END_ADDRESS - 1, END_ADDRESS)},
       {ar(END_ADDRESS - 1, END_ADDRESS - 1), ar(END_ADDRESS - 1, END_ADDRESS - 1)}};


std::vector<ar> intersect_out_tests
    = {ar(START_ADDRESS - 2, START_ADDRESS - 1), ar(END_ADDRESS + 1, END_ADDRESS + 2)};

std::vector<std::pair<ar, ar>> intersect_1_tests
    = {{ar(START_ADDRESS, START_ADDRESS), ar(START_ADDRESS, START_ADDRESS)},
       {ar(START_ADDRESS, START_ADDRESS + 1), ar(START_ADDRESS, START_ADDRESS)},

       {ar(START_ADDRESS - 1, START_ADDRESS), ar(START_ADDRESS, START_ADDRESS)},
       {ar(START_ADDRESS - 1, START_ADDRESS + 1), ar(START_ADDRESS, START_ADDRESS)}

};

std::vector<ar> intersect_0_tests
    = {ar(START_ADDRESS, START_ADDRESS),         ar(START_ADDRESS, START_ADDRESS + 1),
       ar(START_ADDRESS - 1, START_ADDRESS),     ar(START_ADDRESS - 1, START_ADDRESS + 1),
       ar(START_ADDRESS - 1, START_ADDRESS - 1), ar(START_ADDRESS + 1, START_ADDRESS + 1)};

TEST(address_range, constructor_empty) {
	harpoon::memory::address_range a;

	EXPECT_TRUE(a.is_empty());
}

TEST(address_range, constructor_range) {
	harpoon::memory::address_range r(START_ADDRESS, END_ADDRESS);

	EXPECT_EQ(r.get_start(), START_ADDRESS);
	EXPECT_EQ(r.get_end(), END_ADDRESS);
}

TEST(address_range, constructor_range_normalize) {
	harpoon::memory::address_range r(END_ADDRESS, START_ADDRESS);

	EXPECT_EQ(r.get_start(), START_ADDRESS);
	EXPECT_EQ(r.get_end(), END_ADDRESS);
}

TEST(address_range, constructor_copy) {
	harpoon::memory::address_range r(START_ADDRESS, END_ADDRESS);
	harpoon::memory::address_range c(r);

	EXPECT_EQ(r.get_start(), c.get_start());
	EXPECT_EQ(r.get_end(), c.get_end());
}

TEST(address_range, assignment) {
	harpoon::memory::address_range r(START_ADDRESS, END_ADDRESS);
	harpoon::memory::address_range c = r;

	EXPECT_EQ(r.get_start(), c.get_start());
	EXPECT_EQ(r.get_end(), c.get_end());
}

TEST(address_range, equal) {
	harpoon::memory::address_range r(START_ADDRESS, END_ADDRESS);
	harpoon::memory::address_range c = r;

	EXPECT_TRUE(r == c);
}

TEST(address_range, not_equal) {
	harpoon::memory::address_range r(START_ADDRESS, END_ADDRESS);
	harpoon::memory::address_range c;

	EXPECT_TRUE(r != c);
}

TEST(address_range, setters) {
	harpoon::memory::address_range r(START_ADDRESS, END_ADDRESS);

	r.set_start(START_ADDRESS + 1);
	EXPECT_EQ(r.get_start(), START_ADDRESS + 1);
	EXPECT_EQ(r.get_end(), END_ADDRESS);

	r.set_end(END_ADDRESS + 2);
	EXPECT_EQ(r.get_start(), START_ADDRESS + 1);
	EXPECT_EQ(r.get_end(), END_ADDRESS + 2);
}

TEST(address_range, setters_set_end_normalize) {
	harpoon::memory::address_range r(START_ADDRESS, START_ADDRESS);

	r.set_end(START_ADDRESS - 1);
	EXPECT_EQ(r.get_start(), START_ADDRESS - 1);
	EXPECT_EQ(r.get_end(), START_ADDRESS);
}

TEST(address_range, setters_set_start_normalize) {
	harpoon::memory::address_range r(START_ADDRESS, START_ADDRESS);

	r.set_start(START_ADDRESS + 1);
	EXPECT_EQ(r.get_start(), START_ADDRESS);
	EXPECT_EQ(r.get_end(), START_ADDRESS + 1);
}

TEST(address_range, get_length) {
	harpoon::memory::address_range r(START_ADDRESS, END_ADDRESS);

	EXPECT_EQ(r.get_length(), END_ADDRESS - START_ADDRESS + 1);
}

TEST(address_range, get_length_1) {
	harpoon::memory::address_range r(START_ADDRESS, START_ADDRESS);

	EXPECT_EQ(r.get_length(), 1);
}

TEST(address_range, set_length) {
	harpoon::memory::address_range r(START_ADDRESS, END_ADDRESS);

	r.set_length(LENGTH);
	EXPECT_EQ(r.get_length(), LENGTH);
	EXPECT_EQ(r.get_start(), START_ADDRESS);
	EXPECT_EQ(r.get_end(), START_ADDRESS + LENGTH - 1);
}

TEST(address_range, set_length_1) {
	harpoon::memory::address_range r(START_ADDRESS, END_ADDRESS);

	r.set_length(1);
	EXPECT_EQ(r.get_length(), 1);
	EXPECT_EQ(r.get_start(), START_ADDRESS);
	EXPECT_EQ(r.get_end(), START_ADDRESS);
}

TEST(address_range, set_length_0) {
	harpoon::memory::address_range r(START_ADDRESS, END_ADDRESS);

	r.set_length(0);
	EXPECT_EQ(r.get_length(), 0);
	EXPECT_TRUE(r.is_empty());
}

TEST(address_range, set_range) {
	harpoon::memory::address_range r;

	r.set_range(START_ADDRESS, END_ADDRESS);
	EXPECT_EQ(r.get_start(), START_ADDRESS);
	EXPECT_EQ(r.get_end(), END_ADDRESS);
	EXPECT_EQ(r.get_length(), END_ADDRESS - START_ADDRESS + 1);
}

TEST(address_range, set_range_1) {
	harpoon::memory::address_range r;

	r.set_range(START_ADDRESS, START_ADDRESS);
	EXPECT_EQ(r.get_start(), START_ADDRESS);
	EXPECT_EQ(r.get_end(), START_ADDRESS);
	EXPECT_EQ(r.get_length(), 1);
}

TEST(address_range, set_range_normalize) {
	harpoon::memory::address_range r;

	r.set_range(END_ADDRESS, START_ADDRESS);
	EXPECT_EQ(r.get_start(), START_ADDRESS);
	EXPECT_EQ(r.get_end(), END_ADDRESS);
	EXPECT_EQ(r.get_length(), END_ADDRESS - START_ADDRESS + 1);
}

TEST(address_range, set_start_and_length) {
	harpoon::memory::address_range r;

	r.set_start_and_length(START_ADDRESS, LENGTH);
	EXPECT_EQ(r.get_start(), START_ADDRESS);
	EXPECT_EQ(r.get_end(), START_ADDRESS + LENGTH - 1);
	EXPECT_EQ(r.get_length(), LENGTH);
}

TEST(address_range, set_start_and_length_1) {
	harpoon::memory::address_range r;

	r.set_start_and_length(START_ADDRESS, 1);
	EXPECT_EQ(r.get_start(), START_ADDRESS);
	EXPECT_EQ(r.get_end(), START_ADDRESS);
	EXPECT_EQ(r.get_length(), 1);
}

TEST(address_range, set_start_and_length_0) {
	harpoon::memory::address_range r;

	r.set_start_and_length(START_ADDRESS, 0);
	EXPECT_EQ(r.get_length(), 0);
	EXPECT_TRUE(r.is_empty());
}

TEST(address_range, has_address) {
	harpoon::memory::address_range r(START_ADDRESS, END_ADDRESS);

	for (harpoon::memory::address i = START_ADDRESS; i <= END_ADDRESS; i++) {
		EXPECT_TRUE(r.has_address(i));
	}
}

TEST(address_range, has_address_out) {
	harpoon::memory::address_range r(START_ADDRESS, END_ADDRESS);

	EXPECT_FALSE(r.has_address(START_ADDRESS - 1));
	EXPECT_FALSE(r.has_address(END_ADDRESS + 1));
}

TEST(address_range, has_address_1) {
	harpoon::memory::address_range r(START_ADDRESS, START_ADDRESS);

	EXPECT_TRUE(r.has_address(START_ADDRESS));
	EXPECT_FALSE(r.has_address(START_ADDRESS - 1));
	EXPECT_FALSE(r.has_address(START_ADDRESS + 1));
}

TEST(address_range, has_address_0) {
	harpoon::memory::address_range r;

	r.set_start_and_length(START_ADDRESS, 0);
	EXPECT_FALSE(r.has_address(START_ADDRESS));
	EXPECT_FALSE(r.has_address(START_ADDRESS - 1));
	EXPECT_FALSE(r.has_address(START_ADDRESS + 1));
}

TEST(address_range, get_offset) {
	harpoon::memory::address_range r(START_ADDRESS, END_ADDRESS);

	EXPECT_EQ(r.get_offset(START_ADDRESS + 203), 203);
	EXPECT_EQ(r.get_offset(START_ADDRESS), 0);
}

TEST(address_range, overlaps) {
	harpoon::memory::address_range r(START_ADDRESS, END_ADDRESS);

	EXPECT_TRUE(r.overlaps(harpoon::memory::address_range(START_ADDRESS - 1, END_ADDRESS + 1)));
	EXPECT_TRUE(r.overlaps(harpoon::memory::address_range(START_ADDRESS, END_ADDRESS)));
	EXPECT_TRUE(r.overlaps(harpoon::memory::address_range(START_ADDRESS, START_ADDRESS)));
	EXPECT_TRUE(r.overlaps(harpoon::memory::address_range(START_ADDRESS - 1, START_ADDRESS)));
	EXPECT_TRUE(r.overlaps(harpoon::memory::address_range(START_ADDRESS, START_ADDRESS + 1)));
	EXPECT_TRUE(r.overlaps(harpoon::memory::address_range(START_ADDRESS - 1, START_ADDRESS + 1)));
	EXPECT_TRUE(r.overlaps(harpoon::memory::address_range(END_ADDRESS, END_ADDRESS)));
	EXPECT_TRUE(r.overlaps(harpoon::memory::address_range(END_ADDRESS - 1, END_ADDRESS)));
	EXPECT_TRUE(r.overlaps(harpoon::memory::address_range(END_ADDRESS, END_ADDRESS + 1)));
	EXPECT_TRUE(r.overlaps(harpoon::memory::address_range(END_ADDRESS - 1, END_ADDRESS + 1)));
}

TEST(address_range, overlaps_out) {
	harpoon::memory::address_range r(START_ADDRESS, END_ADDRESS);

	EXPECT_FALSE(r.overlaps(harpoon::memory::address_range(START_ADDRESS - 2, START_ADDRESS - 1)));
	EXPECT_FALSE(r.overlaps(harpoon::memory::address_range(END_ADDRESS + 1, END_ADDRESS + 2)));
}

TEST(address_range, overlaps_1) {
	harpoon::memory::address_range r(START_ADDRESS, START_ADDRESS);

	EXPECT_TRUE(r.overlaps(harpoon::memory::address_range(START_ADDRESS, START_ADDRESS)));
	EXPECT_TRUE(r.overlaps(harpoon::memory::address_range(START_ADDRESS - 1, START_ADDRESS)));
	EXPECT_TRUE(r.overlaps(harpoon::memory::address_range(START_ADDRESS, START_ADDRESS + 1)));
	EXPECT_TRUE(r.overlaps(harpoon::memory::address_range(START_ADDRESS - 1, START_ADDRESS + 1)));
}

TEST(address_range, overlaps_1_out) {
	harpoon::memory::address_range r(START_ADDRESS, START_ADDRESS);

	EXPECT_FALSE(r.overlaps(harpoon::memory::address_range(START_ADDRESS - 2, START_ADDRESS - 1)));
	EXPECT_FALSE(r.overlaps(harpoon::memory::address_range(START_ADDRESS + 1, START_ADDRESS + 2)));
}

TEST(address_range, overlaps_0) {
	harpoon::memory::address_range r;

	r.set_start_and_length(START_ADDRESS, 0);

	EXPECT_FALSE(r.overlaps(harpoon::memory::address_range(START_ADDRESS, START_ADDRESS)));
	EXPECT_FALSE(r.overlaps(harpoon::memory::address_range(START_ADDRESS - 1, START_ADDRESS)));
	EXPECT_FALSE(r.overlaps(harpoon::memory::address_range(START_ADDRESS, START_ADDRESS + 1)));
	EXPECT_FALSE(r.overlaps(harpoon::memory::address_range(START_ADDRESS - 1, START_ADDRESS + 1)));
}

TEST(address_range, get_intersection) {
	for (auto i : intersect_tests) {
		ar r(START_ADDRESS, END_ADDRESS);
		EXPECT_EQ(r.get_intersection(i.first), i.second);
	}
}

TEST(address_range, get_intersection_out) {
	for (auto i : intersect_out_tests) {
		ar r(START_ADDRESS, END_ADDRESS);
		EXPECT_TRUE(r.get_intersection(i).is_empty());
	}
}

TEST(address_range, get_intersection_1) {
	for (auto i : intersect_1_tests) {
		ar r(START_ADDRESS, START_ADDRESS);
		EXPECT_EQ(r.get_intersection(i.first), i.second);
	}
}

TEST(address_range, get_intersection_0) {
	for (auto i : intersect_0_tests) {
		ar r;
		r.set_start_and_length(START_ADDRESS, 0);
		EXPECT_TRUE(r.get_intersection(i).is_empty());
	}
}

TEST(address_range, get_intersection_w_0) {
	using ar = harpoon::memory::address_range;
	ar r(START_ADDRESS, END_ADDRESS);
	ar e;

	e.set_start_and_length(START_ADDRESS, 0);

	EXPECT_TRUE(r.get_intersection(e).is_empty());
}

TEST(address_range, intersect) {
	for (auto i : intersect_tests) {
		ar r(START_ADDRESS, END_ADDRESS);
		r.intersect(i.first);
		EXPECT_EQ(r, i.second);
	}
}

TEST(address_range, intersect_out) {
	for (auto i : intersect_out_tests) {
		ar r(START_ADDRESS, END_ADDRESS);
		r.intersect(i);
		EXPECT_TRUE(r.is_empty());
	}
}

TEST(address_range, intersect_1) {
	for (auto i : intersect_1_tests) {
		ar r(START_ADDRESS, START_ADDRESS);
		r.intersect(i.first);
		EXPECT_EQ(r, i.second);
	}
}

TEST(address_range, intersect_0) {
	for (auto i : intersect_0_tests) {
		ar r;
		r.set_start_and_length(START_ADDRESS, 0);
		r.intersect(i);
		EXPECT_TRUE(r.is_empty());
	}
}

TEST(address_range, intersect_w_0) {
	using ar = harpoon::memory::address_range;
	ar r(START_ADDRESS, END_ADDRESS);
	ar e;

	e.set_start_and_length(START_ADDRESS, 0);
	r.intersect(e);
	EXPECT_TRUE(r.is_empty());
}
