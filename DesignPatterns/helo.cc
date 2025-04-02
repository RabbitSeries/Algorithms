
class hugeClass {
    public:
     int num[100];
 };

int main() {
    static hugeClass variable;
    variable.num[0]++;
    return 0;
}