#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "TupleUtilities.h"
 

TEST_CASE("Test tuple_slice lower", "[Tuple]"){
    auto myTuple=std::make_tuple(1, 2, 3);
    auto myResult=tutilities::tuple_slice<0, 2>(myTuple);
    auto myExpected=std::make_tuple(1, 2);
    REQUIRE(myResult==myExpected);
}
TEST_CASE("Test tuple_slice upper", "[Tuple]"){
    auto myTuple=std::make_tuple(1, 2, 3);
    auto myResult=tutilities::tuple_slice<2, 3>(myTuple);
    auto myExpected=std::make_tuple(3);
    REQUIRE(myResult==myExpected);
}
TEST_CASE("Test apply_tuple", "[Tuple]"){
    auto myFunc=[](const auto& x, const auto& y){
        return x*y;
    };
    REQUIRE(tutilities::apply_tuple(myFunc, std::make_tuple(1, 2))==2);
}
TEST_CASE("Test for_each", "[Tuple]"){
    auto myFunc=[](const auto& x, const auto& y){
        return x*y;
    };
    REQUIRE(tutilities::for_each(std::make_tuple(1, 2), [](const auto& val, const auto& index, const auto& lower, const auto& upper){
        return val;
    })==std::make_tuple(1, 2));
}
