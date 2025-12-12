#include <iostream>
#include <vector>
#include <string.h>
#include <set>
#include <map>

using namespace std;


//Remove Outermost Paranthesis
// A valid parentheses string is either empty "", "(" + A + ")", or A + B, where A and B are valid parentheses strings, and + represents string concatenation.
// For example, "", "()", "(())()", and "(()(()))" are all valid parentheses strings.
// A valid parentheses string s is primitive if it is nonempty, and there does not exist a way to split it into s = A + B, with A and B nonempty valid parentheses strings.
// Given a valid parentheses string s, consider its primitive decomposition: s = P1 + P2 + ... + Pk, where Pi are primitive valid parentheses strings.
string removeOuterParentheses(string s) {
    int l= s.length();
    string output="";
    int level=0;
    for(char ch : s){
        if(ch=='('){
            if(level>0) output+=ch;

            level++;
        }
        if(ch==')'){
            level--;
            if(level>0) output+=ch;
        }
    }

    return output;
}

//Reverse Words in a string
// Given an input string s, reverse the order of the words.
// A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.
// Return a string of the words in reverse order concatenated by a single space.


//BRUTE
string reverseWords(string s) {
    s+=" ";
    stack<string> st;
    string str="";
    for(int i =0;i<s.length();i++){
        if(s[i]==' '){
            st.push(str);
            str="";
        }
        else str+=s[i];

    }   
    string ans="";
    while(st.size()!=1){
        ans+=st.top()+" ";
        st.pop();
    }     
    ans += st.top();

    return ans;
}

//OPTIMAL
string reverseWords(string s){
    int left =0;
    int right=s.length()-1;

    string temp="";
    string ans="";

    while(left<=right){
        char ch = s[left];
        if(ch!=' '){
            temp+=ch;
        }else if(ch==' '){
            if(ans!="") ans = temp+" "+ans;
            else ans= temp;
            temp="";

        }
        left++;
    }
    return ans;
}


//Largest odd number in string
string largestOddNumber(string num) {
int ind = -1;
    for (int i = num.length() - 1; i >= 0; i--) {
        if ((num[i] - '0') % 2 == 1) {
            ind = i;
            break;
        }
    }
    int i=0;
    while ( i <= ind && num[i] == '0') i++;

    return num.substr(i, ind - i + 1);
}


//Longest common prefix
string longestCommonPrefix(vector<string>& str) {
if (str.empty()) return "";
    sort(str.begin(), str.end());
    string first = str[0];
    string last = str[str.size() - 1];
    string ans = "";
    int minLength = min(first.size(), last.size());
    for (int i = 0; i < minLength; i++) {
        if (first[i] != last[i]) break;
        ans += first[i];
    }
    return ans;
}

//Isomorphic Strings
// Given two strings s and t, determine if they are isomorphic.
// Two strings s and t are isomorphic if the characters in s can be replaced to get t.
// All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.
bool isIsomorphic(string s, string t) {
    int m1[256]={0},m2[256]={0};
    int n = s.size();
    for(int i =0;i<n;i++){
        if(m1[s[i]]!=m2[t[i]]) return false;

        m1[s[i]]=i+1;
        m2[t[i]]=i+1;
    }  
    return true;      
}

//Rotate String
bool rotateString(string s, string goal) {
    if(s.length()!=goal.length()) return false;
    
    string doubledS = s+s;
    return doubledS.find(goal) != string::npos;
}

//Valid Anangram
bool isAnagram(string s, string t) {
    if(s.length() != t.length()) return false;

    int count[26] = {0};

    for(int i = 0; i < s.length(); i++){
        count[s[i] - 'a']++;   
    }

    for(int x : count){
        if(x != 0) return false;   
    }
    return true;


}

//Sort Characters Bby frequency
static bool comparator(pair<int,char> p1,pair<int,char> p2){
    if(p1.first>p2.first) return true;
    if(p1.first<p2.first) return false;
    return p1.second<p2.second;;
}
string frequencySort(string s) {
    pair<int,char> freq[52];
    for(int i =0;i<26;i++){
        freq[i]={0,i+'a'};
    }        

    for(int i =26;i<52;i++){
        freq[i]={0,i+'A'};
    }

    for(char c:s){
        if(c>='a'&&c<='z'){
            freq[c - 'a'].first++;
        }else if(c>='A'&&c<='Z'){
            freq[c - 'A'].first++;
        }
    }

    sort(freq,freq+26,comparator);

    vector<char> ans;
    for (int i = 0; i < 52; i++) {
        if (freq[i].first > 0) ans.push_back(freq[i].second);

    }
    string result;
    for (char c : ans) {
        result+=c;
    }
    return result;
}

//Maximium Nesting Depth of the Paranthesis
int maxDepth(string s) {
    int depth=0,maxdep=0;
    for(char c: s){
        if(c=='(') depth++;
        maxdep=max(maxdep,depth);
        if(c==')') depth--;
    }
    return maxdep;        
}


//Roman To Integer
int romanToInt(string s) {
    int res=0;
    
    unordered_map<char, int> roman = {
        {'I', 1}, {'V', 5}, {'X', 10},
        {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}
    };

    for(int i =0;i<s.size()-1;i++){
        if(roman[s[i]]<roman[s[i]+1]){
            res -=roman[s[i]];
        }else{
            res+=roman[s[i]];
        }
    }

    return res+roman[s.back()];

}

//Strinng to Integer
int myAtoi(string s) {
    int sign=1,i=0;
    
    long res=0;
    while(i<s.size() && s[i]==' ')i++;

    if(i==s.size()) return 0;

    if(s[i]=='-'){
        sign=-1;
        i++;
    }else if(s[i]=='+'){
        sign=1;
        i++;
    }
    while(i<s.size() && isdigit(s[i])){
        res = res*10 + (s[i]-'0');
        if(sign*res>INT_MAX)return INT_MAX;
        if(sign*res<INT_MIN) return INT_MIN;
        i++;
    }
    return (int)res*sign;
}


//Longest Palindrome Substring
int expandfromCenter(const string& str, int left, int right){
    while(left>=0 && right<str.length() && str[left]==str[right]){
        left--;
        right++;
    }

    return right-left-1;
}
string longestPalindrome(string s) {
    int start=0,end=0;

    for(int center=0;center<s.size();center++){
        int lenodd = expandfromCenter(s,center,center);

        int leneven = expandfromCenter(s,center,center+1);

        int maxlen= max(lenodd,leneven);

        if(maxlen>end-start){
            start=center-(maxlen-1)/2;
            end=center+maxlen/2;
        }
    }
    return s.substr(start, end - start + 1);

}

//Sum of beauty of All Substrings
int beautySum(string s) {
    int n = s.length();
    int sum=0;
    for(int i =0;i<n;i++){
        unordered_map<char,int> freq;

        for(int j =i;j<n;j++){
            freq[s[j]]++;

            int maxi=INT_MIN;
            int mini= INT_MAX;

            for(auto it: freq){
                mini= min(mini, it.second);
                maxi=max(maxi,it.second);
            }
            sum+=(maxi-mini);
        }
    } 
    return sum;       
}


int main(){

}