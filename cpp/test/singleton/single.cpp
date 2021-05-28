#include <iostream>

using namespace std;

class Single {
public:
    ~Single() { cout << "~Single" << endl; }
    static Single *getInstance() {
        if(m_instance == NULL) {
            m_instance = new Single();
        }
        return m_instance;
    }
public:
    class Garbo {
    public:
        ~Garbo() {
            if (Single::m_instance != NULL)
                delete Single::m_instance;
        }
        static Garbo garbo;
    };
private:
    static Single *m_instance;
    Single() { cout << "Single" << endl;}
};


Single* Single::m_instance = NULL;
Single::Garbo Single::Garbo::garbo;

int main() {
    Single *pSingl = Single::getInstance();
    return 0;
}
