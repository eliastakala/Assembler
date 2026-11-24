#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <typeinfo>
#include <unordered_map>
#include <algorithm>
#include "utils.h"

const std::unordered_map<std::string, std::string> jumpTable = {
    {"JGT", "001"},
    {"JEQ", "010"},
    {"JGE", "011"},
    {"JLT", "100"},
    {"JNE", "101"},
    {"JLE", "110"},
    {"JMP", "111"},
};

const std::unordered_map<std::string, std::string> destTable = {
    {"M", "001"},
    {"D", "010"},
    {"MD", "011"},
    {"A", "100"},
    {"AM", "101"},
    {"AD", "110"},
    {"ADM", "111"},
};

const std::unordered_map<std::string, std::string> compTable = {
    {"0", "0101010"},
    {"1", "0111111"},
    {"-1", "0111010"},
    {"D", "0001100"},
    {"A", "0110000"},
    {"!D", "0001101"},
    {"!A", "0110001"},
    {"-D", "0001111"},
    {"-A", "0110011"},
    {"D+1", "0011111"},
    {"A+1", "0110111"},
    {"D-1", "0001110"},
    {"A-1", "0110010"},
    {"D+A", "0000010"},
    {"D-A", "0010011"},
    {"A-D", "0000111"},
    {"D&A", "0000000"},
    {"D|A", "0010101"},
    {"M", "1110000"},
    {"!M", "1110001"},
    {"-M", "1110011"},
    {"M+1", "1110111"},
    {"M-1", "1110010"},
    {"D+M", "1000010"},
    {"D-M", "1010011"},
    {"M-D", "1000111"},
    {"D&M", "1000000"},
    {"D|M", "1010101"},
};

std::string translate (std::string row) { //std::string
    std::string rowToProcess = row;
    // rowToProcess = row.erase(remove_if(row.begin(), row.end(), isspace), row.end());
    trim(row);
    char first_char = row.front();
    // if first char is @ then the row is representing A instruction
    std::cout << row << "currently processing \n";
    if (first_char == '@') {
        std::cout << "A instruction? \n";
        row.erase(0,1);
        int number = std::stoi(row); 
        std::string binaryString = std::bitset<16>(number).to_string();
        binaryString.erase(0,1);
        binaryString.insert(0, "0");
        return binaryString;
    };
    // otherwise it is the C instruction; 111accccccdddjjj, dest=comp;jump
    std::string dest = "000";
    std::string jump = "000";
    std::cout << "C instruction? \n";
    if (row.find('=') != std::string::npos) {
        std::cout << "Equal sign? \n";
        std::size_t pos = row.find("=");
        std::string dest_part = row.substr(0, pos);
        dest = destTable.at(dest_part);
        row.erase(0, pos + 1);   
    }
    if (row.find(';') != std::string::npos) {
        std::cout << "half comma? \n";
        std::size_t pos = row.find(";");
        std::string jump_part = row.substr(pos + 1);
        std::cout << jump_part << "jump part? \n";
        jump = jumpTable.at(jump_part);
        std::cout << jump << "from jump tablet? \n";
        row.erase(pos);   

        ; // found jump
    }
    std::cout << "goes to the end? \n";
    std::string binaryStringC = "111";
    binaryStringC = binaryStringC + compTable.at(row) + dest + jump;
    return binaryStringC;
}

void read_code() {
    // Create a text string, which is used to output the text file
    std::ofstream MyFile("Prog.hack");
    std::string myText;
    // Read from the text file
    std::ifstream MyReadFile("Prog.asm");
    // Use a while loop together with the getline() function to read the file line by line
    std::string output;
    while (getline (MyReadFile, myText)) {
    // Output the text from the file
        std::string assembledText = translate(myText);
        output = output + assembledText + "\n";
        // MyFile << assembledText << "\n";
    }
    if (!output.empty()) output.pop_back();
    MyFile << output;
    MyFile.close();
    MyReadFile.close();
}

int main() {
    read_code();
    return 0;
}