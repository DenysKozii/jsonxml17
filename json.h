#ifndef LIBRARY_JSON_H
#define LIBRARY_JSON_H
using namespace std;

namespace P
{
    class JsonPair {
    private:
        string key;
        string value;
        string parentKey;
    public:
        string getKey() const {
            return key;
        }

        string getValue() const {
            return value;
        }

        string getParent() const {
            return parentKey;
        }
        void setKey(string key_) {
            key = move(key_);
        }

        void setValue(string value_)  {
             value = move(value_);
        }

        void setParent(string parentKey_)  {
             parentKey = move(parentKey_);
        }

        void readNextPair(std::istream &str) {
            string line;
            getline(str, line);
            string::size_type start = 0, end = 0, sep = 0;
            while ((sep = line.find(':', sep+1)) != string::npos) {
                start = line.find('"', 0);
                end = line.find('"', start + 1);
                key = string(&line[start+1], &line[end]);
                start = line.find('"', sep + 1);
                end = line.find('"', start + 1);
                value = string(&line[start+1], &line[end]);
            }
        }
    };

    istream inline &operator>>(istream &str, JsonPair &data) {
        data.readNextPair(str);
        return str;
    }

    class JsonIterator {
    public:

        JsonIterator(std::istream &str) : m_str(str.good() ? &str : NULL) { ++(*this); }

        JsonIterator() : m_str(NULL) {}

        JsonIterator &operator++() {
            if (m_str) { if (!((*m_str) >> m_row)) { m_str = NULL; }}
            return *this;
        }

        JsonIterator operator++(int) {
            JsonIterator tmp(*this);
            ++(*this);
            return tmp;
        }

        JsonPair const &operator*() const { return m_row; }

        JsonPair const *operator->() const { return &m_row; }

        bool operator==(JsonIterator const &rhs) {
            return ((this == &rhs) || ((this->m_str == NULL) && (rhs.m_str == NULL)));
        }

        bool operator!=(JsonIterator const &rhs) { return !((*this) == rhs); }

    private:
        std::istream *m_str;
        JsonPair m_row;
    };

    class JsonRange {
        std::istream &stream;
    public:
        JsonRange(std::istream &str)
                : stream(str) {}

        JsonIterator begin() const { return JsonIterator{stream}; }

        JsonIterator end() const { return JsonIterator{}; }
    };

    class Json
    {
        string filename;
    public:
        void create(string filename);
        void read_keys();
        void read(string key);
        void getPair();
        void add(JsonPair jsonPair);
        void delete_key(string key);
        void update(JsonPair jsonPair);
    };
}

#endif //LIBRARY_JSON_H