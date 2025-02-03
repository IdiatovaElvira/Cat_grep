# Cat_grep
Development of Bash text utilities: cat, greз
Разработка базовых утилит Bash cat и grep по работе с текстами на языке программирования С.

Опция cat
| №  | Опция (GNU)                  | Описание                                                                 |
|----|------------------------------|-------------------------------------------------------------------------|
| 1  | `-b` (GNU: `--number-nonblank`) | Нумерует только непустые строки.                                        |
| 2  | `-e` (GNU: `-E`)              | Также отображает символы конца строки как `$` (GNU: `-E` без `-v`).     |
| 3  | `-n` (GNU: `--number`)        | Нумерует все выходные строки.                                           |
| 4  | `-s` (GNU: `--squeeze-blank`) | Сжимает несколько смежных пустых строк.                                 |
| 5  | `-t` (GNU: `-T`)              | Также отображает табы как `^I` (GNU: `-T` без `-v`).                    |

Опции grep
| №  | Опция      | Описание                                                                 |
|----|------------|-------------------------------------------------------------------------|
| 1  | `-e`       | Шаблон для поиска.                                                      |
| 2  | `-i`       | Игнорирует различия регистра.                                           |
| 3  | `-v`       | Инвертирует смысл поиска (выводит строки, не совпадающие с шаблоном).   |
| 4  | `-c`       | Выводит только количество совпадающих строк.                            |
| 5  | `-l`       | Выводит только имена файлов, содержащих совпадения.                     |
| 6  | `-n`       | Предваряет каждую строку вывода номером строки из файла.                |
| 7  | `-h`       | Выводит совпадающие строки без указания имени файла.                    |
| 8  | `-s`       | Подавляет сообщения об ошибках о несуществующих или нечитаемых файлах.  |
| 9  | `-f file`  | Получает регулярные выражения из файла.                                 |
| 10 | `-o`       | Печатает только совпадающие (непустые) части строки.                    |
