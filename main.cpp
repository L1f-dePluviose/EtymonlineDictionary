#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <shellapi.h>

#pragma comment(lib, "shell32.lib")

using namespace std;

int main() {
    cout << "Search for: " << endl;

    vector<string> words;
    string line;

    while (getline(cin, line)) {
        if (line.empty()) break;
        words.push_back(line);
    }

    sort(words.begin(), words.end());

    for (const auto& word : words) {
        string url = "https://www.etymonline.com/cn/word/" + word;
        cout << "Open: " << url << endl;

        ShellExecuteA(
                // 父窗口句柄
                nullptr,
                // 操作
                "open",
                // 要打开的文件或 URL
                url.c_str(),
                // 参数
                nullptr,
                // 工作目录
                nullptr,
                // 显示方式
                SW_SHOWNORMAL
        );
    }

    cin.get();

    return 0;
}
