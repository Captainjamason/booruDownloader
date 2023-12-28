//      booruDownloader 
//      Jamason P Davis
//      Copywrite 2023
//            <3

#include <iostream>
#include <curl/curl.h>
#include <curl/easy.h>

// Image Download Function
int downloadImage() {
    CURL *easy = curl_easy_init();
    curl_easy_setopt(easy, CURLOPT_URL, "https://testbooru.donmai.us/posts/9863");
    curl_easy_perform(easy);
    curl_easy_cleanup(easy);
    return 1;
}

int main(int argc, char *argv[])
{
    downloadImage();
}
