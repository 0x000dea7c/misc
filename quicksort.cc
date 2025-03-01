#include <algorithm>
#include <string>
#include <vector>
#include <cassert>

template <typename T>
static int
partition (std::vector<T> &data, int start, int end)
{
  auto const pivot_index = end;
  int p = start - 1;

  for (int i = start; i < end; ++i)
    {
      if (data[i] < data[pivot_index])
        {
          ++p;
          std::swap (data[p], data[i]);
        }
    }
  ++p;
  std::swap (data[p], data[pivot_index]);
  return p;
}

template <typename T>
static void
quicksort (std::vector<T> &data, int start, int end)
{
  if (!(start < end))
    return;

  auto const p = partition (data, start, end);
  quicksort (data, start, p - 1);
  quicksort (data, p + 1, end);
}

template <typename T>
static void
sort (std::vector<T> &data)
{
  quicksort (data, 0, data.size () - 1);
}

int
main ()
{
  using namespace std::string_literals;

  {
    // Base case
    std::vector<int> numbers {
      99, 98, 98, 97, 15
    };
    sort (numbers);
    assert (numbers[0] == 15);
    assert (numbers[1] == 97);
    assert (numbers[2] == 98);
    assert (numbers[3] == 98);
    assert (numbers[4] == 99);
  }

  {
    // Single element
    std::vector<int> numbers {
      1
    };
    sort (numbers);
    assert (numbers[0] == 1);
  }

  {
    // Empty container, doesn't blow up
    std::vector<int> numbers;
    sort (numbers);
    assert (numbers.empty ());
  }

  {
    // Even number of elements
    std::vector<std::string> data{"here", "we", "go", "even", "number", "of", "elements", "here"};
    sort (data);
    assert (data[0] == "elements"s);
    assert (data[1] == "even"s);
    assert (data[2] == "go"s);
    assert (data[3] == "here"s);
    assert (data[4] == "here"s);
    assert (data[5] == "number"s);
    assert (data[6] == "of"s);
    assert (data[7] == "we"s);
  }

  {
    // Odd number of elements.
    std::vector<std::string> data{
      "here", "we", "go", "even", "number", "of", "elements",
    };
    sort (data);
    assert (data[0] == "elements"s);
    assert (data[1] == "even"s);
    assert (data[2] == "go"s);
    assert (data[3] == "here"s);
    assert (data[4] == "number"s);
    assert (data[5] == "of"s);
    assert (data[6] == "we"s);
  }

  return 0;
}
