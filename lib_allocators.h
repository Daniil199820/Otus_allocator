#pragma once

#include <memory>

template <typename T, std::size_t block_size>
struct myLinear_allocator {

	using value_type = T;

	using pointer = T * ;
	using const_pointer = const T *;
	using reference = T & ;
	using const_reference = const T &;


	T* Create_pool()
	{
		auto p = std::malloc((block_size+1) * sizeof(T));
		if (!p)
			throw std::bad_alloc();
		begin_block = reinterpret_cast<T *>(p);
		used_block = begin_block;
		end_block = reinterpret_cast<T *>(begin_block + block_size+1);

		return begin_block;
	}

	template <typename U>
	struct rebind {
		using other = myLinear_allocator<U,block_size>;
	};

	myLinear_allocator() = default ;
	~myLinear_allocator() = default;

	template <typename U>
	myLinear_allocator(const myLinear_allocator<U,block_size> &) {
	}

	T *allocate(std::size_t n) {

		if(used_block==nullptr)
		{
			return Create_pool();
		}

		used_block = used_block + n;
		if(used_block>=end_block)throw std::bad_alloc();
		return(used_block);


	}

	template <typename U, typename... Args>
	void construct(U *p, Args &&...args) {
		new (p) U(std::forward<Args>(args)...);
	};

	void deallocate(T *p, std::size_t n) {

	//	if (p==nullptr)
	//		return;
	//	free(begin_block);
	//	begin_block = nullptr;
		//if (begin_block != nullptr)
	//	{
		//	std::free(begin_block);
	//		begin_block = end_block = used_block = nullptr;
	//	}


	}

	template <typename U>
	void destroy(U *p) {

		p->~U();

	}

private:
	T* used_block = nullptr;
	T* begin_block = nullptr;
	T* end_block = nullptr;
};