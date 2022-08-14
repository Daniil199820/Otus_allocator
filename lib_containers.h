#pragma once

#include<memory>

namespace my_containers
{

	template<typename T, typename cust_alloc = std::allocator<T>>
	class list {
	public:

		// Create custom nodes 
		struct node {
			T val;
			node* next;
			node* previous;

			node() { val = 0; next = nullptr; previous = nullptr; }

			template<typename ...Args>
			explicit node(Args &&...args) : val(std::forward<Args>(args)...), next(nullptr), previous(nullptr) {}
		};

		/////////////////----------------------//////////////////////////

		// Create custom list_iterator 
		struct list_iterator {

			using value_type = T;

			using pointer = const T*;

			using reference = const T&;

			using iterator_category = std::bidirectional_iterator_tag;


			node* _node;

			list_iterator() {}

			list_iterator(node* pointer_node) : _node(pointer_node) {}

			const T& operator* () const
			{
				return _node->val;
			}

			const T* operator->() const
			{
				return &(_node->val);
			}

			list_iterator& operator++()
			{
				if (_node == nullptr) return *this;

				else _node = _node->next;

				return *this;
			}

			list_iterator& operator--()
			{
				if (_node == nullptr) return *this;

				else _node = _node->previous;

				return *this;
			}

			bool operator ==(const list_iterator& arg_list_iterator)
			{
				return _node == arg_list_iterator._node;
			}

			bool operator !=(const list_iterator& arg_list_iterator)
			{
				return _node != arg_list_iterator._node;
			}
		};

		///////////////////////-------------------/////////////////////////////////

		//Create list 

	private:
		node* head = nullptr;
		node* tail = nullptr;
		typename cust_alloc::template rebind<node>::other  _alloc;

	public:

		//constructor 
		list() :head(nullptr), tail(nullptr), _alloc() {}


		//push_back method in container
		template <typename ...Args>
		void push_back(Args &&...args) {

			node* n_node = _alloc.allocate(1);
			_alloc.construct(n_node, std::forward<Args>(args)...);

			///// If List is empty
			if (head == nullptr) {
				head = n_node;
				tail = n_node;
			}
			else {
				tail->next = n_node;
				tail = n_node;
				tail->next = nullptr;
			}
		}

		//iterator for beginning
		list_iterator& cbegin() const 
		{
			return &list_iterator(head);
		}

		//iterator for ending
		list_iterator& cend() const
		{
			return &list_iterator();
		}

        bool empty() const
        {
            return (head==nullptr);
        }

		//copy constructor
		template<typename ALLOCATOR>
		list(const list<T, ALLOCATOR>& copy_list):head(nullptr),tail(nullptr),_alloc()
		{
			node* current_node = copy_list.cbegin()._node;
			while(current_node!= nullptr)
			{
				copy_list.push_back(current_node->val);
				current_node = current_node->next;
			}
		}

		//destructor
		~list()
		{
			node* current_node = head;
			while (current_node != nullptr)
			{
				auto temp_node = current_node;
				current_node = current_node->next;
				_alloc.destroy(temp_node);
				_alloc.deallocate(temp_node,1);
			}
		}

        void print()
        {
            node* current_node = head;
			while(current_node!= nullptr)
			{
                std::cout<<current_node->val<<std::endl;
				current_node = current_node->next;
			}
        }

	};
}