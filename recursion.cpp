#include <iostream>
#include<vector>
#include <string.h>
#include <list>
#include <map>
#include <algorithm>
#include <set>
using namespace std;

//Generate Paranthesis
//Brute
bool isValid(string s) {
    int balance = 0;
    for (char c : s) {
        if (c == '(') balance++;
        else balance--;
        if (balance < 0) return false;
    }
    return balance == 0;
}

void generateAll(string curr, int n, vector<string>& res) {
    if (curr.length() == 2 * n) {
        if (isValid(curr)) res.push_back(curr);
        return;
    }
    generateAll(curr + '(', n, res);
    generateAll(curr + ')', n, res);
}
vector<string> generateParenthesis(int n) {
    vector<string> res;
    generateAll("", n, res);
    return res;
}
//Optimal

void backtrack(string curr, int open, int close, int n, vector<string>& res) {
    if (curr.length() == 2 * n) {
        res.push_back(curr);
        return;
    }
    if (open < n) backtrack(curr + '(', open + 1, close, n, res);
    if (close < open) backtrack(curr + ')', open, close + 1, n, res);
}
vector<string> generateParenthesis_optimal(int n) {
    vector<string> res;
    backtrack("", 0, 0, n, res);
    return res;
}
//Generating Power Set
// Each subsequence corresponds to a binary number where the bits represent whether to include (1) or exclude (0) a character at that position.
// There are 2^n subsequences for a string of length n.
// Iterate from 0 to 2^n - 1. For each number, check each bit.
// If the bit is set, include the corresponding character. Else, exclude it.
// Print the subsequence formed by the included characters.

vector<vector<int>> subsets(vector<int>& nums) {
    int n=nums.size();
    vector<vector<int>> res;
    for(int i =0;i<(1<<n);i++){
        vector<int> sub={};
        for(int j =0;j<n;j++){
            if(i&(1<<j)) sub.push_back(nums[j]);
        }
        res.push_back(sub);
    }        
    return res;
}
//Candidate Sum
// Whenever the problem is related to picking up elements from an array to form a combination, start thinking about the “pick and non-pick” approach.
// We use a recursive backtracking approach to find all combinations that sum up to the target.
// We define a recursive function with the following parameters:
// Index — current position in the array.
// Target — remaining sum we need to achieve.
// DS (data structure) — to store the current combination.
// At every step, we have two choices:
// Pick the element at the current index:
// We reduce the target by arr[index].
// Add arr[index] to the DS.
// We stay on the same index since we can reuse the same element.
// Not pick the element:
// We move to the next index.
// Target remains unchanged.
// Element is not added to the DS.
// While backtracking, remove the last inserted element to explore new paths.
// This process is repeated while index < array.size() for a given recursion call.
// We can optionally stop recursion when target == 0, but here we allow the recursion to run fully for generalization.

void findcombination(int ind,int target,vector<int>& arr,vector<vector<int>>& ans,vector<int>& ds){
    if(ind==arr.size()){
        if(target==0) ans.push_back(ds);
        return;
    }
    if(arr[ind]<=target){
        ds.push_back(arr[ind]);
        findcombination(ind,target-arr[ind],arr,ans,ds);
        ds.pop_back();
    }

    findcombination(ind+1,target,arr,ans,ds);
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> ans;
    vector<int> ds;
    findcombination(0,target,candidates,ans,ds);
    return ans;
}
//Combination Sum II
// Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target.
// Each number in candidates may only be used once in the combination.
// Note: The solution set must not contain duplicate combinations.
//Brute - Making some changes if previous code

void findcombination2(int ind,int target,vector<int>& arr,vector<vector<int>>& ans,vector<int>& ds){
    if(ind==arr.size()){
        if(target==0){
            sort(ds.begin(),ds.end());
            auto it = find(ans.begin(),ans.end(),ds);
            if(it == ans.end()) ans.push_back(ds);
            
        } 
        return;
    }
    if(arr[ind]<=target){
        ds.push_back(arr[ind]);
        findcombination2(ind+1,target-arr[ind],arr,ans,ds);
        ds.pop_back();
    }

    findcombination2(ind+1,target,arr,ans,ds);
}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int>> ans;
    vector<int> ds;
    sort(candidates.begin(),candidates.end());
    findcombination2(0,target,candidates,ans,ds);
    return ans;
}
//Optimal
void findcombination2_optimal(int ind,int target,vector<int>& arr,vector<vector<int>>& ans,vector<int>& ds){
    if(target==0){
        ans.push_back(ds);
        return;
    }

    for(int i=ind;i<arr.size();i++){
        if(i>ind && arr[i]==arr[i-1]) continue;

        if(arr[i]>target) break;
        ds.push_back(arr[i]);
        findcombination2_optimal(ind+1,target-arr[i],arr,ans,ds);

        ds.pop_back();

    }
}
vector<vector<int>> combinationSum2_optimal(vector<int>& candidates, int target){
    vector<vector<int>> ans;
    vector<int> ds;
    sort(candidates.begin(),candidates.end());
    findcombination2_optimal(0,target,candidates,ans,ds);
    return ans;
}
//Subset II
// Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
// The solution set must not contain duplicate subsets. Return the solution in any order.
//Brute
// Define a recursive function to generate subsets.
// The base case for the recursion is when all elements of the input array have been considered.
// When the base case is reached, the currently formed subset is complete.
// Insert this complete subset into a Set data structure to automatically handle uniqueness.
// For each element in the array, make two recursive calls: one where the element is included in the subset, and another where it is not included.
// The main function will initialize a Set to store the unique results.
// It will then start the recursion from the first element.
// Finally, it will convert the Set of unique subsets into a list and return it.vector<vector<int>> subsetsWithDup_brute(vector<int>& nums) 

void findsubsets_brute(int ind,   vector<int>& nums,vector<int>& ds, set<vector<int>>& result){
    if(ind==nums.size()){
        result.insert(ds);
        return; 
    }

    ds.push_back(nums[ind]);
    findsubsets_brute(ind+1,nums,ds,result);
    ds.pop_back();
    findsubsets_brute(ind+1,nums,ds,result);
}
vector<vector<int>> subsetsWithDup_brute(vector<int>& nums) {
    set<vector<int>> result;
    vector<int> ds;
    sort(nums.begin(),nums.end());
    findsubsets_brute(0,nums,ds,result);
    vector<vector<int>> ans(result.begin(),result.end());
    return ans;
}
//Optimal
// Sorting is essential here because without sorting, duplicates would be scattered and hard to skip correctly. This method is efficient and avoids unnecessary subset generation, making it better in both runtime and memory usage compared to the brute force approach.
// Sort the input array so that duplicates are adjacent.
// Initialize a list to store the current subset and a list of lists to store all unique subsets.
// Use a recursive backtracking function that:
// Adds the current subset to the list of results.
// Iterates from the current index to the end of the array.
// If the current element is the same as the previous one and not at the starting index of this recursion, skip it.
// Include the current element in the subset and recurse for the next index.
// Backtrack by removing the last added element.
// Return the list of all unique subsets.

void backtrack(int ind,vector<int>& nums,vector<int>& current, vector<vector<int>>& ans){
    ans.push_back(current);

    for(int i=ind;i<nums.size();i++){
        if(i>ind && nums[i]==nums[i-1]) continue;

        current.push_back(nums[i]);
        backtrack(i+1,nums,current,ans);
        current.pop_back();
    }
    
}
vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    sort(nums.begin(),nums.end());
    vector<vector<int>> ans;
    vector<int> current;

    backtrack(0,nums,current, ans);
    return ans;
}
//Combination Sum III

void findcombination3_optimal(int ind,int target,int k,vector<int>& arr,vector<vector<int>>& ans,vector<int>& ds){
    if(ind==arr.size()){
        if(target==0 && ds.size()==k) ans.push_back(ds);
        return;
    }
    if(arr[ind]<=target){
        ds.push_back(arr[ind]);
        findcombination3_optimal(ind+1,target-arr[ind],k,arr,ans,ds);
        ds.pop_back();
    }

    findcombination3_optimal(ind+1,target,k ,arr,ans,ds);
}
vector<vector<int>> combinationSum3_optimal(int k,int n){
    vector<int> nums={1,2,3,4,5,6,7,8,9};
    vector<vector<int>> ans;
    vector<int> ds;
    findcombination3_optimal(0,n,k,nums,ans,ds);
    return ans;
}

//Letter Combinations of a Phone Number
// Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.
// A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.
//Self code
vector<string> mp = {
    "", "", "abc", "def", "ghi", 
    "jkl", "mno", "pqrs", "tuv", "wxyz"
};
void backtrack_phone(int ind,string& digits,string& current, vector<string>& ans){
    if(current.size()==digits.size()){
        ans.push_back(current);
        return;
    }

    string letters = mp[digits[ind] - '0'];
    for (char c : letters) {
        current=current+c;
        backtrack_phone(ind+1,digits,current,ans);
        current.pop_back();
    }

}
vector<string> letterCombinations(string digits) {
    vector<string> ans;
    string current="";
    backtrack_phone(0,digits,current,ans);
    return ans;
}
//Palindrome Partitioning
// The initial idea will be to make partitions to generate substring and check if the substring generated out of the partition will be a palindrome. 
// Partitioning means we would end up generating every substring and checking for palindrome at every step. 
// Since this is a repetitive task being done again and again, at this point we should think of recursion. The recursion continues until the entire string is exhausted. 
// After partitioning, every palindromic substring is inserted in a data structure. 
// When the base case has reached the list of palindromes generated during that recursion call is stored in our answer.

// Use backtracking to explore all possible ways to partition the string.
// Start from index 0 and try all possible substrings from the current index to the end.
// For each substring, check if it is a palindrome.
// If the substring is a palindrome, include it in the current partition and recursively call the function for the remaining string.
// Backtrack by removing the last added substring and trying the next possible partition.
// Continue this process until you reach the end of the string.
// Store all valid partitions (where all substrings are palindromes) in the result.

bool isPalindrome(string& s,int start , int end){
    while(start<end){
        if(s[start]!=s[end]) return false;
        end--;
        start++;
    }
    return true;
}
void backtrack_palindrome(int ind,string& s, vector<string>& path, vector<vector<string>>& res ){
    if(ind==s.size()){
        res.push_back(path);
        return;
    }

    for(int i=ind;i<s.size();i++){
        if(isPalindrome(s,ind,i)){
            path.push_back(s.substr(ind,i-ind+1));
            backtrack_palindrome(i+1,s,path,res);
            path.pop_back();
        }
    }
}
vector<vector<string>> partition(string s) {
    vector<vector<string>> res;
    vector<string> path;
    backtrack_palindrome(0,s,path,res);
    return res;        
}
//Word Search
// Iterate through each cell in the board.
// If the cell matches the first letter of the word, start a DFS search from that cell.
// In DFS, check boundary conditions and whether the character matches the current letter in the word.
// If matched, temporarily mark the cell as visited.
// Recursively search in all four directions for the next letter.
// If the whole word is found, return true.
// Backtrack by restoring the cell’s original value before returning.
// If no path matches the word, return false.

bool dfs(vector<vector<char>>& board, string word,int i,int j ,int ind){
    if(ind==word.size()) return true;

    if(i<0 ||  j<0 || i>=board.size()|| j>=board[0].size() || board[i][j]!=word[ind]) return false;

    char temp=board[i][j];
    board[i][j]='#';

    bool found=dfs(board,word,i+1,j,ind+1) ||
                dfs(board,word,i-1,j,ind+1) ||
                dfs(board,word,i,j+1,ind+1) ||
                dfs(board,word,i,j-1,ind+1);
    board[i][j]=temp;
    return found;
}
bool exist(vector<vector<char>>& board, string word) {
    int row=board.size();
    int col = board[0].size();
    
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if(dfs(board,word,i,j,0)){
                return true;
            }
        }
        
    }
    return false;
    
}
//N Queen
// The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
// Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.
// Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.

//Brute
// Start with the first column and attempt to place a queen in each row one by one.
// For each position, check if placing a queen there is safe from attacks (no same row or upper-left or lower-left diagonal threats).
// If it’s safe, place the queen and move to the next column recursively.
// If placing the queen leads to a dead-end (no safe position in next column), backtrack by removing the queen and try the next row in the current column.
// Repeat this process until a valid configuration is found or all possibilities are exhausted.
// Store or print the board configuration when N queens are successfully placed.

bool isSafe(int row,int col,vector<vector<char>>& board,int n){
    for(int j=0;j<col;j++){
        if(board[row][j]=='Q') return false;
    }
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') return false;
    }
    for (int i = row, j = col; i < n && j >= 0; i++, j--) {
        if (board[i][j] == 'Q') return false;
    }
    return true;
}
void solve_brute(int col,vector<vector<char>>& board,vector<vector<string>>& ans,int n){
    if(col==n){
        vector<string> temp;
        for(int i=0;i<n;i++){
            string row(board[i].begin(),board[i].end());
            temp.push_back(row);
        }
        ans.push_back(temp);
        return;
    }

    for(int row=0;row<n;row++){
        if(isSafe(row,col,board,n)){
            board[row][col]='Q';
            solve_brute(col+1,board,ans,n);
            board[row][col]='.';
        }
    }
}
vector<vector<string>> solveNQueens_brute(int n) {
    vector<vector<string>> ans;
    vector<vector<char>> board(n,vector<char>(n,'.'));
    
    solve_brute(0,board,ans,n);
    return ans;
}
//Optimal
// Instead of checking every row, column, and diagonal every time we place a queen (which is slow), we use precomputed boolean arrays to instantly check if 
// a queen can be safely placed. Each array acts like a hash for fast lookup. A row array keeps track of which rows already have a queen. 
// Two diagonal arrays (lowerDiagonal and upperDiagonal) keep track of the diagonals that are under attack. 
// This avoids repetitive scanning and makes the backtracking highly efficient.

// Initialize three boolean arrays, one for rows, one for lower diagonals, and one for upper diagonals.
// Start placing queens column by column from left to right using backtracking.
// For a given column, iterate through all rows and check if placing a queen at (row, col) is safe using the hash arrays.
// To check if placing a queen is safe, ensure the corresponding row, lower diagonal (row + col), and upper diagonal (n - 1 + col - row) are not already marked as attacked in the boolean arrays.
// If safe, place the queen and mark the corresponding row and diagonals as attacked.
// Recurse to the next column to place the next queen.
// When backtracking, remove the queen and unmark the row and diagonals to try other configurations.
// Count or store the solution if all columns are successfully filled with safe placements

void solve(int col, vector<string>& board, int n,
            vector<int>& leftRow, vector<int>& upperDiagonal, vector<int>& lowerDiagonal,
            vector<vector<string>>& ans) {
    // If all queens are placed
    if (col == n) {
        ans.push_back(board);
        return;
    }

    // Iterate through all rows
    for (int row = 0; row < n; row++) {
        // Check if it's safe to place the queen
        if (leftRow[row] == 0 && lowerDiagonal[row + col] == 0 &&
            upperDiagonal[n - 1 + col - row] == 0) {

            // Place the queen
            board[row][col] = 'Q';

            // Mark the row and diagonals
            leftRow[row] = 1;
            lowerDiagonal[row + col] = 1;
            upperDiagonal[n - 1 + col - row] = 1;

            // Recurse to next column
            solve(col + 1, board, n, leftRow, upperDiagonal, lowerDiagonal, ans);

            // Backtrack and remove the queen
            board[row][col] = '.';
            leftRow[row] = 0;
            lowerDiagonal[row + col] = 0;
            upperDiagonal[n - 1 + col - row] = 0;
        }
    }
}
vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> ans;
    vector<string> board(n, string(n, '.'));
    vector<int> leftRow(n, 0), upperDiagonal(2 * n - 1, 0), lowerDiagonal(2 * n - 1, 0);
    solve(0, board, n, leftRow, upperDiagonal, lowerDiagonal, ans);
    return ans;
}

