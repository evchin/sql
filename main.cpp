#include "includes/sql/sql.h"

int main(int argv, char** argc) 
{
    SQL sql;
    // sql.batch("final21.txt");
    // sql.batch("sample.txt");
    char all[300] = "select * from student";
    cout << sql.command(all) << endl;

    char command[300] = "select * from student where age > 35";
    cout << command << endl;
    cout << sql.command(command) << endl;

    char command2[300] = "select * from student where major < Math and age > 25";
    cout << command2 << endl;
    cout << sql.command(command2) << endl;

    // char command[300] = "select * from student where lname = Yang or major = CS and age < 23 or lname = Jackson";
    // Table table("student");
    // Parser p(command);
    // mmap_ss ptree = p.parse_tree();
    // ptree.print_lookup();
    // cout << table << endl << endl;

    // cout << table.select(table.get_field_names(), {"lname", "=", "Yang", "or", "major", "=", "CS", "and", "age", "<", "23", "or", "lname", "=", "Jackson"});
    // cout << table.select(table.get_field_names(), "age", "<=", "23");

    // table.select(table.get_field_names());
    // //.................
    //:OR AND OR      :
    //.................
    // select * from student where lname = Yang or major = CS and age < 23 or lname = Jackson
}
