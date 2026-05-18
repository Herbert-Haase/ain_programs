#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <numeric>
#include <string>

#include <execution>
#include <iterator>
#include <numeric>
#include <ranges>

constexpr int MIN_LENGTH = 20;

struct Line {
  std::string_view view;

  operator std::string_view() const { return view; }

  friend std::istream &operator>>(std::istream &is, Line &line) {
    thread_local std::string buffer;

    if (std::getline(is, buffer)) {
      line.view = buffer;
    }
    return is;
  }
};

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Fehler: Fehlendes Argument für den Dateipfad." << std::endl;
    return 1;
  }

  std::string filename = argv[1];

  std::ifstream input(filename);
  if (!input.is_open()) {
    std::cerr << "Fehler beim Öffnen der Datei: " << filename << std::endl;
    return 1;
  }

  auto start = std::chrono::high_resolution_clock::now();

  auto pipeline =
      std::views::istream<Line>(input) | std::views::filter([](const Line &l) {
        return (!l.view.empty() &&
                l.view.find_first_not_of(" \t\r\n") != std::string::npos);
      }) |
      std::views::filter(
          [](const Line &l) { return (l.view.size() >= MIN_LENGTH); }) |
      std::views::transform([](const Line &l) { return l.view.size(); });

  int n = std::ranges::fold_left(pipeline, 0, std::plus<>{});

  auto stop = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
          .count();

  std::printf("result = %d (%ld microsec)\n", n, static_cast<long>(duration));

  return 0;
}

// TODO: Implementieren Sie die Funktionen readLines, removeEmptyLines,
// removeShortLines, totalLineLengths Nutzen Sie hierzu Schleifen und
// Verzweigungen (imperativer/prozeduraler Stil).


