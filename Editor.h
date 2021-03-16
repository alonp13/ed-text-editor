#include <iostream>
#include "Document.h"
using namespace std;

class Editor 
{
    private:
        string m_doc_name;
        Document m_doc;
        vector<string> getText();

    public:
        Editor(): m_doc() {};
        Editor(string doc_name);
        void loop();

};  