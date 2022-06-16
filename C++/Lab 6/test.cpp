#include "pch.h"
#include "../../Polynomial/polynomial.h"

TEST(polynomial_value, negative_values) {
	Polynomial object;
	EXPECT_EQ(object.value(-2), -23);
	EXPECT_EQ(object.value(-4), -215);
	EXPECT_EQ(object.value(-6), -767);
	EXPECT_EQ(object.value(-8), -1871);
	EXPECT_EQ(object.value(-10), -3719);
	EXPECT_EQ(object.value(-12), -6503);
}

TEST(polynomial_value, zero) {
	Polynomial object;
	EXPECT_EQ(object.value(0), 1);
}

TEST(polynomial_value, positive_numbers) {
	Polynomial object;
	EXPECT_EQ(object.value(1), 10);
	EXPECT_EQ(object.value(3), 142);
	EXPECT_EQ(object.value(7), 1534);
	EXPECT_EQ(object.value(5), 586);
	EXPECT_EQ(object.value(9), 3178);
	EXPECT_EQ(object.value(11), 5710);
}
