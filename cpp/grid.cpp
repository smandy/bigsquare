#include "docopt/docopt.h"
#include "printers.hpp"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

static const char USAGE[] =
    R"(Grid.

    Usage:
      grid [--debug] <filename>

    Options:
      -h --help  Show this screen.
      --debug  Debug output.
)";

using namespace std;

template <typename T> class Grid;

template <typename T> ostream &operator<<(ostream &os, Grid<T> &g);

template <class T, class Enable = void> struct DefaultFor {
  enum { value = 0 };
};

template <class T>
struct DefaultFor<T, typename enable_if<is_same_v<T,uint64_t>>::type > {
  enum { value = 42 };
};


template <class T>
struct DefaultFor<T, typename enable_if<is_same<T, char>::value>::type> {
  enum { value = ' ' };
}; // specialization for char

template <typename T> class Grid {
  vector<T> data;

public:
  const int n;
  bool debug;

  inline int idx(int i, int j) { return i * n + j; };

  Grid(int _n, bool _debug = false, const T &def = DefaultFor<T>::value)
      : data(_n * _n, def), n(_n), debug(_debug) {}

  T &operator[](int i, int j) { return data[idx(i, j)]; }

  tuple<int, int, int> biggest() {
    Grid<uint32_t> yextents(n);
    Grid<uint32_t> xextents(n);
    Grid<uint32_t> sizes(n);

    // cout << yextents << endl;
    // cout << xextents << endl;
    typedef tuple<int, int> Best;
    vector<std::vector<Best>> bests(n + 1);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (operator[](i, j) != ' ') {
          xextents[i, j] = ((j > 0) ? xextents[i, j - 1] : 0) + 1;
          yextents[i, j] = ((i > 0) ? yextents[i - 1, j] : 0) + 1;
          auto sz = min(xextents[i, j], yextents[i, j]);
          sizes[i, j] = sz;
          bests[sz].emplace_back(i, j);
        }
      }
    }

    if (debug) {
      cout << "Y extents" << endl;
      cout << yextents << endl;
      cout << endl << "X extents" << endl;
      cout << xextents;
      cout << endl << "Sizes" << endl;
      cout << sizes << endl;
      cout << "Bests " << endl;
      for_each(begin(bests), end(bests),
               [&](auto &v) { cout << " " << v << endl; });
    }
    auto trySize = n;
    while (true) {
      for (auto it = begin(bests[trySize]); it != end(bests[trySize]); ++it) {
        int y, x;
        std::tie(y, x) = *it;
        auto i = y - trySize + 1;
        auto j = x - trySize + 1;
        if (isSquare(i, j, trySize))
          return make_tuple(i, j, trySize);
      };
      trySize -= 1;
      if (trySize < 1)
        break;
    }
    return {0, 0, 0};
  };

  inline bool isSquare(int i, int j, int sz) {
    for (int y = 0; y < sz; ++y) {
      for (int x = 0; x < sz; ++x) {
        if (operator[](i + y, j + x) == ' ')
          return false;
      };
    }
    return true;
  };
};

Grid<char> parseFile(const string &fn, int sz) {
  Grid<char> ret(9);
  size_t i = 0;
  std::ifstream file(fn);
  if (file.is_open()) {
    cout << "Reading " << fn << endl;
    std::string line;
    while (std::getline(file, line)) {
      if (line.size() != sz + 1)
        continue;
      for (int j = 0; j < line.size() - 1; ++j) {
        ret[i, j] = line[j];
      };
      ++i;
    }
    file.close();
  } else {
    cout << "File not open" << endl;
  };

  return ret;
};

template <typename T> ostream &operator<<(ostream &os, Grid<T> &g) {
  for (int i = 0; i < g.n; ++i) {
    for (int j = 0; j < g.n; ++j) {
        os << g[i, j];
        //      os << (g[i, j] == '\0' ? ' ' : g[i, j]);
    };
    os << std::endl;
  }
  return os;
}

int main(int argc, const char **argv) {
  std::map<std::string, docopt::value> args =
      docopt::docopt(USAGE, {argv + 1, argv + argc},
                     true,       // show help if requested
                     "grid 1.0", // version string
                     true);      // options first
  auto x = parseFile(args["<filename>"].asString(), 9);

  x.debug = args["--debug"].asBool();

  cout << "=======================" << endl;
  cout << x << endl;
  cout << "=======================" << endl;

  int i, j, sz;
  std::tie(i, j, sz) = x.biggest();
  cout << "Biggest size is " << sz << " at (" << i << "," << j << ")" << endl;
}
