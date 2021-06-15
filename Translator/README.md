Воєводін І.П. Варіант №9

Граматика за варіантом:
1. <signal-program> --> <program>

2. <program> --> PROGRAM <procedure-identifier> ;
	<block>.
3. <block> --> <declarations> BEGIN <statements-list> END

4. <statements-list> --> <empty>

5. <declarations> --> <math-function-declarations>

6. <math-function-declarations> --> DEFFUNC <function-list> | <empty>

7. <function-list> --> <function> <function-list> | <empty>

8. <function> --> <function-identifier> = <constant><function-characteristic> ;

9. <function-characteristic> --> \ <unsigned-integer> , <unsigned-integer>

10. <constant> --> <unsigned-integer>
11. <procedure-identifier> --> <identifier>
12. <function-identifier> --> <identifier>
13. <identifier> --> <letter><string>
14. <string> --> <letter><string> | <digit><string> | <empty>
15. <unsigned-integer> --> <digit><digits-string>
16. <digits-string> --> <digit><digits-string> | <empty>
17. <digit> --> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
18. <letter> --> A | B | C | D | ... | Z

Обробка помилок:
Lexer:
    1) Обробка симболів які заборонені за граматикою та вивід їх місцезнаходження.
    2) Обробка помилок незакритих комментарів.
Parser:
    1) Обробка синтаксичних помилок в конструкціях програми з виводом їх місцезнаходження та виводу очікуваних виразів.
    2) Обробка помилок якщо конструкція не завершена, тобто замість очікуваного токена нічого немає. 
Code generator:
    1) Обробка помилок коли в конструкції DEFFUNC функції отримують однаковий ідинтифікатор з виводом місцезнаходження помилки.
    2) Обробка помилки коли в конструкції DEFFUNC діапазон задан некорректно, тобто перший індекс більше за другий.
    3) Обробка помилки коли в конструкції DEFFUNC значення другого індексу діапазонів менше 1.