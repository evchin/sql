#include "file_record.h"

// write record to file
long FileRecord::write(fstream &outs)
{
    //r.write(f); //take the Record r and write it into file f and return the record number of this Record
    outs.seekg(0, outs.end);    // write to the end of the file.
    long pos = outs.tellp();    // retrieves the current position of the file pointer
    outs.write(_record, sizeof(_record));
    return pos/sizeof(_record);  //record number
}

// read record from file
long FileRecord::read(fstream &ins, long recno)
{
    long pos = recno * sizeof(_record);
    ins.seekg(pos, ios_base::beg);
    ins.read(_record, sizeof(_record));
    _record[ins.gcount()] = '\0';
    return ins.gcount();
}

// return current stored data as vectorstr
vector<string> FileRecord::to_vectorstr()
{
    vector<string> v;
    string s = "";
    for (int i = 0; i < MAX; i++)
    {
        char c = _record[i];
        if (c == ',')
        {
            v += s;     // add string
            s = "";     // reset string
            i++;        // next valid char
        }
        else if (c == '\0')
        {
            v += s;
            break;
        }
        else s += c;
    }
    return v;
}

// print
ostream& operator<<(ostream& outs, const FileRecord& r)
{
    outs<<r._record;
    return outs;
}