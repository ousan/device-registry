// ping.cpp
#include <cstdlib>
#include <string>
#include <unistd.h>

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

/*std::string lookup_env(const std::string &name) {
  char *env = std::getenv(name.c_str());
  if (!env) {
    throw std::runtime_error("missing environment variable: " + name);
  }
  return env;
}*/

#include <httplib.h>
#include <nlohmann/json.hpp>

using namespace httplib;
using json = nlohmann::json;

int main() {
    try {
        sleep(3);
        // Create an instance.
        mongocxx::instance inst{};

        //std::string connection_string = lookup_env("MONGO_CONNECTION_STRING");

        const auto uri = mongocxx::uri{"mongodb://mongodb:27017"};

        // Set the version of the Stable API on the client.
        mongocxx::options::client client_options;
        const auto api = mongocxx::options::server_api{
            mongocxx::options::server_api::version::k_version_1};
        client_options.server_api_opts(api);

        // Setup the connection and get a handle on the "admin" database.
        mongocxx::client conn{uri};
        mongocxx::database db = conn["local"];
        std::cout << "local connection" << std::endl;

        // Ping the database.
        const auto ping_cmd = bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("ping", 1));
        db.run_command(ping_cmd.view());
        std::cout
            << "Pinged your deployment using the MongoDB C++ Driver. "
            << "You successfully connected to MongoDB!"
            << std::endl;

        
        Server svr;

        std::cout << "Server starting..." << std::endl;

        svr.Get("/devices", [](const Request & /*req*/, Response &res) {
            res.set_content("Hello World!", "application/json");
        });
    
        svr.Post("/devices", [](const Request &req, Response &res) {
            
            json data = json::parse(req.body);
            //std::cout << data.dump(4) << std::endl;
            std::cout << data["name"] << std::endl;
            res.set_content("OK", "text/plain");
        });
        
        svr.listen("0.0.0.0", 8085);
    
    } catch (const std::exception &e) {
        // Handle errors
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}