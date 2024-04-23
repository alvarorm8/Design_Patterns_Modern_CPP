#include <iostream>
#include <string>
#include <sstream>
#include <memory>
using namespace std;

/*
* Communication proxy is used to access data which is not in the local process, but in a different space, for example a website.
* 
* Here RemotePong emulates the work of Pong class but accessing to a website to get the data. This way we are maintaining the inteface
* but changing the backend in an invisible way to the user.
*/

struct Pingable
{
    virtual ~Pingable() = default;
    virtual wstring ping(const wstring& message) = 0;
};

struct Pong : Pingable
{
    wstring ping(const wstring& message) override
    {
        return message + L" pong";
    }
};

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

struct RemotePong : Pingable
{
    wstring ping(const wstring& message) override
    {
        wstring result;
        http_client client(U("http://localhost:9149/"));
        uri_builder builder(U("/api/pingpong/"));
        builder.append(message);
        pplx::task<wstring> task = client.request(methods::GET, builder.to_string())
            .then([=](http_response r)
                {
                    return r.extract_string();
                });
        task.wait();
        return task.get();
    }
};

void tryit(Pingable& pp)
{
    wcout << pp.ping(L"ping") << "\n";
}

void communication_proxy()
{
    //Pong pp;
    RemotePong pp;//This is all I have to change to use the proxy, since it has the same interface
    for (int i = 0; i < 3; ++i)
    {
        tryit(pp);
    }
}

int main()
{
    communication_proxy();

    getchar();
    return 0;
}