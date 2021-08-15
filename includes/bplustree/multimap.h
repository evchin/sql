/*
 * Author: Evelyn Chin
 * Project: Map + Multimap
 * Project Purpose: A Map / Multimap Class built up from a BPlusTree class.
 * File Purpose: Multimap Interface. 
 */

#ifndef MULTIMAP_H
#define MULTIMAP_H

#include "bplustree.h"

template <typename K, typename V>
struct MPair
{
    K key;
    vector<V> value_list;

    MPair(const K& k=K()) : key(k) {}
    MPair(const K& k, const V& v) : key(k)
    {
        value_list += v;
    }
    MPair(const K& k, const vector<V>& vlist) : key(k), value_list(vlist) {}
    MPair& operator+=(const V& value)
    {
        value_list += value;
        return *this;
    }
    MPair& operator+=(const vector<V>& values)
    {
        value_list += values;
        return *this;
    }

    friend ostream& operator <<(ostream& outs, const MPair<K, V>& print_me)
    {
        outs << "(" << print_me.key << ", " << print_me.value_list << ")";
        return outs;
    }
    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key == rhs.key;
    }
    friend bool operator !=(const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key != rhs.key;
    }
    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key < rhs.key;
    }
    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key <= rhs.key;
    }
    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key > rhs.key;
    }
    friend bool operator >= (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key >= rhs.key;
    }
    friend MPair<K, V> operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        assert(lhs.key == rhs.key);
        return MPair<K, V>(lhs.key, lhs.value + rhs.value);
    }
};

template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator
    {
    public:
        friend class MMap;
        Iterator(typename map_base::Iterator it) : _it(it) {}
        bool null()
        {
            return _it.is_null();
        }
        Iterator operator ++(int unused)
        {
            Iterator temp(_it);
            _it++;
            return temp;
        }
        Iterator operator ++()
        {
            _it++;
            return *this;
        }
        MPair<K, V> operator *()
        {
            return *_it;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
        {
            return lhs._it == rhs._it;
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
        {
            return lhs._it != rhs._it;
        }
    private:
        typename map_base::Iterator _it;
    };

    MMap(){}

    //  Iterators
    Iterator begin()
    {
        return Iterator(mmap.begin());
    }
    Iterator end()
    {
        return Iterator(mmap.end());
    }

    //  Capacity
    int size() const
    {
        return mmap.size();
    }
    bool empty() const
    {
        return mmap.empty();
    }

    //  Element Access
    const vector<V>& operator[](const K& key) const
    {
        MPair<K, V> pair(key);
        return mmap.get(pair).value_list;
    }
    vector<V>& operator[](const K& key)
    {
        MPair<K, V> pair(key);
        return mmap.get(pair).value_list;
    }

    //  Modifiers
    void insert(const K& k, const V& v)
    {
        MPair<K, V> pair(k, v);
        Iterator it(mmap.find(pair));
        if (!it.null()) get(k) += v;
        else mmap.insert(pair);
    }
    void erase(const K& key)
    {
        mmap.remove(MPair<K, V>(key));
    }
    void clear()
    {
        mmap.clear_tree();
    }

    //  Operations:
    bool contains(const K& key) const
    {
        return mmap.contains(MPair<K, V>(key));
    }
    vector<V>& get(const K& key)
    {
        return mmap.get(MPair<K, V>(key)).value_list;
    }
    Iterator find(const K& key)
    {
        return mmap.find(MPair<K, V>(key));
    }
    int count(const K& key)
    {
        Iterator it(mmap.find(MPair<K,V>(key)));
        if (it._it == nullptr) return 0;
        return (*it).value_list.size();
    }
    bool is_valid()
    {
        return mmap.is_valid();
    }
    Iterator lower_bound(const K& key)
    {
        return Iterator(mmap.lower_bound(key));
    }
    Iterator upper_bound(const K& key)
    {
        return Iterator(mmap.upper_bound(key));
    }
    //    equal_range

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me)
    {
        outs<<print_me.mmap<<endl;
        return outs;
    }

    void print_lookup()
    {
        int width = 10;
        for (Iterator it = begin(); it != end(); it++)
        {
            cout << setw(width) << (*it).key << " : ";
            cout << (*it).value_list << endl;
        }
    }

private:
    BPlusTree<MPair<K, V> > mmap;
};

#endif // MULTIMAP_H