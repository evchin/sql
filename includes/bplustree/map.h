/*
 * Author: Evelyn Chin
 * Project: Map + Multimap
 * Project Purpose: A Map / Multimap Class built up from a BPlusTree class.
 * File Purpose: Map Interface. 
 */

#ifndef MAP_H
#define MAP_H

#include "bplustree.h"

template <typename K, typename V>
struct Pair
{
    K key;
    V value;

    Pair(const K& k=K(), const V& v=V()) : key(k), value(v) {}
    friend ostream& operator <<(ostream& outs, const Pair<K, V>& print_me)
    {
        outs << "(" << print_me.key << ", " << print_me.value << ")";
        return outs;
    }
    friend bool operator ==(const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key == rhs.key;
    }
    friend bool operator < (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key < rhs.key;
    }
    friend bool operator > (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key > rhs.key;
    }
    friend bool operator >= (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key >= rhs.key;
    }
    friend bool operator <= (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key <= rhs.key;
    }
    friend bool operator != (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key != rhs.key;
    }
    friend Pair<K, V> operator + (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        assert(lhs.key == rhs.key);
        return Pair<K, V>(lhs.key, lhs.value + rhs.value);
    }
};

template <typename K, typename V>
class Map
{
public:
    typedef BPlusTree<Pair<K, V> > map_base;
    class Iterator
    {
    public:
        friend class Map;
        
        // iterator constructor
        Iterator(typename map_base::Iterator it) : _it(it) {}

        // postfix increment overload
        Iterator operator ++(int unused)
        {
            Iterator temp(_it);
            _it++;
            return temp;
        }
        
        // prefix increment overload
        Iterator operator ++()
        {
            _it++;
            return *this;
        }
        
        // dereferencing operator
        Pair<K, V> operator *()
        {
            return *_it;
        }
        
        // returns if iterator is null
        bool null()
        {
            return _it.is_null();
        }

        // == operator
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
        {
            return lhs._it == rhs._it;
        }
        
        // != operator
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
        {
            return lhs._it != rhs._it;
        }

    private:
        typename map_base::Iterator _it;
    };

    Map(){}

    //  Iterators
    Iterator begin()
    {
        return Iterator(map.begin());
    }
    Iterator end()
    {
        return Iterator(map.end());
    }

    //  Capacity
    int size() const
    {
        return map.size();
    }
    bool empty() const
    {
        return map.empty();
    }

    //  Element Access
    V& operator[](const K& key)
    {
        Pair<K, V> pair(key);
        return map.get(pair).value;
    }
    V& at(const K& key)
    {
        Pair<K, V> pair(key);
        return map.get(pair).value;
    }
    const V& at(const K& key) const
    {
        Pair<K, V> pair(key);
        return map.get(pair).value;
    }

    //  Modifiers
    void insert(const K& k, const V& v)
    {
        map.insert(Pair<K, V>(k, v));
    }
    void erase(const K& key)
    {
        map.remove(Pair<K, V>(key));
    }
    void clear()
    {
        map.clear_tree();
    }
    V get(const K& key)
    {
        return map.get(Pair<K, V>(key)).value;
    }

    //  Operations:
    Iterator find(const K& key)
    {
        return map.find(Pair<K, V>(key));
    }
    bool contains(const Pair<K, V>& target) const
    {
        return map.contains(target);
    }
    bool is_valid()
    {
        return map.is_valid();
    }
    int count(const K& key)
    {
        if (map.contains(Pair<K, V>(key))) return 1;
        return 0;
    }
    Iterator lower_bound(const K& key)
    {
        return Iterator(map.lower_bound(key));
    }
    Iterator upper_bound(const K& key)
    {
        return Iterator(map.upper_bound(key));
    }
    // equal_range

    friend ostream& operator<<(ostream& outs, const Map<K, V>& print_me)
    {
        outs << print_me.map << endl;
        return outs;
    }

    void print_lookup()
    {
        int width = 25;
        cout << setw(width) << "KEY";
        cout << setw(width) << "VALUE" << endl;
        for (Iterator it = begin(); it != end(); it++)
        {
            cout << setw(width) << (*it).key;
            cout << setw(width) << (*it).value;
            cout << endl;
        }
    }

private:
    int key_count = 0; // TODO??
    BPlusTree<Pair<K, V> > map;
};

#endif // MAP_H