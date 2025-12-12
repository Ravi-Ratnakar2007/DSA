#include <iostream>
#include<vector>
#include <string.h>

using namespace std;

string convert2binary(int n){
    string res="";

    while(n!=1){
        if(n%2==1) res=res+"1";
        else res+="0";
        n=n/2;
    }
    reverse(res.begin(),res.end());
    return res;
}
int convert2decimal(string bin){
    int n = bin.size();
    int p2=1;
    int num=0;
    for(int i=n-1;i>=0;i--){
        if(bin[i]==1){
            num=num+p2;
        }
        p2*=2;
    }
    return num;
}
//Swap 2 no. without 3rd variable
void swap2no(int& a, int& b){
    a=a^b;
    b=a^b;
    a=a^b;
}
//Check if ith bit is set or not
// Use bit masking to isolate the i-th bit in the binary representation of the number.
// By shifting 1 to the left i times, you create a mask where only the i-th bit is set.
// Perform a bitwise AND between the number and the mask to check if that specific bit is active.
// If the result is non-zero, the i-th bit is set to 1; otherwise, it is 0.

bool checkIthBit(int n, int i) {
    // Check if the i-th bit is set using bitwise AND operation
    return (n & (1 << i)) != 0;  // If the i-th bit is 1, the result will be non-zero
}
//Set the iTh bit
int setithbit(int n,int i){
    return (n |(i<<i));
}
//clear the ith bit
int clearithbit(int n,int i){
    return(n|(~(1<<i)));
}
//Toggle ith bit
int togglebit(int n,int i){
    return (n^(1<<i));
}
//Clear the last set bit
int clear_lastsetbit(int n){
    return (n&(n-1));
}
//check if the no is power of 2(implication of above ques)
bool isPowerof2(int n){
    return ((n&(n-1))==0);
}
//Count no of set bits
int countsetbits(int n){
    int cnt=0;
    while(n>1){
        if(n&1==0)cnt++;//n&1 is same as n%2
        n=n/2;
    }
    if(n==1) cnt++;
    return cnt;
}
//Another method
int countsetbits_better(int n){
    int cnt=0;
    while(n!=0){
        n=n&n-1;
        cnt++;
    }
    return cnt;
}
//Divide two integers without using multiplication, division and mod operator
//Brute
int div_brute(int dividend, int divisor){
    int sum=0,cnt=0;
    while(sum+divisor<=dividend){
        cnt++;
        sum+=divisor;
    }
    return cnt;
}
//Optimal
int divide(int dividend, int divisor) {
    if(dividend == divisor) return 1;
    if(dividend == INT_MIN && divisor == -1) return INT_MAX;
    if(divisor == 1) return dividend;
    
    // Variable to store the sign of result
    bool isPositive = true;
    
    // Updating the sign of quotient
    if(dividend >= 0 && divisor < 0) 
        isPositive = false;
    else if(dividend < 0 && divisor > 0)
        isPositive = false;
        
    // Storing absolute dividend & divisor
    long long n = dividend;
    long long d = divisor;

    n = abs(n);
    d = abs(d);
    
    // Variable to store the answer and sum
    long long ans = 0, sum = 0;
    
    /* Looping while sum added to divisor is
    less than or equal to divisor */
    while(sum + d <= n) {
        
        // Increment the count
        ans++;
        // Update the sum
        sum += d;
    }
    
    // Handling overflowing condition
    if(ans > INT_MAX && isPositive) 
        return INT_MAX;
    if(ans > INT_MAX && !isPositive)
        return INT_MIN;
    
    /* Returning the quotient 
    with proper sign */
    return isPositive ? ans : -1*ans;
}
//Minimum Bit flips to convert No.
//find output which contains 1 for different bit feilds
//find no of set bit feild in output
int minBitFlips(int start, int goal) {
    int flips=0;
    int output=start^goal;
    flips=countsetbits_better(output);
    return flips;        
}
// Sieve of Eratosthenes:
// Create a boolean array isPrime[0...n], initially set all values to true.
// Set isPrime[0] = false and isPrime[1] = false (0 and 1 are not prime).
// Start from p = 2, the first prime number.
// For each p:
// If isPrime[p] is true, mark all multiples of p (i.e., p*2, p*3, …) as false.
// Continue this process until p * p > n (no need to go beyond √n).
// At the end, isPrime[i] tells whether i is a prime number.

// Algorithm for the question:
// Use the Sieve of Eratosthenes to mark all primes up to the maximum value R in any query.
// Build a prefix sum array primeCount[i] where each element represents the number of primes ≤ i.
// For each query [L, R], calculate count = primeCount[R] - primeCount[L-1].
// Return the result for each query.

int countPrimes(int n) {
    vector<bool> primes(n,true);
    int count = 0;
    for(int i = 2;i < n; i++){
        if(primes[i]){
            count++;
        for(int j = i; j < n; j+=i){
            primes[j] = false;
        }
        }
    }
    return count;
}