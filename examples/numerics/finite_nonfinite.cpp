#include "rapidcheck.h"
#include <vector>
#include <algorithm>

using namespace rc;

int main() {
  rc::check("No special values", []() {
    const auto x = *rc::gen::FiniteReal<double>();
    RC_ASSERT(std::isfinite(x));
  });
  rc::check("Generate some nans", []() {
    // TODO: This test fails after O(30) tests when there are too many
    //       finite numbers in a row.
    constexpr std::size_t array_size = 100;
    std::array<double, array_size> data;
    for (std::size_t i = 0; i < array_size; ++i) {
      data[i] = *rc::gen::arbitrary<double>();
    }
    RC_ASSERT(std::any_of(data.begin(), data.end(), [](const double d) {
      return !std::isfinite(d);
    }));
  });
  // rc::check("special containers", []() {
  //   TODO: Would want all-nan, all-same, … containers, too.
  //   const auto x = *rc::gen::arbitrary<std::vector<double>>();
  // });
  return 0;
}
