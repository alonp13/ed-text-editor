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
        // DEBUG
        if(input == "DEBUG")
        {
            m_doc.printDoc();
            continue;
        }

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

        if(input.length() > 1 && input.at(0) == '/' && input.at(input.length() - 1) == '/' )
        {
            string text_to_search = input.substr(1,input.length()-2);
            m_doc.searchText(text_to_search);
            continue;
        }

        if(input.length() >= 2 && input.substr(0,2) == "w ")
        {
            string file_name = input.substr(2);
            if(file_name.find(' ') != string::npos)
            {
                cout << "?" << endl; //DEBUG    
            } else {
                m_doc.saveDocument(file_name);
            }
            continue;
        }

        if(input.length() > 2 && input.substr(0,2) == "s/" && input.at(input.length() - 1) == '/')
        {
            string command = input.substr(2,input.length() - 3);
            
            int slash_idx = command.find('/');
            if(slash_idx != string::npos)
            {
                string old_str = command.substr(0,slash_idx);
                string new_str = command.substr(slash_idx + 1);
                cout << "old_str " <<  old_str << endl; //DEBUG
                cout << "new_str " << new_str << endl; //DEBUG

                m_doc.replaceStrings(old_str,new_str);
            } 
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


