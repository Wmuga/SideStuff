#include <fstream>
#include <ctime>
struct Node
{
    char key[10];
    int value;
};



int main() {
    std::ofstream out("..\\..\\FrameWork\\in.txt",std::ios::binary);
    srand(reinterpret_cast<unsigned int>(ctime(0)));
    for (size_t i=0;i<1000000;i++)
    {
        Node in{};
        for (size_t j=0;j<10;j++){
            in.key[j]=(char)(rand()%27)+'a';
        }
        in.value=rand()%345;
        out.write((char*)&in,sizeof(Node));
    }
    return 0;
}
