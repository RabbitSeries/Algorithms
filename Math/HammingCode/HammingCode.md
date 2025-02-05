@[TOC](HammingCode C++ partial functionality implementation.)
# HammingCode
## Preknowledge
### `&`,`|`,`^`
The priority of operator `&` is lower than `!=` in `C++`,`C#`(maybe).

In fact, for digit operators and logic operators:

`||` < `&&` < `|` < `^` < `&` < `!=` = `==` < `other logic operators` < `<<` = `>>`

So, make sure of using parenthesis: `()`


Under csi (C# script interactive):
```C++
> (5+1) & 5 != 0
(1,1): error CS0019: Operator '&' cannot be applied to operands of type 'int' and 'bool'
> 5 & (5+1) != 0
(1,1): error CS0019: Operator '&' cannot be applied to operands of type 'int' and 'bool'
> (5 & (5+1)) != 0 
true
```
The ^ operator can be used as ! operator to binary digits by `$digit ^ 1`,and as copying to binary digits by `$digit ^ 0`:

Under csi:
```C++
> 0^1
1
> 1^1
0
> 0^0
0
> 1^0
1
```
The `&` operator can be used as judging whether the number is the power of `2`.
```C++
bool isPowerOf2(int num) {return (num & (num - 1)) == 0;}
```
Under csi:
```C#
> bool isPowerOf2(int num) {return (num & (num - 1)) == 0;}
> isPowerOf2(8)
true
```

### `<<`
Operator `<<` can be used as judging whether the i-th (starts from 0) digit of a number is `1`:
```C++
bool isDigitTrue(int num, int digit) {return (1<<(digit) & num) != 0;}
```
Under csi:
```C#
> 1 << 6 & 0b10101001
0
> 1 << 5 & 0b10101001
32
> (1 << 5 & 0b10101001) != 0
true
> bool isDigitTrue(int num, int digit) {return (1<<(digit) & num) != 0;}
> isDigitTrue(0b10101001,5) 
true
```

### Hamming code function
$$n + k \leq 2^k - 1 (n: \text{Raw data digitN}, k: \text{Correction digitN})$$
$$suppose:L = n + k (L: \text{Encoded data digitN}, k: \text{Correction digitN in this encoded data}$$
Then we can get $L(k)$ and $L(n)$ relations:
$$L \leq 2^k - 1$$
$$L \leq 2^{L-n} - 1$$
Now:
$$\text{Supposing data}: 1011$$

$$
D_4 = 1,
D_3 = 0,
D_2 = 1,
D_1 = 1
$$
We have the Hamming code:
$$
D_4,D_3,D_2,H_3,D_1,H_2,H_1
\\
1,0,1,\_,1,\_,\_
$$

## Implementation

```cpp
#include "vector"
#include "string"
#include "iostream"
#include "algorithm"
// #include "bits/stdc++.h"
namespace HammingCode
{
    // Obtain hamming code digitN: n + k \leq 2^k - 1 (n: Raw data digitN, k: Correction digitN)
    int getCorrectionCnt(int dataSize, int correctionCnt = 0)
    {

        return (1 << correctionCnt) < dataSize + correctionCnt + 1 ? getCorrectionCnt(dataSize, ++correctionCnt) : correctionCnt;
    }
    int xorOperation(const int pos, const std::vector<int> encodedData)
    {
        int xorResult = 0;
        // Traverse the encoded vector, operating xor operation with specific digits.
        for (int i = 0; i < encodedData.size(); i++)
        {
            // If the corresponding digit of index is 1, do the XORs.
            if ((pos & (i + 1)) != 0)
            {
                // Remind that the correction digit initial value is 0, which does not contribute to the XOR operation.
                // Remind that the xorResult initial value is 0, which still does not contribute to the XOR operation and ensures the operation to include the correction digit.
                xorResult ^= encodedData[encodedData.size() - 1 - i];
            }
        }
        return xorResult;
    }
    std::vector<int> encodeData(const std::vector<int> binarydata)
    {
        int datalength = binarydata.size();
        int correctionCnt = getCorrectionCnt(datalength);
        int encodedLength = datalength + correctionCnt;
        std::vector<int> encodedData(encodedLength, 0);
        // Traverse the encodedData vector.
        for (int i = 0, j = 0; i < encodedLength; i++)
        {
            // If the (i+1)-th digit is not power of 2.
            if (((i + 1) & i) != 0)
            {
                // Copy data.
                encodedData[encodedLength - 1 - i] = binarydata[datalength - 1 - (j++)];
            }
        }
        // Traverse the correctionDigits
        for (int i = 0; i < correctionCnt; i++)
        {
            // The correctionCode's digit position (starts from 1).
            int correctionPos = 1 << i;
            // The val in data vector.
            int correctionDigitVal = 0;
            // Traverse the encoded vector, operating xor operation with specific digits.
            correctionDigitVal = xorOperation(correctionPos, encodedData);
            encodedData[encodedLength - 1 - (correctionPos - 1)] = correctionDigitVal;
        }
        return encodedData;
    }

    std::vector<int> decodeDataAndCorrect(std::vector<int> encodedData)
    {
        int encodedLength = encodedData.size();
        int correctionCnt = 0;
        while ((1 << correctionCnt) < encodedLength + 1)
        {
            correctionCnt++;
        }
        int datalength = encodedLength - correctionCnt;
        int errorCode = 0;
        // Traverse the correctionDigits
        for (int i = 0; i < correctionCnt; i++)
        {
            // The correctionCode's digit position (starts from 1).
            int correctionPos = 1 << i;
            // The val in data vector.
            int xorResult = 0;
            xorResult = xorOperation(correctionPos, encodedData);
            // Amazing huh?
            errorCode |= xorResult << i;
        }
        // If errorCode is not 0, correct the data.
        if (errorCode != 0)
        {
            // The error code is the position of the error bit.
            encodedData[encodedLength - 1 - (errorCode - 1)] ^= 1;
        }
        return encodedData;
    }
}

int main()
{
    std::vector<int> encodedData = HammingCode::encodeData(std::vector<int>{1, 0, 1, 0});
    std::cout << "encodedData:\n";
    std::for_each(encodedData.begin(), encodedData.end(), [](int val)
                  { std::cout << val; });

    encodedData[2] ^= 1;
    std::vector<int> dataToCorrect = encodedData;
    //     std::cout << "dataToCorrect:\n";
    // std::for_each(dataToCorrect.begin(), dataToCorrect.end(), [](int val)
    //               { std::cout << val; });

    std::vector<int> correctedData = HammingCode::decodeDataAndCorrect(dataToCorrect);
    std::cout << "\ncorrectedData:\n";
    std::for_each(correctedData.begin(), correctedData.end(), [](int val)
                  { std::cout << val; });

    return 0;
}
```

## 写在最后
说了这么多直观的,如果是研究一门语言,大部分人可能只需要知道怎么说就行了,这个时候语言学家就要站出来头疼了,所以来看看Hamming Code的原理是什么吧。

我们先来看看一个制药问题/做核酸问题,现在有一批疫苗$n$类（一个班级的学生$n$个,不考虑传染）和一批不限量小鼠（核酸试剂管）,为了统一描述,后文中的疫苗=核酸,小鼠=核酸试剂管。

假设这个班级的学生中有一个人阳了,为了找出这个人,我们设计了这样的一个混检办法:让学生先按照自然数编号,然后转化为二进制编号,并按照高位补零对齐,对齐长度为$k$,$k=\text{最长的二进制数的长度}+1$,混检试剂管也分配$k$支,每个试剂管对应$k$位二进制位中的一位,并让学生看自己的二进制编号,去二进制位为1对应的混检试剂管做检测.

如有20名同学,共需6支核酸试剂管($20=2^4+2^2,5\text{位二进制长}$),其中编号为18的同学为唯一阳性,他的二进制编号为10010,那么他就需要去 1,6 号试剂管做检测,别的同学由于没有阳性,别的同学做完了检测,最后核酸试剂管也还是阴性的,而编号为18的同学做完之后 1,6 号试剂管就会呈阳性,这样一来6个核酸试剂管中阳性的标1,阴性标0,就形成了编号10010,正好对应这位编号为18的同学,接着就可以拉着18号同学去隔离了.

下面证明这样做的合理性:

首先将班级的$n$个学生排列,并获取各自的自然数编号,为了方便举例,我们假设有一个人的编号为18,那么所有人的编号依次为：
$$1,2,...,18,...,n$$

那么每个学生的自然数编号可以转化为二进制,$18=16+2$：
$$1,10,...,10010,...$$

那么我们让这些学生按照最大的二进制位数对齐,并**高位补0**,那么最大的数位长度肯定出现在第$n$位同学的编号中,那么可以找到一个足够大的整数$k(k\geq 0,k\in \mathbf{Z})$使得:
$$2^k\geq n$$

这样的话第$n$位同学的位数就可能为$k+1$位(当这位同学的编号为2的整数幂的时候,$2^k=n$),也可能为$k$位($2^k>n$),这就要分类讨论了,很恼火,因此不妨再放松一点,让$k$尽可能大一点条件,让$k$不要那么的恰好地让等式成立,那么我们再去找这样的一个$k$:
$$2^k-1 \geq n$$

这样一来,当这位同学的编号为2的整数幂的时候,设:
$$n = 2^{k_1} = 2^{k} - 1, k_1 \geq 0,$$
那么$k_1 = k-1.$

在其他情况下,设:
$$n = 2^{k_1} + k_2 = 2^k - 1, k_1\geq 0,  0 < k_2 < 2^{k_1},$$

此时仍然有$k_1 = k - 1$.

因此,无论什么情况下,找到使等式成立的$k$,就可以让$n$由一个2的整数幂$2^{k_1}$决定它的二进制数位长度为$k_1 + 1$,并且$k_1 = k - 1$,就能得出$n$的位数为$k$.

那么在这种编号规则下,这个班级的学生的自然数编号在二进制下的对齐结果为$n$个$k$位长的二进制编码:
$$0..01,0..10,...$$

每个二进制数都有$k$位,对数位编码:
$$1,2,...,k.$$

然后分配$k$个核酸试剂混检管,试剂管依次编号为:
$$1,2,...,k.$$
核酸试剂管与同学的二进制编码数位就可以对应起来,那么就让学生按照二进制编码中为1的数位对应的试剂管中做混检.

因为阴性同学无论在哪些试管中做了检测都不会让试管从0(阴性)变成1(阳性),只有阳性同学在自己编号数位为1的对应试剂管中做了检测,才会让对应的试剂管变成1,这样就让试剂管的检测结果的01组合变成了这位同学的编号,从而找到这位同学.当然,如果所有学生都是阴性,那么核酸试剂管就全000.

正好就对应了海明码最后根据校验码是否为0来找到校验位并取反的过程.

现在来研究$n+k$是从哪来的以及校验位的排列问题.

那么考虑传输数据,数据和校验位必须都在一个整体数据中传输过去,否则就要让接收端设计成一个端口接受数据(可能有一个阳性的原数据),一个端口接受校验码(核酸试剂管),这样设计就很复杂,不如就设计一个端口接受数据,然后设计算法从数据中找到那些校验位,并进行纠错.

因此就需要把核酸试剂管和学生混在一起.让所有的$k$个核酸试剂管和$n$个学生参与这个`自然数排列`,`转换为二进制编号`,`对应数位检测`的过程.

因此总共需要做核酸(纠错)的就有总共就有$L$个:
$$L=n+k$$
那么根据前面的式子,就可以从接受到的待纠错编码长度(核酸,学生总数)$L$计算其中的纠错码数量(试剂管数)$k$:
$$2^k-1\geq L$$

代入$L=n+k$,根据原始数据长度(学生个数)$n$,就能计算需要的纠错码数量(试剂管数)$k$:
$$2^k - 1 \geq n+k$$

假如在检测过程中那个阳性的学生让对应的试剂管变成了1,如果不采取特殊的排列手段,这些变成1的试剂管在$(n+k)$个自然数排列中参与检测就可能会影响别的试剂管.

可能变成1的核酸试剂管之间存在`异管检测`和`自检测`,那么最好的办法就是在自然数排列的时候去掉`异管检测`,只保留`自检测`,让核酸试剂管只和自己检测,不去别的试剂管那里检测.

也就是让这些试剂管正好排在一个2次幂的位置,这样试剂管的二进制数位中就只有一个1(设第$i$位为1),这个试剂管就只需要去i号试管做检测,因此排列的时候让第i位为1的试管排在自然数的$2^{i-1}$个就好了.
