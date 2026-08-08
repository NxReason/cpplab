#pragma once

class VAO {
public:
  VAO(unsigned int stride = 0);

  template<typename T>
  void addAttrib(unsigned int size);

  void bind() const;
  void unbind() const;
  
  unsigned int getStride() const;
  void setStride(unsigned int stride);

  unsigned int getId() const;
private:
  unsigned int m_id;
  unsigned int m_stride;
  unsigned int m_index;
  unsigned long long m_offset;
};