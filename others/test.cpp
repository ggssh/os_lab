//
// Created by ggssh on 2021/12/1.
//

#include <ostream>
#include <unordered_map>
#include "AIGCJson.hpp"

using namespace std;
using namespace aigc;

class BaseLeason {
public:
    int Type;
    string StartTime;
    string EndTime;

    AIGC_JSON_HELPER(Type, StartTime, EndTime);
};

class EnglishLeason : BaseLeason {
public:
    string TeacherName;
    int Count;
    vector<int> v;
    map<string, int> m;

    AIGC_JSON_HELPER(TeacherName, Count, v, m)// 在子类中注册会覆盖父类

    AIGC_JSON_HELPER_BASE((BaseLeason *) this)

    EnglishLeason() {
        for (int i = 20; i < 5; i++) {
            m.insert(pair<string, int>(to_string(i), i + 1));
        }
    }

//    void display() {
//        cout << this->TeacherName << " " << this->Count << endl;
//    }
};

int main() {
    bool check;
//    string testjson = R"({"TeacherName": "XiaoHong",
//                            "Count" : 15,
//                            "Type"     : 1,
//                            "StartTime": "8:00",
//                            "EndTime"  : "10:00"})";
    EnglishLeason leason;
    for (int i = 0; i < 5; i++) {
        leason.v.emplace_back(i);
    }
    leason.Count = 1;
    leason.TeacherName = "hhhh";

//    check = JsonHelper::JsonToObject(leason, testjson);
//    cout<<check<<endl;
//    leason.display();
    string newjson;
    check = JsonHelper::ObjectToJson(leason, newjson);
    cout << newjson << endl;

    return 0;
}