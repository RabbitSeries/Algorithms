#include "vector"
#include "string"
#include "iostream"
#include "algorithm"
#include "chrono"
// #include "bits/stdc++.h"
namespace HammingCode {
int xorOperation(const int pos, const std::vector<int> encodedData) {
    int xorResult = 0;
    // Traverse the encoded vector, operating xor operation with specific digits.
    for (int i = 0; i < encodedData.size(); i++) {
        // If the corresponding digit of index is 1, do the XORs.
        if ((pos & (i + 1)) != 0) {
            // Remind that the correction digit initial value is 0, which does not contribute to the XOR operation.
            // Remind that the xorResult initial value is 0, which still does not contribute to the XOR operation and ensures the operation to include the correction digit.
            xorResult ^= encodedData[encodedData.size() - 1 - i];
        }
    }
    return xorResult;
}
std::vector<int> encodeData(const std::vector<int> binarydata) {
    int rawDataLength = binarydata.size();
    int correctionCnt = 0;
    while ((1 << correctionCnt) < rawDataLength + correctionCnt + 1) {
        correctionCnt++;
    }
    int encodedLength = rawDataLength + correctionCnt;
    std::vector<int> encodedData(encodedLength, 0);
    // Traverse the encodedData vector.
    for (int i = 0, j = 0; i < encodedLength; i++) {
        // If the (i+1)-th digit is not power of 2.
        if (((i + 1) & i) != 0) {
            // Copy data.
            encodedData[encodedLength - 1 - i] = binarydata[rawDataLength - 1 - (j++)];
        }
    }
    // Traverse the correctionDigits
    for (int i = 0; i < correctionCnt; i++) {
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

std::vector<int> decodeDataAndCorrect(std::vector<int> encodedData) {
    int encodedLength = encodedData.size();
    int correctionCnt = 0;
    while ((1 << correctionCnt) < encodedLength + 1) {
        correctionCnt++;
    }
    int datalength = encodedLength - correctionCnt;
    int errorCode = 0;
    // Traverse the correctionDigits
    for (int i = 0; i < correctionCnt; i++) {
        // The correctionCode's digit position (starts from 1).
        int correctionPos = 1 << i;
        // The val in data vector.
        int xorResult = 0;
        xorResult = xorOperation(correctionPos, encodedData);
        // Amazing huh?
        errorCode |= xorResult << i;
    }
    // If errorCode is not 0, correct the data.
    if (errorCode != 0) {
        // The error code is the position of the error bit.
        encodedData[encodedLength - 1 - (errorCode - 1)] ^= 1;
    }
    return encodedData;
}
}

int main() {
    std::vector<int> rawdata;
    for (int i = 0; i < 1 << 26 - 1; i++) {
        if (!(i % 62))
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
    // 3976277 microseconds
    return 0;
}
