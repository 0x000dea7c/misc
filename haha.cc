#include <unistd.h>
#include <chrono>

#define MESSAGE "I like computers"

static void
busy_wait (int ms)
{
  auto start = std::chrono::high_resolution_clock::now ();

  while (std::chrono::high_resolution_clock::now () - start < std::chrono::milliseconds (ms))
    ;
}

template <size_t N>
static constexpr size_t
str_length (char const (&)[N])
{
  return N - 1;
}

int
main (void)
{
  using namespace std::chrono;

  auto constexpr n = str_length (MESSAGE);
  int i {0}, direction {1};

  while (true)
    {
      for (int j {0}; j <= i; ++j)
        {
          write (1, &MESSAGE[j], 1);
          busy_wait (10);
        }

      if (i == n - 1)
        direction = -1;
      else if (i == 0)
        direction = 1;

      i = (i + direction);

      write (1, "\n", 1);
    }

  return 0;
}
