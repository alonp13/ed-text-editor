#include "Document.h"

// Constructor that loads doc_name file into vector of strings
Document::Document(string doc_name): m_doc_name(doc_name), m_cursor(1)
{
    ifstream file(doc_name);
    string line;
    int char_counter = 0;
    if(!file)
    {
        cout << "No Such file!" << endl;
        m_cursor = 0;
    }

    while (getline(file,line))
    {
        string line_to_push = line;
        char_counter += line_to_push.length();
        m_lines.push_back(line_to_push);
    }

    cout << char_counter << endl;
    file.close();
}

// Method that returns the line in current position of the cursor
string Document::getLineAtCursor()
{
    if(m_cursor == 0 || m_cursor > m_lines.size())
    {
        return nullptr;
    }
    return m_lines.at(m_cursor - 1);
}

// Method that sets the line in current position of the cursor
void Document::setLineAtCursor(string new_line)
{
    if(m_cursor == 0 || m_cursor > m_lines.size())
    {
        return;
    }
    m_lines[m_cursor-1] = new_line;
}

// Method that prints the current line
void Document::printAtCursor()
{
    cout << getLineAtCursor() << endl;
}

// Moves to given line
void Document::moveToLine(int line_to_move)
{
    if(line_to_move <= m_lines.size())
    {
        m_cursor = line_to_move;
    }
    printAtCursor();
}

// Moves forward by given steps
void Document::moveCursorForward(int lines_to_move)
{
    if(m_cursor + lines_to_move <= m_lines.size())
    {
        m_cursor += lines_to_move;
    }
    printAtCursor();
}

// Moves to the end of the document
void Document::moveToEnd()
{
    m_cursor = m_lines.size();
}

// Adds text given after the current position of the cursor ('a' option)
void Document::addTextAfter(vector<string> text_to_add)
{
    int idx = m_cursor;
    for(int i = 0 ; i < text_to_add.size(); i++)
    {
        string line_to_add = text_to_add[i];

        cout << i << ". " << line_to_add << endl;
        m_lines.insert(m_lines.begin() + idx,line_to_add);
        idx++;
    }
    m_cursor = idx;
}

// Adds text given before the current position of the cursor ('i' option)
void Document::addTextBefore(vector<string> text_to_add)
{
    int idx = max(m_cursor - 1,0);
    for(int i = 0 ; i < text_to_add.size(); i++)
    {
        string line_to_add = text_to_add[i];

        cout << i << ". " << line_to_add << endl;
        m_lines.insert(m_lines.begin() + idx,line_to_add);
        idx++;
    }
    m_cursor = idx;
}

// Replaces text given with the line in current position of the cursor ('c' option)
void Document::replaceToText(vector<string> text_replace)
{
    removeCurrentLine();
    addTextAfter(text_replace);
}

// Removes the line in current position of the cursor ('d' option)
void Document::removeCurrentLine()
{
    if (m_cursor == 0) return;
    vector<string> new_lines;
    for (int i = 0; i < m_lines.size(); i++)
    {
        if(i == m_cursor - 1) continue;
        new_lines.push_back(m_lines.at(i));
    }
    m_lines = new_lines;
    m_cursor = min(m_cursor,(int)m_lines.size());
}

// Merges the next line to this line ('j' option)
void Document::concatNextLine()
{
    if(m_cursor == m_lines.size()) return;
    string curr_line = getLineAtCursor();
    removeCurrentLine();
    string next_line = getLineAtCursor();
    string new_line = curr_line + next_line;
    setLineAtCursor(new_line);
    printAtCursor();
}

// Moves to the line with first appearance of text ('/text/' option)
void Document::searchText(string text)
{
    for(int i = m_cursor - 1; i < m_lines.size(); i++)
    {
        string curr_line = m_lines[i];
        if(curr_line.find(text) != string::npos)
        {
            moveToLine(i + 1);
            printAtCursor();
            return;
        }
    }

    int start_idx = m_cursor;
    for(int i = 0 ; i < start_idx ; i++)
    {
        string curr_line = m_lines[i];
        if(curr_line.find(text) != string::npos)
        {
            moveToLine(i + 1);
            printAtCursor();
            return;
        }
    }
}

// Replaces strings in current line ('s/old/new/' option)
void Document::replaceStrings(string old_str, string new_str)
{
    string curr_line = getLineAtCursor();
    int old_idx = curr_line.find(old_str);
    string before_old = curr_line.substr(0,old_idx);
    string after_old = curr_line.substr(old_idx + old_str.length());
    string after_change = before_old + new_str + after_old;
    setLineAtCursor(after_change);

}

// Writes to file_name
void Document::saveDocument(string file_name)
{
    ofstream file(file_name);
    for (int i = 0; i < m_lines.size(); i++)
    {
        file << m_lines[i] << endl;
    }
    file.close();
}

// DEBUGGING
void Document::printDoc()
{
    cout << "doc_name: " << m_doc_name << endl;
    cout << "cursor at: " << m_cursor << endl;
    for(int i=0; i<m_lines.size(); ++i)
        cout << m_lines[i] << endl;
}