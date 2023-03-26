#pragma once
#include <cstdint>
#include <stdexcept>
#include <sys/types.h>
#include <vector>
#include <glad/glad.h>

struct VBOElement {
  uint32_t type;
  uint32_t count;
  uint32_t normalized;

  static auto GetSizeOfType(uint32_t type) -> uint32_t {
    switch (type) {
      case GL_FLOAT:         return 4;
      case GL_UNSIGNED_INT:  return 4;
      case GL_UNSIGNED_BYTE: return 1;
    }
    return 0;
  }
};


class VBOLayout {
private:
  std::vector<VBOElement> m_elements;
  uint32_t m_stride;
public:
  VBOLayout() : m_stride{0} {};

  auto Push(uint32_t type, uint32_t count) -> void
  {
    m_elements.push_back({type, count, GL_FALSE});
    m_stride += VBOElement::GetSizeOfType(type) * count;
  }


  inline auto GetElements() const -> const std::vector<VBOElement>& { return m_elements; }
  inline auto GetStride() const -> uint32_t { return m_stride; }

};

  // template<>
  // auto VBOLayout::Push<float>(uint32_t count) -> void
  // {
  //   m_elements.push_back({GL_FLOAT, count, GL_FALSE});
  //   m_stride += VBOElement::GetSizeOfType(GL_FLOAT) * count;
  // }

  // template<>
  // auto VBOLayout::Push<uint32_t>(uint32_t count) -> void
  // {
  //   m_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
  //   m_stride += VBOElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
  // }
  // 
  // template<>
  // auto VBOLayout::Push<unsigned char>(uint32_t count) -> void
  // {
  //   m_elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
  //   m_stride += VBOElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
  // }

