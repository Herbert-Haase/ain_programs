Ich habe Aufgabe 4 in C++ gelöst. Der Grund dafür war, dass C++ mehr Auskunft darüber gibt, wie die Datenstrukturen implementiert sind, ohne den Quellcode lesen zu müssen. Außerdem bevorzuge ich C++ persönlich. Den vorgegebenen Java-Programmcode habe ich mir in C++ übersetzen lassen.
### 4a) 
War recht einfach: Die implementierten Prozeduren und die Funktion sind jeweils unter 5 Zeilen lang und beinhalten je eine Schleife und Verzweigungen. Dass alle getrennt über den Container iterieren, ist natürlich redundant und eine der Optimierungen in 4b.

Das Schwierigste dabei war, dass removeEmptyLines und removeShortLines über den Container iterieren und gleichzeitig Elemente daraus entfernen. Das heißt eine standard for-each loop kann hier nicht verwendet werden, stattdessen habe ich die Abstraktionsschicht heruntergebrochen und mit den Iterator gearbeitet. 
```c++
  for (auto it = lines.begin(); it != lines.end();) {
    if (it->size() < MIN_LENGTH)
      it = lines.erase(it);
    else
      ++it;
  }
```
Wenn ein Element entfernt wird, wird container.erase(element) verwendet, wodurch der Iterator auf das dem entfernten Element folgende Element aktualisiert wird.

### 4b)
Statt java.util.streams habe ich std::views aus der ranges Bibliothek verwendet. Es hat eine Weile gedauert sich da einzulesen, weil die meisten Quellen nur erklären welche APIs verwendet werden sollen, aber nicht was im Hintergrund passiert. Ich fande https://www.studyplan.dev/pro-cpp/views sehr hilfreich.

Views sind Ranges, non-owning. view Adapter nehmen als input views und geben auch views als Output aus. Diese können entweder manuell oder mithilfe des |operator von links nach rechts verkettet werden.

```c++
  // a
  auto View {
    std::views::filter(Numbers, Filter) |
    std::views::take(3) |
    std::views::reverse
  };
 // b 
    auto View {
    std::views::reverse(
      std::views::take(
        std::views::filter(Numbers, Filter),
      3)
    )
  };
```
Mit cppinsights sieht man die zugrundeliegenden Typen:
```c++
// a
std::ranges::reverse_view<std::ranges::take_view<std::ranges::filter_view<std::ranges::ref_view<std::vector<int, std::allocator<int> > >, bool (*)(int)> > > & __range1 = View;
 // b (bis zur 2. Zeile sind hohe Ähnlichkeiten ersichtlich)
 std::ranges::reverse_view<std::ranges::take_view<std::ranges::filter_view<std::ranges::ref_view<std::vector<int, std::allocator<int> > >, bool (*)(int)> > > View = {std::ranges::views::__adaptor::operator|(std::ranges::views::__adaptor::operator|(std::ranges::views::filter.operator()(Numbers, Filter), static_cast<const std::ranges::views::__adaptor::_RangeAdaptor<std::ranges::views::_Take>&>(std::ranges::views::take).operator()(3)), std::ranges::views::reverse)};
  
```

Bis zur zweiten Zeile sind deutliche Ähnlichkeiten ersichtlich. Die verketteten View-Adapter werden zusammen mit der View abgespeichert, und erst bei der tatsächlichen Wertabfrage werden diese Funktionen ausgelöst.

Da die Views der Standardbibliothek kein direktes reduce besitzen, nutze ich im Code stattdessen std::ranges::fold_left aus C++23. Das Prinzip bleibt dabei gleich. Diese View, die ich zum Filtern und Mappen der Zeilen verwendet habe, hat diesen Typen:
```c++
  auto lazy_file_stream =
     std::views::istream<Line>(input) |
     std::views::transform([](const Line &l) { return l.str; });

  auto pipeline =
      lazy_file_stream | std::views::filter([](const std::string &line) {
        return (!line.empty() &&
                line.find_first_not_of(" \t\r\n") != std::string::npos);
      }) |
      std::views::filter(
          [](const std::string &line) { return (line.size() >= MIN_LENGTH); }) |
      std::views::transform(
          [](const std::string &line) { return line.size(); });

  int n = std::ranges::fold_left(pipeline, 0, std::plus<>{});

// typen:
typename __invoke_result<const std::ranges::views::_Transform &,
std::ranges::filter_view<std::ranges::transform_view<std::ranges::
basic_istream_view<line, char, std::char_traits<char>>, (lambda)>,
(lambda)>, (lambda)>, const (lambda) &>::type
``` 
reduce musste mit getrennt verwendet, da dieser einen eager Algorithmus darstellt und es dem entsprechend keinen view adapter davon gibt. Dieses Terminal löst somit die Funktionskette auf.

#### 4c
└── ❯ ./functional ./Functional.cpp                                    
result = 1493 (68 microsec)
└── ❯ ./Procedural ./Functional.cpp 
result = 1493 (162 microsec)
└── ❯ ls -la ./Functional.cpp 
-rw-r--r-- 1 herbert herbert 1880 17. Mai 23:00 ./Functional.cpp


└── ❯ ./functional ~/Music/brownNoise.m4a 
result = 694019004 (2246678 microsec)
└── ❯ ./Procedural ~/Music/brownNoise.m4a 
result = 694019004 (1941156 microsec)
└── ❯ ls -la ~/Music/brownNoise.m4a 
-rw-rw-r-- 1 herbert herbert 698812947 11. Jul 2023  ~/Music/brownNoise.m4a

Whoops: Funktional ist um 13,6% langsamer.

Laut perf verbringt das funktionale Programm die meiste Zeit (5,18 %) mit der Allokation von Strings. Ich habe es dann so abgeändert, dass die anonymen Funktionen keine Strings kopieren, sondern zum Filtern und Rechnen lediglich Referenzen auf die Dateizeilen verwenden:

```c++
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

  auto pipeline =
      std::views::istream<Line>(input) | std::views::filter([](const Line &l) {
        return (!l.view.empty() &&
                l.view.find_first_not_of(" \t\r\n") != std::string::npos);
      }) |
      std::views::filter(
          [](const Line &l) { return (l.view.size() >= MIN_LENGTH); }) |
      std::views::transform([](const Line &l) { return l.view.size(); });
```
Damit ist die funktionale Version tatsächlich schneller.
└── ❯ ./Procedural ~/Music/brownNoise.m4a
result = 694019004 (1912152 microsec)
└── ❯ ./Functional ~/Music/brownNoise.m4a
result = 694019004 (887067 microsec)

Es wäre bestimmt möglich, das prozedurale Programm so umzuschreiben, dass es ebenfalls lediglich Referenzen statt Kopien verwendet, um damit eine weitere Zeitmessung durchzuführen. Aus Zeitgründen habe ich dies jedoch unterlassen.
