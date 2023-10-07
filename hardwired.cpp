#include <bits/stdc++.h>
#include <fstream>

using namespace std;

// Global Variables
string MDR, D;
int PC, MAR, TMP, AC, B, a0, a1, a2, OUT, IN, FGI, FGO;
int f, z, n, c, Sw, I;

// opcode decoded as D0, D1, D2, D3......., D7
void mdr_decoder()
{
    string opcode;
    for (int i = 1; i < 4; i++)
        opcode += MDR[i];
    // cout << opcode << endl;
    if (opcode == "000")
    {
        D = "10000000";
    }
    else if (opcode == "001")
    {
        D = "01000000";
    }
    else if (opcode == "010")
    {
        D = "00100000";
    }
    else if (opcode == "011")
    {
        D = "00010000";
    }
    else if (opcode == "100")
    {
        D = "00001000";
    }
    else if (opcode == "101")
    {
        D = "00000100";
    }

    else if (opcode == "110")
    {
        D = "00000010";
    }
    else if (opcode == "111")
    {
        D = "00000001";
    }
}

void alu_flag_decoder()
{

    if (c == 0 && z == 0)
    {
        a0 = 1;
        a1 = 0;
        a2 = 0;
    }
    else if (c == 1 && z == 0)
    {
        a0 = 0;
        a1 = 1;
        a2 = 0;
    }
    else if (c == 0 && z == 1)
    {
        a0 = 0;
        a1 = 0;
        a2 = 1;
    }
}

// swap function
void swap()
{

    if (Sw == 1)
    { // t4
        cout << "\n\n swapping starts" << endl
             << endl
             << "\t\t\t\t\t.....T4 cycle.....\n \t\t\t\t\t.....swapping....." << endl
             << endl;
        int TMP = AC;
        cout << endl
             << "TMP<--AC" << endl
             << "TMP = " << TMP << endl
             << "AC = " << AC << endl;

        // t5
        cout << endl
             << endl
             << "\t\t\t\t\t.....T5 cycle.....\n \t\t\t\t\t.....swapping....." << endl
             << endl;
        AC = B;
        cout << "AC<--B" << endl
             << "AC = " << AC << endl
             << "B= " << B << endl;

        // t6
        cout << endl
             << endl
             << "\t\t\t\t\t.....T6 cycle.....\n \t\t\t\t\t.....swapping....." << endl
             << endl;
        B = TMP;
        cout << "B<--TMP" << endl
             << "B= " << B << endl
             << "TMP=" << TMP << endl
             << "Sw flag reset" << endl;

        Sw = 0;

        cout << endl
             << "****Clock RESET****" << endl;
    }
}

void H_C_F()
{

    while (1)
    {
        // t0
        cout << endl
             << endl
             << "\t\t\t\t\t.....T0 cycle.....\n \t\t\t\t  .....HCF calculation....." << endl
             << "comparision cycle" << endl;

        if (AC == B)
        {
            c = 0;
            z = 1;
        }
        else
        {
            if (AC < B)
            {
                c = 1;
                z = 0;
            }
            else
            {
                c = 0;
                z = 0;
            }
        }

        alu_flag_decoder();

        // t1
        cout << endl
             << endl
             << "\t\t\t\t\t.....T1 cycle.....\n \t\t\t\t  .....HCF calculation....." << endl
             << endl;
        if (a1)
        {
            Sw = 1;

            cout << "Sw bit sets " << endl;
            swap();
            AC = AC - B;
        }
        else if (a0)
        { // t2
            cout << endl
                 << endl
                 << " T1 cycle : Idle " << endl
                 << endl;
            cout << endl
                 << endl
                 << "\t\t\t\t\tT2 cycle\n \t\t\t\t  .....HCF calculation....." << endl
                 << endl;
            AC = AC - B;
            cout << "AC = AC - B" << endl;
        }
        else if (a2)
        { // t3
            cout << endl
                 << endl
                 << " T1 cycle : Idle  " << endl
                 << endl;
            cout << endl
                 << endl
                 << " T2 cycle : Idle " << endl
                 << endl;
            cout << endl
                 << endl
                 << "\t\t\t\t\t.....T3 cycle.....\n \t\t\t\t  .....HCF calculation....." << endl
                 << endl;

            OUT = AC;

            cout << "OUT <-- AC" << endl
                 << "OUT= " << AC << endl;
            cout << endl
                 << endl
                 << endl
                 << "\t\t\t\t\t.....T4 cycle.....\n \t\t\t\t  .....HCF calculation....." << endl
                 << endl
                 << "****clock reset****" << endl
                 << endl;
            break;
        }
    }
}

int write_line(string content, int address)
{
    // variables for storing the filename of the file, the replacement line of
    // text, and the line number to replace in the file
    string text;
    text = content;
    int line_number;
    line_number = address;

    // fstream object will be used to read all of the existing lines in the file
    fstream read_file;

    // Open the file with the provided filename
    read_file.open("ram.txt");

    // If file failed to open, exit with an error message and error exit status
    if (read_file.fail())
    {
        cout << "Error opening file." << endl;

        // returning 1 instead of 0 is a signal to the shell that something went
        // wrong in the execution of the program
        return 1;
    }

    // Create a vector to store all the file lines, and a string line to store
    // each line that we read
    vector<string> lines;
    string line;

    // Read each line of the file and store it as the next element of the vector,
    // the loop will stop when there are no more lines to read
    while (getline(read_file, line))
        lines.push_back(line);

    // Close our access to the file since we are done reading with it
    read_file.close();

    // The vector will now contain an element for each line in the file, so the
    // size of the vector is the number of lines in the file.  Check to make
    // sure the line number requested does not exceed the number of lines in
    // the file, if it does, exit with an error message and status.
    if (line_number > lines.size())
    {
        cout << "Line " << line_number;
        cout << " not in file." << endl;

        // Inform user how many lines ARE in the file as part of the error message
        cout << "File has " << lines.size();
        cout << " lines." << endl;

        return 1;
    }

    // Create ofstream object for writing to the file
    ofstream write_file;

    // Open the file with the provided filename
    write_file.open("ram.txt");

    // If the file failed to open, exit with an error message and exit status
    if (write_file.fail())
    {
        cout << "Error opening file." << endl;
        return 1;
    }

    // Write all of the lines stored in the vector back to the file, EXCEPT the
    // line that we want to replace, in that case we'll write the replacement
    // text instead.

    // Line number 1 will be stored at vector index 0, line number 2 will be
    // stored at vector index 1, and so on because vectors are zero-indexed, so
    // decrement line_number to help us identify when we've reached the
    // associated line in the file.
    line_number--;

    // Loop through the vector elements to write each line back to the file
    // EXCEPT the line we want to replace
    for (int i = 0; i < lines.size(); i++)
    {
        // If the current index is not the line number we wish to replace, write
        // the line back to the file, OTHERWISE if it IS the line we want to
        // replace write the replacement text back to the file instead.
        if (i != line_number)
            write_file << lines[i] << endl;
        else
            write_file << text << endl;
    }

    // Close our access to the file since we are done working with it
    write_file.close();

    return 0;
}

int read_line(string filename)
{
    // Use the ifstream object file to read the file
    ifstream file;

    // filename will store the name of the file and line_number the line number
    // string filename = "ram.txt";
    int line_number = MAR + 1;

    // The line number must be >= 1 so exit with an error message and status if
    // it is not... returning '1' is an exit status that indicates an error to
    // the shell/terminal.
    if (line_number <= 0)
    {
        cout << "Line number must be >= 1" << endl;
        return 1;
    }

    // Open the file with the provided filename
    file.open(filename);

    // If there was a failure opening the file (perhaps it does not exist) then
    // exit with an error message and status.
    if (file.fail())
    {
        cout << "File failed to open." << endl;
        return 1;
    }

    // We'll read in the file one line at a time until we find the line we're
    // looking for... current_line will keep track of the current line number
    // of the line we're reading in, and line will store the line content/string.
    int current_line = 0;
    string line;

    // Continue to read the file one line at a time, unless we reach the end of
    // the file at which point we stop
    while (!file.eof())
    {
        // Increment the current line number being read as we are reading in the
        // next line now
        current_line++;

        // Read the next line from the 'file' into the 'line' string
        getline(file, line);

        // If current line number of the line we've read in matches the line number
        // that we're looking for, use break to stop the loop
        if (current_line == line_number)
            break;
    }

    // It's possible that the file does not contain as many lines as the line
    // number that the user requested, if this is the case we output an error
    // message and inform the user how many lines are in the file.
    if (current_line < line_number)
    {
        cout << "Line not found!" << endl;
        cout << "File contains " << current_line;
        cout << " lines total." << endl;
    }
    // Otherwise we output the line content/string
    else
        MDR = line;

    // Close the file as we are done working with it
    file.close();
    return 0;
}

string DecimalToBinaryString(int a)
{
    string binary = "";
    int mask = 1;
    for (int i = 0; i < 10; i++)
    {
        if ((mask & a) >= 1)
            binary = "1" + binary;
        else
            binary = "0" + binary;
        mask <<= 1;
    }
    // cout << binary << endl;
    return binary;
}

// Addition module
void add()
{
    // t5
    cout << "addition starts" << endl;
    cout << endl
         << endl
         << "\t\t\t\t\t.....T5 cycle.....\n \t\t\t\t\t.....addition....." << endl
         << endl;
    read_line("ram2.txt"); /* content of Location pointed by MAR --> MDR*/
    cout << "AC =" << AC << endl
         << " MDR <-- M[MAR] " << endl
         << "MDR = " << MDR << endl;

    // t6
    cout << endl
         << endl
         << "\t\t\t\t\t.....T6 cycle.....\n \t\t\t\t\t.....addition....." << endl
         << endl;

    AC = AC + stoi(MDR, 0, 2);
    int E = 1;
    cout << "AC <-- AC+MDR" << endl
         << "AC=" << AC << endl
         << "****clock reset****" << endl;
}

void sub()
{
    cout << "addition starts" << endl;
    // t5
    cout << endl
         << endl
         << "\t\t\t\t\t.....T5 cycle.....\n \t\t\t\t\t.....subtraction....." << endl
         << endl;
    read_line("ram2.txt"); /* content of Location pointed by MAR --> MDR*/
    cout << "AC =" << AC << endl
         << " MDR <-- M[MAR] " << endl
         << "MDR = " << MDR << endl;

    // t6
    cout << endl
         << endl
         << "\t\t\t\t\t.....T6 cycle.....\n \t\t\t\t\t.....subtraction....." << endl
         << endl;

    AC = AC - stoi(MDR, 0, 2);
    int E = 1;
    cout << "AC <-- AC-MDR" << endl
         << "AC=" << AC << endl
         << "****clock reset****" << endl;
}

void lda()
{
    cout << "Loading accumulator to memory starts" << endl;
    // t5
    cout << endl
         << endl
         << "\t\t\t\t\t.....T5 cycle.....\n \t\t\t\t\t.....LDA operation....." << endl
         << endl;

    read_line("ram2.txt"); /* content of Location pointed by MAR --> MDR*/
    cout << " MDR <-- M[MAR] " << endl
         << "MDR = " << MDR << endl;

    // t6
    cout << endl
         << endl
         << "\t\t\t\t\t.....T6 cycle.....\n \t\t\t\t\t.....LDA operation....." << endl
         << endl;

    AC = stoi(MDR, 0, 2);

    cout << "AC <-- MDR" << endl
         << "AC=" << AC << endl
         << "****clock reset****" << endl;
}

void bun()
{
    cout << "branching uncoditional starts" << endl;
    // t5
    cout << endl
         << endl
         << "\t\t\t\t\t.....T5 cycle.....\n \t\t\t\t\t.....BUN operation....." << endl
         << endl;

    PC = MAR;
    cout << "PC <-- MAR" << endl
         << "PC=" << PC << endl
         << "****clock reset****" << endl;
}

void bsa()
{
    cout << "Branch and Save address" << endl;
    // t5
    cout << endl
         << endl
         << "\t\t\t\t\t.....T5 cycle.....\n \t\t\t\t\t.....BSA operation....." << endl
         << endl;

    MDR = PC;
    cout << "MDR <-- PC" << endl
         << "MDR=" << MDR << endl;

    // t6
    cout << endl
         << endl
         << "\t\t\t\t\t.....T6 cycle.....\n \t\t\t\t\t.....BSA operation....." << endl
         << endl;

    write_line(MDR, MAR); /*M[MAR] <-- MDR*/

    MAR = MAR + 1;
    cout << "MAR <-- MAR+1" << endl
         << "MAR=" << MAR << endl;

    // t7
    cout << endl
         << endl
         << "\t\t\t\t\t.....T7 cycle.....\n \t\t\t\t\t.....BSA operation....." << endl
         << endl;

    PC = MAR;
    cout << "PC <-- MAR" << endl
         << "PC=" << PC << endl
         << "****clock reset****" << endl;
}

void sta()
{
    cout << "store accumulator operation starts" << endl;
    // t5
    cout << endl
         << endl
         << "\t\t\t\t\t.....T5 cycle.....\n \t\t\t\t\t.....STA operation....." << endl
         << endl;
    MDR = AC;
    cout << "MDR <-- AC" << endl
         << "MDR =" << MDR << endl;

    // t6
    cout << endl
         << endl
         << "\t\t\t\t\t.....T6 cycle.....\n \t\t\t\t\t.....STA operation....." << endl
         << endl;
    write_line(MDR, MAR); /*M[MAR] <-- MDR*/
}

void swap1()
{
    cout << "swapping operation starts" << endl;
    // t3
    cout << endl
         << endl
         << "\t\t\t\t\t.....T3 cycle.....\n \t\t\t\t\t.....swapping....." << endl
         << endl;
    cout << " condition : ~I & D6 & ~f & T3 = 1 \n swap flag sets" << endl;
    Sw = 1;

    swap();
}

void NMRI()
{
    string nmri_opcode;
    int j = 0;

    for (int i = 4; i <= 9; i++)
    {
        nmri_opcode[j] = MDR[i];
        j++;
    }

    if (I)
    {
        switch (stoi(nmri_opcode, 0, 2))
        {
        case 8: // clock 3
        {
            cout << endl
                 << endl
                 << "\t\t\t\t\t.....T3 cycle.....\n \t\t\t\t\t.....Input operation....." << endl
                 << endl;
            AC = IN;
            cout << "AC<--INP" << endl
                 << "AC=" << AC << endl;
            FGI = 0;
            cout << "FGI=" << FGI << endl
                 << "reset";
            break;
        }
        case 4:
        {
            cout << endl
                 << endl
                 << "\t\t\t\t\t.....T3 cycle.....\n \t\t\t\t\t.....Output operation....." << endl
                 << endl;
            OUT = AC;
            cout << "OUT<-AC" << endl
                 << "OUT=" << OUT << endl;
            FGO = 0;
            cout << "FGO=" << FGO << endl
                 << "reset";
            break;
        }
        }
    }
    else
    {
        switch (stoi(nmri_opcode, 0, 2))
        {
        case 8: // clock 3
        {
            cout << endl
                 << endl
                 << "\t\t\t\t\t.....T3 cycle.....\n \t\t\t\t\t.....CLA operation....." << endl
                 << endl;
            AC = 0;

            cout << "AC <-- 0" << endl
                 << "AC=" << AC << endl
                 << "reset";
            break;
        }
        case 4: // clock 3
        {
            cout << endl
                 << endl
                 << "\t\t\t\t\t.....T3 cycle.....\n \t\t\t\t\t.....CMA operation....." << endl
                 << endl;
            AC = ~AC;
            cout << "Complement of AC is:" << endl
                 << "AC=" << DecimalToBinaryString(AC) << endl
                 << "reset";
            break;
        }
        case 2: // clock 3
        {
            cout << endl
                 << endl
                 << "\t\t\t\t\t.....T3 cycle.....\n \t\t\t\t\t.....Increment operation....." << endl
                 << endl;
            AC = AC + 1;
            cout << "AC<-AC+1" << endl
                 << "AC=" << AC << endl
                 << "reset";
            break;
        }
        case 1: // clock 3
        {
            cout << endl
                 << endl
                 << "\t\t\t\t\t.....T3 cycle.....\n \t\t\t\t\t.....HLT operation....." << endl
                 << endl;
            cout << "Disable clock";
            PC = 0;
            MAR = 0;
            break;
        }
        }
    }
}

void fetch_cycle()
{

    cout << "\n\n\n\n ------------Instruction fetch starts------------ \n\n"
         << endl;
    // t0
    cout << endl
         << endl
         << "\t\t\t\t\t.....T0 cycle.....\n \t\t\t\t\t.....fetching....." << endl
         << endl;
    MAR = PC;
    cout << " MAR <-- PC " << endl
         << "MAR = " << MAR << endl
         << " PC = " << PC << endl;

    // t1
    cout << endl
         << endl
         << "\t\t\t\t\t.....T1 cycle.....\n \t\t\t\t\t.....fetching....." << endl
         << endl;
    read_line("ram.txt"); // content of Location pointed by MAR --> MDR
    PC++;
    cout << " MDR <-- M[MAR] " << endl
         << "MDR = " << MDR << endl
         << " PC = " << PC << endl;

    // t2
    cout << endl
         << endl
         << "\t\t\t\t\t.....T2 cycle.....\n \t\t\t\t\t.....fetching....." << endl
         << endl;
    string address;
    int j = 0;

    for (int i = 4; i <= 9; i++)
    {
        address[j] = MDR[i];
        j++;
    }
    MAR = stoi(address, 0, 2); /* MAR <-- MDR(5-0) */

    I = MDR[0] - '0';
    // jump:
    mdr_decoder(); // MDR(8-6) decoded

    cout << " MAR <-- MDR(5-0) " << endl
         << "MAR = " << MAR << endl
         << " I = " << I << endl
         << "D = " << D << endl;

    // t3
    cout << endl
         << endl
         << "\t\t\t\t\t.....T3 cycle.....\n \t\t\t\t\t.....Decoding....." << endl
         << endl;
    if (((D[7] - '0') == 0) && I)
    {
        read_line("ram2.txt"); // content of Location pointed by MAR --> MAR
        cout << " MDR <-- M[MAR] " << endl;
    }

    cout << "MDR = " << MDR << endl;

    // t4
    cout << endl
         << endl
         << "\t\t\t\t\t.....T4 cycle.....\n \t\t\t\t\t.....Decoding....." << endl
         << endl;
    if ((D[6] - '0') && I) // to extract first operands from data section RAM for HCF macrooperation
    {
        AC = stoi(MDR, 0, 2);
        MAR++;
        cout << "AC <-- MDR" << endl
             << "AC = " << AC << endl
             << " MAR = MAR+1 \n MAR =" << MAR << endl;
    }
    else if ((~(D[7] - '0') && I))
    {
        MAR = stoi(MDR, 0, 2); // string to int
        cout << " MDR <-- M[MAR] " << endl;
    }

    // for t4 cycle onwards
    if ((D[6] - '0') && I) // to extract second operands from data section RAM for HCF macrooperation
    {                      // t5
        cout << endl
             << endl
             << "\t\t\t\t\t.....T5 cycle.....\n \t\t\t\t\t.....fetching....." << endl
             << endl;
        read_line("ram2.txt"); // content of Location pointed by MAR --> MDR
        cout << "MDR <-- M[MAR]" << endl
             << "MDR = " << MDR << endl;

        // t6
        cout << endl
             << endl
             << "\t\t\t\t\t.....T6 cycle.....\n \t\t\t\t\t.....fetching....." << endl
             << endl;
        B = stoi(MDR, 0, 2);
        f = 1;
        /* reset clock */
        cout << "B <-- MDR " << endl
             << "B = " << B << endl
             << " f sets and \n\n ****Clock RESET**** " << endl;

        H_C_F();
    }
    else
    {
        // t5

        /* Call to other macrooperations*/

        switch (stoi(D, 0, 2))
        {
        case 128:
            add();
            break;

        case 64:
            sub();
            break;

        case 32:
            bun();
            break;

        case 16:
            bsa();
            break;

        case 8:
            lda();
            break;

        case 4:
            sta();
            break;

        case 2:
            swap1();
            break;

        case 1:
            NMRI();
            break;
        }
        // goto jump;
    }
}

int main()
{
    MAR = 0;
    PC = 0;

    // cout<<"PC= "<< PC<<endl<< "MAR= "<< MAR <<endl;
    int x = 0;
    cin >> x;
    while (x > 0)
    {
        fetch_cycle();
        x--;
    }
}
