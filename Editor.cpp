#include "Editor.h"

Editor::Editor(string doc_name) : m_doc_name(doc_name), m_doc(doc_name)
{
    m_doc.printDoc(); // DEBUG
}

void Editor::loop()
{
    string input;
    while(getline(cin,input))
    {
        if (input == "q")
        {
            break;
        }

        if(input == "$")
        {
            m_doc.moveToEnd();
            continue;
        }

        if(input == "j")
        {
            m_doc.concatNextLine();
            continue;
        }

        if(input == "a")
        {
            vector<string> text_inserted = getText();
            m_doc.addTextAfter(text_inserted);
            continue;
        }

        if(input == "d")
        {
            m_doc.removeCurrentLine();
            continue;
        } 

        if(input == "i")
        {
            vector<string> text_inserted = getText();
            m_doc.addTextBefore(text_inserted);
            continue;
        }

        if(input == "c")
        {
            vector<string> text_inserted = getText();
            m_doc.replaceToText(text_inserted);
            continue;
        }

        int num = 0;
        try {
            num = stoi(input);
            cout << "NUMBER " << num << endl; //DEBUG

            if(input.at(0) == '+' || input.at(0) == '-')
            {
                cout << "MOVE CURSOR " << num << endl; //DEBUG
                m_doc.moveCursorForward(num);
            } else {
                cout << "MOVE TO LINE " << num << endl; //DEBUG
                m_doc.moveToLine(num);
            }

        } catch (...) {
            cout << "?" << endl;
        }

    }

    cout << "------------" << endl; //DEBUG
    m_doc.printDoc(); //DEBUG
}

vector<string> Editor::getText()
{
    vector<string> res;
    

    cout << "ENTERED getText()" << endl; // DEBUG
    string input;
    
    while (getline(cin,input))
    {        
        
        cout << "INPUT: " << input << endl; // DEBUG
        if(input == ".") break;

        string text_input = input;
        res.push_back(text_input);
    }

    cout << "EXITED getText()" << endl; // DEBUG
    
    return res;
}


