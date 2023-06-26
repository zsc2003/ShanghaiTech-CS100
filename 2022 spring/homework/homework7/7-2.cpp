#include <cstddef>
#include <iterator>
#include <type_traits>
#include <utility>

// The node structure of the linked-list.
template <typename T>
struct Slist_node {
	T value;
	Slist_node<T> *next;
	// Add constructors if you need.
	Slist_node() = delete;//: next((Slist_node<T>)nullptr) {}
	Slist_node(T val) : value(val),next(nullptr) {}
	Slist_node(Slist_node &other) : value(other.val),next(nullptr) {}
};

// A declaration for the 'Slist' class.
template <typename T>
class Slist;

// When 'is_const' is true, this is a const_iterator.
// Otherwise, it is a normal iterator.
template <typename T, bool is_const>
class Slist_iterator {
public:
	// The 'using' declaration is used to declare type aliases, just as 'typedef'.
	// For example,
	//      typedef long long LL;
	// is equivalent to
	//      using LL = long long;
	// But the 'using' type alias declaration has more readability.
	
	// Every STL-style iterator should have the following five type aliases.
	// value_type:
	//      The type of values that can be obtained by dereferencing the iterator.
	// difference_type:
	//      A type that can be used to identify distance between iterators.
	//      It is most likely to be defined as 'ptrdiff_t'.
	// pointer:
	//      Defines a pointer to the type iterated over.
	//      Note: for a const_iterator, 'pointer' should be 'const T *'.
	// reference:
	//      Defines a reference to the type iterated over.
	//      Note: for a const_iterator, 'reference' should be 'const T &'.
	// iterator_category:
	//      The category of the iterator. All kinds of iterators are classified
	//      into five categories: input-iterator, output-iterator,
	//      forward-iterator, bidirectional-iterator and random-access-iterator.
	//      Since our Slist is a singly-linked list, the iterator can only be
	//      moved forward and cannot go backwards. So our iterator falls into the
	//      'forward_iterator' category.
	using value_type = T;//相当于define value_type T
	using difference_type = typename Slist<T>::difference_type;
	// What is std::conditional<...>::type? Have a guess.
	using pointer = typename std::conditional<is_const, const T *, T *>::type;//is_const=True返回第一个类型
	using reference = typename std::conditional<is_const, const T &, T &>::type;//否则第二个 
	using iterator_category = std::forward_iterator_tag;
	
private:
	using node_t = Slist_node<T>;
	using self_t = Slist_iterator<T, is_const>;
	
	// The current position that this iterator is pointing to.
	node_t *m_cur;
	
public:
	Slist_iterator(node_t *pos = nullptr) : m_cur(pos) {}
	
	// Allow conversion from iterator to const_iterator, but not vice versa.
	// You don't need to understand the definition of this function.
	template <typename Other,
				typename = typename std::enable_if<
				is_const &&
				std::is_same<Other, Slist_iterator<T, false>>::value>::type>
	Slist_iterator(const Other &oi) : m_cur(oi.base()) {}
	
	// You may need these two functions in your Slist.
	node_t *base() const {
		return m_cur;
	}
	
	self_t next() const {
		return self_t(m_cur->next);
	}
	
	// Dereference operator.
	reference operator*() const {
		return m_cur->value;
	}
	
	// This operator is a little bit tricky.
	// To work in consistence with operator*, it is always defined as follows.
	pointer operator->() const {
		return std::addressof(operator*());
	}
	
	// Prefix operator++, as in '++iter'.
	self_t &operator++() {
		m_cur=m_cur->next;
		return (self_t &)m_cur;
	}
	
	// Postfix operator++, as in 'iter++'.
	self_t operator++(int) {
		node_t *old_m_cur=m_cur;
		m_cur=m_cur->next;
		return old_m_cur;
	}
};

// Comparison between iterator and const_iterator should be allowed.
template <typename T, bool C1, bool C2>
inline bool operator==(const Slist_iterator<T, C1> &lhs,
						const Slist_iterator<T, C2> &rhs) {
	return lhs.base() == rhs.base();
}

template <typename T, bool C1, bool C2>
inline bool operator!=(const Slist_iterator<T, C1> &lhs,
						const Slist_iterator<T, C2> &rhs) {
	return !(lhs == rhs);
}

template <typename T>
class Slist {
public:
	// Every STL container should have the following type aliases.
	using value_type = T;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using pointer = T *;
	using reference = T &;
	using const_pointer = const T *;
	using const_reference = const T &;
	
	using iterator = Slist_iterator<T, false>;
	using const_iterator = Slist_iterator<T, true>;
	
private:
	using node_t = Slist_node<T>;
	
	// m_head is the head of the linked-list.
	// m_length is the number of elements stored in the list.
	node_t *m_head;
	size_type m_length;
	
public:
	// You also need to implement the default-constructor, copy-constructor,
	// copy-assignment operator and destructor.
	
	// The default-constructor initializes an empty linked-list.

	Slist() : m_length(0),m_head(nullptr) {}//default-constructor
	
	// Both the copy-constructor and the copy-assignment operator provide
	// 'value-semantics', which means that they copy all the elements stored in
	// the list instead of copying only the 'm_head' pointer.
	
	// For the copy-assignment operator, we highly recommend using the
	// 'copy-and-swap' technique. If you don't know what it is, you can refer to
	// the reference solution of hw5-1.
	
	Slist(const Slist &other)//copy-constructor
	{
		//cout<<"11111"<<'\n';
		m_length=other.m_length;
		node_t *other_now=other.m_head;
		if(other.m_head==nullptr)
		{
			m_head=nullptr;
			return;
		}
			
		m_head=new node_t(other_now->value);
		node_t *new_now=m_head;
		while(other_now->next!=nullptr)
		{
			other_now=other_now->next;
			new_now->next=new node_t(other_now->value);
			new_now=new_now->next;
		}
	}
	
	void swap(Slist &other)
	{
		std::swap(this->m_length,other.m_length);
		std::swap(this->m_head,other.m_head);
	}	
	Slist &operator=(const Slist &other)//copy-assignment operator
	{//copy-and-swap
		Slist(other).swap(*this);
  		return *this;
	}
	
	// The destructor should destroy every node and deallocate the memory they
	// take up.
	~Slist()
	{
		while(m_head!=nullptr)
		{
			node_t *nxt=m_head->next;
			delete m_head;
			m_head=nxt; 
		}
		m_length=0;
	}	
	
	//Note that we have defined the base() and next() functions in the Slist iterator class, which
	//you may find helpful
	// Insert an element with given value to be the front of the list.
	void push_front(const value_type &value) {
		++m_length;
		node_t *new_element = new node_t(value);
		new_element->next=m_head;
		m_head=new_element;
	}
	
	// Remove the element at the beginning of the list.
	void pop_front() {
		if(m_length<1)
			return;
		--m_length;
		node_t *to_delete=m_head;
		m_head=m_head->next;
		delete to_delete;
	}
	
	// Insert an element with given value after the position denoted by 'pos'.
	// Return an iterator pointing to the element that has been inserted.
	iterator insert_after(const_iterator pos, const value_type &value) {
		++m_length;
		node_t *insert=new node_t(value); 
		insert->next=pos.next().base();
		node_t *p=pos.base();
		p->next=insert;
		iterator to_return=iterator(insert);
		return to_return;
	}
	
	// Erase the element after the position denoted by 'pos'.
	void erase_after(const_iterator pos) {
		if(m_length<=1)
			return;
		--m_length;
		node_t *to_delete=pos.next().base();
		node_t *p=pos.base();
		p->next=to_delete->next;
		delete to_delete;		
	}
	
	// You also need to implement size(), empty(), clear(),
	// which all follow the STL fashion.
	
	// Note that:
	// size() should return a value of the type 'size_type'.
	// After clear(), the list should contain zero elements and size() == 0.
	
	size_type size() const {return m_length;}
	bool empty() const {return (m_length==0)?1:0;}
	void clear()
	{
		m_length=0;
		while(m_head!=nullptr)
		{
			node_t *nxt=m_head->next;
			delete m_head;
			m_head=nxt; 
		}
	}
	
	// The following are the well-known 'begin' and 'end' functions.
	iterator begin() {
		return iterator(m_head);
	}
	
	iterator end() {
		return iterator(nullptr);
	}
	
	// Why do we need these two functions? Think about this.
	const_iterator begin() const {
		return const_iterator(m_head);
	}
	
	const_iterator end() const {
		return const_iterator(nullptr);
	}
	
	// Note:
	// It was not until C++11 that cbegin() and cend() were added to the standard.
	const_iterator cbegin() const {
		return begin();
	}
	
	const_iterator cend() const {
		return end();
	}
};

// Two Slists are thought of as equal if and only if they are of the same
// length, and every pair of corresponding elements are equal.
// It is guaranteed that we will only use this operator when
// bool operator==(const T &, const T &) is defined.
// Hint: Use std::equal and the iterators you have defined.
template <typename T>
inline bool operator==(const Slist<T> &lhs, const Slist<T> &rhs) {
	if(lhs.size()!=rhs.size())
		return 0;
	return std::equal(lhs.begin(),lhs.end(),rhs.begin());
}

// Lexicographical-order comparison.
// It is guaranteed that we will only use this operator when
// bool operator<(const T &, const T &) is defined.
// Hint: Use std::lexicographical_compare and the iterators you have defined.
template <typename T>
inline bool operator<(const Slist<T> &lhs, const Slist<T> &rhs) {
//std::lexicographical_compare 字典序 
	return std::lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
}

// Why do we define the following functions like this? Think about it.
template <typename T>
inline bool operator!=(const Slist<T> &lhs, const Slist<T> &rhs) {
	return !(lhs == rhs);
}

template <typename T>
inline bool operator>(const Slist<T> &lhs, const Slist<T> &rhs) {
	return rhs < lhs;
}

template <typename T>
inline bool operator<=(const Slist<T> &lhs, const Slist<T> &rhs) {
	return !(lhs > rhs);
}

template <typename T>
inline bool operator>=(const Slist<T> &lhs, const Slist<T> &rhs) {
	return !(lhs < rhs);
}
