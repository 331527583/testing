//
// Created by apple on 2023/3/23.
//

#ifndef PANGUTEST_REGISTERER_H
#define PANGUTEST_REGISTERER_H
#include <map>
#include <string>
namespace registerer {
   class Any{
   public:
       Any(){}
       virtual ~Any(){
           delete content_;
       }

       template<typename ValueType>
       ValueType* any_cast() {
           return content_ ? &static_cast<Holder<ValueType>*>(content_)->held_:NULL;
       }

       template <typename ValueType> //NOLINT
       Any(const ValueType & value):content_(new Holder<ValueType>(value)){
       }

       template<typename ValueType>
       Any(const Any & other):
       content_(other.content_?other.content_->clone():NULL){}

   private:
       class PlaceHolder{
       public:
           virtual ~PlaceHolder(){

           }
           virtual PlaceHolder * clone() const = 0;
       };
       template <typename ValueType>
       class Holder : public PlaceHolder{
       public:
           explicit Holder(const ValueType valueType):held_(valueType){}
           virtual PlaceHolder * clone() const {
               return new Holder(held_);
           }

       public:
           ValueType held_;
       };
       PlaceHolder * content_;
   }; // namespace Any

   class ObjectFactory{
   public:
       ObjectFactory(){}
       virtual ~ObjectFactory(){}

   public:
       virtual Any NewInstance(){
           return Any();
       }
       virtual Any GetSingletonInstance(){
           return Any();
       }
   private:
       ObjectFactory(const ObjectFactory& );
       //ObjectFactory operator=(const ObjectFactory & );
       void operator=(const ObjectFactory & );
   };
   typedef std::map<std::string,ObjectFactory*> FactoryMap;
   typedef std::map<std::string,FactoryMap>  BaseClassMap;
   BaseClassMap& global_factory_map();
} //namespace registerer

#define REGISTER_REGISTERER(base_class) \
class base_class ## Register { \
    typedef ::registerer::Any Any;\
    typedef ::registerer::FactoryMap FactoryMap;\
    public: \
        static base_class *GetInstanceByName(const std::string &name) {\
            FactoryMap &map = ::registerer::global_factory_map()[#base_class];\
            FactoryMap::iterator iter = map.find(name);\
            if(iter == map.end()){\
                return NULL;\
            }\
            Any obj = iter->second->NewInstance();\
            return *(obj.any_cast<base_class*>());\
        }\
        static base_class *GetSingletonInstanceByName(const std::string &name) { \
            FactoryMap &map = ::registerer::global_factory_map()[#base_class];\
            FactoryMap::iterator iter = map.find(name);\
            if(iter == map.end()){\
                return NULL;\
            }\
            Any obj = iter->second->GetSingletonInstance();\
            return *(obj.any_cast<base_class*>());\
        }\
           static const ::std::string GetUniqInstanceName() {\
           FactoryMap &map = ::registerer::global_factory_map()[#base_class];\
           return map.begin()->first;\
           }\
           static base_class *GetUniqInstance(){\
                FactoryMap &map = ::registerer::global_factory_map()[#base_class];\
                Any object = map.begin()->second->NewInstance();\
                return *(object.any_cast<base_class*>());\
           }\
           static bool IsValid(const ::std::string &name) {\
                FactoryMap &map=::registerer::global_factory_map()[#base_class];\
                return map.find(name) != map.end();\
           }\
    };\

    #define REGISTER_CLASS(clazz, name) \
        namespace registerer {\
           class ObjectFactory##name : public ::registerer::ObjectFactory {\
           public:\
                ::registerer::Any NewInstance(){\
                     return ::registerer::Any(new name());\
                }\
                ::registerer::Any GetSingletonInstance() {\
                    return ::registerer::Any(new name());\
                }\
           };\
           void register_factory_##name(){\
                cout << "register_factory__" <<#name << "\n";\
                ::registerer::FactoryMap & map=\
                ::registerer::global_factory_map()[#clazz];\
                if(map.find(#name) == map.end())\
                    map[#name] = new ObjectFactory##name();\
           }\
           __attribute__((constructor)) void register_factory_##name();\
        }
#endif //PANGUTEST_REGISTERER_H
