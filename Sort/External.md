# External Sort Notes
## Loser Tree Structure
Tree nodes:
$$k = 1_{WinnerNode} + (k-1)_{InnerNode}$$
If height is $h$, total leaves is $2^{h-1}$, let it go up but below k, then there will be: $k-2^{h-1}$ extra leaves.
Take $k-2^{h-1}$ leaves down, then each hole can connect two extra leaves, then the tree is able to have $2k-2^h$ leaves.
This is extactly the amount of $k-2^{h-1}$ extra leaves and the taken down $k-2^{h-1}$ leaves.
So in total there will be nodes in h layer plus leaves in last layer in total:
$$2k-1 = 2^{h} - 1 + 2k-2^h$$
in which $k-1$ is internal loser tree nodes for loser recording, and $h$ leaves for data reading.
