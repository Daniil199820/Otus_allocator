#include <iostream>
#include <map>
#include "lib_allocators.h"
#include "lib_containers.h"

class factorial
{
    private:
        int numb=0;
        std::unique_ptr<int[]> arr_ptr;
        void init_array(int value)
        {
            numb=value;    
            arr_ptr = std::make_unique<int[]>(value+1);
            
            int i=0;
            while(i<=value)
            {
                if(i==0)
                    arr_ptr[i]=1;
                else
                    arr_ptr[i]=arr_ptr[i-1]*i;
                ++i;
            }

        }
    
    public:
        factorial() = default;
        ~factorial() = default;

        void reserve_max_factorial(int value)
        {
           init_array(value);
        }


        int calculate(int value)
        {
            if(numb>value)
            {
                return arr_ptr[value];    
            } 
            else
            {
                init_array(value*2);
            }
            return arr_ptr[value];
        }
        
};

template<typename T>
void print_map(const T& container )
{
    for(const auto& it:container)
    {
        std::cout<< it.first <<" "<<it.second<< std::endl;
    }
}

int main()
{
    //1)
    std::map<const int,int> ordered_map;
    factorial factorial_base;
    factorial_base.reserve_max_factorial(9);
    
    //2)
    for(int i=0;i<10;++i)
    {
        ordered_map[i]= factorial_base.calculate(i);
    }
    
    //3)
    std::map<const int,int,std::less<int>,myLinear_allocator<std::pair<const int,int>,10>> ordered_map_custom;

    //4)
    for(int i=0;i<10;++i)
    {
        ordered_map_custom[i]= factorial_base.calculate(i);
    }

    //5)
    std::cout<<"Print map with std::allocator"<<std::endl;
    print_map(ordered_map);

    //6)
    std::cout<<"Print map with custom allocator"<<std::endl;
    print_map(ordered_map_custom);

    //7)
    my_containers::list<int,std::allocator<int>> custom_list_with_std_allocator;
    for(int i=0;i<10;++i)
    {
        custom_list_with_std_allocator.push_back(i);
    }
    
    //8)
    std::cout<<"Print custom list with standart allocator"<<std::endl;
    custom_list_with_std_allocator.print();

    //9)
    my_containers::list<int,myLinear_allocator<int,10>> custom_list_with_custom_allocator;
    for(int i=0;i<10;++i)
    {
        custom_list_with_custom_allocator.push_back(i);
    }
    
    //10)
    std::cout<<"Print custom list with custom allocator"<<std::endl;
    custom_list_with_custom_allocator.print();
}