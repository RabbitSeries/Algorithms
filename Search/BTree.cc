// #include <memory>
// #include <vector>
// template <typename T>
// struct tree_trait {
//     using Tree = std::shared_ptr<T>;
//     using Node = std::shared_ptr<T>;
// };
// struct BTree : public tree_trait<BTree> {
//     using branch = std::vector<std::pair<int, std::shared_ptr<Node>>>;
//     using iter = branch::iterator;
//     std::vector<std::pair<int, std::shared_ptr<Node>>> childs;
//     Node rightMost;
//     BTree(iter begin, iter end) : {}
//     static Tree insert( Tree root, int elem ) {
//         if ( !root ) {
//             return std::
//         }
//     }
// };