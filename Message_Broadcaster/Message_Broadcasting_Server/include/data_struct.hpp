#ifndef __DATA_STRUCT__
#define __DATA_STRUCT__

#include <utility>

using CharAllocator = boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager>;
using SharedMemString = boost::interprocess::basic_string<char, std::char_traits<char>, CharAllocator>;

struct data_struct
{

private:
  SharedMemString _data_buff ;
  size_t _buff_size;

public:
  data_struct(const CharAllocator& alloc, size_t buff_size)
    :_data_buff(alloc)
    , _buff_size(buff_size)
    {}

  ~data_struct() = default;

  std::pair<const char*, size_t>get_buffer_and_size() const
  {
    return {_data_buff.c_str(), _buff_size};
  }

  void set_buffer_and_size(const char* data, const size_t &size)
  {
    _data_buff.clear();
    _buff_size = size;
    _data_buff.append(data, size);
  }
};

#endif
