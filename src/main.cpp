//      booruDownloader 
//      Jamason P Davis
//      Copywrite 2023
//            <3

#include <iostream>
#include <curl/curl.h>
#include <curl/easy.h>
#include <fstream>

size_t writeImage(char *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t realsize = size * nmemb;
    std::ofstream file;
    file.open("images/test.jpg");
    file.write(ptr, realsize);
    file.close();
    return 0;
}

// Image Download Function
int downloadImage() {
    std::cout << "Downloading Image";
    CURL *easy = curl_easy_init(); // Init the easy handle for syncro based downloading, maybe add async support in the future?
    curl_easy_setopt(easy, CURLOPT_URL, "https://testbooru-cdn.donmai.us/original/3a/0e/3a0e769991323dcf9748adba9ab530dc.jpg"); // URL to download
    curl_easy_setopt(easy, CURLOPT_USERAGENT, "libcurl-agent/1.0"); // User agent, required for danbooru
    curl_easy_setopt(easy, CURLOPT_WRITEFUNCTION, writeImage); // Callback to write image
    //curl_easy_setopt(easy, CURLOPT_USERPWD, "Captainjamason:mU4ba6jikixpkNhiDDbTPnHL");   // Authenticate the user
    curl_easy_perform(easy); // do the do
    curl_easy_cleanup(easy); // clean up
    return 0;
}

int main(int argc, char *argv[])
{
    downloadImage();
}
