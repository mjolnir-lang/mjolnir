# JSON (JavaScript Object Notation)

JSON (JavaScript Object Notation) is a lightweight data-interchange format. It
is easy for humans to read and write. It is easy for machines to parse and
generate. It is based on a subset of the JavaScript Programming Language
Standard ECMA-262 3rd Edition - December 1999. JSON is a text format that is
completely language independent but uses conventions that are familiar to
programmers of the C-family of languages, including C, C++, C#, Java,
JavaScript, Perl, Python, and many others. These properties make JSON an ideal
data-interchange language.

JSON is built on two structures:

- A collection of name/value pairs. In various languages, this is realized as
an _object_, record, struct, dictionary, hash table, keyed list, or associative
array.
- An ordered list of values. In most languages, this is realized as an _array_,
vector, list, or sequence.

These are universal data structures. Virtually all modern programming languages
support them in one form or another. It makes sense that a data format that is
interchangeable with programming languages also be based on these structures.

In JSON, they take on these forms:

Valid JSON notation consists of a single _value_.

```txt
json
    element
```

An _object_ is an unordered set of name/value pairs. An object begins with `{`
(left brace) and ends with `}` (right brace). Each name is followed by `:`
(colon) and the name/value pairs are separated by `,` (comma).

```txt
object
    '{' ws '}'
    '{' members '}'

members
    member
    member ',' members

member
    ws string ws ':' element
```

An _array_ is an ordered collection of values. An array begins with `[` (left
bracket) and ends with `]` (right bracket). Values are separated by `,`
(comma).

```txt
array
    '[' ws ']'
    '[' elements ']'

elements
    element
    element ',' elements

element
    ws value ws
```

A _value_ can be a _string_ in double quotes, or a _number_, or `true` or
`false` or `null`, or an _object_ or an _array_. These structures can be
nested.

```txt
value
    object
    array
    string
    number
    "true"
    "false"
    "null"
```

A _string_ is a sequence of zero or more Unicode characters, wrapped in double
quotes, using backslash escapes. A character is represented as a single
character string. A string is very much like a C or Java string.

```txt
string
'"' characters '"'

characters
    ""
    character characters

character
    '0020' . '10FFFF' - '"' - '\'
'\' escape

escape
    '"'
    '\'
    '/'
    'b'
    'f'
    'n'
    'r'
    't'
    'u' hex hex hex hex
```

A _number_ is very much like a C or Java number, except that the octal and
hexadecimal formats are not used.

```txt
hex
    digit
    'A' . 'F'
    'a' . 'f'

number
    integer fraction exponent

integer
    digit
    onenine digits
    '-' digit
    '-' onenine digits

digits
    digit
    digit digits

digit
    '0'
    onenine

onenine
    '1' . '9'

fraction
    ""
    '.' digits

exponent
    ""
    'E' sign digits
    'e' sign digits

sign
    ""
    '+'
    '-'
```

Whitespace can be inserted between any pair of tokens. Excepting a few encoding
details, that completely describes the language.

```txt
ws
    ""
    '0020' ws
    '000A' ws
    '000D' ws
    '0009' ws
```
