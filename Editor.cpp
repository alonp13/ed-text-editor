#include "Editor.h"

// Handles input from the user
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

        // 'q' option
        if (input == "q")
        {
            break;
        }

        // '$' option
        if(input == "$")
        {
            m_doc.moveToEnd();
            continue;
        }

        // 'j' option
        if(input == "j")
        {
            m_doc.concatNextLine();
            continue;
        }

        // 'a' option
        if(input == "a")
        {
            vector<string> text_inserted = getText();
            m_doc.addTextAfter(text_inserted);
            continue;
        }

        // 'd' option
        if(input == "d")
        {
            m_doc.removeCurrentLine();
            continue;
        } 

        // 'i' option
        if(input == "i")
        {
            vector<string> text_inserted = getText();
            m_doc.addTextBefore(text_inserted);
            continue;
        }

        // 'c' option
        if(input == "c")
        {
            vector<string> text_inserted = getText();
            m_doc.replaceToText(text_inserted);
            continue;
        }

        // '/text/' option
        if(input.length() > 1 && input.at(0) == '/' && input.at(input.length() - 1) == '/' )
        {
            string text_to_search = input.substr(1,input.length()-2);
            m_doc.searchText(text_to_search);
            continue;
        }

        // 'w file' option
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

        // 's/old/new/' option
        if(input.length() > 2 && input.substr(0,2) == "s/" && input.at(input.length() - 1) == '/')
        {
            string command = input.substr(2,input.length() - 3);
            
            int slash_idx = command.find('/');
            if(slash_idx != string::npos)
            {
                string old_str = command.substr(0,slash_idx);
                string new_str = command.substr(slash_idx + 1);

                m_doc.replaceStrings(old_str,new_str);
            } 
            continue;
        }

        // Cursor moves options
        int num = 0;
        try {
            num = stoi(input);

            if(input.at(0) == '+' || input.at(0) == '-')
            {
                m_doc.moveCursorForward(num);
            } else {
                m_doc.moveToLine(num);
            }

        } catch (...) {
            cout << "?" << endl;
        }

    }

}

// Returns vector of strings recieving from the user
// when 'a','i' and 'c' options are called
vector<string> Editor::getText()
{
    vector<string> res;
    string input;
    
    while (getline(cin,input))
    {        
        if(input == ".") break;

        string text_input = input;
        res.push_back(text_input);
    }
    
    return res;
}


