#include <list>
#include <unordered_map>
#include <iostream>

template<class K, class V>
class LinkedMap {
 public:
  typedef typename std::pair<K,V> element_t;
  typedef typename std::list< element_t > list_t;
  typedef typename list_t::const_iterator iterator_t;
  typedef typename list_t::iterator nonconstIterator_t;
  typedef typename std::unordered_map<K, nonconstIterator_t > map_t;

  LinkedMap();
  virtual ~LinkedMap();
  LinkedMap( const LinkedMap<K,V> & copy );

  iterator_t begin() const;
  iterator_t end() const;
  bool empty() const;
  int size() const;

  const V & get(const K & k) const;
  V & get(const K & k);
  void clear();
  void erase( const K & k );

 private:
  list_t _data_list;
  map_t _data_map;
};

template<class K, class V>
LinkedMap<K,V>::LinkedMap() {}

template<class K, class V>
LinkedMap<K,V>::~LinkedMap() {}

template<class K, class V>
LinkedMap<K,V>::LinkedMap( const LinkedMap<K,V> & copy ) {
  this->_data_list = copy._data_list;
  nonconstIterator_t it = this->_data_list.begin();
  while( it != this->_data_list.end() ) {
    this->_data_map[it->first] = it;
    it++;
  }
}

//... implement the assignment operator

template<class K,class V>
typename LinkedMap<K,V>::iterator_t
LinkedMap<K,V>::begin() const {
  return _data_list.cbegin();
}

template<class K,class V>
typename LinkedMap<K,V>::iterator_t
LinkedMap<K,V>::end() const {
  return _data_list.cend();
}

template<class K,class V>
bool
LinkedMap<K,V>::empty() const {
  return _data_list.empty();
}

template<class K,class V>
int
LinkedMap<K,V>::size() const {
  return _data_list.size();
}

template<class K,class V>
V &
LinkedMap<K,V>::get(const K & k) {
  typename map_t::iterator it = _data_map.find(k);
  if( it == _data_map.end() ) {
    //insert new element!
    _data_list.push_back( element_t(k,V()) );
    nonconstIterator_t it2 = _data_list.end();
    it2--;
    _data_map[k] = it2;
    return _data_list.back().second;
  }
  return it->second->second;
}

template<class K,class V>
void
LinkedMap<K,V>::clear() {
  _data_map.clear();
  _data_list.clear();
}

template<class K,class V>
void
LinkedMap<K,V>::erase( const K & k ) {
  typename map_t::iterator it = _data_map.find(k);
  if( it != _data_map.end() ) {
    nonconstIterator_t & it2 = it->second;
    _data_map.erase(it);
    _data_list.erase(it2);
  }
}

int main() {
  std::unordered_map<int,double> umap;
  umap[1] = 1.0;
  umap[2] = 2.0;
  umap[0] = 0.0;
  std::unordered_map<int,double>::iterator it = umap.begin();
  while( it != umap.end() ) {
    std::cout << it->second << " ";
    it++;
  }
  std::cout << "\n";

  LinkedMap<int,double> linkedMap;
  linkedMap.get(1) = 1.0;
  linkedMap.get(2) = 2.0;
  linkedMap.get(0) = 0.0;
  LinkedMap<int,double>::iterator_t it2 = linkedMap.begin();
  while( it2 != linkedMap.end() ) {
    std::cout << it2->second << " ";
    it2++;
  }
  std::cout << "\n";

  return 0;
}