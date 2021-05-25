#ifndef LIBRARY_XML_H
#define LIBRARY_XML_H
using namespace std;

namespace P {
    class XmlPair {
    private:
        string key{};
        string value{};
        string parentKey{};
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

        void setValue(string value_) {
            value = move(value_);
        }

        void setParent(string parentKey_) {
            parentKey = move(parentKey_);
        }

        void readNextPair(std::istream &str) {
            string line;
            key = "";
            value = "";
            getline(str, line);
            string::size_type start = 0, start_value = 0, end = 0, sep = 0;
            start = line.find('<', 0);
            end = line.find('>', start + 1);
            start_value = line.find('>', 0);
            if (!line.substr(start_value+1, line.size()).empty()) {
                key = string(&line[start + 1], &line[end]);
                end = line.find('<', start_value + 1);
                value = string(&line[start_value + 1], &line[end]);
            }
        }
    };

    istream inline &operator>>(istream &str, XmlPair &data) {
        data.readNextPair(str);
        return str;
    }

    class XmlIterator {
    public:

        XmlIterator(std::istream &str) : m_str(str.good() ? &str : NULL) { ++(*this); }

        XmlIterator() : m_str(NULL) {}

        XmlIterator &operator++() {
            if (m_str) { if (!((*m_str) >> m_row)) { m_str = NULL; }}
            return *this;
        }

        XmlIterator operator++(int) {
            XmlIterator tmp(*this);
            ++(*this);
            return tmp;
        }

        XmlPair const &operator*() const { return m_row; }

        XmlPair const *operator->() const { return &m_row; }

        bool operator==(XmlIterator const &rhs) {
            return ((this == &rhs) || ((this->m_str == NULL) && (rhs.m_str == NULL)));
        }

        bool operator!=(XmlIterator const &rhs) { return !((*this) == rhs); }

    private:
        std::istream *m_str;
        XmlPair m_row;
    };

    class XmlRange {
        std::istream &stream;
    public:
        XmlRange(std::istream &str)
                : stream(str) {}

        XmlIterator begin() const { return XmlIterator{stream}; }

        XmlIterator end() const { return XmlIterator{}; }
    };

    class Xml {
    private:
        string filename;
    public:
        void create(string filename);

        void read_keys();

        void read(string key);

        void getPair();

        void add(XmlPair XmlPair);

        void delete_key(string key);

        void update(XmlPair XmlPair);
    };
}

#endif //LIBRARY_XML_H