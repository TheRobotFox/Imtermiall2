#include <cstddef>
#include <memory>
namespace Assets {
    class Asset{
        public:
        virtual std::size_t get_type() = 0;
    };
}

#include <map>
#include <string>
#include <unordered_map>
#include <memory>
namespace Assets{
    // template<typename... AT> class _AssetManager;

  template<typename T, typename... Tail> class _AssetHelper : public _AssetHelper<T>, public _AssetHelper<Tail...> {};

    template<typename T> class _AssetHelper<T> {
      template<typename...>
        friend class _AssetManager;
        std::unordered_map<std::string, T> data;
    };
    template<typename... AT> class _AssetManager : public _AssetHelper<AT...> {
    public:
        template<typename T>
        std::shared_ptr<T> get_asset(const std::string id){
            if(_AssetHelper<T>::data.contains(id))
                return std::make_shared(_AssetHelper<T>::data[id]);
            else
              return nullptr;
        }

        template<typename T>
        bool load_asset(std::string &&id, const T &&asset){
            // if(contains(id)) return false;
            _AssetHelper<T>::data[id] = asset;
            return true;
        }
        bool contains(std::string id)
        {
            return _contains<AT...>(id);
        }

    private:
        template<typename T1, typename T2, typename... Tail>
        bool _contains(std::string id)
        {
            if(Assets::_AssetHelper<T1>::data.contains(id)) return true;
            return _contains<T2, Tail...>(id);
        }
        template<typename T> bool _contains(std::string id)
        {
            if(Assets::_AssetHelper<T>::data.contains(id)) return true;
            else return false;
        }

    };
    #define REGISTER_MANAGER(...) typedef Assets::_AssetManager<__VA_ARGS__> AssetManager;
}

namespace Assets {
    inline std::size_t type_id_counter = 0;
    template<typename T> inline std::size_t type_id = type_id_counter++;
    template<typename T> class AssetId : public Asset{
        public:
        std::size_t get_type(){return type_id<T>;}
    };

    #define IMPL_ASSET(NAME) class NAME : public Assets::AssetId<NAME>
}
