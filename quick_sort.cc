#include <algorithm>
#include <string>
#include <vector>
#include <cassert>
#include <concepts>

template <typename T>
concept less_comparable = requires (T a, T b)
{
  {a < b} -> std::convertible_to<bool>;
};

template <less_comparable T>
static int
median_of_three (std::vector<T> &data, int start, int end)
{
  int mid {start + ((end - start) >> 1)};

  if (data[mid] < data[start])
    std::swap (data[mid], data[start]);

  if (data[end] < data[start])
    std::swap (data[end], data[start]);

  if (data[end] < data[mid])
    std::swap (data[end], data[mid]);

  return mid;
}

template <less_comparable T>
static int
partition (std::vector<T> &data, int start, int end)
{
  int pivot_index {median_of_three (data, start, end)};
  T const pivot {data[pivot_index]};
  std::swap (data[pivot_index], data[end]);
  int p {start - 1};

  for (int i {start}; i < end; ++i)
    {
      if (data[i] < pivot)
        {
          ++p;
          std::swap (data[i], data[p]);
        }
    }

  ++p;
  std::swap (data[end], data[p]);
  return p;
}

template <less_comparable T>
static void
quicksort (std::vector<T> &data, int start, int end)
{
  if (!(start < end))
    return;

  int p {partition (data, start, end)};
  quicksort (data, start, p - 1);
  quicksort (data, p + 1, end);
}

template <less_comparable T>
static void
sort (std::vector<T> &data)
{
  quicksort (data, 0, data.size () - 1);
}

struct dummy
{
  int a;
};

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
    std::vector<std::string> data {"here", "we", "go", "even", "number", "of", "elements", "here"};
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
    std::vector<std::string> data {
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

  {
    // this blows up because this struct doesn't implement
    // the < operator
    // std::vector<dummy> data;
    // sort (data);
  }

  return 0;
}
