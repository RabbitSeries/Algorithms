#include "vector"
#include "string"
#include "iostream"
#include "algorithm"
#include "chrono"
// #include "bits/stdc++.h"
namespace HammingCode {
int getRawCorCnt(int rawDataLength) {
    int correctionCnt = 0;
    while ((1 << correctionCnt) < rawDataLength + correctionCnt + 1) {
        correctionCnt++;
    }
    return correctionCnt;
}
int getEncodeCorCnt(int encodeDataLength) {
    int encodeDataDigitCnt = 0;
    while (encodeDataLength) {
        encodeDataLength >>= 1;
        encodeDataDigitCnt++;
    }
    return encodeDataDigitCnt;
}
int xorOperation(const int powerOf2, const std::vector<int> encodedData) {
    int xorResult = 0, datasize = encodedData.size();
    for (int i = powerOf2; i <= datasize; i += 2 * powerOf2) {
        for (int j = 0; (j < powerOf2) && (datasize - 1 - (i - 1) - j >= 0); j++) {
            xorResult ^= encodedData[datasize - 1 - (i - 1) - j];
        }
    }
    return xorResult;
}
std::vector<int> encodeData(const std::vector<int> binarydata) {
    int rawDataLength = binarydata.size();
    int correctionCnt = getRawCorCnt(rawDataLength);
    int encodedLength = rawDataLength + correctionCnt;
    std::vector<int> encodedData(encodedLength, 0);
    for (int i = 0, j = 0; i < encodedLength; i++) {
        if (((i + 1) & i) != 0) {
            encodedData[encodedLength - 1 - i] = binarydata[rawDataLength - 1 - (j++)];
        }
    }
    // Traverse the correctionDigits
    for (int i = 0; i < correctionCnt; i++) {
        int correctionPos = 1 << i;
        int correctionDigitVal = 0;
        correctionDigitVal = xorOperation(correctionPos, encodedData);
        encodedData[encodedLength - 1 - (correctionPos - 1)] = correctionDigitVal;
    }
    return encodedData;
}

std::vector<int> decodeDataAndCorrect(std::vector<int> encodedData) {
    int encodedLength = encodedData.size();
    int correctionCnt = getEncodeCorCnt(encodedLength);
    int datalength = encodedLength - correctionCnt;
    int errorCode = 0;
    for (int i = 0; i < correctionCnt; i++) {
        int correctionPos = 1 << i;
        int xorResult = 0;
        xorResult = xorOperation(correctionPos, encodedData);
        errorCode |= xorResult << i;
    }
    if (errorCode != 0) {
        encodedData[encodedLength - 1 - (errorCode - 1)] ^= 1;
    }
    return encodedData;
}
}

int main() {
    std::vector<int> rawdata;
    for (int i = 0; i < 1 << 26 - 1; i++) {
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
    // 2226742 microseconds
    return 0;
}
