#ifndef TESTINGSTRUCTS_HPP
#define TESTINGSTRUCTS_HPP
namespace Tests{

struct NoStatic{
    int value{0};
    void addOne(){
        ++value;
    }
    void removeOne(){
        --value;
    }
   void add(int i){
       value+=i;
   }
   void remove(int i){
		value-=i;
   }
};
struct StaticStruct{
    static int value;
    static void addOne(){
        ++ value;
    }
    static void removeOne(){
        -- value;
    }
    static void add(int i){
        value+=i;
    }
    static void remove(int i){
        value -=i;
    }
};

int externValue{0};
inline void addOne(){
    ++externValue;
}

inline void removeOne(){
    --externValue;
}

inline void addValue(int i){
    externValue+= i;
}

inline void removeValue(int i){
    externValue -= i;
}

int StaticStruct::value=0;

} // namespace Tests
#endif // TESTINGSTRUCTS_HPP
