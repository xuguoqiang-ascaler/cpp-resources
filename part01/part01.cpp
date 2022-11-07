
#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include <stdexcept>

#include <ctime>
#include <cstdlib>
#include <cstring>

class MemObject {

public:

        // constructor
        MemObject() {
                std::cout << "MemObject constructor(no params) is called! addr:0x" 
                  << std::hex << data_ptr_ << " size:" << size_ << std::endl;
        } 

        explicit MemObject(size_t size) {
                data_ptr_ = malloc(size);
                if (nullptr == data_ptr_) {
                        throw std::runtime_error("MemObject init failed!");
                }
                
                size_ = size;

                std::cout << "MemObject constructor is called! addr:0x" 
                  << std::hex << data_ptr_ << std::dec << " size:" << size_  << std::endl;
        }

        // destructor
        ~MemObject() {
                free(data_ptr_);
                data_ptr_ = nullptr;
                size_ = 0;

                std::cout << "MemObject destructor is called!" << std::endl;
        }

        // copy constructor
        MemObject(MemObject &mem_object) {

                // release old mem object
                free(data_ptr_);
                data_ptr_ = nullptr;
                size_ = 0;

                // alloc new mem object
                data_ptr_ = malloc(mem_object.size_);
                if (nullptr == data_ptr_) {
                        throw std::runtime_error("MemObject init failed!");
                }
                
                size_ = mem_object.size_;
                memcpy(data_ptr_, mem_object.data_ptr_, size_);

                std::cout << "MemObject copy constructor is called! addr:0x" 
                  << std::hex << data_ptr_ << std::dec << " size:" << size_  << std::endl;
        }

        MemObject(const MemObject &mem_object) {

                // release old mem object
                free(data_ptr_);
                data_ptr_ = nullptr;
                size_ = 0;

                // alloc new mem object
                data_ptr_ = malloc(mem_object.size_);
                if (nullptr == data_ptr_) {
                        throw std::runtime_error("MemObject init failed!");
                }
                
                size_ = mem_object.size_;
                memcpy(data_ptr_, mem_object.data_ptr_, size_);

                std::cout << "MemObject const copy constructor is called! addr:0x" 
                  << std::hex << data_ptr_ << std::dec << " size:" << size_  << std::endl;
        }

        // move constructor
        MemObject(const MemObject &&mem_object) {

                // release old mem object
                free(data_ptr_);
                data_ptr_ = nullptr;
                size_ = 0;

                // alloc new mem object
                data_ptr_ = malloc(mem_object.size_);
                if (nullptr == data_ptr_) {
                        throw std::runtime_error("MemObject init failed!");
                }
                
                size_ = mem_object.size_;
                memcpy(data_ptr_, mem_object.data_ptr_, size_);

                std::cout << "MemObject move constructor is called! addr:0x" 
                  << std::hex << data_ptr_ << std::dec << " size:" << size_  << std::endl;
        }

        void* GetMemPtr() const { return data_ptr_; }
        size_t GetMemSize() const { return size_; }
        void LogInfo() const {
                std::cout << "addr:0x" << std::hex << data_ptr_
                          << std::dec << " size:" << size_ << std::endl;
        }

private:
        void *data_ptr_ = nullptr;
        size_t size_ = 0;
};

int main() {

        std::cout << "****************************************" << std::endl;   

        std::cout << "constructor and destructor" << std::endl;
        // constructor and destructor
        {
                MemObject mem_object_0;
                mem_object_0.LogInfo();
        }
        
        std::cout << "****************************************" << std::endl;   
        
        {
                MemObject mem_object_0(5);
                mem_object_0.LogInfo();
        }

        std::cout << "****************************************" << std::endl;   

        {
                MemObject mem_object_0 = static_cast<MemObject>(5);
                mem_object_0.LogInfo();
        }

        std::cout << "****************************************" << std::endl;   

        std::cout << "copy constructor" << std::endl;
        // copy constructor

        std::cout << "****************************************" << std::endl;   
        
        {
                MemObject mem_object_0(5);
                MemObject mem_object_1 = mem_object_0;
                mem_object_1.LogInfo();
        }

        std::cout << "****************************************" << std::endl;   
        
        {
                const MemObject mem_object_0(5);
                MemObject mem_object_1 = mem_object_0;
                mem_object_1.LogInfo();
        }

        std::cout << "****************************************" << std::endl;   

        std::cout << "move constructor" << std::endl;
        // move constructor

        {
                
                MemObject mem_object_0 = MemObject(1024);
                mem_object_0.LogInfo();
        }

        std::cout << "****************************************" << std::endl;   

        {
                MemObject mem_object_0(5); 
                MemObject mem_object_1 = std::move(mem_object_0);
                mem_object_1.LogInfo();
        }

        std::cout << "****************************************" << std::endl;   
        {
                MemObject &&mem_object_0 = MemObject(5);
                mem_object_0.LogInfo();
        }

        std::cout << "****************************************" << std::endl;   

        std::cout << "shared_ptr" << std::endl;
        // shared_ptr
        
        {
                std::shared_ptr<MemObject> ptr_0 = nullptr;
                {
                        std::shared_ptr<MemObject> ptr_1 = std::make_shared<MemObject>(1024);
                        ptr_0 = ptr_1;
                }

                std::cout << "ptr_1 is out of scope!" << std::endl;     

                ptr_0->LogInfo();
        }

        std::cout << "****************************************" << std::endl;   

        std::cout << "weak_ptr" << std::endl;
        // weak_ptr
        {
                std::weak_ptr<MemObject> ptr_0;
                {
                        std::shared_ptr<MemObject> ptr_1 = std::make_shared<MemObject>(1024);
                        ptr_0 = ptr_1;
                }
                std::cout << "ptr_1 is out of scope!" << std::endl;     
                
                if (ptr_0.expired()) {
                        std::cout << "ptr_0 is expired!" << std::endl;
                }

                std::shared_ptr<MemObject> ptr_2 = ptr_0.lock();
                if (nullptr == ptr_2) {
                        std::cout << "ptr_0 object is deleted!" << std::endl;
                }
        }

        std::cout << "****************************************" << std::endl;   

        {
                std::weak_ptr<MemObject> ptr_0;
                std::shared_ptr<MemObject> ptr_1;

                {
                        std::shared_ptr<MemObject> ptr_2 = std::make_shared<MemObject>(1024);
                        ptr_0 = ptr_2;
                        ptr_1 = ptr_2;
                }
                std::cout << "ptr_2 is out of scope!" << std::endl;     
                
                if (ptr_0.expired()) {
                        std::cout << "ptr_0 is expired!" << std::endl;
                }
                else {
                        std::cout << "ptr_0 is not expired!" << std::endl;
                }

                std::shared_ptr<MemObject> ptr_3 = ptr_0.lock();
                if (nullptr == ptr_3) {
                        std::cout << "ptr_0 object is deleted!" << std::endl;
                }
                else {
                        std::cout << "ptr_0 object is not deleted!" << std::endl;
                        ptr_3->LogInfo();
                }
        }

        std::cout << "****************************************" << std::endl;   

        std::cout << "unique_ptr" << std::endl;
        // unique_ptr

        // {
        //         std::unique_ptr<MemObject> ptr_0 = nullptr;
        //         {
        //                 std::unique_ptr<MemObject> ptr_1 = std::make_unique<MemObject>(1024);
        //                 // ptr_0 = ptr_1;
        //                 ptr_0 = std::move(ptr_1);
        //                 if (nullptr == ptr_1) {
        //                         std::cout << "no object managed by ptr_1" << std::endl;
        //                 }
        //         }

        //         ptr_0->LogInfo();
        // }

        std::cout << "****************************************" << std::endl;   

        return 0;
}

