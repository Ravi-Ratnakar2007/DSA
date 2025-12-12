#include <iostream>
#include<vector>
#include <map>
#include <unordered_set>
#include <algorithm>    
#include <set>


using namespace std;

//Question 1 (2Sum)
// Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
// You may assume that each input would have exactly one solution, and you may not use the same element twice.
// You can return the answer in any order.
// Input: nums = [2,7,11,15], target = 9
// Output: [0,1]
// Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> mp; 
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        if (mp.find(complement) != mp.end()) {
            return {mp[complement], i}; 
        }
        mp[nums[i]] = i;
    }
    return {};
}


//Question 2
// Given an array nums with n objects colored red, white, or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.
// We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.
// You must solve this problem without using the library's sort function.
// Example 1:
// Input: nums = [2,0,2,1,1,0]
// Output: [0,0,1,1,2,2]

//Brute(Merge Sort)
void merge(vector<int> &arr,int low, int mid, int high){
    vector<int> temp;
    int left = low;
    int right = mid+1;
    while(left<=mid && right<=high){
        if(arr[left]<= arr[right]){
            temp.push_back(arr[left]);
            left++;
        }else {
            temp.push_back(arr[right]);
            right--;
        }
    }

    while(left<=mid){
        temp.push_back(arr[left]);
        left++;
    }

    while(right<=high){
        temp.push_back(arr[right]);
        right++;
    }
    
    for(int i = low;i<=high;i++){
        arr[i]=temp[i-low];

    }


}
void mS(vector<int> &arr,int low, int high){
    if(low==high) return;
    int mid =(low + high)/2;
    mS(arr,low,mid);
    mS(arr,mid+1,high);
    merge(arr,low,mid,high);
}
void MergeSort(vector<int> &arr, int n){
    mS(arr, 0, n-1);


}
//Better(Counting no of 0s,1s,2s and then placing those values accordingly)
void order(vector<int>& nums){
    int count_0=0,count_1=0,count_2=0;
    for(int i=0;i<nums.size();i++){
        if(nums[i]==0) count_0++;
        if(nums[i]==1) count_1++;
        if(nums[i]==2) count_2++;
    }
    for(int i=0;i<count_0;i++){
        nums[i]=0;
    }
    for(int i =count_0;i<count_0+count_1;i++){
        nums[i]=1;
    }
    for(int i =count_0+count_1;i<nums.size();i++){
        nums[i]=2;
    }
}

//****Optimal Solution (Dutch National flag algorithm)
// This algorithm contains 3 pointers i.e. low, mid, and high, and 3 main rules.  The rules are the following:

// arr[0….low-1] contains 0. [Extreme left part]
// arr[low….mid-1] contains 1.
// arr[high+1….n-1] contains 2. [Extreme right part], n = size of the array
// The middle part i.e. arr[mid….high] is the unsorted segment. So, hypothetically the array with different markers will look like the following:
// In our case, we can assume that the entire given array is unsorted and so we will place the pointers accordingly. For example, if the given array is: [2,0,2,1,1,0], the array with the 3 pointers will look like the following:
// Here, as the entire array is unsorted, we have placed the mid pointer in the first index and the high pointer in the last index. The low is also pointing to the first index as we have no other index before 0. Here, we are mostly interested in placing the ‘mid’ pointer and the ‘high’ pointer as they represent the unsorted part in the hypothetical array.
// Now, let’s understand how the pointers will work to make the array sorted.

// Approach:
// Note: Here in this tutorial we will work based on the value of the mid pointer.
// The steps will be the following:
// First, we will run a loop that will continue until mid <= high.
// There can be three different values of mid pointer i.e. arr[mid]
// If arr[mid] == 0, we will swap arr[low] and arr[mid] and will increment both low and mid. Now the subarray from index 0 to (low-1) only contains 0.
// If arr[mid] == 1, we will just increment the mid pointer and then the index (mid-1) will point to 1 as it should according to the rules.
// If arr[mid] == 2, we will swap arr[mid] and arr[high] and will decrement high. Now the subarray from index high+1 to (n-1) only contains 2.
// In this step, we will do nothing to the mid-pointer as even after swapping, the subarray from mid to high(after decrementing high) might be unsorted. So, we will check the value of mid again in the next iteration.
// Finally, our array should be sorted.
void Dutch_algo(vector<int>& nums){
    int high=nums.size(),low=0,mid=0;
    while(mid<=high){
        if(nums[mid]==0){
            swap(nums[mid],nums[low]);
            low++;
            mid++;
        }
        if(nums[mid]==1){
            mid++;
        }
        if(nums[mid]==2){
            swap(nums[mid],nums[high]);
            high--;
        }
    }
}




// Question 3
// Given an array nums of size n, return the majority element.
// The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

//Better approach(Hashing)
int hash_major(vector<int>& nums){
    map<int,int> mpp;
    for(int i =0;i<nums.size();i++){
        mpp[nums[i]]++;
    }
    for(auto it:mpp){
        if(it.second > (nums.size()/2))
        return it.first;
    }
    return -1;
}

//Optimal SOl(Moore's Voting Algorithm)
// Intuition
// If the array contains a majority element, its occurrence must be greater than the floor(N/2). Now, we can say that the count of minority elements and majority elements is equal up to a certain point in the array. So when we traverse through the array we try to keep track of the count of elements and the element itself for which we are tracking the count. 
// After traversing the whole array, we will check the element stored in the variable. If the question states that the array must contain a majority element, the stored element will be that one but if the question does not state so, then we need to check if the stored element is the majority element or not. If not, then the array does not contain any majority element.

// Approach: 
// Initialize 2 variables:
// Count –  for tracking the count of element
// Element – for which element we are counting
// Traverse through the given array.
// If Count is 0 then store the current element of the array as Element.
// If the current element and Element are the same increase the Count by 1.
// If they are different decrease the Count by 1.
// The integer present in Element should be the result we are expecting

int moore_algo(vector<int>& nums){
    int el;
    int count=0;
    for(int i =0;i<nums.size();i++){
        if(count==0){
            el= nums[i];
        }else if(nums[i]==el){
            count++;
        }else{
            count--;
        }
    }

    return el;

    //To be run , if no major element is necessarily present
    // int count1=0;
    // for(int i =0;i<nums.size();i++){
    //     if(nums[i]==el) count1++;

    // }
    // if(count1 > ((nums.size())/2)){
    //     return el;
    // }


}


//Question 4
//Maximum Subaaray
//Given an integer array nums, find the subarray with the largest sum, and return its sum.

//Brute Force
//Iterating through all subaaray
int major_brute(vector<int>& nums){
    int maxsum=INT16_MIN;
    for(int i =0;i<nums.size();i++){
        int sum=0;
        for(int j =i;j<nums.size();j++){
            
            sum += nums[j];
            maxsum=max(maxsum,sum);
        }
    }
    return maxsum;
}

//OptimalApproach (Kadane`s Algo)
// The intuition of the algorithm is not to consider the subarray as a part of the answer if its sum is less than 0. A subarray with a sum less than 0 will always reduce our answer and so this type of subarray cannot be a part of the subarray with maximum sum.
// Here, we will iterate the given array with a single loop and while iterating we will add the elements in a sum variable. Now, if at any point the sum becomes less than 0, we will set the sum as 0 as we are not going to consider any subarray with a negative sum. Among all the sums calculated, we will consider the maximum one.
// Thus we can solve this problem with a single loop.
// Approach:
// The steps are as follows:
// We will run a loop(say i) to iterate the given array.
// Now, while iterating we will add the elements to the sum variable and consider the maximum one.
// If at any point the sum becomes negative we will set the sum to 0 as we are not going to consider it as a part of our answer.
int major_opt(vector<int>& nums){
    int sum=0, maxi=INT16_MIN;
    for(int i =0;i<nums.size();i++){
        sum+=nums[i];

        if(sum>maxi){
            maxi=sum;
        }

        if(sum<0){
            sum=0;
        }
    }

}

//Question 5(Stock Buy and Sell)
// You are given an array prices where prices[i] is the price of a given stock on the ith day.
// You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
// Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.
//Sol-

int stock_exg(vector<int>& prices){
    int mini= prices[0];
    int profit =0;
    int cost=0;
    for(int i=0;i<prices.size();i++){
        cost = prices[i]-mini;
        profit= max(profit,cost);
        mini=min(prices[i], mini);
    }

    return profit;
}


//Question 5
// Rearrange Array Elements by Sign
// You are given a 0-indexed integer array nums of even length consisting of an equal number of positive and negative integers.
// You should return the array of nums such that the the array follows the given conditions:
// Every consecutive pair of integers have opposite signs.
// For all integers with the same sign, the order in which they were present in nums is preserved.
// The rearranged array begins with a positive integer.
// Return the modified array after rearranging the elements to satisfy the aforementioned conditions.

//My method
vector<int> rearrage(vector<int>& nums){
    vector<int> temp;
    int posiindex=0,negindex=1;
    for(int i =0;i<nums.size();i++){

        if(nums[i]>=0){
            temp[posiindex]=nums[i];
            posiindex+=2;

        }else{
            temp[negindex]=nums[i];
            negindex+=2;
        }
    }
    
    return temp;
}

//Question 6
// A permutation of an array of integers is an arrangement of its members into a sequence or linear order.
// For example, for arr = [1,2,3], the following are all the permutations of arr: [1,2,3], [1,3,2], [2, 1, 3], [2, 3, 1], [3,1,2], [3,2,1].
// The next permutation of an array of integers is the next lexicographically greater permutation of its integer. More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, then the next permutation of that array is the permutation that follows it in the sorted container. If such arrangement is not possible, the array must be rearranged as the lowest possible order (i.e., sorted in ascending order).
// For example, the next permutation of arr = [1,2,3] is [1,3,2].
// Similarly, the next permutation of arr = [2,3,1] is [3,1,2].
// While the next permutation of arr = [3,2,1] is [1,2,3] because [3,2,1] does not have a lexicographical larger rearrangement.
// Given an array of integers nums, find the next permutation of nums.

//Brute(Generate all permutation -> Linear Search -> Next permutation)
//Highly time taking


//Optimal Solution
// Find the break-point, i: Break-point means the first index i from the back of the given array where arr[i] becomes smaller than arr[i+1].
// For example, if the given array is {2,1,5,4,3,0,0}, the break-point will be index 1(0-based indexing). Here from the back of the array, index 1 is the first index where arr[1] i.e. 1 is smaller than arr[i+1] i.e. 5.
// To find the break-point, using a loop we will traverse the array backward and store the index i where arr[i] is less than the value at index (i+1) i.e. arr[i+1].
// If such a break-point does not exist i.e. if the array is sorted in decreasing order, the given permutation is the last one in the sorted order of all possible permutations. So, the next permutation must be the first i.e. the permutation in increasing order.
// So, in this case, we will reverse the whole array and will return it as our answer.
// If a break-point exists:
// Find the smallest number i.e. > arr[i] and in the right half of index i(i.e. from index i+1 to n-1) and swap it with arr[i].
// Reverse the entire right half(i.e. from index i+1 to n-1) of index i. And finally, return the array.

vector<int> permute_next(vector<int>& nums){
        int ind=-1;
        int n = nums.size();
        for(int i =n-2;i>=0;i--){
            if(nums[i]<nums[i+1]){
                ind =i;
                break;
            }
        }
        
        if(ind ==-1){
            reverse(nums.begin(),nums.end());
        }else{
            for(int i =n-1;i>ind;i--){
                if(nums[i]>nums[ind]){
                    swap(nums[i],nums[ind]);
                    break;
                }
            }

            reverse(nums.begin()+ind+1,nums.end());

        }

        

        return nums;
}

//Question 7
// Longest Consecutive Sequence
// Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.
// You must write an algorithm that runs in O(n) time.

//Brute (Fix on a number and try to find next element in the array, and find max length of sequence)
int longest_brute(vector<int>& nums){
    int longest =1;
    int x,count=0;
    for(int i =0;i<nums.size();i++){
        x = nums[i];
        count =1;

        while(ls(nums,x+1)==true){
            x=x+1;
            count+=1;
        }

    }
}
//Linear Search(part of Brute)
bool ls(vector<int>& nums,int n){
    for(int i=0;i<nums.size();i++){
        if(nums[i]==n){
            return true;

        }
    }
    return false;
}

//Better Sol
// First, we will sort the entire array.
// To begin, we will utilize a loop(say i) to iterate through each element one by one.
// For every element, we will check if this can be a part of the current sequence like the following:
// If arr[i]-1 == lastSmaller: The last element in our sequence is labeled as 'lastSmaller' and the current element 'arr[i]' is exactly 'lastSmaller'+1. It indicates that 'arr[i]' is the next consecutive element. To incorporate it into the sequence, we update 'lastSmaller' with the value of 'arr[i]' and increment the length of the current sequence, denoted as 'cnt', by 1.
// If arr[i] == lastSmaller: If the current element, arr[i], matches the last element of the sequence (represented by 'lastSmaller'), we can skip it since we have already included it before.
// Otherwise, if lastSmaller != arr[i]: On satisfying this condition, we can conclude that the current element, arr[i] > lastSmaller+1. It indicates that arr[i] cannot be a part of the current sequence. So, we will start a new sequence from arr[i] by updating ‘lastSmaller’ with the value of arr[i]. And we will set the length of the current sequence(cnt) to 1.
// Every time, inside the loop, we will compare ‘cnt’ and ‘longest’ and update ‘longest’ with the maximum value. longest = max(longest, cnt)
// Finally, once the iteration is complete, we will have the answer stored in the variable ‘longest’.irst, we will sort the entire array.
// To begin, we will utilize a loop(say i) to iterate through each element one by one.
// For every element, we will check if this can be a part of the current sequence like the following:
// If arr[i]-1 == lastSmaller: The last element in our sequence is labeled as 'lastSmaller' and the current element 'arr[i]' is exactly 'lastSmaller'+1. It indicates that 'arr[i]' is the next consecutive element. To incorporate it into the sequence, we update 'lastSmaller' with the value of 'arr[i]' and increment the length of the current sequence, denoted as 'cnt', by 1.
// If arr[i] == lastSmaller: If the current element, arr[i], matches the last element of the sequence (represented by 'lastSmaller'), we can skip it since we have already included it before.
// Otherwise, if lastSmaller != arr[i]: On satisfying this condition, we can conclude that the current element, arr[i] > lastSmaller+1. It indicates that arr[i] cannot be a part of the current sequence. So, we will start a new sequence from arr[i] by updating ‘lastSmaller’ with the value of arr[i]. And we will set the length of the current sequence(cnt) to 1.
// Every time, inside the loop, we will compare ‘cnt’ and ‘longest’ and update ‘longest’ with the maximum value. longest = max(longest, cnt)
// Finally, once the iteration is complete, we will have the answer stored in the variable ‘longest’.

int longest_better(vector<int>& nums){
    int longest =1;
    int curcount=0;
    int lastsmaller=INT16_MIN;
    sort(nums.begin(),nums.end());
    for(int i =0;i<nums.size();i++){
        if(nums[i]-1==lastsmaller){
            curcount+=1;
            lastsmaller=nums[i];
        }else if(nums[i]==lastsmaller){

        }else{
            curcount=1;
            lastsmaller=nums[i];
        }
        longest=max(longest,curcount);
    }
    return longest;

}

//Optimal Solution
// First, we will put all the array elements into the set data structure.
// If a number, num, is a starting number, ideally, num-1 should not exist. So, for every element, x, in the set, we will check if x-1 exists inside the set. :
// If x-1 exists: This means x cannot be a starting number and we will move on to the next element in the set.
// If x-1 does not exist: This means x is a starting number of a sequence. So, for number, x, we will start finding the consecutive elements.
// How to search for consecutive elements for a number, x:
// Instead of using linear search, we will use the set data structure itself to search for the elements x+1, x+2, x+3, and so on.
// Thus, using this method we can narrow down the search and optimize the approach.

int longest_optimal(vector<int>& nums){
    int n = nums.size();
    if(n==0) return 0;
    int longest =1;
    unordered_set<int> st;
    for(int i =0;i,n;i++){
        st.insert(nums[i]);
    }

    for(auto it: st){
        if(st.find(it-1)==st.end()){
            int count =1;
            int x =it;
            while(st.find(x+1) != st.end()){
                x=x+1;
                count +=1;

            }
            longest=max(longest,count);
        }

    }
    return longest;
}

//Question 8
// Set Matrix Zeroes
// Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0's.
// You must do it in place.

// Brute Sol
// First, we will use two loops(nested loops) to traverse all the cells of the matrix.
// If any cell (i,j) contains the value 0, we will mark all cells in row i and column j with -1 except those which contain 0.
// We will perform step 2 for every cell containing 0.
// Finally, we will mark all the cells containing -1 with 0.
// Thus the given matrix will be modified according to the question.

void matrix_brute(vector<vector<int>>& matrix){
    int n = matrix.size();
    for(int i =0;i<n;i++){
        int m =matrix[i].size();
        for(int j =0;j<m;j++){
            if(matrix[i][j]==0){
                Markrow(matrix,i,m);
                Markcol(matrix,j,n);
            }
        }
    }
    for(int i =0;i<n;i++){
        int m =matrix[i].size();
        for(int j =0;j<m;j++){  
            if(matrix[i][j]==-1){
                matrix[i][j]=0;
            }
        }
    }
}
void Markrow(vector<vector<int>>& matrix,int i,int m){
    for(int j =0;j<m;j++){
        if(matrix[i][j]!=0){
            matrix[i][j]=-1;
        }
    }
}
void Markcol(vector<vector<int>>& matrix,int j,int n){
    for(int i =0;i<n;i++){
        if(matrix[i][j]!=0){
            matrix[i][j]=-1;
        }
    }
}

//Better Sol
// First, we will declare two arrays: a row array of size N and a col array of size M and both are initialized with 0.
// Then, we will use two loops(nested loops) to traverse all the cells of the matrix.
// If any cell (i,j) contains the value 0, we will mark ith index of row array i.e. row[i] and jth index of col array col[j] as 1. It signifies that all the elements in the ith row and jth column will be 0 in the final matrix.
// We will perform step 3 for every cell containing 0.
// Finally, we will again traverse the entire matrix and we will put 0 into all the cells (i, j) for which either row[i] or col[j] is marked as 1.
// Thus we will get our final matrix.

void matrix_better(vector<vector<int>>& matrix){
    int n = matrix.size();
    int m = matrix[0].size();

    vector<int> col(n,0);
    vector<int> row(n,0);

    for(int i=0;i<n;i++){
        for(int j =0;j<m;j++){
            if(matrix[i][j]==0){
                col[j]=1;
                row[i]=0;
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j =0;j<m;j++){
            if(row[i] || col[j]){
                matrix[i][j]=0;
            }
        }
    }
}

//Optimal Approach
// First, we will traverse the matrix and mark the proper cells of 1st row and 1st column with 0 accordingly. The marking will be like this: if cell(i, j) contains 0, we will mark the i-th row i.e. matrix[i][0] with 0 and we will mark j-th column i.e. matrix[0][j] with 0.
// If i is 0, we will mark matrix[0][0] with 0 but if j is 0, we will mark the col0 variable with 0 instead of marking matrix[0][0] again.
// After step 1 is completed, we will modify the cells from (1,1) to (n-1, m-1) using the values from the 1st row, 1st column, and col0 variable.
// We will not modify the 1st row and 1st column of the matrix here as the modification of the rest of the matrix(i.e. From (1,1) to (n-1, m-1)) is dependent on that row and column.
// Finally, we will change the 1st row and column using the values from matrix[0][0] and col0 variable. Here also we will change the row first and then the column.
// If matrix[0][0] = 0, we will change all the elements from the cell (0,1) to (0, m-1), to 0.
// If col0 = 0, we will change all the elements from the cell (0,0) to (n-1, 0), to 0.

void matrix_optimal(vector<vector<int>>& matrix){
    int n = matrix.size();
    int m = matrix[0].size();

    int col0=1;

    for(int i=0;i<n;i++){
        for(int j =0;j<m;j++){
            if(matrix[i][j]==0){
             

                if(j!=0)
                    matrix[0][j]=0;
                else
                    col0=0;
                
            }
        }
    }

    for(int i =1;i<n;i++){
        for(int j=1;j<m;j++){
            if(matrix[i][j]!=0){
                if(matrix[i][0]==0 || matrix[0][j]==0){
                    matrix[i][j]=0;
                }
            }
        }
    }

    if(matrix[0][0]==0){
        for(int j=0;j<m;j++){
            matrix[0][j]=0;
        }
    }
    if(col0==0){
        for(int i =0;i<n;i++){
            matrix[i][0]=0;
        }
    }
}

//Question 9
// Rotate Image
// You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).
//You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.

//Brute Sol
//We take another matrix and rotate accordingly
//But we will take too much space

//Optimal Sol
// Step 1: Transpose the matrix. (transposing means changing columns to rows and rows to columns)
// Step 2: Reverse each row of the matrix.

void rotate_optimal(vector<vector<int>>& matrix){
    int n = matrix.size();
    for(int i =0;i<n-1;i++){
        for(int j =i+1;j<n;j++){
            swap(matrix[i][j],matrix[j][i]);
        }
    }

    for(int i=0;i<n;i++){
        reverse(matrix[i].begin(), matrix[i].end());
    }
}

//Question 10
// Spiral Matrix
// Given an m x n matrix, return all elements of the matrix in spiral order.

//Onl one solution to this problem
void spiral(vector<vector<int>>& matrix){
    int n = matrix.size();
    int m = matrix[0].size();
    int left =0, right = m-1;
    int top=0,bottom=n-1;

    vector<int> ans;

    while(top<=bottom && left<=right){
        //right
        for(int i = left;i<=right;i++){
            ans.push_back(matrix[top][i]);
        }
        top++;

        //down
        for(int i =top;i<=bottom;i++){
            ans.push_back(matrix[i][right]);
        }
        right--;

        if(top<=bottom){
            //left
            for(int i =right;i>=left;i--){
                ans.push_back(matrix[bottom][i]);
            }
            bottom--;
        }
        if(left<=right){
            //Up
            for(int i =bottom;i>=top;i--){
                ans.push_back(matrix[i][left]);
            }
            left++;
        }

    }
}

//Question 11
// Subarray Sum Equals K
// Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.
// A subarray is a contiguous non-empty sequence of elements within an array


//Brute
//We can check all subarrays

//Optimal Sol
// First, we will declare a map to store the prefix sums and their counts.
// Then, we will set the value of 0 as 1 on the map.
// Then we will run a loop(say i) from index 0 to n-1(n = size of the array).
// For each index i, we will do the following:
// We will add the current element i.e. arr[i] to the prefix sum.
// We will calculate the prefix sum i.e. x-k, for which we need the occurrence.
// We will add the occurrence of the prefix sum x-k i.e. mpp[x-k] to our answer.
// Then we will store the current prefix sum in the map increasing its occurrence by 1.
int subarraySum(vector<int>& nums, int k) {
    map<int,int> mpp;
    mpp[0]=1;
    int presum =0,cnt=0;
    
    for(int i =0;i<nums.size();i++){
        presum+=nums[i];
        int remove = presum - k;
        cnt +=mpp[remove];  
        mpp[presum]++;

    }
    

    return cnt;
}

//Question 12
// Pascal's Triangle
// Given an integer numRows, return the first numRows of Pascal's triangle.
// In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:
// Input: numRows = 5
// Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]


//1st Type: Give the number acccording to row & col
//Brute
int nCr(int n, int r){
    long long res=1;
    for(int i =0;i<r;i++){
        res= res*(n-i);
        res=res/(i+1);
        
    }
    return res;
}

//2nd type, Give a row of Pascals Triangle
//brute
int pascal_row(int n){
    for(int i =1;i<=n;i++){
        cout<<nCr(n-1,i-1)<<" ";
        

    }
}
//Optimal
int pascal_row_optimal(int n){
    int ans=1;
    printf("%d ",ans);
    cout<<ans<<" ";

    for(int i =1;i<n;i++){
        ans = ans*(n-i);
        ans = ans/i;
        cout<<ans<<" ";
    }
}

//3rd Type,Whole Pascal Triangle
//Brute
//Fomula ncr
vector<vector<int>> pascal(int n){
    vector<vector<int>> ans={};

    for(int row=1;row<=n;row++){
        vector<int> templist={};
        for(int col=1;col<=row;col++){
            templist.push_back(nCr(row-1,col-1));
        }
        ans.push_back(templist);
    }
    return ans;
}

//Optimal
vector<int> generaterow(int row){
    long long ans =1;
    vector<int> ansrow;
    ansrow.push_back(ans);
    for(int i =1;i<row;i++){
        ans=ans*(row-i);
        ans =ans/i;
        ansrow.push_back(ans);
    }
    return ansrow;
}
vector<vector<int>> pascalTriangle(int n){
    vector<vector<int>> ans;
    for(int i =1;i<=n;i++){
        ans.push_back(generaterow(i));
    }
}

//Majority Element [>n/3]
//Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.
//Brute Method

vector<int> major_element(vector<int>& nums){
    vector<int> ls;
    int cnt;
    for(int i =0;i<nums.size();i++){
        if(ls.size()==0 || ls[0]!=nums[i]){
            cnt =0;
            for(int j =0;j<nums.size();j++){
                if(nums[j]==nums[i]) cnt++;

            }
            if(cnt>nums.size()/3){
                ls.push_back(nums[i]);
            }
        }
        if(ls.size()==2) break;
    }
    return ls;
}

//Better(hashing)
vector<int> major_element(vector<int>& nums){
    vector<int> ls;
    map<int,int> mp;
    int n=nums.size();
    int min= (n/3)+1;
    for(int i =0;i<n;i++){
        mp[nums[i]]++;
        if(mp[nums[i]]==min){
            ls.push_back(nums[i]);
        }
        if(ls.size()==2) break;
    }
}

//Optimal Sol(based on Moore's Voting Algorithm)
vector<int> major_element(vector<int>& nums){
    int cnt1 =0,cnt2=0,el1,el2;
    vector<int> ls;
    for(int i =0;i<nums.size();i++){
        if(cnt1==0 && nums[i]!=el2){
            cnt1=1;
            el1=nums[i];
        } else if(cnt2==0 && nums[i]!=el1){
            cnt2=1;
            el2=nums[i];
        } else if(el1==nums[i]) cnt1++;
        else if(el2==nums[i]) cnt2++;
        else{
            cnt1--;
            cnt2--;
        }
    }
    int final_cnt1=0,final_cnt2=0;
    for(int i=0;i<nums.size();i++){
        if(nums.size()==el1) final_cnt1++;
        else if(nums.size()==el2) final_cnt2++;
    }
    if(final_cnt1>((nums.size()/3)+1)) ls.push_back(el1);
    if(final_cnt2>((nums.size()/3)+1)) ls.push_back(el2);

    return ls;
}

//3Sum Problem
//Brute

vector<vector<int>> Sum3_brute(vector<int>& nums){
    
    set<vector<int>> st;
    for(int i =0;i<nums.size();i++){
        for(int j =i+1;j<nums.size();j++){
            for(int k = j+1;k<nums.size();k++){
                if(nums[i]+nums[j]+nums[k]==0){
                    vector<int> temp={nums[i],nums[j],nums[k]};
                    sort(temp.begin(),temp.end());
                    st.insert(temp);
                }
            }
        }
    }
    vector<vector<int>> ans(st.begin(),st.end());
    return ans;
}

//Better
//In the previous approach, we utilized 3 loops, but now our goal is to reduce it to 2 loops. To achieve this, we need to find a way to calculate arr[k] since we intend to eliminate the third loop (k loop). To calculate arr[k], we can derive a formula as follows: 
//arr[k] = target - (arr[i]+arr[j]+arr[k]) = 0-(arr[i]+arr[j]+arr[k]) = -(arr[i]+arr[j]+arr[k]) 
//So, we will first calculate arr[i] and arr[j] using 2 loops and for the third one i.e. arr[k] we will not use another loop and instead we will look up the value 0-(arr[i]+arr[j]+arr[k]) in the set data structure. Thus we can remove the third loop from the algorithm.
//For implementing the search operation of the third element,  we will store all the elements between the indices i and j in a HashSet and then we will search for the third element in the HashSet.

vector<vector<int>> sum3_better(vector<int>& nums){
    set<vector<int>> st;
    for(int i =0;i<nums.size();i++){
        set<int> hashset;
        for(int j =i+1;j<nums.size();j++){
            int third = -(nums[i]+nums[j]);
            if(hashset.find(third) != hashset.end()){
                vector<int> temp={nums[i],nums[j],third};
                sort(temp.begin(),temp.end());
                st.insert(temp);
            }
            hashset.insert(nums[j]);
        }
    }
    vector<vector<int>> ans(st.begin(),st.end());
    return ans;
}

//Optimal
// In this approach, we intend to get rid of two things i.e. the HashSet we were using for the look-up operation and the set data structure used to store the unique triplets.
// So, We will first sort the array. Then, we will fix a pointer i, and the rest 2 pointers j and k will be moving. 
// Now, we need to first understand what the HashSet and the set were doing to make our algorithm work without them. So, the set data structure was basically storing the unique triplets in sorted order and the HashSet was used to search for the third element.
// That is why, we will first sort the entire array, and then to get the unique triplets, we will simply skip the duplicate numbers while moving the pointers.
// How to skip duplicate numbers:
// As the entire array is sorted, the duplicate numbers will be in consecutive places. So, while moving a pointer, we will check the current element and the adjacent element. Until they become different, we will move the pointer by 1 place. We will follow this process for all 3 pointers. Thus, we can easily skip the duplicate elements while moving the pointers.
// Now, we can also remove the HashSet as we have two moving pointers i.e. j and k that will find the appropriate value of arr[j] and arr[k]. So, we do not need that HashSet anymore for the look-up operations.

vector<vector<int>> sum3_opt(vector<int>& nums){
    vector<vector<int>> res;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i-1]) {
                continue;
            }
            
            int j = i + 1;
            int k = nums.size() - 1;

            while (j < k) {
                int total = nums[i] + nums[j] + nums[k];

                if (total > 0) {
                    k--;
                } else if (total < 0) {
                    j++;
                } else {
                    res.push_back({nums[i], nums[j], nums[k]});
                    j++;

                    while (nums[j] == nums[j-1] && j < k) {
                        j++;
                    }
                }
            }
        }
        return res;
}

//4Sum
//Brute
vector<vector<int>> sum4_brute(vector<int>& nums, int target){
    int n = nums.size();
    set<vector<int>> st;
    for(int i =0;i<n;i++){
        for(int j = i+1;j<n;j++){
            for(int k =j+1;k<n;k++){
                for(int l = k+1;l<n;l++){
                    long long sum = nums[i]+ nums[j];
                    sum += nums[k];
                    sum += nums[l];
                    if(sum == target){
                        vector<int> temp ={nums[i],nums[j],nums[k],nums[l]};
                        sort(temp.begin(),nums.end());
                        st.insert(temp);
                    }
                }
            }
        }
    }
    vector<vector<int>> ans(st.begin(),st.end());

    return ans;
}

//better(hashing)
vector<vector<int>> sum4_brute(vector<int>& nums, int target){
    int n =nums.size();
    set<vector<int>> st;
    for(int i =0;i<n;i++){
        for(int j =i+1;j<n;j++){
            set<long long> hashset;
            for(int k =j+1;k<n;k++){
                long long sum = nums[i]+nums[j];
                sum+=nums[k];
                long long fourth = target - sum;;
                if(hashset.find(fourth)!=hashset.end()){
                    vector<int> temp={nums[i],nums[j],nums[k],(int)fourth};
                    sort(temp.begin(),temp.end());
                    st.insert(temp);

                }
                hashset.insert(nums[k]);

            }
        }
    }
    vector<vector<int>> ans(nums.begin(),nums.end());
    return ans;
}

//Optimal(2 pointer approach)
vector<vector<int>> sum4_brute(vector<int>& nums, int target){
    int n = nums.size();
    vector<vector<int>> ans;
    sort(nums.begin(),nums.end());
    for(int i =0;i<n;i++){
        if(i>0 && nums[i]==nums[i-1]) continue;
        for(int j =i+1;j<n;j++){
            if(j>i+1 && nums[j]==nums[j-1]) continue;
            int k =j+1;
            int l=n-1;
            while(k<l){
                long long sum = nums[i]+nums[j];
                sum+=nums[k];
                sum+=nums[l];
                if(sum == target){
                    ans.push_back({nums[i], nums[j], nums[k],nums[l]});
                    k++;l--;
                    while (nums[k] == nums[k-1] && k < l)k++;
                    while (nums[l] == nums[l-1] && k < l) {
                        l--;
                    }
                }else if(sum<target) k++;
                else l--;
            }
        }
    }
    return ans;
}

//Merge intervals
//Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.

//Brute(Checking each interval with each other, checking)
vector<vector<int>> merge(vector<vector<int>>& intervals){
    int n = intervals.size();
    sort(intervals.begin(),intervals.end());
    vector<vector<int>> ans;

    for(int i =0;i<n;i++){
        int start=intervals[i][0];
        int end = intervals[i][1];
        if(!ans.empty() && end <= ans.back()[1]) continue;

        for(int j =0;j<n;j++){
            if(intervals[j][0]<=end){
                end = max(end,intervals[j][1]);
            }else break;
        }
        ans.push_back({start,end});
    }

    return ans;
}

//Optimal
// Instead of checking each interval with every other one (as in brute-force), we first sort the intervals, so that any overlapping intervals will come one after the other. This way, we only need to compare each interval with the last one added to our answer. If they overlap, we merge them. If they don’t, we simply add the current interval as a new entry.
// Sort the intervals based on their starting points. This ensures overlapping intervals come together.
// Initialize an empty list to store the final merged intervals.
// If the list is empty or the current interval starts after the last one ends, it means there is no overlap, so just add it to the list.
// If the current interval starts before or exactly at the end of the last one, it means there is overlap. So, combine both by extending the end of the last one to the further end of the two.
// Keep doing this until all intervals have been checked. The final list will now contain only non-overlapping, merged intervals.
vector<vector<int>> merge(vector<vector<int>>& intervals){
    int n = intervals.size();
    sort(intervals.begin(),intervals.end());
    vector<vector<int>> ans;
    for(int i =0;i<n;i++){
        if(ans.empty() || intervals[i][0]> ans.back()[1]){
            ans.push_back(intervals[i]);
        }else{
            ans.back()[1]=max(ans.back()[1],intervals[i][1]);
        }
    }
    return ans;
}

//Merger Sorted Arrays(without using extra space)
//You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, and two integers m and n, representing the number of elements in nums1 and nums2 respectively.
//Merge nums1 and nums2 into a single array sorted in non-decreasing order.
//The final sorted array should not be returned by the function, but instead be stored inside the array nums1. To accommodate this, nums1 has a length of m + n, where the first m elements denote the elements that should be merged, and the last n elements are set to 0 and should be ignored. nums2 has a length of n.
//1st approach
void merge_sorted(vector<int>& nums1, int m, vector<int>& nums2, int n){
    int left =m-1;
    int right =0;
    while(left>=0 && right <m){
        if(nums1[left]>nums2[right]){
            swap(nums1[left],nums2[right]);
            left--,right++;

        }else{
            break;
        }
        
    }
    sort(nums1.begin(),nums1.end());
    sort(nums2.begin(),nums2.end());
    for(int i=0;i<n;i++){
       nums1[i+m]=nums2[i];
    }
} 

//Reverse PAirs
// Given an integer array nums, return the number of reverse pairs in the array.
// A reverse pair is a pair (i, j) where: 0 <= i < j < nums.length and nums[i] > 2 * nums[j].

//Brute(checking Each Pair)

//Optimal
// The steps are basically the same as they are in the case of the merge sort algorithm. The change will be just in the mergeSort() function:
// In order to count the number of pairs, we will keep a count variable, cnt, initialized to 0 beforehand inside the mergeSort().
// We will add the numbers returned by the previous mergeSort() calls.
// Before the merge step, we will count the number of pairs using a function, named countPairs().
// We need to remember that the left half starts from low and ends at mid, and the right half starts from mid+1 and ends at high.
// The steps of the countPairs() function will be as follows:
// We will declare a variable, cnt, initialized with 0.
// We will run a loop from low to mid, to select an element at a time from the left half.
// Inside that loop, we will use another loop to check how many elements from the right half can make a pair.
// Lastly, we will add the total number of elements i.e. (right-(mid+1)) (where right = current index), to the cnt and return it.
int cnt=0;
void merge_rp(vector<int> &arr,int low, int mid, int high){
    vector<int> temp;
    int left = low;
    int right = mid+1;
    while(left<=mid && right<=high){
        if(arr[left]<= arr[right]){
            temp.push_back(arr[left]);
            left++;
        }else {
            temp.push_back(arr[right]);
            right--;
        }
    }

    while(left<=mid){
        temp.push_back(arr[left]);
        left++;
    }

    while(right<=high){
        temp.push_back(arr[right]);
        right++;
    }
    
    for(int i = low;i<=high;i++){
        arr[i]=temp[i-low];

    }


}
void countPairs(vector<int> &arr,int low,int mid, int high){
    int right =mid+1;
    for(int i =low;i<=mid;i++){
        while(right<=high && arr[i]>(long long)2*arr[right]) right++;
        cnt += (right-(mid+1));
    }
}
void mS_rp(vector<int> &arr,int low, int high){
    if(low==high) return;
    int mid =(low + high)/2;
    mS_rp(arr,low,mid);
    mS_rp(arr,mid+1,high);
    countPairs(arr,low,mid,high);
    merge_rp(arr,low,mid,high);
}
void MergeSort_rp(vector<int> &arr, int n){
    mS(arr, 0, n-1);
}
int reversePairs(vector<int>& nums) {
    MergeSort_rp(nums,nums.size());
}

//Maximum Product Subaaray
//Given an integer array nums, find a subarray that has the largest product, and return the product.

//Brute (Checking all subarray)


//Optimal Approach
// The product of elements in a subarray can become large when there are positive numbers, but negative numbers and zeros make it tricky. A negative number can flip a large product into a negative one, but if we meet another negative later, the sign flips back to positive. Therefore, to capture all possible max products, we do two things:
// Traverse the array from left to right (prefix) to build cumulative product.
// Traverse the array from right to left (suffix) to catch subarrays ending at the back (helpful when max product is at the end or due to even negatives).
// Reset the product to 1 whenever a zero is found, as it breaks the subarray continuity.
// By comparing products in both directions at each step, we ensure we don’t miss any possible maximum.

int maxProduct(vector<int>& nums){
    int pre=1,suff=1;
    int ans = INT32_MIN;
    int n = nums.size();
    for(int i =0;i<n;i++){
        if(pre==0) pre=1;
        if(suff==0) suff=1;

        pre*= nums[i];
        suff*= nums[n-i-1];
        ans=max(ans,max(pre,suff));
    }
    return ans;
}

int main(){

    
}