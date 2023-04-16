#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "printers.hpp"

using namespace std;

template <typename T> class Grid;

template <typename T> ostream &operator<<(ostream &os, Grid<T> &g);

template <typename T> class Grid {
  vector<T> data;

public:
  const int n;

  inline int idx(int i, int j) { return i * n + j; };

  Grid(int _n) : data(_n * _n), n(_n) {
    for (int i = 0; i < n; ++i) {
      // std::cout << data[i] << std::endl;
    };
  }

  T &operator[](int i, int j) { return data[idx(i, j)]; }

  tuple<int, int, int> biggest() {
    Grid<uint32_t> yextents(n);
    Grid<uint32_t> xextents(n);
    Grid<uint32_t> sizes(n);

    // cout << yextents << endl;
    // cout << xextents << endl;
    typedef tuple<int, int> Best;
    std::vector<std::vector<Best>> bests(n + 1);
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

    if (false) {
      cout << "Y extents" << endl;
      cout << yextents << endl;
      cout << endl << "X extents" << endl;
      cout << xextents;
      cout << "Sizes" << endl;
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

template <typename T> ostream &operator<<(ostream &os, Grid<T> &g) {
  for (int i = 0; i < g.n; ++i) {
    for (int j = 0; j < g.n; ++j) {
      os << g[i, j];
    };
    os << std::endl;
  }
  return os;
};

Grid<char> parseFile(string &&fn, int sz) {
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

template <> ostream &operator<<(ostream &os, Grid<char> &g) {
  for (int i = 0; i < g.n; ++i) {
    for (int j = 0; j < g.n; ++j) {
      os << (g[i, j] == '\0' ? ' ' : g[i, j]);
    };
    os << std::endl;
  }
  return os;
}

int main(int argc, char *argv[]) {
  auto x = parseFile(string(argv[1]), 9);

  cout << "=======================" << endl;
  cout << x << endl;
  cout << "=======================" << endl;

  int i,j,sz;
  std::tie(i,j,sz) = x.biggest();
  cout << "Biggest size is " << sz << " at (" << i << "," << j << ")" << endl;
};
