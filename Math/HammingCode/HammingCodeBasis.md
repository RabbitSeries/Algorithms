


@[TOC](海明码原理)
## Why海明码？
今天写了异或运算的一些性质，在文章中完成了海明码的编码和纠码实现:
[HammingCode C++ partial functionality implementation.（海明码C++部分实现，C++，海明码，Hamming code，纠错编码）](https://blog.csdn.net/A2365974701/article/details/140912199 "Hamming Code C++ implementation")

说了这么多直观的,如果是研究一门语言,大部分人可能只需要知道怎么说就行了,这个时候语言学家就要站出来头疼了,所以来想想Hamming Code的原理是什么,就不写英文了.
## 问题提出
我们先来看看一个制药问题/做核酸问题,现在有一批疫苗$n$类（一个班级的学生$n$个,不考虑传染）和一批不限量小鼠（核酸试剂管）,为了统一描述,后文中的疫苗=同学,小鼠=核酸试剂管。

假设这个班级的学生中有一个人阳了,需要找出这个人,并只用**较少**（根据后文可知，保证**最少**就会失去编程的统一建模性）的核酸试剂管.
## 方法提出

我们设计了这样的一个混检办法:让学生先按照自然数编号,然后转化为二进制编号,并按照高位补零对齐,对齐长度为$k$,$k=\text{最长的二进制数的长度}+1$,混检试剂管也分配$k$支,每个试剂管对应$k$位二进制位中的一位,并让学生看自己的二进制编号,去二进制位为1对应的混检试剂管做检测.

如有20名同学,共需6支核酸试剂管($20=2^4+2^2,5\text{位二进制长}$),其中编号为18的同学为唯一阳性,他的二进制编号为010010,那么他就需要去 2,5 号试剂管做检测,别的同学由于没有阳性,别的同学做完了检测,最后核酸试剂管也还是阴性的,而编号为18的同学做完之后 2,5 号试剂管就会呈阳性,这样一来6个核酸试剂管中阳性的标1,阴性标0,就形成了编号010010,正好对应这位编号为18的同学,接着就可以拉着18号同学去隔离了.
## 案例证明
下面证明这样做的合理性:

首先将班级的$n$个学生排列,并获取各自的自然数编号,为了方便举例,我们假设有一个人的编号为18,那么所有人的编号依次为：
$$1,2,...,18,...,n$$

那么每个学生的自然数编号可以转化为二进制,$18=16+2$：
$$1,10,...,10010,...$$

那么我们让这些学生按照最大的二进制位数对齐,并**高位补0**,那么最大的数位长度肯定出现在第$n$位同学的编号中,那么可以找到一个足够大的整数$k(k\geq 0,k\in \mathbf{Z})$使得:
$$2^k\geq n$$

这样的话第$n$位同学的位数就可能为$k+1$位(当这位同学的编号为2的整数幂的时候,$2^k=n$),也可能为$k$位($2^k>n$),这就要分类讨论了,很恼火,因此不妨再放松一点条件,让$k$尽可能大一点,让$k$不要那么的恰好地让等式成立,那么我们再去找这样的一个$k$:
$$2^k-1 \geq n$$

这样一来,当这位同学的编号为2的整数幂的时候,设:
$$n = 2^{k_1} \leq 2^{k} - 1, k_1 \geq 0,$$
那么$k_1 = k-1.$

在其他情况下,设:
$$n = 2^{k_1} + k_2 \leq 2^k - 1, k_1 > 1,  0 < k_2 \leq 2^{k_1}-1,$$

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

正好就对应了海明码最后根据校验码是否为0来找到错误位并取反的过程.

## 回到数据纠错编码
现在来研究$n+k$是从哪来的以及校验位的排列问题.

考虑传输数据的过程中,数据和校验位必须都以一个整体数据中传输过去,否则就要让接收端设计成一个端口接受数据(可能有一个阳性的学生群体),一个端口接受校验码(核酸试剂管),这样设计就很复杂,不如就设计一个端口接受数据,然后设计算法从数据中找到那些校验位,并进行纠错.

因此就需要把核酸试剂管和学生混在一起.让所有的$k$个核酸试剂管和$n$个学生参与这个`自然数排列`,`转换为二进制编号`,`对应数位检测`的过程.

因此总共需要做核酸(纠错)的就有总共就有$L$个:
$$L=n+k$$
那么根据前面的式子,就可以从接受到的待纠错编码长度(核酸,学生总数)$L$计算其中的纠错码数量(试剂管数)$k$:
$$2^k-1\geq L$$

代入$L=n+k$,根据原始数据长度(学生个数)$n$,就能计算需要的纠错码数量(试剂管数)$k$:
$$2^k - 1 \geq n+k$$

假如在检测过程中那个阳性的学生让对应的试剂管变成了1,如果不采取特殊的排列手段,这些变成1的试剂管在$(n+k)$个自然数排列中参与检测就可能会影响别的试剂管.

可能变成1的核酸试剂管之间存在`异管检测`和`自检测`,那么最好的办法就是在自然数排列的时候去掉`异管检测`,只保留`自检测`,让核酸试剂管只和自己检测,不去别的试剂管那里检测.

也就是让这些试剂管正好排在一个2的整数幂的位置,这样试剂管的二进制数位中就只有一个1(设第$i$位为1),这个试剂管就只需要去$i$号试管做检测,因此排列的时候让第$i$个试管排在自然数的$2^{i-1}$个就好了.

这就是为什么第$i$位纠错码需要排列在数据中的$2^{i-1}$位.根据纠错码结果就能指导哪一位出错了,
而这个`检测`本质上就是`异或`操作.

所有`同学去对应试管检测`和`试管自检测`就相当于 **`异或运算`计算校验位的过程**,只需从1到k位,让`i-th`位为1的同学(数据)来`i`试管`检测`(`异或`),这个过程因为都是好数据(好同学),检测结果为全阴性.

传输数据后,可能有数据反相了(同学阳了),数据变为原数据异或1的混合式(同学正常核酸和病毒核酸混合),**组合校验结果**的过程就相当于把所有的同学和试管再做一次检测(`异或`).

阴性的同学(正确数据)参与检测(`异或`)不会使试管变1,而阳性的同学(错误数据)参与`异或`相当于对原有的异或结果做了多做了一次`异或1`,本质上是取了反,就阳了,找到了对应数据:

假设海明码数据排列如下:
$$H_{n+k}H_{n+k-1}...H_2H_1$$
其中每个2的整数幂都是纠错码,共$k$个,初值为0:
$$...P_k...P_{k-1}...P_2P_1$$
$$...H_{2^{k-1}}...H_{2^{k-2}}...H_{2^{1}}H_{2^{0}}$$
首先计算纠错码:
$$
\begin{align*}
P_i &=&H_{1 * 2^{i-1}+1} \oplus ...\oplus  H_{2 * 2^{i-1} - 1} \oplus H_{3 * 2^{i-1}} \oplus ...\\
&= 0 &\oplus H_{1 * 2^{i-1}+1} \oplus ...\oplus  H_{2 * 2^{i-1} - 1} \oplus H_{3 * 2^{i-1}} \oplus ...\\
&= H_{2^{i-1}} &\oplus H_{1 * 2^{i-1}+1} \oplus ...\oplus  H_{2 * 2^{i-1} - 1} \oplus H_{3 * 2^{i-1}} \oplus ...
\end{align*}

$$
则错误数据（阳性同学）的二进制编码中第$i$位为1,指示它参与$S_i$的异或运算,对应的第$i$个异或纠错码$P_i$(此时$P_i$有数值)在自然数中排在第$2^{i-1}$个,没有错误数据情况下:
$$
\begin{align*}
S_i &= P_i &\oplus H_{1 * 2^{i-1}+1} \oplus ...\oplus  H_{2 * 2^{i-1} - 1} \oplus H_{3 * 2^{i-1}}\oplus ...\\
& = 0\\
 &= H_{2^{i-1}} &\oplus H_{1 * 2^{i-1}+1} \oplus ...\oplus  H_{2 * 2^{i-1} - 1} \oplus H_{3 * 2^{i-1}}\oplus ... \\
\end{align*}

$$
据此可以进一步优化上一篇文章中遍历数组找$i$位为1再进行异或运算的过程！

有错误数据情况下,这一位数据对参与运算的$S_i$取了反，即:
$$
\begin{align*}
&S_i &= &H_{2^{i-1}}\oplus H_{1 * 2^{i-1}+1} \oplus ...\oplus  H_{2 * 2^{i-1} - 1} \oplus H_{3 * 2^{i-1}} \oplus ...&\oplus 1 &= 0 \oplus 1 = 1\\
&S_{...} &= &H_{...} \oplus ... &\oplus 1  &= 0 \oplus 1 = 1\\
&...
\end{align*}
$$
## 算法优化
对计算纠错码个数做优化(本质上只是换了个计算方法,没有降低时间复杂度):
```cpp
int getEncodeCorCnt(int encodeDataLength)
{
    int encodeDataDigitCnt = 0;
    while (encodeDataLength)
    {
        encodeDataLength >>= 1;
        encodeDataDigitCnt++;
    }
    return encodeDataDigitCnt;
}
```
对异或运算做优化:
```cpp
int xorOperation(const int powerOf2, const std::vector<int> encodedData)
{
    int xorResult = 0, datasize = encodedData.size();
    for (int i = powerOf2; i <= datasize; i += 2 * powerOf2)
    {
        for (int j = 0; j < powerOf2 && j <= datasize - 1 - (i - 1); j++)
        {
            xorResult ^= encodedData[datasize - 1 - (i - 1) - j];
        }
    }
    return xorResult;
}
```

实测数据量为$2^{20}$时，加速了50%。

源码如下:
```cpp
#include "vector"
#include "string"
#include "iostream"
#include "algorithm"
#include "chrono"
// #include "bits/stdc++.h"
namespace HammingCode
{
    int getRawCorCnt(int rawDataLength)
    {
        int correctionCnt = 0;
        while ((1 << correctionCnt) < rawDataLength + correctionCnt + 1)
        {
            correctionCnt++;
        }
        return correctionCnt;
    }
    int getEncodeCorCnt(int encodeDataLength)
    {
        int encodeDataDigitCnt = 0;
        while (encodeDataLength)
        {
            encodeDataLength >>= 1;
            encodeDataDigitCnt++;
        }
        return encodeDataDigitCnt;
    }
    int xorOperation(const int powerOf2, const std::vector<int> encodedData)
    {
        int xorResult = 0, datasize = encodedData.size();
        for (int i = powerOf2; i <= datasize; i += 2 * powerOf2)
        {
            for (int j = 0; (j < powerOf2) && (datasize - 1 - (i - 1) - j >= 0); j++)
            {
                xorResult ^= encodedData[datasize - 1 - (i - 1) - j];
            }
        }
        return xorResult;
    }
    std::vector<int> encodeData(const std::vector<int> binarydata)
    {
        int rawDataLength = binarydata.size();
        int correctionCnt = getRawCorCnt(rawDataLength);
        int encodedLength = rawDataLength + correctionCnt;
        std::vector<int> encodedData(encodedLength, 0);
        // Traverse the encodedData vector.
        for (int i = 0, j = 0; i < encodedLength; i++)
        {
            // If the (i+1)-th digit is not power of 2.
            if (((i + 1) & i) != 0)
            {
                // Copy data.
                encodedData[encodedLength - 1 - i] = binarydata[rawDataLength - 1 - (j++)];
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
        int correctionCnt = getEncodeCorCnt(encodedLength);
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
    std::vector<int> rawdata;
    for (int i = 0; i < 1 << 20 - 1; i++)
    {
        if (i % 62 == 0)
            rawdata.push_back(0);
        else
            rawdata.push_back(1);
    }
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> encodedData = HammingCode::encodeData(rawdata);
    std::cout << "encodedData:\n";
    // std::for_each(encodedData.begin(), encodedData.end(), [](int val)
    //               { std::cout << val; });

    encodedData[2] ^= 1;
    std::vector<int> dataToCorrect = encodedData;
    //     std::cout << "dataToCorrect:\n";
    // std::for_each(dataToCorrect.begin(), dataToCorrect.end(), [](int val)
    //               { std::cout << val; });

    std::vector<int> correctedData = HammingCode::decodeDataAndCorrect(dataToCorrect);
    std::cout << "\ncorrectedData:\n";
    // std::for_each(correctedData.begin(), correctedData.end(), [](int val)
    //               { std::cout << val; });
    auto end = std::chrono::high_resolution_clock::now();
    // std::cout << "\nTime taken: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << "ns\n";
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "\nTime taken by function: "
              << duration.count() << " microseconds" << std::endl;
    // 57008 microseconds
    // Original algorithm takes 103480 microseconds
    return 0;
}

```

## What-If?
假如不止一位数据出错了呢,设想把数据分为两组,对每一组就可以做海明码纠错,再增加一位纠错码用01来区分是前一组还是后一组,就可以纠错两位,这样继续增加纠错码,从而纠更多的位,在此不证明...