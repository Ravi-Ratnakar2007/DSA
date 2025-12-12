#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath> 
#include <numeric>

using namespace std;
// BS on 1D Array
//For each question , there is a answer via linear search , but its time complexity is high.

//Binary Search(Normal)
int search(vector<int>& nums, int target) {
    int n = nums.size();
    int low=0,high = n-1;  
    while(low<=high){
        int mid=(low+mid)/2;
        if(nums[mid]==target) return mid;
        else if(target > nums[mid]) low = mid+1;
        else high = mid-1;
    }      
    return -1;
}

//Binary Search(Recursive)
int bs_recursive(vector<int>& nums,int low, int high, int target){
    if(low>high) return -1;
    int mid= (low + high)/2;
    if(nums[mid]==target) return mid;
    else if(target > nums[mid]) return bs_recursive(nums,mid+1, high,target);
    return bs_recursive(nums, low,mid-1,target);
}
int search_recursive(vector<int>& nums, int target){
    return bs_recursive(nums,0,nums.size()-1,target);
}

//Lower bound(Smallest index s.t. arr[ind]>=target)
int lowerbound(vector<int>& nums, int target){
    int low=0,high=nums.size()-1;
    int ans= nums.size();
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]>=target){
            ans=mid;
            high=mid-1;
        }else{
            low = mid+1;
        }
    }
}

//Upper bound(Smallest index s.t. arr[ind]>target)
int upperbound(vector<int>& nums, int target){
    int low=0,high=nums.size()-1;
    int ans= nums.size();
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]>target){
            ans=mid;
            high=mid-1;
        }else{
            low = mid+1;
        }
    }
}

//Floor and Ceil in an array

int floor_arr(vector<int>& nums, int target){
    int ans=-1,low=0,high=nums.size()-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]<=target){
            ans=nums[mid];
            low=mid+1;
        }else{
            high = mid-1;
        }
    }
}

int ceil_arr(vector<int>& nums, int target){
    int ans=-1,low=0,high=nums.size()-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]<target){
            
            low=mid+1;
        }else{
            ans=nums[mid];
            high = mid-1;
        }
    }
}

//Search Elements in a rotated Array - I(Unique Elements), Algo-
// Place the 2 pointers i.e. low and high: Initially, we will place the pointers like this: low will point to the first index, and high will point to the last index.
// Calculate the ‘mid’: Now, inside a loop, we will calculate the value of ‘mid’ using the following formula:
// mid = (low+high) // 2 ( ‘//’ refers to integer division)
// Check if arr[mid] == target: If it is, return the index mid.
// Identify the sorted half, check where the target is located, and then eliminate one half accordingly:
// If arr[low] <= arr[mid]: This condition ensures that the left part is sorted.
// If arr[low] <= target && target <= arr[mid]: It signifies that the target is in this sorted half. So, we will eliminate the right half (high = mid-1).
// Otherwise, the target does not exist in the sorted half. So, we will eliminate this left half by doing low = mid+1.
// Otherwise, if the right half is sorted:
// If arr[mid] <= target && target <= arr[high]: It signifies that the target is in this sorted right half. So, we will eliminate the left half (low = mid+1).
// Otherwise, the target does not exist in this sorted half. So, we will eliminate this right half by doing high = mid-1.
// Once, the ‘mid’ points to the target, the index will be returned.


int bs_rotated_I(vector<int>& nums, int target){
    int low =0,high = nums.size()-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]==target) return mid;
        //left rotated
        if(nums[low]<= nums[mid]){
            if(nums[low]<= target && target<=nums[mid]){
                high = mid -1;
            }else{
                low=mid+1;
            }
        }
        //Right rotated
        else{
            if(nums[mid]<= target && target<=nums[high]){
                low = mid+1;
            }else{
                high=mid-1;
            }
        }
    }
    return -1;
}

//Search Elements in a rotated Array - I(Duplicate Elements)
//This check was effective in the previous problem, where there were no duplicate numbers. However, in the current problem, the array may contain duplicates. Consequently, the previous approach will not work when arr[low] = arr[mid] = arr[high].
//How to handle the edge case arr[low] = arr[mid] = arr[high]:
//In the algorithm, we first check if arr[mid] is the target before identifying the sorted half. If arr[mid] is not our target, we encounter this edge case. In this scenario, since arr[mid] = arr[low] = arr[high], it means that neither arr[low] nor arr[high] can be the target. To handle this edge case, we simply remove arr[low] and arr[high] from our search space, without affecting the original algorithm. 
//To eliminate elements arr[low] and arr[high], we can achieve this by simply incrementing the low pointer and decrementing the high pointer by one step. We will continue this process until the condition arr[low] = arr[mid] = arr[high] is no longer satisfied.
int bs_rotated_II(vector<int>& nums, int target){
    int low =0,high = nums.size()-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]==target) return mid;
        //Checking condition for duplicates(VVIMP)
        if(nums[low]==nums[mid] && nums[mid]==nums[high]){
            low++,high--;
            continue;
        }

        //left rotated
        if(nums[low]<= nums[mid]){
            if(nums[low]<= target && target<=nums[mid]){
                high = mid -1;
            }else{
                low=mid+1;
            }
        }
        //Right rotated
        else{
            if(nums[mid]<= target && target<=nums[high]){
                low = mid+1;
            }else{
                high=mid-1;
            }
        }
    }
    return -1;
}

//Find minimum in Rotated Sorted Array

int findMin(vector<int>& nums) {
    int low=0,high = nums.size()-1;
    int ans= INT_MAX;
    while(low<=high){
        int mid=(high+low)/2;
        //Search space is already sorted
        //themn always nums[low] will be smaller in that seacrh space
        if(nums[low]<=nums[mid]){
            ans=min(ans,nums[low]);
            break;
        }

        if(nums[low]<=nums[mid]){
            ans=min(ans,nums[low]);
            low=mid+1;
        }else{
            ans = min(ans,nums[mid]);
            high=mid-1;
        }
    } 
    return ans;       
}

//Single element in a Sorted Array
// The index sequence of the duplicate numbers in the left half is always (even, odd). That means one of the following conditions will be satisfied if we are in the left half:
// If the current index is even, the element at the next odd index will be the same as the current element.
// Similarly, If the current index is odd, the element at the preceding even index will be the same as the current element.
// The index sequence of the duplicate numbers in the right half is always (odd, even). That means one of the following conditions will be satisfied if we are in the right half:
// If the current index is even, the element at the preceding odd index will be the same as the current element.
// Similarly, If the current index is odd, the element at the next even index will be the same as the current element.

int singleNonDuplicate(vector<int>& nums) {
    int low=1,high=nums.size()-2;
    if(nums.size()==1) return nums[0];
    if(nums[0]!= nums[1]) return nums[0];
    if(nums[nums.size()-1]!= nums[nums.size()-2]) return nums[nums.size()-1];
    
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid]!= nums[mid-1] && nums[mid]!=nums[mid+1]) return nums[mid];
        if(mid%2==0){
            if(nums[mid-1]==nums[mid]){//odd,even
                high=mid-1;
            }else{
                low=mid+1;
            }
        }else{
            if(nums[mid-1]==nums[mid]){//even,odd
                low=mid+1;
            }else{
                high=mid-1;
            }
        }
    }
}

//Find Peak Element
//To know how to eliminate the half efficiently, we can clearly notice a striking distinction between the left and right halves of the peak element in the array. The left half of the peak element has an increasing order whereas the right half of the peak element has a decreasing order.
//Thus we know that if current element is greater than its left neighbour, we are in the left half and if our current element is greater than its right neighbour then we are in the right half. If we know the half that we are in currently, we can eliminate it to find our peak element.
int findPeakElement(vector<int>& nums) {
    int n = nums.size();
    int low=1,high = n-2;
    if(nums[0]>nums[1]) return 0;
    if(nums[n-1]>nums[n-2]) return n-1;
    
    while(low<=high){
        int mid=(low+high)/2;
        if(nums[mid-1]<nums[mid] && nums[mid]>nums[mid+1]) return mid;

        if(nums[mid]>nums[mid-1]){
            low=mid+1;
        }else{
            high = mid-1;
        }
    }
}





// BS on Answers

//Koko eating bananas(IMP)- return the min int k s.t. koko can eat all n bananas within n hrs.
int counthrs(vector<int>& piles,int k){
    int totalhrs=0;
    for(int i =0;i<piles.size();i++){
        if(piles[i]%k==0) totalhrs +=piles[i]/k;
        else totalhrs +=(piles[i]/k)+1;

    }
    return totalhrs;
}
int minEatingSpeed(vector<int>& piles, int h) {
    int low=0,high = *max_element(piles.begin(),piles.end());
    
    while(low<=high){
        int mid=(low+high)/2;
        if(counthrs(piles,mid)<=h) high=mid-1;
        else low = mid+1;
        
    }
    return low;
}

//Minimum no of days to make m Bouquets

//Brute
int possible(vector<int>& bloomDay, int m, int k,int day){
    int cnt=0,noofB=0;

    for(int i =0;i<bloomDay.size();i++){
        if(bloomDay[i]<=day) cnt++;
        else{
            noofB+=(cnt/k);
            cnt=0;
        }
    }
    noofB+=(cnt/k);
    if(noofB>=m) return 1;
    else return 0;
}
int minDays(vector<int>& bloomDay, int m, int k) {
    int low =*min_element(bloomDay.begin(),bloomDay.end()),  high = *max_element(bloomDay.begin(),bloomDay.end()),ans=high;
    if(bloomDay.size()<(m*k)) return -1;     
    for(int i = low;i<=high;i++){
        if(possible(bloomDay,m,k,i)) {
            ans=min(ans,i);
        }
    } 
    return ans;
}

//BS
int possible(vector<int>& bloomDay, int m, int k,int day){
    int cnt=0,noofB=0;

    for(int i =0;i<bloomDay.size();i++){
        if(bloomDay[i]<=day) cnt++;
        else{
            noofB+=(cnt/k);
            cnt=0;
        }
    }
    noofB+=(cnt/k);
    if(noofB>=m) return 1;
    else return 0;
}
int minDays(vector<int>& bloomDay, int m, int k) {
    int low =*min_element(bloomDay.begin(),bloomDay.end()),  high = *max_element(bloomDay.begin(),bloomDay.end());
    long long size = m*k;
    if(bloomDay.size()<size) return -1;     
    while(low<=high){
        int mid=(low+high)/2;
        if(possible(bloomDay,m,k,mid)){
           
            high = mid-1;
        }else{
            low=mid+1;
        }
    }
    return low;
}


//Find smallest divisor given a threshold value
//Given an array of integers nums and an integer threshold, we will choose a positive integer divisor, divide all the array by it, and sum the division's result. Find the smallest divisor such that the result mentioned above is less than or equal to threshold.
int possible_div(vector<int>& nums, int threshold,int divisor){
    int cnt=0,res;
    for(int i =0;i<nums.size();i++){
        res=ceil(nums[i]/divisor);
        cnt+=res;
    }
    if(threshold>=cnt) return 1;
    else return 0;
}
int smallestDivisor(vector<int>& nums, int threshold) {
    int low=1,high=*max_element(nums.begin() ,nums.end());   

    while(low<=high){
        int mid = (high +low)/2;
        if(possible_div(nums,threshold,mid)==1) high=mid-1;
        else low=mid+1;
    }
    return low;
}



//CApacity to ship packages within D days
int possible_wieghts(vector<int>& weights, int days , int capacity){
    int sum=0,cnt=1;
    for(int i =0;i<weights.size();i++){
        if(weights[i]+sum>capacity){
            cnt++;
            sum=weights[i];
        }else{
            sum+=weights[i];
        }
    }
    if(days>=cnt) return 1;
    else return 0;
}
int shipWithinDays(vector<int>& weights, int days) {
    int low=*max_element(weights.begin() ,weights.end());
    long long high=0;
    for(int i =0;i<=weights.size();i++){
        high += weights[i];
    }
    
    while(low<=high){
        int mid=low +(high-low)/2;
        if(possible_wieghts(weights,days,mid)) high = mid-1;
        else low =mid+1;
    }
    return low;
}


//Kth Missing Povitive Integer
//Given an array arr of positive integers sorted in a strictly increasing order, and an integer k.
//Return the kth positive integer that is missing from this array.

//Brute
int findKthPositive_brute(vector<int>& arr, int k) {
    for(int i =0;i<arr.size();i++){
        if(arr[i]>k) break;
        k++;
    }
    return k;

}

//Optimal
//From the above example, we can derive a formula to find the number of missing numbers before any array index, i. The formula is
// Number of missing numbers up to index i = vec[i] - (i+1).
// The given array, vec, is currently containing the number vec[i] whereas it should contain (i+1) if no numbers were missing. The difference between the current and the ideal element will give the result.
int findKthPositive(vector<int>& arr, int k) {
    int low=0,n = arr.size(),gap;
    int high = n-1;


    while(low<= high){
        int mid=low +(high-low)/2;;

        gap=arr[mid]-(mid+1);
        if(k>gap) high = mid-1;
        else low=mid+1;
        
    }
    
    return high+1+k;
}



int sum_subarray(vector<int>& nums, int limit){
    int sum =0,cnt=1;
    for(int i =0;i<nums.size();i++){
        if(sum + nums[i]<=limit){
            sum+=nums[i];
        }else{
            sum = nums[i];
            cnt++;
        }
       
    }
     return cnt;
}


//Split Array - Largest Sum
// Place the 2 pointers i.e. low and high: Initially, we will place the pointers. The pointer low will point to max(arr[]) and the high will point to sum(arr[]).
// Calculate the ‘mid’: Now, inside the loop, we will calculate the value of ‘mid’ using the following formula:
// mid = (low+high) // 2 ( ‘//’ refers to integer division)
// Eliminate the halves based on the number of subarrays returned by countPartitions():
// We will pass the potential value of ‘maxSum’, represented by the variable 'mid', to the ‘countPartitions()' function. This function will return the number of partitions we can make.
// If partitions > k: On satisfying this condition, we can conclude that the number ‘mid’ is smaller than our answer. So, we will eliminate the left half and consider the right half(i.e. low = mid+1).
// Otherwise, the value mid is one of the possible answers. But we want the minimum value. So, we will eliminate the right half and consider the left half(i.e. high = mid-1).
// Finally, outside the loop, we will return the value of low as the pointer will be pointing to the answer.
// The steps from 3-4 will be inside a loop and the loop will continue until low crosses high.

int splitArray(vector<int>& nums, int k) {
    int low=*max_element(nums.begin() ,nums.end());
    int high = accumulate(nums.begin(), nums.end(), 0);
    
    while(low<=high){
        int mid =low +(high-low)/2;

        if(sum_subarray(nums,mid)==k)high=mid-1;
        else if(sum_subarray(nums,mid)>k) low=mid+1;
        else{
            high= mid-1;
        }
    }
    return low;
}

//Median of 2 sorted Arrays
//We choose a cut (partition) in the first array, and accordingly calculate the cut in the second array such that the total number of elements on the left side equals the number of elements on the right (or differs by one if the total number is odd). For the correct partition, the maximum of the left parts should be less than or equal to the minimum of the right parts.
//To check this, we compare the maximum of the left side from both arrays with the minimum of the right side. If the condition is not met, we move the binary search window either left or right depending on which condition fails. This process continues until we find the right partition.
//Once the correct partition is found, the median is calculated based on the total number of elements. If the total is even, we take the average of the two middle values (i.e., max of left part and min of right part). If the total is odd, the median is the max of the left part since it would be the middle element.
double findMedianSortedArrays(vector<int>& a, vector<int>& b){
    int n1= a.size(),n2= b.size();
    if(n1>n2) return findMedianSortedArrays(b,a);
    int low=0,high=n1;
    int left =(n1+n2+1)/2;
    int n = n1+n2;
    while(low<= high){
        int mid1= low+(high - low)/2;
        int mid2= left-mid1;
        int l1= INT_MIN,l2 = INT_MIN;
        int r1 = INT_MAX, r2 = INT_MAX;
        if(mid1<n1) r1=a[mid1];
        if(mid2<n2) r2 = b[mid2];
        if(mid1-1 >=0)l1 = a[mid1-1]; 
        if(mid2-1 >=0)l2 = a[mid2-1];
        
        if(l1<= r2 && l2<=r1 ){
            if(n%2==1) return max(l1,l2);
            return ((double)(max(l1,l2)+min(r1,r2)))/2.0;
        }else if( l1>r2) high = mid1-1;
        else low= mid1+1;

    }
    return 0;
}



//BS on ANSWERS


//Search in a 2D MAtrix I
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int low = 0,m= matrix.size(),n= matrix[0].size();
    int high=(m*n)-1;

    while(low<=high){
        int mid= low+((high-low)/2);

        int row=mid/n;
        int col= mid%n;

        if(matrix[row][col]==target) return true;
        else if(matrix[row][col]>target) high = mid-1;
        else low=mid+1;

    }
    return 0;
}


//Search in a 2D MAtrix II
// Write an efficient algorithm that searches for a value target in an m x n integer matrix matrix. This matrix has the following properties:
// Integers in each row are sorted in ascending from left to right.
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int row =0,m= matrix.size(),n= matrix[0].size();
    int col= m-1;
    
    while(row<n && col>=0){
        if(matrix[row][col]== target) return true;
        else if(matrix[row][col]<target) row++;
        else col--;
    }
    return false;
}


//Find a Peak Element II
// A peak element in a 2D grid is an element that is strictly greater than all of its adjacent neighbors to the left, right, top, and bottom.
// Given a 0-indexed m x n matrix mat where no two adjacent cells are equal, find any peak element mat[i][j] and return the length 2 array [i,j].
// You may assume that the entire matrix is surrounded by an outer perimeter with the value -1 in each cell.
// You must write an algorithm that runs in O(m log(n)) or O(n log(m)) time.
vector<int> findPeakGrid(vector<vector<int>>& arr) {
    int m = arr.size(), n = arr[0].size();
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int row = 0;
        for (int i = 1; i < m; i++)
            if (arr[i][mid] > arr[row][mid])
            row = i;

        int left = (mid - 1 >= 0) ? arr[row][mid - 1] : -1;
        int right = (mid + 1 < n) ? arr[row][mid + 1] : -1;

        if (arr[row][mid] > left && arr[row][mid] > right)
            return {row, mid};
        else if (arr[row][mid] < right)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return {-1, -1};
}

int main(){
    
}