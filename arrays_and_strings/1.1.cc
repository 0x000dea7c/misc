// Implement an algorithm to determine if a string has all unique
// characters. What if you cannot use additional data structures?

// Assume we're working in the English alphabet and we're case sensitive
#include <cstdint>
#include <cassert>
#include <string>

#define ARRAY_COUNT(a) sizeof(a) / sizeof(a[0])

struct test_entry
{
  std::string value;
  bool expected;
};

static bool
is_unique (std::string const &str)
{
  // O(n) runtime, O(1) space
  auto const n = str.length ();
  std::uint32_t lowercase_alphabet {0};
  std::uint32_t uppercase_alphabet {0};

  for (std::size_t i {0}; i < n; ++i)
    {
      auto character = str[i];

      if (character >= 65 && character <= 90)
        {
          character -= 'A';

          if ((uppercase_alphabet & (1 << character)) != 0)
            return false;

          uppercase_alphabet |= (1 << character);
        }
      else if (character >= 97 && character <= 122)
        {
          character -= 'a';

          if ((lowercase_alphabet & (1 << character)) != 0)
            return false;

          lowercase_alphabet |= (1 << character);
        }
    }

  return true;
}

int
main ()
{
  test_entry entries[] =
    {
      {"lain", true},
      {"lainn", false},
      {"", true},
      {"heather", false},
      {"weather", false},
      {"germany", true},
      {"qwertyuiopasdfghjklzxcvbnm", true},
      {"qwertyuiopasdfghjklzxcvbnmz", false},
      {"Lainl", true},
      {"@abc@", true}, // we ignore garbage characters, feature not a bug
    };

  for (std::size_t i {0}; i < ARRAY_COUNT (entries); ++i)
    assert (is_unique (entries[i].value) == entries[i].expected);

  return 0;
}
