#ifndef __DATA_STRUCT__
#define __DATA_STRUCT__
#include <utility>
#include <iostream>

struct data_struct
{

private:
  std::string _data_buff ;
  size_t _buff_size;

public:
  data_struct():_data_buff() {}
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
