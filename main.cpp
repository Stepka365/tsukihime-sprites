#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>

const std::string folder_str = R"(C:\Users\selya\Games\pictures\Arcueid)";
using namespace std::filesystem;

void undir_files_to(const path& from, const path& to) {
    for (const auto& cur_obj: directory_iterator(from)) {
        if (cur_obj.is_directory()) {
            undir_files_to(cur_obj, to);
        }
        else {
            path file = to.string() + '\\' +  cur_obj.path().filename().string();
            copy_file(cur_obj, file);
            remove(cur_obj);
        }
    }
    remove(from);
}

void undir_files(const path& folder) {
    for (const auto& cur_obj: directory_iterator(folder)) {
        if (cur_obj.is_directory()) {
            undir_files_to(cur_obj, folder);
        }
    }
}

void remove_duplicates(const path& folder, size_t key_pos, char key_letter_good, char key_letter_bad) {
    for (const auto& cur_file: directory_iterator(folder)) {
        if (!cur_file.is_directory() && cur_file.path().string()[key_pos] == key_letter_bad) {
            std::string file_a_str = cur_file.path().string();
            file_a_str[key_pos] = key_letter_good;
            path file_a = file_a_str;
            if (exists(file_a)) {
                remove(cur_file);
            }
        }
    }
}

void remove_blurred(const path& folder) {
    for (const auto& cur_file: directory_iterator(folder)) {
        std::string file_name = relative(cur_file, folder).string();
        if (!cur_file.is_directory() && std::count(file_name.begin(), file_name.end(), '_') > 4) {
            remove(cur_file);
        }
    }
}

void remove_lines(const path& folder){
    for (const auto& cur_file: directory_iterator(folder)) {
        std::string file_name = relative(cur_file, folder).string();
        if (!cur_file.is_directory() && std::count(file_name.begin() + 5, file_name.end(), 'a') > 0) {
            remove(cur_file);
        }
    }
}

int main() {
    path folder = folder_str;
    size_t key_pos = folder_str.size() + 5;
//    remove_blurred(folder);
//    remove_duplicates(folder, key_pos, 'a', 'l');
//    remove_duplicates(folder, key_pos, 'a', 'm');
//    remove_duplicates(folder, key_pos, 'a', 's');
    remove_lines(folder);
    //undir_files(folder);
    return 0;
}
