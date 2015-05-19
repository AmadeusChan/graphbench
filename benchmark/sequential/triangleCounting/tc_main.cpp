#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <iomanip>
#include <set>
#include <map>
#include "graph.h"
#include "graph_io.h"
#include "tc.h"
#include "graph_util.h"
#include <getopt.h>

using std::cout;
using std::endl;

void usage() {
    cout << "usage: ./undirected_triangle_count -g graph.txt <-f csv [optional, default to tsv]>  <-o [optional, default to not print the result>" << endl;
    exit(1);
}

static void doTriangleCount (const Graph &graph, bool print_output) {
    double before, after;
    std::set<Triangle> triangles;
    std::set<Triangle>::iterator it;
    cout << "Running undirected triangle count" << endl;

    // run triangle count and time it
    before = getRealTime();
    undirectedTriangleCount(graph, triangles);
    after = getRealTime();

    // print triangles
    if (print_output) {
        for(it = triangles.begin(); it != triangles.end(); ++it) {
            cout << it->a.getLabel()
            << " "
            << it->b.getLabel()
            << " "
            << it->c.getLabel()
            << std::endl;
        }
    }

    // construct the runtime
    double sec = after - before;

    cout << "Runtime: "
    << sec
    << "s"
    << endl;
    cout << "Triangle count: "
    << triangles.size()
    << endl;
}

int main(int argc, const char **argv) {
    Graph graph;
    const char* graph_file = NULL;
    const char* format = "tsv";
    bool print_output = false;

    int opt;
    int position = 2;

    while ((opt = getopt(argc, (char* const*)argv, "g:f:o")) != -1) {
        switch (opt) {
        case 'g':
            graph_file = argv[position];
            position += 2;
            break;
        case 'f':
            format = argv[position];
            position += 2;
            break;
        case 'o':
            print_output = true;
            position += 1;
            break;
        default:
            usage();
            break;
        }
    }

    if (graph_file == NULL) {
        cout << "Must specify which graph to use."
        << "e.g. '-g graph.txt'" << endl;
        usage();
    }

    // import the graph in the specified format
    if (strcmp(format, "tsv") == 0) {
        importTSVGraph(graph_file, graph, false);
        } else if (strcmp(format, "csv") == 0) {
        importCSVGraph(graph_file, graph, false);
        } else {
        // the specified format does not match any supported format
        cout << "Unknown graph file format: " << format << endl;
        usage();
    }

    doTriangleCount(graph, print_output);

    return EXIT_SUCCESS;
}
