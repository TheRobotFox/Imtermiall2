#include "Assets.h"
#include <iostream>

using namespace Assets;

REGISTER_MANAGER(int, float)

int main(void) {
    std::cout << "Is Asset loaded ? " << (AssetManager::contains("funny_num") ? "yes" : "no.") << std::endl;
    std::cout << "Register Asset! (69)" << std::endl;

    AssetManager::register_asset("funny_num", 69);

    std::cout << "Register Asset again!" << std::endl;

    AssetManager::register_asset("funny_num", 69);

    std::cout << "Is Asset loaded ? " << (AssetManager::contains("funny_num") ? "yes" : "no.") << std::endl;
    std::string the_asset = AssetManager::get_asset<int>("funny_num").transform([](auto a){return std::to_string(a);}).value_or("not present");
    std::cout << "The Asset: " << the_asset << std::endl;

    std::cout << "Unregister once!" << std::endl;

    AssetManager::unregister_asset("funny_num");

    std::cout << "Is Asset loaded ? " << (AssetManager::contains("funny_num") ? "yes" : "no.") << std::endl;
    std::cout << "Unregister again!" << std::endl;

    AssetManager::unregister_asset("funny_num");

    std::cout << "Is Asset loaded ? " << (AssetManager::contains("funny_num") ? "yes" : "no.") << std::endl;
    the_asset = AssetManager::get_asset<int>("funny_num").transform([](auto a){return std::to_string(a);}).value_or("not present");
    std::cout << "The Asset: " << the_asset << std::endl;
}
