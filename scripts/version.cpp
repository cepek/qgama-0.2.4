#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

int main() {
  ifstream input("../../gama/configure.ac");
  string line;

  // getting the GNU Gama version
  while (getline(input,line)) {
    if (line.substr(0,7)=="AC_INIT")
        break;
  }

  istringstream ac_init(line);
  string gama_version;

  ac_init >> gama_version;
  ac_init >> gama_version;

  gama_version = gama_version.substr(1,gama_version.length()-3);
  
  ofstream output("../config.h");
  output << "#define VERSION \"" << gama_version << "\""<< endl;
#ifdef QGAMA_VERSION
  output << "#define QGAMA_VERSION \"" << QGAMA_VERSION << "\"" << endl;
#endif
}
