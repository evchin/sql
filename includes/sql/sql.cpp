#include "sql.h"

SQL::SQL()
{
    ifstream f("sql.txt");
    string line;
    while (getline(f, line))
    {
        Table t(line);
        tables[line] = t;
    }
    f.close();
}

void SQL::batch(string file, bool verbose)
{
    ifstream f(file);
    Table t;
    string line;
    int i = 0;
    while (getline(f, line))
    {
        if (line.substr(0, 2) == "//" || line.find_first_not_of(' ' != string::npos)) 
        {
            cout << line << endl;
            continue;
        }
        cout << "[" << i++ << "] " << line << endl;
        t = command(line);
        if (verbose) cout << endl << t << endl;
        else cout << "Recnos: " << _select_recnos << endl;
    }
    f.close();
}

Table SQL::command(char* s)
{
    string str(s);
    return command(str);
}

Table SQL::command(const string& s)
{
    parser.set_string(s);
    mmap_ss ptree = parser.parse_tree();
    string command = ptree["command"][0];
    string name = ptree["table"][0];

    if (command == "create" || command == "make")
    {
        // write file to persisting sql.txt
        ofstream ofs("sql.txt", std::ios::app);
        if (!tables.contains(name))
        {
            string line = name + "\n";
            ofs.write(line.c_str(), line.length());
        }
        Table table(name, ptree["fields"]);
        tables[name] = table;
        return table;
    }
    else if (command == "insert")
    {
        // assert(tables.contains(name));
        tables[name].insert_into(ptree["values"]);
        return tables[name];
    }
    else if (command == "select")
    {
        // assert(tables.contains(name));
        Table out_table;
        bool where = ptree.contains("where");

        if (ptree["fields"][0] == "*")
        {
            Table table = tables[name];
            vectorstr fields = table.get_field_names();
            if (where) out_table = tables[name].select(fields, ptree["conditions"]);
            else out_table = tables[name].select_all();
        }
        else
        {
            if (where) out_table = tables[name].select(ptree["fields"], ptree["conditions"]);
            else out_table = tables[name].select_fields(ptree["fields"]);
        }

        _select_recnos = tables[name].select_recnos();
        return out_table;
    }

    cout << "Received invalid command: " + command;
    assert(false && "Received invalid command.");
    return Table();
}

vector<long> SQL::select_recnos()
{
    return _select_recnos;
}