#include <filesystem>
#include <fstream>
#include <string>

using namespace std::string_literals;

int main()
{
    std::filesystem::copy_options co = std::filesystem::copy_options::overwrite_existing;

    for (const auto& f : std::filesystem::directory_iterator{"."}) {
        if (!std::filesystem::is_regular_file(f.path())) continue;

        std::string cur = f.path().string();

        std::string_view cur_sv = cur;

        // std::filesystem::copy(f.path(), cur + "(1)", co);
        auto dot_pos = cur.find_last_of('.');
        auto rem_pos_it = cur.begin() + dot_pos;

        cur_sv.remove_suffix(cur.end() - rem_pos_it);
        std::string new_n = cur_sv.data() + ".mp3"s;

        system(("ffmpeg -hwaccel vaapi -i \""s + cur + "\" \"" + new_n + "\"").c_str());

        std::filesystem::remove(cur);
    }

    return 0;
}
