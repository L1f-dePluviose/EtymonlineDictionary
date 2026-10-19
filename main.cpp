#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <windows.h>
#include <shellapi.h>

#pragma comment(lib, "shell32.lib")

int main() {
    std::cout << "Searching Words from Etymonline." << std::endl;
    std::cout << "'.' to undo previous, empty line to finish." << std::endl;
    std::cout << std::endl;
    std::cout << "Search for: " << std::endl;

    std::vector<std::string> words;
    std::string line;
    bool lastDelete = false;

    while (getline(std::cin, line)) {
        if (line.empty()) break;

        if (line == ".") {
            if (!lastDelete && !words.empty()) words.pop_back();
            lastDelete = true;
        } else {
            words.push_back(line);
            lastDelete = false;
        } // if else
    } // while

    if (words.empty()) return 1;

    sort(words.begin(), words.end());

    words.erase(unique(words.begin(), words.end()), words.end());

    const auto interval = std::chrono::milliseconds(500);
    auto nextAllowed = std::chrono::steady_clock::now();

    std::cout << "Open:" << std::endl;

    for (const auto& word : words) {
        auto now = std::chrono::steady_clock::now();
        if (now < nextAllowed) std::this_thread::sleep_until(nextAllowed);

        std::string url = "https://www.etymonline.com/cn/word/" + word;
        std::cout << url << std::endl;

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

        nextAllowed = std::chrono::steady_clock::now() + interval;
    } // for

    std::cin.get();

    return 0;
} // main()
