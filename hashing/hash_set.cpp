#include <iostream>
#include <variant>
#include <vector>
#include <string>

using namespace std;

class HashSet : public HashTable {
public:
    HashSet(CollisionType collision_type, const vector<int>& params)
        : HashTable(collision_type, params), table(table_size) {}

    void insert(const string& key) override {
        if (find(key)) return;
        if (collision_type != Chain && size == table_size) {
            throw runtime_error("HashSet table full");
        }

        int k = calc_hash(key, params[0], table_size);
        if (table[k].index() == 0) { // nullptr
            if (collision_type == Chain) {
                table[k] = vector<string>{key};
            } else {
                table[k] = key;
            }
            size++;
        } else {
            if (collision_type == Chain) {
                if (holds_alternative<vector<string>>(table[k])) {
                    get<vector<string>>(table[k]).push_back(key);
                } else {
                    // Single string replaced with vector
                    string old_key = get<string>(table[k]);
                    table[k] = vector<string>{old_key, key};
                }
                size++;
            } else if (collision_type == Linear) {
                for (int i = 1; i < table_size; i++) {
                    int idx = (k + i) % table_size;
                    if (table[idx].index() == 0) {
                        table[idx] = key;
                        size++;
                        break;
                    }
                }
            } else if (collision_type == Double) {
                int step = double_hash(key);
                for (int i = 1; i < table_size; i++) {
                    int idx = (k + i * step) % table_size;
                    if (table[idx].index() == 0) {
                        table[idx] = key;
                        size++;
                        break;
                    }
                }
            }
        }
    }

    bool find(const string& key) const override {
        int k = calc_hash(key, params[0], table_size);
        if (table[k].index() == 1 && get<string>(table[k]) == key) {
            return true;
        }
        if (collision_type == Chain) {
            if (holds_alternative<vector<string>>(table[k])) {
                const vector<string>& chain = get<vector<string>>(table[k]);
                return find(chain.begin(), chain.end(), key) != chain.end();
            }
        } else if (collision_type == Linear) {
            for (int i = 1; i < table_size; i++) {
                int idx = (k + i) % table_size;
                if (table[idx].index() == 0) return false;
                if (holds_alternative<string>(table[idx]) && get<string>(table[idx]) == key)
                    return true;
            }
        } else if (collision_type == Double) {
            int step = double_hash(key);
            for (int i = 1; i < table_size; i++) {
                int idx = (k + i * step) % table_size;
                if (table[idx].index() == 0) return false;
                if (holds_alternative<string>(table[idx]) && get<string>(table[idx]) == key)
                    return true;
            }
        }
        return false;
    }

    string find(const string& key) const override {
        return ""; // Dummy for HashSet
    }

    double get_load() const override {
        return (double)size / table_size;
    }

    int get_slot(const string& key) const override {
        return calc_hash(key, params[0], table_size);
    }

    string to_string() const {
        string result;
        for (int i = 0; i < table_size; i++) {
            if (table[i].index() == 0) {
                result += "<EMPTY>";
            } else if (holds_alternative<string>(table[i])) {
                result += get<string>(table[i]);
            } else {
                const vector<string>& chain = get<vector<string>>(table[i]);
                for (size_t j = 0; j < chain.size(); j++) {
                    result += chain[j];
                    if (j != chain.size() - 1) result += " ; ";
                }
            }
            if (i != table_size - 1) result += " | ";
        }
        return result;
    }

private:
    vector<variant<nullptr_t, string, vector<string>>> table;
};
