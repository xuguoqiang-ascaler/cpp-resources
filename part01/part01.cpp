
#include <vector>
#include <iostream>
#include <stdexcept>

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
                  << std::hex << data_ptr_ << " size:" << size_  << std::endl;
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

		std::cout << "MemObject copy constructor is called!" << std::endl;
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

		std::cout << "MemObject const copy constructor is called!" << std::endl;
	}

	void* GetMemPtr() const { return data_ptr_; }
	size_t GetMemSize() const { return size_; }
	void LogInfo() const {
		std::cout << "addr:0x" << std::hex << data_ptr_
                  << " size:" << size_ << std::endl;
	}

private:
	void *data_ptr_ = nullptr;
	size_t size_ = 0;
};

int main() {

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

	// copy constructor

	std::cout << "****************************************" << std::endl;	
	
	{
		MemObject mem_object_0(5);
		MemObject mem_object_1 = mem_object_0;
		mem_object_0.LogInfo();
	}

	std::cout << "****************************************" << std::endl;	
	
	{
		const MemObject mem_object_0(5);
		MemObject mem_object_1 = mem_object_0;
		mem_object_0.LogInfo();
	}

	std::cout << "****************************************" << std::endl;	
	return 0;
}
