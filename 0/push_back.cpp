#include <vector>
#include <fstream>
using namespace std;

int main() {
    ofstream fout("push_back.txt");
    vector<int> v;
    for (int i = 0; i < 1000000; i++) {
        v.push_back(i);
        fout << v.size() << " " << v.capacity() << endl;
    }
}