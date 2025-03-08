// Check permutation: given two strings, write a method to decide
// if one is a permutation of the other
#include <cassert>
#include <string>

static bool
is_permutation (std::string &current, std::string const &target, int start, int end)
{
  // it's case sensitive
  if (start == end)
    {
      if (current == target)
        return true;
      else
        return false;
    }

  for (size_t i {start}; i <= end; ++i)
    {
      std::swap (current[i], current[start]);

      if (is_permutation (current, target, start + 1, end))
        return true;

      std::swap (current[i], current[start]);
    }

  return false;
}

bool
is_permutation (std::string const &src, std::string const &dst)
{
  // O(n * n!) runtime complexity
  if (src.empty () && !dst.empty())
    return false;
  else if (!src.empty () && dst.empty())
    return false;
  else if (src.empty () && dst.empty ()) // ambiguous
    return true;
  else if (src.length () != dst.length ())
    return false;

  std::string start_str {src};
  return is_permutation (start_str, dst, 0, start_str.length () - 1);
}

int
main ()
{
  {
    std::string source {"lain"}, target {"ainl"};
    assert (is_permutation (source, target));
  }

  {
    std::string source {""}, target {"random"};
    assert (!is_permutation (source, target));
  }

  {
    std::string source {"abc"}, target {""};
    assert (!is_permutation (source, target));
  }

  {
    std::string source {""}, target {""};
    assert (is_permutation (source, target));
  }

  {
    std::string source {"despera"}, target {"erapdes"};
    assert (is_permutation (source, target));
  }

  {
    std::string source {"permutation"}, target {"permutation"};
    assert (is_permutation (source, target));
  }

  {
    std::string source {"aabbcc"}, target {"abcabc"};
    assert (is_permutation (source, target));
  }

  {
    std::string source {"abcde"}, target {"abcdf"};
    assert (!is_permutation (source, target));
  }

  {
    std::string source {"Abc"}, target {"abc"};
    assert (!is_permutation (source, target));
  }

  return 0;
}
