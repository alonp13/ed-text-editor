#include "Editor.h"

int main(int argc, char* argv[]) 
{
    switch (argc)
    {
        case 1:
        {
            cout << argv[0] << endl;
            Editor editor;
            editor.loop();
            break;
        }

        case 2:
        {
            cout << argv[1] << endl;
            Editor editor(argv[1]);
            editor.loop();
            break;
        }

        default:
        {
            cout << "default" << endl;
            break;
        }
    }

    return 0;
}