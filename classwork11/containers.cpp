#include <iostream>
#include <vector>
#include <set>
#include <random>
#include <map>

using namespace std;
//1 task
int numRabbits(vector<int>& answers) {
    int result = answers.size();
    for(int i = 0; i < answers.size(); i++){
        if(answers[i] != -1) {
            int current = answers[i];
            int n = 0;
            for (int j = i; j < answers.size(); j++) {
                if(current == answers[j]) {
                    ++n;
                    answers[j] = -1;
                }
            }
            if(n % (current+1) != 0){
                result += (current + 1 - n % (current+1));
            }
        }
    }
    return result;
}
//2 task
class RandomizedSet {
public:
    RandomizedSet(){
        set<int> a;
        data = a;
    };

    bool insert(int val){
        if(data.count(val) > 0){
            return false;
        }else{
            data.insert(val);
            return true;
        }
    };

    bool remove(int val){
        if(data.count(val) > 0){
            data.erase(val);
            return true;
        }else{
            return false;
        }
    };

    int getRandom(){
        std::default_random_engine rng(10);
        std::uniform_int_distribution<int> dstr(0, data.size());
        int idx = dstr(rng);
        int i = 0;
        for(int x: data){
            if (i == idx)
                return x;
            i++;
        }
    };

private:
    set<int> data;
};

//3 task

multimap<int, int> map_constructor(vector<int>& nums){
    multimap<int, int> data;
    for(int i = 0; i < nums.size(); i++) {
        if (nums[i] != NULL) {
            int current = nums[i];
            int n = 0;
            for (int j = i; j < nums.size(); j++) {
                if (current == nums[j]) {
                    ++n;
                    nums[j] = NULL;
                }
            }
            data.insert(pair<int, int>(n, current));
        }
    }
    return data;
}

int majorityElement1(vector<int>& nums) {
    multimap<int, int> data = map_constructor(nums);
    for (auto&& item : data) {
        if (item.first > nums.size()/2)
            return item.second;
    }
    return NULL;
}

vector<int> majorityElement2(vector<int>& nums) {
    multimap<int, int> data = map_constructor(nums);
    vector<int> result;
    for (auto&& item : data) {
        if (item.first > nums.size()/3) {
            result.push_back(item.second);
        }
    }
    return result;
}

vector<int> majorityElement3(vector<int>& nums, int k) {
    multimap<int, int> data = map_constructor(nums);
    vector<int> result;
    auto iter = (data.end());
    for (int i = 0; i < k; i++) {
        iter--;
        result.push_back(iter->second);
    }
    return result;
}

//task 4
vector<int> twoSum(vector<int>& nums, int target) {
    vector<int> result;
    for(int i = 0; i < nums.size() - 1; i++) {
        for (int j = i + 1; j < nums.size(); j++){
            if(nums[i] + nums[j] == target){
                result.push_back(i);
                result.push_back(j);
                return result;
            }
        }
    }
}

//task 5
int removeDuplicates(vector<int>& nums) {
    auto iter = nums.begin();
    int size = 1;
    iter++;
    for (int i = 1; i < nums.size(); i++){
        if(nums[i] != nums[i-1]){
            *iter = nums[i];
            iter++;
            size++;
        }
    }
    return size;
}

//task 6
vector<string> findRepeatedDnaSequences(string s) {
    vector<string> result;
    for(int i = 0; i < s.length() - 10; i++){
        bool flag = false;
        for(string item: result){
            if(s.substr(i, 10) == item)
                flag = true;
        }
        if (!flag) {
            for (int j = i + 1; j < s.length() - 10; j++) {
                if (s.substr(i, 10) == s.substr(j, 10)) {
                    result.push_back(s.substr(i, 10));
                    break;
                }
            }
        }
    }
    return result;
}

int main(){
    cout << "-------1-------" << endl;
    vector<int> answers = {1,1,2};
    cout << numRabbits(answers) << endl;

    cout << "-------2-------" << endl;
    RandomizedSet s1;
    cout << s1.insert(5) << endl;
    cout << s1.insert(5) << endl;
    cout << s1.insert(6) << endl;
    cout << s1.remove(3) << endl;
    cout << s1.remove(5) << endl;
    cout << s1.getRandom() << endl;

    cout << "--------3------" << endl;
    vector<int> nums1 = {1, 1, 2, 5, 5, 5, 5};
    cout << majorityElement1(nums1) << endl;

    vector<int> nums2 = {1, 1, 1, 5, 5, 5, 2};
    for (auto && item : majorityElement2(nums2)){
        cout << item << ' ';
    }
    cout << '\n';

    vector<int> nums3 = {1, 1, 1, 5, 5, 5, 2, 2, 1, 3, 2, 2, 2};
    for (auto && item : majorityElement3(nums3, 2)){
        cout << item << ' ';
    }
    cout << '\n';

    cout << "-------4-------" << endl;
    vector<int> nums4 = {2,7,11,15};
    for (auto && item : twoSum(nums4, 22)){
        cout << item << ' ';
    }
    cout << '\n';

    cout << "-------5-------" << endl;
    vector<int> nums5 = {2,2, 2, 2, 4, 4, 4, 5, 6, 6};
    int new_size = removeDuplicates(nums5);
    cout << new_size << endl;
    for (int i = 0; i < new_size; ++i){
        cout << nums5[i] << ' ';
    }
    cout << '\n';

    cout << "-------6-------" << endl;
    string s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
    for (auto && item : findRepeatedDnaSequences(s)){
        cout << item << ' ';
    }
}