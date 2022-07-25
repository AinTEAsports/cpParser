#include <iostream>
#include <string>
#include <cpr/cpr.h>

#include "cpparser.cpp"


void resumeUrl(std::string url) {
    cpr::Response response = cpr::Get(cpr::Url{url});

    std::cout << "URL: " << url << '\n';
    std::cout << "Reason: " << response.reason << '\n';
    std::cout << "Redirect count: " << response.redirect_count << '\n';
    std::cout << "Status code: " << response.status_code << '\n';
    std::cout << "Status line: " << response.status_line << '\n';
    std::cout << "Elapsed: " << response.elapsed << '\n';
}


void shortResumeUrl(std::string url) {
    cpr::Response response = cpr::Get(cpr::Url{url});

    std::cout << "URL: " << url << '\n';
    std::cout << "Status code: " << response.status_code << '\n';
    std::cout << "Elapsed: " << response.elapsed << '\n';
}



int main(int argc, char** argv) {
    Parser parser("A CLI tool that get informations about URLs");

    parser.addArgument(
        "-u",
        "--urls",
        "urlList",
        Parser::STORE_MULTIPLE_VALUES,
        "The URLs you want to check"
    );

    parser.addArgument(
        "-s",
        "--short-version",
        "shortversion",
        Parser::STORE_TRUE,
        "Option to put if you want short resume"
    );

    auto args = parser.parseArgs(argc, argv);


    for (std::string url: args["urlList"].Vector) {
        if (args["shortversion"].Bool) {
            shortResumeUrl(url);
        } else {
            resumeUrl(url);
        }

        std::cout << "\n----- ----- -----\n\n";
    }

    return 0;
}
