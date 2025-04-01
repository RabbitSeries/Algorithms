# TODO List

## More Simplified Code

- 1010, 1012, 1018 is too complex
- 1039, 1045 ~~why bit operator << is slower than multuply *~~(bitwise op is lower than plus), why ~~unordered_map is slower than vector and map~~(hash cost and confilct cost)?
- 1040 Change to DP.

## Long-term optimization

- Move to gnuc++20
- Change all tree datastructure into __gnu_pd_bs::tree.
[Ref](https://www.bilibili.com/video/BV1xWKpe7E65/?vd_source=17ae3da38f146f52a5262d73f91d0fb3) :

## 这些 STL 的手写都会远快于 STL

    bitset::count() 返回 1 的个数，复杂度为 O(n/w)
    pbds 平衡树的 tag：
        rb_tree_tag：红黑树
        splay_tree_tag：伸展树
        ov_tree_tag：有序向量树（不建议使用）
    pbds 堆的 tag：
        pairing_heap_tag：
            使用配对堆（Pairing Heap）实现。
            配对堆是一种具有良好理论性能和实际性能的堆结构，通常在实践中表现优异。
        binary_heap_tag：
            使用二叉堆（Binary Heap）实现。
            二叉堆是一种经典的堆结构，通常用于实现优先队列。
        binomial_heap_tag：
            使用二项堆（Binomial Heap）实现。
            二项堆是一种支持高效合并操作的堆结构。
        rc_binomial_heap_tag：
            使用放宽的二项堆（Relaxed Binomial Heap）实现。
            这种堆结构在二项堆的基础上进行了优化，以提高某些操作的性能。
        thin_heap_tag：
            使用瘦堆（Thin Heap）实现。
            瘦堆是一种专门为Dijkstra算法设计的堆结构，适用于图算法中的优先队列。
