Ich habe die Aufgabe 4 in C++ gelöst, der Grund dafür war, dass C++ mehr Auskunft darüber gibt wie die Datenstrukturen implementiert sind, ohne den Source Code zulesen, außerdem bevorzuge ich C++ persönlich.

Den vorgegebenen Java Program Code habe ich mir in C++ übersetzen lassen.

### 4a) 
War recht einfach, die implemtierten Prozeduren und eine Funktion sind jeweils unter 5 Zeilen und beinhalten je eine Schleife und Verzweigungen. Dass Alle über den Container getrennt iterieren ist natürlich redundant und eine der Optimierungen in 4b. Das Schwierigste dabei war, dass removeEmptyLines und removeShortLines über den Container iterieren und gleichzeitig Elemente daraus entfernen. Das heißt eine standard for-each loop kann hier nicht verwendet werden, stattdessen habe ich die Abstraktionsschicht heruntergebrochen und mit den Iterator gearbeitet. 
```c++
  for (auto it = lines.begin(); it != lines.end();) {
    if (it->size() < MIN_LENGTH)
      it = lines.erase(it);
    else
      ++it;
  }
```
Wenn ein Element entfernt wird, wird container.erase(element) verwendet und damit den Iterator auf das entfernte Element folgende Element weitergegeben.

### 4b)
Statt java.util.streams habe ich std::views aus der ranges Bibliothek verwendet. Es hat eine Weile gedauert sich da einzulesen, weil die meisten Quellen nur erklären welche APIs verwendet werden sollen, aber nicht was im Hintergrund passiert. Ich fande https://www.studyplan.dev/pro-cpp/views sehr hilfreich.

views sind ranges, non-owning. view Adapter nehmen als input views und geben auch views als Output aus. Diese können entweder manuell oder mithilfe des |operator von links nach rechts gechained werden.

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
mit cppinsights
```c++
// a
std::ranges::reverse_view<std::ranges::take_view<std::ranges::filter_view<std::ranges::ref_view<std::vector<int, std::allocator<int> > >, bool (*)(int)> > > & __range1 = View;
 // b (bis zur 2. Zeile sind hohe Ähnlichkeiten ersichtlich)
 std::ranges::reverse_view<std::ranges::take_view<std::ranges::filter_view<std::ranges::ref_view<std::vector<int, std::allocator<int> > >, bool (*)(int)> > > View = {std::ranges::views::__adaptor::operator|(std::ranges::views::__adaptor::operator|(std::ranges::views::filter.operator()(Numbers, Filter), static_cast<const std::ranges::views::__adaptor::_RangeAdaptor<std::ranges::views::_Take>&>(std::ranges::views::take).operator()(3)), std::ranges::views::reverse)};
  
```

Die gechaineten view-Adapter werden zusammen mit der View abgespeichert und zusammen und bei der Wert Abfrage werden diese Funktionen ausgelöst.
Da das view der Standard Bibliothek kein reduce besitzt bin ich auf range-v3 umgestiegen, das Prinzip bleibt aber gleich.
Dieses view die ich zum Filtern und Mappen der Zeilen verwendet habe, hat diesen Typen:
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
reduce musste mit getrennt verwendet, da dieser einen eager Algorithmus darstellt und es dem entsprechend keinen view adapter davon gibt. Dementsprechend löst dieses Terminal die Funktionskette auf.

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

Whoops



