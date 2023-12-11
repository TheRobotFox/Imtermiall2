#include <map>
#include <string>
#include <unordered_map>
#include <memory>
#include <cstddef>
#include <functional>

namespace Assets {

    class Asset;

    inline std::size_t type_id_counter;
    template<typename T> inline std::size_t type_id = type_id_counter++;

    template<typename T>
    struct _AssetInfo{
        T asset;
        std::size_t registered = 1;
        std::size_t type = type_id<T>;
    };

    template<typename... AT> class _AssetManager {

           template<typename T>
            static std::unordered_map<std::string, _AssetInfo<T>> data;

    public:
        template<typename T>
        static std::shared_ptr<T> get_asset(const std::string id){
            if(data<T>.contains(id))
                return std::make_shared(data<T>[id]);
            else
              return nullptr;
        }

    template<typename T>
    static bool register_asset(std::string &&id, T &&asset){
        if(contains(id)) {
            if(data<T>[id].asset != asset){
                return false;
            }
            data<T>[id].registered++;
        } else {
            data<T>[id] = _AssetInfo {.asset = asset};
        }
        return true;
    }

    static bool unregister_asset(std::string &&id){
        bool ret = false;
        ([&]{
            if(data<AT>.contains(id)){
                if(!--data<AT>[id].registered){
                    data<AT>.erase(id);
                }
                ret = true;
            }
        }(), ...);
        return false;
    }

    public:
        template<typename T>
        static bool load_asset(std::string &&id, const T &&asset){
            if(!contains(id)) return false;
            return (data<T>[id].asset.loaded = data<T>[id].asset.load());
        }

    public:
        static bool contains(std::string id)
        {
            return (data<AT>.contains(id) || ...);
        }

    };

    template<typename... AT>
    template<typename T>
      std::unordered_map<std::string, _AssetInfo<T>> _AssetManager<AT...>::data;

#define REGISTER_MANAGER(...) typedef Assets::_AssetManager<__VA_ARGS__> AssetManager;
} // Namespace Assets

namespace Assets {
    class Asset{
        template<typename...>
        friend class _AssetManager;

        std::size_t registerd = 0;
        bool loaded=false;

        protected:
        virtual bool load() = 0;
        virtual void unload() = 0;
        virtual bool operator!=(const Asset &rhs) = 0;

        public:
        virtual std::size_t get_type() = 0;
    };
}
