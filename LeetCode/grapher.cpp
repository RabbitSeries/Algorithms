#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>

std::vector<std::pair<int, int>> extractPairs( const std::string& input ) {
    std::regex re( R"(\[(\d+),(\d+)\])" );
    std::smatch match;
    std::vector<std::pair<int, int>> pairs;

    std::string::const_iterator searchStart( input.cbegin() );
    while( std::regex_search( searchStart, input.cend(), match, re ) ) {
        int from = std::stoi( match[1].str() );
        int to = std::stoi( match[2].str() );
        pairs.emplace_back( from, to );
        searchStart = match.suffix().first; // Move to next match
    }

    return pairs;
}

void generateDOTFile( const std::string& filename, const std::vector<std::pair<int, int>>& pairs ) {
    std::ofstream dotFile( filename );

    if( !dotFile ) {
        std::cerr << "Error: Unable to create DOT file.\n";
        return;
    }

    dotFile << "digraph G {\n";
    for( const auto& p : pairs ) {
        dotFile << "    " << p.first << " -> " << p.second << ";\n";
    }
    dotFile << "}\n";

    dotFile.close();
    std::cout << "DOT file generated: " << filename << "\n";
}

int main() {
    // Input string containing pairs
    std::ifstream input( "input.txt" );
    std::string buf;
    std::getline( input, buf );
    auto pairs = extractPairs( buf );

    // Generate DOT file
    std::string dotFilename = "graph.dot";
    generateDOTFile( dotFilename, pairs );

    // Run Graphviz to create a PDF
    std::string command = "dot -Tpdf " + dotFilename + " -o graph.pdf";
    int result = system( command.c_str() );
    if( result == 0 ) {
        std::cout << "Graph PDF generated: graph.pdf\n";
    }
    else {
        std::cerr << "Error: Unable to generate PDF using Graphviz.\n";
    }

    return 0;
}
