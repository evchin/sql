# SQL

Building a SQL Database from the ground up.

# basic_test.cpp output:

```
----------running basic_test.cpp---------


[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from SQL_BASIC
[ RUN      ] SQL_BASIC.SQLBasic
>make table employee fields  last,       first,         dep,      salary, year
basic_test: table created.

>make table employee fields  last,       first,         dep,      salary, year
>insert into employee values Blow,       Joe,           CS,       100000, 2018
>insert into employee values Blow,       JoAnn,         Physics,  200000, 2016
>insert into employee values Johnson,    Jack,          HR,       150000, 2014
>insert into employee values Johnson,    "Jimmy",     Chemistry,140000, 2018
>make table student fields  fname,          lname,    major,    age
>insert into student values Flo,            Yao,        Art,    20
>insert into student values Bo,                      Yang,      CS,             28
>insert into student values "Sammuel L.", Jackson,      CS,             40
>insert into student values "Billy",         Jackson,   Math,   27
>insert into student values "Mary Ann",   Davis,        Math,   30



>select * from employee
Table Name: _select_table_1
Records: 4
                   record                     last                    first                      dep                   salary                     year
                        0                     Blow                      Joe                       CS                   100000                     2018
                        1                     Blow                    JoAnn                  Physics                   200000                     2016
                        2                  Johnson                     Jack                       HR                   150000                     2014
                        3                  Johnson                    Jimmy                Chemistry                   140000                     2018


basic_test: records selected: [0, 1, 2, 3]

>select last, first, age from employee
Table Name: _select_table_2
Records: 4
                   record                     last                    first                      age
                        0                     Blow                      Joe                     Blow
                        1                     Blow                    JoAnn                     Blow
                        2                  Johnson                     Jack                  Johnson
                        3                  Johnson                    Jimmy                  Johnson


basic_test: records selected: [0, 1, 2, 3]

>select last from employee
Table Name: _select_table_3
Records: 4
                   record                     last
                        0                     Blow
                        1                     Blow
                        2                  Johnson
                        3                  Johnson


basic_test: records selected: [0, 1, 2, 3]

>select * from employee where last = Johnson
Table Name: _select_table_5
Records: 2
                   record                     last                    first                      dep                   salary                     year
                        0                  Johnson                     Jack                       HR                   150000                     2014
                        1                  Johnson                    Jimmy                Chemistry                   140000                     2018


basic_test: records selected: [2, 3]

>select * from employee where last=Blow and major="JoAnn"
Table Name: _select_table_9
Records: 0
                   record                     last                    first                      dep                   salary                     year


basic_test: records selected: []

>select * from student
Table Name: _select_table_10
Records: 5
                   record                    fname                    lname                    major                      age
                        0                      Flo                      Yao                      Art                       20
                        1                       Bo                     Yang                       CS                       28
                        2               Sammuel L.                  Jackson                       CS                       40
                        3                    Billy                  Jackson                     Math                       27
                        4                 Mary Ann                    Davis                     Math                       30


basic_test: records selected: [0, 1, 2, 3, 4]

>select * from student where (major=CS or major=Art)
Table Name: _select_table_14
Records: 3
                   record                    fname                    lname                    major                      age
                        0                      Flo                      Yao                      Art                       20
                        1                       Bo                     Yang                       CS                       28
                        2               Sammuel L.                  Jackson                       CS                       40


basic_test: records selected: [0, 1, 2]

>select * from student where lname>J
Table Name: _select_table_16
Records: 4
                   record                    fname                    lname                    major                      age
                        0               Sammuel L.                  Jackson                       CS                       40
                        1                    Billy                  Jackson                     Math                       27
                        2                       Bo                     Yang                       CS                       28
                        3                      Flo                      Yao                      Art                       20


basic_test: records selected: [2, 3, 1, 0]

>select * from student where lname>J and (major=CS or major=Art)
Table Name: _select_table_22
Records: 3
                   record                    fname                    lname                    major                      age
                        0               Sammuel L.                  Jackson                       CS                       40
                        1                       Bo                     Yang                       CS                       28
                        2                      Flo                      Yao                      Art                       20


basic_test: records selected: [2, 1, 0]
----- END TEST --------
[       OK ] SQL_BASIC.SQLBasic (262 ms)
[----------] 1 test from SQL_BASIC (262 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (265 ms total)
[  PASSED  ] 1 test.
```

# testB.cpp output:

```
----------running testB.cpp---------


[==========] Running 3 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 3 tests from TEST_SQL
[ RUN      ] TEST_SQL.TestSample
//****************************************************************************
//              CREATE AND INSERT
//****************************************************************************

//---- employee table ----------
[0] make table employee fields  last,           first,                  dep
Recnos: []
[1] insert into employee values Blow,           Joe,                    CS
Recnos: []
[2] insert into employee values Johnson,        "Jimmy",                Chemistry
Recnos: []
[3] insert into employee values Yang,           Bo,                     CS
Recnos: []
[4] insert into employee values "Jackson",      Billy,                  Math
Recnos: []
[5] insert into employee values Johnson,        Billy,                  "Phys Ed"
Recnos: []
[6] insert into employee values "Van Gogh",     "Jim Bob",              "Phys Ed"
Recnos: []

[7] select * from employee
Recnos: [0, 1, 2, 3, 4, 5]

//----- student table ----------
[8] make table student fields   fname,                  lname,          major,                          age
Recnos: [0, 1, 2, 3, 4, 5]
[9] insert into student values  Flo,                    Yao,            CS,                             20
Recnos: [0, 1, 2, 3, 4, 5]
[10] insert into student values         "Flo",                  "Jackson",      Math,                           21
Recnos: [0, 1, 2, 3, 4, 5]
[11] insert into student values         Calvin,                 Woo,            Physics,                        22
Recnos: [0, 1, 2, 3, 4, 5]
[12] insert into student values         "Anna Grace",   "Del Rio",      CS,                                     22
Recnos: [0, 1, 2, 3, 4, 5]
[13] select * from student
Recnos: [0, 1, 2, 3]



//****************************************************************************
//              SIMPLE SELECT
//****************************************************************************

[14] select * from student
Recnos: [0, 1, 2, 3]

//------- simple strings -------------------
[15] select * from student where lname = Jackson
Recnos: [1]

//----- quoted strings ---------------------
[16] select * from student where lname = "Del Rio"
Recnos: [3]

//-------- non-existing string ------------------
[17] select * from student where lname = "Does Not Exist"
Recnos: []

//****************************************************************************
//              RELATIONAL OPERATORS:
//****************************************************************************

//.................
//:Greater Than   :
//.................
[18] select * from student where lname > Yang
Recnos: [0]


//. . . . . . . . . . . . . (Greater Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .
[19] select * from student where age > 50
Recnos: []

//. . . . . . . . . . . . . (Greater than: last item) . . . . . . . . . . . . . . . . . .
[20] select * from student where age  > 53
Recnos: []

//. . . . . . . . . . . . . (Greater Than: Passed last item) . . . . . . . . . . . . . . . . . . . . .
[21] select * from student where age > 54
Recnos: []

//.................
//:Greater Equal  :
//.................
[22] select * from student where lname >= Yang
Recnos: [0]
//. . . . . .  (Greater Equal non-existing: ) . . . . . . . . . . .
[23] select * from employee where last >= Jack
Recnos: [3, 1, 4, 5, 2]


//.................
//:Less Than      :
//.................


//. . . . . . . . . . . . . (Less Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .
[24] select * from student where lname < Jackson
Recnos: [3]

//. . . . . . . . . . . . . (Less than: first item) . . . . . . . . . . . . . . . . . .
[25] select * from student where age  < 20
Recnos: []


//. . . . . . . . . . . . . (Less Than: before first item) . . . . . . . . . . . . . . . . . . . . .

[26] select * from student where age  < 19
Recnos: []


//.................
//:Less Equal     :
//.................

[27] select * from student where lname <= Smith
Recnos: [3, 1]

//. . . . . .  (Less Equal non-existing: ) . . . . . . . . . . .
[28] select * from employee where last <= Peach
Recnos: [0, 3, 1, 4]

//****************************************************************************
//              LOGICAL OPERATORS
//****************************************************************************


//.................
//:AND            :
//.................

[29] select * from student where fname = "Flo" and lname = "Yao"
Recnos: [0]


//.................
//:OR            :
//.................
[30] select * from student where fname = Flo or lname = Jackson
Recnos: [1, 0]


//.................
//:OR AND         :
//.................
[31] select * from student where fname = Flo or major = CS and age <= 23
Recnos: [0, 3, 1]


//.................
//:AND OR AND     :
//.................

[32] select * from student where age <30 and major=CS or major = Physics and lname = Jackson
Recnos: [0, 3]


//.................
//:OR AND OR      :
//.................

[33] select * from student where lname = Yang or major = CS and age < 23 or lname = Jackson
Recnos: [1, 0, 3]










[       OK ] TEST_SQL.TestSample (400 ms)
[ RUN      ] TEST_SQL.TestFinal21
//****************************************************************************
//              CREATE TABLES AND INSERT RECORDS
//****************************************************************************


[0] make table employee fields  last,           first,                  dep,            salary,         year
Recnos: []
[1] insert into employee values Blow,           Joe,                    CS,                     100000,         2018
Recnos: []
[2] insert into employee values Blow,           JoAnn,                  Physics,        200000,         2016
Recnos: []
[3] insert into employee values Johnson,        Jack,                   HR,             150000,         2014
Recnos: []
[4] insert into employee values Johnson,        "Jimmy",                Chemistry,      140000,         2018
Recnos: []
[5] insert into employee values Yao,            Jimmy,                  Math,           145000,         2014
Recnos: []
[6] insert into employee values "Yao",          Flo,                    CS,                     147000,         2012
Recnos: []
[7] insert into employee values Yang,           Bo,                     CS,                     160000,         2013
Recnos: []
[8] insert into employee values Jackson,        "Flo",                  Math,           165000,         2017
Recnos: []
[9] insert into employee values Jackson,        Bo,                             Chemistry,      130000,         2011
Recnos: []
[10] insert into employee values "Jackson",     Billy,                  Math,           170000,         2017
Recnos: []
[11] insert into employee values Johnson,       "Mary Ann",     Math,           165000,         2014
Recnos: []
[12] insert into employee values Johnson,       "Billy Bob",    Physics,        142000,         2014
Recnos: []
[13] insert into employee values Johnson,       Billy,                  "Phys Ed",      102000,         2014
Recnos: []
[14] insert into employee values "Van Gogh",    Vincent,                Art,            240000,         2015
Recnos: []
[15] insert into employee values "Van Gogh",    Vincent,                CS,                     245000,         2015
Recnos: []
[16] insert into employee values "Van Gogh",    "Jim Bob",              "Phys Ed",      230000,         2010
Recnos: []
[17] select * from employee
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]

[18] make table student fields fname, lname, major, age, company
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[19] insert into student values Flo,                    Yao,            CS,                             20,     Google
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[20] insert into student values Bo,                             Yang,           CS,                             28,             Microsoft
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[21] insert into student values "Sammuel L.",   Jackson,        CS,                             40,             Uber
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[22] insert into student values "Flo",                  "Jackson",      Math,                           21,             Google
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[23] insert into student values "Greg",                         "Pearson",      Physics,                        20,             Amazon
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[24] insert into student values "Jim Bob",              Smith,          Math,                           23,             Verizon
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[25] insert into student values Calvin,                         Woo,            Physics,                        22,             Uber
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[26] insert into student values "Anna Grace",   "Del Rio",      CS,                                     22,             USAF
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[27] insert into student values "Teresa Mae",   Gowers,         Chemistry,                      22,             Verizon
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[28] insert into student values Alex,                   Smith,          "Gender Studies",       53,             Amazon
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[29] select * from student
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]


//****************************************************************************
//              SIMPLE SELECT:
//****************************************************************************

[30] select * from student
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

//------- simple strings -------------------
[31] select * from student where lname = Jackson
Recnos: [2, 3]
[32] select * from student where major = CS
Recnos: [0, 1, 2, 7]
[33] select * from student where company = Uber
Recnos: [2, 6]

//----- quoted strings ---------------------
[34] select * from student where lname = "Del Rio"
Recnos: [7]
[35] select * from student where fname = "Jim Bob"
Recnos: [5]
[36] select * from student where fname = "Anna Grace"
Recnos: [7]
[37] select * from student where fname = "Teresa Mae"
Recnos: [8]

//-------- non-existing string ------------------
[38] select * from student where lname = "Does Not Exist"
Recnos: []

//****************************************************************************
//              RELATIONAL OPERATORS:
//****************************************************************************

//.................
//:Greater Than   :
//.................
[39] select * from student where lname > Yang
Recnos: [0]
[40] select * from student where major > Math
Recnos: [4, 6]
[41] select * from student where fname > "Sammuel L."
Recnos: [8]
[42] select * from employee where salary > 200000
Recnos: [15, 13, 14]
[43] select * from employee where dep > Chemistry
Recnos: [2, 4, 7, 9, 10, 12, 15, 1, 11]
[44] select * from employee where last > Jackson
Recnos: [2, 3, 10, 11, 12, 13, 14, 15, 6, 4, 5]
[45] select * from employee where first > "Billy Bob"
Recnos: [6, 8, 5, 7, 2, 15, 3, 4, 1, 0, 10, 13, 14]


//. . . . . . . . . . . . . (Greater Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .
[46] select * from student where age > 50
Recnos: [9]
[47] select * from student where age > 35
Recnos: [2, 9]
[48] select * from student where fname > T
Recnos: [8]
[49] select * from employee where salary > 130000
Recnos: [3, 11, 4, 5, 2, 6, 7, 10, 9, 1, 15, 13, 14]
[50] select * from employee where  year > 2009
Recnos: [15, 8, 5, 6, 2, 4, 10, 11, 12, 13, 14, 1, 7, 9, 0, 3]

//. . . . . . . . . . . . . (Greater than: last item) . . . . . . . . . . . . . . . . . .
[51] select * from student where age  > 53
Recnos: []
[52] select * from student where lname > Yao
Recnos: []
[53] select * from student where fname > "Teresa Mae"
Recnos: []
[54] select * from employee where last > "Van Gogh"
Recnos: [6, 4, 5]
[55] select * from employee where first > Vincent
Recnos: []
[56] select * from employee where salary > 260000
Recnos: []

//. . . . . . . . . . . . . (Greater Than: Passed last item) . . . . . . . . . . . . . . . . . . . . .
[57] select * from student where age > 54
Recnos: []
[58] select * from student where lname > Zoolander
Recnos: []
[59] select * from employee where last > Zoolaner
Recnos: []
[60] select * from employee where first > Xu
Recnos: []

//.................
//:Greater Equal  :
//.................
[61] select * from student where lname >= Yang
Recnos: [1, 0]
[62] select * from student where fname >= "Sammuel L."
Recnos: [2, 8]
[63] select * from student where age >= 40
Recnos: [2, 9]
//. . . . . .  (Greater Equal non-existing: ) . . . . . . . . . . .
[64] select * from employee where last >= Jack
Recnos: [7, 8, 9, 2, 3, 10, 11, 12, 13, 14, 15, 6, 4, 5]
[65] select * from employee where first >= Bill
Recnos: [9, 12, 11, 6, 8, 5, 7, 2, 15, 3, 4, 1, 0, 10, 13, 14]
[66] select * from employee where salary >= 235000
Recnos: [13, 14]


//.................
//:Less Than      :
//.................


//. . . . . . . . . . . . . (Less Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .
[67] select * from student where lname < Jackson
Recnos: [7, 8]
[68] select * from student where major < Math
Recnos: [0, 1, 2, 7, 8, 9]
[69] select * from student where fname < "Jim Bob"
Recnos: [9, 7, 1, 6, 0, 3, 4]
[70] select * from employee where salary < 200000
Recnos: [0, 12, 8, 3, 11, 4, 5, 2, 6, 7, 10, 9]
[71] select * from employee where dep < CS
Recnos: [13]
[72] select * from employee where last < Jackson
Recnos: [0, 1]
[73] select * from employee where first < "Billy Bob"
Recnos: [9, 12]

//. . . . . . . . . . . . . (Less than: first item) . . . . . . . . . . . . . . . . . .
[74] select * from student where age  < 20
Recnos: []
[75] select * from student where lname < "Del Rio"
Recnos: []
[76] select * from student where fname < Alex
Recnos: []
[77] select * from employee where last < Blow
Recnos: []
[78] select * from employee where first < Billy
Recnos: []
[79] select * from employee where salary < 100000
Recnos: []


//. . . . . . . . . . . . . (Less Than: before first item) . . . . . . . . . . . . . . . . . . . . .

[80] select * from student where age  < 19
Recnos: []
[81] select * from student where lname < Adams
Recnos: []
[82] select * from student where fname < Adam
Recnos: []
[83] select * from employee where last < Alex
Recnos: []
[84] select * from employee where first < Avory
Recnos: []
[85] select * from employee where dep < Alchemy
Recnos: []


//.................
//:Less Equal     :
//.................

[86] select * from student where lname <= Smith
Recnos: [7, 8, 2, 3, 4, 5, 9]
[87] select * from student where fname <= Greg
Recnos: [9, 7, 1, 6, 0, 3, 4]
[88] select * from student where age <= 40
Recnos: [0, 4, 3, 6, 7, 8, 5, 1, 2]

//. . . . . .  (Less Equal non-existing: ) . . . . . . . . . . .
[89] select * from employee where last <= Peach
Recnos: [0, 1, 7, 8, 9, 2, 3, 10, 11, 12]
[90] select * from employee where first <= Gary
Recnos: [9, 12, 11, 6, 8, 5, 7]
[91] select * from employee where salary <= 23500
Recnos: [0, 12, 8, 3, 11, 4, 5, 2, 6, 7, 10, 9, 1, 15]

//****************************************************************************
//              LOGICAL OPERATORS
//****************************************************************************


//.................
//:AND            :
//.................

[92] select * from student where fname = "Flo" and lname = "Yao"
Recnos: [0]
[93] select * from student where major = "CS" and age < 25
Recnos: [0, 7]
[94] select * from student where major < Math and age > 25
Recnos: [1, 2, 9]
[95] select * from employee where dep = CS and salary > 150000
Recnos: [6, 14]
[96] select * from employee where last = Jackson and year < 2015
Recnos: [8]
[97] select * from employee where last = Johnson and year >=2014
Recnos: [2, 10, 11, 12, 3]


//.................
//:OR            :
//.................
[98] select * from student where fname = Flo or lname = Jackson
Recnos: [2, 3, 0]
[99] select * from student where age >=40  or company = Verizon
Recnos: [5, 8, 2, 9]
[100] select * from employee where first = Bo or last = Johnson
Recnos: [2, 3, 10, 11, 12, 6, 8]
[101] select * from employee where year >= 2015 or dep = CS
Recnos: [0, 5, 6, 14, 13, 1, 7, 9, 3]


//.................
//:OR AND         :
//.................
[102] select * from student where fname = Flo or major = CS and age <= 23
Recnos: [0, 7, 3]
[103] select * from student where lname = Jackson or age < 23 and company > Uber
Recnos: [8, 2, 3]
[104] select * from employee where last = "Van Gogh" or last = Jackson and salary >= 165000
Recnos: [7, 9, 13, 14, 15]


//.................
//:AND OR AND     :
//.................

[105] select * from student where age <30 and major=CS or major = Physics and company = Amazon
Recnos: [4, 0, 7, 1]
[106] select * from student where age <=40 and company=Uber or major = CS and company = Google
Recnos: [0, 6, 2]
[107] select * from employee where dep = CS and salary >= 160000 or year > 2014 and last = "Van Gogh"
Recnos: [13, 14, 6]


//.................
//:OR AND OR      :
//.................

[108] select * from student where lname = Yang or major = CS and age < 23 or company = Google
Recnos: [0, 3, 7, 1]
[109] select * from student where major = Physics or major = Math and company = Google or lname = Jackson
Recnos: [2, 3, 4, 6]
[110] select * from employee where dep = CS or year >2014 and year < 2018 or salary >= 265000
Recnos: [13, 14, 1, 7, 9, 0, 5, 6]










[       OK ] TEST_SQL.TestFinal21 (2614 ms)
[ RUN      ] TEST_SQL.TestFinal19
//****************************************************************************
//              CREATE TABLES AND INSERT RECORDS
//****************************************************************************


[0] make table employee fields  last,           first,                  dep,            salary,         year
Recnos: []
[1] insert into employee values Blow,           Joe,                    CS,                     100000,         2018
Recnos: []
[2] insert into employee values Blow,           JoAnn,                  Physics,        200000,         2016
Recnos: []
[3] insert into employee values Johnson,        Jack,                   HR,             150000,         2014
Recnos: []
[4] insert into employee values Johnson,        "Jimmy",                Chemistry,      140000,         2018
Recnos: []
[5] insert into employee values Yao,            Jimmy,                  Math,           145000,         2014
Recnos: []
[6] insert into employee values "Yao",          Flo,                    CS,                     147000,         2012
Recnos: []
[7] insert into employee values Yang,           Bo,                     CS,                     160000,         2013
Recnos: []
[8] insert into employee values Jackson,        "Flo",                  Math,           165000,         2017
Recnos: []
[9] insert into employee values Jackson,        Bo,                             Chemistry,      130000,         2011
Recnos: []
[10] insert into employee values "Jackson",     Billy,                  Math,           170000,         2017
Recnos: []
[11] insert into employee values Johnson,       "Mary Ann",     Math,           165000,         2014
Recnos: []
[12] insert into employee values Johnson,       "Billy Bob",    Physics,        142000,         2014
Recnos: []
[13] insert into employee values Johnson,       Billy,                  "Phys Ed",      102000,         2014
Recnos: []
[14] insert into employee values "Van Gogh",    Vincent,                Art,            240000,         2015
Recnos: []
[15] insert into employee values "Van Gogh",    Vincent,                CS,                     245000,         2015
Recnos: []
[16] insert into employee values "Van Gogh",    "Jim Bob",              "Phys Ed",      230000,         2010
Recnos: []
[17] select * from employee
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]

[18] make table student fields fname, lname, major, age, company
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[19] insert into student values Flo,                    Yao,            CS,                             20,     Google
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[20] insert into student values Bo,                             Yang,           CS,                             28,             Microsoft
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[21] insert into student values "Sammuel L.",   Jackson,        CS,                             40,             Uber
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[22] insert into student values "Flo",                  "Jackson",      Math,                           21,             Google
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[23] insert into student values "Greg",                         "Pearson",      Physics,                        20,             Amazon
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[24] insert into student values "Jim Bob",              Smith,          Math,                           23,             Verizon
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[25] insert into student values Calvin,                         Woo,            Physics,                        22,             Uber
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[26] insert into student values "Anna Grace",   "Del Rio",      CS,                                     22,             USAF
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[27] insert into student values "Teresa Mae",   Gowers,         Chemistry,                      22,             Verizon
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[28] insert into student values Alex,                   Smith,          "Gender Studies",       53,             Amazon
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
[29] select * from student
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]


//****************************************************************************
//              SIMPLE SELECT:
//****************************************************************************

[30] select * from student
Recnos: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

//------- simple strings -------------------
[31] select * from student where lname = Jackson
Recnos: [2, 3]
[32] select * from student where major = CS
Recnos: [0, 1, 2, 7]
[33] select * from student where company = Uber
Recnos: [2, 6]

//----- quoted strings ---------------------
[34] select * from student where lname = "Del Rio"
Recnos: [7]
[35] select * from student where fname = "Jim Bob"
Recnos: [5]
[36] select * from student where fname = "Anna Grace"
Recnos: [7]
[37] select * from student where fname = "Teresa Mae"
Recnos: [8]

//-------- non-existing string ------------------
[38] select * from student where lname = "Does Not Exist"
Recnos: []

//****************************************************************************
//              RELATIONAL OPERATORS:
//****************************************************************************

//.................
//:Greater Than   :
//.................
[39] select * from student where lname > Yang
Recnos: [0]
[40] select * from student where major > Math
Recnos: [4, 6]
[41] select * from student where fname > "Sammuel L."
Recnos: [8]
[42] select * from employee where salary > 200000
Recnos: [15, 13, 14]
[43] select * from employee where dep > Chemistry
Recnos: [2, 4, 7, 9, 10, 12, 15, 1, 11]
[44] select * from employee where last > Jackson
Recnos: [2, 3, 10, 11, 12, 13, 14, 15, 6, 4, 5]
[45] select * from employee where first > "Billy Bob"
Recnos: [6, 8, 5, 7, 2, 15, 3, 4, 1, 0, 10, 13, 14]


//. . . . . . . . . . . . . (Greater Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .
[46] select * from student where age > 50
Recnos: [9]
[47] select * from student where age > 35
Recnos: [2, 9]
[48] select * from student where fname > T
Recnos: [8]
[49] select * from employee where salary > 130000
Recnos: [3, 11, 4, 5, 2, 6, 7, 10, 9, 1, 15, 13, 14]
[50] select * from employee where  year > 2009
Recnos: [15, 8, 5, 6, 2, 4, 10, 11, 12, 13, 14, 1, 7, 9, 0, 3]

//. . . . . . . . . . . . . (Greater than: last item) . . . . . . . . . . . . . . . . . .
[51] select * from student where age  > 53
Recnos: []
[52] select * from student where lname > Yao
Recnos: []
[53] select * from student where fname > "Teresa Mae"
Recnos: []
[54] select * from employee where last > "Van Gogh"
Recnos: [6, 4, 5]
[55] select * from employee where first > Vincent
Recnos: []
[56] select * from employee where salary > 260000
Recnos: []

//. . . . . . . . . . . . . (Greater Than: Passed last item) . . . . . . . . . . . . . . . . . . . . .
[57] select * from student where age > 54
Recnos: []
[58] select * from student where lname > Zoolander
Recnos: []
[59] select * from employee where last > Zoolaner
Recnos: []
[60] select * from employee where first > Xu
Recnos: []

//.................
//:Greater Equal  :
//.................
[61] select * from student where lname >= Yang
Recnos: [1, 0]
[62] select * from student where fname >= "Sammuel L."
Recnos: [2, 8]
[63] select * from student where age >= 40
Recnos: [2, 9]
//. . . . . .  (Greater Equal non-existing: ) . . . . . . . . . . .
[64] select * from employee where last >= Jack
Recnos: [7, 8, 9, 2, 3, 10, 11, 12, 13, 14, 15, 6, 4, 5]
[65] select * from employee where first >= Bill
Recnos: [9, 12, 11, 6, 8, 5, 7, 2, 15, 3, 4, 1, 0, 10, 13, 14]
[66] select * from employee where salary >= 235000
Recnos: [13, 14]


//.................
//:Less Than      :
//.................


//. . . . . . . . . . . . . (Less Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .
[67] select * from student where lname < Jackson
Recnos: [7, 8]
[68] select * from student where major < Math
Recnos: [0, 1, 2, 7, 8, 9]
[69] select * from student where fname < "Jim Bob"
Recnos: [9, 7, 1, 6, 0, 3, 4]
[70] select * from employee where salary < 200000
Recnos: [0, 12, 8, 3, 11, 4, 5, 2, 6, 7, 10, 9]
[71] select * from employee where dep < CS
Recnos: [13]
[72] select * from employee where last < Jackson
Recnos: [0, 1]
[73] select * from employee where first < "Billy Bob"
Recnos: [9, 12]

//. . . . . . . . . . . . . (Less than: first item) . . . . . . . . . . . . . . . . . .
[74] select * from student where age  < 20
Recnos: []
[75] select * from student where lname < "Del Rio"
Recnos: []
[76] select * from student where fname < Alex
Recnos: []
[77] select * from employee where last < Blow
Recnos: []
[78] select * from employee where first < Billy
Recnos: []
[79] select * from employee where salary < 100000
Recnos: []


//. . . . . . . . . . . . . (Less Than: before first item) . . . . . . . . . . . . . . . . . . . . .

[80] select * from student where age  < 19
Recnos: []
[81] select * from student where lname < Adams
Recnos: []
[82] select * from student where fname < Adam
Recnos: []
[83] select * from employee where last < Alex
Recnos: []
[84] select * from employee where first < Avory
Recnos: []
[85] select * from employee where dep < Alchemy
Recnos: []


//.................
//:Less Equal     :
//.................

[86] select * from student where lname <= Smith
Recnos: [7, 8, 2, 3, 4, 5, 9]
[87] select * from student where fname <= Greg
Recnos: [9, 7, 1, 6, 0, 3, 4]
[88] select * from student where age <= 40
Recnos: [0, 4, 3, 6, 7, 8, 5, 1, 2]

//. . . . . .  (Less Equal non-existing: ) . . . . . . . . . . .
[89] select * from employee where last <= Peach
Recnos: [0, 1, 7, 8, 9, 2, 3, 10, 11, 12]
[90] select * from employee where first <= Gary
Recnos: [9, 12, 11, 6, 8, 5, 7]
[91] select * from employee where salary <= 23500
Recnos: [0, 12, 8, 3, 11, 4, 5, 2, 6, 7, 10, 9, 1, 15]

//****************************************************************************
//              LOGICAL OPERATORS
//****************************************************************************


//.................
//:AND            :
//.................

[92] select * from student where fname = "Flo" and lname = "Yao"
Recnos: [0]
[93] select * from student where major = "CS" and age < 25
Recnos: [0, 7]
[94] select * from student where major < Math and age > 25
Recnos: [1, 2, 9]
[95] select * from employee where dep = CS and salary > 150000
Recnos: [6, 14]
[96] select * from employee where last = Jackson and year < 2015
Recnos: [8]
[97] select * from employee where last = Johnson and year >=2014
Recnos: [2, 10, 11, 12, 3]


//.................
//:OR            :
//.................
[98] select * from student where fname = Flo or lname = Jackson
Recnos: [2, 3, 0]
[99] select * from student where age >=40  or company = Verizon
Recnos: [5, 8, 2, 9]
[100] select * from employee where first = Bo or last = Johnson
Recnos: [2, 3, 10, 11, 12, 6, 8]
[101] select * from employee where year >= 2015 or dep = CS
Recnos: [0, 5, 6, 14, 13, 1, 7, 9, 3]
[102] select * from employee where year >= 2020 or dep = CompSci
Recnos: []
[103] select * from employee where year < 2010 or dep = CS
Recnos: [0, 5, 6, 14]


//.................
//:OR AND         :
//.................
[104] select * from student where fname = Flo or major = CS and age <= 23
Recnos: [0, 7, 3]
[105] select * from employee where last = "Van Gogh" or last = Jackson and salary >= 165000
Recnos: [7, 9, 13, 14, 15]
[106] select * from student where lname = Jackson or age < 23 and company > Uber
Recnos: [8, 2, 3]
[107] select * from student where lname = Jackson or age > 23 and company > Uber
Recnos: [2, 3]
[108] select * from student where lname = Jackson or age > 73 and company > Uber
Recnos: [2, 3]
[109] select * from student where lname = "Jackson" or age > 73 and company > Uber
Recnos: [2, 3]
[110] select * from student where lname = "Solis" or age > 73 and company > Uber
Recnos: []
[111] select * from student where lname = "Solis" or age > 23 and company > Uber
Recnos: []


//.................
//:AND OR AND     :
//.................

[112] select * from student where age <30 and major=CS or major = Physics and company = Amazon
Recnos: [4, 0, 7, 1]
[113] select * from student where age <=40 and company=Uber or major = CS and company = Google
Recnos: [0, 6, 2]
[114] select * from employee where dep = CS and salary >= 160000 or year > 2014 and last = "Van Gogh"
Recnos: [13, 14, 6]
[115] select * from employee where dep = CS and salary >= 160000 or year > 2015 and last = "Van Gogh"
Recnos: [6, 14]


//.................
//:OR AND OR      :
//.................

[116] select * from student where lname = Yang or major = CS and age < 23 or company = Google
Recnos: [0, 3, 7, 1]
[117] select * from student where major = Physics or major = Math and company = Google or lname = Jackson
Recnos: [2, 3, 4, 6]
[118] select * from employee where dep = CS or year >2014 and year < 2018 or salary >= 240000
Recnos: [13, 14, 1, 7, 9, 0, 5, 6]
[119] select * from employee where dep = CS or year >2014 and year < 2018 or salary >= 242000
Recnos: [14, 13, 1, 7, 9, 0, 5, 6]
[120] select * from employee where dep = CS or year >2014 and year < 2018 or salary > 240000
Recnos: [14, 13, 1, 7, 9, 0, 5, 6]










[       OK ] TEST_SQL.TestFinal19 (2895 ms)
[----------] 3 tests from TEST_SQL (5913 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 1 test suite ran. (5913 ms total)
[  PASSED  ] 3 tests.
```
