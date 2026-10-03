#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <typeinfo>

std::string translate (std::string row) { //std::string
    char first_char = row.front();
    // if first char is @ then the row is representing A instruction
    if (first_char == '@') {
        std::cout << "first char is @" << "\n";
        row.erase(0,1);
        int number = std::stoi(row); 
        std::string binaryString = std::bitset<16>(number).to_string();
        binaryString.insert(0, "0");
        std::cout << binaryString << std::endl;
        return binaryString;
    };
    // otherwise it is the C instruction; 111accccccdddjjj, dest=comp;jump
    std::string dest = "000";
    std::string jump = "000";
    if (row.find('=') != std::string::npos) {
        std::size_t pos = row.find("=");
        std::string dest_part = row.substr(0, pos);
        std::cout << dest_part << "dest part is here\n";
        ; // found dest
    }
    if (row.find(';') != std::string::npos) {
        ; // found jump
    }
    return "kind of works";
}

void read_code() {
    // Create a text string, which is used to output the text file
    std::ofstream MyFile("output.txt");
    std::string myText;

    // Read from the text file
    std::ifstream MyReadFile("input.txt");

    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, myText)) {
    // Output the text from the file
        std::cout << myText << "\n";
        std::string assembledText = translate(myText);
        MyFile << assembledText << "are we writin\n";

    }
    MyFile.close();
    MyReadFile.close();
}

int main() {
    std::cout << "Hello, Mac World!\n";
    read_code();
    if (20 > 18) {
        std::cout << "20 is greater than 18";
    }
    return 0;
}