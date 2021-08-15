#include "table.h"

int serial = 1;

Table::Table(){}

Table::Table(string table) : name(table)
{
    // open binary file
    fstream f;
    string file_name = name + ".bin";
    assert(file_exists(file_name.c_str()));
    open_fileRW(f, file_name.c_str());

    // set up field_names and indices
    field_names = get_fields(table);
    for (int i = 0; i < field_names.size(); i++) 
    {
        indices += MMap<string, long>();
        field_name_indices[field_names[i]] = i;
    }

    // read file
    FileRecord fr;
    int i = 0;
    long bytes = fr.read(f, i);
    while (bytes > 0)
    {
        vectorstr data = fr.to_vectorstr();
        for (int field = 0; field < data.size(); field++)
            indices[field].insert(data[field], i);
        bytes = fr.read(f, ++i);
    }

    // close file
    f.close();
}

Table::Table(string table, vectorstr fields) : name(table)
{
    // create binary file
    fstream f;
    fstream fields_f;
    string file_name = name + ".bin";
    string fields_file_name = name + "_fields.bin";
    open_fileW(f, file_name.c_str());
    open_fileW(fields_f, fields_file_name.c_str());

    // create indices
    for (int i = 0; i < fields.size(); i++)
    {
        string field = fields[i];
        field_names += field;
        field_name_indices[field] = i;
        indices += MMap<string, long>();
    }

    // write field names to file
    FileRecord fr(fields);
    long recno = fr.write(fields_f);

    // close file
    f.close();
    fields_f.close();
}

Table::Table(string table, vector<long> recnos) : _select_recnos(recnos)
{
    // open original files
    fstream original_f;
    string original_file_name = table + ".bin";
    open_fileRW(original_f, original_file_name.c_str());

    // open derived files
    name = "_select_table_" + to_string(serial++);
    fstream f;
    fstream fields_f;
    string file_name = name + ".bin";
    string fields_file_name = name + "_fields.bin";
    open_fileW(f, file_name.c_str());
    open_fileW(fields_f, fields_file_name.c_str());

    // read fields from original + create indices + write fields to new
    FileRecord fr;
    field_names = get_fields(table);
    for (int i = 0; i < field_names.size(); i++) 
    {
        field_name_indices[field_names[i]] = i;
        indices += MMap<string, long>();
    }
    long recno = fr.write(fields_f);

    // read in values
    for (int recno : recnos)
    {
        long bytes = fr.read(original_f, recno);
        assert (bytes != 0);
        insert_into(fr.to_vectorstr());
    }

    // close file
    original_f.close();
    f.close();
    fields_f.close();
}

void Table::insert_into(vectorstr v)
{
    // open file
    fstream f;
    string file_name = name + ".bin";
    open_fileRW(f, file_name.c_str());

    // write record into the file
    FileRecord fr(v);
    long recno = fr.write(f);

    // insert field values with recno into mmap
    for (int i = 0; i < v.size(); i++)
        indices[i].insert(v[i], recno);


    // close file
    f.close();
}

Table Table::select(vectorstr fields, string field, string op, string value)
{
    // cout << "SELECT CONDITION: " << field << op << value << endl;
    // get field's mmap
    MMap<string, long> m = indices[field_name_indices[field]];

    // get records
    _select_recnos.clear();
    if (op == "=") 
    {
        _select_recnos = m[value];
    }
    else if (op == "<")
    {
        for (MMap<string, long>::Iterator it = m.begin(); it != m.end() && *it < value; it++)
            _select_recnos += (*it).value_list;
    }
    else if (op == ">")
    {
        for (MMap<string, long>::Iterator it = m.upper_bound(value); it != m.end(); it++)
            _select_recnos += (*it).value_list;
    }
    else if (op == "<=")
    {
        for (MMap<string, long>::Iterator it = m.begin(); it != m.end() && *it <= value; it++)
            _select_recnos += (*it).value_list;
    }
    else if (op == ">=")
    {
        for (MMap<string, long>::Iterator it = m.lower_bound(value); it != m.end(); it++)
            _select_recnos += (*it).value_list;
    }

    // open file
    fstream f;
    string file_name = name + ".bin";
    open_fileRW(f, file_name.c_str());

    // get field indices
    vector<int> field_indices;
    for (string field : fields)
        field_indices += field_name_indices[field];

    // read + insert records into table
    Table t("_select_table_" + to_string(serial++), fields);
    FileRecord fr;
    t._select_recnos = _select_recnos;

    for (int recno : _select_recnos)
    {
        long bytes = fr.read(f, recno);
        assert (bytes != 0);

        // filter out unnecessary fields
        vectorstr insert;
        vectorstr fr_vector = fr.to_vectorstr();
        for (int index : field_indices) insert += fr_vector[index];
        t.insert_into(insert);
    }

    // close file
    f.close();
    return t;
}

Table Table::select(vectorstr fields, Queue<Token*> q)
{
    Stack<Token*> values;
    Stack<Table> tables;

    // Queue<Token*> q2(q);
    // while (!q2.empty()) cout << *(q2.pop()) << endl;

    while (!q.empty())
    {
        Token* t = q.pop();
        if (t->type() == SYMBOL) values.push(t);
        else if (t->type() == RELATIONAL)
        {
            assert(values.size() > 1 && "there are less than 2 values in the stack.");
            Token* value = values.pop();
            Token* field = values.pop();
            // cout << "VALUE: " << *value << endl;
            // cout << "FIELD: " << *field << endl;
            Table table = select(fields, field->token_str(), t->token_str(), value->token_str());
            // cout << "SELECTED TABLE: " << table << endl;
            tables.push(table);
        }
        else if (t->type() == AND || t->type() == OR)
        {
            assert(tables.size() > 1 && "there are less than 2 tables in the stack.");
            vector<long> v1 = tables.pop().select_recnos();
            vector<long> v2 = tables.pop().select_recnos();
            // cout << "t: " << t->type_string() << endl;
            // cout << "v1: " << v1 << endl;
            // cout << "v2: " << v2 << endl;

            if (t->type() == AND) _select_recnos = vector_intersection(v1, v2);
            else if (t->type() == OR) _select_recnos = vector_union(v1, v2);
            Table t = Table(name, _select_recnos);
            // cout << "SELECTED TABLE: " << t << endl;
            tables.push(t);
        }
    }

    Table t = tables.pop().select_fields(fields);
    return t;
}

Table Table::select(vectorstr fields, vectorstr conditions)
{
    Queue<Token*> q = infix_to_postfix(conditions);
    return select(fields, q);
}

Table Table::select_all()
{
    return select_fields(field_names);
}

Table Table::select_fields(vectorstr fields)
{
    Table t("_select_table_" + to_string(serial++), fields);
    _select_recnos.clear();

    // get indices to needed fields 
    vector<int> field_indices;
    for (string field : fields)
        field_indices += field_name_indices[field];

    // read from file
    fstream f;
    string file_name = name + ".bin";
    open_fileRW(f, file_name.c_str());

    FileRecord fr;
    int i = 0;
    long bytes = fr.read(f, i);
    while (bytes != 0)
    {
        _select_recnos += (long)i;
        vectorstr v;
        vectorstr original = fr.to_vectorstr();
        for (int index : field_indices) v += original[index];
        t.insert_into(v);
        bytes = fr.read(f, ++i);
    }

    // close files
    f.close();
    return t;
}

vector<long> Table::select_recnos()
{
    return _select_recnos;
}

vectorstr Table::get_field_names()
{
    return field_names;
}

ostream& operator<<(ostream& os, const Table& t)
{
    // open binary file
    fstream f;
    stringstream ss;
    string file_name = t.name + ".bin";
    open_fileRW(f, file_name.c_str());

    // read + print file
    FileRecord fr;
    int i = 0;
    long bytes = fr.read(f, i);
    while (bytes > 0)
    {
        ss << setw(width) << i++;
        vectorstr v = fr.to_vectorstr();
        for (string s : v) ss << setw(width) << s;
        ss << endl;
        bytes = fr.read(f, i);
    }

    // print header
    os << "Table Name: " << t.name << endl;
    os << "Records: " << i << endl;
    os << setw(width) << "record";
    for (string field : t.field_names)
        os << setw(width) << field;
    os << endl;
    os << ss.str() << endl;

    // close file
    f.close();
    return os;
}

Queue<Token*> Table::infix_to_postfix(vectorstr infix)
{
    Stack<Token*> stack;
    Queue<Token*> queue;

    for (string token : infix)
    {
        // cout << "TOKEN: " << token << endl;

        if (keywords.contains(token))
        {
            Token* t = new Token(token, keywords[token]);
            // cout << "TOKEN TYPE: " << t->type_string() << endl;
            // if (!stack.empty()) cout << "STACK TOP: " << stack.top()->type_string() << endl;

            if (t->type() == START_BRACKET) stack.push(t);
            else if (t->type() == END_BRACKET)
            {
                while (stack.top()->type() != START_BRACKET)
                    queue.push(stack.pop());
                stack.pop();
            }
            else if (!stack.empty() && stack.top()->type() < t->type())
            {
                while (!stack.empty() && stack.top()->type() < t->type())
                    queue.push(stack.pop());
                stack.push(t);
            }
            else stack.push(t);
        }
        else
        {
            Token* t = new Token(token, SYMBOL);
            queue.push(t);
        }

        // cout << "STACK:" << endl;
        // Stack<Token*> s2(stack);
        // while (!s2.empty()) cout << *(s2.pop()) << " ";
        // cout << endl;
        // cout << "QUEUE:" << endl;
        // Queue<Token*> q2(queue);
        // while (!q2.empty()) cout << *(q2.pop()) << " ";
        // cout << endl << endl;
    }
    while (!stack.empty()) queue.push(stack.pop());
    return queue;
}

vectorstr Table::get_fields(string table)
{
    // open fields file
    fstream fields_f;
    string fields_file_name = table + "_fields.bin";
    assert(file_exists(fields_file_name.c_str()));    
    open_fileRW(fields_f, fields_file_name.c_str());

    // read from file
    FileRecord fr;
    int i = 0;
    long bytes = fr.read(fields_f, i);

    // close and return fields
    fields_f.close();
    return fr.to_vectorstr();
}