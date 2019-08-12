
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "stb/stb_image_write.h"
#include "cmdline.hxx"
#include "../cactus/cactus.hpp"
int split(cactus::Tensor<stbi_uc>& data,std::vector<cactus::Tensor<stbi_uc>> &tmp) {
    for (size_t i = 0; i < data.size(); i++)
    {
        
    }
    return 0;
}
cactus::Tensor<stbi_uc> readImage(const char* path) {
    size_t x, y, ch;
    stbi_uc* data=stbi_load(path, (int*)&x, (int*)&y, (int*)&ch, 0);
    cactus::Tensor<stbi_uc> tmp({x,y,ch});
    memcpy(tmp.data(),data,x*y*ch);
    stbi_image_free(data);
    return std::move(tmp);
}
int saveJpeg(const char* path, cactus::Tensor<stbi_uc> tmp) {
    auto s=tmp.shape();
    return stbi_write_jpg(path, s[0], s[1], s[2], tmp.data(), 0);
}
int main(int argc, char **argv) {
    cmdline::parser args;

    args.add<std::string>("src", 's', "src audio'path", true, "./");
    args.add<std::string>("dst", 'd', "dst feature'path", true, "./");
    args.parse_check(argc, argv);
    auto data=readImage("lenna.png");
    saveJpeg("test.jpg", data);
    return 0;
}