#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Document {

    private:
        string m_doc_name;
        vector<string> m_lines;
        int m_cursor;
        string getLineAtCursor();
        void setLineAtCursor(string new_line);
        void printAtCursor();

    public:
        Document(): m_cursor(0) {};
        Document(string doc_name);

        void moveToLine(int line_to_move);
        void moveCursorForward(int lines_to_move);
        void moveToEnd();

        void addTextAfter(vector<string> text_to_add);
        void addTextBefore(vector<string> text_to_add);
        void replaceToText(vector<string> text_replace);
        void removeCurrentLine();
        void concatNextLine();

        void searchText(string text);
        void replaceStrings(string old_str, string new_str);
        void saveDocument(string file_name);

        // FOR DEBUG
        void printDoc();
};