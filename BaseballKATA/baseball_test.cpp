#include "gmock/gmock.h"
#include "baseball.cpp"
using namespace testing;

class BaseballFixture : public testing::Test {
public:
	Baseball game{ "123" };
	void assertIllegalArgument(string guessNumber) {
		try {
			game.guess(string(guessNumber));
			FAIL();
		}
		catch (exception e) {
			// PASS
		}
	}
};

TEST_F(BaseballFixture, ThrowExceptionWhenInvalidCase) {
	assertIllegalArgument("12");
	assertIllegalArgument("12S");
	assertIllegalArgument("121");
}

TEST_F(BaseballFixture, ReturnSolvedResultIfMatchedNumber) {
	GuessResult result = game.guess("123");

	EXPECT_TRUE(result.solved);
	EXPECT_EQ(3, result.strikes);
	EXPECT_EQ(0, result.balls);
}

TEST_F(BaseballFixture, ReturnSolvedResultIfMatchedNumber1) {
	GuessResult result = game.guess("124"); // 2 Strikes, 0 Ball

	EXPECT_FALSE(result.solved);
	EXPECT_EQ(2, result.strikes);
	EXPECT_EQ(0, result.balls);
}

TEST_F(BaseballFixture, ReturnSolvedResultIfMatchedNumber2) {
	GuessResult result = game.guess("321"); // 1 Strikes, 2 Ball

	EXPECT_FALSE(result.solved);
	EXPECT_EQ(1, result.strikes);
	EXPECT_EQ(2, result.balls);
}


int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}