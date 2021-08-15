/*
 * Author: Evelyn Chin
 * Project: BPlusTree
 * Project Purpose: A BPlusTree class.
 * File Purpose: BPlusTree. 
 */

#ifndef B_PLUS_TREE_H
#define B_PLUS_TREE_H

#include "btree_array_funcs.h"
#include <string>
#include <stack>
#include <iomanip>
using namespace std;

template <typename T>
class BPlusTree
{
public:

    class Iterator
    {
    public:
        friend class BPlusTree;

        Iterator(BPlusTree<T>* _it=nullptr, int _key_ptr = 0) 
            : it(_it), key_ptr(_key_ptr){}

        // return btree's data[key_ptr]
        T operator *()
        {
            assert(it != nullptr && key_ptr < it->data_count);
            return it->data[key_ptr];
        }

        // postfix increment overload
        Iterator operator++(int un_used)
        {
            Iterator i(it, key_ptr);
            if (key_ptr >= it->data_count - 1) 
            {
                it = it->next;
                key_ptr = 0;
            }
            else key_ptr++;
            return i;
        }

        // prefix increment overload
        Iterator operator++()
        {
            if (key_ptr >= it->data_count - 1) 
            {
                it = it->next;
                key_ptr = 0;
            }
            else key_ptr++;
            return *this;
        }

        // == operator
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
        {
            if (lhs.it == nullptr && rhs.it == nullptr) return true;
            return lhs.it == rhs.it && lhs.key_ptr == rhs.key_ptr;
        }

        // != operator
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
        {
            if (lhs.it == nullptr && rhs.it == nullptr) return false;
            return lhs.it != rhs.it || lhs.key_ptr != rhs.key_ptr;
        }

        // print iterator
        void print_Iterator()
        {
            if (it)
            {
                cout << "iterator: ";
                print_array(it->data, it->data_count, key_ptr);
            }
            else cout << "iterator: null, key_ptr: "<<key_ptr<<endl;
        }
        
        // true if null
        bool is_null()
        {
            return !it;
        }

        // print iterator info
        void info()
        {
            cout<<endl<<"Iterator info:"<<endl;
            cout<<"key_ptr: "<<key_ptr<<endl;
            cout<<"it: "<<*it<<endl;
        }

    private:
        BPlusTree<T>* it = nullptr;
        int key_ptr;
    };

    // constructor
    BPlusTree(bool dups = false){}

    // constructor with array
    BPlusTree(const T* array, const int size)
    {
        for (int i = 0; i < size; i++) insert(array[i]);
    }

    // constructor with vector
    BPlusTree(const vector<T>& items)
    {
        for(T i : items) insert(i);
    }

    // copy constructor
    BPlusTree(const BPlusTree<T>& other)
    {
        copy_tree(other);
    }

    // deconstructor
    ~BPlusTree()
    {
        clear_tree();
    }

    // assignment operator
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS)
    {
        copy_tree(RHS);
        return *this;
    }

    // insert entry into the tree
    void insert(const T& entry)
    {
        loose_insert(entry);
        if (data_count > MAXIMUM)
        {
            // create a new node and copy all the contents of this root into it
            BPlusTree<T>* temp = new BPlusTree<T>(*this);
            // clear this root node
            clear_tree();
            // make the new node this root's only child (subset[0])
            subset[0] = temp;
            child_count = 1;
            // call fix_excess on this only subset (subset[0])
            fix_excess(0);
        }
    }
    
    // remove entry from the tree
    void remove(const T& entry)
    {
        if (empty()) return;
        loose_remove(entry);
        // shrink tree
        if (data_count == 0 && child_count == 1)
        {
            // point shrink_ptr at this root's only subset
            BPlusTree<T>* shrink_ptr = subset[0];
            // copy subset into the root
            copy_tree(*shrink_ptr);
            // delete shrink_ptr
            shrink_ptr->clear_tree();
            delete shrink_ptr;
        }
    }

    // clear this object (delete all nodes etc.)
    void clear_tree()
    {
        if (!is_leaf())
            for (int i = 0; i < child_count; i++)
                subset[i]->clear_tree();
        data_count = 0;
        child_count = 0;
        next = nullptr;
    }

    // copy other into this object
    void copy_tree(const BPlusTree<T>& other)
    {
        if (!empty()) clear_tree();
        stack<BPlusTree<T>*> s;
        s.push(nullptr);
        copy_tree(other, s);
    }

    // copy other into this object with stack that contains last leaf
    void copy_tree(const BPlusTree<T>& other, stack<BPlusTree<T>*>& s)
    {
        if (!other.is_leaf())
        {
            child_count = other.child_count;
            for (int i = 0; i < child_count; i++)
            {
                subset[i] = new BPlusTree<T>(dups_ok);
                subset[i]->copy_tree(*(other.subset[i]), s);
            }
        }
        else
        {
            // get and remove last leaf
            BPlusTree<T>* last_leaf = s.top();
            s.pop();
            // point last leaf's next to this if not nullptr
            if (last_leaf) last_leaf->next = this;
            // push this node as next last leaf
            s.push(this);
        }
        dups_ok = other.dups_ok;
        child_count = other.child_count;
        copy_array(data, other.data, data_count, other.data_count);   
    }
    
    // true if entry can be found in the tree
    bool contains(const T& entry) const 
    {
        if (data_count == 0) return false;
        int i = first_ge(data, data_count, entry);
        if (i != data_count && data[i] == entry) return true;
        if (is_leaf()) return false;
        return subset[i]->contains(entry);
    }

    // return a reference to entry in the tree
    T& get(const T& entry)
    {
        if (!contains(entry))
            insert(entry);
        return get_existing(entry);
    }

    // return a reference to entry in the tree
    const T& get(const T& entry) const
    {
        return get_existing(entry);
    }
    
    // return a reference to existing entry in the tree
    T& get_existing(const T& entry)
    {
        //assert that entry is not in the tree.
        assert(contains(entry));

        const bool debug = false;
        int i = first_ge(data, data_count, entry);
        bool found = i < data_count && data[i] == entry;

        // leaf
        if (is_leaf())
            if (found) return data[i];
            else assert(found && "get_existing was called with nonexistent entry");

        // not leaf
        if (found) return subset[i+1]->get(entry);
        else return subset[i]->get(entry);
    }

    // return a const reference to existing entry in the tree
    const T& get_existing(const T& entry) const
    {
        //assert that entry is not in the tree.
        assert(contains(entry));

        const bool debug = false;
        int i = first_ge(data, data_count, entry);
        bool found = i < data_count && data[i] == entry;

        // leaf
        if (is_leaf())
            if (found) return data[i];
            else assert(found && "get_existing was called with nonexistent entry");

        // not leaf
        if (found) return subset[i+1]->get(entry);
        else return subset[i]->get(entry);
    }

    // return an iterator to this key. NULL if not there.
    Iterator find(const T& entry)
    {
        Iterator i;
        if (data_count == 0) return i;
        int index = first_ge(data, data_count, entry);
        if (index != data_count && data[index] == entry) 
        {
            if (!is_leaf()) return subset[index + 1]->find(entry);
            Iterator out(this, index);
            return out;
        }
        if (is_leaf()) return i;
        return subset[index]->find(entry);
    }

    // return first that goes BEFORE key entry or next if there is no it >= entry
    Iterator lower_bound(const T& key)
    {
        // cout << "Calculating lower bound of " << key << " for bpt\n";
        // cout << *this << endl;
        Iterator i;
        if (data_count == 0) return i;
        int index = first_ge(data, data_count, key);
        // cout << "Index: " << index << endl;

        if (is_leaf())
        {
            if (index == data_count) 
            {
                Iterator out(this, index-1);
                return ++out;
            }
            return Iterator(this, index);
        }
        if (index == data_count || data[index] > key) return subset[index]->lower_bound(key);
        return subset[index + 1]->lower_bound(key);
    }
    
    // return first that goes AFTER key
    Iterator upper_bound(const T& key)
    {
        // cout << "Calculating upper bound of " << key << " for bpt\n";
        // cout << *this << endl;
        Iterator i;
        if (data_count == 0) return i;
        int index = first_ge(data, data_count, key);
        // cout << "Index: " << index << endl;

        if (is_leaf())
        {
            if (index == data_count) 
            {
                Iterator out (this, index-1);
                return ++out;
            }
            Iterator out (this, index);
            if (data[index] <= key) return ++out;
            return out;
        }
        if (index == data_count || data[index] > key) return subset[index]->upper_bound(key);
        return subset[index + 1]->upper_bound(key);
    }

    // count the number of elements in the tree
    int size() const
    {
        if (is_leaf()) return data_count;
        int n = 0;
        for (int i = 0; i < child_count; i++)
            n += subset[i]->size();
        return n;
    }
    
    // true if the tree is empty
    bool empty() const
    {
        return data_count == 0;
    }

    // print a readable version of the tree
    void print_tree(int level = 0, ostream &outs=cout) const 
    {
        // print last subtree if exists
        if (data_count < child_count) subset[data_count]->print_tree(level + 1);
        // print rest of items
        outs << string(level * 4, ' ') << "--" << endl;
        for (int i = data_count-1; i >= 0; i--)
        {
            outs << string(level * 4, ' ');
            outs  << data[i] << endl;
            if (i == 0) outs << string(level * 4, ' ') << "--" << endl;
            if (i < child_count) subset[i]->print_tree(level + 1);
        }
    }
    
    // << overload
    friend ostream& operator<<(ostream& outs, const BPlusTree<T>& print_me)
    {
        print_me.print_tree(0, outs);
        return outs;
    }

    // return if valid
    bool is_valid()
    {
        // check that every data[i] < data[i+1]
        for (int i = 0; i < data_count - 1; i++) 
            if (data[i] > data[i+1]) 
            {
                cout << "data[" << i << "]" << " > data[" <<i+1 << "]" << endl;
                cout << *this << endl;
                cout << in_order_vector() << endl;
                return false;
            }

        // if leaf, return true
        if (is_leaf()) return true;

        //data[data_count-1] must be less than equal to every subset[child_count-1]->data[ ]
        for (int i = 0; i < subset[child_count - 1]->data_count; i++)
            if (data[data_count-1] > subset[child_count-1]->data[i]) 
            {
                cout << "data[" << data_count - 1 << "]" << " > subset[" << child_count-1 << "]->data[" << i << "]" << endl;
                cout << *this << endl;
                cout << in_order_vector() << endl;
                return false;
            }
        
        //every data[i] is greater than or equal to every subset[i]->data[ ]
        for (int i = 0; i < data_count; i++)
            for (int j = 0; j < subset[i]->data_count; j++)
                if (data[i] < subset[i]->data[j]) 
                {
                    cout << "data[" << i << "]" << " < subset[" << i << "]->data[" << j << "]" << endl;
                    cout << *this << endl;
                    cout << in_order_vector() << endl;
                    return false;
                }

        //B+Tree: Every data[i] is equal to subset[i+1]->smallest
        for (int i = 0; i < data_count; i++)
        {
            T entry;
            subset[i+1]->get_smallest(entry);
            if (data[i] != entry) 
            {
                cout << "data[" << i << "]" << " != smallest entry " << entry << endl;
                cout << *this << endl;
                cout << in_order_vector() << endl;
                return false;
            }
        }

        //Recursively validate every subset[i]
        for (int i = 0; i < child_count; i++)
            if (!subset[i]->is_valid()) return false;

        return true;
    }

    // returns in order string
    string in_order() const
    {
        string out;
        if (is_leaf()) 
        {
            for (int i = 0; i < data_count; i++)
            {
                out += to_string(data[i]);
                out += "|";
            }
            return out;
        }
        for (int i = 0; i < data_count; i++)
        {
            out += subset[i]->in_order();
            out += to_string(data[i]);
            out += "|";
        }
        if (subset[data_count] != nullptr) out += subset[data_count]->in_order();
        return out;
    }
    
    // returns in order vector
    vector<T> in_order_vector()
    {
        vector<T> out;
        if (empty()) return out;
        out.reserve(size());
        for (Iterator i = begin(); i != end(); i++) out += *i;
        if (out.size() != size())
        {
            cout << "Vector: " << out << endl;
            cout << "Vector Size: " << out.size() << endl;
            cout << "SIZE: " << size() << endl;
            cout << "BT:\n" << *this << endl;
            assert(false);
        }
        return out;
    }

    // get iterator of smallest node
    Iterator begin()
    {
        return Iterator(get_smallest_node());
    }

    // get last iterator
    Iterator end()
    {
        return Iterator(nullptr);
    }

private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok = false;               //true if duplicate keys may be inserted
    int data_count = 0;                 //number of data elements
    T data[MAXIMUM + 1];                //holds the keys
    int child_count = 0;                //number of children
    BPlusTree<T>* subset[MAXIMUM + 2];  //subtrees
    BPlusTree<T>* next = nullptr;

    // true if this is a leaf node
    bool is_leaf() const
    {
        return child_count == 0;
    }

    // return a pointer to this key. NULL if not there.
    T* find_ptr(const T& entry)
    {
        if (data_count == 0) return nullptr;
        int i = first_ge(data, data_count, entry);
        if (i != data_count && data[i] == entry) return data + i;
        if (is_leaf()) return nullptr;
        return subset[i]->find_ptr(entry);
    }

    // insert element function - allows MAXIMUM+1 data elements in the root
    void loose_insert(const T& entry)
    {
        int i = first_ge(data, data_count, entry);
        bool found = (i < data_count && data[i] == entry);

        // if found
        if (found)
        {
            if (is_leaf()) data[i] = entry;
            else
            {
                subset[i+1]->loose_insert(entry);
                if (subset[i+1]->data_count > MAXIMUM) fix_excess(i+1);
            }
        }
        else
        {
            if (is_leaf()) ordered_insert(data, data_count, entry);
            else
            {
                subset[i]->loose_insert(entry);
                if (subset[i]->data_count > MAXIMUM) fix_excess(i);
            }
        }
    }

    // fix excess of data elements in child i
    void fix_excess(int i)
    {
        // add a new subset at i+1
        BPlusTree<T>* temp = new BPlusTree<T>(dups_ok);
        insert_item(subset, i+1, child_count, temp);
        // split data/subset[i] into data/subset[i+1]
        split(subset[i]->data, subset[i]->data_count, subset[i+1]->data, subset[i+1]->data_count);
        split(subset[i]->subset, subset[i]->child_count, subset[i+1]->subset, subset[i+1]->child_count);
        // detach the last data item of subset[i] and insert it into data
        T entry;
        detach_item(subset[i]->data, subset[i]->data_count, entry);
        ordered_insert(data, data_count, entry);

        //  B_PLUS_TREE
        if (subset[i]->is_leaf())
        {
            // transfer the middle entry to the right
            insert_item(subset[i+1]->data, 0, subset[i+1]->data_count, entry);
            // update next pointer of subset[i] to subset[i+1]
            subset[i+1]->next = subset[i]->next;
            subset[i]->next = subset[i+1];
        }
    }

    // remove element function - allows MINIMUM-1 data elements in the root
    void loose_remove(const T& entry)
    {
        int i = first_ge(data, data_count, entry);
        bool found = (i != data_count) && (data[i] == entry);
        T found_entry;

        if (is_leaf())
        {
            // if not found, do nothing
            if(!found) return;
            // else, delete the item
            else delete_item(data, i, data_count, found_entry);
        }
        else
        {
            if (!found)
            {
                subset[i]->loose_remove(entry);
                if (subset[i]->data_count < MINIMUM) fix_shortage(i);
            }
            else
            {
                assert(i < child_count-1);
                // loose remove recursive call 
                subset[i+1]->loose_remove(entry);
                T smallest;

                // if shortage
                if (subset[i+1]->data_count < MINIMUM) 
                {
                    BPlusTree<T>* smallest_tree = fix_shortage(i+1);
                    // search for entry in data and replace it with smallest
                    smallest_tree->get_smallest(smallest);
                    for (int j = 0; j < data_count; j++) 
                    {
                        if (data[j] == entry) 
                        {
                            data[j] = smallest;
                            return;
                        }
                    }
                    // else search for it in subset[i]->data and replace it
                    for (int j = 0; j < subset[i]->data_count; j++) 
                    {
                        if (subset[i]->data[j] == entry) 
                        {
                            subset[i]->data[j] = smallest;
                            return;
                        }
                    }
                }
                else 
                {
                    subset[i+1]->get_smallest(smallest);
                    data[i] = smallest;
                }
            }
        }
    }

     // fix shortage of data elements in child i and return the smallest key in this subtree
    BPlusTree<T>* fix_shortage(int i)
    {
        if ((i < child_count-1) && (subset[i+1]->data_count > MINIMUM)) transfer_left(i+1);
        else if ((i > 0) && (subset[i-1]->data_count > MINIMUM)) transfer_right(i-1);
        else if (i > 0) return merge_with_next_subset(i-1);
        else return merge_with_next_subset(i);
        return subset[i]->get_smallest_node();
    }
    
    // get tree with smallest node
    BPlusTree<T>* get_smallest_node()
    {
        // if not a leaf, recursive call smallest child 
        if (!is_leaf()) return subset[0]->get_smallest_node();
        return this;
    }
    
    // replace entry with the left_most leaf of this tree
    void get_smallest(T& entry)
    {
        // Keep looking in the first subtree (recursive) until you get to a leaf.
        BPlusTree<T>* left = get_smallest_node();
        // Then, replace entry with data[0] of the leaf node
        entry = left->data[0];
    }

    //entry := rightmost leaf
    void get_biggest(T& entry)
    {
        // Keep looking in the last subtree until you get to a leaf.
        BPlusTree<T>* right;
        while (!right->is_leaf()) right = right->subset[child_count - 1];
        // Then, replace entry with data[data_count - 1] of the leaf node
        entry = right->data[data_count - 1];
    }

    //remove the biggest child of this tree->entry
    void remove_biggest(T& entry)
    {
        get_biggest(entry);
        remove(entry);
    }
    
    // transfer one element LEFT from child i
    void transfer_left(int i)
    {
        // if not leaf, perform BTree rotate left
        if (!subset[i]->is_leaf())
        {
            T up;
            T down = data[i-1];
            delete_item(subset[i]->data, 0, subset[i]->data_count, up);
            // subset[i]->data[0] replaces data[i-1]
            data[i-1] = up;
            // data[i-1] is attached to subset[i-1]->data
            attach_item(subset[i-1]->data, subset[i-1]->data_count, down);

            // If needed, shift first subset of subset[i] to end of subset[i-1]
            if (subset[i]->child_count > subset[i]->data_count + 1)
            {
                BPlusTree<T>* child;
                delete_item(subset[i]->subset, 0, subset[i]->child_count, child);
                attach_item(subset[i-1]->subset, subset[i-1]->child_count, child);
            }
        }
        // else if leaf
        else
        {
            // transfer subset[i+1]->data[0] to end of subset[i]->data
            T entry;
            delete_item(subset[i]->data, 0, subset[i]->data_count, entry);
            attach_item(subset[i-1]->data, subset[i-1]->data_count, entry);

            // replace data[i] with [i+1]->data[0]
            data[i-1] = subset[i]->data[0];
        }
    }
    
    // transfer one element RIGHT from child i
    void transfer_right(int i)
    {
        // if not leaf, perform BPlusTree rotate right
        if (!subset[i]->is_leaf())
        {
            T up;
            T down = data[i];
            detach_item(subset[i]->data, subset[i]->data_count, up);
            // last item of subset[i]->data replaces data[i]
            data[i] = up;
            // data[i] inserted to the LEFT of subset[i+1]->data
            T smallest; 
            subset[i+1]->get_smallest(smallest);
            // insert_item(subset[i+1]->data, 0, subset[i+1]->data_count, down);
            insert_item(subset[i+1]->data, 0, subset[i+1]->data_count, smallest);
            
            // If needed, shift last subset of subset[i] to front of subset[i+1]
            if (subset[i]->child_count > subset[i]->data_count + 1)
            {
                BPlusTree<T>* child;
                delete_item(subset[i]->subset, subset[i]->child_count - 1, subset[i]->child_count, child);
                insert_item(subset[i+1]->subset, 0, subset[i+1]->child_count, child);
            }
        }
        // else if leaf
        else
        {
            // transfer last element of subset[i-1]->data to start of subset[i]->data
            T entry;
            delete_item(subset[i]->data, subset[i]->data_count - 1, subset[i]->data_count, entry);
            insert_item(subset[i+1]->data, 0, subset[i+1]->data_count, entry);

            // replace data[i] with entry
            data[i] = entry;
        }
    }

    // merge subset i with subset i+1
    BPlusTree<T>* merge_with_next_subset(int i)
    {
        // 1. remove data[i] from this object
        T entry;
        int smallest_index;
        BPlusTree<T>* smallest = subset[i];
        delete_item(data, i, data_count, entry);
        // 2. append it to child[i]->data if not leaf
        if (!subset[i]->is_leaf()) 
        {
            attach_item(subset[i]->data, subset[i]->data_count, entry);
            smallest_index = subset[i]->data_count;
        }
        // 3. Move all data items from subset[i+1]->data to subset[i]->data
        merge(subset[i]->data, subset[i]->data_count, subset[i+1]->data, subset[i+1]->data_count);
        // 4. Move all subset pointers from subset[i+1]->subset to subset[i]->subset
        merge(subset[i]->subset, subset[i]->child_count, subset[i+1]->subset, subset[i+1]->child_count);
        // 5. update next
        if (subset[i]->is_leaf()) subset[i]->next = subset[i+1]->next;
        // else set smallest tree to return
        else smallest = subset[i]->subset[smallest_index];
        // delete subset[i+1] (store in a temp ptr)
        BPlusTree<T>* child;
        delete_item(subset, i+1, child_count, child);
        // delete temp ptr
        delete child;
        return smallest;
    }
};

#endif // B_PLUS_TREE_H