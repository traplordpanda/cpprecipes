#include <boost/hana.hpp>
#include <boost/json.hpp>
#include <cstdint>
#include <fmt/core.h>
#include <iostream>

namespace hana = boost::hana;

// Convert the struct to a boost::json::object

// Define a struct with Hana introspection capabilities
struct Person {
  BOOST_HANA_DEFINE_STRUCT(Person, (std::uint32_t, weight),
                           (std::uint32_t, age), (std::uint32_t, height));
};

boost::json::object to_json(const Person &person) {
  boost::json::object j;

  hana::for_each(hana::keys(person), [&](auto key) {
    // Use the key as the name of the member
    auto name = hana::to<char const *>(key);

    // Add each member to the json object
    j[name] = hana::at_key(person, key);
  });

  return j;
}

int main() {
  Person john;
  john.weight = 500500;
  john.age = 25;
  john.height = 62;

  // Iterate over each member and print the name and value
  hana::for_each(hana::keys(john), [&](auto key) {
    fmt::print("key : {}\tvalue: {}\n", hana::to<char const *>(key),
               hana::at_key(john, key));
  });
  auto j = to_json(john);
  std::string json_str = boost::json::serialize(j);

  fmt::print("json repr {}\n", json_str);
  fmt::print("size of person struct {}\n", sizeof(john));

  return 0;
}
