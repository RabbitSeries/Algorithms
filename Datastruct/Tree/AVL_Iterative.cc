#include "AVL_Iterative.hpp"
using namespace std;
int main() {
    using namespace AVL_Ietrative;
    node<int, less<>>* root{ nullptr };
    string helpMessage(
        "Command format: \n\
        <I D E> num\n\
        where I for insert, D for deletion, E for exit\n" );
    cout << helpMessage;
    string cmd{};
    while ( cin >> cmd ) {
        if ( cmd == "I" ) {
            int val;
            cin >> val;
            root = insert( root, val );
            cout << "Tree:\n";
            BFS( root );
        } else if ( cmd == "D" ) {
            int val;
            cin >> val;
            root = delNode( root, val );
            cout << "Tree:\n";
            BFS( root );
        } else {
            break;
        }
    }
    cout << "Root: " << ( root ? to_string( root->elem ) : "EMPTY" ) << endl;
    cout << "Height: " << ( root ? root->height : 0 ) << endl;
}