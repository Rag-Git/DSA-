#include <iostream>
#include <variant>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class HashMap : public HashTable {
public:
    HashMap(CollisionType collision_type, const vector<int>& params)
        : HashTable(collision_type, params), table(table_size) {}

    void insert(const pair<string, string>& kv) override {
        const string& key = kv.first;
        if (find(key) != "") return;
        if (collision_type != Chain && size == table_size) {
            throw runtime_error("HashMap table full");
        }

        int k = calc_hash(key, params[0], table_size);

        if (table[k].index() == 0) {
            if (collision_type == Chain) {
                table[k] = vector<pair<string, string>>{kv};
            } else {
                table[k] = kv;
            }
            size++;
        } else {
            if (collision_type == Chain) {
                if (holds_alternative<vector<pair<string,string>>>(table[k])) {
                    get<vector<pair<string,string>>>(table[k]).push_back(kv);
                } else {
                    pair<string,string> old_kv = get<pair<string,string>>(table[k]);
                    table[k] = vector<pair<string,string>>{old_kv, kv};
                }
                size++;
            } else if (collision_type == Linear) {
                for (int i = 1; i < table_size; i++) {
                    int idx = (k + i) % table_size;
                    if (table[idx].index() == 0) {
                        table[idx] = kv;
                        size++;
                        break;
                    }
                }
            } else if (collision_type == Double) {
                int step = double_hash(key);
                for (int i = 1; i < table_size; i++) {
                    int idx = (k + i * step) % table_size;
                    if (table[idx].index() == 0) {
                        table[idx] = kv;
                        size++;
                        break;
                    }
                }
            }
        }
    }

    string find(const string& key) const override {
        int k = calc_hash(key, params[0], table_size);

        if (table[k].index() == 0) return "";

        if (table[k].index() == 2) { // vector
            const auto& vec = get<vector<pair<string,string>>>(table[k]);
            for (const auto& p : vec) {
                if (p.first == key) return p.second;
            }
            return "";
        }

        if (holds_alternative<pair<string,string>>(table[k])) {
            const auto& kv = get<pair<string,string>>(table[k]);
            if (kv.first == key) return kv.second;
        }

        if (collision_type == Linear) {
            for (int i = 1; i < table_size; i++) {
                int idx = (k + i) % table_size;
                if (table[idx].index() == 0) return "";
                if (holds_alternative<pair<string,string>>(table[idx])) {
                    const auto& kv = get<pair<string,string>>(table[idx]);
                    if (kv.first == key) return kv.second;
                }
            }
        } else if (collision_type == Double) {
            int step = double_hash(key);
            for (int i = 1; i < table_size; i++) {
                int idx = (k + i * step) % table_size;
                if (table[idx].index() == 0) return "";
                if (holds_alternative<pair<string,string>>(table[idx])) {
                    const auto& kv = get<pair<string,string>>(table[idx]);
                    if (kv.first == key) return kv.second;
                }
            }
        }

        return "";
    }

    bool find(const string& key) const override {
        return false; // dummy for HashSet compatibility
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
            } else if (holds_alternative<pair<string,string>>(table[i])) {
                const auto& kv = get<pair<string,string>>(table[i]);
                result += "(" + kv.first + " , " + kv.second + ")";
            } else {
                const auto& vec = get<vector<pair<string,string>>>(table[i]);
                for (size_t j = 0; j < vec.size(); j++) {
                    const auto& kv = vec[j];
                    result += "(" + kv.first + " , " + kv.second + ")";
                    if (j != vec.size() - 1) result += " ; ";
                }
            }
            if (i != table_size - 1) result += " | ";
        }
        return result;
    }

private:
    vector<variant<nullptr_t, pair<string,string>, vector<pair<string,string>>>> table;
};
