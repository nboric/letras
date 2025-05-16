//
// Created by Neven Boric on 5/16/25.
//

#include <codecvt>

#include "gtest/gtest.h"
#include "../src/dict.h"

class ValidDictTest : public testing::Test
{
protected:
    Dict dict_;

    ValidDictTest()
        : dict_("res/dict/fise-2.txt")
    {
    }
};

TEST_F(ValidDictTest, ExistingSimpleWordIsValid)
{
    EXPECT_TRUE(dict_.is_valid("hola"));
}

TEST_F(ValidDictTest, ExistingWordFromWStringIsValid)
{
    EXPECT_TRUE(dict_.is_valid("niño"));
}

TEST_F(ValidDictTest, NonExistingIsInvalid)
{
    EXPECT_FALSE(dict_.is_valid("noexiste"));
}
