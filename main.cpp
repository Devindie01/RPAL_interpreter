#include <iostream>
#include "parser.h"
#include <string>
#include <stack>
#include <vector>

int main(int argc, char *argv[])
{
    // Check if a file name is provided as a command-line argument
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <file_name> [-ast]" << std::endl;
        return 1;
    }

    // Get the file name from the command-line argument
    std::string filename = argv[1];

    // Check if the -ast switch is provided
    bool printASTRequested = false;
    if (argc == 3 && std::string(argv[2]) == "-ast")
    {
        printASTRequested = true;
    }

    else if (argc > 3)
    {
        std::cerr << "Usage: " << argv[0] << " <file_name> [-ast]" << std::endl;
        return 1;
    }

    // Open the input file
    std::ifstream inputFile(filename);

    if (!inputFile)
    { // Check if the file opened successfully
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    // Read the entire content of the file into a single string
    std::string input((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    inputFile.close(); // Close the file after reading
                       // Create a lexer instance
    lexer lexer;

    //     // Tokenize the input string
    lexer.tokenize(input);

    //     // Get the vector of tokens
    std::vector<token> tokens = lexer.getTokens();

    parser parser(&lexer);

    //     // Parse the input tokens
    parser.parse();

    if (argc == 2 && std::string(argv[1]) == "input.txt")
    {
        std::cout << "Output of the above program is: " << endl;

        parser.evaluateProgram();
    }

    // If the -ast switch is provided, call the function to print the AST
    if (printASTRequested)
    {
        parser.printAST();
    }

    return 0;
}
