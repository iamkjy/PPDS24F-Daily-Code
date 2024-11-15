// 참고 : https://leetcode.com/problems/minimum-one-bit-operations-to-make-integers-zero/solutions/4345996/easiest-approach-maths-recursive-lc-hard-lc-daily-nov-30

// 이 문제를 풀려면 직접 여러 case를 적어보고 규칙을 찾는수밖에 없다.

#include <cmath> // pow 함수를 사용
class Solution {
public:
    int minimumOneBitOperations(int n) {
        if (n == 0) //0일 경우 더이상 연산할 필요가 없어서 0 반환
            return 0;
        
        // 가장 왼쪽에서 켜져 있는 비트 위치를 찾습니다.
        int k = 0;
        while ((1 << k) <= n) // 1<<k는 2^k  : 따라서 이 loop는 k를 증가시키면서 2^k가 n보다 작거나 같은지 확인. k는 n의 가장 높은 비트 위치가 됨.
            k++;
        k--;  // k는 가장 높은 비트 위치를 나타냅니다. (위 while문 통과하면 마지막 k값이 n의 비트수를 초과해서 하나 줄여줌.--? 가장 높은 위치로 조정.)

        // 연산의 결과는 `2^(k+1) - 1` 연산 (0에서 2^k까지의 모든 비트를 0으로 만들기 위해 필요한 최대 연산 수)에서 재귀적으로 줄여 나가는 연산을 뺀 것입니다.
        // minimumOneBitOperations((1 << k) ^ n) : ((1 << k) ^ n)는 n에서 가장 높은 비트만 반전시킨 값
        // 최대에서 minimumOneBitOperations((1 << k) ^ n) 이 값을 빼 줌으로써 최소 연산횟수 결정
        return pow(2, k + 1) - 1 - minimumOneBitOperations((1 << k) ^ n);
    }

};


//------------[규칙찾는 과정]-------------------
/*

현재 숫자: 0
최소 연산 수: 0 (더 이상 연산할 필요 없음)
n = 1 (이진수 1)

현재 숫자: 1
연산: 1 -> 0 (1번 연산)
최소 연산 수: 1
n = 2 (이진수 10)

현재 숫자: 2
연산:
10 -> 00 (2번 연산: 2를 1로 바꾼 후 다시 0으로)
최소 연산 수: 3
n = 3 (이진수 11)

현재 숫자: 3
연산:
11 -> 10 (1번 연산)
10 -> 00 (2번 연산)
최소 연산 수: 2
n = 4 (이진수 100)

현재 숫자: 4
연산:
100 -> 000 (3번 연산)
최소 연산 수: 7
n = 5 (이진수 101)

현재 숫자: 5
연산:
101 -> 100 (1번 연산)
100 -> 000 (3번 연산)
최소 연산 수: 5
n = 6 (이진수 110)

현재 숫자: 6
연산:
110 -> 010 (1번 연산)
010 -> 000 (2번 연산)
최소 연산 수: 3
n = 7 (이진수 111)

현재 숫자: 7
연산:
111 -> 110 (1번 연산)
110 -> 100 (1번 연산)
100 -> 000 (3번 연산)
최소 연산 수: 5

*/

/*규칙 도출
발견가능한 패턴
    1. 비트 수의 증가: 각 비트 수에 대해 숫자가 증가할 때마다 필요한 최소 연산 수가 증가하는 경향
    2. 특정 비트에 따라 달라짐: 가장 높은 비트가 1로 설정된 경우, 해당 비트를 0으로 만들기 위해 필요한 연산 수가 많아짐
    3. 1비트의 역할: 설정된 비트를 반전시키는 과정에서 연산의 수가 크게 줄어들거나 늘어날 수 있음.