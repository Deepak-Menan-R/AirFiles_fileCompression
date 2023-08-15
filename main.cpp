#include <iostream>
#include "AirFile.hpp"
using namespace std;

int main()
{
    string inputFileName, outputFileName;
    bool flag = true;
    bool compressed = false;

    while (flag)
    {
        int choice;
        if (compressed)
        {
            cout << "1. Decompress" << endl;
            cout << "2. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
        }
        else
        {
            cout << "1. Compress" << endl;
            cout << "2. Exit" << endl;
            cin >> choice;
        }

        if (choice == 1)
        {
            if (!compressed)
            {
                bool vaildFileInput = false;
                while (!vaildFileInput)
                {
                    cout << "Enter the name of the file you want to compress: ";
                    cin >> inputFileName;
                    if (cin.fail() || inputFileName.find(".txt") == string::npos)
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid input. Please try again." << endl;
                    }
                    else
                    {
                        vaildFileInput = true;
                    }
                }

                AirFile f(inputFileName, "compressedFiles/" + inputFileName + ".af");
                f.compress();

                cout << "Compressed successfully" << endl;
                compressed = true;
            }
            else
            {
                bool vaildFileInput = false;
                while (!vaildFileInput)
                {
                    cout << "Name your decompressed file: ";
                    cin >> outputFileName;
                    if (cin.fail() || outputFileName.find(".txt") == string::npos)
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid input. Please try again." << endl;
                    }
                    else
                    {
                        vaildFileInput = true;
                    }
                }
                AirFile f(inputFileName + ".af", outputFileName);
                f.decompress();

                cout << "Decompressed successfully" << endl;
                compressed = false;
            }
        }
        else if (choice == 2)
        {
            flag = false;
        }
        else
        {
            cout << "Invalid input. Please try again." << endl;
        }

        cout << "Do you want to continue? (y/n): ";
        char c;
        cin >> c;

        if (c == 'n')
        {
            flag = false;
        }
    }

    return 0;
}