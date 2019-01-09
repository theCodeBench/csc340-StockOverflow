#include "../catch.hpp"
#include "../../src/Market/Market.h"

TEST_CASE("Market Initialize Market")
{
    DataProvider dataProvider;
    Market market(dataProvider);
}
