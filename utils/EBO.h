#pragma once

#include <cstdint>
#include <glad/glad.h>

///////////////////////////////////////////////////////////////////////////////
/// Element Buffer Object (Index Array)
class EBO {
private:
  uint32_t m_ID;
  uint32_t m_count;
public:
  EBO(const uint32_t* indices, uint32_t count);
  // ~EBO();

  auto Bind() const -> void;
  auto Unbind() const -> void;
  auto Delete() const -> void;

  inline auto GetCount() const -> uint32_t { return m_count; }
};
