// ExprLexer.g4
lexer grammar ExprLexer;

//KEYWORDS
BIS: 'bis';
UHR: 'Uhr';
TAEGLICH: 'täglich';
RUHETAG: 'Ruhetag';
GESCHLOSSEN: 'vorübergehend geschlossen';
SONN_FEIERTAG: 'an Sonn- und Feiertagen' | 'Sonn- und Feiertagen';
AB: 'ab';
GUTEM_WETTER: 'bei gutem Wetter';

// DAYS and MONTHS
WEEKDAY: 'Montag' | 'Dienstag' | 'Mittwoch' | 'Donnerstag' | 'Freitag' | 'Samstag' | 'Sonntag';
MONTH: 'Januar' | 'Februar' | 'März' | 'April' | 'Mai' | 'Juni' | 'Juli' | 'August' | 'September' | 'Oktober' | 'November' | 'Dezember';

TIME: ([0-1]?[0-9] | '2'[0-3]) '.' [0-5][0-9];

// dates like 1., 15., 23.
DAY_NUM: [1-3]?[0-9] '.';

COMMA: ',';

WORD: [a-zA-ZäöüÄÖÜßé\-]+;

WS: [ \t\r\n]+ -> channel(HIDDEN);

InvalidChar: .;

