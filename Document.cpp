#include "Document.h"

Document::Document(string doc_name): m_doc_name(doc_name), m_cursor(1)
{
    ifstream file(doc_name);
    string line;

    if(!file)
    {
        cout << "No Such file!" << endl;
        m_cursor = 0;
    }

    while (getline(file,line))
    {
        string line_to_push = line;
        m_lines.push_back(line_to_push);
    }

    file.close();
}

string Document::getLineAtCursor()
{
    if(m_cursor == 0 || m_cursor > m_lines.size())
    {
        return nullptr;
    }
    return m_lines.at(m_cursor - 1);
}

void Document::setLineAtCursor(string new_line)
{
    if(m_cursor == 0 || m_cursor > m_lines.size())
    {
        return;
    }
    m_lines[m_cursor-1] = new_line;
}

void Document::moveToLine(int line_to_move)
{
    if(line_to_move <= m_lines.size())
    {
        m_cursor = line_to_move;
    }
}

void Document::moveCursorForward(int lines_to_move)
{
    if(m_cursor + lines_to_move <= m_lines.size())
    {
        m_cursor += lines_to_move;
    }
}

void Document::moveToEnd()
{
    m_cursor = m_lines.size();
}


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

void Document::replaceToText(vector<string> text_replace)
{
    removeCurrentLine();
    addTextBefore(text_replace);
}

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

void Document::concatNextLine()
{
    if(m_cursor == m_lines.size()) return;
    string curr_line = getLineAtCursor();
    removeCurrentLine();
    string next_line = getLineAtCursor();
    string new_line = curr_line + next_line;
    setLineAtCursor(new_line);
}

void Document::searchText(string text)
{
    for(int i = m_cursor - 1; i < m_lines.size(); i++)
    {
        string curr_line = m_lines[i];
        if(curr_line.find(text) != string::npos)
        {
            moveToLine(i + 1);
            cout << curr_line << endl; // DEBUG
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
            cout << curr_line << endl; // DEBUG
            return;
        }
    }
    cout << text << " Not Found!" << endl; // DEBUG
}

void Document::replaceStrings(string old_str, string new_str)
{
    string curr_line = getLineAtCursor();
    int old_idx = curr_line.find(old_str);
    string before_old = curr_line.substr(0,old_idx);
    string after_old = curr_line.substr(old_idx + 1);
    string after_change = before_old + new_str + after_old;
    setLineAtCursor(after_change);

}

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