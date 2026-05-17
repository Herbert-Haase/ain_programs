#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

constexpr int MIN_LENGTH = 20;

void readLines(std::ifstream &input, std::list<std::string> &lines);
void removeEmptyLines(std::list<std::string> &lines);
void removeShortLines(std::list<std::string> &lines);
int totalLineLengths(const std::list<std::string> &lines);

void readLines(std::ifstream &input, std::list<std::string> &lines) {
  std::string line;
  while (std::getline(input,line)) {
    lines.push_back(std::move(line));
  }
}

void removeEmptyLines(std::list<std::string> &lines) {
  for (auto it = lines.begin(); it != lines.end();) {
    if (!it->empty() && it->find_first_not_of(" \t\r\n") != std::string::npos)
      ++it;
    else
      it = lines.erase(it);
  }
}

void removeShortLines(std::list<std::string> &lines) {
  for (auto it = lines.begin(); it != lines.end();) {
    if (it->size() < MIN_LENGTH)
      it = lines.erase(it);
    else
      ++it;
  }
}

int totalLineLengths(const std::list<std::string> &lines) {
  int totalLength = 0;
  for (const auto &line : lines) {
    totalLength += line.size();
  }
  return totalLength;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Fehler: Fehlendes Argument für den Dateipfad." << std::endl;
    return 1;
  }

  std::string filename = argv[1];
  std::list<std::string> lines;

  std::ifstream input(filename);
  if (!input.is_open()) {
    std::cerr << "Fehler beim Öffnen der Datei: " << filename << std::endl;
    return 1;
  }

  auto start = std::chrono::high_resolution_clock::now();

  readLines(input, lines);
  removeEmptyLines(lines);
  removeShortLines(lines);
  int n = totalLineLengths(lines);

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
