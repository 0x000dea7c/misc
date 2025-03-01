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
static void
merge (std::vector<T> &data, int start, int mid, int end)
{
  auto const n = data.size ();

  // TODO: here
  std::vector<T> left (mid - start + 1);
  std::vector<T> right (end - mid);
  int i {0}, j {0}, k {start};

  while (i < n && j < n)
    {
      if (left[i] < right[j])
        data[k++] = left[i++];
      else
        data[k++] = right[j++];
    }
}

template <less_comparable T>
static void
merge_sort (std::vector<T> &data, int start, int end)
{
  if (!(start < end))
    return;

  int mid {start + ((end - start) >> 1)};
  merge (data, start, mid);
  merge (data, mid + 1, end);
}

template <less_comparable T>
void
sort (std::vector<T> &data)
{
  merge_sort (data);
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
    // Blows up because it doesn't implement < operator
    // std::vector<dummy> data;
    // sort (data);
  }

  return 0;
}
