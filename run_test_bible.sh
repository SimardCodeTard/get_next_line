#!/bin/zsh

if [ ! -f tests/the_holy_bible.txt ]; then
    curl https://www.gutenberg.org/cache/epub/7999/pg7999.txt > tests/the_holy_bible.txt
fi

clang -Werror -Wextra -Wall -DBUFFER_SIZE=$1 -I./ get_next_line.c get_next_line_utils.c -o mandatory.out tests/main.c
clang -Werror -Wextra -Wall -DBUFFER_SIZE=$1 -o bonus.out -I./ get_next_line_bonus.c get_next_line_utils_bonus.c tests/main.c

echo "Mandatory :"
./mandatory.out tests/the_holy_bible.txt -1 1

echo "Bonus :"
./bonus.out tests/the_holy_bible.txt -1 1
