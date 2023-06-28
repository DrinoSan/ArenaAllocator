#include <iostream>
#include <string>
#include <unistd.h>

struct Region {
  int64_t capacity = 0;
  int64_t size = 0;
  char* data = nullptr;
};


void arenaInit(Region& r, size_t capacity)
{
    r.capacity = capacity;
    r.size = 0;
    r.data = new char[capacity];
}

void* arenaAllocate(Region& r, int32_t size) {
  if (!r.size + size > r.capacity)
  {
    std::cout << "You are exceeding the max capacity!\n";
    return nullptr;
  }

  void* ptr = r.data + r.size;
  r.size += size;

  return ptr;
}

void arenaDeallocate(Region& r)
{
    r.size = 0;
}

void arenaDelete(Region& r)
{
    delete[] r.data;
}

int main() 
{ 
    Region arena;
    arenaInit(arena, 1024UL * 1024UL * 1024UL * 1024UL);

    int* ptr1 = static_cast<int*>(arenaAllocate(arena, sizeof(double)));
    *ptr1 =  500;


    int* ptr2 = static_cast<int*>(arenaAllocate(arena, sizeof(double)));
    *ptr2 =  222;


    std::cout << "ptr1: " << *ptr1 << std::endl;
    std::cout << "Address ptr1: " << ptr1 << std::endl;

    std::cout << "ptr2: " << *ptr2 << std::endl;
    std::cout << "Address ptr2: " << ptr2 << std::endl;

    std::cout << "--------------------------------------" << std::endl;

    arenaDeallocate(arena);

    std::string* ptr3 = static_cast<std::string*>(arenaAllocate(arena, sizeof(std::string)));
    *ptr3 =  "SANDRINO";


    std::string* ptr4 = static_cast<std::string*>(arenaAllocate(arena, sizeof(std::string)));
    *ptr4 =  "ARENA";

    std::cout << "ptr3: " << *ptr3 << std::endl;
    std::cout << "Address ptr3: " << ptr3 << std::endl;

    std::cout << "ptr4: " << *ptr4 << std::endl;
    std::cout << "Address ptr4: " << ptr4 << std::endl;

    std::cout << "--------------------------------------" << std::endl;

    arenaDeallocate(arena);

    std::string* ptr5 = static_cast<std::string*>(arenaAllocate(arena, sizeof(std::string)));
    *ptr3 =  "SANDRINO";


    std::string* ptr6 = static_cast<std::string*>(arenaAllocate(arena, sizeof(std::string)));
    *ptr4 =  "ARENA";

    std::cout << "ptr5: " << *ptr5 << std::endl;
    std::cout << "Address ptr5: " << ptr5 << std::endl;

    std::cout << "ptr6: " << *ptr6 << std::endl;
    std::cout << "Address ptr6: " << ptr6 << std::endl;

    std::cout << "--------------------------------------" << std::endl;

    for(int64_t i = 0; i < 1024UL * 1024UL * 1024UL; ++i)
    {
         *(static_cast<std::string*>(arenaAllocate(arena, sizeof(std::string)))) = "DEADBEEF";
    }

    // Objects are still in memory but will be overwritten
    arenaDeallocate(arena);
    std::cout << "Deallocated arena" << std::endl;
    std::string* ptr7 = static_cast<std::string*>(arenaAllocate(arena, sizeof(std::string)));
    *ptr7 =  "FINISHED";
    std::cout << "ptr7: " << *ptr7 << std::endl;
    std::cout << "Address ptr7: " << ptr7 << std::endl;


    arenaDelete(arena);
    sleep(60);
    return 0;
}
