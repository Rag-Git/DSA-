#include <string>
#include <vector>
#include <variant>
#include <stdexcept>
#include <algorithm>
#include <iostream>

using namespace std;

class HashTable {
public:
    enum CollisionType { Chain, Linear, Double };

    HashTable(CollisionType collision_type, const vector<int>& params)
        : collision_type(collision_type), params(params) {
        table_size = params.back();
        size = 0;
    }

    virtual ~HashTable() = default;

    virtual void insert(const string& key) = 0; // HashSet insert
    virtual void insert(const pair<string, string>& kv) = 0; // HashMap insert

    virtual bool find(const string& key) const = 0; // HashSet find
    virtual string find(const string& key) const = 0; // HashMap find

    virtual double get_load() const {
        return (double)size / table_size;
    }

    virtual int get_slot(const string& key) const {
        return calc_hash(key, params[0], table_size);
    }

protected:
    int number_for_latin_letter(char c) const {
        if (islower(c)) return c - 'a';
        else return c - 'A' + 26;
    }

    int calc_hash(const string& key, int z, int p) const {
        long long h = 0;
        for (char c : key) {
            h = (h * z + number_for_latin_letter(c)) % p;
        }
        return (int)h;
    }

    int double_hash(const string& key) const {
        return params[2] - calc_hash(key, params[1], params[2]);
    }

    CollisionType collision_type;
    vector<int> params;
    int table_size;
    int size;
};


// HashSet forward declaration (for completeness)
class HashSet;
class HashMap;
