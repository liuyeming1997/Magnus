#include "mgpch.h"
#include "OpenGLBuffer.h"
#include "glad/glad.h"
namespace Magnus {
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, unsigned int size) {
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }
    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        glDeleteBuffers(1, &m_RendererID);
    }
    void OpenGLVertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLVertexBuffer::UnBind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }



    /////////////////////////////



    OpenGLIndexBuffer::OpenGLIndexBuffer(const unsigned int* data, unsigned int count)
        : m_Count(count) {
    
       glCreateBuffers(1, &m_RendererID);
       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
       glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    }
    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
       glDeleteBuffers(1, &m_RendererID);
    }
    void OpenGLIndexBuffer::Bind() const {
       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLIndexBuffer::UnBind() const {
       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}