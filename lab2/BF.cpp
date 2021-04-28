#include <iostream>

using namespace std;

void BruteForce(string znaki, size_t iteracja) 
{
    if (iteracja == znaki.size()) 
    {
        cout << znaki << endl;
        return;
    }
    for (int i = iteracja; i <= znaki.size() - 1; i++)
    {
        swap(znaki[iteracja], znaki[i]);
        BruteForce(znaki, iteracja + 1);
        swap(znaki[iteracja], znaki[i]);
    }
}

int main(int argc, char** argv) 
{
    //if (argc > 1) 
    //{
        string znaki = "123"; //string(argv[1]);
        BruteForce(znaki, 0);
        return 0;
    //}
    cout << argv[0] << " [znaki]\n";
    return 0;
}